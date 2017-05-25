/**
  ********************************  STM32F3xx  *********************************
  * @文件名     ： bsp.c
  * @作者       ： redScarf
  * @库版本     ： V1.2.3
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年5月25日
  * @摘要       ： BSP板级支持包源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2017-5-25 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
函数名称 ： RCC_Configuration
功    能 ： 时钟配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void RCC_Configuration(void)
{
  /* 使能AHB时钟 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | 
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | 
                        RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOF, ENABLE);

#if 0
  /* 使能APB2时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* 使能APB1时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
#endif
}

/************************************************
函数名称 ： GPIO_Basic_Configuration
功    能 ： 基本输入输出引脚配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void GPIO_Basic_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = PIN_LED;                             //LED引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //高速输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推完输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //无上下拉(浮空)
  GPIO_Init(PORT_LED, &GPIO_InitStructure);

#if 0
  /* MCO时钟配置 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_0);

  #ifdef STM32F303xC
  RCC_MCOConfig(RCC_MCOSource_SYSCLK);
  #else
  RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCO1Div_2);
  #endif
#endif
}

/************************************************
函数名称 ： BSP_Initializes
功    能 ： 底层初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void BSP_Initializes(void)
{
  RCC_Configuration();                                               //时钟配置
  GPIO_Basic_Configuration();                                        //IO配置
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
