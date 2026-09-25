// Autonomous Snakes & Ladders Bot
// CoreXY gondola under the board drags a magnetic piece to each square.
// TMC2209 sensorless homing, shared single-wire UART, OLED status display.
//
// Libraries required (Library Manager):
//   TMCStepper      by teemuatlut
//   AccelStepper    by Mike McCauley
//   Adafruit GFX Library
//   Adafruit SSD1306

#include <TMCStepper.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "config.h"

// ---- drivers (share one Serial/UART bus, told apart by address) ----
TMC2209Stepper driverA(&Serial, R_SENSE, DRIVER_ADDR_A);
TMC2209Stepper driverB(&Serial, R_SENSE, DRIVER_ADDR_B);

// ---- steppers ----
AccelStepper stepperA(AccelStepper::DRIVER, STEP_A_PIN, DIR_A_PIN);
AccelStepper stepperB(AccelStepper::DRIVER, STEP_B_PIN, DIR_B_PIN);

// ---- OLED ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// The bot only has a magnet for its OWN piece, but the roll (dice) is
// onboard and used for BOTH turns, so software has to track both
// players' squares to know who's ahead and who's won.
int humanSquare = 1;
int botSquare = 1;

// EEPROM layout: [0]=magic byte, [1]=humanSquare, [2]=botSquare
#define EEPROM_MAGIC_ADDR    0
#define EEPROM_HUMAN_ADDR    1
#define EEPROM_BOT_ADDR      2
#define EEPROM_MAGIC_VALUE   0x5A   // marks "state has been saved at least once"

void saveState() {
  EEPROM.update(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_VALUE);
  EEPROM.update(EEPROM_HUMAN_ADDR, (uint8_t)humanSquare);
  EEPROM.update(EEPROM_BOT_ADDR, (uint8_t)botSquare);
}

bool loadState() {
  if (EEPROM.read(EEPROM_MAGIC_ADDR) != EEPROM_MAGIC_VALUE) return false; // nothing saved yet
  humanSquare = EEPROM.read(EEPROM_HUMAN_ADDR);
  botSquare = EEPROM.read(EEPROM_BOT_ADDR);
  if (humanSquare < 1 || humanSquare > 100) humanSquare = 1; // sanity check
  if (botSquare < 1 || botSquare > 100) botSquare = 1;
  return true;
}

// ============================================================
// SETUP
// ============================================================
void setup() {
  pinMode(EN_A_PIN, OUTPUT);
  pinMode(EN_B_PIN, OUTPUT);
  pinMode(DIAG_A_PIN, INPUT);
  pinMode(DIAG_B_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(EN_A_PIN, LOW);   // active LOW = enabled
  digitalWrite(EN_B_PIN, LOW);

  Serial.begin(115200);          // this is the shared TMC2209 UART bus, not a USB debug console
  driverA.begin();
  driverB.begin();
  setupDriver(driverA);
  setupDriver(driverB);

  stepperA.setMaxSpeed(RUN_SPEED_SPS);
  stepperA.setAcceleration(RUN_ACCEL_SPS2);
  stepperB.setMaxSpeed(RUN_SPEED_SPS);
  stepperB.setAcceleration(RUN_ACCEL_SPS2);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showMessage("Booting...");

  randomSeed(analogRead(A0));   // leave A0 floating/unconnected — needed for real randomness

  bool resumed = loadState();   // false on very first boot ever, or if EEPROM was blank

  homeAxes();                    // motors always need a fresh physical reference after power-up

  if (!resumed) {
    humanSquare = 1;
    botSquare = 1;
    saveState();
  }
  moveToSquare(botSquare);       // put the gondola back where the bot's piece actually was
  showStatus();
}

// Common per-driver config. TMC2209 loses this on every power cycle,
// which is why it lives in setup() rather than being a one-time flash.
void setupDriver(TMC2209Stepper &drv) {
  drv.toff(5);
  drv.rms_current(MOTOR_RMS_CURRENT_MA);
  drv.microsteps(MICROSTEPS);
  drv.en_spreadCycle(false);      // stealthChop for quiet running
  drv.pwm_autoscale(true);
  drv.TCOOLTHRS(0xFFFFF);         // enable StallGuard across full speed range for homing
  drv.SGTHRS(STALLGUARD_THRESHOLD);
}

// ============================================================
// MAIN LOOP
// ============================================================
bool gameOver = false;

void loop() {
  if (!gameOver && digitalRead(BUTTON_PIN) == LOW) {
    delay(30);                    // debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      playRound();
      while (digitalRead(BUTTON_PIN) == LOW) { /* wait for release */ }
    }
  }
}

// ============================================================
// GAME LOGIC
// One button press = one full round: human rolls (onboard dice,
// software-only move — human slides their own piece by hand to
// match the displayed number), then the bot auto-rolls and the
// gondola physically drives its piece there.
// ============================================================
void playRound() {
  // ---- human's roll ----
  int humanRoll = random(1, 7);
  showMessage(("Your roll: " + String(humanRoll)).c_str());
  beep(1);
  delay(1200);   // give them time to read it and move their piece by hand

  int humanTarget = humanSquare + humanRoll;
  if (humanTarget > 100) humanTarget = humanSquare; // must land exactly on 100
  humanSquare = applyJump(humanTarget, false);
  saveState();   // saved here, after humanSquare holds the final post-jump value

  if (humanSquare == 100) {
    endGame("You win!");
    return;
  }

  // ---- bot's roll, automatic, no second button press ----
  delay(600);
  int botRoll = random(1, 7);
  showMessage(("Bot roll: " + String(botRoll)).c_str());
  delay(500);

  int botTarget = botSquare + botRoll;
  if (botTarget > 100) botTarget = botSquare;

  moveToSquare(botTarget);
  botSquare = botTarget;
  saveState();   // save right after the physical move so gondola position always matches saved square

  botSquare = applyJump(botSquare, true);
  saveState();   // saved here, after botSquare holds the final post-jump value

  if (botSquare == 100) {
    endGame("Bot wins!");
    return;
  }

  showStatus();
}

