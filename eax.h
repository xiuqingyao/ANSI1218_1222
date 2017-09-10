#ifndef EAX_H
#define EAX_H

#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "aes.h"

void CMacStart(unsigned char *, char);
void CMacNext(unsigned char *, int);
void CMacEnd(unsigned char *);
void AesCtr(unsigned char *, unsigned char *, unsigned char *, int);
void Dbl(unsigned char *);
void PrintByteArrayMSB(char *, unsigned char *, int);
void PrintByteArrayLSB(char *, unsigned char *, int);

void eaxTest();

#endif // EAX_H
