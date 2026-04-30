# # Microcontroller Lab — STM32 Bare-Metal Programming

This repository contains bare-metal C programs for the **STM32F103C8T6 (Blue Pill)** microcontroller, written without HAL or CMSIS libraries. Each experiment directly accesses hardware registers to perform GPIO control, arithmetic operations, logical operations, and comparison operations — while observing **APSR (Application Program Status Register) flags** through inline assembly.

---

## 🎯 Objectives

- Blink an LED by directly configuring GPIO registers
- Perform **arithmetic operations** using inline ARM assembly and observe APSR flags:
  - **N (Negative)**, **Z (Zero)**, **C (Carry)**, **V (Overflow)**
- Perform **logical operations**: AND, OR, XOR
- Perform **comparison operations**: Equal, Greater Than, Less Than
- Read CPU flags using the `MRS` instruction
- Control/clear flags using the `MSR` instruction
- Visualize results via the **onboard LED (PC13)**

---

## 🧠 APSR Flag Overview

| Flag | Bit Position | Description                    |
|------|--------------|--------------------------------|
| N    | 31           | Set if result is negative      |
| Z    | 30           | Set if result is zero          |
| C    | 29           | Set if carry/borrow occurs     |
| V    | 28           | Set if signed overflow occurs  |
| Q    | 27           | Set if saturation occurs       |

---

## ⚙️ Hardware Used

- **STM32F103C8T6** (Blue Pill)
- Onboard LED connected to **PC13** (active LOW)
- ST-Link V2 Programmer

---

## 💻 Software Used

- STM32CubeIDE
- ARM GCC Compiler (bundled with STM32CubeIDE)

---

## 📂 Project Structure

```
Microcontroller-Lab/
│
│── STM32 Fundamental Note.md
│
├── LED Blink/
│   └── LED Blink .c                        # Blink PC13 onboard LED
│
├── Arithmetic Operations/
│   ├── Addition .c                          # ADDS instruction — Zero & Carry 
│   ├── Addition (Flag Show Another Way) .c  # Alternative flag check approach
│   ├── Subtraction .c                       # SUBS instruction — Negative flag 
│   ├── Multiplication .c                    # MULS instruction — flag observation
│   └── Division .c                          # SDIV + CMP — Negative flag demo
│
├── Logical Operation/
│   └── All Logical Operations .c           # ANDS / ORRS / EORS — N and Z flags
│
└── Comparison Operations/
    └── All Comparison Operations .c         # CMP — N, Z, V flags for ==, >, <
```

---

## 🚀 How It Works

### 1. GPIO Setup (Common to All Files)

All programs follow the same GPIO initialization pattern:

```c
// Enable clock for GPIOC
RCC_APB2ENR |= (1 << 4);

// Configure PC13 as output (2 MHz push-pull)
GPIOC_CRH &= ~(0xF << 20);
GPIOC_CRH |=  (0x2 << 20);

// LED OFF by default (PC13 is active LOW)
GPIOC_ODR |= (1 << 13);
```

---

### 2. Experiment Descriptions

#### 💡 LED Blink (`LED Blink/`)

Blinks the onboard PC13 LED using `GPIOC_BSRR` (set) and `GPIOC_BRR` (reset) with a software delay loop.

```c
GPIOC_BRR  = (1 << 13);   // LED ON  (active LOW)
delay();
GPIOC_BSRR = (1 << 13);   // LED OFF
delay();
```

---

#### ➕ Arithmetic Operations (`Arithmetic Operations/`)

Each file performs one arithmetic operation using inline ARM assembly, reads the APSR, and blinks the LED for each set flag.

**Key instruction pattern:**

```c
// Clear all APSR flags first
__asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

// Perform arithmetic operation (e.g., ADDS)
__asm volatile (
    "ADDS %0, %1, %2"
    : "=r"(result)
    : "r"(a), "r"(b)
    : "cc"
);

// Read flags from xPSR
__asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

// Check flags N(31), Z(30), C(29), V(28), Q(27)
for (int i = 27; i <= 31; i++) {
    if (psr_value & (1 << i)) {
        // Blink LED to indicate flag is set
    }
}
```

