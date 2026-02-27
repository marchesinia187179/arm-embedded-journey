# ARM VersatilePB Bare-Metal "Hello World"

This repository contains a professional-grade starting point for **ARM Bare-Metal development**. It demonstrates how to boot an ARM926EJ-S CPU (emulated via QEMU), initialize the stack, and communicate via a PL011 UART peripheral without any underlying Operating System.

## 📂 Project Structure

The project follows a standard embedded systems directory layout:

* **`src/`**: Contains the source files.
    * `startup.s`: Assembly bootloader responsible for CPU initialization.
    * `main.c`: The main logic written in C.
* **`linker/`**: Contains the Linker Script.
    * `linker.ld`: Defines the memory map (Flash and RAM regions).
* **`build/`**: (Auto-generated) Contains compiled object files and the final `.elf` executable.
* **`Makefile`**: Automates the entire build and emulation process.

---

## ⚙️ Technical Deep Dive

### 1. The Boot Process (`startup.s`)
Since there is no OS, the CPU starts executing at a specific memory address defined in the vector table.
* **Vector Table**: Placed at the very beginning of the binary.
* **Stack Pointer (SP)**: The assembly code initializes the `sp` register to point to the top of a reserved 4KB memory area.
* **Branch to Main**: Once the environment is set, it performs a Branch with Link (`bl`) to the C `main()` function.

### 2. Memory Mapping (`linker.ld`)
The linker script organizes how code and data are placed in the physical memory of the **VersatilePB** board:
* **FLASH (0x00010000)**: Where the persistent code resides.
* **RAM (0x00030000)**: Where variables and the stack are managed during execution.
* **Entry Point**: Explicitly set to `_Reset`.

### 3. Peripheral Communication (`main.c`)
Communication is handled via **Memory-Mapped I/O (MMIO)**. 
* The UART0 Data Register is located at address `0x101f1000`.
* By casting this address to a `volatile unsigned int *`, the C code can send characters to the serial port by simply writing to that memory location.

---

## 🛠️ Requirements

To build and run this project, you need:
1.  **GNU Arm Embedded Toolchain**: `arm-none-eabi-gcc`, `ld`, etc.
2.  **QEMU**: Specifically `qemu-system-arm`.
3.  **Make**: To handle the build automation.

On Ubuntu/Debian, you can install these with:
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi qemu-system-arm make
```

---

## 🚀 How to Run

1. Compile the project
Navigate to the root folder and run:

```bash
make
```
This will create the `build/` folder and generate `my_project.elf`.

2. Launch the Emulation
Run the following command to start QEMU in non-graphical mode:

```bash
make run
```
You should see the output:
`Hello, World!`

3. Exit QEMU
To stop the emulation and return to your terminal:
- Press `Ctrl + A` then `X`.

---

## 🔍 Debugging
If you need to inspect the CPU state (registers):
- Inside QEMU, press `Ctrl + A` then `C` to enter the monitor.
- Type `info registers`.
- Type `Ctrl + A` then `C` again to return to the serial output.
