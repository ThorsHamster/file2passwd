#!/bin/bash

set -euo pipefail

find **/* -iname *.hpp -o -iname *.cpp | xargs clang-format -i