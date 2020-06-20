#!/bin/bash

set -euo pipefail

find . \( -name '*.hpp' -o -name '*.cpp' \) -exec clang-format -i {} +

not_correct_list=`git status | grep "modified"`

if [[ -z $not_correct_list ]]; then
  echo "No styleguide violation with clang-format found."
  exit 0;
else
  echo "Please check for following files:";
  for f in $notcorrectlist; do
      echo $f
      git diff $f
  done
  exit 1;
fi
