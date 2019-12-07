#!/bin/bash

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake ../
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j $(nproc)
