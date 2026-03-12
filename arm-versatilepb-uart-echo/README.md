# ARM VersatilePB UART Echo & Polling

This project is an evolution of the basic bare-metal "Hello World." It introduces **bidirectional communication** and the concept of **Hardware Polling**, allowing the ARM926EJ-S CPU to not only send data but also "listen" to user input via the PL011 UART peripheral.

## 📂 Project Structure

The project maintains the standard embedded systems directory layout:

* **`src/`**: Contains the source files.
    * `startup.s`: Assembly bootloader that initializes the Stack Pointer (SP) and jumps to C.
    * `main.c`: The core logic implementing the UART Echo and Polling mechanisms.
* **`linker/`**: Contains the Linker Script.
    * `linker.ld`: Maps the binary to the specific memory regions of the VersatilePB (Flash @ 0x10000, RAM @ 0x30000).
* **`build/`**: (Auto-generated) Stores compiled object files and the `uart_echo.elf` binary.
* **`Makefile`**: Configures the toolchain and manages the build/emulation workflow.

---

## ⚙️ Technical Deep Dive

### 1. Bidirectional UART Communication
While the previous project only wrote to the Data Register, this version interacts with multiple UART registers to manage data flow:
* **UART0_DR (0x101f1000)**: Used for both sending (Write) and receiving (Read) characters.
* **UART0_FR (0x101f1018)**: The **Flag Register**, used to check the status of the transmission and reception buffers.

### 2. Hardware Polling & Bitmasking
To receive data without an Operating System or Interrupts, the CPU uses **Polling**. 
The code continuously checks the **RXFE (Receive FIFO Empty)** bit in the Flag Register (Bit 4).
* **The Mask**: Using `(1 << 4)` creates a bitmask to isolate only the 4th bit.
* **The Logic**: An `AND` operation between the register value and the mask determines if the buffer is empty. The CPU "spins" in a `while` loop until a character is detected.

### 3. Stack Verification
By defining local variables and buffers (e.g., `char echo_str[2]`), this project validates the **Stack Pointer** initialization performed in `startup.s`. If the stack were incorrectly mapped, the function calls and local variable allocations would cause an immediate system crash.

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
