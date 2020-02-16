#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, x;
    char nome[30][30];
        for(i=0;i<5;i++){
           printf("Digite um nome: ");
           gets(nome[i]);
        }

        for(i=0; i< 4; i++){
            for(j=0; j<5; j++){
            if(nome[i][j]>nome[i][j]){
                x=nome[i][j];
                nome[i][j]=nome[i][j];
                nome[i][j]=x;

                }
            }
        }

         for (i=0;i<5;i++){
            for(j=0;j<5;j++){
               printf("%s",nome[i][j]);
            }
        }
        getchar();
}
