/*
 * Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _PAL_UART_PL011_H_
#define _PAL_UART_PL011_H_

#include "pal_interfaces.h"

/* typedef's */
typedef struct {
    volatile uint32_t uartdr;          /* Offset: 0x000 (R/W) Data Register */
    union {
        volatile uint32_t uartrsr;     /* Offset: 0x004 (R/ ) Receive status register */
        volatile uint32_t uartecr;     /* Offset: 0x004 ( /W) Error clear register */
    };
    volatile uint32_t reserved_0[4];   /* Offset: 0x008-0x014 Reserved */
    volatile uint32_t uartfr;          /* Offset: 0x018 (R/ ) Flag register */
    volatile uint32_t reserved_1;      /* Offset: 0x01C Reserved */
    volatile uint32_t uartilpr;        /* Offset: 0x020 (R/W) IrDA low-power counter register */
    volatile uint32_t uartibrd;        /* Offset: 0x024 (R/W) Integer baud rate register */
    volatile uint32_t uartfbrd;        /* Offset: 0x028 (R/W) Fractional baud rate register */
    volatile uint32_t uartlcr_h;       /* Offset: 0x02C (R/W) Line control register */
    volatile uint32_t uartcr;          /* Offset: 0x030 (R/W) Control register */
    volatile uint32_t uartifls;        /* Offset: 0x034 (R/W) Interrupt FIFO level select reg */
    volatile uint32_t uartimsc;        /* Offset: 0x038 (R/W) Interrupt mask set/clear register */
    volatile uint32_t uartris;         /* Offset: 0x03C (R/ ) Raw interrupt status register */
    volatile uint32_t uartmis;         /* Offset: 0x040 (R/ ) Masked interrupt status register */
    volatile uint32_t uarticr;         /* Offset: 0x044 ( /W) Interrupt clear register */
    volatile uint32_t uartdmacr;       /* Offset: 0x048 (R/W) DMA control register */
} uart_t;

/* UART Enable */
#define UART_PL011_UARTCR_UARTEN_OFF       0x0u
#define UART_PL011_UARTCR_EN_MASK          (0x1u << UART_PL011_UARTCR_UARTEN_OFF)
/* Transmit enable */
#define UART_PL011_UARTCR_TXE_OFF          0x8u
#define UART_PL011_UARTCR_TX_EN_MASK       (0x1u << UART_PL011_UARTCR_TXE_OFF)
#define UART_PL011_UARTFR_TX_FIFO_FULL_OFF 0x5u
#define UART_PL011_UARTFR_TX_FIFO_FULL     (0x1u << UART_PL011_UARTFR_TX_FIFO_FULL_OFF)

#define UART_PL011_INTR_TX_OFF             0x5u
#define UART_PL011_TX_INTR_MASK            (0x1u << UART_PL011_INTR_TX_OFF)
#define UART_PL011_UARTLCR_H_FEN_OFF       0x4u
#define UART_PL011_UARTLCR_H_FEN_MASK      (0x1u << UART_PL011_UARTLCR_H_FEN_OFF)
#define UART_PL011_UARTLCR_H_WLEN_8         5
#define UART_PL011_UARTLCR_H_WLEN_8_MASK   (3 << UART_PL011_UARTLCR_H_WLEN_8)
#define UART_PL011_CLK_IN_HZ    24000000
#define UART_PL011_BAUDRATE     115200
#define UART_PL011_LINE_CONTROL  (UART_PL011_UARTLCR_H_FEN_MASK | UART_PL011_UARTLCR_H_WLEN_8_MASK)

#if defined(SP1_COMPILE)
#define PLATFORM_UART_BASE PLATFORM_S_UART_BASE
#elif defined(VM1_COMPILE)
#define PLATFORM_UART_BASE PLATFORM_NS_UART_BASE
#else
#define PLATFORM_UART_BASE 0x0
#endif

/* function prototypes */
extern void driver_uart_pl011_putc(uint8_t c);

#endif /* _PAL_UART_PL011_H_ */
