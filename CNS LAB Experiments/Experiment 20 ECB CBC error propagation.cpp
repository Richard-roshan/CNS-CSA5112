#include <stdio.h>
#include <stdint.h>
unsigned char E(unsigned char x){return (unsigned char)(x*5u+7u);}unsigned char D(unsigned char x){return (unsigned char)(((x-7u)*205u)&255u);}
int main(){unsigned char p[4]={10,20,30,40},e[4],c[4],o[4],iv=99,prev=iv;for(int i=0;i<4;i++)e[i]=E(p[i]);for(int i=0;i<4;i++){c[i]=E(p[i]^prev);prev=c[i];}e[1]^=1;for(int i=0;i<4;i++)o[i]=D(e[i]);printf("ECB after C1 bit error: ");for(int i=0;i<4;i++)printf("%u ",o[i]);c[1]^=1;prev=iv;for(int i=0;i<4;i++){o[i]=D(c[i])^prev;prev=c[i];}printf("\nCBC after C1 bit error: ");for(int i=0;i<4;i++)printf("%u ",o[i]);puts("\nToy 8-bit transform only: ECB damages corresponding block; CBC damages current and next plaintext block for a ciphertext bit error.");}
