/**
  ********************************  STM32F3xx  *********************************
  * @�ļ���     �� bsp.c
  * @����       �� redScarf
  * @��汾     �� V1.2.3
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��5��25��
  * @ժҪ       �� BSP�弶֧�ְ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2017-5-25 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
�������� �� RCC_Configuration
��    �� �� ʱ������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void RCC_Configuration(void)
{
  /* ʹ��AHBʱ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | 
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | 
                        RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOF, ENABLE);

#if 0
  /* ʹ��APB2ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* ʹ��APB1ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
#endif
}

/************************************************
�������� �� GPIO_Basic_Configuration
��    �� �� �������������������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void GPIO_Basic_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = PIN_LED;                             //LED����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                      //���ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //�������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //��������(����)
  GPIO_Init(PORT_LED, &GPIO_InitStructure);

#if 0
  /* MCOʱ������ */
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
�������� �� BSP_Initializes
��    �� �� �ײ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void BSP_Initializes(void)
{
  RCC_Configuration();                                               //ʱ������
  GPIO_Basic_Configuration();                                        //IO����
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
