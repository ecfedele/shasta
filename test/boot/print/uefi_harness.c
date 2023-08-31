// -------------------------------------------------------------------------------------------------------- //
// Title       : UEFI Test Harnesses (Implementation), UEFI Print Utility Tests, UEFI Bootloader Test Suite //
// Filename    : main.c                                                                                     //
// Description : Provides the source file for some UEFI test functionality harnesses. Mimics several UEFI   //
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

#include "uefi_harness.h"

/// Provides a mimic of the `EFI_ERROR` function. Returns true if the `EFI_STATUS` code provided is an error;
/// returns false otherwise.
///
/// @param Status the `EFI_STATUS` to evaluate
/// @return       a `bool` indicating whether `Status` represented an error or not
bool EFI_ERROR(EFI_STATUS Status)
{
    return (Status != EFI_SUCCESS);
}

/// Provides a memory allocation of desired size and assigns a pointer to it. Internally, this function
/// translates to the C standard `malloc()`; some checking is done of the returned pointer, which means
/// that `AllocatePool` will not initialize or modify the pointer unless the operation is successful.
///
/// @param EfiType    the type of memory; this function only responds to EfiLoaderData
/// @param BufferSize the desired size of the memory allocation
/// @param Buffer     a pointer to a pointer which will be aimed at a successful allocation
/// @return           an `EFI_STATUS` value indicating the status of the operation
EFI_STATUS AllocatePool(EFI_MEMORY_TYPE EfiType, uint32_t BufferSize, void **Buffer)
{
    if (EfiType == EfiLoaderData) {
        void *InternalBuffer = malloc(BufferSize);
        if (InternalBuffer == NULL)
            return EFI_BUFFER_TOO_SMALL;
        else {
            *Buffer = InternalBuffer;
            return EFI_SUCCESS;
        }
    }
    else return EFI_INVALID_PARAMETER;
}

/// Releases a memory allocation provided earlier by `AllocatePool`. Internally, this simply redirects to
/// the C standard library function `free()`, and always returns `EFI_SUCCESS`.
///
/// @param  Buffer a pointer to the memory area to release
/// @return an `EFI_STATUS` value indicating the status of the operation
EFI_STATUS FreePool(void *Buffer)
{
    free(Buffer);
    return EFI_SUCCESS;
}
