#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

//static GPIO_InitTypeDef  GPIO_InitStructure;

void TIM_Configuration(void);


int main(void)
{
	 /* HCLK = SYSCLK/2 */
	  RCC_HCLKConfig(RCC_SYSCLK_Div2);

	  /* PCLK1 = HCLK/4 */
	  RCC_PCLK1Config(RCC_HCLK_Div4);

	// タイマのPWMの設定
	TIM_Configuration();


	while(1)
    {
    }
	return 0;
}

void TIM_Configuration(void){
	uint16_t CCR1_Val = 40;
	uint16_t PrescalerValue = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	/* GPIOD Configuration: TIM3 CH1 (PD12) */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	//Configuration
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);


	// 原発振は 8MHz
	/* Time base configuration */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	PrescalerValue =(uint16_t) (SystemCoreClock  / 8000000)-1;//3
	// TIMER TEMEL AYARLAMALAR
	TIM_TimeBaseStructure.TIM_Period=400;
	TIM_TimeBaseStructure.TIM_Prescaler=839;//PrescalerValue;

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

	//PWM canal 1
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

	/* TIM enable counter */
	TIM_Cmd(TIM4, ENABLE);
    /* Main Output Enable */
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
}
