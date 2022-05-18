///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//Filename	:app_can.c
//Project Code	:
//
//Version	:V0.0
//Autor	:NLH
//Accomplished Date:20200820
//Change Content:
//
//RVersions	:
//Autor	:
//Accomplished Date:
//Change Content:
//
//RVersions	:
//Autor	:
//Accomplished Date:
//Change Content:
//
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#include "app_can.h"
#include "ac78xx_can.h"
#include "ac78xx.h"
#include "ac78xx_irq_cb.h"
#include "main.h"
#include "user.h"




unsigned char CanTime2MsFlag;;


#define CAN_CLEAR_ALL_ID_BIT	(0x60000000)//是清零所有ID位,保留控制过滤ID类型位
CAN_FilterControl 		canFilterTab[CAN_MAX_FILTER_NUM] = 
{
		{ 0, 0, 0x00000000, 0x00000000},    
    { 1, 0, 0x00000000, 0x00000000},    
    { 2, 0, 0x00000000, 0x00000000},
    { 3, 0, 0x00000000, 0x00000000},
    { 4, 0, 0x00000000, 0x00000000},
    { 5, 0, 0x00000000, 0x00000000},
    { 6, 0, 0x00000000, 0x00000000},
    { 7, 0, 0x00000000, 0x00000000},
    { 8, 0, 0x00000000, 0x00000000},    
    { 9, 0, 0x00000000, 0x00000000},    
    {10, 0, 0x00000000, 0x00000000},   
    {11, 0, 0x00000000, 0x00000000},
    {12, 0, 0x00000000, 0x00000000},
    {13, 0, 0x00000000, 0x00000000},
    {14, 0, 0x00000000, 0x00000000},
    {15, 0, 0x00000000, 0x00000000},
};
const uint32_t	canFilterMask[3] = {0x5FFFFFFF,  0x7FFFFFFF,  0x1FFFFFFF};//只接收标准帧 只接收扩展帧 接收两种数据帧

void CAN_SetFilterParam(uint8_t filterNum, uint8_t filterEn, CAN_FilterMode_TypeDef filterMode, CAN_FilterMask_TypeDef filterMask, uint32_t ID)
{
	canFilterTab[filterNum].enable = filterEn;
  canFilterTab[filterNum].code = ID;
	if (filterMode == CAN_FILTER_MASK_MODE)
	{
			canFilterTab[filterNum].mask = (canFilterMask[filterMask] & ~ID);//进行掩码屏蔽
	}
	else
	{
			canFilterTab[filterNum].mask = (canFilterMask[filterMask] & CAN_CLEAR_ALL_ID_BIT);//进行ID屏蔽,就是ID必须与设置的ID一模一样,才接收
	}   
}





int32_t CAN1_IRQnCallBack(uint32_t event, uint32_t wparam, uint32_t lparam)
{

	CAN_MSG_INFO RecCANMsgInfo;
	if (event & CAN_EVENT_RECVMSG)
	{
		if (CAN_IsMsgInReceiveBuf((CAN_Type*)lparam))
		{
				CAN_MessageRead((CAN_Type*)lparam, &RecCANMsgInfo);
				for(unsigned char i=0;i<CAN1_RX_NUM;i++)
				{
					if(CAN1Rx[i].ID==RecCANMsgInfo.ID)
					{
						CAN1Rx[i].Time1msAcc=0;
						CAN1Rx[i].ErrFlag=0;
						CAN1Rx[i].GetDataFlag=1;
						for(unsigned char j=0;j<RecCANMsgInfo.DLC;j++)
						{
							CAN1Rx[i].Data[j]=RecCANMsgInfo.Data[j];
						}
					}
				}	
		}
	}
	return 1;
}