| File             | Instruction | Example Values         | Expected Flag |
|------------------|-------------|------------------------|---------------|
| `Addition`       | `ADDS`      | `a=5, b=-5`            | Z (Zero)      |
| `Subtraction`    | `SUBS`      | Result is negative     | N (Negative)  |
| `Multiplication` | `MULS`      | `a=5, b=-6`            | N (Negative)  |
| `Division`       | `SDIV`+`CMP`| `a=10, b=-5` → result=-2 | N (Negative) |

> **Note:** `SDIV` does not update APSR by itself. A `CMP result, #0` is added after to trigger flag updates.

---

#### 🔣 Logical Operations (`Logical Operation/`)

Demonstrates bitwise operations (`ANDS`, `ORRS`, `EORS`) and observes the **N** and **Z** flags. Logical operations do **not** affect the C or V flags.

```c
int a = 0x0F;   // 0000 1111
int b = 0xF0;   // 1111 0000

__asm volatile (
    "ANDS %0, %1, %2"   // Result = 0x00 → Z flag set
    : "=r"(result)
    : "r"(a), "r"(b)
    : "cc"
);
```

| Operation | Instruction | Flags Affected |
|-----------|-------------|----------------|
| AND       | `ANDS`      | N, Z           |
| OR        | `ORRS`      | N, Z           |
| XOR       | `EORS`      | N, Z           |

> Swap the commented instruction lines in the source to test different operations.

---

#### ⚖️ Comparison Operations (`Comparison Operations/`)

Uses the `CMP` instruction (which computes `a - b` and updates flags without storing the result) to implement equal, greater-than, and less-than checks.

```
Condition    Logic (signed)
a == b       Z == 1
a > b        Z == 0 && N == V
a < b        N != V
```

```c
int a = 50, b = 20;   // a > b

__asm volatile (
    "CMP %0, %1"
    :
    : "r"(a), "r"(b)
    : "cc"
);

// Check N=0 and Z=0 for greater-than
if (!(psr_value & (1 << 31)) && !(psr_value & (1 << 30))) {
    // LED blink: greater-than condition met
}
```

---

## ▶️ How to Run

1. Open **STM32CubeIDE** and create or open an STM32F103C8T6 project.
2. Copy one `.c` file from this repository into `Core/Src/main.c` (replace existing content).
3. **Build** the project (`Ctrl+B`).
4. **Flash** to the STM32 board via ST-Link (`Run` → `Debug`).
5. Observe the LED behavior on **PC13**.

> ⚠️ Only one `main()` can be active per build. Use one source file at a time.

---

## 💡 Key Concepts

- Only **flag-setting instructions** (e.g., `ADDS`, `SUBS`, `ANDS`) update the APSR — not all instructions do.
- The APSR is **overwritten by the last flag-setting instruction** — always clear it before a new test.
- The **Q flag is sticky** — it must be manually cleared via `MSR`.
- Logical operations (`ANDS`, `ORRS`, `EORS`) affect only **N and Z** flags.
- `SDIV` does not set flags — pair it with `CMP` to observe results.
- **PC13 LED is active LOW**: writing `0` turns it ON, writing `1` turns it OFF.

---

## ⚠️ Important Notes

- Software delay loops (`for volatile int i`) are not precise — use debug mode for exact timing.
- Always clear APSR before each new test to avoid stale flag readings:
  ```c
  __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");
  ```
- If LED behavior appears inverted, confirm the active-LOW nature of PC13.
- Delay can be skipped in debug/step mode for faster testing.

---

## 📘 Learning Outcomes

- Understand **ARM Cortex-M3 APSR flags** (N, Z, C, V, Q) and when they are set
- Write and use **inline assembly** within C programs
- Directly access **STM32 peripheral registers** without HAL
- Correlate **arithmetic/logical/comparison results** with CPU status flags
- Use LEDs as a **hardware debug output** for bare-metal programs

---

## 👨‍💻 Author

**Masud Rana Mushfiq**  
Dept. of Computer Science and Engineering  
University of Rajshahi  

---
## ⭐ Support

If this repository helped you, consider giving it a ⭐ on GitHub!



