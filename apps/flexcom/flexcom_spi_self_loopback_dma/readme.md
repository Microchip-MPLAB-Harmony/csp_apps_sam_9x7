---
parent: Harmony 3 peripheral library application examples for SAM9X7 family
title: FLEXCOM SPI self loopback dma  
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# FLEXCOM SPI self loopback dma 

This example application shows how to use the FLEXCOM SPI peripheral with DMA to transmit and receive a block of data.

## Description

This example demonstrates transmit and receive operation over FLEXCOM SPI interface using DMA. Two DMA channels are used - one for transmission and another for receiption. The loop back test requires the MOSI output pin to be connected to the MISO input pin so that anything transmitted will also be received.
The example first transmits 10 bytes and receives 10 bytes. If the received data is same as transmitted then it transmits 0 bytes and receives 10 bytes. In this case, dummy data will be transmitted to receive 10 characters, hence all the received data should be 0xFF. Next, 10 bytes are transmitted and 5 bytes are received. Here, the received bytes must match the first 5 bytes in the transmit buffer. Finally, 5 bytes are transmitted and 10 bytes are received. In this case, the first 5 bytes in the receive buffer must match the first 5 bytes in the transmit buffer. The remaining 5 bytes in the receive buffer must be 0xFF.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/flexcom/flexcom_spi_self_loopback_dma/firmware** .

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

- Use jumper wire to Connect "MOSI of mikroBUS Connector" to "MISO of mikroBUS Connector"
  - FLEXCOM5 MOSI signal is mapped to PA16 that is routed to "Pin 6 of mikroBUS Connector"
  - FLEXCOM5 MISO signal is mapped to PA15 that is routed to "Pin 5 of mikroBUS Connector"
- Connect the DBGU0 J34 on board to the computer using a UART-FTDI cable (to enable debug com port)
- Connect the USB port J28 on board to the computer using a micro USB cable (to power the board)

## Running the Application

1. Build the application using its IDE
2. LED indicates the success or failure:
    - The LED is turned ON when the received data matches the transmitted data

Following table provides the LED name:

| Board      | LED Name                                    |
| ----------------- | ---------------------------------------------- |
| [SAM9X75-EB Evaluation Board]() | RGB_LED(Green)  |
|||
