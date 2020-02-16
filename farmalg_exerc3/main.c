#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {

 int start1,end1,start2,end2;
 scanf("%d", &start1);
 scanf("%d", &end1);
 scanf("%d", &start2);
 scanf("%d", &end2);

    if((end1 >= start2) ){
        printf("%d\n",end1 - start2 + 1);
         printf("%d %d",start2,end1 );
    }
    else{
        printf("0\n");
        printf("nulo");

    }
 return 0;
}
