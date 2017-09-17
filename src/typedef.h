#ifndef TYPEDEF_H
#define TYPEDEF_H

#define LITTLE_ENDIAN 1
#define SW_SIMULATION 1

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned long      uint32;
typedef signed char        int8;
typedef signed short       int16;
typedef signed long        int32;
typedef float              float32;
typedef double             float64;

#define  FALSE     0
#define  TRUE      (!FALSE)

//ANSI协议中的数据类型
#define UINT8   uint8
#define BOOL	uint8
#define ARRAY   uint8
#define SET     uint8
#define STRING  uint8
#define BCD     uint8
#define FILL    uint8
#define CHAR    uint8
#define UINT16  uint16
#define UINT32  uint32
#define INT32   int32

typedef union { uint8 b[2]; uint16 w; } u8_16_t, union16;
typedef union { uint8 b[4]; uint16 w[2]; uint32 l; } u8_32_t, union32;

#endif // TYPEDEF_H
