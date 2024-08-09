---
title: Harmony 3 peripheral library application examples for SAM9X7 family
nav_order: 1
has_children: true
has_toc: false
---
[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Harmony 3 peripheral library application examples for SAM9X7 family

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices.  Refer to the following links for more information.

- [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)
- [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
- [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)
- [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)

This repository contains the MPLAB® Harmony 3 peripheral library application examples for SAM9X7 family

- [Release Notes](release_notes.md)
- [MPLAB® Harmony License](mplab_harmony_license.md)

To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

## Contents Summary

| Folder     | Description                             |
| ---        | ---                                     |
| apps       | Contains peripheral library example applications |
| docs       | Contains documentation in html format for offline viewing (to be used only after cloning this repository onto a local machine). Use [github pages](https://microchip-mplab-harmony.github.io/csp_apps_sam_9x7/) of this repository for viewing it online. |

## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more peripheral libraries.

| Name | Description |
| ---- | ----------- |
| [ADC automatic window comparison](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_ADC_AUTOMATIC_WINDOW_COMPARISON&redirect=true) | This example application shows how to sample an analog input in polled mode and send the converted data to console using automatic window comparison of converted values |
| [ADC low power](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_ADC_LOW_POWER&redirect=true) | This example application shows the different low power sleep modes available with Fast Wake up either enabled or disabled |
| [ADC Polling](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_ADC_POLLING&redirect=true) | This example application shows how to sample an analog input in polled mode and send the converted data to console |
| [Clock configuration](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_CLOCK_CONFIGURATION&redirect=true) | This example application shows how to configure the clock system to run the device at maximum frequency. It also outputs a prescaled clock signal on a GPIO pin for measurement and verification |
| [Low power modes](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_LOW_POWER_MODES&redirect=true) | This example application shows how to enter low power modes of SAM9X75 MPU |
| [DBGU blocking](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_DBGU_BLOCKING&redirect=true) | This example application demonstrates how to use the DBGU peripheral to transfer a block of data in a blocking manner |
| [DBGU Interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_DBGU_INTERRUPT&redirect=true) | This example application demonstrates how to use the DBGU peripheral to transfer a block of data in a non-blocking manner |
| [DBGU ring buffer](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_DBGU_RING_BUFFER&redirect=true) | This example application shows how to use DBGU peripheral in ring buffer mode |
| [FLEXCOM SPI EEPROM read write](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_FLEXCOM_SPI_EEPROM_READ_WRITE&redirect=true) | This example application shows how to use the flexcom module in SPI mode |
| [FLEXCOM SPI self loopback dma ](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_FLEXCOM_SPI_SELF_LOOPBACK_DMA&redirect=true) | This example application shows how to use the FLEXCOM SPI peripheral with DMA to transmit and receive a block of data |
| [FLEXCOM TWI (I2C) EEPROM]() | This example application shows how to use the flexcom module in TWI mode |
| [FLEXCOM USART flow control](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_FLEXCOM_USART_FLOW_CONTROL&redirect=true) | This example application shows how to use the flexcom module in USART flow control mode |
| [MCAN FD blocking](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_MCAN_FD_BLOCKING&redirect=true) | This example shows how to use the MCAN module to transmit and receive CAN FD messages in polling mode |
| [MCAN FD interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_MCAN_FD_INTERRUPT&redirect=true) | This example shows how to use the MCAN module to transmit and receive CAN FD messages in interrupt mode |
| [MCAN interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_MCAN_INTERRUPT&redirect=true) | This example shows how to use the MCAN module to transmit and receive CAN messages in interrupt mode |
| [OTPC read write (emulation)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_OTPC_READ_WRITE_EMULATION&redirect=true) | This example application shows how to use the OTPC Peripheral library to perform OTP operations |
| [PIO interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PIO_INTERRUPT&redirect=true) | This example application shows how to generate GPIO interrupt on switch press and release, and indicate the switch status using the LED |
| [PIO polling](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PIO_POLLING&redirect=true) | This example application shows how to poll the switch input, and indicate the switch status using the LED |
| [PIT polling](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PIT_POLLING&redirect=true) | This example application shows how to use PIT counter in polling mode |
| [PIT period change](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PIT_PERIOD_CHANGE&redirect=true) | This example application shows how PIT period can be changed during runtime |
| [PIT start stop](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PIT_START_STOP&redirect=true) | This example application shows how PIT can be started and stopped at runtime |
| [PIT64B periodic interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PIT64B_PERIODIC_INTERRUPT&redirect=true) | This application shows how to use PIT64B counter in interrupt mode |
| [PWM channels](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_PWM_CHANNELS&redirect=true) | This example demonstrates how to use the PWM peripheral to generate PWM signals |
| [RSTC interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_RSTC_INTERRUPT&redirect=true) | This example application shows how to use the RSTC peripheral to generate an interrupt instead of generating a reset, when the Reset switch is pressed on board |
| [RSTC reset cause](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_RSTC_RESET_CAUSE&redirect=true) | This example shows how to use the RSTC peripheral to indicate the cause of the device reset |
| [RTC alarm interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_RTC_ALARM_INTERRUPT&redirect=true) | This example application shows how to use the RTC to configure the time and generate the alarm |
| [RTT alarm interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_RTT_ALARM_INTERRUPT&redirect=true) | This example application shows how to use the RTT to generate alarm interrupt |
| [RTT periodic interrupt](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_RTT_PERIODIC_INTERRUPT&redirect=true) | This example application shows how to use the RTT to generate periodic interrupts |
| [SHDWC wakeup](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_SHDWC_WAKEUP&redirect=true) | This example application shows how to shutdown and wakeup the device using SHDWC peripheral |
| [TC timer mode](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_TC_TIMER_MODE&redirect=true) | This example application shows how to use the TC module in timer mode to generate periodic interrupt |
| [TRNG random number](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_TRNG_RANDOM_NUMBER&redirect=true) | This example application shows how to use the TRNG Peripheral library to generate and read a random number |
| [WDT timeout](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_WDT_TIMEOUT&redirect=true) | This example application shows how to generate a Watchdog timer reset by emulating a deadlock |
| [XDMAC memory transfer](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=CSP_APPS_SAM_9x7_XDMAC_MEMORY_TRANSFER&redirect=true) | This example application shows how to use the XDMAC peripheral to do a memory to memory transfer and illustrates the usage of burst size to reduce the transfer time |

____

[![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7/blob/master/mplab_harmony_license.md)
[![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/csp_apps_sam_9x7.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7/releases/latest)
[![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/csp_apps_sam_9x7.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7/releases/latest)
[![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/csp_apps_sam_9x7.svg)](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_9x7/graphs/commit-activity)
[![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/csp_apps_sam_9x7.svg)]()

____

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/csp_apps_sam_9x7.svg?style=social)]()
[![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/csp_apps_sam_9x7.svg?style=social)]()