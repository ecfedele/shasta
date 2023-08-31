// -------------------------------------------------------------------------------------------------------- //
// Title       : UEFI Print Functions (Header), UEFI Print Utility Tests, UEFI Bootloader Test Suite        //
// Filename    : main.c                                                                                     //
// Description : Provides the header file for the Print function and some necessary auxiliary functions.    //
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

#ifndef UEFI_PRINT_H_INCLUDED
#define UEFI_PRINT_H_INCLUDED

#include "uefi_harness.h"

struct FormatSpecifier {
    int  location;
    char format;
    char modifier;
    int  width;
    int  precision;
};

size_t     StringLength        (const char *String);
size_t     CountCharOccurrences(const char *String, const char c);
size_t     ParseFormattedString(const char *Format, struct FormatSpecifier *fs, size_t NumAlloc);
EFI_STATUS Print               (const char *Format, ...);

#endif // UEFI_PRINT_H_INCLUDED
