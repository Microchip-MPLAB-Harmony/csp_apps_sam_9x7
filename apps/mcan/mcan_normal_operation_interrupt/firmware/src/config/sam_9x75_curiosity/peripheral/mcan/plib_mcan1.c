/*******************************************************************************
  Controller Area Network (MCAN) Peripheral Library Source File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_mcan1.c

  Summary:
    MCAN peripheral library interface.

  Description:
    This file defines the interface to the MCAN peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
//DOM-IGNORE-END
// *****************************************************************************
// *****************************************************************************
// Header Includes
// *****************************************************************************
// *****************************************************************************

#include "device.h"
#include "interrupts.h"
#include "plib_mcan1.h"

// *****************************************************************************
// *****************************************************************************
// Global Data
// *****************************************************************************
// *****************************************************************************
#define MCAN_STD_ID_Msk        0x7FFU

volatile static MCAN_TX_FIFO_CALLBACK_OBJ mcan1TxFifoCallbackObj;
volatile static MCAN_TX_EVENT_FIFO_CALLBACK_OBJ mcan1TxEventFifoCallbackObj;
volatile static MCAN_RX_FIFO_CALLBACK_OBJ mcan1RxFifoCallbackObj[2];
volatile static MCAN_CALLBACK_OBJ mcan1CallbackObj;
static MCAN_OBJ mcan1Obj;

static const mcan_sidfe_registers_t mcan1StdFilter[] =
{
    {
        .MCAN_SIDFE_0 = MCAN_SIDFE_0_SFT(0UL) |
                  MCAN_SIDFE_0_SFID1(0x469UL) |
                  MCAN_SIDFE_0_SFID2(0x469UL) |
                  MCAN_SIDFE_0_SFEC(1UL)
    },
};

static inline void MCAN1_ZeroInitialize(volatile void* pData, size_t dataSize)
{
    volatile uint8_t* data = (volatile uint8_t*)pData;
    for (uint32_t index = 0; index < dataSize; index++)
    {
        data[index] = 0U;
    }
}

// *****************************************************************************
// *****************************************************************************
// MCAN1 PLib Interface Routines
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Function:
    void MCAN1_Initialize(void)

   Summary:
    Initializes given instance of the MCAN peripheral.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    None
*/
void MCAN1_Initialize(void)
{
    /* Start MCAN initialization */
    MCAN1_REGS->MCAN_CCCR = MCAN_CCCR_INIT_Msk;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) != MCAN_CCCR_INIT_Msk)
    {
        /* Wait for initialization complete */
    }

    /* Set CCE to unlock the configuration registers */
    MCAN1_REGS->MCAN_CCCR |= MCAN_CCCR_CCE_Msk;

    /* Set Nominal Bit timing and Prescaler Register */
    MCAN1_REGS->MCAN_NBTP  = MCAN_NBTP_NTSEG2(0) | MCAN_NBTP_NTSEG1(1) | MCAN_NBTP_NBRP(14) | MCAN_NBTP_NSJW(0);


    /* Global Filter Configuration Register */
    MCAN1_REGS->MCAN_GFC = MCAN_GFC_ANFS(2) | MCAN_GFC_ANFE(2);

    /* Set the operation mode */


    MCAN1_REGS->MCAN_CCCR &= ~MCAN_CCCR_INIT_Msk;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) == MCAN_CCCR_INIT_Msk)
    {
        /* Wait for initialization complete */
    }

    /* Select interrupt line */
    MCAN1_REGS->MCAN_ILS = 0x0U;

    /* Enable interrupt line */
    MCAN1_REGS->MCAN_ILE = MCAN_ILE_EINT0_Msk;

    /* Enable MCAN interrupts */
    MCAN1_REGS->MCAN_IE = MCAN_IE_BOE_Msk | MCAN_IE_ARAE_Msk | MCAN_IE_PEDE_Msk | MCAN_IE_PEAE_Msk | MCAN_IE_WDIE_Msk
                                      | MCAN_IE_EWE_Msk | MCAN_IE_EPE_Msk | MCAN_IE_ELOE_Msk
                                       | MCAN_IE_TFEE_Msk
                                       | MCAN_IE_TEFNE_Msk | MCAN_IE_TEFLE_Msk | MCAN_IE_TEFFE_Msk | MCAN_IE_TCFE_Msk | MCAN_IE_HPME_Msk
                                       | MCAN_IE_RF0NE_Msk | MCAN_IE_RF0LE_Msk | MCAN_IE_RF0FE_Msk
                                       | MCAN_IE_RF1NE_Msk | MCAN_IE_RF1LE_Msk | MCAN_IE_RF1FE_Msk
                                      
                                      | MCAN_IE_MRAFE_Msk;

  MCAN1_ZeroInitialize(&mcan1Obj.msgRAMConfig, sizeof(MCAN_MSG_RAM_CONFIG));
}


