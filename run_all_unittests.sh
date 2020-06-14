#!/bin/bash

set -euo pipefail

cd build || exit

make all_tests
