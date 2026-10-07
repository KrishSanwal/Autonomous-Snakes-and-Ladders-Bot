# Automatic Snakes and Ladders Board

![Status](https://img.shields.io/badge/status-work_in_progress-orange)
![Licence](https://img.shields.io/badge/licence-CC_BY--NC--SA_4.0-blue)
![Platform](https://img.shields.io/badge/platform-Arduino_Uno-teal)

A Snakes and Ladders board that plays against a human. A CoreXY mechanism is used under the board and it moves a gondola connected to a magnet, which drags the machine's piece across the board. Features sensorless homing as seen in many FDM printers.

> **Status: work in progress.** Hardware is being sourced. Firmware is not written yet. Items marked `[TBC]` are not finalised. Do not order parts from this README until those are resolved.

---

## Table of contents

1. [Overview](#overview)
   - [Features](#features)
2. [How it works](#how-it-works)
   - [Electronics](#electronics)
3. [Bill of materials](#bill-of-materials)
   - [Motion parts](#motion-parts)
   - [Electronic parts](#electronic-parts)
   - [Fasteners](#fasteners)
   - [Tools](#tools)
4. [3D Files](#3d-files)
   - [Full System](#full-system)
   - [Outer Frame](#outer-frame)
   - [Gondola System](#gondola-system)
6. [Wiring Diagram](#wiring-diagram)
7. [Licence](#licence)
8. [Author](#author)

---

## Overview

### Features

- Plays a game of Snakes and Ladders against a human.
- Moves its own piece from under the board with a magnet, no visible mechanism.
- Remembers the position of the human's piece and it's piece so it knows who won.
- Sensor-less homing and therefore no limit switches are needed.
- Dice is rolled on an OLED display using a button.
- Runs on an Arduino Uno with a CNC Shield unit on it.


---

## How it works

This board uses a CoreXY Mechanism that consists of two static motors (motors don't move) on the front end of the board that control the main magnetic piece using timing belts. The movement happens by spinning either one of the motors or both of them. The motors move the magnetic gondola to set positions that translate to movement on the top board surface where a magnetic piece moves with the gondola. The game is played turn based and the dice is on a OLED screen activated by a push button. An E-Dice will help the machine know how much to move and also helps to tell the machine if the player has reached the end without the use of any physical sensors.

### Electronics

- Arduino Uno R3 with CNC Shield V3
- 2x NEMA 17 Stepper Motors
- 2x TMC2209 stepper drivers
- 1.3 inch I2C OLED for dice and messages
- 16 mm illuminated push button (Lanboo LB16QC, 5-24 V, 1NO)
- 5 V active buzzer
- 12 V 5 A supply with a rocker switch on the 12 V positive line


---

## Bill of materials

### Motion parts

| Qty | Part | Price (USD) | Price (INR) | Link |
|---:|---|---:|---:|---|
| 2 | StepperOnline 17HE15-1504S NEMA17 (42 N·cm, 1.5 A, 1 m detachable cable) | $15.64 | ₹1,498.00 | [Robu](https://robu.in/product/stepperonline-nema-17-42ncm-bipolar-stepper-motor/) |
| 2 (1 pack) | Aluminium GT2 20-tooth pulley, 5 mm bore, for 6 mm belt | $1.37 | ₹131.00 | [Robu](https://robu.in/product/aluminum-gt2-timing-pulley-for-6mm-belt-20-tooth-5mm-bore-2pcs/) |
| 8 | Flyrobo GT2 idler pulley without teeth, 5 mm bore, for 6 mm belt | $23.64 | ₹2,264.00 | [Amazon](https://www.amazon.in/gp/product/B0H7K3W1P3) |
| 2 | Self Lub GT2 timing belt 2 m x 6 mm, open | $9.38 | ₹898.00 | [Amazon](https://www.amazon.in/gp/product/B0HCLLLB88) |
| 6 (3 packs of 2) | INVENTO EN31 steel smooth rod 10 mm x 300 mm | $11.56 | ₹1,107.00 | [Amazon](https://www.amazon.in/gp/product/B071W8FKQV) |
| 8 | Two Trees SK10 (SH10A) rod support | $5.85 | ₹560.00 | [Robu](https://robu.in/product/sk10-10mm-linear-bearing-rail-support-xyz-shaft-table-cnc-router-sh10a/) |
| 4 | SC10UU 10 mm linear bearing block | $6.39 | ₹612.00 | [Robu](https://robu.in/product/sc10uu-10-mm-linear-ball-bearing-slide-unit-cnc-3d-printer/) |
| 1 pack | SNOOGG 12 x 2 mm N35 neodymium disc magnets (pack of 20) | $3.96 | ₹379.00 | [Amazon](https://www.amazon.in/gp/product/B0DMVKSZ74) |

### Electronic parts

| Qty | Part | Price (USD) | Price (INR) | Link |
|---:|---|---:|---:|---|
| 1 | Arduino Uno R3 with USB cable | $4.17 | ₹398.97 | [Robu](https://robu.in/product/arduino-uno-r3/) |
| 1 | CNC Shield V3 | $1.03 | ₹99.00 | [Robu](https://robu.in/product/cnc-shield-v3-engraving-machine-3d-printer-a4988-drv8825-driver-expansion-board/) |
| 2 | TMC2209 stepper driver module with heatsink (must expose DIAG and UART pins) | $13.55 | ₹1,298.00 | [Robu](https://robu.in/product/tmc2209-stepper-motor-driver-module-with-heatsink/) |
| 1 | 12 V 5 A 60 W power supply, 5.5 mm DC plug | $4.44 | ₹425.00 | [Robu](https://robu.in/product/orange-ac-100-240v-to-dc-12v-5a-60w-power-adapter/) |
| 1 | DC jack socket (female) with moulded wire lead, 15 cm | $0.22 | ₹21.00 | [Robu](https://robu.in/product/5mm-dc-jack-socket-female-jack-socket-with-wire/) |
| 1 | Electronic Spices DC female to 2 male Y-splitter cable | $1.24 | ₹119.00 | [Amazon](https://www.amazon.in/gp/product/B08PRS2Q23) |
| 1 | 6A 250V AC SPST ON-OFF rocker switch | $0.17 | ₹16.00 | [Robu](https://robu.in/product/6a-250v-ac-spst-on-off-rocker-switch/) |
| 1 | 1.3 inch I2C OLED display, blue | $3.02 | ₹289.00 | [Robu](https://robu.in/product/1-3-inch-i2c-iic-4-pin-oled-display-module-with-vcc-gnd-blue/) |
| 1 | Lanboo LB16QC-P10F 16 mm push button switch, blue, DC 5-24V, 1NO | $4.62 | ₹442.00 | [Robu](https://robu.in/product/lb16qc-p10f-lanboo-16mm-tact-push-button-switch-bluedc-5-24v1no/) |
| 1 | 5 V active buzzer | $0.17 | ₹16.00 | [Robu](https://robu.in/product/5v-active-electromagnetic-buzzer-pack-of-5/) |
| 17 (1 needed) | 1 kΩ 0.25 W metal film resistor (UART TX to RX link) | $0.11 | ₹10.20 | [Robu](https://robu.in/product/1k-ohm-0-25w-metal-film-resistor-pack-of-100/) |
| 2 | 1000 µF 25 V electrolytic capacitor (12 V input) | $0.23 | ₹22.00 | [Robu](https://robu.in/product/1000uf-25v-electrolytic-capacitor-dip-pack-of-5/) |
| 4 (3 needed, 2 works) | Rubycon 35ZLH100M 100 µF 35 V electrolytic capacitor (driver VMOT) | $0.16 | ₹15.64 | [Robu](https://robu.in/product/35zlh100mefct16-3x11-rubycon-100uf-35v-%c2%b120-plugind6-3xl11mm-aluminum-electrolytic-capacitors-leaded-rohs/) |
| 1 set | Dupont jumper wires, female-female, 20 cm, 40 pcs | $0.43 | ₹41.00 | [Robu](https://robu.in/product/20cm-dupont-wire-color-jumper-cable-2-54mm-1p-1p-female-female-40pcs/) |
| 1 set | Dupont jumper wires, male-female, 20 cm, 10 pcs | $0.14 | ₹13.00 | [Robu](https://robu.in/product/10-wire-male-to-female-jumper-wires-20cm/) |
| 4 | 3 mm black heat shrink sleeve | $0.25 | ₹24.00 | [Robu](https://robu.in/product/heat-shrink-sleeve-3mm-black-industrial-grade-woer-hst/) |

### Fasteners

| Qty | Part | Price (USD) | Price (INR) | Link |
|---:|---|---:|---:|---|
| 10 | M5 x 35mm Phillips pan head screw | $0.29 | ₹28.00 | [OnlyScrews](https://onlyscrews.in/products/m5-x-35mm-phillips-pan-head-mild-steel-with-zinc-blue-plating-screw-dia-5mm-length-35mm?variant=52692527186233) |
| 20 | M5 x 15mm Phillips pan head screw | $0.33 | ₹32.00 | [OnlyScrews](https://onlyscrews.in/products/m5-x-15mm-phillips-pan-head-mild-steel-with-zinc-blue-plating-screw-dia-5mm-length-15mm?variant=52691038503225) |
| 25 | M5 x 10mm Phillips pan head screw | $0.37 | ₹35.00 | [OnlyScrews](https://onlyscrews.in/products/m5-x-10mm-phillips-pan-head-mild-steel-with-zinc-blue-plating-screw-dia-5mm-length-10mm?variant=52690606784825) |
| 67 | M5 x 5mm brass threaded inserts | $1.54 | ₹147.40 | [OnlyScrews](https://onlyscrews.in/products/m5-x-5mm-brass-threaded-inserts-dia-5mm-length-5mm?variant=51217096835385) |
| 30 | M3 x 3mm brass threaded inserts | $0.75 | ₹72.00 | [OnlyScrews](https://onlyscrews.in/products/m3-x-3mm-brass-threaded-inserts?variant=49729062273337) |
| 25 | M5 plain washer SS304 (ID 5.4mm, OD 9.8mm, T 1mm) | $0.31 | ₹30.00 | [OnlyScrews](https://onlyscrews.in/products/m5-washer-ss304?variant=48883899105593) |
| 9 | M3 x 6mm Phillips pan head screw SS304 | $0.15 | ₹14.40 | [OnlyScrews](https://onlyscrews.in/products/phillips-pan-head-m3-x-6mm-pack-of-20?variant=48468588757305) |
| 15 | M3 x 10mm Phillips pan head screw SS304 | $0.28 | ₹27.00 | [OnlyScrews](https://onlyscrews.in/products/phillips-pan-head-m3-x-10mm-pack-of-20?variant=48468583874873) |
| 5 | M3 x 16mm Phillips pan head screw SS304 | $0.11 | ₹11.00 | [OnlyScrews](https://onlyscrews.in/products/phillips-pan-head-m3-x-16mm-pack-of-20?variant=48468578959673) |
| 4 | M5 hex nut SS304 | $0.058 | ₹5.60 | [OnlyScrews](https://onlyscrews.in/a/search?q=m5+nut&options%5Bprefix%5D=last) |


### Tools

| Qty | Part | Price (USD) | Price (INR) | Link |
|---:|---|---:|---:|---|
| 1 | UNI-T UT890D+ digital multimeter, True RMS 6000 count | $19.83 | ₹1,899.00 | [Robu](https://robu.in/product/uni-t-ut890d-digital-multimeter/) |
| 1 | Serplex 12-in-1 soldering iron tool kit 80W | $16.70 | ₹1,599.00 | [Amazon](https://www.amazon.in/gp/product/B0G2H4J193) |

3D printer: parts here are made on a Bambu Lab P2S.

### Total

**~$154 (₹14,599.21)**



---

## 3D Files

### Full Mechanism

<img width="2341" height="1418" alt="image" src="https://github.com/user-attachments/assets/59de0603-c4f7-4933-ae95-05ef2ce7b841" />



### Outer Frame

<img width="2098" height="1297" alt="image" src="https://github.com/user-attachments/assets/83d343a7-ea52-4070-b1db-59044d644bd9" />



### Gondola System

<img width="1881" height="910" alt="image" src="https://github.com/user-attachments/assets/5170f346-471b-41fd-af13-47a27407a2d2" />



---
## Wiring Diagram
This project does not use a custom PCB rather relies on an Arduino Board with a CNC Shield Attachment.

<img width="1012" height="502" alt="image" src="https://github.com/user-attachments/assets/44a18601-ab82-4e4c-b1ba-40671bcdc24d" />






---
## Licence

Licensed under CC BY-NC-SA 4.0. See [LICENSE](LICENSE).

Personal, educational and classroom use is welcome. You may build it, modify it and share your changes under the same licence, with credit.

Selling is not permitted: no assembled units, kits, printed parts, files or firmware, original or modified. For commercial licensing, contact me.

This project is source-available, not open source as defined by OSI or OSHWA.

Third-party libraries remain under their own licences.


---

## Author

Krish Sanwal
https://github.com/KrishSanwal
