#!/bin/bash
# FynOS clean script - thin wrapper around make clean
set -e
cd "$(dirname "$0")/.."
make clean
