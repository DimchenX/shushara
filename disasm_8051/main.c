// Copyright 2021 IOsetting <iosetting(at)outlook.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/***

 */


#include "stc8hx.h"

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned        uint32_t;

void READ_DATA(uint8_t adres);
void READ_CODE(uint16_t adres, uint8_t count);
void toHEX(uint8_t __xdata const *H, uint16_t count);
void Uart1_Init(void);
void Timer0_Init(void);
void UART_SEND_BYTE(uint8_t B);
void UART_SEND_String(uint8_t __xdata const *msg);

__xdata uint8_t RX_bufc;
__xdata uint8_t RX_buf[128];
__xdata uint8_t TX_bufc;
__xdata uint8_t TX_buf[128];
__xdata uint8_t HEX_bufc;
__xdata uint8_t HEX_buf[128*2];
__xdata uint8_t Buffer[128];
__code  uint8_t HEX_TAB[17] = "0123456789ABCDEF";
__code __at(0x0000) uint8_t _CODE_PAGE_[]; 
__data __at(0x0000) uint8_t _DATA_PAGE_[0xff];
__bit   TX_busy;


void READ_DATA(uint8_t adres)
{
	Buffer[127] = _DATA_PAGE_[adres];
} 

void READ_CODE(uint16_t adres, uint8_t count)
{   
	uint8_t i = 0;
	while(count--)
	Buffer[i] = _CODE_PAGE_[adres+i]; i++;
	
}

void toHEX(uint8_t __xdata const *H, uint16_t count)
{
    while (count--) {
        uint8_t b = *H++;
        HEX_buf[HEX_bufc++] = HEX_TAB[b >> 4];
        HEX_buf[HEX_bufc++] = HEX_TAB[b & 0x0F];
    }
    HEX_buf[HEX_bufc] = '\0';
}

void Timer0_Isr(void) __interrupt(1)
{
	P34 = !P34;
}

void Uart1_Isr(void) __interrupt(4)
{
	if (TI)				//Check UART1 transmit interrupt
	{
        TX_busy = 0;
		TI = 0;	          //Clear UART1 transmit interrupt flag
	}

	if (RI)				//Check UART1 receive interrupt
	{
			RX_buf[RX_bufc++] = SBUF;
			RX_bufc &= 127;
		RI = 0;			//Clear UART1 receive interrupt flag
	}
}

void Uart1_Init(void)	//115200bps@36.864MHz
{
	SCON = 0x50;		//8 bits and variable baudrate
	AUXR |= 0x40;		//imer clock is 1T mode
	AUXR &= 0xFE;		//UART 1 use Timer1 as baudrate generator
	TMOD &= 0x0F;		//Set timer work mode
	P_SW1 = (P_SW1 & ~0xc0) | 0x40;		//UART1/USART1: RxD(P3.6), TxD(P3.7)
	TL1 = 0xB0;			//Initial timer value
	TH1 = 0xFF;			//Initial timer value
	ET1 = 0;			//Disable Timer%d interrupt
	TR1 = 1;			//Timer1 start run
	ES = 1;				//Enable UART1 interrupt

}


void Timer0_Init(void)		//100us@36.864MHz
{
	AUXR |= 0x80;			//imer clock is 1T mode
	TMOD &= 0xF0;			//Set timer work mode
	TL0 = 0x9A;				//Initial timer value
	TH0 = 0xF1;				//Initial timer value
	TF0 = 0;				//Clear TF0 flag
	TR0 = 1;				//Timer0 start run
	ET0 = 1;				//Enable timer0 interrupt
}

void UART_SEND_BYTE(uint8_t B)
{
	while(TX_busy); 
	SBUF = B;
	TX_busy = 1;
}

void UART_SEND_String(uint8_t __xdata const *msg)
{
	uint8_t i = 0;
	while(msg[i])
		UART_SEND_BYTE(msg[i++]);
}

void UART_SEND_Stringc(uint8_t __code const *msg)
{
	uint8_t i = 0;
	while(msg[i])
		UART_SEND_BYTE(msg[i++]);
}

int main(void)
{
    //SYS_SetClock();
   
	P3M0 = 0;
	P3M1 = 0;
	P33 = 1;
	P34 = 1;
	P35 = 1;
	P1M0 = 0;
    P1M1 = 0;

	TX_bufc = 0;
	RX_bufc = 0;
	HEX_bufc = 0;

	Uart1_Init();
	Timer0_Init();

    while(1)
    {
		UART_SEND_Stringc("HELLO\t\n");
		READ_CODE(0x00, 0x20);
		toHEX(Buffer, 0x20);
		UART_SEND_String(HEX_buf);
		READ_DATA(0x55);
		UART_SEND_BYTE(Buffer[127]);
		UART_SEND_BYTE('\n');
        P33 = !P33;
    }
}
