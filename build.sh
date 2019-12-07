#!/bin/bash

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake -DCODE_COVERAGE=ON -DBUILD_DOC=OFF ..
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j $(nproc)
# Coverage
make coverage
cd ..
