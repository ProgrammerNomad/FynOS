#include "cpu/idt.h"
#include "cpu/pic.h"
#include "drivers/keyboard.h"

#define IDT_ENTRIES 256
#define IRQ_BASE    0x20

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attr;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[IDT_ENTRIES];

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void isr32(void);
extern void isr33(void);
extern void isr34(void);
extern void isr35(void);
extern void isr36(void);
extern void isr37(void);
extern void isr38(void);
extern void isr39(void);
extern void isr40(void);
extern void isr41(void);
extern void isr42(void);
extern void isr43(void);
extern void isr44(void);
extern void isr45(void);
extern void isr46(void);
extern void isr47(void);

extern void isr_ignore(void);

static void (*isr_stubs[48])(void) = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7,
    isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31,
    isr32, isr33, isr34, isr35, isr36, isr37, isr38, isr39,
    isr40, isr41, isr42, isr43, isr44, isr45, isr46, isr47
};

static void idt_set_gate(uint8_t num, void (*handler)(void))
{
    uint32_t addr = (uint32_t)handler;

    idt[num].base_low  = (uint16_t)(addr & 0xFFFF);
    idt[num].base_high = (uint16_t)((addr >> 16) & 0xFFFF);
    idt[num].selector  = 0x08;
    idt[num].zero      = 0;
    idt[num].type_attr = 0x8E;
}

void idt_init(void)
{
    uint16_t i;
    struct idt_ptr idtp;

    for (i = 0; i < 48; i++) {
        idt_set_gate((uint8_t)i, isr_stubs[i]);
    }

    for (i = 48; i < IDT_ENTRIES; i++) {
        idt_set_gate((uint8_t)i, isr_ignore);
    }

    idtp.limit = (uint16_t)(sizeof(struct idt_entry) * IDT_ENTRIES - 1);
    idtp.base  = (uint32_t)&idt;

    __asm__ volatile("lidt %0" : : "m"(idtp));
}

void isr_handler(registers_t *regs)
{
    if (regs->int_no >= IRQ_BASE && regs->int_no < IRQ_BASE + 16) {
        uint8_t irq = (uint8_t)(regs->int_no - IRQ_BASE);

        if (irq == 1) {
            keyboard_irq_handler();
        }

        pic_send_eoi(irq);
    }
}
