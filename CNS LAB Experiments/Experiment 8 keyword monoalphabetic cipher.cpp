#include <stdio.h>
#include <ctype.h>
int main(){char k[100],a[27],s[1000];int u[26]={0},n=0,m;scanf("%99s",k);for(int i=0;k[i];i++){int x=toupper(k[i])-'A';if(x>=0&&x<26&&!u[x])u[x]=1,a[n++]=x+65;}for(int i=0;i<26;i++)if(!u[i])a[n++]=i+65;a[26]=0;printf("Cipher alphabet %s\n1 Encrypt 2 Decrypt: ",a);scanf("%d",&m);getchar();fgets(s,1000,stdin);for(int i=0;s[i];i++)if(isalpha(s[i])){int x=toupper(s[i])-'A',y=x;if(m==1)y=a[x]-65;else for(y=0;y<26&&a[y]-65!=x;y++);s[i]=(islower(s[i])?'a':'A')+y;}printf("%s",s);}
