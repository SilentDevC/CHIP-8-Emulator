# 🎮 CHIP-8C Emulator

> A cycle-accurate CHIP-8C emulator built in C++17 — a computer engineering student's bridge between theory and practice.

---

## 📖 About

This project is a faithful emulation of the **CHIP-8C** virtual machine, originally designed in the 1970s for hobbyist microcomputers. Built from scratch in C++17 using SDL2 for display, input, and audio.

The goal is not just a working emulator — but a practical understanding of the concepts behind every real computer system:

- Fetch → Decode → Execute cycle
- Flat memory models and addressing
- Register files and special-purpose registers
- Stack-based subroutine calls
- Memory-mapped I/O

---

## 🏗️ Architecture

### Memory Map (CHIP-8C Spec)

| Address Range | Function       |
|---------------|----------------|
| `0x0000–0x003F` | Stack          |
| `0x0040–0x004C` | Scratchpad (Font sprites) |
| `0x004D–0x00FF` | Unused         |
| `0x0100–0x01FF` | Display buffer |
| `0x0200–0x0FFF` | Program area   |

### CPU Registers

| Register | Size | Purpose |
|----------|------|---------|
| `V0–VF`  | 8-bit | General purpose (VF doubles as flag register) |
| `I`      | 16-bit | Index register (memory addressing) |
| `PC`     | 16-bit | Program counter (starts at `0x200`) |
| Delay    | 8-bit | Timing timer (60Hz) |
| Sound    | 8-bit | Buzzer timer (60Hz) |

---

## ✅ Progress

### Core
- [x] Memory layout defined (`uint8_t memory[4096]`)
- [x] General purpose registers (`V0–VF`)
- [x] Index register and program counter
- [x] Font sprites loaded into memory at `0x0040`
- [x] Constructor with full memory initialization
- [x] Opcode function declarations (all 34 opcodes)
- [ ] Fetch → Decode → Execute loop
- [ ] Opcode implementations

### Display
- [ ] SDL2 window initialization
- [ ] 64×32 pixel framebuffer rendering
- [ ] `DXYN` sprite draw with XOR and collision detection
- [ ] `00E0` clear screen

### Input
- [ ] SDL2 keypad mapping (hex keypad 0–F)
- [ ] Key press / release state tracking
- [ ] Blocking key wait (`FX0A`)

### Audio
- [ ] SDL2 audio callback
- [ ] Buzzer tone on sound timer

---

## 🗂️ Project Structure

```
chip8/
├── CMakeLists.txt
├── header/
│   ├── chip8c.h        ← CPU, memory, registers, opcodes
│   ├── display.h       ← SDL2 rendering
│   └── keypad.h        ← SDL2 input
├── source/
│   ├── chip8c.cpp
│   ├── display.cpp
│   └── keypad.cpp
├── entry.cpp           ← main()
├── roms/               ← .ch8 ROM files
└── build/              ← CMake output (git ignored)
```

---

## 🔧 Building

### Prerequisites

- C++17 compiler (MinGW / GCC / Clang)
- CMake 3.20+
- SDL2 (via vcpkg)
- Ninja or MinGW Makefiles

### Setup

```bash
# Install SDL2 via vcpkg
vcpkg install SDL2
vcpkg integrate install

# Configure and build
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build .
```

---

## 📚 References

| Resource | Link |
|----------|------|
| Cowgod's CHIP-8 Technical Reference | http://devernay.free.fr/hacks/chip8/C8TECH10.HTM |
| How to Write an Emulator — Laurence Muller | https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/ |
| Guide to making a CHIP-8 emulator — Tobias Langhoff | https://tobiasvl.github.io/blog/write-a-chip-8-emulator/ |
| SDL2 Documentation | https://wiki.libsdl.org/SDL2 |

---

## 📐 Implemented Opcodes

| Category | Opcodes |
|----------|---------|
| Flow Control | `1NNN` `2NNN` `00EE` `BNNN` |
| Display | `00E0` `DXYN` |
| Conditionals | `3XNN` `4XNN` `5XY0` `9XY0` |
| Math & Logic | `7XNN` `8XY0–8XYE` |
| Constants | `6XNN` `CXNN` |
| Memory | `ANNN` `FX1E` `FX29` `FX33` `FX55` `FX65` |
| Keypad | `EX9E` `EXA1` `FX0A` |
| Timers | `FX07` `FX15` `FX18` |

---

## 📝 License

MIT — see [LICENSE](LICENSE)
