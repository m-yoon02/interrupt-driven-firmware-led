# interrupt-driven-firmware-led
This project implements interrupt-driven embedded firmware in C on the ATmega328P (Arduino Uno) using direct memory-mapped register access. The system uses hardware timer interrupts for non-blocking scheduling and UART communication with interrupt-driven RX handling and a circular buffer.

Features

1.Timer1 configured in CTC mode (10ms system tick)

2.Cooperative scheduler (non-blocking)

3.UART driver (register-level configuration)

4.Interrupt-driven RX with circular buffer

5.Command-line interface for runtime control

6.Modular peripheral driver structure


# Interrupt-Driven Bare-Metal Firmware (ATmega328P)

This project implements interrupt-driven embedded firmware in C on the ATmega328P (Arduino Uno R3) using direct memory-mapped register access (no Arduino GPIO/UART APIs). A hardware timer interrupt generates a periodic system tick to support non-blocking scheduling, and a register-level UART driver provides an interactive CLI.

## Features
- Timer1 configured in CTC mode to generate a 10ms system tick interrupt
- Non-blocking LED pattern scheduler (no delay loops)
- UART driver configured via registers (UBRR0/UCSR0/UDR0)
- Interrupt-driven UART RX with circular buffer
- UART CLI commands:
  - `help`
  - `pattern <0|1|2>`
  - `speed <ms>`
  - `status`

## Hardware
- Board: Arduino Uno R3
- MCU: ATmega328P @ 16 MHz
- LED: On-board LED (PB5 / D13)


## Build & Run (Arduino IDE)
1. Open `avr_interrupt_led_uart.ino` in Arduino IDE
2. Tools -> Board: **Arduino Uno**
3. Tools -> Port: select your device
4. Upload
5. Open Serial Monitor at **115200 baud**, newline enabled

## Notes
- GPIO is controlled via DDRx/PINx/PORTx registers
- UART is configured via UBRR0/UCSR0/UDR0 registers
- ISR-to-main shared data uses `volatile` and atomic access where required
