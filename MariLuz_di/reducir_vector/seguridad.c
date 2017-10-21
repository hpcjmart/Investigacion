#include <stdio.h>

int main (int argc, char *argv[]) {
    char test[28];
    int a,b,c = 0;
    int i;
    FILE *vector = fopen(argv[1], "r");
    FILE *alfabeto = fopen(argv[2], "r");
    int haydos;

    while ((fscanf(vector,"%d %d %d\n",&a,&b,&c)) != -1) {

         int bytes = 29 * a;
         fseek (alfabeto, bytes, SEEK_SET);
         fgets(test, 28, alfabeto);
         haydos=0;
         for(i=0;i<28;i++)
             if(test[i]=='2'){haydos=1;break;}
         if (haydos==0) printf("%d %d %d\n",a,b,c);
         rewind(alfabeto);

    }

    fclose (alfabeto);
    fclose (vector);
    return 0;
}