// *****************************************************************************
/* Function:
    bool MCAN1_MessageTransmitFifo(uint8_t numberOfMessage, MCAN_TX_BUFFER *txBuffer)

   Summary:
    Transmit multiple messages into MCAN bus from Tx FIFO.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    numberOfMessage - Total number of message.
    txBuffer        - Pointer to Tx buffer

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool MCAN1_MessageTransmitFifo(uint8_t numberOfMessage, MCAN_TX_BUFFER *txBuffer)
{
    uint8_t  *txFifo = NULL;
    uint8_t  *txBuf = (uint8_t *)txBuffer;
    uint32_t bufferNumber = 0U;
    uint8_t  tfqpi = 0U;
    uint8_t  count = 0U;

    if (((numberOfMessage < 1U) || (numberOfMessage > 1U)) || (txBuffer == NULL))
    {
        return false;
    }

    tfqpi = (uint8_t)((MCAN1_REGS->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk) >> MCAN_TXFQS_TFQPI_Pos);

    for (count = 0; count < numberOfMessage; count++)
    {
        txFifo = (uint8_t *)((uint8_t*)mcan1Obj.msgRAMConfig.txBuffersAddress + ((uint32_t)tfqpi * MCAN1_TX_FIFO_BUFFER_ELEMENT_SIZE));

        (void) memcpy(txFifo, txBuf, MCAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);

        txBuf += MCAN1_TX_FIFO_BUFFER_ELEMENT_SIZE;
        bufferNumber |= (1UL << tfqpi);
        tfqpi++;
        if (tfqpi == 1U)
        {
            tfqpi = 0U;
        }
    }

    __DSB();

    /* Set Transmission request */
    MCAN1_REGS->MCAN_TXBAR = bufferNumber;

    return true;
}

// *****************************************************************************
/* Function:
    uint8_t MCAN1_TxFifoFreeLevelGet(void)

   Summary:
    Returns Tx FIFO Free Level.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    None.

   Returns:
    Tx FIFO Free Level.
*/
uint8_t MCAN1_TxFifoFreeLevelGet(void)
{
    return (uint8_t)(MCAN1_REGS->MCAN_TXFQS & MCAN_TXFQS_TFFL_Msk);
}

// *****************************************************************************
/* Function:
    bool MCAN1_TxBufferIsBusy(uint8_t bufferNumber)

   Summary:
    Check if Transmission request is pending for the specific Tx buffer.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    None.

   Returns:
    true  - Transmission request is pending.
    false - Transmission request is not pending.
*/
bool MCAN1_TxBufferIsBusy(uint8_t bufferNumber)
{
    return ((MCAN1_REGS->MCAN_TXBRP & (1UL << bufferNumber)) != 0U);
}

