
### STM32F103C8Tx 

The **STM32F103C8Tx** is a popular 32-bit microcontroller from STMicroelectronics based on the ARM Cortex-M3 core, widely used in embedded systems and development boards like the “Blue Pill”.
### Core & Performance

**Concept:** Defines the CPU architecture and how fast the MCU can execute instructions.
- **Core:** ARM Cortex-M3 (32-bit RISC)
- **Max Clock Frequency:** 72 MHz
- **Performance:** ~1.25 DMIPS/MHz
- **Instruction Set:** Thumb-2
- **Hardware multiplier & divider:** Yes

### Memory

**Concept:** Internal storage for program code and runtime data.
- **Flash Memory:** 64 KB (some variants unofficially have 128 KB)
- **SRAM:** 20 KB
- **EEPROM:** Not available (emulated in Flash)

---


### 1. To use STM32F103
- Enable peripheral clock via `RCC_APB2ENR` (GPIOC clock on APB2 bus)
- Configure pin mode using `GPIOC_CRH/CRL`
- Control pin using `ODR` or `BSRR/BRR`

### RCC (Reset and Clock Control)

**RCC** is the core STM32 module that:
- **Controls system clocks**
- **Turns peripherals ON/OFF**
- **Selects clock source (HSI, HSE, PLL)**

So RCC:
- enables peripherals
- defines how fast the MCU runs


### 2. Clock Sources

#### 1. HSI (High-Speed Internal)
- Internal oscillator
- No external hardware needed
- Default startup clock
- Example: **8 MHz**

#### 2. HSE (High-Speed External)
- External crystal oscillator
- More accurate than HSI
- Example: **8 MHz crystal (Blue Pill)**

#### 3. PLL (Phase Locked Loop)
- Clock multiplier
- Increases frequency

Example:
```text
8 MHz → 72 MHz
```


### 3. RCC_APB2ENR (Peripheral Enable Register)

Controls enabling of peripherals on APB2 bus.

#### GPIO Enable Bits
- GPIOA → Bit 2
- GPIOB → Bit 3
- GPIOC → Bit 4

#### Example
```c
RCC_APB2ENR |= (1 << 4);
```

Meaning:
- Set bit 4 = 1
- Enable **GPIOC clock**
- Without this → GPIOC will NOT work


### 4. GPIO Ports (STM32F103)

#### GPIOA
- Pins: PA0 – PA15
- Most commonly used
- Used for:
    - ADC
    - UART, SPI, I2C
    - General GPIO

Idea: **Main working port**

#### GPIOB
- Pins: PB0 – PB15
- Similar to GPIOA
- Used for:
    - Communication peripherals
    - Extra GPIO

Idea: **Support/extension port**

#### GPIOC
- Pins: PC0 – PC15
- Limited availability on Blue Pill
- Important:
    - **PC13 → onboard LED**

Note:
- Internally 16 pins exist
- But only few are exposed (PC13–PC15)


### 5. What are CRL and CRH?

They are **GPIO configuration registers** used to set the mode and behavior of each GPIO pin.

Each GPIO port has **16 pins (0–15)**, and these registers divide them:
- **CRL (Configuration Register Low) → controls pins 0 to 7**
- **CRH (Configuration Register High) → controls pins 8 to 15**

### Pin Configuration Structure

Each pin uses **4 bits**
```text
1 pin = 4 bits
```

#### These 4 bits are divided into:
- **MODE (2 bits)** → speed / input-output type
- **CNF (2 bits)** → pin behavior (how it works internally)(No need to learn them now)
##### MODE (2 bits)
Controls speed or input/output
- 00 → Input
- 01 → Output 10 MHz
- 10 → Output 2 MHz
- 11 → Output 50 MHz


### 6. LED Connection with PC13

Hardware connection:
```text
3.3V → resistor → LED → PC13
```

This is **Active LOW configuration**
- PC13 = LOW → LED ON
- PC13 = HIGH → LED OFF


### 7. ODR (Output Data Register)
**ODR is responsible for controlling the LED state indirectly**, but it does NOT turn on the LED directly. It is a register that stores the **output logic level of GPIO pins**.

Each bit in ODR corresponds to one pin:
- Bit 13 → PC13

Bit 13 is connected to the internal GPIO output logic for PC13, and PC13 pin is what physically drives the LED ON or OFF.

Example:
```c
GPIOC_ODR &= ~(1 << 13);  // LOW → LED ON
GPIOC_ODR |=  (1 << 13);  // HIGH → LED OFF
```

Problem:
- Uses **read → modify → write**
- Not safe in interrupt systems

### 8. BSRR and BRR Registers

#### Purpose
- Fast control of GPIO pins

#### Behavior
- **BSRR(Bit Set Reset Register) → set pin HIGH** (0-15)
- **BRR(Bit Reset Register) → reset pin LOW** (16-31)

Example:
```c
GPIOC_BSRR = (1 << 13);  // HIGH
GPIOC_BSRR = (1 << (13+16)); // Reset PC13 (LOW)

GPIOC_BRR  = (1 << 13);  // LOW
```

