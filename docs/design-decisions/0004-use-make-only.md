# ADR 0004: Makefile-only build on Linux/WSL

## Problem

Multiple build systems cause drift and confusion.

## Options

- Makefile + build.bat
- CMake
- Makefile only on Linux/WSL

## Decision

Single Makefile; WSL Ubuntu or native Linux only.

## Why

One canonical path; matches project rules and reduces maintenance.
