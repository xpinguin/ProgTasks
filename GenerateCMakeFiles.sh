#!/bin/bash

OS=$(uname -a | cut -d ' ' -f 1)
if [ "${OS}" == "Linux" ]; then
  START=$(date +%s.%N)
fi

source cmake/GenerateCMakeFiles-lib.sh

GENERATE_VERBOSE="0"        # set to "1" - enable additional output during script processing on the screen
GENERATE_DEBUG="0"          # set to "1" - enable debug output during script processing on the screen
GENERATE_PACKAGE="0"        # set to "1" - create a tarball package of the project

#GENERATE_NOT_Cxx="1"                # set to "1" - do not use compiler -std=c++14 parameter (compiler parameter is enabled as default)
#GENERATE_NOT_PARALLEL="1"           # set to "1" - do not build with multiple processes (parralel build is enabled as default)
GENERATE_NOT_PCH="1"                # set to "1" - do not build with precompiled header support (precompiled header support is enabled as default)
if [ "${OS}" == "SunOS" ]; then
  GENERATE_NOT_REMOVE_UNUSED_CODE="1" # set to "1" - do not use compile and link parameters to remove unused code and functions (unused code and functions are removed as default)
fi

CMAKE_VERBOSE_OVERWRITE="0" # set to "0" - do not generate cmake verbose makefile output (even when the debug flag is set)
#CMAKE_VERBOSE_OVERWRITE="1" # set to "1" - always generate cmake verbose makefile output

UPP_SRC_BASE="upp"
UPP_SRC_DIR="${UPP_SRC_BASE}/uppsrc"

PROJECT_NAME="src/ProgTasks.upp"

PROJECT_EXTRA_COMPILE_FLAGS="-std=c++14"
PROJECT_EXTRA_LINK_FLAGS=""
PROJECT_FLAGS="-DflagGUI -DflagMT -DflagCLANG"

generate_main_cmake_file "${PROJECT_NAME}" "${PROJECT_FLAGS}"

if [ "${OS}" == "Linux" ]; then
  DUR=$(echo "$(date +%s.%N) - ${START}" | bc)
  echo "Execution time: $(date -d@0${DUR} -u +%H:%M:%S.%N)"
fi
