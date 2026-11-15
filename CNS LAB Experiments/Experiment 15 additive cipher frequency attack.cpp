#include <stdio.h>
#include <ctype.h>
#include <string.h>
double score(char*s){char*f="ETAOINSHRDLU";double v=0;int n=0;for(int i=0;s[i];i++)if(isalpha(s[i])){char c=toupper(s[i]);for(int j=0;j<12;j++)if(c==f[j])v+=12-j;n++;}return n?v/n:0;}
int main(){char s[5000],t[5000];double sc[26];int top;fgets(s,5000,stdin);printf("Top candidates (1-26): ");scanf("%d",&top);if(top<1)top=1;if(top>26)top=26;for(int k=0;k<26;k++){strcpy(t,s);for(int i=0;t[i];i++)if(isalpha(t[i])){int b=islower(t[i])?'a':'A';t[i]=b+(t[i]-b-k+26)%26;}sc[k]=score(t);}for(int r=0;r<top;r++){int b=-1;for(int k=0;k<26;k++)if(sc[k]>=0&&(b<0||sc[k]>sc[b]))b=k;if(b<0)break;strcpy(t,s);for(int i=0;t[i];i++)if(isalpha(t[i])){int z=islower(t[i])?'a':'A';t[i]=z+(t[i]-z-b+26)%26;}printf("shift %d: %s",b,t);sc[b]=-1;}}
