#include <stdio.h>
#include <ctype.h>
int main(){char s[1000];int k[1000],n=0,m,j=0;printf("1 Encrypt 2 Decrypt: ");scanf("%d",&m);getchar();fgets(s,1000,stdin);puts("Enter key numbers 0-25, one per letter, then -1:");while(n<999){scanf("%d",&k[n]);if(k[n]==-1)break;if(k[n]<0||k[n]>25)return puts("Invalid key"),1;n++;}for(int i=0;s[i];i++)if(isalpha(s[i])){if(j>=n)return puts("Not enough key values"),1;int b=islower(s[i])?'a':'A';s[i]=b+(s[i]-b+(m==1?k[j]:-k[j])+26)%26;j++;}printf("%s",s);}
