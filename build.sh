#!/bin/bash

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake -DCMAKE_INSTALL_PREFIX=../_install -DGOOGLE_TESTS=OFF -DCODE_COVERAGE=OFF -DBUILD_DOC=ON -DBUILD_PYTHON=ON ..
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . -j "$(nproc)" --target install

# run python tests
cd ../_install/bin || exit
python3 system_test.py