#ifndef CRC_H
#define CRC_H

//#include <stdio.h>
#include "typedef.h"

uint16 crc16(uint8 octet, uint16 crc);
uint16 crc(int32 size, uint8 *packet);

#endif // CRC_H
