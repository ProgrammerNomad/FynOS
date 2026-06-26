# ADR 0007: Serial debug first

## Problem

When the kernel crashes, QEMU may exit or reboot with no VGA output. Normal app debugging tools do not exist in bare metal.

## Options

- VGA only
- COM1 serial to host stdio
- GDB stub only

## Decision

Add COM1 (`0x3F8`) serial driver and `make run-debug` with `-serial stdio` before adding more kernel features.

## Why

Serial logs survive VGA failures and show `BOOT n` stage markers to pinpoint init failures. Standard practice in OS development.
