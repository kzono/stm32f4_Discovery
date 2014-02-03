#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

static GPIO_InitTypeDef  GPIO_InitStructure;

void busy_wait(unsigned int cnt);


int main(void)
{
//	const unsigned int count = 100; // 待ち時間用ループカウント

	// クロックの設定
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// GPIO の初期化。PD12, PD13, PD14 and PD15　を出力に設定。
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIOD, &GPIO_InitStructure);

	 // ボード上のスイッチ用にPA0 を入力に設定。
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);


	while(1)
    {
		// スイッチが押されたら　LED　を点灯する
		if(0 != GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){
			// LED ON
			GPIO_SetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			//busy_wait(count);
		}else{
			// LED OFF
			GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			//busy_wait(count);
		}

    }
	return 0;
}

void busy_wait(unsigned int cnt){
	unsigned int i, j, k;
	int x = 0;

	for (i = 0; i < cnt; ++i) {
		for (j = 0; j < cnt; ++j) {
			for (k = 0; k < cnt; ++k) {
				x++;
			}
		}
	}
}
