#include<stdio.h>
#include "cs.h"

csi cs_print_2 (const cs *A, csi brief)
{
    csi p, j, m, n, nzmax, nz, *Ap, *Ai ;
    double *Ax ;
    if (!A) { printf ("(null)\n") ; return (0) ; }
    m = A->m ; n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    nzmax = A->nzmax ; nz = A->nz ;
    //printf ("CSparse Version %d.%d.%d, %s.  %s\n", CS_VER, CS_SUBVER,
    //    CS_SUBSUB, CS_DATE, CS_COPYRIGHT) ;
    if (nz < 0)
    {
        //printf ("%g-by-%g, nzmax: %g nnz: %g, 1-norm: %g\n", (double) m,
        //    (double) n, (double) nzmax, (double) (Ap [n]), cs_norm (A)) ;
        for (j = 0 ; j < n ; j++)
        {
            //printf ("    col %g : locations %g to %g\n", (double) j,
            //    (double) (Ap [j]), (double) (Ap [j+1]-1)) ;
            for (p = Ap [j] ; p < Ap [j+1] ; p++)
            {
                if(Ax[p]>=999999) continue;
                printf ("%g 0 %g\n", (double) (Ai [p]), Ax ? Ax [p] : 1) ;
                if (brief && p > 20) { printf ("  ...\n") ; return (1) ; }
            }
        }
    }
    else
    {
        //printf ("triplet: %g-by-%g, nzmax: %g nnz: %g\n", (double) m,
        //    (double) n, (double) nzmax, (double) nz) ;
        for (p = 0 ; p < nz ; p++)
        {
            if(Ax[p]>=999999) continue;
            printf ("%g %g %g\n", (double) (Ai [p]), (double) (Ap [p]),
                Ax ? Ax [p] : 1) ;
            if (brief && p > 20) { printf ("  ...\n") ; return (1) ; }
        }
    }
    return (1) ;
}



int main (int argc, char *argv[])
{
    cs  *A, *B, *C, *D;
    cs  *AC, *BC;
    csi i, m ;
    csi columns;
    FILE *f, *g;
    f = fopen(argv[1],"r");
    g = fopen(argv[2],"r");

    A = cs_load (f) ;               
    AC = cs_compress (A) ;
    B = cs_load (g);
    BC = cs_compress (B) ;


    C = cs_add(AC,BC,1.0,-1.0);

    cs_print_2(C, 0) ;

    cs_spfree (A) ;                     
    cs_spfree (B) ;
    cs_spfree (C) ;
    fclose(f);
    fclose(g);
    return (0) ;
}
