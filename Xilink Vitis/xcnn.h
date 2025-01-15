// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCNN_H
#define XCNN_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xcnn_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_bus_BaseAddress;
} XCnn_Config;
#endif

typedef struct {
    u64 Control_bus_BaseAddress;
    u32 IsReady;
} XCnn;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCnn_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCnn_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCnn_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCnn_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XCnn_Initialize(XCnn *InstancePtr, u16 DeviceId);
XCnn_Config* XCnn_LookupConfig(u16 DeviceId);
int XCnn_CfgInitialize(XCnn *InstancePtr, XCnn_Config *ConfigPtr);
#else
int XCnn_Initialize(XCnn *InstancePtr, const char* InstanceName);
int XCnn_Release(XCnn *InstancePtr);
#endif

void XCnn_Start(XCnn *InstancePtr);
u32 XCnn_IsDone(XCnn *InstancePtr);
u32 XCnn_IsIdle(XCnn *InstancePtr);
u32 XCnn_IsReady(XCnn *InstancePtr);
void XCnn_EnableAutoRestart(XCnn *InstancePtr);
void XCnn_DisableAutoRestart(XCnn *InstancePtr);
u32 XCnn_Get_return(XCnn *InstancePtr);

u32 XCnn_Get_input_image_BaseAddress(XCnn *InstancePtr);
u32 XCnn_Get_input_image_HighAddress(XCnn *InstancePtr);
u32 XCnn_Get_input_image_TotalBytes(XCnn *InstancePtr);
u32 XCnn_Get_input_image_BitWidth(XCnn *InstancePtr);
u32 XCnn_Get_input_image_Depth(XCnn *InstancePtr);
u32 XCnn_Write_input_image_Words(XCnn *InstancePtr, int offset, word_type *data, int length);
u32 XCnn_Read_input_image_Words(XCnn *InstancePtr, int offset, word_type *data, int length);
u32 XCnn_Write_input_image_Bytes(XCnn *InstancePtr, int offset, char *data, int length);
u32 XCnn_Read_input_image_Bytes(XCnn *InstancePtr, int offset, char *data, int length);

void XCnn_InterruptGlobalEnable(XCnn *InstancePtr);
void XCnn_InterruptGlobalDisable(XCnn *InstancePtr);
void XCnn_InterruptEnable(XCnn *InstancePtr, u32 Mask);
void XCnn_InterruptDisable(XCnn *InstancePtr, u32 Mask);
void XCnn_InterruptClear(XCnn *InstancePtr, u32 Mask);
u32 XCnn_InterruptGetEnabled(XCnn *InstancePtr);
u32 XCnn_InterruptGetStatus(XCnn *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
