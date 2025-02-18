# STM32L432_FlashMaster

<p align="center">
    <a href="https://github.com/imahjoub/STM32L432_FlashMaster/actions">
        <img src="https://github.com/imahjoub/STM32L432_FlashMaster/actions/workflows/STM32L432_FlashMaster.yml/badge.svg" alt="Build Status"></a>    
    <a href="https://github.com/imahjoub/STM32L432_FlashMaster/actions/workflows/STM32L432_FlashMaster_CodeQl.yml">
        <img src="https://github.com/imahjoub/STM32L432_FlashMaster/actions/workflows/STM32L432_FlashMaster_CodeQl.yml/badge.svg" alt="CodeQL"></a>
    <a href="https://github.com/imahjoub/STM32L432_FlashMaster/issues">
        <img src="https://custom-icon-badges.herokuapp.com/github/issues-raw/imahjoub/STM32L432_FlashMaster?logo=github" alt="Issues" /></a>
    <a href="https://github.com/imahjoub/STM32L432_FlashMaster/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License"></a>
    <a href="https://github.com/imahjoub/STM32L432_FlashMaster" alt="GitHub code size in bytes">
        <img src="https://img.shields.io/github/languages/code-size/imahjoub/STM32L432_FlashMaster" /></a>
    <a href="https://github.com/imahjoub/STM32L432_FlashMaster" alt="Activity">
        <img src="https://img.shields.io/github/commit-activity/y/imahjoub/STM32L432_FlashMaster" /></a>
</p>

This project implements **bare-metal** drivers for the **IS25LP128F** serial flash memory and the **SerLCD** 20x4 display on the **STM32L432KC** development board.
The flash memory is controlled via **SPI**, and the LCD is driven using **I2C**, all without relying on STM32 HAL, CMSIS, or any third-party libraries.

&nbsp;&nbsp;&nbsp;&nbsp;

## Hardware Used

| **Part**              | **Description**                                      |
|-----------------------|------------------------------------------------------|
| **STM32L432KC**       | NUCLEO-STM32L432KC Development Board.                |
| **IS25LP128F**        | Serial Flash Memory (SPI).                           |
| **SerLCD**            | SparkFun 20x4 Serial LCD Display (I2C).              |

- 
## Project Goals

The main goals of this project are:  
- Develop a **Fully bare-metal SPI driver** for IS25LP128F flash memory.
- Develop a **bare-metal I2C driver** for the SerLCD 20x4 display.
- Enable direct register-level control of peripherals for maximum efficiency.
- Implement reliable data storage and retrieval from the flash memory.
- Keep the code minimal, optimized, and dependency-free.

## Task Scheduling & Application  

The project uses a simple bare-metal scheduler to manage three tasks:  

- **Task01 (LED Blinking)**         : Toggles an LED on PB3 every 1 second.  
- **Task02 (Flash Memory Handler)** : Handles SPI flash operations, including erase, write, read, and verification every 5 seconds.  
- **Task03 (LCD Display)**          : Displays the current flash operation status on the SerLCD via I2C.  

Each task runs at a predefined interval without an RTOS, ensuring efficient execution.  

## Getting Started

### Wiring & Connections
To set up the hardware, connect the components as follows:  

| Peripheral | Interface | STM32L432KC Pins Used                             |
|------------|-----------|---------------------------------------------------|
| **IS25LP128F (Flash)** | SPI | PA5 (SCK), PA6 (MISO), PA7 (MOSI), PA4 (CS) |
| **SerLCD (LCD)**       | I2C | PB6 (SDA), PB7 (SCL)                        |

### Circuit Overview
Below is the circuit of the STM32L432KC with the flash memory and LCD display:  