// *****************************************************************************
/* Function:
    bool MCAN1_TxEventFifoRead(uint8_t numberOfTxEvent, MCAN_TX_EVENT_FIFO *txEventFifo)

   Summary:
    Read Tx Event FIFO for the transmitted messages.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    numberOfTxEvent - Total number of Tx Event
    txEventFifo     - Pointer to Tx Event FIFO

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool MCAN1_TxEventFifoRead(uint8_t numberOfTxEvent, MCAN_TX_EVENT_FIFO *txEventFifo)
{
    uint8_t txefgi     = 0U;
    uint8_t count      = 0U;
    uint8_t *txEvent   = NULL;
    uint8_t *txEvtFifo = (uint8_t *)txEventFifo;

    if (txEventFifo == NULL)
    {
        return false;
    }

    /* Read data from the Rx FIFO0 */
    txefgi = (uint8_t)((MCAN1_REGS->MCAN_TXEFS & MCAN_TXEFS_EFGI_Msk) >> MCAN_TXEFS_EFGI_Pos);
    for (count = 0U; count < numberOfTxEvent; count++)
    {
        txEvent = (uint8_t *) ((uint8_t *)mcan1Obj.msgRAMConfig.txEventFIFOAddress + ((uint32_t)txefgi * sizeof(MCAN_TX_EVENT_FIFO)));

        (void) memcpy(txEvtFifo, txEvent, sizeof(MCAN_TX_EVENT_FIFO));

        if ((count + 1U) == numberOfTxEvent)
        {
            break;
        }
        txEvtFifo += sizeof(MCAN_TX_EVENT_FIFO);
        txefgi++;
        if (txefgi == 1U)
        {
            txefgi = 0U;
        }
    }

    /* Ack the Tx Event FIFO position */
    MCAN1_REGS->MCAN_TXEFA = MCAN_TXEFA_EFAI((uint32_t)txefgi);

    return true;
}


// *****************************************************************************
/* Function:
    bool MCAN1_MessageReceiveFifo(MCAN_RX_FIFO_NUM rxFifoNum, uint8_t numberOfMessage, MCAN_RX_BUFFER *rxBuffer)

   Summary:
    Read messages from Rx FIFO0/FIFO1.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    rxFifoNum       - Rx FIFO number
    numberOfMessage - Total number of message
    rxBuffer        - Pointer to Rx buffer

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool MCAN1_MessageReceiveFifo(MCAN_RX_FIFO_NUM rxFifoNum, uint8_t numberOfMessage, MCAN_RX_BUFFER *rxBuffer)
{
    uint8_t rxgi = 0U;
    uint8_t count = 0U;
    uint8_t *rxFifo = NULL;
    uint8_t *rxBuf = (uint8_t *)rxBuffer;
    bool status = false;

    if (rxBuffer == NULL)
    {
        return status;
    }

    switch (rxFifoNum)
    {
        case MCAN_RX_FIFO_0:
            /* Read data from the Rx FIFO0 */
            rxgi = (uint8_t)((MCAN1_REGS->MCAN_RXF0S & MCAN_RXF0S_F0GI_Msk) >> MCAN_RXF0S_F0GI_Pos);
            for (count = 0U; count < numberOfMessage; count++)
            {
                rxFifo = (uint8_t *) ((uint8_t *)mcan1Obj.msgRAMConfig.rxFIFO0Address + ((uint32_t)rxgi * MCAN1_RX_FIFO0_ELEMENT_SIZE));

                (void) memcpy(rxBuf, rxFifo, MCAN1_RX_FIFO0_ELEMENT_SIZE);

                if ((count + 1U) == numberOfMessage)
                {
                    break;
                }
                rxBuf += MCAN1_RX_FIFO0_ELEMENT_SIZE;
                rxgi++;
                if (rxgi == 1U)
                {
                    rxgi = 0U;
                }
            }

            /* Ack the fifo position */
            MCAN1_REGS->MCAN_RXF0A = MCAN_RXF0A_F0AI((uint32_t)rxgi);

            status = true;
            break;
        case MCAN_RX_FIFO_1:
            /* Read data from the Rx FIFO1 */
            rxgi = (uint8_t)((MCAN1_REGS->MCAN_RXF1S & MCAN_RXF1S_F1GI_Msk) >> MCAN_RXF1S_F1GI_Pos);
            for (count = 0U; count < numberOfMessage; count++)
            {
                rxFifo = (uint8_t *) ((uint8_t *)mcan1Obj.msgRAMConfig.rxFIFO1Address + ((uint32_t)rxgi * MCAN1_RX_FIFO1_ELEMENT_SIZE));

                (void) memcpy(rxBuf, rxFifo, MCAN1_RX_FIFO1_ELEMENT_SIZE);

                if ((count + 1U) == numberOfMessage)
                {
                    break;
                }
                rxBuf += MCAN1_RX_FIFO1_ELEMENT_SIZE;
                rxgi++;
                if (rxgi == 1U)
                {
                    rxgi = 0U;
                }
            }
            /* Ack the fifo position */
            MCAN1_REGS->MCAN_RXF1A = MCAN_RXF1A_F1AI((uint32_t)rxgi);

            status = true;
            break;
        default:
            /* Do nothing */
            break;
    }
    return status;
}

