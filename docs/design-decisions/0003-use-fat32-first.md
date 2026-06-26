# ADR 0003: FAT32 as first filesystem

## Problem

FynOS needs to load files from disk in v0.3+.

## Options

- FAT32 read-only
- ext2
- Custom FynFS immediately

## Decision

FAT32 read-only for v0.3; native FynFS later.

## Why

Easy to create test images on the host, widely documented, sufficient for loading apps.
