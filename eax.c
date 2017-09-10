#include "eax.h"

static unsigned char buffer[16];
static int buffer_idx;
static unsigned char key[16];
static unsigned char d_value[16];
static unsigned char q_value[16];
static unsigned char nonce[16];

/***********************************************************************************************
 * Description: Initiate a CMAC computation
 *
 * Inputs: key = 16 bytes key
 *         init_with = can be set to either 'D' or 'Q'
 ***********************************************************************************************/
void CMacStart(unsigned char *_key, char init_with)
{
    buffer_idx = 0;
    memcpy(key, _key, 16);
    memset(d_value, 0, 16);
    AesEncrypt(d_value, key);

    Dbl(d_value);
    memcpy(q_value, d_value, 16);
    Dbl(q_value);

    if (init_with == 'D')
    {
        memcpy(nonce, d_value, 16);
        PrintByteArrayMSB("key = ", key, 16);
        PrintByteArrayMSB("D =   ", d_value, 16);
        PrintByteArrayMSB("Q =   ", q_value, 16);
    }
    else
        memcpy(nonce, q_value, 16);
}

/***********************************************************************************************
 * Description: Add an array of bytes to the CMAC computation
 *
 * Inputs: byte = Array of bytes to be included in the CMAC computation
 ***********************************************************************************************/
void CMacNext(unsigned char *s, int lgn)
{
    int i, j;

    for (i=0; i<lgn; i++)
    {
        if (buffer_idx == 16)
        {
            //PrintByteArrayLSB("S =   ", buffer, 16);

            for(j=0; j<16; j++)
                nonce[j] ^= buffer[j];

            AesEncrypt(nonce, key);

            buffer_idx = 0;
        }

        buffer[buffer_idx++] = s[i];
        printf("%02x", s[i]);
    }
    printf("\n");
}

/***********************************************************************************************
 * Description: Complete the CMAC computation
 ***********************************************************************************************/
void CMacEnd(unsigned char *s)
{
    int i;

    if (buffer_idx == 16)
    {
        PrintByteArrayLSB("S =   ", buffer, 16);
        for(i=0; i<16; i++)
            buffer[i] ^= d_value[i];
    }
    else
    {
        buffer[buffer_idx++] = 0x80;
        for(i = buffer_idx; i < 16; i++)
            buffer[i] = 0;

        PrintByteArrayLSB("S =   ", buffer, 16);

        for(i=0; i<16; i++)
            buffer[i] ^= q_value[i];
    }

    for(i=0; i<16; i++)
	    nonce[i] ^= buffer[i];

    AesEncrypt(nonce, key);
    memcpy(s, nonce, 16);
}

/***********************************************************************************************
 * Description: Functions that encrypts or decrypt an array of bytes.
 *
 * Inputs: data = Pointer to the data which should be encrypted or decrypted
 *		   data_length = size of the data field in bytes
 *		   key = The pointer to the 16 bytes key used for the encryption
 ***********************************************************************************************/
void AesCtr(unsigned char *mykey, unsigned char *_nonce, unsigned char *data, int data_length)
{
    int i;
    unsigned char *ptr = data;
    unsigned char mynonce[16], encrypted_nonce[16];

    memcpy(mynonce, _nonce, 16);
    mynonce[1] &= 0x7F;
    mynonce[3] &= 0x7F;

    while (data_length > 0)
    {
        memcpy(encrypted_nonce, mynonce, 16);
        AesEncrypt(encrypted_nonce, mykey);

        for (i=0; i < 16; i++, ptr++)
        {
            if (data_length-- <= 0)
                return;
            *ptr ^= encrypted_nonce[i];
        }

        /* Incrementing the nouce */
        mynonce[15]++;
        if (mynonce[15] == 0)
        {
            mynonce[14]++;
            if (mynonce[14] == 0)
            {
                mynonce[13]++;
                if (mynonce[13] == 0)
                    mynonce[12]++;
            }
        }
    }
}

void AesCtrDe(unsigned char *mykey, unsigned char *_nonce, unsigned char *data, int data_length)
{
    int i;
    unsigned char *ptr = data;
    unsigned char mynonce[16], encrypted_nonce[16];

    memcpy(mynonce, _nonce, 16);
    mynonce[1] &= 0x7F;
    mynonce[3] &= 0x7F;

    while (data_length > 0)
    {
        memcpy(encrypted_nonce, mynonce, 16);
        AesDecrypt(encrypted_nonce, mykey);

        for (i=0; i < 16; i++, ptr++)
        {
            if (data_length-- <= 0)
                return;
            *ptr ^= encrypted_nonce[i];
        }

        /* Incrementing the nouce */
        mynonce[15]++;
        if (mynonce[15] == 0)
        {
            mynonce[14]++;
            if (mynonce[14] == 0)
            {
                mynonce[13]++;
                if (mynonce[13] == 0)
                    mynonce[12]++;
            }
        }
    }
}

