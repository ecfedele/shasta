#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef EFI_APP
#include <efi.h>
#include <efilib.h>
#endif /* EFI_APP */

int main(int argc, char **argv) {
    printf("Hello, world!\n");
    return EXIT_SUCCESS;
}

#ifdef EFI_APP
EFI_STATUS EFIAPI efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    Print(L"Hello, world!\r\n");
    return EFI_SUCCESS;
}
#endif /* EFI_APP */