// *****************************************************************************
/* Function:
    MCAN_ERROR MCAN1_ErrorGet(void)

   Summary:
    Returns the error during transfer.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    None.

   Returns:
    Error during transfer.
*/
MCAN_ERROR MCAN1_ErrorGet(void)
{
    MCAN_ERROR error;
    uint32_t   errorStatus = MCAN1_REGS->MCAN_PSR;

    error = (MCAN_ERROR) ((errorStatus & MCAN_PSR_LEC_Msk) | (errorStatus & MCAN_PSR_EP_Msk) | (errorStatus & MCAN_PSR_EW_Msk)
            | (errorStatus & MCAN_PSR_BO_Msk) | (errorStatus & MCAN_PSR_DLEC_Msk) | (errorStatus & MCAN_PSR_PXE_Msk));

    if ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) == MCAN_CCCR_INIT_Msk)
    {
        MCAN1_REGS->MCAN_CCCR &= ~MCAN_CCCR_INIT_Msk;
        while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) == MCAN_CCCR_INIT_Msk)
        {
            /* Wait for initialization complete */
        }
    }

    return error;
}

// *****************************************************************************
/* Function:
    void MCAN1_ErrorCountGet(uint8_t *txErrorCount, uint8_t *rxErrorCount)

   Summary:
    Returns the transmit and receive error count during transfer.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    txErrorCount - Transmit Error Count to be received
    rxErrorCount - Receive Error Count to be received

   Returns:
    None.
*/
void MCAN1_ErrorCountGet(uint8_t *txErrorCount, uint8_t *rxErrorCount)
{
    *txErrorCount = (uint8_t)(MCAN1_REGS->MCAN_ECR & MCAN_ECR_TEC_Msk);
    *rxErrorCount = (uint8_t)((MCAN1_REGS->MCAN_ECR & MCAN_ECR_REC_Msk) >> MCAN_ECR_REC_Pos);
}

