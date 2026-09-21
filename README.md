# Automatic Snakes and Ladders Board

![Status](https://img.shields.io/badge/status-work_in_progress-orange)
![Licence](https://img.shields.io/badge/licence-CC_BY--NC--SA_4.0-blue)
![Platform](https://img.shields.io/badge/platform-Arduino_Uno-teal)

A Snakes and Ladders board that plays against you. A CoreXY belt mechanism hidden under the board moves a magnetic gondola, which drags the machine's playing piece across the squares from below. Homing is sensorless (TMC2209 StallGuard), so there are no limit switches.

> **Status: work in progress.** Hardware is being sourced. Firmware is not written yet. Items marked `[TBC]` are not finalised. Do not order parts from this README until those are resolved.

[PHOTO OR GIF OF THE BOARD: add when built]

---

## Table of contents

1. [Overview](#overview)
   - [Features](#features)
   - [How it plays](#how-it-plays)
2. [How it works](#how-it-works)
   - [Mechanics](#mechanics)
   - [Electronics](#electronics)
3. [Bill of materials](#bill-of-materials)
   - [Motion parts](#motion-parts)
   - [Electronic parts](#electronic-parts)
   - [Fasteners](#fasteners)
   - [Printed parts](#printed-parts)
   - [Tools](#tools)
4. [Board dimensions](#board-dimensions)
5. [Wiring](#wiring)
   - [Wiring notes](#wiring-notes)
     - [Drivers](#drivers)
     - [Motors](#motors)
     - [Power](#power)
   - [Wiring diagram](#wiring-diagram)
6. [Roadmap](#roadmap)
7. [Licence](#licence)
8. [Author](#author)

---

## Overview

### Features

- Plays a full game of Snakes and Ladders against one human
- Moves its own piece from under the board with a magnet, no visible mechanism
- Counts out each move square by square, the way a player would
- CoreXY motion with two fixed motors
- Sensorless homing, no limit switches
- Dice roll on an OLED display, triggered by a push button
- Runs on an Arduino Uno with a CNC Shield attached

### How it plays

- One human versus the machine.
- The human presses the button to roll. The dice result shows on the OLED display.
- The human moves their own piece by hand. The machine tracks the human's position in software.
- The machine rolls for itself and moves its own piece with the gondola.
- The machine's piece moves square by square. It does not jump straight to the destination.
- Landing on a snake or ladder triggers a move to the destination square.
- The human's piece has no magnet, so the gondola does not disturb it when passing underneath.

[Back to top](#table-of-contents)

---

## How it works

### Mechanics

- CoreXY belt layout: two fixed motors drive two GT2 belts. Neither motor rides on the gantry.
- Layout: 2 fixed Y rods, 2 fixed rods for structural stability, a gantry block on each carrying 2 X rods, carriage in the middle, motors at the front corners.
- 10 mm smooth rods with linear bearing blocks, held by rod supports.
- A magnet stack in the gondola moves the machine's piece through the board.
- Printed parts are made on a Bambu Lab P2S and use M5 heat-set inserts.

### Electronics

- Arduino Uno R3 with CNC Shield V3
- 2x TMC2209 stepper drivers, configured over UART
- Sensorless homing: each driver's DIAG output is wired to a limit input, and the StallGuard threshold is set over UART
- 1.3 inch I2C OLED for dice and messages
- 16 mm illuminated push button (Lanboo LB16QC, 5-24 V, 1NO) to roll
- 5 V active buzzer
- 12 V 5 A supply with a rocker switch on the 12 V positive line

[Back to top](#table-of-contents)

---

## Bill of materials

### Motion parts

| Qty | Part |
|---|---|
| 2 | StepperOnline 17HE15-1504S NEMA17 (42 N·cm, 1.5 A, 1 m detachable cable) |
| 2 | GT2 20-tooth pulley, 5 mm bore, for 6 mm belt |
| 8 | GT2 idler, 5 mm bore, for 6 mm belt |
| 2 | 2 meter GT2 open belt, 6 mm wide |
| 6 | 10 mm hardened smooth rod |
| 8 | SK10 (SH10A) rod support |
| 4 | SC10UU linear bearing block |
| 1 pack | 12 x 2 mm N35 neodymium disc magnets (pack of 20) |

### Electronic parts

| Qty | Part |
|---|---|
| 1 | Arduino Uno R3 with USB cable |
| 1 | CNC Shield V3 |
| 2 | TMC2209 stepper driver module with heatsink (must expose DIAG and UART pins) |
| 1 | 12 V 5 A power supply, 5.5 mm DC plug |
| 1 | DC jack socket (female) with moulded wire lead |
| 1 | DC Y-splitter cable (1 female to 2 male) |
| 1 | Rocker switch, 6 A |
| 1 | 1.3 inch I2C OLED display |
| 1 | Lanboo LB16QC-P10F 16 mm illuminated push button, blue, 5-24 V, 1NO |
| 1 | 5 V active buzzer |
| 1 | 1 kΩ resistor (UART TX to RX link) |
| 2 | 1000 µF 25 V electrolytic capacitor (12 V input) |
| 3 (2 works) | 100 µF 35 V electrolytic capacitor (driver VMOT) |
| 1 set | Dupont jumper wires, female-female and male-female |
| as needed | 3 mm heat shrink sleeve |

### Fasteners

- M5 heat-set inserts
- M5 bolts (rod supports, bearing blocks, idler axles)
- M3 x 8 bolts (motor mounting)
- Washers or shims for idler stacks

### Printed parts

`[TBC: list of STL files once CAD is final]`

### Tools

- Soldering iron and solder
- Multimeter
- 3D printer (parts here are made on a Bambu Lab P2S)

[Back to top](#table-of-contents)

---

## Board dimensions

| Item | Value |
|---|---|
| Board size | `[TBC]` |
| Square size | `[TBC]` |
| Rod length | `[TBC]` |
| Gondola travel X / Y | `[TBC]` |
| Board thickness over gondola | `[TBC]` |

[Back to top](#table-of-contents)

---

## Wiring

### Wiring notes

#### Drivers

- Both TMC2209 drivers share one UART line. They are addressed through MS1/MS2: driver 1 with no jumpers (address 0), driver 2 with the M0 jumper fitted (address 1). Microstepping is set by register.
- Leave the M2 jumper position open on the CNC Shield. On most TMC2209 modules that position lands on a UART pin. Check the pinout of your module.
- DIAG is active-high. The CNC Shield limit inputs expect active-low switches, so the input is inverted in firmware.

#### Motors

- Check motor coil pairs with a multimeter before plugging in. Cable pin order may not match the shield.
- **Never connect or disconnect a motor while the drivers are powered.** This can destroy the driver.

#### Power

- The rocker switch sits on the 12 V positive line before the Y-splitter, so it cuts power to both the Uno and the shield.
- The TMC2209 drivers lose their UART configuration when 12 V is removed. Configuration and homing run in `setup()`.

### Wiring diagram

[WIRING DIAGRAM: add when final]

[Back to top](#table-of-contents)

---

## Roadmap

- [ ] Finalise board size and rod length
- [ ] Finish sourcing parts
- [ ] CAD for base plate, gantry blocks, carriage, motor mounts and idler blocks
- [ ] Test magnet coupling through the board
- [ ] Firmware: TMC2209 UART setup and sensorless homing
- [ ] Firmware: CoreXY motion and square-by-square moves
- [ ] Firmware: game logic, OLED, button and buzzer
- [ ] Build guide and photos

[Back to top](#table-of-contents)

---

## Licence

Licensed under CC BY-NC-SA 4.0. See [LICENSE](LICENSE).

Personal, educational and classroom use is welcome. You may build it, modify it and share your changes under the same licence, with credit.

Selling is not permitted: no assembled units, kits, printed parts, files or firmware, original or modified. For commercial licensing, contact me.

This project is source-available, not open source as defined by OSI or OSHWA.

Third-party libraries remain under their own licences.

[Back to top](#table-of-contents)

---

## Author

Krish Sanwal
https://github.com/KrishSanwal
