
#include "system.h"

// cycles per microsecond
static uint32_t usTicks = 0;
// current uptime for 1kHz systick timer. will rollover after 49 days. hopefully we won't care.
static volatile uint32_t sysTickUptime = 0;
// cached value of RCC->CSR
uint32_t cachedRccCsrValue;

void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

// SysTick

static volatile int sysTickPending = 0;


// Return system uptime in microseconds (rollover in 70minutes)

uint32_t microsISR(void)
{
    register uint32_t ms, pending, cycle_cnt;

    
        cycle_cnt = SysTick->VAL;

        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            // Update pending.
            // Record it for multiple calls within the same rollover period
            // (Will be cleared when serviced).
            // Note that multiple rollovers are not considered.

            sysTickPending = 1;

            // Read VAL again to ensure the value is read after the rollover.

            cycle_cnt = SysTick->VAL;
        }

        ms = sysTickUptime;
        pending = sysTickPending;
    

    return ((ms + pending) * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

uint32_t micros(void)
{
    register uint32_t ms, cycle_cnt;

    // Call microsISR() in interrupt and elevated (non-zero) BASEPRI context

    if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) || (__get_BASEPRI())) {
        return microsISR();
    }

    do {
        ms = sysTickUptime;
        cycle_cnt = SysTick->VAL;
        /*
         * If the SysTick timer expired during the previous instruction, we need to give it a little time for that
         * interrupt to be delivered before we can recheck sysTickUptime:
         */
        asm volatile("\tnop\n");
    } while (ms != sysTickUptime);

    return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

// Return system uptime in milliseconds (rollover in 49 days)
uint32_t millis(void)
{
    return sysTickUptime;
}

#if 1
void delayMicroseconds(uint32_t us)
{
    uint32_t now = micros();
    while (micros() - now < us);
}
#else
void delayMicroseconds(uint32_t us)
{
    uint32_t elapsed = 0;
    uint32_t lastCount = SysTick->VAL;

    for (;;) {
        register uint32_t current_count = SysTick->VAL;
        uint32_t elapsed_us;

        // measure the time elapsed since the last time we checked
        elapsed += current_count - lastCount;
        lastCount = current_count;

        // convert to microseconds
        elapsed_us = elapsed / usTicks;
        if (elapsed_us >= us)
            break;

        // reduce the delay by the elapsed time
        us -= elapsed_us;

        // keep fractional microseconds for the next iteration
        elapsed %= usTicks;
    }
}
#endif

void delay(uint32_t ms)
{
    while (ms--)
        delayMicroseconds(1000);
}

#define SHORT_FLASH_DURATION 50
#define CODE_FLASH_DURATION 250

//void failureMode(failureMode_e mode)
//{
//    int codeRepeatsRemaining = 10;
//    int codeFlashesRemaining;
//    int shortFlashesRemaining;
//
//    while (codeRepeatsRemaining--) {
//
//        shortFlashesRemaining = 5;
//        codeFlashesRemaining = mode + 1;
//        uint8_t flashDuration = SHORT_FLASH_DURATION;
//
//        while (shortFlashesRemaining || codeFlashesRemaining) {
//
//            delay(flashDuration);
//
// 
//            delay(flashDuration);
//
//            if (shortFlashesRemaining) {
//                shortFlashesRemaining--;
//                if (shortFlashesRemaining == 0) {
//                    delay(500);
//                    flashDuration = CODE_FLASH_DURATION;
//                }
//            } else {
//                codeFlashesRemaining--;
//            }
//        }
//        delay(1000);
//    }
//
//#ifdef DEBUG
//    systemReset();
//#else
//    systemResetToBootloader();
//#endif
//}
