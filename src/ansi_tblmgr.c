/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ansi_def.h"
#include "ansi_tblmgr.h"
#include "ansi_c1219.h"

/**
 * calculate check sum
 *
 * @param sum total sum
 */
uint8 GetChecksum(uint8 sum)
{
    return ~sum + 1;
}

/**
 * search table id
 *
 * @param tableId: search table id
 * @return index of table
 */
uint16 SearchTableIndex(uint16 tableId)
{
    uint16 i;
    for(i=0; i < g_AnsiTabSize; i++)
    {
        if(C1219_TABLE[i].Table_Id == tableId)
        {
            return i;
        }
        else if(C1219_TABLE[i].Table_Id > tableId)
        {
            //return 0xFFFF;
            break;
        }
    }
    return 0xFFFF;
}

/**
 * get access right of table
 *
 * @param tableId: table id
 * @param ctrl: permission
 */
uint8 GetSum(uint8 *pScr, uint8 Len)
{
    u8_16_t sum ;
    sum.w = 0x0000;
    while(Len--)
    {
        sum.w += *pScr++;
    }

#if (LITTLE_ENDIAN == 1)
    return sum.b[0];
#else
    return sum.b[1];
#endif
}

#if 0
/**
 * get access right of table
 *
 * @param tableId: table id
 * @param ctrl: permission
 */
 uint8 access_permission(uint16 tableId, uint8 ctrl)
 {
     return 1;
 }
 #endif

/**
 * read data from table
 *
 * @param tableId: table id
 * @param offset: offset from first item
 * @param count: read bytes
 * @param pData: buffer to store data
 * @param pSize: read bytes
 * @param pchkSum: check sum value
 * @return : error code
 */
uint8 PartialRead(uint8 serviceCode, uint8 tableId, uint32 offset, uint16 count, uint8 *pData, uint16 *pSize, uint8 *pchkSum)//stEpsemPayload *pEpsemData)
{
    uint16 i, j = 0;
    uint16 curOffsetIdx = 0xFFFF;
    uint16 itemSize = 0;
    uint16 contnum = 0;
    uint16 TableIdx = SearchTableIndex(tableId);
    uint16 totalItems = 0;//total items, including sub-items
    uint32 totalSize = 0;//total size, including sub-items
    uint8 *ptr_buffer = pData + 3;//reserve first 3 bytes for "response code(1 byte) + count(2 bytes)"
    uint16 subItems = 0;//total items, excluding sub-items
    STRU_COMTABL *tablehead_ptr;

    if (0xFFFF == TableIdx)
    {
        return CODE_ERR;//cannot find table id in access right table, return
    }

    subItems = C1219_TABLE[TableIdx].Item_Number;//total items, excluding sub-items
    tablehead_ptr = (STRU_COMTABL *)C1219_TABLE[TableIdx].pTable_Addr;

    /*access right judgment*/
    if(0 == (C1219_TABLE[TableIdx].OPMOD & TB_OPMOD_READ_ACCESS))
    {
        return CODE_IAR;//no read permission, return
    }

    /*calculate total items & size, find offset index in table*/
    for(i = 0; i < subItems; i++)
    {
        if(tablehead_ptr[i].OPMOD & OPMOD_CONTNUM_VAR)
        {
            //TODO:================================================
            contnum = 1;//g_LpSet.Number_intervals_set1;
            //TODO:================================================
        }
        else
        {
            contnum = tablehead_ptr[i].ContNum;
        }

        /*calculate sub-items*/
        for (j = 0; j < contnum; j++)
        {
            totalItems++;
            totalSize += tablehead_ptr[i].Len;

            /*find offset index*/
            if (curOffsetIdx == 0xFFFF)
            {
                if (offset == 0)
                {
                    curOffsetIdx = 1;//first item index
                    itemSize = tablehead_ptr[0].Len;//first item size
                }
                else if ((offset == totalSize))// && (i != (totalItems + contnum - 1)))
                {
                    curOffsetIdx = totalItems + 1;
                }
            }
            else
            {
                if (curOffsetIdx == totalItems)//offset index is current index
                {
                    itemSize = tablehead_ptr[i].Len;
                }
            }
        }
    }

    if (serviceCode == 0x30)//full read
    {
        memcpy(ptr_buffer, C1219_TABLE[TableIdx].pTable_Addr[0].pData_Addr, totalSize);
        *pSize = totalSize;
        *pchkSum = GetSum(ptr_buffer, *pSize);
    }
    else if (serviceCode == 0x3F)//partial read
    {
        /*if offset is not right*/
        if (curOffsetIdx == 0xFFFF)
        {
            return CODE_IAR;
        }

        /*read bytes is not the same as item size*/
        if ((count != 0) && (itemSize != count))
        {
            return CODE_IAR;
        }

        /*read bytes from table*/
        if (0 == count)//according to c12.22, read data from offset to end of table
        {
            itemSize = totalSize - offset;
        }

        //read specific bytes
        memcpy(ptr_buffer, C1219_TABLE[TableIdx].pTable_Addr[curOffsetIdx - 1].pData_Addr, itemSize);
        *pSize = itemSize;
        *pchkSum = GetSum(ptr_buffer, *pSize);
    }
    else
    {
        //should not reach here......
        return CODE_IAR;
    }

    return CODE_OK;
}

