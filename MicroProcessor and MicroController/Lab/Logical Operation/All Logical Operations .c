/*
Using the same ANDS-based code, you can perform all logical (bitwise) operations by observing the flags (N, Z) set in xPSR.
Technique: ANDS/ORRS/EORS/BICS → performs bitwise operation → updates flags → check flags
Logical operations mainly affect the N and Z flags, and sometimes the C flag. They have no effect on the V flag.

Flags meaning:
Z == 1  → result is zero
N == 1  → result is negative (MSB = 1)
*/

#define RCC_APB2ENR   (*(volatile unsigned int*)0x40021018) // RCC clock enable register
#define GPIOC_CRH     (*(volatile unsigned int*)0x40011004) // GPIOC configuration (pins 8–15)
#define GPIOC_ODR     (*(volatile unsigned int*)0x4001100C) // GPIOC output data register

// Simple delay function for visible LED transition
void delay(){
    for (volatile int i = 0; i < 300000; i++);
}

int main(void) {

    volatile unsigned int psr_value; // Stores PSR (CPU status register flags like N, Z, C, V, Q)
    int result;                      // Stores operation result

    // Enable clock for GPIOC
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output (LED pin)
    GPIOC_CRH &= ~(0xF << 20); // Clear bits
    GPIOC_CRH |=  (0x2 << 20); // Set as output mode (2 MHz)

    GPIOC_ODR |= (1 << 13); // Turn LED OFF (active LOW)

    while(1) {

        // ====================================================
        // LOGICAL OPERATION (Z flag set)
        // Condition: AND operation with opposite bits = 0
        // Note: Logical ops affect only N and Z flags
        // ====================================================

        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        int a = 0x0F;   // 0000 1111
        int b = 0xF0;   // 1111 0000

        __asm volatile (
            "ANDS %0, %1, %2"   // AND operation (result = 0)
            // "ORRS %0, %1, %2" // OR operation
            // "EORS %0, %1, %2" // XOR operation
            : "=r"(result)
            : "r"(a), "r"(b)
            : "cc"
        );

        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        // Check flags (N, Z, C, V, Q)
        for (int i = 27; i <= 31; i++) {
            if (psr_value & (1 << i)) {
                GPIOC_ODR &= ~(1 << 13);   // LED ON (active low)
                GPIOC_ODR |=  (1 << 13);   // LED OFF
            }
        }

        delay();
    }
}

