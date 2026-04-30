#define RCC_APB2ENR   (*(volatile unsigned int*)0x40021018) // RCC clock enable register
#define GPIOC_CRH     (*(volatile unsigned int*)0x40011004) // GPIOC configuration (pins 8–15)
#define GPIOC_ODR     (*(volatile unsigned int*)0x4001100C) // GPIOC output data register

// Simple delay function
void delay(){
    for (volatile int i = 0; i < 300000; i++);
}

int main(void) {

    volatile unsigned int psr_value; // Stores PSR flags
    int result;                      // Stores operation result

    // Enable clock for GPIOC
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    GPIOC_ODR |= (1 << 13); // LED OFF (active LOW)

    while(1) {

        // ====================================================
        // DIVISION OPERATION (Negative Flag Demo)
        // Condition: a / b = negative → N flag set
        // ====================================================

        // Clear flags
        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        int a = 10, b = -5;  // Result = -2

        __asm volatile (
            "SDIV %0, %1, %2 \n"   // result = a / b
            "CMP  %0, #0      \n"  // it jus set flags based on result, don't store result
            : "=r"(result)          // \n is given here for multiple instruction
            : "r"(a), "r"(b)
            : "cc"
        );

        // Read flags
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