/**
 * write data to table
 *
 * @param srcData: write buffer
 * @param tableId: table id
 * @param offset: offset from first item
 * @return : error code
 */
uint8 PartialWrite(uint8 serviceCode, uint8 tableId, uint32 offset, uint16 count, uint8 *pSrcData)
{
    uint16 i, j = 0;
    uint16 curOffsetIdx = 0xFFFF;
    uint16 itemSize = 0;
    uint16 contnum = 0;
    uint16 TableIdx = SearchTableIndex(tableId);
    uint16 totalItems = 0;//total items, including sub-items
    uint32 totalSize = 0;//total size, including sub-items
    uint16 subItems = 0;//total items, excluding sub-items
    STRU_COMTABL *tablehead_ptr;

    if (0xFFFF == TableIdx)
    {
        return CODE_ERR;//cannot find table id in access right table, return
    }

    subItems = C1219_TABLE[TableIdx].Item_Number;//total items, excluding sub-items
    tablehead_ptr = (STRU_COMTABL *)C1219_TABLE[TableIdx].pTable_Addr;

    /*access right judgment*/
    if(0 == (C1219_TABLE[TableIdx].OPMOD & TB_OPMOD_WRITE_ACCESS))
    {
        return CODE_IAR;//no write permission, return
    }

    /*calculate total items & size, find offset index in table*/
    for(i = 0; i < subItems; i++)
    {
        if(tablehead_ptr[i].OPMOD & OPMOD_CONTNUM_VAR)
        {
            //TODO:================================================
            contnum = 1;//g_LpSet.Number_intervals_set1;
            //TODO:================================================
        }
        else
        {
            contnum = tablehead_ptr[i].ContNum;
        }

        /*calculate sub-items*/
        for (j = 0; j < contnum; j++)
        {
            totalItems++;
            totalSize += tablehead_ptr[i].Len;

            /*find offset index*/
            if (curOffsetIdx == 0xFFFF)
            {
                if (offset == 0)
                {
                    curOffsetIdx = 1;//first item index
                    itemSize = tablehead_ptr[0].Len;//first item size
                }
                else if ((offset == totalSize))// && (i != (totalItems + contnum - 1)))
                {
                    curOffsetIdx = totalItems + 1;
                }
            }
            else
            {
                if (curOffsetIdx == totalItems)//offset index is current index
                {
                    itemSize = tablehead_ptr[i].Len;
                }
            }
        }
    }

    if (serviceCode == 0x40)//full write
    {
        if (totalSize != count)
        {
            return CODE_IAR;
        }

#if 0//(SW_SIMULATION == 1)
        printf("\r\nbefore write:********************\r\n");
        int cnt = 0;
        for (; cnt < totalSize; cnt++)
        {
            printf ("0x%02x ", C1219_TABLE[TableIdx].pTable_Addr[0].pData_Addr[cnt]);
            if ((cnt+1)%10 == 0)
                printf("\r\n");
        }
        printf("\r\n");
#endif

        memcpy(C1219_TABLE[TableIdx].pTable_Addr[0].pData_Addr, pSrcData, totalSize);

#if 0//(SW_SIMULATION == 1)
        printf("\r\nafter write:********************\r\n");
        for (cnt = 0; cnt < totalSize; cnt++)
        {
            printf ("0x%02x ", C1219_TABLE[TableIdx].pTable_Addr[0].pData_Addr[cnt]);
            if ((cnt+1)%10 == 0)
                printf("\r\n");
        }
        printf("\r\n");
#endif
    }
    else if (serviceCode == 0x4F)//partial write
    {
        /*if offset is not right*/
        if ((count == 0) || (curOffsetIdx == 0xFFFF))
        {
            return CODE_IAR;
        }

        /*write size is not the same as item size*/
        if (itemSize != count)
        {
            return CODE_IAR;
        }

#if 0//(SW_SIMULATION == 1)
        printf("\r\nbefore write:********************\r\n");
        int cnt = 0;
        for (; cnt < itemSize; cnt++)
        {
            printf ("0x%02x ", C1219_TABLE[TableIdx].pTable_Addr[curOffsetIdx - 1].pData_Addr[cnt]);
            if ((cnt+1)%10 == 0)
                printf("\r\n");
        }
        printf("\r\n");
#endif

        /*overwrite item content*/
        memcpy(C1219_TABLE[TableIdx].pTable_Addr[curOffsetIdx - 1].pData_Addr, pSrcData, itemSize);

#if 0//(SW_SIMULATION == 1)
        printf("\r\nafter write:********************\r\n");
        for (cnt = 0; cnt < itemSize; cnt++)
        {
            printf ("0x%02x ", C1219_TABLE[TableIdx].pTable_Addr[curOffsetIdx - 1].pData_Addr[cnt]);
            if ((cnt+1)%10 == 0)
                printf("\r\n");
        }
        printf("\r\n");
#endif
    }
    else
    {
        //should not reach here......
        return CODE_IAR;
    }

    return CODE_OK;
}

