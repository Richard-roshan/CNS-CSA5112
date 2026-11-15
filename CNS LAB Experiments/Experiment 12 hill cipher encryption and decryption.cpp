#include <stdio.h>
#include <ctype.h>
int inv(int a){for(int i=1;i<26;i++)if(a*i%26==1)return i;return -1;}
int main(){char s[1000];int n=0;int a=9,b=4,c=5,d=7,det=(a*d-b*c)%26;if(det<0)det+=26;int di=inv(det);if(di<0)return puts("Key not invertible"),1;int A=d*di%26,B=(26-b*di%26)%26,C=(26-c*di%26)%26,D=a*di%26;fgets(s,1000,stdin);for(int i=0;s[i];i++)if(isalpha(s[i]))s[n++]=toupper(s[i]);if(n%2)s[n++]='X';printf("Encrypted: ");for(int i=0;i<n;i+=2){int x=s[i]-65,y=s[i+1]-65;printf("%c%c",(9*x+4*y)%26+65,(5*x+7*y)%26+65);}printf("\nInverse matrix: [%d %d; %d %d]\nDecrypted: ",A,B,C,D);for(int i=0;i<n;i+=2){int x=((9*(s[i]-65)+4*(s[i+1]-65))%26),y=((5*(s[i]-65)+7*(s[i+1]-65))%26);printf("%c%c",(A*x+B*y)%26+65,(C*x+D*y)%26+65);}puts("");}
