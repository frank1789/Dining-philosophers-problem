

mkdir build
cd build
lcov --directory . --zerocounters
cmake -D CODE_COVERAGE=ON ..
cmake --build . --config Debug
./Dining-philosophers

# Create lcov report capturing coverage info
lcov --directory . --capture --output-file coverage.info
# filter out system and extra files.
# To also not include test code in coverage add them with full path to the patterns: '*/tests/*'
lcov --remove coverage.info '/usr/*' "${HOME}"'/.cache/*' \
    --output-file coverage-filtered.info
# output coverage data for debugging (optional)
lcov --list coverage-filtered.info
genhtml coverage.info --output-directory out-coverage  --show-details
