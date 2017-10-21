#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void search(char *pat, char *txt, int *exit, int *where)
{
    int M = strlen((const char *)pat);
    int N = strlen((const char *)txt);
    int i,j;
    int x;
    
    *exit=0;
    *where=0;
 
    /* A loop for 'pat' */
    for (i = 0; i <= N-M+1; i++) 
    {
 
       /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
        {
              if (txt[i+j] != pat[j])
              break;
        }
 
        if (j == M) 
        {
         //printf( "Pattern (" );
         //for( x = 0; x < M; x++) printf("%c", pat[x]);  
         //printf(") found at index %d \n", i+1);
         *exit=1;
         *where=i+1;
         break; //Si quitamos esto, encuentra todas las veces que aparece la cadena (ojo)
        }
 
    }
}


void copia2(char *txt, char *txt_ext2)
{
    int M = strlen((const char *)txt);
    int N = M+2;
    int i,j;
    
    for(j = 0; j < N; j++) txt_ext2[j] = '0'; //Incializado vector
    txt_ext2[0]=txt[M-1];
    txt_ext2[N-1]=txt[0];
    for(i = 0; i < M; i++) txt_ext2[i+1]=txt[i];
}
    
void copia4(char *txt, char *txt_ext4)
{
    int M = strlen((const char *)txt);
    int N = M+4;
    int i,j;

    for(j = 0; j < N; j++) txt_ext4[j] = '0'; //Incializado vector
    txt_ext4[0]=txt[M-2];
    txt_ext4[1]=txt[M-1];
    txt_ext4[N-1]=txt[1];
    txt_ext4[N-2]=txt[0];
    for(i = 0; i < M; i++) txt_ext4[i+2]=txt[i];
}

void copia6(char *txt, char *txt_ext6)
{
    int M = strlen((const char *)txt);
    int N = M+6;
    int i,j;

    for(j = 0; j < N; j++) txt_ext6[j] = '0'; //Incializado vector
    txt_ext6[0]=txt[M-3];
    txt_ext6[1]=txt[M-2];
    txt_ext6[2]=txt[M-1];
    txt_ext6[N-1]=txt[2];
    txt_ext6[N-2]=txt[1];
    txt_ext6[N-3]=txt[0];
    for(i = 0; i < M; i++) txt_ext6[i+3]=txt[i];
}
 

int main(int argc, char *argv[]){

   FILE *f;
   int x;
   char c[]  =    "00000000000";
   char cc[] = "00000000000000000";
   int *vector;
   int exit=0;
   int where=0;

   int desde=0,hasta=atoi(argv[2]);
   int numero_ceros=0;

   int longitud_cadena=atoi(argv[3]);
   vector=(int *)malloc(hasta*sizeof(int));


   char pat1[] = "111";
   char pat12[] = "113";
   char pat13[] = "311";
   char pat14[] = "313";
   char pat2[] = "21";
   char pat3[] = "12";
   char pat4[] = "23";
   char pat5[] = "32";
   
   int noinfinito=0;


   f = fopen(argv[1],"r");

   for(desde=0;desde<hasta;desde++){
     fscanf(f, "%c %c %c %c %c %c %c %c %c %c %c\n", &c[0],&c[1],&c[2],&c[3],&c[4],&c[5],&c[6],&c[7],&c[8],&c[9],&c[10]);
     copia6(c,cc);
     search(pat1, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat12, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat13, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat14, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat2, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat3, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat4, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     search(pat5, cc, &exit, &where);
     if(exit==1){vector[desde]=999;continue;}
     
     noinfinito++;

     numero_ceros=0;
     for(x=0;x<longitud_cadena;x++){
        if(c[x]=='0')
        numero_ceros++;
     }
     vector[desde]=numero_ceros; 

     //printf("\n");
     //for(x = 0; x < longitud_cadena; x++) printf("%c ", c[x]);
     //printf("%d\t%d\t%d\n",desde,1,numero_ceros);

   }


   //printf("\n");
   //for(x = 0; x < hasta; x++) printf("vector[%d] =  %d\n", x,vector[x]);

   //printf("\n");
   //printf("No infinito = %d\n",noinfinito);

   //printf("%d\t%d\t%d\n",hasta,1,noinfinito);
   for(x = 0; x < hasta; x++) 
      if(vector[x]!=999) printf("%d %d %d\n",x,0,vector[x]);

   fclose(f);

   return 0;
}
