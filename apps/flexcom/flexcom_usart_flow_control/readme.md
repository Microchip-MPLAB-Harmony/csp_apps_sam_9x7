---
parent: Harmony 3 peripheral library application examples for SAM9X7 family
title: FLEXCOM USART flow control 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# FLEXCOM USART flow control

This example application shows how to use the flexcom module in USART flow control mode.

## Description

This application configures FLEXCOM5 in non-blocking mode and FLEXCOM7 in blocking mode. FLEXCOM5 is used for data transmission and FLEXCOM7 is used for receiption. The TX line of FLEXCOM5 is connected to the RX line of FLEXCOM7. The RTS line of FLEXCOM7 is connected to the CTS line of FLEXCOM5. FLEXCOM5 transmits 100 characters using interrupts. Application however simulates a slow receiver by inserting a delay after each character is read on FLEXCOM7. As a result, once the RX FIFO is full, the RTS line is de-asserted and transmitter (FLEXCOM5) stops sending the data. Eventually, when the receiver reads out sufficient number of bytes from the RX FIFO, such that the
number of bytes in the FIFO goes below RXFTHRES2, the RTS line is again asserted and the transmitter continues sending the data. The demo application indicates success if the received data matches the transmitted data.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/flexcom/flexcom_usart_flow_control/firmware** .

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

#### Setting up the board

- Connect the DBGU0 J34 on board to the computer using a UART-FTDI cable (to enable debug com port)
- Connect the USB port J28 on board to the computer using a micro USB cable (to power the board)
- Make connections as following:
    - Short PIN 6 (PA16, FLEXCOM5 TXD) on mikroBUS connector to the PIN 12 (PC1, FLEXCOM7 RXD) on mikroBUS connector
    - Short PIN 3 (PA14, FLEXCOM5 CTS) on mikroBUS connector to the PIN 4 (PD2, FLEXCOM7 RTS) on J9 connector

## Running the Application

1. Build the application using its IDE
2. LED is turned ON on success.

Refer to the following table for LED name:

| Board      | LED Name                                    |
| ----------------- | ---------------------------------------------- |
| [SAM9X75-EB Evaluation Board]() | RGB_LED(Green)  |
|||