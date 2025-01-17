/*
 * Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "val_framework.h"
#include "val_interfaces.h"
#include "val_ffa.h"

static ffa_args_t ffa_smccc(uint64_t fid, uint64_t arg1, uint64_t arg2,
                            uint64_t arg3, uint64_t arg4, uint64_t arg5,
                            uint64_t arg6, uint64_t arg7)
{
    ffa_args_t args;

    args.fid = fid;
    args.arg1 = arg1;
    args.arg2 = arg2;
    args.arg3 = arg3;
    args.arg4 = arg4;
    args.arg5 = arg5;
    args.arg6 = arg6;
    args.arg7 = arg7;
    val_call_conduit(&args);
    return args;
}

static void ffa_error(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_ERROR_32, args->arg1, args->arg2, args->arg3,
                      args->arg4, args->arg5, args->arg6, args->arg7);
}

/**
 * @brief Returns error code in response to a previous invocation
          of a FF-A function.
 * @param args - Input arguments to FFA_ERROR abi.
 * @return Error code in response to FF-A function.
**/
void val_ffa_error(ffa_args_t *args)
{
    ffa_error(args);
}

static void ffa_success(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_SUCCESS_64, args->arg1, args->arg2, args->arg3,
                          args->arg4, args->arg5, args->arg6, args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_SUCCESS_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
    }
}

/**
 * @brief Returns results upon successful completion of a previous
          invocation of a FF-A function.
 * @param args - Input arguments to FFA_SUCCESS_32 abi.
 * @return Returns success status code in response to FF-A function.
**/
void val_ffa_success_32(ffa_args_t *args)
{
    ffa_success(args, false);
}

/**
 * @brief Returns results upon successful completion of a previous
          invocation of a FF-A function.
 * @param args - Input arguments to FFA_SUCCESS_64 abi.
 * @return Returns success status code in response to FF-A function.
**/
void val_ffa_success_64(ffa_args_t *args)
{
    ffa_success(args, true);
}

static void ffa_version(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_VERSION_32, (uint32_t)args->arg1,
                      (uint32_t)args->arg2, (uint32_t)args->arg3,
                      (uint32_t)args->arg4, (uint32_t)args->arg5,
                      (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief Returns version of the Firmware Framework implementation
 *        at a FF-A instance.
 * @param args - Input arguments to FFA_VERSION abi.
 * @return Returns FFA version.
**/
void val_ffa_version(ffa_args_t *args)
{
    ffa_version(args);
}

static void ffa_msg_send_direct_req(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_MSG_SEND_DIRECT_REQ_64, args->arg1, args->arg2,
                          args->arg3, args->arg4, args->arg5, args->arg6,
                          args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_MSG_SEND_DIRECT_REQ_32, args->arg1, args->arg2,
                          args->arg3, args->arg4, args->arg5, args->arg6,
                          args->arg7);
    }
}

/**
 * @brief - Send a Partition message in parameter registers as a request to
 *          a target endpoint, run the endpoint and block until a response is
 *          available
 * @param args - Input arguments to FFA_MSG_SEND_DIRECT_REQ_32 abi.
 * @return - Returns success/error status code in response to
 *           FFA_MSG_SEND_DIRECT_REQ function.
**/
void val_ffa_msg_send_direct_req_32(ffa_args_t *args)
{
    ffa_msg_send_direct_req(args, false);
}

/**
 * @brief - Send a Partition message in parameter registers as a request to
 *          a target endpoint, run the endpoint and block until a response is
 *          available
 * @param args - Input arguments to FFA_MSG_SEND_DIRECT_REQ_64 abi.
 * @return - Returns success/error status code in response to
 *           FFA_MSG_SEND_DIRECT_REQ function.
**/
void val_ffa_msg_send_direct_req_64(ffa_args_t *args)
{
    ffa_msg_send_direct_req(args, true);
}

static void ffa_msg_send_direct_resp(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_MSG_SEND_DIRECT_RESP_64, args->arg1, args->arg2,
                          args->arg3, args->arg4, args->arg5, args->arg6,
                          args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_MSG_SEND_DIRECT_RESP_32, args->arg1, args->arg2,
                          args->arg3, args->arg4, args->arg5, args->arg6,
                          args->arg7);
    }
}

