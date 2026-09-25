#pragma once

// ============================================================
// PIN MAP — matches the KiCad schematic wiring table
// ============================================================
// Driver A = U1, UART address 0 (MS1/AD0 tied to GND)
//   -> physically wired to motor connector J6 ("Motor 2" on schematic)
// Driver B = U2, UART address 1 (MS1/AD0 tied to VCC_IO)
//   -> physically wired to motor connector J5 ("Motor 1" on schematic)
// If you want the silkscreen labels to match, swap the two
// TMC2209Stepper objects in the .ino instead of rewiring.

#define STEP_A_PIN   2
#define DIR_A_PIN    3
#define EN_A_PIN     4
#define DIAG_A_PIN   5

#define STEP_B_PIN   6
#define DIR_B_PIN    7
#define EN_B_PIN     8
#define DIAG_B_PIN   9

#define BUZZER_PIN   10
#define BUTTON_PIN   11

// UART bus: shared PD/UART line on both drivers, joined to
// Arduino D0 (RX) / D1 (TX) through the 1k resistor (R1).
// This means the USB serial monitor is NOT available for debug
// prints while the drivers are active — use the OLED for status.
#define DRIVER_ADDR_A   0b00
#define DRIVER_ADDR_B   0b01
#define R_SENSE         0.11f   // check your TMC2209 module's sense resistor silkscreen — common value, not guaranteed

// ============================================================
// MOTION / CoreXY CONSTANTS — tune these to your actual build
// ============================================================
#define STEPS_PER_REV     200     // 1.8° NEMA17
#define MICROSTEPS        16      // set to match driver config below
#define PULLEY_TEETH      20      // GT2 20T pulley
#define BELT_PITCH_MM     2.0f    // GT2 = 2mm pitch
#define MM_PER_REV        (PULLEY_TEETH * BELT_PITCH_MM)                // 40mm
#define STEPS_PER_MM      ((STEPS_PER_REV * MICROSTEPS) / MM_PER_REV)   // 80 steps/mm at 16x

#define HOMING_SPEED_SPS      400   // steps/sec while seeking the stall
#define HOMING_ACCEL_SPS2     200
#define HOMING_BACKOFF_MM     5.0f
#define HOMING_MAX_TRAVEL_MM  350.0f  // generous over-travel bound, stall should trigger well before this

#define RUN_SPEED_SPS     2000
#define RUN_ACCEL_SPS2    1500

#define STALLGUARD_THRESHOLD  70   // 0-255, LOWER = more sensitive. Start high, lower until it triggers reliably without false-triggering mid-move
#define MOTOR_RMS_CURRENT_MA  1200 // set below your motor's rated current, raise only if it's losing steps

// ============================================================
// BOARD GEOMETRY
// ============================================================
#define BOARD_SIZE       10        // 10x10 squares = 100 squares
#define SQUARE_SIZE_MM    30.0f    // 300mm board / 10

// ============================================================
// SNAKES & LADDERS MAP — edit to match your printed board
// Format: {from, to}. from > to = snake, from < to = ladder.
// ============================================================
struct JumpPair { int from; int to; };

const JumpPair SNAKES_AND_LADDERS[] = {
  {4, 25},   // ladder
  {13, 46},  // ladder
  {33, 49},  // ladder
  {42, 63},  // ladder
  {50, 69},  // ladder
  {62, 81},  // ladder
  {74, 92},  // ladder
  {27, 5},   // snake
  {40, 3},   // snake
  {43, 18},  // snake
  {54, 31},  // snake
  {66, 45},  // snake
  {76, 58},  // snake
  {89, 53},  // snake
  {99, 41},  // snake
};
const int NUM_JUMPS = sizeof(SNAKES_AND_LADDERS) / sizeof(JumpPair);
