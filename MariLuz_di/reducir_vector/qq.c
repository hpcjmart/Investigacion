#include <stdio.h>

int main (int argc, char *argv[]) {
    char test[12];
    int a,b,c = 0;
    int i;
    FILE *vector = fopen(argv[1], "r");
    FILE *alfabeto = fopen(argv[2], "r");
    int haydos;

    while ((fscanf(vector,"%d %d %d\n",&a,&b,&c)) != -1) {

         int bytes = 13 * a;
         fseek (alfabeto, bytes, SEEK_SET);
         fgets(test, 12, alfabeto);
         haydos=0;
         for(i=0;i<12;i++)
             if(test[i]=='2'){haydos=1;break;}
         if (haydos==0) printf("%d %d %d\n",a,b,c);
         rewind(alfabeto);

    }

    fclose (alfabeto);
    fclose (vector);
    return 0;
}

