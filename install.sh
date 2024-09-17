#!/bin/bash

# Install SDL2, SDL2_image, and SDL2_ttf on Ubuntu

echo "Updating package lists..."
sudo apt update

echo "Installing SDL2..."
sudo apt install -y libsdl2-dev

echo "Installing SDL2_image..."
sudo apt install -y libsdl2-image-dev

echo "Installing SDL2_ttf..."
sudo apt install -y libsdl2-ttf-dev

echo "Installing SDL2_mixer..."
sudo apt install -y libsdl2-mixer-dev

echo "SDL2, SDL2_image, and SDL2_ttf installation completed."