// *****************************************************************************
/* Function:
    void MCAN1_MessageRAMConfigSet(uint8_t *msgRAMConfigBaseAddress)

   Summary:
    Set the Message RAM Configuration.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    msgRAMConfigBaseAddress - Pointer to application allocated buffer base address.
                              Application must allocate buffer from non-cached
                              contiguous memory and buffer size must be
                              MCAN1_MESSAGE_RAM_CONFIG_SIZE

   Returns:
    None
*/
void MCAN1_MessageRAMConfigSet(uint8_t *msgRAMConfigBaseAddress)
{
    uint32_t offset = 0U;
    uint32_t msgRAMConfigBaseAddr = (uint32_t)msgRAMConfigBaseAddress;

   (void) memset(msgRAMConfigBaseAddress, 0x00, MCAN1_MESSAGE_RAM_CONFIG_SIZE);

    /* Set MCAN CCCR Init for Message RAM Configuration */
    MCAN1_REGS->MCAN_CCCR |= MCAN_CCCR_INIT_ENABLED;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) != MCAN_CCCR_INIT_Msk)
    {
        /* Wait for configuration complete */
    }

    /* Set CCE to unlock the configuration registers */
    MCAN1_REGS->MCAN_CCCR |= MCAN_CCCR_CCE_Msk;

    mcan1Obj.msgRAMConfig.rxFIFO0Address = (mcan_rxf0e_registers_t *)msgRAMConfigBaseAddr;
    offset = MCAN1_RX_FIFO0_SIZE;
    /* Receive FIFO 0 Configuration Register */
    MCAN1_REGS->MCAN_RXF0C = MCAN_RXF0C_F0S(1UL) | MCAN_RXF0C_F0WM(0UL) | MCAN_RXF0C_F0OM_Msk |
            MCAN_RXF0C_F0SA(((uint32_t)mcan1Obj.msgRAMConfig.rxFIFO0Address >> 2));

    mcan1Obj.msgRAMConfig.rxFIFO1Address = (mcan_rxf1e_registers_t *)(msgRAMConfigBaseAddr + offset);
    offset += MCAN1_RX_FIFO1_SIZE;
    /* Receive FIFO 1 Configuration Register */
    MCAN1_REGS->MCAN_RXF1C = MCAN_RXF1C_F1S(1UL) | MCAN_RXF1C_F1WM(0UL) | MCAN_RXF1C_F1OM_Msk |
            MCAN_RXF1C_F1SA(((uint32_t)mcan1Obj.msgRAMConfig.rxFIFO1Address >> 2));

    mcan1Obj.msgRAMConfig.txBuffersAddress = (mcan_txbe_registers_t *)(msgRAMConfigBaseAddr + offset);
    offset += MCAN1_TX_FIFO_BUFFER_SIZE;
    /* Transmit Buffer/FIFO Configuration Register */
    MCAN1_REGS->MCAN_TXBC = MCAN_TXBC_TFQS(1UL) |
            MCAN_TXBC_TBSA(((uint32_t)mcan1Obj.msgRAMConfig.txBuffersAddress >> 2));

    mcan1Obj.msgRAMConfig.txEventFIFOAddress =  (mcan_txefe_registers_t *)(msgRAMConfigBaseAddr + offset);
    offset += MCAN1_TX_EVENT_FIFO_SIZE;
    /* Transmit Event FIFO Configuration Register */
    MCAN1_REGS->MCAN_TXEFC = MCAN_TXEFC_EFWM(0UL) | MCAN_TXEFC_EFS(1UL) |
            MCAN_TXEFC_EFSA(((uint32_t)mcan1Obj.msgRAMConfig.txEventFIFOAddress >> 2));

    mcan1Obj.msgRAMConfig.stdMsgIDFilterAddress = (mcan_sidfe_registers_t *)(msgRAMConfigBaseAddr + offset);
    (void) memcpy((void *)mcan1Obj.msgRAMConfig.stdMsgIDFilterAddress,
           (const void *)mcan1StdFilter,
           MCAN1_STD_MSG_ID_FILTER_SIZE);
    offset += MCAN1_STD_MSG_ID_FILTER_SIZE;
    /* Standard ID Filter Configuration Register */
    MCAN1_REGS->MCAN_SIDFC = MCAN_SIDFC_LSS(1UL) |
            MCAN_SIDFC_FLSSA(((uint32_t)mcan1Obj.msgRAMConfig.stdMsgIDFilterAddress >> 2));

    /* Set 16-bit MSB of mcan1 base address */

    /* Reference offset variable once to remove warning about the variable not being used after increment */
    (void)offset;

    /* Complete Message RAM Configuration by clearing MCAN CCCR Init */
    MCAN1_REGS->MCAN_CCCR &= ~MCAN_CCCR_INIT_Msk;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) == MCAN_CCCR_INIT_Msk)
    {
        /* Wait for configuration complete */
    }
}

// *****************************************************************************
/* Function:
    bool MCAN1_StandardFilterElementSet(uint8_t filterNumber, mcan_sidfe_registers_t *stdMsgIDFilterElement)

   Summary:
    Set a standard filter element configuration.

   Precondition:
    MCAN1_Initialize and MCAN1_MessageRAMConfigSet must have been called
    for the associated MCAN instance.

   Parameters:
    filterNumber          - Standard Filter number to be configured.
    stdMsgIDFilterElement - Pointer to Standard Filter Element configuration to be set on specific filterNumber.

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool MCAN1_StandardFilterElementSet(uint8_t filterNumber, mcan_sidfe_registers_t *stdMsgIDFilterElement)
{
    if ((filterNumber > 1U) || (stdMsgIDFilterElement == NULL))
    {
        return false;
    }
    mcan1Obj.msgRAMConfig.stdMsgIDFilterAddress[filterNumber - 1U].MCAN_SIDFE_0 = stdMsgIDFilterElement->MCAN_SIDFE_0;

    return true;
}

// *****************************************************************************
/* Function:
    bool MCAN1_StandardFilterElementGet(uint8_t filterNumber, mcan_sidfe_registers_t *stdMsgIDFilterElement)

   Summary:
    Get a standard filter element configuration.

   Precondition:
    MCAN1_Initialize and MCAN1_MessageRAMConfigSet must have been called
    for the associated MCAN instance.

   Parameters:
    filterNumber          - Standard Filter number to get filter configuration.
    stdMsgIDFilterElement - Pointer to Standard Filter Element configuration for storing filter configuration.

   Returns:
    Request status.
    true  - Request was successful.
    false - Request has failed.
*/
bool MCAN1_StandardFilterElementGet(uint8_t filterNumber, mcan_sidfe_registers_t *stdMsgIDFilterElement)
{
    if ((filterNumber > 1U) || (stdMsgIDFilterElement == NULL))
    {
        return false;
    }
    stdMsgIDFilterElement->MCAN_SIDFE_0 = mcan1Obj.msgRAMConfig.stdMsgIDFilterAddress[filterNumber - 1U].MCAN_SIDFE_0;

    return true;
}


