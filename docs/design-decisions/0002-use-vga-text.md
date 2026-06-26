# ADR 0002: VGA text mode first

## Problem

FynOS needs early console output before graphics exist.

## Options

- VGA text (0xB8000)
- Framebuffer (VBE) immediately
- Serial only

## Decision

VGA text mode driver in the kernel for v0.1–v0.2.

## Why

Simple, well documented, works in QEMU without extra setup. Framebuffer deferred to v0.5.
