/*
 * Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _PAL_NVM_H_
#define _PAL_NVM_H_

#include "pal_interfaces.h"

uint32_t driver_nvm_write(uint32_t offset, void *buffer, size_t size);
uint32_t driver_nvm_read(uint32_t offset, void *buffer, size_t size);
#endif /* _PAL_NVM_H_ */
