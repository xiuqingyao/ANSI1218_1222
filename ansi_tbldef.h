#ifndef ANSI_TBLDEF_H
#define ANSI_TBLDEF_H

/*table id(standard, self-defined) & procedure id*/
#define ST00  0x0000
#define ST01  0x0001
#define ST02  0x0002
#define ST03  0x0003
#define ST05  0x0005
#define ST06  0x0006
#define ST07  0x0007
#define ST08  0x0008
#define ST10  0x000A
#define ST11  0x000B
#define ST12  0x000C
#define ST13  0x000D
#define ST15  0x000F
#define ST16  0x0010
#define ST20  0x0014
#define ST21  0x0015
#define ST22  0x0016
#define ST23  0x0017
#define ST24  0x0018
#define ST25  0x0019
#define ST26  0x001A
#define ST27  0x001B
#define ST28  0x001C
#define ST30  0x001E
#define ST31  0x001F
#define ST32  0x0020
#define ST33  0x0021

#define ST34  0x0022
#define ST40  0x0028
#define ST41  0x0029
#define ST42  0x002A
#define ST43  0x002B
#define ST44  0x002C
#define ST50  0x0032
#define ST51  0x0033
#define ST52  0x0034
#define ST53  0x0035
#define ST54  0x0036
#define ST55  0x0037

#define ST60  0x003C
#define ST61  0x003D
#define ST62  0x003E
#define ST63  0x003F
#define ST64  0x0040

#define ST70  0x0046
#define ST71  0x0047
#define ST72  0x0048
#define ST73  0x0049
#define ST74  0x004A
#define ST75  0x004B
#define ST76  0x004C

#define MT00  0x0800
#define MT01  0x0801
#define MT02  0x0802
#define MT03  0x0803
#define MT04  0x0804
#define MT05  0x0805
#define MT06  0x0806
#define MT07  0x0807
#define MT08  0x0808
#define MT09  0x0809
#define MT11  0x080B
#define MT12  0x080C
#define MT13  0x080D
#define MT14  0x080E
#define MT15  0x080F
#define MT16  0x0810
#define TABLE_END 0xFFFF


/*table permission*/
#if 0
#define TB_OPMOD_30					0x80	//bit7 set 1, table support fully read
#define TB_OPMOD_3F					0x40	//bit6 set 1, table support partial read
#define TB_OPMOD_40					0x20	//bit5 set 1, table support fully write
#define TB_OPMOD_4F					0x10	//bit4 set 1, table support partial write
#endif
#define TB_OPMOD_READ_ACCESS		0x08	//bit3 set 1, table support read
#define TB_OPMOD_WRITE_ACCESS		0x04	//bit2 set 1, table support write for column in table
#define TB_OPMOD_CALI               0x02    //bit1 set 1, calibrate meter
#define TB_OPMOD_NONE               0x01    //bit0 set 1, table cannot be read or written

/*table attribute permission*/
#define OPMOD_W                   0x8000	//表示允许写
#define OPMOD_R                   0x4000	//表示允许读
#if 0
#define OPMOD_BITMAP_REV          0x2000	//表示位域需要取反
#define OPMOD_FACT                0x1000    //表示只能在厂内模式下可设
#endif
#define OPMOD_CONTNUM_VAR         0x0800    //表示ContNum可变，如ST64的负荷数
#if 0
#define OPMOD_ST08_RESP           0x0400    //ST08响应，长度特殊
#define OPMOD_CALI                0x0200    //校准表，需要更新校表参数
#define OPMOD_REVERSE             0x0100    //数据长度大于1，且需要倒置
#define OPMOD_LOAD                0x0080    //负荷曲线，读取时特殊处理
#define OPMOD_SELFREAD            0x0040    //日冻历史电量，读取时特殊处理
#define OPMOD_SELFREAD_MONTH      0x0020    //月冻历史电量，读取时特殊处理
#define OPMOD_EVENT               0x0010    //月冻历史电量，读取时特殊处理
#define OPMOD_MEM_MARK            0x0007
#endif

//for table-41
#define ST41_NUM_PASSWORDS          3	   //u08
#define ST41_PASSWORD_LEN           20	   //u08
#define ST41_NUM_KEYS               0	   //u08
#define ST41_KEY_LEN                0	   //u08
#define ST41_NUM_PERMISS_USED       13     //u16

/*table structure*/
typedef struct
{
	uint8*	pData_Addr;	//data address, maybe in E2PROM, RAM, ROM
	uint32	Len;		//data length
	uint32  ContNum;    //item number
	uint32	OPMOD;		//access permission
}STRU_COMTABL;

/*table manager*/
typedef struct
{
    uint16 Table_Id;  	        //table id
    STRU_COMTABL* pTable_Addr;	//table address
    uint16 Item_Number;         //record number
    uint16 Table_Lenth;	        //table data length
    uint8  OPMOD;	            //access permission
}STRU_INDEX_TABLE;

#endif // ANSI_TBLDEF_H