#### Key Properties
- 32-bit registers
- Each bit controls a pin
- **Write-only**
- **Atomic operation**

### Why BSRR/BRR are Better

#### 1. Atomic
- Single-step operation
- No interruption possible
- No race condition
#### 2. Faster
- No read-modify-write
#### 3. Safe for interrupts
- Does not overwrite other bits


### 9. PSR (Program Status Register)

#### xPSR includes:
1. APSR → flags
2. IPSR → interrupt status
3. EPSR → execution state

#### APSR (Flags)

Contains:
- N → Negative
- Z → Zero
- C → Carry
- V → Overflow
- Q → Saturation



### 10. MRS and MSR Instructions

#### 1. MRS

Full form:  
**Move Register from System register**

Meaning:
- Read system register → store in normal register

Example:
```asm
MRS R0, xPSR
```


#### 2. MSR

Full form:  
**Move System register from Register**

Meaning:
- Write value → system register

Example:
```asm
MSR APSR_nzcvq, R0
```

### System Registers

#### xPSR
- Full status register
- Combines APSR, IPSR, EPSR

#### APSR_nzcvq
- Only flag bits (NZCVQ)

### System Register Definition

System registers:
- Special CPU registers
- Hold status flags and control info


### 11. GCC Inline Assembly Format

```c
asm("instruction"
    : outputs
    : inputs
    : clobbers);
```


#### About `"cc"` Clobber
Use `"cc"` when:
- Your assembly **changes condition flags (NZCV)**

Meaning:
- Compiler must not trust old condition flags
- It must recompute them


### 12. Saturation ( APSR context)
**Saturation** means the result of a calculation has **reached its maximum or minimum limit and cannot go beyond that range**, so it gets “clamped” (stuck) at the limit instead of overflowing.

If a value goes too high or too low:
- Instead of wrapping around (overflow)
- It stops at the maximum or minimum allowed value

### Types of Saturation 
- **SSAT (Signed Saturation)**  
    Limits value to a **signed range** (includes negative numbers).  
    Example: -128 to +127 (8-bit)
- **USAT (Unsigned Saturation)**  
    Limits value to an **unsigned range** (only positive numbers).  
    Example: 0 to 255 (8-bit)


### 13. Important Insight About `CMP` Function
`CMP` is actually a **non-destructive subtract** - it performs the subtraction but throws away the result, keeping only the side effects (flag updates).

`CMP` is a _flag-only_ instruction. It performs an internal subtraction (`a - b`) **just to update flags**, and **does not produce a result value** that you can store.

### Simple logic For Logical Comparison

Using the same `CMP`-based code, you can perform all comparison operations by **observing the flags (N, Z, V)** set in xPSR.

**Technique:** `CMP a, b` → evaluates `(a - b)` → check flags

```
Condition    Logic (signed)
a == b       Z == 1
a > b        Z == 0 && N == V
a < b        N != V
```

- Positive result → A > B
- Zero result → A = B
- Negative result → A < B

After CMP that is (a - b):

|Condition|Flag rule|
|---|---|
|==|Z = 1|
|!=|Z = 0|
|>|Z = 0 AND N = V|
|<|N ≠ V|
|>=|N = V|
|<=|Z = 1 OR N ≠ V|



---

### Instruction Explain:

**1. First Instruction:**
```bash
 __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");
```
- In `MSR`, structure must be explicit
- It tells that input value that is come from **"r"(0)** is zero, will be moved to **APSR_nzcvq** that is CPU Flag register and **"cc"** tells that it will affect the CPU flag. So finally we can say that by this line we make **APSR_nzcvq all 5 flags make zero or reset** and also tells the CPU that your flag is **changed**. Here we directly write CPU flags. 

**2. Second Instruction:**
```bash
    __asm volatile (
        "ADDS %0, %1, %2"
        : "=r"(result)
        : "r"(a), "r"(b)
        : "cc"
     );
```

- It tells that instruction **"ADDS %0, %1, %2"** will take input values from **"r"(a)** and **"r"(b)** and perform addition, then store the result into **result** variable using **"=r"(result)**. The **"cc"** tells that this operation will affect the CPU condition flags (APSR flags like N, Z, C, V), so after execution the CPU flags will be updated according to the result of the addition. So finally we can say that by this line we calculate **result = a + b** and also update the **CPU flag register (APSR_nzcvq)** based on the result.


**3. Third Instruction:**
```bash
 __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));
```
- In `MRS`, trailing `::` can be omitted

It tells that instruction **"MRS %0, xPSR"** will read the value from the **xPSR system register (CPU status register)** and move it into the variable **psr_value** using **"=r"(psr_value)**. So the output operand receives the current CPU status, which includes **APSR flags (N, Z, C, V, Q), IPSR (interrupt status), and EPSR (execution state)**. Finally, we can say that by this line we are reading the full **CPU status register (xPSR)** and storing its value into **psr_value** variable.


---








