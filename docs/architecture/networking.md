# Networking Architecture

> Status: **Planned (v2.x)**

## Overview

FynOS networking will provide IPv4 connectivity with a TCP/IP stack suitable for sockets-based applications.

## Planned Stack

```
Applications (apps/)
    -> syscalls
Socket API (kernel/net/socket.c)
    ->
TCP (kernel/net/tcp.c)
    ->
IPv4 (kernel/net/ipv4.c)
    ->
Ethernet driver (kernel/drivers/ethernet.c)
    ->
NIC hardware
```

## Milestone M8 Deliverables

- Ethernet driver (e.g. RTL8139 or E1000 for QEMU)
- ARP, ICMP, IPv4
- TCP and UDP
- Berkeley sockets API via syscalls

## Rules

- Network stack never draws graphics
- All network access from userspace via syscalls
- Drivers handle hardware; net stack handles protocols

## Dependencies

- PCI enumeration for NIC discovery
- Memory allocator for packet buffers
- Scheduler for async I/O (future)

## References

- [OSDev Wiki - Networking](https://wiki.osdev.org/Network)
