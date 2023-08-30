// -------------------------------------------------------------------------------------------------------- //
// Title       : Implementation File, UEFI Utility Functions                                                //
// Filename    : uefiutil.c                                                                                 //
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

#include "uefiutil.h"

static EFI_HANDLE        IH;
static EFI_SYSTEM_TABLE *ST;

struct FormatSpecifier {
    int  location;
    char format;
    char modifier;
    int  width;
    int  precision;
};

size_t  StringLength        (const char *);
size_t  ParseFormattedString(const char *, struct FormatSpecifier *, size_t);

/// @brief InitializeLib stores local copies of the EFI image and system table handles.
/// @param ImageHandle the `EFI_HANDLE` passed to `efi_main`
/// @param SystemTable the `EFI_SYSTEM_TABLE` passed to `efi_main`
void InitializeLib(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    IH = ImageHandle;
    ST = SystemTable;
}

/// @brief Requests a memory allocation of specified type and size to be mapped to the supplied pointer. This 
///        version is modified from its UEFI original form to conform more closely to C native types and avoid 
///        the double indirection (i.e. `VOID **`) of the underlying UEFI call.
/// @param EfiType    the memory type to be allocated
/// @param BufferSize the size of the buffer allocation desired
/// @param Buffer     a supplied pointer to be pointed at the allocated memory area
/// @return           an `EFI_STATUS` indicating the result of the call to `AllocatePool`
EFI_STATUS AllocatePool(EFI_MEMORY_TYPE EfiType, uint64_t BufferSize, void *Buffer) {
    return ST->BootServices->AllocatePool(EfiType, BufferSize, &Buffer);
}

/// @brief Frees (releases) a memory allocation made via `AllocatePool`.
/// @param Buffer a pointer to the allocated buffer
/// @return       an `EFI_STATUS` indicating the result of the call to `AllocatePool`
EFI_STATUS FreePool(void *Buffer) {
    return ST->BootServices->AllocatePool(Buffer);
}

/// @brief Provides a print function similar to `printf()` in the C standard library. Processes the most 
///        useful subset of the available format specifiers and formatting modes. Note that this function will 
///        only handle up to 256 characters by design due to internal fixed allocation strategies.
/// @param fmt The formatted string to substitute and print
/// @param ... A vararg list to inject into `fmt` in accordance with the format specifiers
/// @return    an `EFI_STATUS` indicating the result of the call to `Print`
EFI_STATUS Print(const char *fmt, ...) {
    // if the string is greater than 256 characters, error out - the fixed-length buffers
    // allocated below will not handle it
    if (StringLength(str) > 256)
        return EFI_BUFFER_TOO_SMALL;
}

/// @brief Private helper function for `Print`. Returns string length. Assumes regular `char` code points, 
///        rather than the 16-bit wide chars of UEFI printing implementations.
/// @param str the string to measure
/// @return    the length of the supplied string
size_t StringLength(const char *str) {
    size_t i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

size_t ParseFormattedString(const char *fmt, struct FormatSpecifier *fs, size_t numalloc) {
    int location = 0;
    size_t specIndex = 0;
    bool isSpecifier = false;

    // Initialize all FormatSpecifier structs to zero.
    for (int i = 0; i < numalloc; i++)
        fs[i] = {0};

    // Iterate over the format string.
    while (*fmt) {
        
        // If the current character is a '%' and an open specifier has not yet been detected, set the 
        // isSpecifier flag to true and save the location of this point in the current FormatSpecifier struct. 
        // Increment format pointer, location, and continue.
        if (*fmt == '%' && !isSpecifier) {
            isSpecifier = true;
            fs[specIndex].location = location;
            fmt++;
            location++;
            continue;
        }
        else if (isSpecifier) {

            // If the next character is a '%', it is escaped - roll back the saved location
            if (*fmt == '%') {
                isSpecifier = false;
                fs[specIndex].location = 0;
            }

            // If we haven't encountered a width yet, save the format character directly. As the format 
            // character must necessarily be the last character in the format specifier sequence, this ends 
            // the current specifier. Set isSpecifier to false; increment specIndex.
            else if (*fmt == 'd' || *fmt == 'i' || *fmt == 'u' || *fmt == 'o' || *fmt == 'x' || *fmt == 'X' || 
                     *fmt == 's' || *fmt == 'e' || *fmt == 'E' || *fmt == 'f') {
                fs[specIndex].format = *fmt;
                isSpecifier = false;
                specIndex++;
            }

            // Handle any modifiers, widths, or precisions which may be specified.
            else {
                switch (*fmt) {
                    case 'b':   // byte       (  8-bit)
                    case 'h':   // halfword   ( 16-bit)
                    case 'w':   // word       ( 32-bit)
                    case 'd':   // doubleword ( 64-bit)
                    case 'q':   // quadword   (128-bit)
                        fs[specIndex].modifier = *fmt;
                        break;
                    case '0' ... '9':
                    case '.':
                }
            }
        }

        fmt++;
    }
}