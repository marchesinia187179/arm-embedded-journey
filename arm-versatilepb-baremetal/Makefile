# --- Compiler and Toolchain variables ---
CC		= arm-none-eabi-gcc
AS		= arm-none-eabi-gcc
LD		= arm-none-eabi-ld
OBJCOPY	= arm-none-eabi-objcopy

# --- CPU params ---
CPU_FLAGS	= -mcpu=arm926ej-s -g

# --- Folder paths ---
SRC_DIR		= src
LINK_DIR	= linker
BUILD_DIR	= build

# --- Compilation and Linker Flag ---
CFLAGS	= $(CPU_FLAGS) -Wall -ffreestanding -Iinclude
ASFLAGS	= $(CPU_FLAGS)
LDFLAGS	= -T $(LINK_DIR)/linker.ld

# --- Project file ---
OBJS	= $(BUILD_DIR)/startup.o $(BUILD_DIR)/main.o
TARGET	= $(BUILD_DIR)/my_project.elf

# --- Desault ---
all: $(BUILD_DIR) $(TARGET)

# Create the build folder if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linker: joins objects in the .elf executable
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

# Compiling the Assembly file
$(BUILD_DIR)/startup.o: $(SRC_DIR)/startup.s
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Utility ---
clean:
	rm -rf $(BUILD_DIR)

run: all
	qemu-system-arm -M versatilepb -m 128M -kernel $(TARGET) -nographic -serial mon:stdio

.PHONY: all clean run