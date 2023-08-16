#include <stdint.h>

// Base addresses for peripheral registers
#define RCC_BASE            0x40023800U
#define GPIOA_BASE          0x40020000U

// RCC (Reset and Clock Control) Registers
#define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x30U))

// GPIOA (General Purpose I/O Port A) Registers
#define GPIOA_MODER         (*(volatile uint32_t*)(GPIOA_BASE + 0x00U))
#define GPIOA_ODR           (*(volatile uint32_t*)(GPIOA_BASE + 0x14U))

int main(void)
{
    // Enable the clock for GPIOA
    RCC_AHB1ENR |= (1 << 0);

    // Configure GPIOA Pin 5 as output
    GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

    while (1)
    {
        // Toggle the LED pin
        GPIOA_ODR ^= (1 << 5);

        // Simple delay
        for (volatile int i = 0; i < 100000; ++i);
    }

    return 0;
}