void MCAN1_SleepModeEnter(void)
{
    MCAN1_REGS->MCAN_CCCR |=  MCAN_CCCR_CSR_Msk;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_CSA_Msk) != MCAN_CCCR_CSA_Msk)
    {
        /* Wait for clock stop request to complete */
    }
}

void MCAN1_SleepModeExit(void)
{
    MCAN1_REGS->MCAN_CCCR &=  ~MCAN_CCCR_CSR_Msk;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_CSA_Msk) == MCAN_CCCR_CSA_Msk)
    {
        /* Wait for no clock stop */
    }
    MCAN1_REGS->MCAN_CCCR &= ~MCAN_CCCR_INIT_Msk;
    while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) == MCAN_CCCR_INIT_Msk)
    {
        /* Wait for initialization complete */
    }
}

bool MCAN1_BitTimingCalculationGet(MCAN_BIT_TIMING_SETUP *setup, MCAN_BIT_TIMING *bitTiming)
{
    bool status = false;
    uint32_t numOfTimeQuanta;
    uint8_t tseg1;
    float temp1;
    float temp2;

    if ((setup != NULL) && (bitTiming != NULL))
    {
        if (setup->nominalBitTimingSet == true)
        {
            numOfTimeQuanta = MCAN1_CLOCK_FREQUENCY / (setup->nominalBitRate * ((uint32_t)setup->nominalPrescaler + 1U));
            if ((numOfTimeQuanta >= 4U) && (numOfTimeQuanta <= 385U))
            {
                if (setup->nominalSamplePoint < 50.0f)
                {
                    setup->nominalSamplePoint = 50.0f;
                }
                temp1 = (float)numOfTimeQuanta;
                temp2 = (temp1 * setup->nominalSamplePoint) / 100.0f;
                tseg1 = (uint8_t)temp2;
                bitTiming->nominalBitTiming.nominalTimeSegment2 = (uint8_t)(numOfTimeQuanta - tseg1 - 1U);
                bitTiming->nominalBitTiming.nominalTimeSegment1 = tseg1 - 2U;
                bitTiming->nominalBitTiming.nominalSJW = bitTiming->nominalBitTiming.nominalTimeSegment2;
                bitTiming->nominalBitTiming.nominalPrescaler = setup->nominalPrescaler;
                bitTiming->nominalBitTimingSet = true;
                status = true;
            }
            else
            {
                bitTiming->nominalBitTimingSet = false;
            }
        }
    }

    return status;
}

bool MCAN1_BitTimingSet(MCAN_BIT_TIMING *bitTiming)
{
    bool status = false;
    bool nominalBitTimingSet = false;

    if ((bitTiming->nominalBitTimingSet == true)
    && (bitTiming->nominalBitTiming.nominalTimeSegment1 >= 0x1U)
    && (bitTiming->nominalBitTiming.nominalTimeSegment2 <= 0x7FU)
    && (bitTiming->nominalBitTiming.nominalPrescaler <= 0x1FFU)
    && (bitTiming->nominalBitTiming.nominalSJW <= 0x7FU))
    {
        nominalBitTimingSet = true;
    }

    if (nominalBitTimingSet == true)
    {
        /* Start MCAN initialization */
        MCAN1_REGS->MCAN_CCCR = MCAN_CCCR_INIT_Msk;
        while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) != MCAN_CCCR_INIT_Msk)
        {
            /* Wait for initialization complete */
        }

        /* Set CCE to unlock the configuration registers */
        MCAN1_REGS->MCAN_CCCR |= MCAN_CCCR_CCE_Msk;

        /* Set Nominal Bit timing and Prescaler Register */
        MCAN1_REGS->MCAN_NBTP  = MCAN_NBTP_NTSEG2(bitTiming->nominalBitTiming.nominalTimeSegment2) | MCAN_NBTP_NTSEG1(bitTiming->nominalBitTiming.nominalTimeSegment1) | MCAN_NBTP_NBRP(bitTiming->nominalBitTiming.nominalPrescaler) | MCAN_NBTP_NSJW(bitTiming->nominalBitTiming.nominalSJW);

        /* Set the operation mode */


        MCAN1_REGS->MCAN_CCCR &= ~MCAN_CCCR_INIT_Msk;
        while ((MCAN1_REGS->MCAN_CCCR & MCAN_CCCR_INIT_Msk) == MCAN_CCCR_INIT_Msk)
        {
            /* Wait for initialization complete */
        }
        status = true;
    }
    return status;
}