void Dbl(unsigned char *x)
{
    int i;
    int carry = (x[15] & 0x80) != 0;

    for (i=15; i>0; i--)
    {
	    x[i] <<= 1;
	    if ((x[i-1] & 0x80) != 0)
		    x[i] |= 0x01;
    }
    x[0] <<= 1;

    if (carry)
	    x[0] ^= 0x87;
}

void PrintByteArrayMSB(char *text, unsigned char *mybuffer, int lgn)
{
#if (SW_SIMULATION == 1)
    int i;

    printf(text);

    for (i=lgn-1; i>=0; i--)
	    printf("%02x", mybuffer[i]);
    printf("\n");
#endif
}

void PrintByteArrayLSB(char *text, unsigned char *mybuffer, int lgn)
{
#if (SW_SIMULATION == 1)
    int i;

    printf(text);

    for (i=0; i<lgn; i++)
	    printf("%02x", mybuffer[i]);
    printf("\n");
#endif
}


void eaxTest()
{
    unsigned char tagN[16], tagC[16], T[16];
    int i;

    unsigned char testkey[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    unsigned char called_AP_title_uid[] = {0xA2,0x0C,0x06,0x0A,0x60,0x7C,0x86,0xF7,0x54,0x01,0x16,0x00,0x7B,0x02};
    unsigned char calling_AE_qualifier_element[] = {0xA7,0x03,0x02,0x01,0x04};
    unsigned char calling_AP_invocation_id_element[] = {0xA8,0x03,0x02,0x01,0x02};
    unsigned char calling_authentication_value[] = {0xAC,0x0F,0xA2,0x0D,0xA0,0x0B,0xA1,0x09};
    unsigned char key_id_element[] = {0x80,0x01,0x02};
    unsigned char iv_element[] = {0x81,0x04,0x48,0xF3,0xD2,0xF8};
    unsigned char user_information[] = {0xBE,0x19,0x28,0x17,0x81,0x15};
    unsigned char epsem_control[] = {0x9A};
    unsigned char calling_AP_title_uid[] = {0xA6,0x0D,0x06,0x0B,0x60,0x7C,0x86,0xF7,0x54,0x01,0x16,0x00,0x7B,0x82,0x11};
    unsigned char key_id[] = {0x02};
    unsigned char iv[] = {0x48,0xF3,0xD2,0xF8};
    unsigned char epsem_data[] = {0x54,0x45,0x4D,0x50,0x0B,0x40,0x00,0x07,0x00,0x05,0x1A,0x00,0x00,0x02,0x00,0xE4};

    PrintByteArrayMSB("********************", "", 0);
    CMacStart(testkey, 'D');
    CMacNext(called_AP_title_uid, sizeof(called_AP_title_uid));
    CMacNext(calling_AE_qualifier_element, sizeof(calling_AE_qualifier_element));
    CMacNext(calling_AP_invocation_id_element, sizeof(calling_AP_invocation_id_element));
    CMacNext(calling_authentication_value, sizeof(calling_authentication_value));
    CMacNext(key_id_element, sizeof(key_id_element));
    CMacNext(iv_element, sizeof(iv_element));
    CMacNext(user_information, sizeof(user_information));
    CMacNext(epsem_control, sizeof(epsem_control));
    CMacNext(calling_AP_title_uid, sizeof(calling_AP_title_uid));
    CMacNext(key_id, sizeof(key_id));
    CMacNext(iv, sizeof(iv));
    CMacEnd(tagN);
    PrintByteArrayMSB("Tag = ", tagN, 16);
    PrintByteArrayMSB("********************", "", 0);

    /* Encryption of the paylaod */
    AesCtr(testkey, tagN, epsem_data, sizeof(epsem_data));

    PrintByteArrayMSB("********************", "", 0);
    CMacStart(key, 'Q');
    CMacNext(epsem_data, sizeof(epsem_data));
    CMacEnd(tagC);
    PrintByteArrayMSB("Tag = ", tagC, 16);
    PrintByteArrayMSB("********************", "", 0);

    for (i=0; i<16; i++)
	    T[i] = tagN[i] ^ tagC[i];

    PrintByteArrayMSB("MAC = (Expected 0x1BD78F32) ", T+12, 4);

    //PrintByteArrayMSB("EPSEM = ", epsem_data, sizeof(epsem_data));
    //AesCtrDe(testkey, tagN, epsem_data, sizeof(epsem_data));
    //PrintByteArrayMSB("EPSEM = ", epsem_data, sizeof(epsem_data));
}