/**
 * read data from table, this API is invoked by module
 *
 * @param rx_ptr: write buffer
 * @param tableId: table id
 * @param offset: offset from first item
 * @return : error code
 */
uint8* TableRead(uint8 tableId, uint32 index, uint16 *pItemSize)
{
    uint16 TableIdx = SearchTableIndex(tableId);

    *pItemSize = C1219_TABLE[TableIdx].pTable_Addr[index].Len;

    return C1219_TABLE[TableIdx].pTable_Addr[index].pData_Addr;
}

/**
 * write data to table, this API is invoked by module
 *
 * @param srcData: source data
 * @param tableId: table id
 * @param offset: offset from first item
 * @return : write bytes
 */
uint8 TableWrite(uint8 *srcData, uint8 tableId, uint32 index)
{
    uint16 TableIdx = SearchTableIndex(tableId);

    memset(C1219_TABLE[TableIdx].pTable_Addr[index].pData_Addr, 0x00, C1219_TABLE[TableIdx].pTable_Addr[index].Len);
    memcpy(C1219_TABLE[TableIdx].pTable_Addr[index].pData_Addr, srcData, C1219_TABLE[TableIdx].pTable_Addr[index].Len);

    return C1219_TABLE[TableIdx].pTable_Addr[index].Len;
}

