#!/bin/bash

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake -DGOOGLE_TESTS=ON -DCODE_COVERAGE=ON ..
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j "$(nproc)"
