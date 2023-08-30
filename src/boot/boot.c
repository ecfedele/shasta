// -------------------------------------------------------------------------------------------------------- //
// Title       : Main Entry Point, 64-bit UEFI Bootloader                                                   //
// Filename    : boot.c                                                                                     //
// Description : Provides the main entry point and program body for the 64-bit UEFI bootloader.             //
//                                                                                                          //
// Project     : Shasta Microkernel                                                                         //
// Main Author : Elijah Creed Fedele <ecfedele@outlook.com>                                                 //
// Created     : August 27, 2023                                                                            //
// Modified    : August 27, 2023                                                                            //
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

#include <efi.h>
#include <efilib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include "uefiutil.h"

EFI_STATUS EFIAPI efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
    EFI_SYSTEM_TABLE *ST = SystemTable;
    InitializeLib(ImageHandle, SystemTable);
    Print(L"Hello, world!\r\n");

    Status = ST->ConIn->Reset(ST->ConIn, FALSE);
    if (EFI_ERROR(Status))
        return Status;
    while ((Status = ST->ConIn->ReadKeyStroke(ST->ConIn, &Key)) == EFI_NOT_READY);

    return Status;
}
