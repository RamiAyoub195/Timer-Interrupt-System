# Timer and Interrupt-Based LED Control System

This repository contains the code and documentation for a real-time embedded systems project. The project demonstrates the use of timers and interrupts to control LED behavior based on user input through switches.

## Overview

The objective of this project is to:
- Configure timers and interrupts on a microcontroller.
- Implement interrupt service routines (ISRs) for handling events.
- Demonstrate multi-mode LED control using switches and a timer.

### Features
1. **Switch Configuration**  
   - Configures switches as inputs with pull-up internal resistors.
   - Sets up interrupts for switch presses.

2. **LED Configuration**  
   - LEDs are initialized and controlled via timer interrupts.

3. **Timer Configuration**  
   - Implements a delay mechanism to toggle LEDs based on user input and mode.

4. **Modes of Operation**  
   - **Regular Mode**: LEDs toggle at a delay of 1.5 seconds.
   - **Slow Mode**: LEDs toggle at a delay of 3 seconds.
   - **Paused Mode**: All LEDs turn off, and timer interrupts are disabled.
