# ADR 0001: Use a C kernel

## Problem

FynOS needs a kernel language that balances learning, maintainability, and growth toward a full OS.

## Options

- Pure assembly kernel
- C kernel with ASM stubs
- C++ kernel

## Decision

C kernel only; assembly for bootloaders and arch entry/ISR stubs.

## Why

Matches the constitution, keeps the codebase readable as it grows, and is the standard OSDev path for hobby kernels.
