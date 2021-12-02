/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            isr
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/


#include "FIRELOCK.h"
/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            isr
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/

#include "isr.h"
#include "headfile.h"
#define WHEEL_C         192             //�����ܳ�192mm
#define ENCODER_PULSE   1024            //������ת��һ��������
#define WHEEL_PULSE    (1024*104/50)     //����ת��һ����������104���ֳ�������50��������������
#define Speed_Limit     240


void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DMA1_Channel1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DMA1_Channel2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DMA1_Channel3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DMA1_Channel5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DMA1_Channel6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void DMA1_Channel7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void ADC1_2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_BRK_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_TRG_COM_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_CC_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void I2C1_EV_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void I2C1_ER_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void I2C2_EV_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void I2C2_ER_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void SPI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void SPI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI15_10_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void RTCAlarm_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USBWakeUp_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USBHD_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));


void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update );


        icm_flag=1;
        encode_count++;
        encode();

        if(encode_count==4)
        {
            encode_count=0;
            encode_calculation();
            velocity_L = (LF+LB)/2;
             velocity_R = (RF+RB)/2;

             PID_motor(wheels.v1,wheels.v4,wheels.v2,wheels.v3,DIRF);  //�ٶ�����
             if(Abs(LF)>Speed_Limit||Abs(RF)>Speed_Limit||Abs(LB)>Speed_Limit||Abs(RB)>Speed_Limit)      //������ʩ1
             {
               motor_init();
               while(1)
               {
                   oled_int16(1, 3, 404);
                   gpio_set(A9,0);
               }

             }

        }





    }
}

void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update );

    }
}

void USART1_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{
    camera_flag=1;
    get_slave_data();
}

void USART3_IRQHandler(void)
{

}

void DMA1_Channel4_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{

}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{

  while (1)
  {
  }
}




//int16 i=0;
//int16 flag=0;
//
//
//
//void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//
////��ʱ��1 ���
////��ʱ��2 ��·pwm
////��ʱ��3 ���ж�
////��ʱ��2 ��·pwm���ܹ���·��
//
//void TIM3_IRQHandler(void)
//{
//
//    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//    {
//        TIM_ClearITPendingBit(TIM3, TIM_IT_Update );
//       // flash_a_test++;
//        encode();
//
//
//
//
////        velocity_L = (LF+LB)/2;
////        velocity_R = (RF+RB)/2;
////
////        PID_motor(wheels.v1,wheels.v4,wheels.v2,wheels.v3,DIRF);  //�ٶ�����
//
//    }
//}
//
//void USART2_IRQHandler(void)
//{
//    uint8 dat;
//    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//    {
//        USART_ClearITPendingBit(USART2, USART_IT_RXNE); //������ڽ����жϱ�־λ
//        dat = USART_ReceiveData(USART2);                //��ȡ��������
//        get_slave_data(dat);                            //��ÿһ���ֽڵĴ������ݴ���temp_buff�С�
//    }
//}
//


