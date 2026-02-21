# Grbl -- Turn Your Arduino Into a CNC Machine Controller

## What Is This?

Imagine you could tell a machine *exactly* where to move a tool -- a drill, a laser, a pen, a router bit -- and it would follow your instructions with pinpoint accuracy. That is what **Grbl** does.

Grbl (pronounced "gerbil") is a small piece of software you upload to an inexpensive **Arduino** board. Once installed, the Arduino becomes the "brain" of a CNC (Computer Numerically Controlled) machine. You send it instructions from your computer, and it translates those instructions into precise electrical signals that drive motors, spin cutting tools, and more.

**In simple terms:** Grbl is what makes a DIY CNC machine actually work.

**Version:** Grbl 1.1f

---

## Table of Contents

- [Who Is This For?](#who-is-this-for)
- [What Can You Build With Grbl?](#what-can-you-build-with-grbl)
- [What You Will Need (Shopping List)](#what-you-will-need-shopping-list)
- [How It All Fits Together (The Big Picture)](#how-it-all-fits-together-the-big-picture)
- [Where to Plug Everything In (Pin Connections)](#where-to-plug-everything-in-pin-connections)
  - [Arduino Uno Wiring](#arduino-uno-wiring)
  - [Arduino Mega 2560 Wiring](#arduino-mega-2560-wiring)
- [Step-by-Step Wiring Guide](#step-by-step-wiring-guide)
- [Installing Grbl on Your Arduino](#installing-grbl-on-your-arduino)
- [Your First Connection](#your-first-connection)
- [Setting Up Your Machine](#setting-up-your-machine)
- [Sending Your First Movement Command](#sending-your-first-movement-command)
- [Understanding G-code (The Language of CNC)](#understanding-g-code-the-language-of-cnc)
- [All the Settings Explained](#all-the-settings-explained)
- [Complete Command Reference](#complete-command-reference)
- [Live Controls (While the Machine Is Moving)](#live-controls-while-the-machine-is-moving)
- [Recommended Software](#recommended-software)
- [Ready-Made Configurations for Popular Machines](#ready-made-configurations-for-popular-machines)
- [Common Problems and How to Fix Them](#common-problems-and-how-to-fix-them)
- [Glossary (CNC Terms Explained)](#glossary-cnc-terms-explained)
- [License](#license)

---

## Who Is This For?

You do **not** need to be an engineer or a programmer to use Grbl. This guide is written for:

- **Hobbyists and makers** who want to build their own CNC machine at home.
- **Students** learning about robotics, automation, or manufacturing.
- **Artists and designers** who want to automate cutting, engraving, or drawing.
- **Small business owners** looking for an affordable way to prototype products.
- **Anyone curious** about how computer-controlled machines work.

If you can follow a recipe or assemble IKEA furniture, you can set up Grbl.

---

## What Can You Build With Grbl?

Grbl is incredibly versatile. Here are real projects people build with it:

### CNC Router / Milling Machine

Cut shapes out of **wood, plastic, acrylic, aluminum, or carbon fiber** using a spinning cutting bit. Think of it like a robotic version of a handheld router -- but it follows a computer design with perfect precision. Great for making signs, furniture parts, enclosures, and mechanical parts.

### Laser Cutter / Engraver

Replace the cutting tool with a **laser beam**. Grbl controls the laser power and movement to cut thin materials or engrave detailed images and text onto wood, leather, acrylic, paper, and more. Popular for personalized gifts, jewelry, and decorations.

### Pen Plotter / Drawing Machine

Attach a **pen or marker** instead of a cutting tool. The machine draws intricate designs, technical drawings, calligraphy, or artwork on paper. The up/down axis lifts the pen when moving between drawing areas.

### PCB (Circuit Board) Maker

Use a fine engraving bit to carve circuit board traces directly into copper-clad board. This lets you **prototype electronic circuit boards at home** without sending designs to a factory and waiting weeks.

### Vinyl / Sticker Cutter

Attach a small blade to cut **vinyl decals, stickers, heat transfer designs**, and stencils from sheets of vinyl material.

### Foam Cutter

Use a **hot wire** attached to the frame to cut shapes from styrofoam or foam board -- great for RC airplane wings, architectural models, and packaging inserts.

### Automatic Dispenser

Control a syringe or pump to precisely dispense **solder paste, glue, frosting, or other liquids** in patterns -- useful in electronics manufacturing or even cake decorating.

### 3D Surface Scanner

Use the probe feature to **map the shape of a surface** by touching it with a sensor at many points. Useful for engraving on curved or uneven objects.

### Education & Learning

Grbl is an excellent hands-on way to learn about **motors, electronics, programming, physics of motion, and manufacturing** -- all with affordable hardware.

---

## What You Will Need (Shopping List)

Here is everything you need to get started. Don't worry -- it is simpler than it looks.

### The Essentials

| Item | What It Does | Typical Cost |
|---|---|---|
| **Arduino Uno** (recommended) or **Arduino Mega 2560** | The "brain" -- runs the Grbl software | $5 - $25 |
| **CNC Shield v3** (for Uno) | A board that plugs on top of the Arduino and makes wiring easy | $3 - $10 |
| **Stepper Motor Drivers** (e.g., A4988 or DRV8825) -- one per axis | Small circuit boards that amplify the Arduino's signals to power the motors | $1 - $5 each |
| **Stepper Motors** (NEMA 17 recommended) -- one per axis | The motors that physically move the machine (typically 3: X, Y, and Z) | $8 - $15 each |
| **Power Supply** (12V or 24V, 5A+) | Provides power to the motors (the Arduino's USB power is not enough for motors) | $10 - $20 |
| **USB Cable** (Type A to Type B) | Connects your computer to the Arduino | $3 - $5 |

### Optional but Useful

| Item | What It Does |
|---|---|
| **Limit Switches** (3x microswitches) | Small switches placed at the ends of each axis so the machine knows where its boundaries are |
| **Emergency Stop Button** | A big red button that immediately stops everything -- important for safety |
| **Spindle Motor** (DC motor, router, or laser) | The tool that does the actual work (cutting, engraving, etc.) |
| **Probe / Touch Plate** | A small metal plate used to automatically find the exact height of your workpiece |
| **Cooling System** | A pump and tubing for flood or mist coolant when cutting metals |

---

## How It All Fits Together (The Big Picture)

Here is the chain from your design to a finished part:

```
  Your Computer                Arduino                    CNC Machine
  ─────────────               ─────────                  ───────────
                    USB
  Design Software  ──────►  Grbl Firmware  ──────►  Stepper Motors (movement)
  (creates the               (translates              Spindle Motor (cutting/engraving)
   instructions)              instructions             Limit Switches (safety)
                              into motor               Coolant (cooling)
                              signals)                 Probe (measuring)
```

**Step by step:**

1. You create a design in software (like a drawing, a shape to cut, or an image to engrave).
2. CAM software (like Fusion 360, Easel, or Carbide Create) converts your design into **G-code** -- a simple text file of movement instructions.
3. A **G-code sender** program on your computer sends the G-code to the Arduino over USB.
4. **Grbl** (running on the Arduino) reads each instruction and sends precisely timed electrical pulses to the stepper motor drivers.
5. The **stepper drivers** amplify those pulses and spin the **stepper motors** by exact amounts.
6. The motors move the machine along the **X axis** (left/right), **Y axis** (forward/back), and **Z axis** (up/down).
7. A cutting tool, laser, or pen attached to the Z axis does the actual work on your material.

---

## Where to Plug Everything In (Pin Connections)

"Pins" are the numbered connection points on your Arduino board. Each pin has a specific job in Grbl. Below is a guide to which wire goes where.

> **Tip:** If you are using a **CNC Shield v3**, you do not need to worry about individual pins -- the shield has labeled screw terminals and slots for the stepper drivers. Just plug everything into the shield. The pin tables below are for reference or custom wiring.

---

### Arduino Uno Wiring

This is the default and most common setup.

#### Motor Connections (Stepper Motors)

Each motor needs two signals: **Step** (tells the motor to take one step) and **Direction** (tells it which way to step). There is also a shared **Enable** pin that turns all motors on or off.

| What It Does | Arduino Pin | Plain English |
|---|---|---|
| X Motor -- Step | Pin 2 | Each pulse moves the X motor one tiny step |
| Y Motor -- Step | Pin 3 | Each pulse moves the Y motor one tiny step |
| Z Motor -- Step | Pin 4 | Each pulse moves the Z motor one tiny step |
| X Motor -- Direction | Pin 5 | HIGH = one direction, LOW = the other |
| Y Motor -- Direction | Pin 6 | HIGH = one direction, LOW = the other |
| Z Motor -- Direction | Pin 7 | HIGH = one direction, LOW = the other |
| All Motors -- Enable | Pin 8 | Turns motor power on or off (all axes) |

#### Limit Switches (End-of-Travel Sensors)

These small switches tell Grbl when the machine has reached the physical end of an axis, preventing crashes.

| What It Does | Arduino Pin | Plain English |
|---|---|---|
| X Limit Switch | Pin 9 | Triggers when X axis reaches its end |
| Y Limit Switch | Pin 10 | Triggers when Y axis reaches its end |
| Z Limit Switch | Pin 12 | Triggers when Z axis reaches its end |

#### Spindle / Laser Control

The "spindle" is your cutting or engraving tool -- a router motor, a DC motor with a drill bit, or a laser.

| What It Does | Arduino Pin | Plain English |
|---|---|---|
| Spindle Speed (PWM) | Pin 11 | Controls how fast the spindle spins (or laser power) |
| Spindle Direction | Pin 13 | Controls rotation direction (clockwise or counter-clockwise) |

#### Coolant Control

If your machine uses liquid cooling (common when cutting metal), these pins control the coolant pumps.

| What It Does | Arduino Pin | Plain English |
|---|---|---|
| Flood Coolant | Pin A3 | Turns the flood coolant pump on/off |
| Mist Coolant | Pin A4 | Turns the mist coolant sprayer on/off |

#### Control Buttons

You can wire physical buttons to these pins for hands-on control without touching the computer.

| What It Does | Arduino Pin | Plain English |
|---|---|---|
| Reset / Emergency Stop | Pin A0 | Immediately stops and resets the machine |
| Pause (Feed Hold) | Pin A1 | Pauses the machine mid-job (you can resume later) |
| Start / Resume | Pin A2 | Starts a job or resumes after a pause |

#### Probe (Touch Sensor)

A probe is used to automatically measure the height of your workpiece or find the edge of material.

| What It Does | Arduino Pin | Plain English |
|---|---|---|
| Probe Input | Pin A5 | Detects when the tool touches a conductive surface |

---

### Arduino Mega 2560 Wiring

The Mega has more pins and memory. Use it if you need extra I/O or are building a more complex machine.

> To switch to the Mega, you will need to change one line in the file `cpu_map.h` before uploading. Instructions are in the [Installing Grbl](#installing-grbl-on-your-arduino) section.

#### Motor Connections

| What It Does | Arduino Pin |
|---|---|
| X Motor -- Step | Pin 24 |
| Y Motor -- Step | Pin 25 |
| Z Motor -- Step | Pin 26 |
| X Motor -- Direction | Pin 30 |
| Y Motor -- Direction | Pin 31 |
| Z Motor -- Direction | Pin 32 |
| All Motors -- Enable | Pin 13 |

#### Limit Switches

| What It Does | Arduino Pin |
|---|---|
| X Limit Switch | Pin 10 |
| Y Limit Switch | Pin 11 |
| Z Limit Switch | Pin 12 |

#### Spindle / Laser Control

| What It Does | Arduino Pin |
|---|---|
| Spindle Enable | Pin 6 |
| Spindle Direction | Pin 5 |
| Spindle Speed (PWM) | Pin 7 |

#### Coolant Control

| What It Does | Arduino Pin |
|---|---|
| Flood Coolant | Pin 8 |
| Mist Coolant | Pin 9 |

#### Control Buttons

| What It Does | Arduino Pin |
|---|---|
| Reset / Emergency Stop | Pin A8 |
| Pause (Feed Hold) | Pin A9 |
| Start / Resume | Pin A10 |
| Safety Door | Pin A11 |

#### Probe

| What It Does | Arduino Pin |
|---|---|
| Probe Input | Pin A15 |

---

## Step-by-Step Wiring Guide

### Overview Diagram (Arduino Uno)

```
                      Arduino Uno
                   ┌──────────────────┐
                   │                  │
    X Motor  ◄─────┤ Pin 2  (Step)    │
    X Motor  ◄─────┤ Pin 5  (Dir)     │
                   │                  │
    Y Motor  ◄─────┤ Pin 3  (Step)    │
    Y Motor  ◄─────┤ Pin 6  (Dir)     │
                   │                  │
    Z Motor  ◄─────┤ Pin 4  (Step)    │
    Z Motor  ◄─────┤ Pin 7  (Dir)     │
                   │                  │
    Motor Power ◄──┤ Pin 8  (Enable)  │
                   │                  │
    Spindle  ◄─────┤ Pin 11 (Speed)   │
                   │                  │
    X Switch ──────┤ Pin 9            │
    Y Switch ──────┤ Pin 10           │
    Z Switch ──────┤ Pin 12           │
                   │                  │
    Probe    ──────┤ Pin A5           │
                   │                  │
    Coolant  ◄─────┤ Pin A3           │
                   │                  │
    Reset Btn ─────┤ Pin A0           │
    Pause Btn ─────┤ Pin A1           │
    Start Btn ─────┤ Pin A2           │
                   │                  │
    Computer ◄─────┤ USB Port         │
                   └──────────────────┘
```

### How to Wire a Stepper Motor (Each Axis)

You do **not** connect a motor directly to the Arduino. A small circuit board called a **stepper driver** sits in between. It takes the tiny signal from the Arduino and converts it into enough power to spin the motor.

```
    Arduino                Stepper Driver              Stepper Motor
    ───────               ────────────────             ─────────────

    Step Pin  ──────────►  STEP input                   Coil A wires
    Dir Pin   ──────────►  DIR input                    Coil B wires
    Enable Pin ─────────►  ENABLE input
                           VMOT  ◄── 12-24V Power Supply
                           GND   ◄── Power Supply GND ── Arduino GND
                           VDD   ◄── 5V (from Arduino)
```

**Important:** The Arduino GND, the power supply GND, and the driver GND must all be connected together (common ground). Without this, nothing will work properly.

### How to Wire Limit Switches

Limit switches are simple: just two wires -- one to the Arduino pin, one to GND (ground). The Arduino has built-in pull-up resistors, so no extra components are needed.

```
    Arduino Pin ────── Switch ────── Arduino GND
```

**Recommended:** Use **Normally Closed (NC)** switches. This means the switch is always connected, and it *breaks* the connection when triggered. The advantage is that if a wire comes loose, the machine stops -- which is the safe behavior. If you use Normally Open (NO) switches instead, send the command `$5=1` to tell Grbl.

### How to Wire a Probe / Touch Plate

A probe is used to find where the top of your material is. It works by detecting when a metal tool touches a metal plate placed on the material.

```
    Pin A5 ────── Alligator Clip on Tool
                        |
                  (touch contact)
                        |
    Arduino GND ── Metal Plate on Workpiece
```

When the tool touches the plate, the circuit is completed, and Grbl records that position.

---

## Installing Grbl on Your Arduino

### What You Need on Your Computer

- **Arduino IDE** (free software) -- download it from [arduino.cc](https://www.arduino.cc/en/software)
- This Grbl library (the folder you are reading this README from)

### Steps

1. Make sure the `grbl` folder is inside your Arduino libraries folder:
   - **Windows:** `Documents\Arduino\libraries\grbl\`
   - **Mac:** `~/Documents/Arduino/libraries/grbl/`
   - **Linux:** `~/Arduino/libraries/grbl/`

2. Open the **Arduino IDE**.

3. Go to **File > Examples > grbl > grblUpload**. This opens a small sketch that loads Grbl onto your Arduino.

4. **If using Arduino Mega 2560:** Before uploading, open the file `cpu_map.h` in this folder and change:
   ```c
   #define CPU_MAP_ATMEGA328P
   ```
   to:
   ```c
   #define CPU_MAP_ATMEGA2560
   ```

5. Plug in your Arduino via USB.

6. In the Arduino IDE, go to **Tools > Board** and select your board (Arduino Uno or Mega 2560).

7. Go to **Tools > Port** and select the port your Arduino is connected to (it will say something like COM3 on Windows or /dev/ttyACM0 on Linux).

8. Click the **Upload** button (the right-arrow icon).

9. Wait for the upload to finish. You should see "Done uploading."

That's it -- Grbl is now running on your Arduino.

---

## Your First Connection

Now that Grbl is installed, let's talk to it.

1. Open the **Arduino IDE Serial Monitor** (click the magnifying glass icon in the top-right corner), or use any serial terminal program.

2. At the bottom of the Serial Monitor:
   - Set the **baud rate** to **115200** (this is the speed at which Grbl communicates).
   - Set the **line ending** to **Carriage Return** or **Both NL & CR**.

3. You should see a welcome message:

```
Grbl 1.1f ['$' for help]
```

If you see this, congratulations -- Grbl is running and talking to your computer.

4. Type `$$` and press Enter. This shows all of Grbl's current settings. You will use these to configure your specific machine.

---

## Setting Up Your Machine

Every CNC machine is different -- different motors, different lead screws, different sizes. Grbl needs to know the specifics of *your* machine. You configure it by typing simple commands.

### The Most Important Setting: Steps Per Millimeter

This tells Grbl how many motor steps it takes to move the machine exactly 1 millimeter. If this number is wrong, your machine will cut parts that are the wrong size.

**How to calculate it:**

```
Steps per mm = (Steps per revolution x Microstepping) / Travel per revolution
```

**Example:**
- Your motor takes **200 steps** per full revolution (most standard stepper motors)
- Your driver is set to **1/8 microstepping** (so multiply by 8)
- Your lead screw moves **8 mm per revolution**

```
Steps per mm = (200 x 8) / 8 = 200 steps/mm
```

Set it by typing:

```
$100=200    (for the X axis)
$101=200    (for the Y axis)
$102=200    (for the Z axis)
```

### Setting Maximum Speed

This limits how fast each axis can move, in millimeters per minute. Start slow and increase gradually.

```
$110=500    (X axis max speed: 500 mm/min)
$111=500    (Y axis max speed: 500 mm/min)
$112=500    (Z axis max speed: 500 mm/min)
```

### Setting Acceleration

This controls how quickly the motors speed up and slow down. Too high and the motors may skip steps (miss beats). Too low and jobs take forever.

```
$120=10     (X axis acceleration: 10 mm/sec²)
$121=10     (Y axis acceleration: 10 mm/sec²)
$122=10     (Z axis acceleration: 10 mm/sec²)
```

### Setting Up Homing (Recommended)

Homing is when the machine moves to its limit switches on startup so it knows exactly where it is. This is like a GPS calibration for your CNC.

```
$22=1       (Turn on homing)
$24=25.0    (Slow speed when approaching the switch)
$25=500.0   (Fast speed when searching for the switch)
$27=1.0     (After touching the switch, back off 1 mm)
```

After setting this up, type `$H` to run the homing cycle. The machine will move each axis toward its limit switch, touch it, and then back off slightly.

### Setting Machine Size

Tell Grbl how large your machine's work area is (in millimeters):

```
$130=200    (X axis can travel 200 mm)
$131=200    (Y axis can travel 200 mm)
$132=200    (Z axis can travel 200 mm)
```

---

## Sending Your First Movement Command

Let's make the machine move! Type these commands one at a time in the serial terminal:

```
G21         (Use millimeters)
G90         (Use absolute positions -- "go TO this position")
G0 X10 Y10  (Rapidly move to the point X=10mm, Y=10mm)
G1 X50 F200 (Slowly move to X=50mm at a speed of 200 mm/min)
G1 Y50      (Move to Y=50mm)
G1 X10      (Move back to X=10mm)
G1 Y10      (Move back to Y=10mm -- completing a square)
```

**What just happened:** You told the machine to draw a square that is 40mm on each side. If you had a pen attached, it would have drawn a square on paper.

---

## Understanding G-code (The Language of CNC)

G-code is a simple text-based language. Each line is one instruction. Here are the most common ones explained in plain English:

### Movement Commands (The Ones You'll Use Most)

| Command | What It Does | Example | Plain English |
|---|---|---|---|
| `G0` | **Rapid move** -- moves as fast as possible to a position (no cutting) | `G0 X10 Y20` | "Rush over to position X=10, Y=20" |
| `G1` | **Cutting move** -- moves at a controlled speed (for actual work) | `G1 X50 F200` | "Move to X=50 at 200 mm/min while cutting" |
| `G2` | **Clockwise arc** -- cuts a curve going clockwise | `G2 X10 Y10 R5` | "Cut a clockwise curve to X=10, Y=10 with radius 5" |
| `G3` | **Counter-clockwise arc** -- cuts a curve going counter-clockwise | `G3 X10 Y10 R5` | "Cut a counter-clockwise curve" |
| `G4` | **Pause** -- wait for a specified time | `G4 P2` | "Wait 2 seconds before the next move" |
| `G28` | **Go home** -- move to a saved home position | `G28` | "Go back to the home position" |

### Setting Units and Modes

| Command | What It Does |
|---|---|
| `G20` | Use **inches** for all measurements |
| `G21` | Use **millimeters** for all measurements |
| `G90` | **Absolute mode** -- coordinates are positions on the work area ("go TO X=50") |
| `G91` | **Relative mode** -- coordinates are distances from current position ("move 50mm in X") |

### Tool Control

| Command | What It Does | Plain English |
|---|---|---|
| `M3 S1000` | **Turn on spindle/laser** clockwise at speed 1000 | "Start the cutting tool at speed 1000" |
| `M4 S1000` | **Turn on spindle/laser** counter-clockwise at speed 1000 | "Start tool spinning the other direction" |
| `M5` | **Turn off spindle/laser** | "Stop the cutting tool" |
| `M8` | **Turn on flood coolant** | "Start the coolant pump" |
| `M9` | **Turn off coolant** | "Stop the coolant" |

### Program Control

| Command | What It Does |
|---|---|
| `M0` | **Pause the program** -- wait for the operator to press resume |
| `M2` | **End the program** -- the job is done |
| `M30` | **End and reset** -- the job is done, go back to the beginning |

### Probing (Measuring)

| Command | What It Does | Plain English |
|---|---|---|
| `G38.2 Z-10 F50` | Move Z down slowly until the probe touches something | "Lower the tool slowly and stop when it touches the surface" |
| `G38.3 Z-10 F50` | Same as G38.2 but no error if nothing is touched | "Try to touch the surface, but don't panic if it doesn't" |

### Coordinate Systems

Grbl supports **6 different "zero points"** (called work coordinate systems). This is useful if you are making multiple parts in different positions on your machine bed.

| Command | What It Does |
|---|---|
| `G54` | Use work zero #1 (this is the default) |
| `G55` to `G59` | Use work zero #2 through #6 |
| `G92 X0 Y0 Z0` | "Call my current position the new zero" |

---

## All the Settings Explained

Type `$$` to see all settings. Here is what each one means:

| Setting | What It Controls | Default | In Simple Terms |
|---|---|---|---|
| `$0` | Step pulse length | 10 us | How long each "step" electrical pulse lasts. Leave this alone unless motors are misbehaving. |
| `$1` | Motor idle time | 25 ms | How long after stopping before motors are allowed to relax. Use 255 to keep them locked forever (prevents drift). |
| `$2` | Step signal inversion | 0 | Fixes motors that step on the wrong edge of the signal. Usually leave at 0. |
| `$3` | Direction inversion | 0 | If an axis moves backwards, change this. (1=X, 2=Y, 4=Z, add them together for multiple axes.) |
| `$4` | Enable pin inversion | 0 | If motors are ON when they should be OFF (or vice versa), set this to 1. |
| `$5` | Limit switch inversion | 0 | Set to 1 if using Normally Open limit switches. Leave at 0 for Normally Closed switches. |
| `$6` | Probe pin inversion | 0 | Set to 1 if the probe signal is inverted. |
| `$10` | Status report content | 1 | Controls what information is included when you ask for a status update. |
| `$11` | Junction deviation | 0.01 mm | Controls how much the machine slows down at corners. Smaller = slower but more accurate corners. |
| `$12` | Arc tolerance | 0.002 mm | How closely arcs follow the ideal curve. Smaller = smoother arcs. |
| `$13` | Report in inches | 0 | Set to 1 if you prefer position reports in inches instead of millimeters. |
| `$20` | Soft limits | 0 | When ON (1), Grbl will refuse to move beyond your machine's defined work area. Requires homing. |
| `$21` | Hard limits | 0 | When ON (1), hitting a limit switch during a job immediately stops the machine (emergency stop). |
| `$22` | Homing | 0 | When ON (1), enables the homing cycle (`$H` command). |
| `$23` | Homing direction | 0 | Which direction each axis moves to find its home switch. (1=X, 2=Y, 4=Z, add together.) |
| `$24` | Homing slow speed | 25 mm/min | The slow, precise speed used when the switch is located. |
| `$25` | Homing fast speed | 500 mm/min | The fast speed used to initially search for the switch. |
| `$26` | Homing switch delay | 250 ms | How long to wait after touching a switch before confirming (prevents false triggers from vibration). |
| `$27` | Homing pull-off | 1.0 mm | After touching a switch, the machine backs off this far. Prevents staying on the switch. |
| `$30` | Max spindle/laser speed | 1000 | The maximum speed your spindle can spin (or max laser power). |
| `$31` | Min spindle/laser speed | 0 | The minimum speed below which the spindle stays off. |
| `$32` | Laser mode | 0 | Set to 1 if using a laser. In laser mode, the laser turns off during rapid moves automatically. |
| `$100` | X steps per mm | 250 | How many motor steps = 1 mm of movement on the X axis. |
| `$101` | Y steps per mm | 250 | Same for Y axis. |
| `$102` | Z steps per mm | 250 | Same for Z axis. |
| `$110` | X max speed | 500 mm/min | Fastest the X axis can move. |
| `$111` | Y max speed | 500 mm/min | Fastest the Y axis can move. |
| `$112` | Z max speed | 500 mm/min | Fastest the Z axis can move. |
| `$120` | X acceleration | 10 mm/sec² | How quickly the X axis speeds up and slows down. |
| `$121` | Y acceleration | 10 mm/sec² | Same for Y. |
| `$122` | Z acceleration | 10 mm/sec² | Same for Z. |
| `$130` | X max travel | 200 mm | Total distance the X axis can travel (used for soft limits). |
| `$131` | Y max travel | 200 mm | Same for Y. |
| `$132` | Z max travel | 200 mm | Same for Z. |

### Useful Shortcut Commands

| Command | What It Does | When to Use It |
|---|---|---|
| `$$` | Show all settings | To check your current configuration |
| `$I` | Show Grbl version | To verify which version is running |
| `$H` | Run homing | After startup, to calibrate machine position |
| `$X` | Unlock the machine | When Grbl is in alarm mode and won't move |
| `$C` | Check mode (toggle) | To test a G-code file without actually moving anything |
| `$RST=$` | Reset settings to factory | When you want to start over with default settings |
| `$RST=*` | Full factory reset | Erases everything (settings + saved positions) |
| `$N0=G21 G90` | Set startup command | Runs automatically every time Grbl starts (example: set mm + absolute mode) |

---

## Complete Command Reference

### All Supported G-codes

<details>
<summary>Click to expand the full G-code list</summary>

#### Motion

| Code | Description |
|---|---|
| `G0` | Rapid move (fast, no cutting) |
| `G1` | Linear move (controlled speed, for cutting) |
| `G2` | Clockwise arc |
| `G3` | Counter-clockwise arc |
| `G4` | Dwell / Pause |
| `G10 L2` | Set a coordinate system's zero point |
| `G10 L20` | Set coordinate system relative to current position |
| `G28` | Go to saved position #1 |
| `G28.1` | Save current position as position #1 |
| `G30` | Go to saved position #2 |
| `G30.1` | Save current position as position #2 |
| `G38.2` | Probe toward workpiece (error if no contact) |
| `G38.3` | Probe toward workpiece (no error if no contact) |
| `G38.4` | Probe away from workpiece (error on loss of contact) |
| `G38.5` | Probe away from workpiece (no error) |
| `G53` | Move using machine coordinates (ignoring work offsets) |
| `G80` | Cancel current motion mode |

#### Units, Planes, and Modes

| Code | Description |
|---|---|
| `G17` | Select XY plane (default) |
| `G18` | Select XZ plane |
| `G19` | Select YZ plane |
| `G20` | Use inches |
| `G21` | Use millimeters |
| `G90` | Absolute positioning |
| `G91` | Relative / incremental positioning |
| `G91.1` | Incremental arc center mode (default) |
| `G93` | Inverse time feed rate |
| `G94` | Units per minute feed rate (default) |

#### Coordinate Systems

| Code | Description |
|---|---|
| `G54` - `G59` | Select work coordinate system 1-6 |
| `G92` | Set coordinate offset ("call here zero") |
| `G92.1` | Clear coordinate offset |

#### Tool

| Code | Description |
|---|---|
| `G43.1` | Set tool length offset |
| `G49` | Cancel tool length offset |

#### Spindle, Coolant, and Program (M-codes)

| Code | Description |
|---|---|
| `M3` | Spindle on, clockwise |
| `M4` | Spindle on, counter-clockwise |
| `M5` | Spindle off |
| `M7` | Mist coolant on |
| `M8` | Flood coolant on |
| `M9` | All coolant off |
| `M0` | Pause program |
| `M2` | End program |
| `M30` | End and reset program |

</details>

---

## Live Controls (While the Machine Is Moving)

These commands work **instantly** -- you can send them at any time, even while the machine is in the middle of a job. They are your real-time control panel.

### Essential Controls

| What to Send | What It Does | When to Use It |
|---|---|---|
| `?` | **Ask for status** -- shows current position, speed, and state | Anytime you want to know what the machine is doing |
| `!` | **Pause** -- smoothly slows down and stops all motion | When you need to pause a job (tool change, inspection, etc.) |
| `~` | **Resume** -- continues from where it paused | After a pause, when you are ready to continue |
| `Ctrl+X` | **Emergency reset** -- immediately stops everything | When something goes wrong and you need to stop NOW |

### Speed Adjustments (On the Fly)

You can speed up or slow down the machine *while it is running* without stopping the job. These are sent as special characters by your G-code sender software:

| Action | Effect |
|---|---|
| Increase feed rate +10% | Machine moves faster |
| Decrease feed rate -10% | Machine moves slower |
| Reset feed rate to 100% | Back to the original programmed speed |
| Set rapid speed to 50% or 25% | Slow down the fast (non-cutting) moves for safety |
| Increase/decrease spindle speed | Speed up or slow down the spindle/laser in real time |

Most G-code sender software (like Universal Gcode Sender or CNCjs) provides buttons for all these adjustments, so you don't need to memorize the codes.

---

## Recommended Software

You'll need software on your computer to talk to Grbl. Here are the best free options:

### G-code Senders (Pick One)

These send your G-code files to Grbl and provide a visual interface for controlling the machine.

| Software | Works On | Best For | Link |
|---|---|---|---|
| **Universal Gcode Sender (UGS)** | Windows, Mac, Linux | All-around best option, great visualizer | [ugs_website](https://winder.github.io/ugs_website/) |
| **CNCjs** | Windows, Mac, Linux | Modern web-based interface, runs in browser | [cnc.js.org](https://cnc.js.org/) |
| **Candle** | Windows | Simple and lightweight, good for beginners | [GitHub](https://github.com/Denvi/Candle) |
| **bCNC** | Windows, Mac, Linux | Advanced features, auto-leveling for PCBs | [GitHub](https://github.com/vlachoudis/bCNC) |
| **LaserGRBL** | Windows | Specifically designed for laser engraving | [lasergrbl.com](https://lasergrbl.com/) |

### Design & CAM Software (to Create G-code)

| Software | What It Does | Cost |
|---|---|---|
| **Easel** (by Inventables) | Beginner-friendly, design and generate G-code in one place | Free |
| **Carbide Create** | Easy 2D/2.5D design and toolpath creation | Free |
| **Fusion 360** | Professional 3D CAD and CAM in one package | Free for hobbyists |
| **FlatCAM** | Converts PCB Gerber files into G-code for circuit board milling | Free |
| **Inkscape + gcodetools** | Convert vector art (SVG files) to G-code | Free |
| **LightBurn** | Laser cutting/engraving design software | Paid |

---

## Ready-Made Configurations for Popular Machines

If you have one of these machines, Grbl comes with pre-configured settings (steps/mm, speeds, acceleration, etc.) already built in. To activate one, you need to change a setting in the file `config.h` before uploading.

| Machine | Configuration Name |
|---|---|
| Generic / Custom CNC (default) | `DEFAULTS_GENERIC` |
| Shapeoko (original) | `DEFAULTS_SHAPEOKO` |
| Shapeoko 2 | `DEFAULTS_SHAPEOKO_2` |
| Shapeoko 3 | `DEFAULTS_SHAPEOKO_3` |
| X-Carve 500mm | `DEFAULTS_X_CARVE_500MM` |
| X-Carve 1000mm | `DEFAULTS_X_CARVE_1000MM` |
| Sherline 5400 | `DEFAULTS_SHERLINE_5400` |
| Zen Toolworks 7x7 | `DEFAULTS_ZEN_TOOLWORKS_7x7` |
| OpenBuilds OX CNC | `DEFAULTS_OXCNC` |
| Simulator (for testing without hardware) | `DEFAULTS_SIMULATOR` |

---

## Common Problems and How to Fix Them

### "Nothing happens when I connect"

- **Check the baud rate.** It must be **115200**. If it's set to 9600 (the Arduino default), you will see garbage characters or nothing at all.
- **Check the USB cable.** Some cheap cables are "charge only" and don't carry data. Try a different cable.
- **Check the COM port.** Make sure you selected the correct port in your software. On Windows, check Device Manager to see which COM port the Arduino is on.

### "The machine shows ALARM and won't move"

This is normal on first startup if homing is enabled. Grbl is waiting for you to tell it where it is.

- Type `$X` to unlock the machine (this clears the alarm).
- Or type `$H` to run the homing cycle (the machine will move to its limit switches to calibrate position).

### "The motors are not moving at all"

- Check that the **power supply** is connected and turned on. The Arduino's USB power is not strong enough for motors.
- Check that the **enable pin** polarity is correct. Try `$4=1` (inverts the enable signal). Some drivers need the signal inverted.
- Check your wiring -- are the step and direction wires connected to the correct pins?

### "An axis moves the wrong direction"

Change the direction inversion setting `$3`. The value is a combination: X=1, Y=2, Z=4. Add the values for each axis you want to reverse.

- Only X reversed: `$3=1`
- Only Y reversed: `$3=2`
- X and Z reversed: `$3=5` (1+4)
- All three reversed: `$3=7` (1+2+4)

### "The dimensions are wrong (parts are too big or too small)"

Your **steps per mm** settings (`$100`, `$101`, `$102`) are incorrect. Recalculate using the formula in the [Setting Up Your Machine](#setting-up-your-machine) section.

**Quick test:** Command the machine to move exactly 100mm (`G1 X100 F200`), then measure the actual distance with a ruler. If it moved 50mm instead of 100mm, your steps/mm is half of what it should be.

### "The motors make noise but don't move (or skip steps)"

- The **acceleration** is too high. Lower `$120`, `$121`, `$122` (try 5 or even 2).
- The **speed** is too high. Lower `$110`, `$111`, `$112`.
- The **motor current** on the driver is set too low. Adjust the tiny potentiometer on the driver board.
- The **power supply** voltage or current is insufficient.

### "Limit switches trigger randomly during a job"

This is usually caused by **electrical noise** from the motors or spindle. Solutions:

- Add a small capacitor (0.1 uF) across each switch.
- Use **shielded wires** for the switch connections.
- Keep switch wires away from motor and spindle wires.
- Use **Normally Closed (NC)** switches, which are more noise-resistant.

### Alarm Code Quick Reference

| Alarm | What Happened |
|---|---|
| ALARM:1 | A limit switch was triggered, or homing failed |
| ALARM:2 | The machine tried to move outside its defined work area |
| ALARM:3 | The machine was reset while it was moving |
| ALARM:4 | Probe cycle failed -- the probe didn't make contact |
| ALARM:5 | Probe error -- the probe was already triggered before the cycle started |
| ALARM:6 | Homing failed -- machine was reset during homing |
| ALARM:7 | Homing failed -- safety door was opened during homing |
| ALARM:8 | Homing failed -- couldn't move away from the limit switch |
| ALARM:9 | Homing failed -- couldn't find the limit switch at all |

---

## Glossary (CNC Terms Explained)

| Term | What It Means |
|---|---|
| **CNC** | Computer Numerical Control -- a machine controlled by a computer program |
| **G-code** | The simple text language used to tell a CNC machine what to do |
| **Arduino** | A small, inexpensive computer board popular with hobbyists and makers |
| **Stepper Motor** | A motor that moves in precise small steps, perfect for CNC machines |
| **Stepper Driver** | A small circuit board that takes signals from the Arduino and provides enough power to run a stepper motor |
| **Axis** | A direction of movement. Most CNC machines have 3: X (left-right), Y (front-back), Z (up-down) |
| **Spindle** | The motor that holds and spins the cutting tool (like a router or drill) |
| **Feed Rate** | How fast the machine moves while cutting, measured in mm/min or inches/min |
| **Rapid Move** | A fast, non-cutting move to reposition the tool |
| **Homing** | The process where the machine finds its starting position using limit switches |
| **Limit Switch** | A small sensor at the end of each axis that tells the machine "stop, you've reached the edge" |
| **Probe** | A sensor used to detect the surface of the workpiece (for measuring height or finding edges) |
| **Work Zero** | The point on your workpiece that you call "position 0,0,0" -- the reference point for all your cuts |
| **Machine Zero** | The absolute starting position of the machine (set by homing) |
| **PWM** | Pulse Width Modulation -- a way to control speed or power by rapidly turning a signal on and off |
| **Baud Rate** | The speed of serial communication (Grbl uses 115200) |
| **EEPROM** | A small memory on the Arduino that remembers settings even when power is turned off |
| **Lead Screw** | A threaded rod that converts the spinning of a motor into straight-line movement |
| **Microstepping** | A technique that divides each motor step into smaller sub-steps for smoother, quieter motion |
| **CAM Software** | Computer-Aided Manufacturing software that converts your design into G-code instructions |

---

## License

Grbl is **free and open-source software** released under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html). You are free to use it, modify it, and share it.

---

**Grbl v1.1f** -- Created by Sungeun K. Jeon for Gnea Research LLC
