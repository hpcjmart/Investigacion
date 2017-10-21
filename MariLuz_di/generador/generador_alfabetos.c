#include<stdio.h>
#include<string.h>
#include "_generate.h"
 
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

void copia8(char *txt, char *txt_ext8)
{
    int M = strlen((const char *)txt);
    int N = M+8;
    int i,j;

    for(j = 0; j < N; j++) txt_ext8[j] = '0'; //Incializado vector
    txt_ext8[0]=txt[M-4];
    txt_ext8[1]=txt[M-3];
    txt_ext8[2]=txt[M-2];
    txt_ext8[3]=txt[M-1];
    txt_ext8[N-1]=txt[3];
    txt_ext8[N-2]=txt[2];
    txt_ext8[N-3]=txt[1];
    txt_ext8[N-4]=txt[0];
    for(i = 0; i < M; i++) txt_ext8[i+4]=txt[i];
}

 
int main()
 
 {
   char m = 3; //Longitud alfabeto
   char n = 10; //Longitud palabra
   char txt[]      =     "0000000000";
   char txt_ext2[] =    "000000000000";
   char txt_ext4[] =   "00000000000000";
   char txt_ext6[] =  "0000000000000000";
   char txt_ext8[] = "000000000000000000";

   //Apartado a) de las condiciones

   char pat1[] = "00";
   char pat2[] = "22";

   //Apartado c) de las condiciones
   char pat70[] = "1111";
   char pat71[] = "1112";
   char pat72[] = "2111";
   char pat73[] = "2112";

   int gen_result;         //return value of generation functions
   unsigned int set_counter;        //counting generated sequences
   int x;                  //iterator

   set_counter = 0;
   //printf("vari_rep_lex(%d, %d)\n", m, n);
   gen_result = gen_vari_rep_lex_init(txt, m, n);
   copia2(txt,txt_ext2);
   copia4(txt,txt_ext4);
   copia6(txt,txt_ext6);
   copia8(txt,txt_ext8);

   if(gen_result == GEN_EMPTY)
   {
   set_counter++;
   //printf("{} (%u)\n", set_counter);
   }
  
   int exit=0;
   int where=0;

   while(gen_result == GEN_NEXT)
   {
    set_counter++;

    search(pat1, txt_ext2, &exit, &where);   
    if(exit==1){
      gen_result = gen_vari_rep_lex_next(txt, m, n);
      copia2(txt,txt_ext2);
      copia4(txt,txt_ext4);
      copia6(txt,txt_ext6);
      copia8(txt,txt_ext8);
      continue;   
    }
    search(pat2, txt_ext2, &exit, &where);
    if(exit==1){
      gen_result = gen_vari_rep_lex_next(txt, m, n);
      copia2(txt,txt_ext2);
      copia4(txt,txt_ext4);
      copia6(txt,txt_ext6);
      copia8(txt,txt_ext8);
      continue;
    }

    search(pat70, txt_ext6, &exit, &where);
    if(exit==1){
      gen_result = gen_vari_rep_lex_next(txt, m, n);
      copia2(txt,txt_ext2);
      copia4(txt,txt_ext4);
      copia6(txt,txt_ext6);
      copia8(txt,txt_ext8);
      continue;
    }

    search(pat71, txt_ext6, &exit, &where);
    if(exit==1){
      gen_result = gen_vari_rep_lex_next(txt, m, n);
      copia2(txt,txt_ext2);
      copia4(txt,txt_ext4);
      copia6(txt,txt_ext6);
      copia8(txt,txt_ext8);
      continue;
    }

    search(pat72, txt_ext6, &exit, &where);
    if(exit==1){
      gen_result = gen_vari_rep_lex_next(txt, m, n);
      copia2(txt,txt_ext2);
      copia4(txt,txt_ext4);
      copia6(txt,txt_ext6);
      copia8(txt,txt_ext8);
      continue;
    }

    search(pat73, txt_ext6, &exit, &where);
    if(exit==1){
      gen_result = gen_vari_rep_lex_next(txt, m, n);
      copia2(txt,txt_ext2);
      copia4(txt,txt_ext4);
      copia6(txt,txt_ext6);
      copia8(txt,txt_ext8);
      continue;
    }


//#ifdef PRINT
    for(x = 0; x < n; x++) printf("%c ", txt[x]);
    printf("\n");
//#endif

    gen_result = gen_vari_rep_lex_next(txt, m, n);
    copia2(txt,txt_ext2);
    copia4(txt,txt_ext4);
    copia6(txt,txt_ext6);
    copia8(txt,txt_ext8);

   }// Del While

   return 0;
}
