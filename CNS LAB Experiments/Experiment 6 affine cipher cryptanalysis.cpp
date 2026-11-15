#include <stdio.h>
#include <ctype.h>
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main(){char s[5000];int f[26]={0};puts("Paste ciphertext:");fgets(s,sizeof s,stdin);for(int i=0;s[i];i++)if(isalpha(s[i]))f[toupper(s[i])-'A']++;puts("Assuming B and U represent the two most frequent plaintext letters E and T, test affine keys satisfying E->B and T->U:");for(int a=0;a<26;a++)if(gcd(a,26)==1){int b=(1-a*4%26+26)%26;if((a*19+b)%26==20)printf("candidate a=%d b=%d\n",a,b);}puts("Frequency assumptions alone may not uniquely identify the key; inspect candidate decryptions.");}
