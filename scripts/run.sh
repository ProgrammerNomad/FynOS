#!/bin/bash
# FynOS run script - thin wrapper around make run
set -e
cd "$(dirname "$0")/.."
make run
