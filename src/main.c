#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include "ansi_c1222.h"
#include "ansi_c1218.h"
#include "eax.h"

int main()
{
#if 1//C12.18 test

    /*identification request*/
    //uint8 testReqData[] = {0xEE, 0x00, 0x00, 0x00, 0x00, 0x01, 0x20, 0x13, 0x10};

    /*negotiate request*/
    //uint8 testReqData[] = {0x06, 0xEE,0x00,0x20,0x00,0x00,0x05,0x61,0x00,0x40,0x04,0x08,0x8A,0x5F};
    //uint8 testReqData[] = {0x06, 0xEE,0x00,0x20,0x00,0x00,0x05,0x61,0x00,0x40,0x04,0x06,0xF4,0xB6};

    /*log on request*/
    //uint8 testReqData[] = {0x06, 0xEE,0x00,0x00,0x00,0x00,0x0D,0x50,0x11,0x11,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0xCA,0x33};

    /*security request*/
    //uint8 testReqData[] = {0x06, 0xEE,0x00,0x20,0x00,0x00,0x15,0x51,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x86,0x27};

    /*read table 0, partial-read*/
    uint8 testReqData[] = {0x06, 0xEE,0x00,0x00,0x00,0x00,0x08,0x3F,0x00,0x00,0x00,0x00,0x03,0x00,0x04,0xDA,0xA2};

    //write table2, partial write, offset0, size6
    //uint8 testReqData[] = {0x06,0xEE,0x00,0x00,0x00,0x00,0x0e,0x4F,0x00,0x02,0x00,0x00,0x00,0x00,0x06,0x31,0x32,0x33,0x34,0x20,0x20,0x80,0x83};

    //write table5, full write
    //uint8 testReqData[] = {0x06,0xee,0x00,0x00,0x00,0x00,0x19,0x40,0x00,0x05,0x00,0x14,0x48,0x45,0x58,0x20,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x56,0x1f};
    //write table5, partial write
    //uint8 testReqData[] = {0x06,0xee,0x00,0x00,0x00,0x00,0x1C,0x4F,0x00,0x05,0x00,0x00,0x00,0x00,0x14,0x44,0x45,0x56,0x49,0x43,0x45,0x20,0x49,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x85,0xee};

    /*other type test*/
    //uint8 testReqData[] = {0xEE, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6E, 0x69, 0xbb};

    if (TestC1218SingleFrame(testReqData))
    {
        printf("\r\n=========================");
        printf("\r\nANSI C12.18 test OK!");
        printf("\r\n=========================");
    }
    else
    {
        printf("\r\n=========================");
        printf("\r\nANSI C12.18 test FAILED!");
        printf("\r\n=========================");
    }
#endif // 0

#if 0//C12.22 test
    /*logon request*/
    //uint8 testReqData[43] = {0x60,0x29,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x07,0xBE,0x15,0x28,0x13,0x81,0x11,0x80,0x0F,0x50,0x00,0x02,0x55,0x53,0x45,0x52,0x20,0x4E,0x41,0x4D,0x45,0x20,0x00,0x3C	};

    /*logon request with ed-class, always response*/
    //uint8 testReqData[47] = {0x60,0x2D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x07,0xBE,0x19,0x28,0x17,0x81,0x15,0x90,0x12,0x34,0x56,0x78,0x0F,0x50,0x00,0x02,0x55,0x53,0x45,0x52,0x20,0x4E,0x41,0x4D,0x45,0x20,0x00,0x3C};
    /*logon request with ed-class, no response*/
    //uint8 testReqData[47] = {0x60,0x2D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x07,0xBE,0x19,0x28,0x17,0x81,0x15,0x92,0x12,0x34,0x56,0x78,0x0F,0x50,0x00,0x02,0x55,0x53,0x45,0x52,0x20,0x4E,0x41,0x4D,0x45,0x20,0x00,0x3C};
    /*logon request with ed-class, always response, with ed-class, no authentication value*/
    //uint8 testReqData[64] =  {0x60,0x3E,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x07,0xAC,0x0F,0xA2,0x0D,0xA0,0x0B,0xA1,0x09,0x80,0x01,0x02,0x81,0x04,0x48,0xF3,0xCA,0xBD,0xBE,0x19,0x28,0x17,0x81,0x15,0x90,0x12,0x34,0x56,0x78,0x0F,0x50,0x00,0x02,0x55,0x53,0x45,0x52,0x20,0x4E,0x41,0x4D,0x45,0x20,0x00,0x3C};
    /*logon request with ed-class, always response, with authentication value*/
    uint8 testReqData[64] =  {0x60,0x3E,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x04,0xAC,0x0F,0xA2,0x0D,0xA0,0x0B,0xA1,0x09,0x80,0x01,0x02,0x81,0x04,0x48,0xF3,0xC2,0x05,0xBE,0x19,0x28,0x17,0x81,0x15,0x84,0x0F,0x50,0x00,0x02,0x55,0x53,0x45,0x52,0x20,0x4E,0x41,0x4D,0x45,0x20,0x00,0x3C,0xAD,0xDC,0x46,0x60};

    /*logoff request-short title*/
    //uint8 testReqData[29] = {0x60,0x1B,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x01,0xBE,0x07,0x28,0x05,0x81,0x03,0x80,0x01,0x52};

    /*logoff request-long title*/
    //uint8 testReqData[30] = {0x60,0x1C,0xA2,0x06,0x80,0x04,0x7B,0x82,0x85,0x63,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x01,0xBE,0x07,0x28,0x05,0x81,0x03,0x80,0x01,0x52};

    //read table0, full read
    //uint8 testReqData[31] = {0x60,0x1D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x09,0x28,0x07,0x81,0x05,0x80,0x03,0x30,0x00,0x00};
    //read table0, partial read, offset3, size 4
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x00,0x00,0x00,0x03,0x00,0x04};
    //read table0, partial read, offset1, right size is 1, and test size is 2
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x00,0x00,0x00,0x01,0x00,0x02};
    //read table0, partial read, offset1, size 0
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x00,0x00,0x00,0x01,0x00,0x00};
    //read table0, partial read, offset3, size 0
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x00,0x00,0x00,0x03,0x00,0x00};

    //read table1, full read
    //uint8 testReqData[31] = {0x60,0x1D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x09,0x28,0x07,0x81,0x05,0x80,0x03,0x30,0x00,0x01};
    //read table1, partial read�� offset4, size 8
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x01,0x00,0x00,0x04,0x00,0x08};
    //read table1, partial read�� offset4, size 0
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x01,0x00,0x00,0x04,0x00,0x00};
    //read table1, partial read�� offset4, right size is 8, and test size is 2
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x01,0x00,0x00,0x04,0x00,0x04};

    //read table2, full read
    //uint8 testReqData[31] = {0x60,0x1D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x09,0x28,0x07,0x81,0x05,0x80,0x03,0x30,0x00,0x02};
    //read table2, partial read, offset6, size 6
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x02,0x00,0x00,0x15,0x00,0x0C};
    //write table2, partial write, offset0, size6
    //uint8 testReqData[42] = {0x60,0x28,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x14,0x28,0x12,0x81,0x10,0x80,0x0E,0x4F,0x00,0x02,0x00,0x00,0x00,0x00,0x06,0x31,0x32,0x33,0x34,0x20,0x20};


    //read table3, full read
    //uint8 testReqData[31] = {0x60,0x1D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x09,0x28,0x07,0x81,0x05,0x80,0x03,0x30,0x00,0x03};

    //read table5, full read
    //uint8 testReqData[31] = {0x60,0x1D,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x09,0x28,0x07,0x81,0x05,0x80,0x03,0x30,0x00,0x05};
    //write table5, full write
    //uint8 testReqData[53] = {0x60,0x33,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x19,0x28,0x1D,0x81,0x1B,0x80,0x19,0x40,0x00,0x05,0x00,0x14,0x48,0x45,0x58,0x20,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30};
    //write table5, partial write
    //uint8 testReqData[56] = {0x60,0x36,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x1C,0x28,0x20,0x81,0x1E,0x80,0x1C,0x4F,0x00,0x05,0x00,0x00,0x00,0x00,0x14,0x44,0x45,0x56,0x49,0x43,0x45,0x20,0x49,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};

    //read table12, partial read
    //uint8 testReqData[36] = {0x60,0x22,0xA2,0x05,0x80,0x03,0x7B,0xC1,0x75,0xA6,0x04,0x80,0x02,0x7B,0x04,0xA8,0x03,0x02,0x01,0x00,0xBE,0x0E,0x28,0x07,0x81,0x0A,0x80,0x03,0x3F,0x00,0x0C,0x00,0x01,0x38,0x00,0x04};

    //clear-text + authentication test
    //uint8 testReqData[85] = {0x60,0x53,0xA2,0x0C,0x06,0x0A,0x60,0x7C,0x86,0xF7,0x54,0x01,0x16,0x00,0x7B,0x02,0xA6,0x0D,0x06,0x0B,0x60,0x7C,0x86,0xF7,0x54,0x01,0x16,0x00,0x7B,0x82,0x11,0xA7,0x03,0x02,0x01,0x04,0xA8,0x03,0x02,0x01,0x02,0xAC,0x0F,0xA2,0x0D,0xA0,0x0B,0xA1,0x09,0x80,0x01,0x02,0x81,0x04,0x48,0xF3,0xD2,0xF8,0xBE,0x19,0x28,0x17,0x81,0x15,0x96,0x54,0x45,0x4D,0x50,0x0B,0x40,0x00,0x07,0x00,0x05,0x1A,0x00,0x00,0x02,0x00,0xE4,0x1B,0xD7,0x8F,0x32};

    if (TestC1222SingleFrame(testReqData))
    {
        printf("\r\n=========================");
        printf("\r\nANSI C12.22 test OK!");
        printf("\r\n=========================");
    }
    else
    {
        printf("\r\n=========================");
        printf("\r\nANSI C12.22 test FAILED!");
        printf("\r\n=========================");
    }
#endif//ACSE PDU test

#if 0//CRC test
    uint8 packet[] =  { 0xee,0x00,0x00,0x00,0x00,0x1C,0x4F,0x00,0x05,0x00,0x00,0x00,0x00,0x14,0x44,0x45,0x56,0x49,0x43,0x45,0x20,0x49,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20 };
	printf("CRC=%04x\n", crc(sizeof(packet), packet));
#endif//CRC test

#if 0//EAX encryption algorithm test
    eaxTest();
#endif // 0

#if 0//time test
    int i = 0;
    for(; i < 10; i++)
    {
        printf("this is %d time to print msg!\n", i);
    }
#endif

    return 0;
}
