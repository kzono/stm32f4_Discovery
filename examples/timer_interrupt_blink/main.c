#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "misc.h"	// 	割り込みコントローラ用関数




void NVIC_Configuration(void);
void GPIO_Configuration(void);
void Timer_Configuration(void);

int main(void)
{
	  int i;

	  // クロックの設定
//	  RCC_PCLK1Config(RCC_HCLK_Div4);

	  // 割り込みコントローラの設定
	  NVIC_Configuration();

	  // GPIO の設定(LED)
	  GPIO_Configuration();

	  // タイマの設定
	  Timer_Configuration();

    while(1)
    {
    }
    return 0;
}

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    // タイマ２の割り込みを有効にする
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void GPIO_Configuration(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  // IOポートD　のクロックを有効にする
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	  // LEDにつながっているピンを出力に設定する
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;

	  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Timer_Configuration(void)
{
	  uint16_t PrescalerValue;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_OCInitTypeDef  TIM_OCInitStructure;

	  // タイマクロックを有効にする
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	  // TimeBase を設定する
	  TIM_TimeBaseStructure.TIM_Period = 250;
	  TIM_TimeBaseStructure.TIM_Prescaler = 40000-1;
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	  // タイマ割り込みを有効にする
	  TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE);

	  // タイマ２のカウントアップを開始する
	  TIM_Cmd(TIM2, ENABLE);
}




