# ARM VersatilePB UART Echo & Polling (Modularized)

This project evolves the basic bare-metal "Hello World" by implementing a **modular driver architecture**. It demonstrates **bidirectional communication** and **Hardware Polling**, with a professional separation between the hardware-specific driver layer and the application logic.

## 📂 Project Structure

The project follows a clean, industry-standard embedded directory layout:

* **`src/`**: Contains the C source files and assembly.
    * `startup.s`: Bootloader that initializes the Stack Pointer (SP).
    * `main.c`: The core application logic.
    * `uart.c`: The hardware-specific driver implementation.
* **`include/`**: Contains header files.
    * `uart.h`: The driver interface (API) for the application.
* **`linker/`**: Contains the Linker Script (`linker.ld`).
* **`build/`**: (Auto-generated) Stores compiled objects and the `uart_echo.elf` binary.
* **`Makefile`**: Manages multi-file compilation and the emulation workflow.

---

## ⚙️ Technical Deep Dive

### 1. Driver Layering (Hardware Abstraction)
By separating `uart.c` from `main.c`, we isolate hardware-specific details (like the register address `0x101f1000`) from the application. The `main.c` now interacts only with the clean API defined in `uart.h`.

### 2. UART Control & Initialization
The `uart_init()` function now explicitly configures the **UART Control Register (UART0_CR)**:
* **UARTEN (Bit 0)**: Enables the UART peripheral.
* **TXE (Bit 8) & RXE (Bit 9)**: Explicitly enables transmission and reception paths.
This ensures a predictable hardware state before any data transfer begins.

### 3. Hardware Polling & Bitmasking
The CPU monitors the **Flag Register (UART0_FR)** to detect incoming data via the **RXFE (Receive FIFO Empty)** bit (Bit 4).
* **The Mask**: The operation `(1 << 4)` isolates the status bit.
* **The Logic**: The CPU performs an `AND` check, effectively "spinning" in place until the buffer status indicates data has arrived.

### 4. Stack Verification
By using local variables and function calls within a modular environment, this project validates that the **Stack Pointer** configured in `startup.s` correctly handles the call stack, ensuring that the driver calls and variable allocations do not cause system crashes.

---

## 🛠️ Requirements

To build and run this project, you need:
1.  **GNU Arm Embedded Toolchain**: `arm-none-eabi-gcc`, `ld`, etc.
2.  **QEMU**: Specifically `qemu-system-arm`.
3.  **Make**: To handle the build automation.

Installation on Ubuntu/Debian:
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

This will create the `build/` folder and generate `uart_echo.elf`.

2. Launch the Emulation
Run the following command to start QEMU in non-graphical mode:

```bash
make run
```

3. Interaction
Type any character in your terminal: The CPU will read it and "echo" it back to you.

Special Command: Type ! to trigger a specific response from the firmware.

4. Exit QEMU
To stop the emulation and return to your terminal:
- Press `Ctrl + A` then `X`.

---

## 🔍 Debugging
If you need to inspect the CPU state (registers):
- Inside QEMU, press `Ctrl + A` then `C` to enter the QEMU monitor.
- Type `info registers` to see the current state of R0-R15 and the CSPR.
- Type `Ctrl + A` then `C` again to return to the Echo mode.
