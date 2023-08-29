#include <efi.h>
#include <efilib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef EFI_FUNCTIONS_H
#define EFI_FUNCTIONS_H

void        InitializeLib   (EFI_HANDLE, EFI_SYSTEM_TABLE *);
EFI_STATUS  AllocatePool    (EFI_MEMORY_TYPE, UINTN, VOID **);
EFI_STATUS  FreePool        (VOID *);
EFI_STATUS  Print           (const char *, ...);

#endif /* EFI_FUNCTIONS_H */