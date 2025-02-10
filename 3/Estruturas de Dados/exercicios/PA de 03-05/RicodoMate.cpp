#include <iostream>
#include <cmath>

using namespace std;
 
int main(void) {
   
   int n, l, q, lx, ly, qx, qy;
   char s[100][100];
   int i,r;

   scanf("%d %d.%d %d.%d", &n, &lx, &ly, &qx, &qy);
   l = lx * 10 + ly;
   q = qx * 10 + qy;

   for (int i = 0; i < n; i++){
       scanf("%s",s[i]);
   }
    r = l % q;

   printf("%s %.1lf\n",s[((int)ceil((double)l / q)-1) % n],(r ? r /10. : q / 10.));
 
    return 0;
}