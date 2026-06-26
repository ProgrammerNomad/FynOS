# ADR 0006: Identity-map first 4 MB

## Problem

Enabling paging can break a kernel that assumes physical addresses equal virtual addresses.

## Options

- Higher-half kernel
- Identity map low memory only
- Full 4 GB identity map

## Decision

Identity-map the first 4 MB with one page directory entry and one page table.

## Why

Minimal page tables; keeps kernel at 0x1000, VGA at 0xB8000, and allocator pool working. Page faults call `panic()`.
