#include "crc.h"

uint16 crc16(uint8 octet, uint16 crc)
{
	int32 i;

	for (i = 8; i; i--)
	{
		if (crc & 0x0001)
		{
			crc >>= 1;
			if (octet & 0x01)
				crc |= 0x8000;
			crc = crc ^ 0x8408;   /* 0x1021 inverted = 1000 0100 0000 1000 */
			octet >>= 1;
		}
		else
		{
			crc >>= 1;
			if (octet & 0x01)
				crc |= 0x8000;
			octet >>= 1;
		}
	}

	return crc;
}

uint16 crc(int32 size, uint8 *packet)
{
	int32 i;
	uint16 crc;

	crc = (~packet[1] << 8) | (~packet[0] & 0xFF);

	for (i=2 ; i<size; i++)
		crc = crc16(packet[i], crc);

	crc = crc16(0x00, crc);
	crc = crc16(0x00, crc);
	crc = ~crc;

	crc = crc >> 8 | crc << 8; /* SWAP the bytes for Little Endian*/

	return crc;
}

