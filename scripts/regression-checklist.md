# FynOS v0.2 Regression Checklist

Run after `make clean && make && make run` in QEMU.

```text
[ ] make run-debug - serial BOOT lines visible in terminal
[ ] make run - QEMU stays open (-no-shutdown)
[ ] Prints welcome banner
[ ] Keyboard input works
[ ] help
[ ] version
[ ] about
[ ] clear
[ ] echo hello
[ ] mem (physical + heap free KB)
[ ] uptime (seconds increment over time)
[ ] Heap self-test passes at boot (no panic)
[ ] No reboot loop / unexpected kernel panic
```

v0.3 will add: `ls`, `cat`
v0.4 will add: `run hello`
