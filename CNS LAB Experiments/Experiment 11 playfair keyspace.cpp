#include <stdio.h>
#include <math.h>
int main(){long double n=1;for(int i=1;i<=25;i++)n*=i;printf("Nominal key-square arrangements = 25! = %.0Lf\n",n);printf("log2(25!) = %.3Lf, so approximately 2^%.0Lf\n",log2l(n),log2l(n));puts("Some arrangements may be equivalent; the effective count depends on the equivalence rule used.");}