// Checks a square for a snake/ladder, beeps, and — for the bot only —
// physically drives the gondola to the destination. Returns the
// final resting square after any jump.
int applyJump(int square, bool isBot) {
  int jumped = checkSnakeOrLadder(square);
  if (jumped == square) {
    beep(1);
    return square;
  }
  delay(400);
  bool isLadder = jumped > square;
  beep(isLadder ? 2 : 1);         // 2 short beeps = ladder, 1 long = snake
  if (isBot) {
    moveToSquare(jumped);
  }
  return jumped;
}

void endGame(const char *msg) {
  gameOver = true;
  saveState();
  showMessage(msg);
}

int checkSnakeOrLadder(int square) {
  for (int i = 0; i < NUM_JUMPS; i++) {
    if (SNAKES_AND_LADDERS[i].from == square) {
      return SNAKES_AND_LADDERS[i].to;
    }
  }
  return square;
}

// ============================================================
// SQUARE -> BOARD COORDINATE (boustrophedon numbering)
// Square 1 = bottom-left, row 0 goes left->right,
// row 1 goes right->left, and so on.
// ============================================================
void squareToXY(int square, float &xmm, float &ymm) {
  int idx = square - 1;
  int row = idx / BOARD_SIZE;
  int col = idx % BOARD_SIZE;
  if (row % 2 == 1) col = (BOARD_SIZE - 1) - col;

  xmm = col * SQUARE_SIZE_MM + SQUARE_SIZE_MM / 2.0f;
  ymm = row * SQUARE_SIZE_MM + SQUARE_SIZE_MM / 2.0f;
}

void moveToSquare(int square) {
  float x, y;
  squareToXY(square, x, y);
  moveToXY(x, y);
}

// ============================================================
// CoreXY MOTION
// stepsA = x + y, stepsB = x - y  (relative to the homed corner)
// ============================================================
void moveToXY(float xmm, float ymm) {
  long xSteps = lround(xmm * STEPS_PER_MM);
  long ySteps = lround(ymm * STEPS_PER_MM);

  long targetA = xSteps + ySteps;
  long targetB = xSteps - ySteps;

  stepperA.moveTo(targetA);
  stepperB.moveTo(targetB);

  while (stepperA.distanceToGo() != 0 || stepperB.distanceToGo() != 0) {
    stepperA.run();
    stepperB.run();
  }
}

// ============================================================
// SENSORLESS HOMING
// Moves both motors together (equal sign = pure X, opposite
// sign = pure Y) until either DIAG pin flags a stall.
// ============================================================
void homeAxes() {
  showMessage("Homing X...");
  homeOneAxis(true);   // pure X
  showMessage("Homing Y...");
  homeOneAxis(false);  // pure Y

  stepperA.setCurrentPosition(0);
  stepperB.setCurrentPosition(0);
}

void homeOneAxis(bool isX) {
  long maxSteps = lround(HOMING_MAX_TRAVEL_MM * STEPS_PER_MM);
  long backoffSteps = lround(HOMING_BACKOFF_MM * STEPS_PER_MM);

  stepperA.setMaxSpeed(HOMING_SPEED_SPS);
  stepperA.setAcceleration(HOMING_ACCEL_SPS2);
  stepperB.setMaxSpeed(HOMING_SPEED_SPS);
  stepperB.setAcceleration(HOMING_ACCEL_SPS2);

  // isX: both motors move the same direction -> pure X travel
  // !isX: motors move opposite directions -> pure Y travel
  stepperA.move(-maxSteps);
  stepperB.move(isX ? -maxSteps : maxSteps);

  bool stalled = false;
  while (!stalled && (stepperA.distanceToGo() != 0 || stepperB.distanceToGo() != 0)) {
    if (digitalRead(DIAG_A_PIN) == HIGH || digitalRead(DIAG_B_PIN) == HIGH) {
      stalled = true;
      break;
    }
    stepperA.run();
    stepperB.run();
  }

  stepperA.stop();
  stepperB.stop();
  stepperA.setCurrentPosition(stepperA.currentPosition());
  stepperB.setCurrentPosition(stepperB.currentPosition());

  // back off the corner
  stepperA.move(isX ? backoffSteps : backoffSteps);
  stepperB.move(isX ? backoffSteps : -backoffSteps);
  while (stepperA.distanceToGo() != 0 || stepperB.distanceToGo() != 0) {
    stepperA.run();
    stepperB.run();
  }

  stepperA.setMaxSpeed(RUN_SPEED_SPS);
  stepperA.setAcceleration(RUN_ACCEL_SPS2);
  stepperB.setMaxSpeed(RUN_SPEED_SPS);
  stepperB.setAcceleration(RUN_ACCEL_SPS2);
}

// ============================================================
// OLED + BUZZER HELPERS
// ============================================================
void showMessage(const char *msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
}

void showStatus() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Snakes & Ladders");
  display.setCursor(0, 16);
  display.print("You: ");
  display.println(humanSquare);
  display.setCursor(0, 28);
  display.print("Bot: ");
  display.println(botSquare);
  display.setCursor(0, 50);
  display.println("Press button to roll");
  display.display();
}

void beep(int times) {
  for (int i = 0; i < times; i++) {
    tone(BUZZER_PIN, 2000, 150);
    delay(200);
  }
}
