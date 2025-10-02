RISCV_PREFIX = riscv64-unknown-elf-
AS = $(RISCV_PREFIX)as
LD = $(RISCV_PREFIX)ld
GCC = $(RISCV_PREFIX)gcc
OBJCOPY = $(RISCV_PREFIX)objcopy

BUILD_DIR = build
CFLAGS = -march=rv32i -mabi=ilp32
CCFLAGS = -march=rv32i -mabi=ilp32 -nostdlib -ffreestanding -fno-exceptions -fno-builtin -mstrict-align -Wall -Wextra -g -fverbose-asm -T linker.ld
S_SOURCE = bootloader.s
C_SOURCE = c_src/main.c

all: bootloader cfile dump

dump:
	$(RISCV_PREFIX)objdump -d -M no-aliases $(BUILD_DIR)/cmes.elf >> $(BUILD_DIR)/dump.s
	$(RISCV_PREFIX)objdump -S -d -M no-aliases $(BUILD_DIR)/cmes.elf >> $(BUILD_DIR)/verbose_dump.s

cfile:
	$(GCC) $(CCFLAGS) -o $(BUILD_DIR)/cmes.elf $(BUILD_DIR)/bootloader.o $(C_SOURCE)
	$(OBJCOPY) -O binary $(BUILD_DIR)/cmes.elf $(BUILD_DIR)/cmes.bin

bootloader:
	$(AS) $(CFLAGS) -o $(BUILD_DIR)/bootloader.o $(S_SOURCE)

clean:
	rm -rf $(BUILD_DIR)/bootloader.o $(BUILD_DIR)/cmes.elf $(BUILD_DIR)/cmes.bin $(BUILD_DIR)/dump.s
