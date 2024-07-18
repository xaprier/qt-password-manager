#!/bin/bash

# Determine the package manager
if command -v apt-get &> /dev/null; then
    INSTALL_CMD="sudo apt-get install -y"
    # Check Ubuntu version
    UBUNTU_VERSION=$(lsb_release -rs)
    if [[ $(echo "$UBUNTU_VERSION >= 21" | bc) -eq 1 ]]; then
        REQUIRED_PACKAGES="cmake build-essential qtbase5-dev qtbase5-dev-tools libssl-dev"
    else
        echo "You are using an old system and this program using newer packages. You should install Qt manually to your system."
        exit 1
    fi
elif command -v pacman &> /dev/null; then
    INSTALL_CMD="sudo pacman -S --noconfirm --needed"
    REQUIRED_PACKAGES="cmake gcc make qt5-base qt5-tools openssl"
else
    echo "No supported package manager found. Exiting script."
    exit 1
fi

echo "Installing $REQUIRED_PACKAGES"
$INSTALL_CMD $REQUIRED_PACKAGES

# CMake build and install
INSTALL_PREFIX="/usr"  # Set your project directory here
PROJECT_DIR=$(dirname "$(realpath "$0")")
BUILD_DIR="$PROJECT_DIR/build"

# Create build directory
rm -rf $BUILD_DIR # clean build
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Build the project
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
cmake --build .

# Install the project
sudo cmake --install .

echo "Project successfully built and installed."
