# ADR 0005: Simple heap free-list (v0.2)

## Problem

The bump allocator cannot free memory; the kernel needs `kmalloc`/`kfree` for v0.2.

## Options

- Buddy allocator
- Slab allocator
- Simple singly-linked free-list

## Decision

Singly-linked free-list on top of `phys_alloc` blocks. No coalescing, no `realloc`.

## Why

Easy to debug; good enough for v0.2. Can redesign in a later release if needed.
