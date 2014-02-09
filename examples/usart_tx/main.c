//
// http://cyberworks.cocolog-nifty.com/blog/2011/12/stm32f4-disco-2.html
// こちらのプログラムを出発点にさせてもらう。多謝。
//
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"


//時間遅延関数
void myDelay(){
	uint32_t ii;
	ii=0;
	//1,000,000回ループを回る
	while(ii<1000000){
		ii++;
	}
}

int main(void)
{
	//GPIOAとUSART2にクロック供給
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//GPIO初期化用構造体を作る
	GPIO_InitTypeDef GPIO_InitStructure;

	//GPIOAのPIN2を出力に設定
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//GPIOAのPIN2をオルタネィテブファンクションのUSART2に割り当て
	GPIO_PinAFConfig(GPIOA , GPIO_PinSource2 , GPIO_AF_USART2);

	//USART初期化用構造体を作る
	USART_InitTypeDef USART_InitStructure;

	//USART2を9600bps,8bit,ストップビット1,パリティなし,フロー制御なし,送受信有効に設定
	USART_InitStructure.USART_BaudRate = 9600*3;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	//USART2を有効化
	USART_Cmd(USART2, ENABLE);

	//Aを繰り返し送信
	while (1)
	{
		USART_SendData(USART2, 'A');
		myDelay();
	}
}
