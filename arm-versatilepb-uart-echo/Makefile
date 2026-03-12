# Variables
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CFLAGS = -mcpu=arm926ej-s -g -I./include
LDFLAGS = -T linker/linker.ld

# Sources and Objects
SRCS = src/main.c src/uart.c
OBJS = $(SRCS:.c=.o)
TARGET = build/uart_echo.elf

# Rules
all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJS) src/startup.o
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

src/startup.o: src/startup.s
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	qemu-system-arm -M versatilepb -nographic -serial mon:stdio -kernel $(TARGET)

clean:
	rm -f $(OBJS) src/startup.o $(TARGET)
