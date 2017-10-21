#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    FILE *fp;
    int count = 0;
    int a,b,c;
    char command[50];
 
 
    // Open the file
    fp = fopen(argv[1], "r");
 
    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", argv[1]);
        return 0;
    }
    
 
    // Extract characters from file and store in character c
    while ((fscanf(fp,"%d %d %d\n",&a,&b,&c)) != -1) {
            //printf("Line : %d ",a);
            sprintf(command, "awk \'FNR>=%d && FNR<=%d\' alfabeto11.txt",a,a);
            //printf("Command : %s\n",command);
            system(command);
            count = count + 1;
    }

    // Close the file
    fclose(fp);

    printf("The file %s has %d lines\n", argv[1], count);
 
    return 0;
}
