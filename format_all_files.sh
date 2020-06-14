#!/bin/bash

set -euo pipefail

find . \( -name '*.hpp' -o -name '*.cpp' \) -exec clang-format -i {} +