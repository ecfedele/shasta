// -------------------------------------------------------------------------------------------------------- //
// Title       : UEFI Test Harnesses (Header), UEFI Print Utility Tests, UEFI Bootloader Test Suite         //
// Filename    : main.c                                                                                     //
// Description : Provides the header file for some UEFI test functionality harnesses. Mimics several UEFI   //
//               functions incorporated into /src/boot/uefiutil.h using C standard functions to provide 1:1 //
//               testing of the Print logic.                                                                //
//                                                                                                          //
// Project     : Shasta Microkernel                                                                         //
// Main Author : Elijah Creed Fedele <ecfedele@outlook.com>                                                 //
// Created     : August 30, 2023                                                                            //
// Modified    : August 31, 2023                                                                            //
// Version     : 0.0.0                                                                                      //
// License     : GNU General Public License (GPL) version 3.0                                               //
// Copyright   : (C) 2023- Elijah Creed Fedele                                                              //
// -------------------------------------------------------------------------------------------------------- //
// This file is part of the Shasta microkernel project (https://github.com/ecfedele/shasta).                //
// Copyright (c) 2023- Elijah Creed Fedele.                                                                 //
//                                                                                                          //
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU       //
// General Public License as published by the Free Software Foundation, version 3.                          //
//                                                                                                          //
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even   //
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public  //
// License for more details.                                                                                //
//                                                                                                          //
// You should have received a copy of the GNU General Public License along with this program. If not, see   //
//     <http://www.gnu.org/licenses/>.                                                                      //
// -------------------------------------------------------------------------------------------------------- //

#ifndef UEFI_HARNESS_H_INCLUDED
#define UEFI_HARNESS_H_INCLUDED

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define EFI_SUCCESS             0x00000000
#define EFI_LOAD_ERROR          0x80000001
#define EFI_INVALID_PARAMETER   0x80000002
#define EFI_UNSUPPORTED         0x80000003
#define EFI_BAD_BUFFER_SIZE     0x80000004
#define EFI_BUFFER_TOO_SMALL    0x80000005
#define EFI_NOT_READY           0x80000006
#define EFI_DEVICE_ERROR        0x80000007
#define EFI_WRITE_PROTECTED     0x80000008
#define EFI_OUT_OF_RESOURCES    0x80000009
#define EFI_VOLUME_CORRUPTED    0x8000000A
#define EFI_VOLUME_FULL         0x8000000B
#define EFI_NO_MEDIA            0x8000000C
#define EFI_MEDIA_CHANGED       0x8000000D
#define EFI_NOT_FOUND           0x8000000E
#define EFI_ACCESS_DENIED       0x8000000F
#define EFI_NO_RESPONSE         0x80000010
#define EFI_NO_MAPPING          0x80000011
#define EFI_TIMEOUT             0x80000012
#define EFI_NOT_STARTED         0x80000013

#define EfiLoaderData           0x00000001

typedef uint32_t EFI_STATUS;
typedef uint32_t EFI_MEMORY_TYPE;

bool       EFI_ERROR   (EFI_STATUS Status);
EFI_STATUS AllocatePool(EFI_MEMORY_TYPE EfiType, uint32_t BufferSize, void **Buffer);
EFI_STATUS FreePool    (void *Buffer);

#endif // UEFI_HARNESS_H_INCLUDED
