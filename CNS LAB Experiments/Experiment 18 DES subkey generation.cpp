/* OpenSSL libcrypto required. */
#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
int main(){char k[9]={0};DES_cblock key;DES_key_schedule ks;printf("8-char DES key: ");scanf("%8s",k);memcpy(key,k,8);if(DES_set_key_checked(&key,&ks))return puts("Invalid/weak key"),1;for(int i=0;i<16;i++){unsigned long long v=0;for(int j=0;j<8;j++)v=(v<<8)|ks.ks[i].deslong[j];v>>=16;printf("K%d %012llX | %06llX %06llX\n",i+1,v,(v>>24)&0xffffffULL,v&0xffffffULL);}}
