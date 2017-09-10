#ifndef AES_H
#define AES_H

/*
 * encrypt the passed message in place using the passed key and the
 * AES-128 algorithm as defined in FIPS PUB 197
 */
void AesEncrypt(unsigned char msg[16], unsigned char key[16]);

/*
 * decrypt the passed message in place using the passed key and the
 * AES-128 algorithm as defined in FIPS PUB 197
 */
void AesDecrypt(unsigned char msg[16], unsigned char key[16]);

#endif // AES_H
