#include <stdio.h>
#include <ctype.h>
int main(){char s[5000],order[]="ETAOINSHRDLUCMFPGWYBVKXJQZ";int f[26]={0},used[26]={0},map[26];fgets(s,sizeof s,stdin);for(int i=0;s[i];i++)if(isalpha(s[i]))f[toupper(s[i])-'A']++;for(int j=0;j<26;j++){int b=-1;for(int i=0;i<26;i++)if(!used[i]&&(b<0||f[i]>f[b]))b=i;used[b]=1;map[b]=order[j];}for(int i=0;s[i];i++)if(isalpha(s[i])){char c=map[toupper(s[i])-'A'];putchar(islower(s[i])?tolower(c):c);}else putchar(s[i]);puts("\n(Heuristic frequency estimate; manual refinement may be needed.)");}
