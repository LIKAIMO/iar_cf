#include "fc_init.h"

void init(void)
{
    mySystemInit();
    UART1_init(115200);
}

void checkForBootLoaderRequest(void)
{
    void(*bootJump)(void);

    if (*((uint32_t *)0x20009FFC) == 0xDEADBEEF) {

        *((uint32_t *)0x20009FFC) = 0x0;

        __enable_irq();
        __set_MSP(*((uint32_t *)0x1FFFD800));

        bootJump = (void(*)(void))(*((uint32_t *) 0x1FFFD804));
        bootJump();
        while (1);
    }
}
void enableGPIOPowerUsageAndNoiseReductions(void)
{
    RCC_AHBPeriphClockCmd(
        RCC_AHBPeriph_GPIOA |
        RCC_AHBPeriph_GPIOB |
        RCC_AHBPeriph_GPIOC |
        RCC_AHBPeriph_GPIOD |
        RCC_AHBPeriph_GPIOE |
        RCC_AHBPeriph_GPIOF,
        ENABLE
    );

    gpio_config_t gpio;

    gpio.mode = Mode_AIN;

    gpio.pin = Pin_All & ~(Pin_13 | Pin_14 | Pin_15);  // Leave JTAG pins alone
    gpioInit(GPIOA, &gpio);

    gpio.pin = Pin_All;
    gpioInit(GPIOB, &gpio);
    gpioInit(GPIOC, &gpio);
    gpioInit(GPIOD, &gpio);
    gpioInit(GPIOE, &gpio);
    gpioInit(GPIOF, &gpio);
}
void mySystemInit(void)
{
    //上电时检测boot是否短接
    checkForBootLoaderRequest();
    
    //初始化DFU，重置RCC
    SystemInit();
    
    // Configure NVIC preempt/priority groups
    NVIC_PriorityGroupConfig(NVIC_PRIORITY_GROUPING);

    // cache RCC->CSR value to use it in isMPUSoftreset() and others
    cachedRccCsrValue = RCC->CSR;
    RCC_ClearFlag();

    //初始化GPIO
    //enableGPIOPowerUsageAndNoiseReductions();

    // Init cycle counter
    //配置micros计数
    cycleCounterInit();
    
    // SysTick
    //72M
    SysTick_Config(SystemCoreClock / 1000);
}

void UART1_init(u32 bound)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    //USART1 Tx(PA.09) Rx(PA.10)
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_7);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1配置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

