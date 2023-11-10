#!/bin/bash
clang++-14 badcalc.cpp -o badcalc -fprofile-instr-generate -fcoverage-mapping

for f in *.txt; do
        export LLVM_PROFILE_FILE="$f.prof"
        ./badcalc $f
done

llvm-profdata-14 merge -sparse *.prof -o merge.profdata
llvm-cov-14 show badcalc -instr-profile=merge.profdata >& profile.report