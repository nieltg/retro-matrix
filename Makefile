# Makefile by @nieltg

# Places

OUT_DIR := bin
OBJ_DIR := $(OUT_DIR)/obj

SRC_DIR := src
SRC_CTRL_DIR := $(SRC_DIR)/_ctrl

FLOPPY_IMG := $(OUT_DIR)/floppy.img
FLOPPY_IMG_GZ := $(FLOPPY_IMG).gz

BOOTLD_SRC := $(SRC_CTRL_DIR)/loader.asm

BOOTLD_OBJ := \
	$(addprefix $(OBJ_DIR)/, \
		$(patsubst %.asm,%.o,$(BOOTLD_SRC)))

MAIN_SRC := $(SRC_CTRL_DIR)/main.s

MAIN_OBJ := \
	$(addprefix $(OBJ_DIR)/, \
		$(patsubst %.s,%.o,$(MAIN_SRC)))

KERNEL_BIN := $(OUT_DIR)/kernel.bin

SRC_DIRS := $(shell find $(SRC_DIR) -type d)
OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS))

SRC_OBJS := \
	$(shell find $(SRC_DIR) -name '*.c' -type f) \
	$(shell find $(SRC_DIR) -name '*.s' -type f)

SRC_DEFS := \
	$(shell find $(SRC_DIR) -name '*.h' -type f)

OBJ_OBJS := \
	$(addprefix $(OBJ_DIR)/, \
		$(patsubst %.c,%.o, \
		$(patsubst %.s,%.o, \
			$(filter-out $(SRC_DIR)/manual/%,$(SRC_OBJS)))))

# Tools

LD := ld86 -d -M
AS := as86 -u
CC := bcc -ansi -c -I$(SRC_DIR)
NASM := nasm

# Targets

.PHONY: all clean

all: $(FLOPPY_IMG_GZ)

$(FLOPPY_IMG_GZ): $(FLOPPY_IMG)
	@echo " gzip: $@"
	@gzip -9 -c $< > $@

$(FLOPPY_IMG): $(BOOTLD_OBJ) $(KERNEL_BIN)
	@echo " dd: floppy.img <- /dev/zero"
	@dd if=/dev/zero of=$@ bs=512 count=2880 > /dev/null 2>&1
	@echo " dd: floppy.img <- $(BOOTLD_OBJ)"
	@dd if=$(BOOTLD_OBJ) of=$@ bs=512 conv=notrunc seek=0 > /dev/null 2>&1
	@echo " dd: floppy.img <- $(KERNEL_BIN)"
	@dd if=$(KERNEL_BIN) of=$@ bs=512 conv=notrunc seek=3 > /dev/null 2>&1

$(KERNEL_BIN): $(MAIN_OBJ) $(OBJ_OBJS) | $(OUT_DIR)
	@echo " link: $@"
	@$(LD) -o $@ $^

$(OUT_DIR) $(OBJ_DIRS):
	@echo " mkdir: $@"
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.asm | $(OBJ_DIRS)
	@echo " nasm: $@"
	@$(NASM) -o $@ $<

$(OBJ_DIR)/%.o : %.s | $(OBJ_DIRS)
	@echo " as: $@"
	@$(AS) -o $@ $<

$(OBJ_DIR)/%.o : %.c $(SRC_DEFS) | $(OBJ_DIRS)
	@echo " cc: $@"
	@$(CC) -o $@ $<

clean:
	@echo " cleanup: $(OUT_DIR)"
	@rm -rf $(OUT_DIR)
