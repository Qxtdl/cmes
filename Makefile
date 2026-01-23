RISCV_PREFIX = ~/xpack-riscv-none-elf-gcc-15.2.0-1/bin/riscv-none-elf-

CC = $(RISCV_PREFIX)gcc
CFLAGS = -O3 -march=rv32i -mabi=ilp32 \
	-Wno-error=unused-parameter \
	-Wno-error=int-to-pointer-cast \
	-Wno-error=unused-function \
	-Werror -nostdlib -ffreestanding -fno-exceptions -fno-builtin \
	-mstrict-align \
	-g -Wall -Wextra \
	-fverbose-asm -T linker.ld -lgcc

ASFLAGS = -march=rv32i -mabi=ilp32

AS = $(RISCV_PREFIX)as
LD = $(RISCV_PREFIX)ld
OBJCOPY = $(RISCV_PREFIX)objcopy

BUILD = build
OUTPUT = cmes

CSRCS = $(shell find src -name '*.c')
ASRCS = $(shell find src -name '*.s')
COBJS = $(patsubst %.c,$(BUILD)/%.o,$(CSRCS))
AOBJS = $(patsubst %.s,$(BUILD)/%.o,$(ASRCS))
OBJS = $(AOBJS) $(COBJS)

all: clean $(OBJS) $(OUTPUT) dump run

force:

$(BUILD)/%.o : %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BUILD)/$(OUTPUT).elf
	$(OBJCOPY) -O binary $(BUILD)/$(OUTPUT).elf $(BUILD)/$(OUTPUT).bin

dump:
	$(RISCV_PREFIX)objdump -d -M no-aliases $(BUILD)/$(OUTPUT).elf >> $(BUILD)/dump.s
	$(RISCV_PREFIX)objdump -S -d -M no-aliases $(BUILD)/$(OUTPUT).elf >> $(BUILD)/verbose_dump.s
	$(GCC) -E $(CSRCS) -o $(BUILD)/preprocessed.c

run:
	python taurus_encoder.py build/$(OUTPUT).bin
	./cm2-riscv-emulator build/$(OUTPUT).bin disk_dump.bin

clean:
	rm -rf $(BUILD)
