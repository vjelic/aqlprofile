HSA extension AMD AQL profile library.
Provides AQL packets helper methods for perfcounters (PMC) and SQ threadtraces (SQTT).

Library supports GFX8/GFX9 APIs.
The library source tree:
 - doc  - Documantation, the API specification and the presentation
 - <hsa-runtime>/inc/hsa_ven_amd_aqlprofile.h - AMD AQL profile library public API
 - src  - AMD AQL profile library sources
   - core - AQL API sources
   - pm4 - cmd/pmc/sqtt builders
 - test - library test suite
   - ctrl - Test controll
   - util - Test utils
   - simple_convolution - Simple convolution test kernel

To build the library:

$ export CMAKE_PREFIX_PATH="<path to hsa-runtime includes>;<path to hsa-runtime library>"
$ export CMAKE_BUILD_TYPE=<debug|release> # release by default

$ cd .../hsa-amd-aqlprofile
$ mkdir build
$ cd build
$ cmake ..
$ make

To run the test:

$ cd .../hsa-amd-aqlprofile/build
$ export LD_LIBRARY_PATH=$PWD
$ ./test/ctrl

To enable PMC profiling:

$ export ROCR_ENABLE_PMC=1

To enable SQTT profiling:

$ export ROCR_ENABLE_SQTT=1

To enabled error messages logging to '/tmp/aql_profile_log.txt':

$ export HSA_VEN_AMD_AQLPROFILE_LOG=1

Or to use the script:

$ ./run.sh
