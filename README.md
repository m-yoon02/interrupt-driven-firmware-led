# interrupt-driven-firmware-led
This project implements interrupt-driven embedded firmware in C on the ATmega328P (Arduino Uno) using direct memory-mapped register access. The system uses hardware timer interrupts for non-blocking scheduling and UART communication with interrupt-driven RX handling and a circular buffer.

Features

1.Timer1 configured in CTC mode (10ms system tick)

2.Cooperative scheduler (non-blocking)

3.UART driver (register-level configuration)

4.Interrupt-driven RX with circular buffer

5.Command-line interface for runtime control

6.Modular peripheral driver structure
