#include "stm32f4xx_it.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"

void TIM2_IRQHandler(void)
{
	if( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET)
	{
		// 割り込み保留ビット(=割り込み要因フラグ)をクリア
	    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	    GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	    GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	    GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
	    GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	}
}
