
/*
This program visualizes ARM CPU status flags without a debugger
by converting xPSR flags into LED blink patterns (PC13).

 * N → blink 1 time
 * Z → blink 2 times
 * C → blink 3 times
 * V → blink 4 times
 * Q → blink 5 times
 */

#define RCC_APB2ENR (*(volatile unsigned int*) 0x40021018)
#define GPIOC_CRH (*(volatile unsigned int*) 0x40011004)
#define GPIOC_BSRR (*(volatile unsigned int*)(0x40011010))
#define GPIOC_BRR (*(volatile unsigned int*)(0x40011014))

/* Delay */
void delay(){
    for (volatile int i = 0; i < 300000; i++);
}

/* Blink pattern (used by flags) */
void blink(int times){
    for (int i = 0; i < times; i++){
        GPIOC_BRR = (1 << 13);
        delay();
        GPIOC_BSRR = (1 << 13);
        delay();
    }
    delay();
}


int main(void){
    volatile unsigned int psr_value;
    int result;

    /* Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* Configure PC13 as output */
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    GPIOC_BSRR = (1 << 13);

    while(1){
        // Clear APSR flags
        __asm volatile ("MSR APSR_nzcvq, %0" : : "r"(0) : "cc");

        int a = 5, b = -5;

        // ADD operation (sets flags)
        __asm volatile (
            "ADDS %0, %1, %2"
            : "=r"(result)
            : "r"(a), "r"(b)
            : "cc"
        );

        // Read xPSR flags
        __asm volatile ("MRS %0, xPSR" : "=r"(psr_value));

        // N flag (bit 31)
        if (psr_value & (1 << 31))
            blink(1);

        // Z flag (bit 30)
        if (psr_value & (1 << 30))
            blink(2);

        // C flag (bit 29)
        if (psr_value & (1 << 29))
            blink(3);

        // V flag (bit 28)
        if (psr_value & (1 << 28))
            blink(4);

        // Q flag (bit 27)
        if (psr_value & (1 << 27))
            blink(5);

            delay();
    }
}

