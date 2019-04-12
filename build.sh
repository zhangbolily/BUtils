#!/bin/bash

COVERAGE_FILE=coverage.info
REPORT_FOLDER=coverage_report

set -euo pipefail

mkdir -p build && cd build

# Configure
cmake -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug ..
# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . --config Debug -- -j $(nproc)
# Test
ctest -j $(nproc) --output-on-failure

# Generate test coverage report
lcov --rc lcov_branch_coverage=1 -c -d ./ -o ${COVERAGE_FILE}_tmp
lcov --rc lcov_branch_coverage=1  -e ${COVERAGE_FILE}_tmp "*src*" -o ${COVERAGE_FILE}
genhtml --rc genhtml_branch_coverage=1 ${COVERAGE_FILE} -o ${REPORT_FOLDER}
