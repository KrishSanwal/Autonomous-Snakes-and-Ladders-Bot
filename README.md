# Automatic Snakes and Ladders Board

![Status](https://img.shields.io/badge/status-work_in_progress-orange)
![Licence](https://img.shields.io/badge/licence-CC_BY--NC--SA_4.0-blue)
![Platform](https://img.shields.io/badge/platform-Arduino_Uno-teal)

A Snakes and Ladders board that plays against a human. A CoreXY mechanism is used under the board and it moves a gondola connected to a magnet, which drags the machine's piece across the board. Homing is sensorless, so there are no limit switches.

> **Status: work in progress.** Hardware is being sourced. Firmware is not written yet. Items marked `[TBC]` are not finalised. Do not order parts from this README until those are resolved.

---

## Table of contents

1. [Overview](#overview)
   - [Features](#features)
2. [How it works](#how-it-works)
   - [Mechanics](#mechanics)
   - [Electronics](#electronics)
3. [Bill of materials](#bill-of-materials)
   - [Motion parts](#motion-parts)
   - [Electronic parts](#electronic-parts)
   - [Fasteners](#fasteners)
   - [Printed parts](#printed-parts)
   - [Tools](#tools)
4. [Licence](#licence)
5. [Author](#author)

---

## Overview

### Features

- Plays a game of Snakes and Ladders against a human.
- Moves its own piece from under the board with a magnet, no visible mechanism.
- Remembers the position of the human's piece and it's piece so it knows who won.
- Sensor-less homing and therefore no limit switches are needed.
- Dice is rolled on an OLED display using a button.
- Runs on an Arduino Uno with a CNC Shield unit on it.

[Back to top](#table-of-contents)

---

## How it works

### Mechanics

- CoreXY belt layout: two fixed motors drive two GT2 belts (design inspired from bambulab 3d printers).
- Layout: 2 fixed Y rods, 4 fixed rods for structural stability, motors are on the bottom corners.
- 10 mm smooth rods with linear bearing blocks, held by rod supports.
- A magnet stack in the gondola moves the machine's piece.

### Electronics

- Arduino Uno R3 with CNC Shield V3
- 2x NEMA 17 Stepper Motors
- 2x TMC2209 stepper drivers
- 1.3 inch I2C OLED for dice and messages
- 16 mm illuminated push button (Lanboo LB16QC, 5-24 V, 1NO)
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
