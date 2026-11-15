/* OpenSSL libcrypto required. DES is obsolete; classroom demonstration only. */
#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
int main(){char k[9]={0},b[9]={0};DES_cblock key,in,out;DES_key_schedule ks;printf("8-char key: ");scanf("%8s",k);printf("8-char ciphertext block: ");scanf("%8s",b);memcpy(key,k,8);memcpy(in,b,8);if(DES_set_key_checked(&key,&ks))return puts("Invalid or weak DES key"),1;DES_ecb_encrypt(&in,&out,&ks,DES_DECRYPT);printf("Plaintext bytes: ");for(int i=0;i<8;i++)printf("%02X ",out[i]);puts("");}
