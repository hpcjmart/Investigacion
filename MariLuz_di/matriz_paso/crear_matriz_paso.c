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
   FILE *f1;

   int x;
   char p[]  =   "00000000000000000";
   char p4[] = "000000000000000000000";


   char q[]  =   "00000000000000000";
   char q4[] = "000000000000000000000";

   int exit=0;
   int where=0;

   int m1=0,m2=0,hasta=atoi(argv[2]);
   int numero_ceros=0;

   int longitud_cadena=atoi(argv[3]);

   int noinfinito=0;

   int i,j; 
   i=2;j=2+longitud_cadena;
   int posicion;
   int siguiente;

   //printf("La palabra es de longitud %d \n",longitud_cadena);
   //printf("Extendida hasta %d \n",longitud_cadena+4);
   //printf("Recorremos la palabra desde %d hasta %d\n",i,j);

   f = fopen(argv[1],"r");
   f1 = fopen(argv[1],"r");

   for(m1=0;m1<hasta;m1++){

     fscanf(f, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", 
                &q[0],&q[1],&q[2],&q[3],&q[4],&q[5],&q[6],&q[7],&q[8],&q[9],&q[10],&q[11],&q[12],&q[13],&q[14],&q[15],&q[16]);
     copia4(q,q4);
     rewind(f1);


     for(m2=0;m2<hasta;m2++){

     fscanf(f1, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n",
                &p[0],&p[1],&p[2],&p[3],&p[4],&p[5],&p[6],&p[7],&p[8],&p[9],&p[10],&p[11],&p[12],&p[13],&p[14],&p[15],&p[16]);

        copia4(p,p4);
  
        siguiente=0;

        for(posicion=i;posicion<j;posicion++) {

            if(q4[posicion]=='0'){
               if(p4[posicion]=='0') {siguiente=1;break;}
               if(p4[posicion]=='2') {siguiente=1;break;}
            }
            if(q4[posicion]=='1'){
               if((p4[posicion-1]=='1')&&(p4[posicion]=='1')&&(p4[posicion+1]=='1')) {siguiente=1;break;}
               if((p4[posicion-1]=='2')&&(p4[posicion]=='1')&&(p4[posicion+1]=='1')) {siguiente=1;break;}
               if((p4[posicion-1]=='1')&&(p4[posicion]=='1')&&(p4[posicion+1]=='2')) {siguiente=1;break;}
               if((p4[posicion-1]=='2')&&(p4[posicion]=='1')&&(p4[posicion+1]=='2')) {siguiente=1;break;}
            }
            if(q4[posicion]=='2'){
               if(p4[posicion]=='1') {siguiente=1;break;}
               if(p4[posicion]=='2') {siguiente=1;break;}
            }
            
       } 
       if(siguiente==0){
         //Contamos los ceros y ponemos el valor en la matriz
         numero_ceros=0;
         for(x=i;x<j;x++) if(p4[x]=='0') numero_ceros++;
         //matriz_paso[m2][m1]=numero_ceros;
         printf("%d %d %d\n",m2,m1,numero_ceros);
       }//else matriz_paso[m2][m1]=999;


     }


   }


   fclose(f);
   fclose(f1);

   return 0;
}
