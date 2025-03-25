#!/bin/bash

# Configuration
PI_USER="patch"
PI_HOST="10.0.0.48"  # Change this to your Pi's hostname or IP
PI_DIR="/home/patch/pipd"

# Sync changes to Raspberry Pi
echo "Syncing changes to Raspberry Pi..."
rsync -avz --exclude '.git' --exclude '*.o' --exclude '*.so' ./ ${PI_USER}@${PI_HOST}:${PI_DIR}/

# Compile on Raspberry Pi
echo "Compiling on Raspberry Pi..."
ssh ${PI_USER}@${PI_HOST} "cd ${PI_DIR} && \
    cd drivers && make && \
    cd ../extensions/pi2c_dac && make" 