int32_t CAN2_IRQnCallBack(uint32_t event, uint32_t wparam, uint32_t lparam)
{
	CAN_MSG_INFO RecCANMsgInfo;
	if (event & CAN_EVENT_RECVMSG)
	{
		if (CAN_IsMsgInReceiveBuf((CAN_Type*)lparam))
		{
				CAN_MessageRead((CAN_Type*)lparam, &RecCANMsgInfo);
				for(unsigned char i=0;i<CAN2_RX_NUM;i++)
				{
					if(CAN2Rx[i].ID==RecCANMsgInfo.ID)
					{
						CAN2Rx[i].Time1msAcc=0;
						CAN2Rx[i].ErrFlag=0;
						CAN2Rx[i].GetDataFlag=1;
						for(unsigned char j=0;j<RecCANMsgInfo.DLC;j++)
						{
							CAN2Rx[i].Data[j]=RecCANMsgInfo.Data[j];
						}
					}
				}	
		}
	}
	return 1;
}


CAN_SendSts_TypeDef CAN_SendMsg(CAN_Type *CANx, _CAN_TX CanTx)
{
	CAN_MSG_INFO 			sendCANMsgInfo;
	sendCANMsgInfo.ID = CanTx.ID;
	sendCANMsgInfo.IDE = CanTx.IDE;
	sendCANMsgInfo.RTR = CanTx.RTR;
	sendCANMsgInfo.DLC = CanTx.DLC;
	for(unsigned char i=0;i<8;i++)
	{
		sendCANMsgInfo.Data[i]=CanTx.Data[i];
	}
    
    if((CANx == CAN1) || (CANx == CAN2))
    {
        if(!CAN_IsTransmitBusy(CANx, TRANSMIT_SECONDARY))
        {
            if (!CAN_MessageSend(CANx, &sendCANMsgInfo, TRANSMIT_SECONDARY))
            {
                return CAN_SEND_MSG_SUCCS;
            }
            else
            {
                return CAN_SEND_MSG_FILED;
            }
        }
				else
				{
					return CAN_SEND_MSG_FILED;
				}
    }
	
	return CAN_SEND_MSG_FILED;
}
 
void CAN1_Send_handler(void)
{
	static unsigned char CAN1SendState=0;
	if(CAN1_TX_NUM>0)
	{
		if(CAN1Tx[CAN1SendState].SendMode==CIRCULATION)
		{
			if(CAN1Tx[CAN1SendState].Time1msAcc>=CAN1Tx[CAN1SendState].SendCycle)
			{
				if(CAN_SendMsg(CAN1,CAN1Tx[CAN1SendState])==CAN_SEND_MSG_SUCCS)
					CAN1Tx[CAN1SendState].Time1msAcc=0;
			}
		}
		else
		{
			if(CAN1Tx[CAN1SendState].SendFlag)
			{
				if(CAN_SendMsg(CAN1,CAN1Tx[CAN1SendState])==CAN_SEND_MSG_SUCCS)
					CAN1Tx[CAN1SendState].SendFlag=0;
					
			}
		}
		if(++CAN1SendState>=CAN1_TX_NUM)
			CAN1SendState=0;
	}	
}
void CAN2_Send_handler(void)
{
	static unsigned char CAN2SendState=0;
	if(CAN2_TX_NUM>0)
	{
		if(CAN2Tx[CAN2SendState].SendMode==CIRCULATION)
		{
			if(CAN2Tx[CAN2SendState].Time1msAcc>=CAN2Tx[CAN2SendState].SendCycle)
			{
				if(CAN_SendMsg(CAN2,CAN2Tx[CAN2SendState])==CAN_SEND_MSG_SUCCS)
					CAN2Tx[CAN2SendState].Time1msAcc=0;
			}
		}
		else
		{
			if(CAN2Tx[CAN2SendState].SendFlag)
			{
				if(CAN_SendMsg(CAN2,CAN2Tx[CAN2SendState])==CAN_SEND_MSG_SUCCS)
					CAN2Tx[CAN2SendState].SendFlag=0;
					
			}
		}
		if(++CAN2SendState>=CAN2_TX_NUM)
			CAN2SendState=0;
	}	
}

