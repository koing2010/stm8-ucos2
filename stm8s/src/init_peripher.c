/**********************************************************************************

File_name:      init_peripher.c
Version:		   0.0
Revised:        $Date:2014-7-  ; $
Description:    the main file of this project.
Notes:          This version targets the stm8
Editor:		    Mr.Kong

**********************************************************************************/


/*================================================================================
@ Include files
*/
#include "init_peripher.h"


/*================================================================================
@ Global variable
*/


/*================================================================================
@ All functions  as follow
*/

/*********************************************************************************
Function:  void Delay_Ms(u16 z)
Description:
delay 1ms @  8MHz

Input:        ByteData you want to send.
Output:       None
Return:       None
Others:
*********************************************************************************/
void Delay_Ms(u16 z)
{
  u16 x,y;
  for(x=z;x>0;x--)
  { for(y=1600;y>0;y--);}


}

/*********************************************************************************
**名称：void EEPROM_WriteByte(uchar EEPROM_Data,uint EEPROM_Add)
**
**功能：向EEPROM 写入一字节
**
**说明：存储一字节数据 0-639
**
**时间：2013.5.6
**********************************************************************************/
void EEPROM_WriteByte(uchar EEPROM_Data,u16 EEPROM_Add)
{
  uchar *Address;
  Address=(uchar *)(EEPROM_Add+0x4000);
  do
  {
    FLASH_DUKR=0xae; // 写入第一个密钥
    FLASH_DUKR=0x56; // 写入第二个密钥
  }
  while((FLASH_IAPSR&0x08)==0); // 若解锁未成功，则重新再来
  *Address =EEPROM_Data;     // 写入第一个字节
  while((FLASH_IAPSR&0x04)==0); // 等待写操作成功
}




/*********************************************************************************
**名称：uchar EEPROM_ReadByte(uint EEPROM_Add)
**
**功能：从EEPROM 读取一字节
**
**说明：读取一字节数据
**
**时间：2013.5.6
*********************************************************************************/
uchar EEPROM_ReadByte(u16 EEPROM_Add)
{
  uchar EEPROM_Data;
  EEPROM_Data = *((uchar*) (EEPROM_Add+0x4000));

  return EEPROM_Data;
}


/********************************************************************************
Function:  void UART1_SendBytE
Description:
send a byte by UART1
Input:        ByteData you want to send.
Output:       None
Return:       None
Others:
*********************************************************************************/
void UART1_SendByte(uchar ByteData)
{

   while(!UART1_SR_TXE);
   UART1_DR=ByteData;     //向USART1发送一字节数据

   while(!UART1_SR_TC);   //是否发送完毕

}

/********************************************************************************
Function:       TIM1_PWM_Init
Description:
configurate PWM generator
Input:        CarrierFrq  you set
Output:       None
Return:       None
Others:
*********************************************************************************/
void TIM1_PWM_Init(u8 CarrierFrq)

{

  u16  TIM1_ARR;

  TIM1_CCMR1=TIM1_CCMR1|0x70;
  TIM1_CCER1=TIM1_CCER1|0x03;

  TIM1_ARR  = ( 16000 / CarrierFrq ) -1 ;// calculate the timer1 count.
  TIM1_ARRH =( TIM1_ARR >> 8) & 0xFF;//
  TIM1_ARRL = TIM1_ARR & 0XFF;


  TIM1_ARR = (TIM1_ARR +1 )/ 3 -1 ;//calculate the timer1 compare data.
  TIM1_CCR1H = (TIM1_ARR >> 8) & 0xFF;//
  TIM1_CCR1L = TIM1_ARR & 0xFF;

  TIM1_PSCRH = 0x00;
  TIM1_PSCRL = 0x00;
  //TIM1_CCMR1_OC1M = 100;
  // TIM1_CR1=TIM1_CR1|0X01;
  TIM1_BKR=0x80;
  DISABLE_TIM1_PWM;



}
/********************************************************************************
Function: void SendFrame(u8 *data,u8 Length)
Description: send a frame of data by UART1

Input:     u8 *data    pointer  of a series of data you want to send.
u8 Length  the number of this series of

data.
Output:       None
Return:       None
Others:
*********************************************************************************/
void SendFrame(u8 *data,u8 Length)
{

  while( Length>0 )
  {

    UART1_SendByte(*data);
    data++;
    Length--;

  }
}

/********************************************************************************
**名称：void TIM4_Init(void)
**
**功能：定时器4 初始化
**
**说明：定时器4 用于模拟串口  波特率为9600
**
**时间：2013.04.26
*********************************************************************************/
void TIM4_Init(void)
{
  TIM4_IER=0x00; // 禁止中断
  TIM4_EGR=0x01; // 允许产生更新事件 // 设置控制器，启动定时器

  TIM4_PSCR = 0x00;//0.0625us

  TIM4_ARR  = 0xEF; // 15us
  TIM4_CNTR = 0XEF;

  //TIM4_CR1=0x01; // b0=1,允许计数器工作
  TIM4_IER=0x01; // 允许中断
  ENABLE_TIM4  ;


}
/********************************************************************************
**名称：void IWDG_Init(void)
**
**功能：独立看门狗初始化
**
**说明：
**
**时间：2013.09.27
*********************************************************************************/
void IWDG_Init(void)
{

  IWDG_KR=0xcc;
  IWDG_KR=0x55;
  IWDG_PR=0x06;
  IWDG_RLR=0xff;
  IWDG_KR=0xaa;

}