// *****************************************************************************
/* Function:
    void MCAN1_TxFifoCallbackRegister(MCAN_TX_FIFO_CALLBACK callback, uintptr_t contextHandle)

   Summary:
    Sets the pointer to the function (and it's context) to be called when the
    given MCAN's transfer events occur.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    callback - A pointer to a function with a calling signature defined
    by the MCAN_TX_FIFO_CALLBACK data type.

    contextHandle - A value (usually a pointer) passed (unused) into the function
    identified by the callback parameter.

   Returns:
    None.
*/
void MCAN1_TxFifoCallbackRegister(MCAN_TX_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    if (callback == NULL)
    {
        return;
    }

    mcan1TxFifoCallbackObj.callback = callback;
    mcan1TxFifoCallbackObj.context = contextHandle;
}

// *****************************************************************************
/* Function:
    void MCAN1_TxEventFifoCallbackRegister(MCAN_TX_EVENT_FIFO_CALLBACK callback, uintptr_t contextHandle)

   Summary:
    Sets the pointer to the function (and it's context) to be called when the
    given MCAN's transfer events occur.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    callback - A pointer to a function with a calling signature defined
    by the MCAN_TX_EVENT_FIFO_CALLBACK data type.

    contextHandle - A value (usually a pointer) passed (unused) into the function
    identified by the callback parameter.

   Returns:
    None.
*/
void MCAN1_TxEventFifoCallbackRegister(MCAN_TX_EVENT_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    if (callback == NULL)
    {
        return;
    }

    mcan1TxEventFifoCallbackObj.callback = callback;
    mcan1TxEventFifoCallbackObj.context = contextHandle;
}


// *****************************************************************************
/* Function:
    void MCAN1_RxFifoCallbackRegister(MCAN_RX_FIFO_NUM rxFifoNum, MCAN_RX_FIFO_CALLBACK callback, uintptr_t contextHandle)

   Summary:
    Sets the pointer to the function (and it's context) to be called when the
    given MCAN's transfer events occur.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    rxFifoNum - Rx FIFO Number

    callback  - A pointer to a function with a calling signature defined
    by the MCAN_RX_FIFO_CALLBACK data type.

    contextHandle - A value (usually a pointer) passed (unused) into the function
    identified by the callback parameter.

   Returns:
    None.
*/
void MCAN1_RxFifoCallbackRegister(MCAN_RX_FIFO_NUM rxFifoNum, MCAN_RX_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    if (callback == NULL)
    {
        return;
    }

    mcan1RxFifoCallbackObj[rxFifoNum].callback = callback;
    mcan1RxFifoCallbackObj[rxFifoNum].context = contextHandle;
}

// *****************************************************************************
/* Function:
    void MCAN1_CallbackRegister(MCAN_CALLBACK callback, uintptr_t contextHandle)

   Summary:
    Sets the pointer to the function (and it's context) to be called when the
    given MCAN's transfer events occur.

   Precondition:
    MCAN1_Initialize must have been called for the associated MCAN instance.

   Parameters:
    callback  - A pointer to a function with a calling signature defined
    by the MCAN_CALLBACK data type.

    contextHandle - A value (usually a pointer) passed (unused) into the function
    identified by the callback parameter.

   Returns:
    None.
*/
void MCAN1_CallbackRegister(MCAN_CALLBACK callback, uintptr_t contextHandle)
{
    if (callback != NULL)
    {
        mcan1CallbackObj.callback = callback;
        mcan1CallbackObj.context = contextHandle;
    }
}

