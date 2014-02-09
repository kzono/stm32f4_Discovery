#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"




/* leds in the board will fade */

int main(void)
{
  uint16_t PrescalerValue;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  int i;

  /* TIM config */
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* LEDs are on GPIOD */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
//  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
//  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
//  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

  /* pwm set up */

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 21000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 665;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

#if 0
  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);


  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);


  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
#endif

  TIM_ARRPreloadConfig(TIM4, ENABLE);

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);


  /* DEMO */
  int brightness = 0;
  int delta = 1;

  while(1)  // Do not exit
  {
#if 0
       brightness += delta;

       if(brightness > 256){
      	   delta = -1;
       }else if(brightness <= 0){
       	   delta = 1;
       }
       TIM4->CCR1 = brightness;
#else
       brightness++;
 //         TIM4->CCR3 = 333 - (brightness + 0) % 333; // set brightness
 //         TIM4->CCR4 = 333 - (brightness + 166/2) % 333; // set brightness
       TIM4->CCR1 = 333 - (brightness + 333/2) % 333; // set brightness
 //         TIM4->CCR2 = 333 - (brightness + 499/2) % 333; // set brightness
#endif

       for(i=0;i<10000;i++);  // delay
//          for(i=0;i<10000;i++);  // delay
//          for(i=0;i<10000;i++);  // delay

  }
}