void CAN_CAN1_CAN2_Init(void)  
{
	CAN_Config canConfig;
	CAN_BaudrateConfig baudrate;
//================CAN1===============================
	CAN_SetEventCallBack(CAN1, CAN1_IRQnCallBack);
	
	GPIO_SetFunc(GPIO_PC14, GPIO_FUN1);
	GPIO_SetFunc(GPIO_PC15, GPIO_FUN1);

	canConfig.canMode = CAN_MODE_NORMAL;
	canConfig.clockSrc = CAN_CLKSRC_AHB;
	canConfig.interruptEnable = ENABLE;
	canConfig.autoReset = ENABLE;
	canConfig.TPSS = DISABLE;
	canConfig.TSSS = ENABLE;
	canConfig.TSMODE = 0;
	canConfig.ROM = 1;
	baudrate.S_PRESC = 5;
	baudrate.S_SEG_1 = 11;
	baudrate.S_SEG_2 = 2;
	baudrate.S_SJW = 2;
	for(unsigned char i=0;i<CAN1_RX_NUM;i++)
	{
		CAN_SetFilterParam(i, 1, CAN_FILTER_CODE_MODE, (CAN_FilterMask_TypeDef)CAN1Rx[i].IDE, CAN1Rx[i].ID);
	}
	canConfig.filterList=canFilterTab;
	CAN_Initialize(CAN1, &canConfig, &baudrate);
	
//	CAN_Standby(CAN1, DISABLE);
//================CAN2===============================	
	
	CAN_SetEventCallBack(CAN2, CAN2_IRQnCallBack);
	GPIO_SetFunc(GPIO_PC10, GPIO_FUN1);
	GPIO_SetFunc(GPIO_PC11, GPIO_FUN1);
	
	canConfig.canMode = CAN_MODE_NORMAL;
	canConfig.clockSrc = CAN_CLKSRC_AHB;
	canConfig.interruptEnable = ENABLE;
	canConfig.autoReset = ENABLE;
	canConfig.TPSS = DISABLE;
	canConfig.TSSS = ENABLE;
	canConfig.TSMODE = 0;
	canConfig.ROM = 1;
	baudrate.S_PRESC = 5;
	baudrate.S_SEG_1 = 11;
	baudrate.S_SEG_2 = 2;
	baudrate.S_SJW = 2;
	for(unsigned char i=0;i<16;i++)
	{
		canFilterTab[i].code=0;
		canFilterTab[i].enable=0;
		canFilterTab[i].mask=0;
	}
	for(unsigned char i=0;i<CAN2_RX_NUM;i++)
	{
		CAN_SetFilterParam(i, 1, CAN_FILTER_CODE_MODE, (CAN_FilterMask_TypeDef)CAN2Rx[i].IDE, CAN2Rx[i].ID);
	}
	canConfig.filterList=canFilterTab;
	CAN_Initialize(CAN2, &canConfig, &baudrate);
	//CAN_Standby(CAN2, DISABLE);
}

void App_CAN_1ms_Interrupt(void)
{
	for(unsigned char i=0;i<CAN1_RX_NUM;i++)
	{
		if(++CAN1Rx[i].Time1msAcc>=2000)
		{
			CAN1Rx[i].Time1msAcc=2000;
			CAN1Rx[i].ErrFlag=1;
		}
	}
	
	for(unsigned char i=0;i<CAN2_RX_NUM;i++)
	{
		if(++CAN2Rx[i].Time1msAcc>=2000)
		{
			CAN2Rx[i].Time1msAcc=2000;
			CAN2Rx[i].ErrFlag=1;
		}
	}
	
	for(unsigned char i=0;i<CAN1_TX_NUM;i++)
	{
		if(++CAN1Tx[i].Time1msAcc>=100000)
		{
			CAN1Tx[i].Time1msAcc=100000;
		}
	}
	
	for(unsigned char i=0;i<CAN2_TX_NUM;i++)
	{
		if(++CAN2Tx[i].Time1msAcc>=100000)
		{
			CAN2Tx[i].Time1msAcc=100000;
		}
	}
	static unsigned char Time1msAcc;
	if(++Time1msAcc>=3)
	{
		CanTime2MsFlag=1;
		Time1msAcc=0;
	}
}



void App_CAN_Init(void)
{

	
	CAN_CAN1_CAN2_Init();
	
}

void App_CAN_Main(void)
{
	if(CanTime2MsFlag)
	{
		CanTime2MsFlag=0;
		CAN1_Send_handler();
		CAN2_Send_handler();
	}
	
	
}
	




