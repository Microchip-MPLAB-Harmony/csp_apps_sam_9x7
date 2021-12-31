---
parent: Harmony 3 peripheral library application examples for SAM9X7 family
title: MCAN normal operation interrupt 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# MCAN normal operation interrupt

This example shows how to use the MCAN module to transmit and receive CAN messages in interrupt mode.

## Description

This application transmits and receives CAN messages on the CAN bus. To run this application, two evaluation boards of same type are required. These boards acts as different nodes on the CAN bus. Same application is programmed onto both the boards. Boards are connected to PC via UART. While running the application, user can send and receive CAN messages between the boards using UART console applications running on the PC.

### MCAN Message RAM configuration
- Allocate MCAN Message RAM configuration in contiguous non-cacheable buffer in the application.
  For example, uint8_t CACHE_ALIGN mcan0MessageRAM[MCAN0_MESSAGE_RAM_CONFIG_SIZE] __attribute__((__section__(".region_sram"))); 

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/mcan/mcan_normal_operation_interrupt/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_9x75_eb.X | MPLABX project for [SAM9X75-EB Evaluation Board]() |
|||

## Setting up AT91Bootstrap loader

To load the application binary onto the target device, we need to use at91bootstrap loader. Refer to the [at91bootstrap loader documentation](../../docs/readme_bootstrap.md) for details on how to configure, build and run bootstrap loader project and use it to bootstrap the application binaries.

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_9x75_eb.X | [SAM9X75-EB Evaluation Board]() |
|||

### Setting up [SAM9X75-EB Evaluation Board]()

#### Hardware required

| Name |Quantity |
| -------- | ------- |
| [SAM9X75-EB Evaluation Board]() | 2 |
| SD Card with FAT32 file system | 2 |
|||

#### Setting up the SD Card

- Download harmony MPU bootstrap loader from this [location](firmware/at91bootstrap_sam_9x75_eb.X/build/binaries/boot.bin)
- Copy the downloaded boot loader binary( boot.bin) onto the each SD card

#### Setting up the board

- Connect SAM9X75-EB Evaluation Board to another SAM9X75-EB Evaluation Board as per the pin connections shown below

| SAM9X75-EB - 1    | SAM9X75-EB - 2    |
| ----------------- | ------------------ |
| CAN1_H            | CAN1_H             |
| CAN1_L            | CAN1_L             |
| GND               | GND                |
|||

- SDMMC slot used for bootloading the application is SDMMC0 (J8)
- Connect the DBGU0 J34 on board to the computer using a UART-FTDI cable (to enable debug com port)
- Connect the USB port J28 on board to the computer using a micro USB cable (to power the board)

## Running the Application

1. Build the application using its IDE
2. Copy the output binary (named 'harmony.bin') onto the SD Card (Refer to the 'Setting up hardware' section above for setting up the SD card)
3. Insert the SD card into SDMMC slot on the board (Refer to the 'Setting up hardware' section for the correct SDMMC slot)
4. Open the Terminal application (Ex.:Tera term) on the computer.
5. Connect to the (USB to Serial) COM port and configure the serial settings as follows:
    - Baud : 115200
    - Data : 8 Bits
    - Parity : None
    - Stop : 1 Bit
    - Flow Control : None
6. Build and Program the application on both the boards using their respective IDEs
7. In the console associated with board 1, press "1" to transmit a CAN message
8. Transmitted message status will be displayed in the console window of board 1
9. Received message will be displayed in the console window of board 2
10. Follow the sequence below to send and receive CAN message:
    - Press '1' on board 2
11. If the steps are executed in this sequence, the final output in the consoles will be as below:

  ![output](images/mcan_normal_operation_interrupt.png)
