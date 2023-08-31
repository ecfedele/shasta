// -------------------------------------------------------------------------------------------------------- //
// Title       : Main File, UEFI Print Utility Tests, UEFI Bootloader Test Suite                            //
// Filename    : main.c                                                                                     //
// Description : Provides the main program file for the test of the formatted-print (Print) functionality   //
//               incorporated into Shasta's UEFI bootloader.                                                //
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

#include <stdio.h>
#include <stdlib.h>

#include "uefi_harness.h"
#include "uefi_print.h"

int main()
{
    const char *String = "Some basic format specifiers: %u, %3d, %.2f, %lu, %10.3lf";

    size_t occurrences = CountCharOccurrences(String, '%');
    struct FormatSpecifier *fs = malloc(2 * occurrences * sizeof(struct FormatSpecifier));
    if (fs == NULL) {
        return EXIT_FAILURE;
    }

    size_t count = ParseFormattedString(String, fs, 2 * occurrences);
    printf("Counted %d format specifier(s) in provided string.\n", count);
    printf("Enumerating:\n");
    for (int i = 0; i < count; i++) {
        printf("    Specifier #%d:\n", i);
        printf("        Location  = %d\n", fs[i].location);
        printf("        Format    = %c\n", fs[i].format);
        printf("        Modifier  = %c\n", fs[i].modifier);
        printf("        Width     = %d\n", fs[i].width);
        printf("        Precision = %d\n", fs[i].precision);
    }

    size_t bytes = GetSpecifierLength(fs, count);
    printf("These specifiers consume %d bytes of the string.\n", bytes);

    return EXIT_SUCCESS;
}