/**
 * @brief - Send a Partition message in parameter registers as a response to
 *          a target endpoint, run the endpoint and block until a response is
 *          available
 * @param args - Input arguments to FFA_MSG_SEND_DIRECT_RESP_32 abi.
 * @return - Returns success/error status code in response to
 *           FFA_MSG_SEND_DIRECT_RESP function.
**/
void val_ffa_msg_send_direct_resp_32(ffa_args_t *args)
{
    ffa_msg_send_direct_resp(args, false);
}

/**
 * @brief - Send a Partition message in parameter registers as a response to
 *          a target endpoint, run the endpoint and block until a response is
 *          available
 * @param args - Input arguments to FFA_MSG_SEND_DIRECT_RESP_64 abi.
 * @return - Returns success/error status code in response to
 *           FFA_MSG_SEND_DIRECT_RESP function.
**/
void val_ffa_msg_send_direct_resp_64(ffa_args_t *args)
{
    ffa_msg_send_direct_resp(args, true);
}

static void ffa_id_get(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_ID_GET_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Returns 16-bit ID of calling FF-A component.
 * @param id - Store the 16-bit ID.
 * @return - status code.
**/
ffa_endpoint_id_t val_get_curr_endpoint_id(void)
{
    ffa_args_t ret;
    ffa_endpoint_id_t id;

    ret = ffa_smccc(FFA_ID_GET_32, 0, 0, 0, 0, 0, 0, 0);
    if (ret.fid == FFA_ERROR_32)
        VAL_PANIC("\t Error: FFA_ID_GET_32 failed\n");

    id = ret.arg2 & 0xffff;
    return id;
}

/**
 * @brief - Returns 16-bit ID of calling FF-A component.
 * @param args - Input arguments to FFA_ID_GET_32 abi.
 * @return - void.
**/
void val_ffa_id_get(ffa_args_t *args)
{
    ffa_id_get(args);
}

static void ffa_rx_release(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_RX_RELEASE_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Relinquish ownership of a RX buffer after reading a message from it.
 * @param args - Input arguments to FFA_RX_RELEASE abi.
 * @return - void.
**/
void val_ffa_rx_release(ffa_args_t *args)
{
    ffa_rx_release(args);
}

static void ffa_rxtx_unmap(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_RXTX_UNMAP_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);

}
/**
 * @brief - Unmaps an endpoint's RX/TX buffer pair from the callee's
            translation regime.
 * @param args - Input arguments to FFA_RXTX_UNMAP abi.
 * @return - void.
**/
void val_ffa_rxtx_unmap(ffa_args_t *args)
{
    ffa_rxtx_unmap(args);
}

static void ffa_rxtx_map(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_RXTX_MAP_64, args->arg1, args->arg2, args->arg3,
                                args->arg4, args->arg5, args->arg6, args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_RXTX_MAP_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
    }
}

/**
 * @brief - Maps the RX/TX buffer pair in the callee's translation regime
 *          on behalf of an endpoint.
 * @param args - Input arguments to FFA_RXTX_MAP_32 abi.
 * @return - Returns success/error status code in response to
 *           FFA_RXTX_MAP_32 function.
**/
void val_ffa_rxtx_map_32(ffa_args_t *args)
{
    ffa_rxtx_map(args, false);
}

/**
 * @brief - Maps the RX/TX buffer pair in the callee's translation regime
 *          on behalf of an endpoint.
 * @param args - Input arguments to FFA_RXTX_MAP_64 abi.
 * @return - Returns success/error status code in response to
 *           FFA_RXTX_MAP_64 function.
**/
void val_ffa_rxtx_map_64(ffa_args_t *args)
{
    ffa_rxtx_map(args, true);
}

