#ifndef ANSI_TBLMGR_H
#define ANSI_TBLMGR_H

#include "typedef.h"

/*following API are used by C12.18 & C12.22*/
uint8 GetChecksum(uint8 sum);

/*following two APIs are used by application module*/
uint8* TableRead(uint8 tableId, uint32 index, uint16 *pItemSize);
uint8 TableWrite(uint8 *srcData, uint8 tableId, uint32 index);

/*following two APIs are used by protocol*/
uint8 PartialRead(uint8 serviceCode, uint8 tableId, uint32 offset, uint16 count, uint8* pData, uint16* pSize, uint8* pchkSum);
uint8 PartialWrite(uint8 serviceCode, uint8 tableId, uint32 offset, uint16 count, uint8 *pSrcData);

#endif // ANSI_TBLMGR_H
