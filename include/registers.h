#include <stdint.h>

#define PERIPH_BASE (0x40000000UL)

#define AHB_OFFSET (0x00020000UL)

#define RCC_OFFSET (0x00001000UL)

#define AHBENR_OFFSET (0x14UL)

#define GPIOB_OFFSET (0x08000400UL)

#define MODER_OFFSET (0x00UL)

#define ODR_OFFSET (0x14)
/* BASE ADDRESS */
#define AHB_BASE (PERIPH_BASE+AHB_OFFSET)

#define RCC_BASE (AHB_BASE+RCC_OFFSET)

#define GPIOB_BASE (PERIPH_BASE + GPIOB_OFFSET)

/* REGISTERS */
#define RCC_AHBENR (*(volatile unsigned int *)(RCC_BASE+AHBENR_OFFSET))

#define GPIOB_MODER (*(volatile unsigned int *)(GPIOB_BASE+MODER_OFFSET))

#define GPIOB_ODR (*(volatile unsigned int *)(GPIOB_BASE+ODR_OFFSET))

//ill kill myself
