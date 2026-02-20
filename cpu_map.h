/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */


#ifndef cpu_map_h
#define cpu_map_h


#ifdef CPU_MAP_ATMEGA328P // (Arduino Uno) Officially supported by Grbl.

  // Virtual Ports for 28BYJ change ( allows ignoring previous hardware control )
  uint8_t VPORTB;
  uint8_t VPORTC;
  uint8_t VPORTD;
  uint8_t VDDRB;
  uint8_t VDDRC;
  uint8_t VDDRD;
  uint8_t VPINB;
  uint8_t VPINC;
  uint8_t VPIND;

  // Define serial port pins and interrupt vectors.
  #define SERIAL_RX     USART_RX_vect
  #define SERIAL_UDRE   USART_UDRE_vect

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEP_DDR        VDDRD
  #define STEP_PORT       VPORTD
  #define X_STEP_BIT      2  // Uno Digital Pin 2
  #define Y_STEP_BIT      3  // Uno Digital Pin 3
  #define Z_STEP_BIT      4  // Uno Digital Pin 4
  #define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_DDR     VDDRD
  #define DIRECTION_PORT    VPORTD
  #define X_DIRECTION_BIT   5  // Uno Digital Pin 5
  #define Y_DIRECTION_BIT   6  // Uno Digital Pin 6
  #define Z_DIRECTION_BIT   7  // Uno Digital Pin 7
  #define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
  #define STEPPERS_DISABLE_DDR    VDDRB
  #define STEPPERS_DISABLE_PORT   VPORTB
  #define STEPPERS_DISABLE_BIT    0  // Uno Digital Pin 8
  #define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)

  // Define homing/hard limit switch input pins and limit interrupt vectors.
  // Limit switches span two ports, so each axis has its own DDR/PORT/PIN definitions.
  // X Limit: Pin 10 (PORTB bit 2)
  #define X_LIMIT_DDR      DDRB
  #define X_LIMIT_PORT     PORTB
  #define X_LIMIT_PIN      PINB
  #define X_LIMIT_BIT      2  // Uno Digital Pin 10
  // Y Limit: Pin 11 (PORTB bit 3)
  #define Y_LIMIT_DDR      DDRB
  #define Y_LIMIT_PORT     PORTB
  #define Y_LIMIT_PIN      PINB
  #define Y_LIMIT_BIT      3  // Uno Digital Pin 11
  // Z Limit: Pin A4 (PORTC bit 4)
  #define Z_LIMIT_DDR      DDRC
  #define Z_LIMIT_PORT     PORTC
  #define Z_LIMIT_PIN      PINC
  #define Z_LIMIT_BIT      4  // Uno Analog Pin A4

  // Legacy defines kept for compatibility with code that uses single-port LIMIT_ macros
  #define LIMIT_DDR        DDRB
  #define LIMIT_PIN        PINB
  #define LIMIT_PORT       PORTB
  #define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)) // X and Y on PORTB only
  #define LIMIT_INT        PCIE0  // Pin change interrupt for PORTB
  #define LIMIT_INT_vect   PCINT0_vect
  #define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register for PORTB
  // Z limit uses PORTC pin change interrupt
  #define Z_LIMIT_INT      PCIE1  // Pin change interrupt for PORTC
  #define Z_LIMIT_INT_vect PCINT1_vect
  #define Z_LIMIT_PCMSK    PCMSK1 // Pin change interrupt register for PORTC

  // Define spindle enable pin - DC motor ON/OFF on Digital Pin 7 (PORTD bit 7)
  // Uses real PORTD (not virtual) so the hardware pin is actually driven.
  #define SPINDLE_ENABLE_DDR    DDRD
  #define SPINDLE_ENABLE_PORT   PORTD
  #define SPINDLE_ENABLE_BIT    7  // Uno Digital Pin 7
  #ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
    #define SPINDLE_DIRECTION_DDR   VDDRB
    #define SPINDLE_DIRECTION_PORT  VPORTB
    #define SPINDLE_DIRECTION_BIT   5  // Unused - direction not needed for simple DC motor
  #endif

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_DDR   VDDRC
  #define COOLANT_FLOOD_PORT  VPORTC
  #define COOLANT_FLOOD_BIT   3  // Uno Analog Pin 3
  #define COOLANT_MIST_DDR   VDDRC
  #define COOLANT_MIST_PORT  VPORTC
  #define COOLANT_MIST_BIT   4  // Uno Analog Pin 4

  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_DDR       VDDRC
  #define CONTROL_PIN       VPINC
  #define CONTROL_PORT      VPORTC
  #define CONTROL_RESET_BIT         0  // Uno Analog Pin 0
  #define CONTROL_FEED_HOLD_BIT     1  // Uno Analog Pin 1
  #define CONTROL_CYCLE_START_BIT   2  // Uno Analog Pin 2
  #define CONTROL_SAFETY_DOOR_BIT   1  // Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.
  #define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
  #define CONTROL_INT_vect  PCINT1_vect
  #define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
  #define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
  #define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.

  // Define probe switch input pin.
  #define PROBE_DDR       VDDRC
  #define PROBE_PIN       VPINC
  #define PROBE_PORT      VPORTC
  #define PROBE_BIT       5  // Uno Analog Pin 5
  #define PROBE_MASK      (1<<PROBE_BIT)

  // Variable spindle configuration below. Do not change unless you know what you are doing.
  // NOTE: Only used when variable spindle is enabled.
  #define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
  #define SPINDLE_TCCRA_REGISTER	  TCCR2A
  #define SPINDLE_TCCRB_REGISTER	  TCCR2B
  #define SPINDLE_OCR_REGISTER      OCR2A
  #define SPINDLE_COMB_BIT	        COM2A1

  // Prescaled, 8-bit Fast PWM mode.
  #define SPINDLE_TCCRA_INIT_MASK   ((1<<WGM20) | (1<<WGM21))  // Configures fast PWM mode.
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
  // #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
  #define SPINDLE_TCCRB_INIT_MASK      (1<<CS22)               // 1/64 prescaler -> 0.98kHz (J-tech laser)

  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
  #define SPINDLE_PWM_DDR	  VDDRB
  #define SPINDLE_PWM_PORT  VPORTB
  #define SPINDLE_PWM_BIT	  3    // Uno Digital Pin 11

#endif

/*
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif
