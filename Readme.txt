HSA extension AMD AQL profile library.
Provides AQL packets helper methods for perfcounters (PMC) and SQ threadtraces (SQTT).

Library supports GFX8/GFX9 APIs.
The library source tree:
 - doc  - Documantation, the API specification and the presentation
 - <hsa-runtime>/inc/hsa_ven_amd_aqlprofile.h - AMD AQL profile library public API
 - src  - AMD AQL profile library sources
   - core - AQL API sources
   - pm4 - cmd/pmc/sqtt pm4 builders
   - def - GFXIP definition headers
 - test - library test suite
   - ctrl - Test controll
   - util - Test utils
   - simple_convolution - Simple convolution test kernel

Build environment:

$ export CMAKE_PREFIX_PATH="<path to hsa-runtime includes>;<path to hsa-runtime library>"
$ export CMAKE_BUILD_TYPE=<debug|release> # release by default
$ export CMAKE_DEBUG_TRACE=1 # 1 to enable debug tracing

To build with the current installed ROCM:

$ cd .../hsa-amd-aqlprofile
$ mkdir build
$ cd build
$ cmake -DCMAKE_PREFIX_PATH=/opt/rocm ..
$ make

To run the test:

$ cd .../hsa-amd-aqlprofile/build
$ export LD_LIBRARY_PATH=$PWD
$ run.sh

To enabled error messages logging to '/tmp/aql_profile_log.txt':

$ export HSA_VEN_AMD_AQLPROFILE_LOG=1

To enable verbose tracing:

$ export AQLPROFILE_TRACE=1
