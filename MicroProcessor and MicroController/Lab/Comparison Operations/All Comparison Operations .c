/*
Using the same CMP-based code, you can perform all comparison operations by observing the flags (N, Z, V) set in xPSR.
Technique: CMP a, b → evaluates (a - b) → check flags

Condition    Logic (signed)
a == b       Z == 1
a > b        Z == 0 && N == V
a < b        N != V

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
        // COMPARISON OPERATION Example (Greater Than)
        // Condition: a > b (N=0, Z=0 for signed comparison)
        // ====================================================
        
        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");
        
        int a = 50, b = 20;  // a > b

        __asm volatile (
            "CMP %0, %1"     // Compare (a - b) sets flags
            :                // CMP subtracts (a - b) only to update flags (N, Z, C, V); it does not store the result.
            : "r"(a), "r"(b)
            : "cc"
        );

        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        // Check if N=0 and Z=0 (For Greater Than condition)
        // You also can make a loop to check all 5 flag
        if (!(psr_value & (1 << 31)) && !(psr_value & (1 << 30))) {
            GPIOC_ODR &= ~(1 << 13);  // LED ON
            for (volatile int j = 0; j < 100000; j++);
            GPIOC_ODR |= (1 << 13);   // LED OFF
        }

        delay();
    }
}

