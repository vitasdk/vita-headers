# vita-headers

This repository contains all Vita headers needed for development.

## Structure :
- `db` contains all the unique identifiers (NID) of the available functions.
- `include/` contains the header files themselves
  - `psp2` is for header files of user-exported libraries
  - `psp2kern` is for header files of kernel-exported libraries
- `docs` contains everything related to the generation of the documentation using doxygen.

## Documentation

The documentation is rebuilt every time a commit is pushed to master and it is hosted at the following address: http://vitasdk.github.io/vita-headers
