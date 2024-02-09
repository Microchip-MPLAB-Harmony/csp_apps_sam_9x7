/*
 * Component description for SCKC
 *
 * Copyright (c) 2023 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2023-01-20T08:33:42Z */
#ifndef _SAM9X7_SCKC_COMPONENT_H_
#define _SAM9X7_SCKC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR SCKC                                         */
/* ************************************************************************** */

/* -------- SCKC_CR : (SCKC Offset: 0x00) (R/W 32) Slow Clock Controller Configuration Register -------- */
#define SCKC_CR_RESETVALUE                    _UINT32_(0x01)                                       /*  (SCKC_CR) Slow Clock Controller Configuration Register  Reset Value */

#define SCKC_CR_OSC32EN_Pos                   _UINT32_(1)                                          /* (SCKC_CR) 32.768 kHz Crystal Oscillator Position */
#define SCKC_CR_OSC32EN_Msk                   (_UINT32_(0x1) << SCKC_CR_OSC32EN_Pos)               /* (SCKC_CR) 32.768 kHz Crystal Oscillator Mask */
#define SCKC_CR_OSC32EN(value)                (SCKC_CR_OSC32EN_Msk & (_UINT32_(value) << SCKC_CR_OSC32EN_Pos)) /* Assigment of value for OSC32EN in the SCKC_CR register */
#define   SCKC_CR_OSC32EN_0_Val               _UINT32_(0x0)                                        /* (SCKC_CR) 32.768 kHz crystal oscillator is disabled.  */
#define   SCKC_CR_OSC32EN_1_Val               _UINT32_(0x1)                                        /* (SCKC_CR) 32.768 kHz crystal oscillator is enabled.  */
#define SCKC_CR_OSC32EN_0                     (SCKC_CR_OSC32EN_0_Val << SCKC_CR_OSC32EN_Pos)       /* (SCKC_CR) 32.768 kHz crystal oscillator is disabled. Position  */
#define SCKC_CR_OSC32EN_1                     (SCKC_CR_OSC32EN_1_Val << SCKC_CR_OSC32EN_Pos)       /* (SCKC_CR) 32.768 kHz crystal oscillator is enabled. Position  */
#define SCKC_CR_OSC32BYP_Pos                  _UINT32_(2)                                          /* (SCKC_CR) 32.768 kHz Crystal Oscillator Bypass Position */
#define SCKC_CR_OSC32BYP_Msk                  (_UINT32_(0x1) << SCKC_CR_OSC32BYP_Pos)              /* (SCKC_CR) 32.768 kHz Crystal Oscillator Bypass Mask */
#define SCKC_CR_OSC32BYP(value)               (SCKC_CR_OSC32BYP_Msk & (_UINT32_(value) << SCKC_CR_OSC32BYP_Pos)) /* Assigment of value for OSC32BYP in the SCKC_CR register */
#define   SCKC_CR_OSC32BYP_0_Val              _UINT32_(0x0)                                        /* (SCKC_CR) 32.768 kHz crystal oscillator is not bypassed.  */
#define   SCKC_CR_OSC32BYP_1_Val              _UINT32_(0x1)                                        /* (SCKC_CR) 32.768 kHz crystal oscillator is bypassed and accepts an external slow clock on XIN32.  */
#define SCKC_CR_OSC32BYP_0                    (SCKC_CR_OSC32BYP_0_Val << SCKC_CR_OSC32BYP_Pos)     /* (SCKC_CR) 32.768 kHz crystal oscillator is not bypassed. Position  */
#define SCKC_CR_OSC32BYP_1                    (SCKC_CR_OSC32BYP_1_Val << SCKC_CR_OSC32BYP_Pos)     /* (SCKC_CR) 32.768 kHz crystal oscillator is bypassed and accepts an external slow clock on XIN32. Position  */
#define SCKC_CR_TD_OSCSEL_Pos                 _UINT32_(24)                                         /* (SCKC_CR) Timing Domain Slow Clock Selector Position */
#define SCKC_CR_TD_OSCSEL_Msk                 (_UINT32_(0x1) << SCKC_CR_TD_OSCSEL_Pos)             /* (SCKC_CR) Timing Domain Slow Clock Selector Mask */
#define SCKC_CR_TD_OSCSEL(value)              (SCKC_CR_TD_OSCSEL_Msk & (_UINT32_(value) << SCKC_CR_TD_OSCSEL_Pos)) /* Assigment of value for TD_OSCSEL in the SCKC_CR register */
#define   SCKC_CR_TD_OSCSEL_RC_Val            _UINT32_(0x0)                                        /* (SCKC_CR) Slow clock of the timing domain is driven by the embedded 32 kHz (typical) RC oscillator.  */
#define   SCKC_CR_TD_OSCSEL_XTAL_Val          _UINT32_(0x1)                                        /* (SCKC_CR) Slow clock of the timing domain is driven by the 32.768 kHz crystal oscillator.  */
#define SCKC_CR_TD_OSCSEL_RC                  (SCKC_CR_TD_OSCSEL_RC_Val << SCKC_CR_TD_OSCSEL_Pos)  /* (SCKC_CR) Slow clock of the timing domain is driven by the embedded 32 kHz (typical) RC oscillator. Position  */
#define SCKC_CR_TD_OSCSEL_XTAL                (SCKC_CR_TD_OSCSEL_XTAL_Val << SCKC_CR_TD_OSCSEL_Pos) /* (SCKC_CR) Slow clock of the timing domain is driven by the 32.768 kHz crystal oscillator. Position  */
#define SCKC_CR_Msk                           _UINT32_(0x01000006)                                 /* (SCKC_CR) Register Mask  */


/** \brief SCKC register offsets definitions */
#define SCKC_CR_REG_OFST               _UINT32_(0x00)      /* (SCKC_CR) Slow Clock Controller Configuration Register Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SCKC register API structure */
typedef struct
{  /* Slow Clock Controller */
  __IO  uint32_t                       SCKC_CR;            /**< Offset: 0x00 (R/W  32) Slow Clock Controller Configuration Register */
} sckc_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAM9X7_SCKC_COMPONENT_H_ */
