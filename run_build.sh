#!/bin/sh
set -e

# Default settings
CLEAN=true
SRC_FILE=""
TEST_FILE=""

show_help() {
    echo "Usage: ./run_build.sh [OPTIONS]"
    echo "Options:"
    echo "  -s, --src PATH      Path to a specific C source file"
    echo "  -t, --test PATH     Path to a specific C++ test file"
    echo "  -b, --no-clean      Skip wiping the build directory before running"
    echo "  -h, --help          Show this help message"
    echo "  (If no files are specified, all files in src/ and tests/ are processed)"
}

# Parse command line flags
while [ "$#" -gt 0 ]; do
    case "$1" in
        -s|--src)
            SRC_FILE="$2"
            shift 2
            ;;
        -t|--test)
            TEST_FILE="$2"
            shift 2
            ;;
        -b|--no-clean)
            CLEAN=false
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# 1. Clean Step
if [ "$CLEAN" = true ]; then
    echo "Wiping old build directory..."
    rm -rf build/
fi

# 2. Configuration Step
# Construct the CMake command dynamically based on what was passed in
CMAKE_ARGS="-B build -S . -DCMAKE_BUILD_TYPE=Debug"

if [ -n "$SRC_FILE" ]; then
    CMAKE_ARGS="$CMAKE_ARGS -DSRC_FILE=$SRC_FILE"
fi

if [ -n "$TEST_FILE" ]; then
    CMAKE_ARGS="$CMAKE_ARGS -DTEST_FILE=$TEST_FILE"
fi

echo "Configuring project..."
cmake $CMAKE_ARGS

# 3. Compile Step
echo "Compiling..."
CPUS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)
cmake --build build -j"$CPUS"

# 4. Test Step
echo "Running tests..."
env GTEST_COLOR=1 ctest --test-dir build --output-on-failure
