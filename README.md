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
