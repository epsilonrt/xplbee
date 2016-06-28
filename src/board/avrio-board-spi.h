/*
 * Licensed under the Apache License, Version 2.0 (the "License")
 */
#ifndef _AVRIO_BOARD_SPI_H_
#define _AVRIO_BOARD_SPI_H_
#include <avrio/defs.h>
#include <avrio/delay.h>
#include <avr/io.h>

/* constants ================================================================ */
#define SPI_SS_BIT       4
#define SPI_SCK_BIT      7
#define SPI_MOSI_BIT     5
#define SPI_MISO_BIT     6
#define SPI_DDR          DDRB
#define SPI_PORT         PORTB

#define SPI_VCC_BIT      4
#define SPI_VCC_DDR      DDRA
#define SPI_VCC_PORT     PORTA

/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
INLINE void 
vSpiBoardInitMaster (void) {

  SPI_PORT &= ~(_BV (SPI_SCK_BIT) | _BV (SPI_MOSI_BIT));
  SPI_DDR  |= _BV (SPI_SCK_BIT) | _BV (SPI_MOSI_BIT);
  SPI_PORT |= _BV (SPI_MISO_BIT);
  SPI_DDR  &= ~_BV (SPI_MISO_BIT);
  SPI_VCC_PORT &= ~_BV (SPI_VCC_BIT);
  SPI_VCC_DDR  |=  _BV (SPI_VCC_BIT);
}


// -----------------------------------------------------------------------------
INLINE void 
vSpiBoardSetSsAsInput (void) {

  SPI_PORT |=  _BV (SPI_SS_BIT); /* Validation pull-up sur SS */
  SPI_DDR  &= ~_BV (SPI_SS_BIT);
}

// -----------------------------------------------------------------------------
INLINE void 
vSpiBoardSetSsAsOutput (void) {

  SPI_PORT |= _BV (SPI_SS_BIT); /* SS = 1 */
  SPI_DDR  |= _BV (SPI_SS_BIT);
}

// -----------------------------------------------------------------------------
INLINE void 
vSpiSetSs (void) {

  SPI_VCC_PORT  |= _BV (SPI_VCC_BIT);
  delay_ms(10);  // délai de démarrage max HSC 7.3 ms
  SPI_PORT &= ~_BV (SPI_SS_BIT); /* SS = 0 -> validé */
}

// -----------------------------------------------------------------------------
INLINE void 
vSpiClearSs (void) {

  SPI_PORT |= _BV (SPI_SS_BIT); /* SS = 1 -> invalidé */
  delay_ms(1);
  SPI_VCC_PORT &= ~_BV (SPI_VCC_BIT);
}

/* ========================================================================== */
#endif  /* _AVRIO_BOARD_SPI_H_ not defined */