static void ffa_msg_send(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_MSG_SEND_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Send a Partition message to a VM through the RX/TX buffers
 *          by using indirect messaging
 * @param args - Input arguments to FFA_MSG_SEND abi.
 * @return - Returns success/error status code in response to
 *           FFA_MSG_SEND function.
**/
void val_ffa_msg_send(ffa_args_t *args)
{
    ffa_msg_send(args);
}

static void ffa_partition_info_get(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_PARTITION_INFO_GET_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Request Hypervisor and SPM to return information about
 *          partitions instantiated in the system.
 * @param args - Input arguments to FFA_PARTITION_INFO_GET abi.
 * @return - Returns success/error status code in response to
 *           FFA_PARTITION_INFO_GET function.
**/
void val_ffa_partition_info_get(ffa_args_t *args)
{
    ffa_partition_info_get(args);
}

static void ffa_features(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_FEATURES_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - This interface is used by a FF-A component at the lower EL
 *          at a FF-A instance to query.
 * @param args - Input arguments to FFA_FEATURES abi.
 * @return - Returns success/error status code or interface properties in
 *           response to FFA_FEATURES function.
**/
void val_ffa_features(ffa_args_t *args)
{
    ffa_features(args);
}

static void ffa_mem_reclaim(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_MEM_RECLAIM_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Restores exclusive access to a memory region back to its Owner.
 * @param args - Input arguments to FFA_MEM_RECLAIM abi.
 * @return - Returns success/error status code in
 *           response to FFA_MEM_RECLAIM function.
**/
void val_ffa_mem_reclaim(ffa_args_t *args)
{
    ffa_mem_reclaim(args);
}

static void ffa_msg_wait(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_MSG_WAIT_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Blocks the caller until message available in RX buffer
 *          or parameter registers
 * @param args - Input arguments to FFA_MSG_WAIT abi.
 * @return - Returns success/error status code in
 *           response to FFA_MSG_WAIT function.
**/
void val_ffa_msg_wait(ffa_args_t *args)
{
    ffa_msg_wait(args);
}

static void ffa_yield(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_YIELD_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Relinquish execution back to the scheduler on
 *          current physical CPU from the calling VM.
 * @param args - Input arguments to FFA_YIELD abi.
 * @return - Returns success/error status code in response to FFA_YIELD function.
**/
void val_ffa_yield(ffa_args_t *args)
{
    ffa_yield(args);
}

static void ffa_run(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_RUN_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Run an endpoint's execution context on the current PE.
 * @param args - Input arguments to FFA_RUN abi.
 * @return - Returns success/error status code in response to FFA_RUN abi.
**/
void val_ffa_run(ffa_args_t *args)
{
    ffa_run(args);
}

static void ffa_msg_poll(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_MSG_POLL_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Poll if a message is available in the caller's RX buffer.
 *          Execution is returned to the caller if no message is available.
 * @param args - Input arguments to FFA_MSG_POLL abi.
 * @return - Returns success/error status code in response to FFA_MSG_POLL abi.
**/
void val_ffa_msg_poll(ffa_args_t *args)
{
    ffa_msg_poll(args);
}

static void ffa_mem_donate(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_MEM_DONATE_64, args->arg1, args->arg2, args->arg3,
                                args->arg4, args->arg5, args->arg6, args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_MEM_DONATE_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
    }
}

/**
 * @brief - Starts a transaction to transfer of ownership of a memory region
 *          from a Sender endpoint to a Receiver endpoint.
 * @param args - Input arguments to FFA_MEM_DONATE_32 abi.
 * @return - Returns success/error status code in response to FFA_MEM_DONATE abi.
**/
void val_ffa_mem_donate_32(ffa_args_t *args)
{
    ffa_mem_donate(args, false);
}

/**
 * @brief - Starts a transaction to transfer of ownership of a memory region
 *          from a Sender endpoint to a Receiver endpoint.
 * @param args - Input arguments to FFA_MEM_DONATE_64 abi.
 * @return - Returns success/error status code in response to FFA_MEM_DONATE abi.
**/
void val_ffa_mem_donate_64(ffa_args_t *args)
{
    ffa_mem_donate(args, true);
}

static void ffa_mem_lend(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_MEM_LEND_64, args->arg1, args->arg2, args->arg3,
                                args->arg4, args->arg5, args->arg6, args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_MEM_LEND_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
    }
}

/**
 * @brief - Starts a transaction to transfer an Owner's access to a memory
 *          region and grant access to it to one or more Borrowers
 * @param args - Input arguments to FFA_MEM_LEND_32 abi.
 * @return - Returns success/error status code in response to FFA_MEM_LEND abi.
**/
void val_ffa_mem_lend_32(ffa_args_t *args)
{
    ffa_mem_lend(args, false);
}

/**
 * @brief - Starts a transaction to transfer an Owner's access to a memory
 *          region and grant access to it to one or more Borrowers.
 * @param args - Input arguments to FFA_MEM_LEND_64 abi.
 * @return - Returns success/error status code in response to FFA_MEM_LEND abi.
**/
void val_ffa_mem_lend_64(ffa_args_t *args)
{
    ffa_mem_lend(args, true);
}

static void ffa_mem_share(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_MEM_SHARE_64, args->arg1, args->arg2, args->arg3,
                                args->arg4, args->arg5, args->arg6, args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_MEM_SHARE_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
    }
}

/**
 * @brief - Starts a transaction to grant access to a memory region
 *          to one or more Borrowers.
 * @param args - Input arguments to FFA_MEM_SHARE_32 abi.
 * @return - Returns success/error status code in response to FFA_MEM_SHARE abi.
**/
void val_ffa_mem_share_32(ffa_args_t *args)
{
    ffa_mem_share(args, false);
}

/**
 * @brief - Starts a transaction to grant access to a memory region
 *          to one or more Borrowers.
 * @param args - Input arguments to FFA_MEM_SHARE_64 abi.
 * @return - Returns success/error status code in response to FFA_MEM_SHARE abi
**/
void val_ffa_mem_share_64(ffa_args_t *args)
{
    ffa_mem_share(args, true);
}

static void ffa_mem_retrieve(ffa_args_t *args, bool arch64)
{
    if (arch64)
    {
        *args = ffa_smccc(FFA_MEM_RETRIEVE_REQ_64, args->arg1, args->arg2,
                          args->arg3, args->arg4, args->arg5, args->arg6,
                          args->arg7);
    }
    else
    {
        *args = ffa_smccc(FFA_MEM_RETRIEVE_REQ_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
    }
}

/**
 * @brief - Requests completion of a donate, lend or share memory management
 *          transaction.
 * @param args - Input arguments to FFA_MEM_RETRIEVE_32 abi.
 * @return - Returns success/error status code in response to
            FFA_MEM_RETRIEVE_32 abi.
**/
void val_ffa_mem_retrieve_32(ffa_args_t *args)
{
    ffa_mem_retrieve(args, false);
}

/**
 * @brief - Requests completion of a donate, lend or share memory management
 *          transaction.
 * @param args - Input arguments to FFA_MEM_RETRIEVE_64 abi.
 * @return - Returns success/error status code in response to
            FFA_MEM_RETRIEVE_64 abi.
**/
void val_ffa_mem_retrieve_64(ffa_args_t *args)
{
    ffa_mem_retrieve(args, true);
}

static void ffa_mem_relinquish(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_MEM_RELINQUISH_32, (uint32_t)args->arg1,
                          (uint32_t)args->arg2, (uint32_t)args->arg3,
                          (uint32_t)args->arg4, (uint32_t)args->arg5,
                          (uint32_t)args->arg6, (uint32_t)args->arg7);
}

/**
 * @brief - Starts a transaction to transfer access to a shared or lent memory
 *          region from a Borrower back to its Owner.
 * @param args - Input arguments to FFA_MEM_RELINQUISH abi.
 * @return - Returns success/error status code in response to
            FFA_MEM_RELINQUISH abi.
**/
void val_ffa_mem_relinquish(ffa_args_t *args)
{
    ffa_mem_relinquish(args);
}

static void ffa_secondary_ep_register_64(ffa_args_t *args)
{
    *args = ffa_smccc(FFA_SECONDARY_EP_REGISTER_64,
                      (uint64_t)&pal_secondary_cpu_boot_entry,
                          args->arg2, args->arg3,
                          args->arg4, args->arg5,
                          args->arg6, args->arg7);
}

/**
 * @brief - Register secondary cpu endpoint with SPMC
 * @param - Void
 * @return - Void
**/
void val_ffa_secondary_ep_register_64(void)
{
    ffa_args_t args;

    val_memset(&args, 0, sizeof(ffa_args_t));
    ffa_secondary_ep_register_64(&args);
}

/**
 * @brief - Maps the RX/TX buffer pair in the callee's translation regime
 *          on behalf of an endpoint.
 * @param tx_buf - TX buffer address.
 * @param rx_buf - RX buffer address.
 * @param page_count - 4K page count.
 * @return - Returns status code.
**/
uint32_t val_rxtx_map_64(uint64_t tx_buf, uint64_t rx_buf, uint32_t page_count)
{
    ffa_args_t payload;
    static bool is_registered = false;


    /* TODO: TF-A is not supporting FFA_RXTX_UNMAP, so the endpoint must register only once.
     *       Remove this work-around once feature is available.
     */
    if (!is_registered)
    {
        val_memset(&payload, 0, sizeof(ffa_args_t));
        payload.arg1 = (uint64_t)val_mem_virt_to_phys((void *)tx_buf);
        payload.arg2 = (uint64_t)val_mem_virt_to_phys((void *)rx_buf);
        payload.arg3 = page_count;

        val_ffa_rxtx_map_64(&payload);

        if (payload.fid == FFA_ERROR_32)
        {
            LOG(ERROR, "\tRXTX_MAP failed err 0x%x\n", payload.arg2, 0);
            return VAL_ERROR;
        }

        is_registered = true;
    }

    return VAL_SUCCESS;
}

/**
 * @brief - Maps the RX/TX buffer pair in the callee's translation regime
 *          on behalf of an endpoint.
 * @param tx_buf - TX buffer address.
 * @param rx_buf - RX buffer address.
 * @param page_count - 4K page count.
 * @return - Returns status code.
**/
uint32_t val_rxtx_map_32(uint64_t tx_buf, uint64_t rx_buf, uint32_t page_count)
{
    ffa_args_t payload;

    val_memset(&payload, 0, sizeof(ffa_args_t));
    payload.arg1 = (uint64_t)val_mem_virt_to_phys((void *)tx_buf);
    payload.arg2 = (uint64_t)val_mem_virt_to_phys((void *)rx_buf);
    payload.arg3 = page_count;

    val_ffa_rxtx_map_32(&payload);

    if (payload.fid == FFA_ERROR_32)
    {
        LOG(ERROR, "\tRXTX_MAP failed err 0x%x\n", payload.arg2, 0);
        return VAL_ERROR;
    }
    return VAL_SUCCESS;
}

/**
 * @brief - Unmaps an endpoint's RX/TX buffer pair from the callee's
            translation regime.
 * @param id - Endpoint id.
 * @return - Returns status code.
**/
uint32_t val_rxtx_unmap(ffa_endpoint_id_t id)
{
    ffa_args_t payload;

    /* TODO: TF-A is not supporting this feature, so return success.
     *       Remove this work-around once this feature is available.
     */
    return VAL_SUCCESS;

    val_memset(&payload, 0, sizeof(ffa_args_t));
    payload.arg1 = (uint32_t)(id << 16);
    val_ffa_rxtx_unmap(&payload);

    if (payload.fid == FFA_ERROR_32)
    {
        LOG(ERROR, "RXTX_UNMAP failed err 0x%x\n", payload.arg2, 0);
        return VAL_ERROR;
    }
    return VAL_SUCCESS;
}

/**
 * @brief - Relinquish ownership of a RX buffer after reading a message from it.
 * @param - void
 * @return - Returns status code.
**/
uint32_t val_rx_release(void)
{
    ffa_args_t payload;

    /* Release the RX buffer */
    val_memset(&payload, 0, sizeof(ffa_args_t));
    val_ffa_rx_release(&payload);

    if (payload.fid == FFA_ERROR_32)
    {
        LOG(ERROR, "RX_RELEASE failed err 0x%x\n", payload.arg2, 0);
        return VAL_ERROR;
    }
    return VAL_SUCCESS;
}

/**
 * @brief - Check the reserved parameters are zero, if not return error.
 * @param args - Parameter structure.
 * @param param_count - Reserve parameter count.
 * @return - Returns status code.
**/
uint32_t val_reserve_param_check(ffa_args_t args, uint32_t param_count)
{
    uint32_t total_count = 8;
    uint32_t count = total_count - param_count;
    uint64_t *payload = (uint64_t *)&args;

    for (; count < 8; count++)
    {
        if (payload[count])
            return VAL_ERROR;
    }

    return VAL_SUCCESS;
}

