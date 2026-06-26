#!/bin/bash
# Create GitHub milestones and issues for FynOS (requires gh CLI)
set -e

if ! command -v gh &> /dev/null; then
    echo "Error: gh CLI not found. Install from https://cli.github.com/"
    echo "See docs/github-milestones.md for manual setup."
    exit 1
fi

create_milestone() {
    local title="$1"
    local desc="$2"
    gh api repos/:owner/:repo/milestones -f title="$title" -f description="$desc" 2>/dev/null || \
    gh api repos/$(gh repo view --json nameWithOwner -q .nameWithOwner)/milestones -f title="$title" -f description="$desc"
}

create_issue() {
    local title="$1"
    local milestone="$2"
    local body="$3"
    gh issue create --title "$title" --body "$body" --milestone "$milestone"
}

MILESTONES=(
    "M0: Bootloader|Multi-stage BIOS boot, protected mode, A20, kernel load"
    "M1: C Kernel|Unified C kernel build, modular layout"
    "M2: Memory|Physical bump allocator"
    "M3: Keyboard|PS/2 driver with IRQ handling"
    "M4: Shell|Interactive CLI with help, clear, mem, version"
    "M5: Filesystem|VFS layer and FAT32 driver"
    "M6: Graphics|Framebuffer and 2D primitives"
    "M7: GUI|Window manager and desktop (userspace)"
    "M8: Networking|IPv4 and TCP/IP stack"
)

for m in "${MILESTONES[@]}"; do
    title="${m%%|*}"
    desc="${m##*|}"
    echo "Creating milestone: $title"
    gh api repos/$(gh repo view --json nameWithOwner -q .nameWithOwner)/milestones \
        -f title="$title" -f description="$desc" || true
done

echo "Milestones created. See docs/github-milestones.md for issue definitions."
echo "Create a GitHub Project board manually and link these milestones."
