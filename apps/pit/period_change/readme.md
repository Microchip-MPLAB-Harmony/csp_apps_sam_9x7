---
parent: Harmony 3 peripheral library application examples for SAM9X7 family
title: PIT period change 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# PIT period change

This example application shows how PIT period can be changed during runtime.

## Description

The LED starts blinking at one second intervals. When the switch is pushed the timer is stopped. When the switch is pressed again, the period is cut in half and the timer is restarted. The timer is turned off and on every alternate switch press. When the timer is started on every alternate switch press, the period is also toggled from .5 second, .25 second intervals, .125 second intervals and 1 second intervals. There is no debounce in the switch so it is possible that pressing the switch will jump more than one interval.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/pit/period_change/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_9x75_curiosity.X | MPLABX project for [SAM9X75 CURIOSITY Board]() |
|||

## Setting up AT91Bootstrap loader

To load the application binary onto the target device, we need to use at91bootstrap loader. Refer to the [at91bootstrap loader documentation](../../docs/readme_bootstrap.md) for details on how to configure, build and run bootstrap loader project and use it to bootstrap the application binaries.

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_9x75_curiosity.X | [SAM9X75 CURIOSITY Board]() |
|||

### Setting up [SAM9X75 CURIOSITY Board]()

#### Setting up the board

- Connect the DBGU0 J32 on board to the computer using a UART-FTDI cable (to enable debug com port)
- Connect the USB port J2 on board to the computer using a micro USB cable (to power the board)

## Running the Application

1. Build the application using its IDE
2. LED toggles every 1000 ms
3. Press switch to stop the timer and hence the LED toggle
4. Pressing the switch again starts the timer and changes the rate of LED toggle
5. The application alternates between step 6 and 7 on each switch press

Refer to the following table for LED name:

| Board             | LED Name                                       | Switch Name |
| ----------------- | ---------------------------------------------- | ----------- |
| [SAM9X75 CURIOSITY Board]() | RGB_LED(Green) | USER |
|||