/********************************************************************************
Function:  All_Iint
Description:  external device will be configurated in this sector.
Input:        None
Output:       None
Return:       None
Others:
*********************************************************************************/
void All_Init(void)
{


  /***************MCU clock config*********/
  CLK_ECKR=0x03;//外部时钟寄存器 外部时钟准备就绪，外部时钟开
  CLK_CKDIVR = 0x00;
  CLK_SWCR=0x02;//切换控制寄存器 使能切换机制
  CLK_SWR=0xB4;//主时钟切换寄存器 选择HSE为主时钟源


  while (!(CLK_SWCR & 0x08));
  CLK_CSSR=0x05;//切换中断开启，时钟安全系统使能
  CLK_ICKR_LSIEN = 1; //开启看门狗时钟
  // IWDG_Init();//in


  /* ALARM_INDICATOR  PA6 push_pull output*/

  PA_DDR_DDR6 = 1;
  PA_CR1_C16  = 1;
  PA_CR2_C26  = 0; //LED

  /*RUNNING_INDICATOR PD3 push_pull output*/

  PD_DDR_DDR2 = 1;
  PD_CR1_C12  = 1;
  PD_CR2_C22  = 0; //LED

  /*STATUS_INDICATOR PC1 PC2 PC3 PC4 push_pull output*/

  PC_DDR_DDR1 = 1;
  PC_CR1_C11  = 1;
  PC_CR2_C21  = 0; //INDICATOR_1

  PC_DDR_DDR2 = 1;
  PC_CR1_C12  = 1;
  PC_CR2_C22  = 0; //INDICATOR_2

  PC_DDR_DDR3 = 1;
  PC_CR1_C13  = 1;
  PC_CR2_C23  = 0; //INDICATOR_3

  PC_DDR_DDR4 = 1;
  PC_CR1_C14  = 1;
  PC_CR2_C24  = 0; //INDICATOR_4


  /*******serial_port_config************/


  //UART1
     UART1_BRR2= 0x02;
     UART1_BRR1= 0x68;
     UART1_CR2 = 0x2c;//允许接收，发送，开接收中断
  //UART3
     UART3_BRR2= 0x02;
     UART3_BRR1= 0x68;
     UART3_CR2 = 0x2c;//允许接收，发送，开接收中断

   //UART1_CR2=0x0c;//关闭接收中断

  /*************TIM2_config************/

  //主要用于10ms计时
  TIM2_IER = 0x00; // 禁止中断
  TIM2_EGR = 0x01; // 允许产生更新事件 // 设置控制器，启动定时器

  TIM2_PSCR = 0x08;//计数器时钟=主时钟/2^8相当于计数器周期为16us

  TIM2_ARRH = 0x02; // 设定重装载时的寄存器值，
  TIM2_ARRL = 0x70;
  TIM2_CNTRH = 0x02;// 设定计数器的初值
  TIM2_CNTRL = 0x70;// 定时周期=(ARR+1)*16uS=10mS;
  TIM2_CR1 = 0x01; // b0=1,允许计数器工作
  TIM2_IER = 0x01; // 允许中断
  //   //TIM1_PWM_Init( CarrierFreqency);



  /*************TIM4_config***********/
  //主要为接收数据计时用
  //   TIM4_CR1= 0x01;//使能计数器
  //
  //   TIM4_IER= 0x01;//更新中断使能
  //   TIM4_EGR= 0x01;
  //   TIM4_CNTR= 255;//计数器值
  //   TIM4_ARR=  255;//自动重装的值
  //   TIM4_PSCR= 0x07;//128分频值
  //   ENABLE_TIM4  ;

}


/*********************************************************************************
Function:  ModBus_CRC16
Description:
Calculate  ModBus_CRC16

Input:       uchar *puchMsg :   the buffer address
uchar crc_count :   length of data buffer

Output:       None
Return:       CRC
Others:	      dont care
*********************************************************************************/
u16 ModBus_CRC16(uchar *puchMsg,uchar crc_count)
 {
    uchar i ,j;
    uchar XORResult;
    u16 xorCRC = 0xA001; //计算CRC的多项式
    u16 CRC = 0xFFFF;
    for ( i = 0; i <crc_count; i++)
     {
        CRC ^= puchMsg[i];
        for (j = 0; j < 8; j++)
         {
            XORResult = CRC & 1;
            CRC >>= 1;
            if (XORResult)
               CRC ^= xorCRC;
         }
     }

    return  CRC;
 }
/*@*****************************end of file*************************************@*/
