/*
 * Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "test_database.h"

volatile uint32_t ffa_msg_send_client_delay_cnt;

static void delay(void)
{
    while (ffa_msg_send_client_delay_cnt--);
}

uint32_t ffa_msg_send_client(uint32_t test_run_data)
{
    ffa_args_t payload;
    uint32_t status = VAL_SUCCESS, i;
    uint32_t client_logical_id = GET_CLIENT_LOGIC_ID(test_run_data);
    uint32_t server_logical_id = GET_SERVER_LOGIC_ID(test_run_data);
    const char message[] = "FFA ACS suite";
    mb_buf_t mb;
    uint32_t output_reserve_count = 7, size = PAGE_SIZE_4K;

    if (val_is_ffa_feature_supported(FFA_MSG_SEND_32))
    {
        LOG(TEST, "\t   FFA_MSG_SEND_32 not supported, skipping the test\n", 0, 0);
        return VAL_SKIP_CHECK;
    }

    val_select_server_fn_direct(test_run_data, 0, 0, 0, 0);

    mb.send = val_memory_alloc(size);
    mb.recv = val_memory_alloc(size);
    if (mb.send == NULL || mb.recv == NULL)
    {
        LOG(ERROR, "\tFailed to allocate RxTx buffer\n", 0, 0);
        status = VAL_ERROR_POINT(1);
        goto free_memory;
    }

    /* Map TX and RX buffers */
    if (val_rxtx_map_64((uint64_t)mb.send, (uint64_t)mb.recv, PAGE_SIZE_4K))
    {
        LOG(ERROR, "\tRxTx Map failed\n", 0, 0);
        status = VAL_ERROR_POINT(2);
        goto free_memory;
    }

    val_memcpy(mb.send, message, sizeof(message));

    /* Fill the payload and send messgae to server
     * Executing the below squence twice, one for
     * ffa_send_direct_resp and one for ffa_msg_wait
     * */
    for (i = 0; i < 2 ; i++)
    {
retry_send:
        ffa_msg_send_client_delay_cnt = 0xff;
        val_memset(&payload, 0, sizeof(ffa_args_t));
        payload.arg1 = ((uint32_t)val_get_endpoint_id(client_logical_id) << 16) |
                                    val_get_endpoint_id(server_logical_id);
        payload.arg3 = sizeof(message);
        payload.arg4 = 0;
        val_ffa_msg_send(&payload);
        if (payload.arg2 == FFA_ERROR_BUSY)
        {
            /* If reciever rx buffer is not available, retry send after some time */
            delay();
            goto retry_send;
        }

        if (payload.fid != FFA_SUCCESS_32)
        {
            if (payload.fid != FFA_SUCCESS_64)
            {
                LOG(ERROR, "\tFFA_MSG_SEND failed err %x\n", payload.arg2, 0);
                status = VAL_ERROR_POINT(3);
            }
        }

        /* Return value for reserved registers - MBZ */
        if (val_reserve_param_check(payload, output_reserve_count))
        {
            LOG(ERROR, "\tReceived non-zero value for reserved registers\n",
                    0, 0);
            return VAL_ERROR_POINT(4);
        }
    }

    if (val_rxtx_unmap(val_get_endpoint_id(client_logical_id)))
    {
        LOG(ERROR, "\tRXTX_UNMAP failed\n", 0, 0);
        status = status ? status : VAL_ERROR_POINT(5);
    }

free_memory:
    if (val_memory_free(mb.recv, size) || val_memory_free(mb.send, size))
    {
        LOG(ERROR, "\tfree_rxtx_buffers failed\n", 0, 0);
        status = status ? status : VAL_ERROR_POINT(6);
    }

    /* Collect the server status in payload.arg3 */
    payload = val_select_server_fn_direct(test_run_data, 0, 0, 0, 0);

    return status ? status : (uint32_t)payload.arg3;
}
