// -------------------------------------------------------------------------------------------------------- //
// Title       : Header File, UEFI Utility Functions                                                        //
// Filename    : uefiutil.h                                                                                 //
// Description : Provides a collection of functions primarily intended to serve as a replacement for some   //
//               GNU-EFI utility functions.                                                                 //
//                                                                                                          //
// Project     : Shasta Microkernel                                                                         //
// Main Author : Elijah Creed Fedele <ecfedele@outlook.com>                                                 //
// Created     : August 29, 2023                                                                            //
// Modified    : August 29, 2023                                                                            //
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
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef UEFI_FUNCTIONS_H
#define UEFI_FUNCTIONS_H

void        InitializeLib   (EFI_HANDLE, EFI_SYSTEM_TABLE *);
EFI_STATUS  AllocatePool    (EFI_MEMORY_TYPE, UINTN, VOID **);
EFI_STATUS  FreePool        (VOID *);
EFI_STATUS  Print           (const char *, ...);

#endif /* UEFI_FUNCTIONS_H */