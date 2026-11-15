/* OpenSSL libcrypto required. AES-128-CBC is a modern alternative stronger than DES. */
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
int main(){unsigned char k[16],iv[16],in[2048],out[2100],dec[2100];int n,m,t;printf("Plaintext: ");fgets((char*)in,sizeof in,stdin);n=strlen((char*)in);if(!RAND_bytes(k,16)||!RAND_bytes(iv,16))return 1;EVP_CIPHER_CTX*c=EVP_CIPHER_CTX_new();EVP_EncryptInit_ex(c,EVP_aes_128_cbc(),0,k,iv);EVP_EncryptUpdate(c,out,&m,in,n);t=m;EVP_EncryptFinal_ex(c,out+t,&m);t+=m;EVP_CIPHER_CTX_free(c);printf("IV: ");for(int i=0;i<16;i++)printf("%02X",iv[i]);printf("\nCiphertext: ");for(int i=0;i<t;i++)printf("%02X",out[i]);c=EVP_CIPHER_CTX_new();EVP_DecryptInit_ex(c,EVP_aes_128_cbc(),0,k,iv);EVP_DecryptUpdate(c,dec,&m,out,t);n=m;EVP_DecryptFinal_ex(c,dec+n,&m);n+=m;dec[n]=0;EVP_CIPHER_CTX_free(c);printf("\nDecrypted: %s",dec);}
