#!/bin/bash
# Build and run the Pokemon Battle Game
# Usage: ./build.sh [--run]

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

echo "=== Pokemon Battle Game Build Script ==="

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
echo "Configuring..."
cmake "$SCRIPT_DIR"

# Build
echo "Building..."
cmake --build .

echo ""
echo "Build successful! Executable: $BUILD_DIR/pokemon_battle"
echo ""

# Run if --run flag is provided
if [ "$1" = "--run" ]; then
    echo "=== Starting Battle ==="
    "$BUILD_DIR/pokemon_battle"
fi
