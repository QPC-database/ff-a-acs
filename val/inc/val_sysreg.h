/*
 * Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _VAL_SYSREG_H_
#define _VAL_SYSREG_H_

#include "val_framework.h"

extern void val_mair_write(uint64_t value, uint64_t el_num);
extern void val_tcr_write(uint64_t value, uint64_t el_num);
extern void val_ttbr0_write(uint64_t value, uint64_t el_num);
extern void val_sctlr_write(uint64_t value, uint64_t el_num);
extern uint64_t val_sctlr_read(uint64_t el_num);
extern uint64_t val_ttbr0_read(uint64_t el_num);
extern uint64_t val_read_mpidr(void);
extern uint64_t val_read_current_el(void);
extern uint64_t val_elr_el1_read(void);
extern uint64_t val_esr_el1_read(void);
extern uint64_t val_far_el1_read(void);
extern void val_elr_el1_write(uint64_t value);
extern uint64_t val_id_aa64mmfr0_el1_read(void);
extern void val_dataCacheCleanInvalidateVA(uint64_t va);
extern void val_dataCacheCleanVA(uint64_t va);
extern void val_dataCacheInvalidateVA(uint64_t va);
#endif /* _VAL_SYSREG_H_ */
