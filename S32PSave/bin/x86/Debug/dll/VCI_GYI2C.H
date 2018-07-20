//#include "GY7501_USBI2C.H"

#define DEV_GY7501		1//1ch-I2C
#define DEV_GY7512		2//2ch-I2C
#define DEV_GY7514		3//4ch-I2C
#define DEV_GY7518		4//8ch-I2C
#define DEV_GY7503		5//1ch-I2C
#define DEV_GY7506		6//1ch-I2C,module/
#define DEV_GY7601		7//1ch-I2C
#define DEV_GY7602		8//2ch-I2C
#define DEV_GY7604		9//4ch-I2C
#define DEV_GY7608		10//8ch-I2C

typedef struct GYI2C_DATA_INFO{
						BYTE SlaveAddr;//设备物理地址，bit7-1有效
						BYTE Databuffer[520];//Data 报文的数据；
						UINT WriteNum;//地址和数据的总个数
						UINT ReadNum;//需要读的数据的个数
						BYTE IoSel;//1 表示被选择，将被读/写
						BYTE IoData;//IO口状态，bit3－0分别表示4个IO口
									//只有与IoSel中为1的位相同的位值有效
						UINT DlyMsRead;//I2C读操作时，PC发出读命令后，延时多少ms请求读到的数据。
						BYTE Reserved[4];//Reserved 系统保留。
						}GYI2C_DATA_INFO,*pGYI2C_DATA_INFO;





extern "C" 
{ 
	DWORD	__stdcall  GYI2C_Open(DWORD DeviceType,DWORD DeviceInd,DWORD Reserved);
	DWORD	__stdcall  GYI2C_Close(DWORD DeviceType,DWORD DeviceInd);
	DWORD	__stdcall GYI2C_SetMode(DWORD DeviceType,DWORD DeviceInd,BYTE ModeValue);
	DWORD	__stdcall GYI2C_GetMode(DWORD DeviceType,DWORD DeviceInd);
	DWORD	__stdcall  GYI2C_SetClk(DWORD DeviceType,DWORD DeviceInd,DWORD ClkValue);
	DWORD	__stdcall  GYI2C_GetClk(DWORD DeviceType,DWORD DeviceInd);
	DWORD	__stdcall  GYI2C_SetChannel(DWORD DeviceType,DWORD DeviceInd,BYTE ChannelValue);
	DWORD	__stdcall  GYI2C_GetChannel(DWORD DeviceType,DWORD DeviceInd);

	DWORD	__stdcall  GYI2C_Read(DWORD DeviceType,DWORD DeviceInd,pGYI2C_DATA_INFO  pDataInfo);
	DWORD	__stdcall  GYI2C_Write(DWORD DeviceType,DWORD DeviceInd,pGYI2C_DATA_INFO pDataInfo);

	DWORD	__stdcall  GYI2C_SetIO(DWORD DeviceType,DWORD DeviceInd,pGYI2C_DATA_INFO pDataInfo);
	DWORD	__stdcall  GYI2C_GetIO(DWORD DeviceType,DWORD DeviceInd,pGYI2C_DATA_INFO pDataInfo);

	DWORD	__stdcall  GYI2C_Start(DWORD DeviceType,DWORD DeviceInd);
	DWORD	__stdcall  GYI2C_WriteByte(DWORD DeviceType,DWORD DeviceInd,BYTE DataValue);
	DWORD	__stdcall  GYI2C_ReadByte(DWORD DeviceType,DWORD DeviceInd,BYTE AckValue);
	DWORD	__stdcall  GYI2C_Stop(DWORD DeviceType,DWORD DeviceInd);





}
