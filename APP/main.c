/**
  ********************************  STM32F3xx  *********************************
  * @文件名     ： main.c
  * @作者       ： redScarf
  * @库版本     ： V1.2.3
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年5月25日
  * @摘要       ： 主函数
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2017-5-25 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "fc_init.h"


/* 宏定义 --------------------------------------------------------------------*/
#define PORT_LED                  GPIOB                     //端口
#define PIN_LED                   GPIO_Pin_3 | GPIO_Pin_4            //引脚

/* LED亮、灭、变化 */
#define LED_ON                    GPIO_SetBits(PORT_LED, PIN_LED)
#define LED_OFF                   GPIO_ResetBits(PORT_LED, PIN_LED)
#define LED_TOGGLE                (PORT_LED->ODR ^= PIN_LED)

static void GPIO_Basic_Configuration(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能AHB时钟 */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | 
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | 
                        RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOF, ENABLE);

    //必须先使能时钟再初始化IO口
    GPIO_InitStructure.GPIO_Pin = PIN_LED;                             //LED引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //高速输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推完输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //无上下拉(浮空)
    GPIO_Init(PORT_LED, &GPIO_InitStructure);

    
}

/************************************************
函数名称 ： main
功    能 ： 主函数入口
参    数 ： 无
返 回 值 ： 0
作    者 ： redScarf
*************************************************/
int main(void)
{
    char b = '1';
    GPIO_Basic_Configuration();
    init();
    
    while(1)
    {
        LED_ON;                                  //LED变化
        USART1->TDR = b;
        delay(1000);
        b = USART1->RDR;
        LED_OFF;
        delay(1000);
    }
}


/**** Copyright (C)2017 redScarf. All Rights Reserved **** END OF FILE ****/
