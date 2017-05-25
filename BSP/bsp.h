/**
  *********************************  STM32F3xx  ********************************
  * @�ļ���     �� bsp.h
  * @����       �� redScarf
  * @��汾     �� V1.2.3
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��5��25��
  * @ժҪ       �� BSP�弶֧�ְ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f30x.h"


/* �궨�� --------------------------------------------------------------------*/
#define PORT_LED                  GPIOB                     //�˿�
#define PIN_LED                   GPIO_Pin_3               //����

/* LED�����𡢱仯 */
#define LED_ON                    GPIO_SetBits(PORT_LED, PIN_LED)
#define LED_OFF                   GPIO_ResetBits(PORT_LED, PIN_LED)
#define LED_TOGGLE                (PORT_LED->ODR ^= PIN_LED)

/* �������� ------------------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Basic_Configuration(void);
void BSP_Initializes(void);


#endif /* _BSP_H */

/**** Copyright (C)2017 redScarf. All Rights Reserved **** END OF FILE ****/
