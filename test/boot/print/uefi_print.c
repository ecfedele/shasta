// -------------------------------------------------------------------------------------------------------- //
// Title       : UEFI Print Functions (Source), UEFI Print Utility Tests, UEFI Bootloader Test Suite        //
// Filename    : main.c                                                                                     //
// Description : Provides the source file for the Print function and some necessary auxiliary functions.    //
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

#include "uefi_print.h"

/// Helper function (equivalent to C standard `strlen()`) which returns the length of the string provided.
///
/// @param String the string whose length is to be evaluated
/// @return       the length of the provided string as a `size_t` integer
size_t StringLength(const char *String)
{
    size_t length = 0;
    while (String[length] != '\0') {
        length++;
    }
    return length;
}

/// Counts the number of occurrences of a character `c` in the provided string `String`.
///
/// @param String the string to evaluate
/// @param c      the character to scan for
/// @returns      the number of occurrences of `c` in `String` as a `size_t` integer
size_t CountCharOccurrences(const char *String, const char c)
{
    size_t occurrences = 0;
    for (int i = 0; i < StringLength(String); i++) {
        if (String[i] == c) {
            occurrences++;
        }
    }
    return occurrences;
}

/// Parses the formatted string provided and returns an array of `FormatSpecifier` structures, pointed to by
/// the provided pointer `fs`, which indicate the format specifiers encoded in the formatted string. This
/// function supports a subset of the most commonly-encountered format specifiers and ones which are thought
/// to be most useful for operating system development.
///
/// @param Format   the string to evaluate
/// @param fs       a pointer to an allocated memory area of `FormatSpecifier` structures
/// @param NumAlloc the number of allocated `FormatSpecifier` structures in the memory area pointed to by `fs`
/// @return         the number of valid format specifiers as a `size_t` integer
size_t ParseFormattedString(const char *Format, struct FormatSpecifier *fs, size_t NumAlloc)
{
    int location = 0;
    size_t specIndex = 0;
    bool isSpecifier = false, isPrecision = false;

    // Initialize all FormatSpecifier structs to zero.
    for (int i = 0; i < NumAlloc; i++)
        fs[i] = (struct FormatSpecifier){0};

    // Iterate over the format string.
    while (*Format) {

        // If the current character is a '%' and an open specifier has not yet been detected, set the
        // isSpecifier flag to true and save the location of this point in the current FormatSpecifier struct.
        // Increment format pointer, location, and continue.
        if (*Format == '%' && !isSpecifier) {
            isSpecifier = true;
            fs[specIndex].location = location;
            Format++;
            location++;
            continue;
        }
        else if (isSpecifier) {

            // If the next character is a '%', it is escaped - roll back the saved location
            if (*Format == '%') {
                isSpecifier = false;
                fs[specIndex].location = 0;
            }

            // If we haven't encountered a width yet, save the format character directly. As the format
            // character must necessarily be the last character in the format specifier sequence, this ends
            // the current specifier. Set isSpecifier to false; increment specIndex.
            else if (*Format == 'd' || *Format == 'i' || *Format == 'u' || *Format == 'o' || *Format == 'x' ||
                     *Format == 'X' || *Format == 's' || *Format == 'e' || *Format == 'E' || *Format == 'f') {
                fs[specIndex].format = *Format;
                isSpecifier = false;
                isPrecision = false;
                specIndex++;
            }

            // Handle any modifiers, widths, or precisions which may be specified.
            else {
                switch (*Format) {
                    case 'b':   // byte       (  8-bit)
                    case 'h':   // halfword   ( 16-bit)
                    case 'w':   // word       ( 32-bit)
                    case 'l':   // doubleword ( 64-bit)
                    case 'q':   // quadword   (128-bit)
                        fs[specIndex].modifier = *Format;
                        break;
                    case '0' ... '9':
                        if (!isPrecision) {
                            fs[specIndex].width = (fs[specIndex].width * 10) + (*Format - '0');
                        }
                        else {
                                fs[specIndex].precision = (fs[specIndex].precision * 10) + (*Format - '0');
                        }
                        break;
                    case '.':
                        isPrecision = true;
                        fs[specIndex].precision = 0;
                        break;
                }
            }
        }

        Format++;
        location++;
    }

    return specIndex;
}

EFI_STATUS Print(const char *Format, ...)
{
    return EFI_SUCCESS;
}
