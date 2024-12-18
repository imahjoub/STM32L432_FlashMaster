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

STM32L432_FlashMaster is a baremetal project that uses the STM32L432KC microcontroller. Its purpose is to communicate with the IS25LP128F flash chip through SPI.

## Devices Used

- **STM32L432KC**: NUCLEO-STM32L432KC Development Board.
- **IS25LP128F** : Serial Flash Memory.
- **SerLCD**     : SparkFun 20x4 SerLCD

## Project Goals
TBD

## Getting Started

### Setup & Communication Protocols

1. Connect the IS25LP128F flash memory to the NUCLEO-STM32L432KC using SPI (PA5, PA6, PA7).
2. Connect the SerLCD to the NUCLEO-STM32L432KC using I2C (PB6, PB7).
3. Program the NUCLEO-STM32L432KC using an ST-Link or J-Link programmer.