// *****************************************************************************
/* Function:
    void MCAN1_INT0_InterruptHandler(void)

   Summary:
    MCAN1 Peripheral Interrupt Handler.

   Description:
    This function is MCAN1 Peripheral Interrupt Handler and will
    called on every MCAN1 interrupt.

   Precondition:
    None.

   Parameters:
    None.

   Returns:
    None.

   Remarks:
    The function is called as peripheral instance's interrupt handler if the
    instance interrupt is enabled. If peripheral instance's interrupt is not
    enabled user need to call it from the main while loop of the application.
*/
void __attribute__((used)) MCAN1_INT0_InterruptHandler(void)
{
    uint8_t numberOfMessage = 0U;
    uint8_t numberOfTxEvent = 0U;

    uint32_t ir = MCAN1_REGS->MCAN_IR;
    /* Additional local variable to prevent MISRA violations (Rule 13.x) */
    uintptr_t context;

    if ((ir & (~(MCAN_IR_RF0N_Msk | MCAN_IR_RF1N_Msk | MCAN_IR_TFE_Msk | MCAN_IR_TEFN_Msk))) != 0U)
    {
        MCAN1_REGS->MCAN_IR = (ir & (~(MCAN_IR_RF0N_Msk | MCAN_IR_RF1N_Msk | MCAN_IR_TFE_Msk | MCAN_IR_TEFN_Msk)));
        if (mcan1CallbackObj.callback != NULL)
        {
            context = mcan1CallbackObj.context;
            mcan1CallbackObj.callback(ir, context);
        }
    }
    /* New Message in Rx FIFO 0 */
    if ((ir & MCAN_IR_RF0N_Msk) != 0U)
    {
        MCAN1_REGS->MCAN_IR = MCAN_IR_RF0N_Msk;

        numberOfMessage = (uint8_t)(MCAN1_REGS->MCAN_RXF0S & MCAN_RXF0S_F0FL_Msk);

        if (mcan1RxFifoCallbackObj[MCAN_RX_FIFO_0].callback != NULL)
        {
            context = mcan1RxFifoCallbackObj[MCAN_RX_FIFO_0].context;
            mcan1RxFifoCallbackObj[MCAN_RX_FIFO_0].callback(numberOfMessage, context);
        }
    }
    /* New Message in Rx FIFO 1 */
    if ((ir & MCAN_IR_RF1N_Msk) != 0U)
    {
        MCAN1_REGS->MCAN_IR = MCAN_IR_RF1N_Msk;
        numberOfMessage = (uint8_t)(MCAN1_REGS->MCAN_RXF1S & MCAN_RXF1S_F1FL_Msk);
        if (mcan1RxFifoCallbackObj[MCAN_RX_FIFO_1].callback != NULL)
        {
            context = mcan1RxFifoCallbackObj[MCAN_RX_FIFO_1].context;
            mcan1RxFifoCallbackObj[MCAN_RX_FIFO_1].callback(numberOfMessage, context);
        }
    }

    /* TX FIFO is empty */
    if ((ir & MCAN_IR_TFE_Msk) != 0U)
    {
        MCAN1_REGS->MCAN_IR = MCAN_IR_TFE_Msk;
        if (mcan1TxFifoCallbackObj.callback != NULL)
        {
            context = mcan1TxFifoCallbackObj.context;
            mcan1TxFifoCallbackObj.callback(context);
        }
    }
    /* Tx Event FIFO new entry */
    if ((ir & MCAN_IR_TEFN_Msk) != 0U)
    {
        MCAN1_REGS->MCAN_IR = MCAN_IR_TEFN_Msk;

        numberOfTxEvent = (uint8_t)(MCAN1_REGS->MCAN_TXEFS & MCAN_TXEFS_EFFL_Msk);
        if (mcan1TxEventFifoCallbackObj.callback != NULL)
        {
            context = mcan1TxEventFifoCallbackObj.context;
            mcan1TxEventFifoCallbackObj.callback(numberOfTxEvent, context);
        }
    }
}

/*******************************************************************************
 End of File
*/
