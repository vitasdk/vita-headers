# vita-headers

This repository contains all Vita headers needed for development.

## Structure :
- `build.py` file used to build nid db. No longer recommended
- `check_size` build test project for check the validity of structures and enums
- `db` contains all the unique identifiers (NID) of the available functions.
- `include/` contains the header files themselves
  - `psp2` is for header files of user-exported libraries
  - `psp2kern` is for header files of kernel-exported libraries
  - `psp2common` is for shared defines on psp2 and psp2kern
- `docs` contains everything related to the generation of the documentation using doxygen.
- `vita.header_warn.cmake` definition to notify developers when there are breaking changes to backwards compatibility in vita-headers

## Documentation

The documentation is rebuilt every time a commit is pushed to master and it is hosted at the following address: http://vitasdk.github.io/vita-headers

## Special macros

|name|locate|description|
|-----|-----|-----|
|`PSP2_SDK_VERSION`|`psp2common/defs.h`|A macro defined with an integer indicating the SDK version.|
|`__USE_SCE_KERNEL_DOMAIN_TEXT_MEMCPY_IMPORT`|`psp2kern/kernel/cpu.h`|A macro to switch sceKernelDomainTextMemcpy to import. Since 3.63, sceKernelDomainTextMemcpy has been removed from the sysmem export, so this macro is forced to undef and becomes a static inline function if `PSP2_SDK_VERSION` is 0x3630000 or higher.|
