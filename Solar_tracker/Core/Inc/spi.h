#ifndef __SPI_H__
#define __SPI_H__
#include "common.h"
#include "stm32f446xx.h"

/*perform these steps:
1.Write proper GPIO registers: Configure GPIO for MOSI, MISO and SCK pins.
2.Write to the SPI_CR1 register:
Note:
    a)Configure the serial clock baud rate using the BR[2:0] bits (Note: 3).
    b)Configure the CPOL and CPHA bits combination to define one of the four
relationships between the data transfer and the serial clock. (Note: 2 - except the
case when CRC is enabled at TI mode).
    c)Select simplex or half-duplex mode by configuring RXONLY or BIDIMODE and
BIDIOE (RXONLY and BIDIMODE can't be set at the same time).
    d)Configure the LSBFIRST bit to define the frame format (Note: 2).
    e)Configure the CRCEN and CRCEN bits if CRC is needed (while SCK clock signal is at idle state).
    f)Configure SSM and SSI (Note: 2).
    g)Configure the MSTR bit (in multimaster NSS configuration, avoid conflict state on
NSS if master is configured to prevent MODF error).
    h)Set the DFF bit to configure the data frame format (8 or 16 bits).
3. Write to SPI_CR2 register:
    a)Configure SSOE (Note: 1 & 2).
    b)Set the FRF bit if the TI protocol is required.
4. Write to SPI_CRCPR register: Configure the CRC polynomial if needed.
5. Write proper DMA registers: Configure DMA s*/

#endif // __SPI_H__