#include<stdio.h>
#include "cs.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

/* x = x + beta * A(:,j), where x is a dense vector and A(:,j) is sparse */
csi cs_scatter_2 (const cs *A, csi j, double beta, csi *w, double *x, csi mark,
    cs *C, csi nz)
{
    csi i, p, *Ap, *Ai, *Ci ;
    double *Ax ;
    if (!CS_CSC (A) || !w || !CS_CSC (C)) return (-1) ;     /* check inputs */
    Ap = A->p ; Ai = A->i ; Ax = A->x ; Ci = C->i ;
    for (p = Ap [j] ; p < Ap [j+1] ; p++)
    {
        i = Ai [p] ;                            /* A(i,j) is nonzero */
        if (w [i] < mark)
        {
            w [i] = mark ;                      /* i is new entry in column j */
            Ci [nz++] = i ;                     /* add i to pattern of C(:,j) */
            if (x) x [i] = beta + Ax [p] ;      /* x(i) = beta*A(i,j) */
        }
        else if (x) x [i] =  MIN( x[i],(beta + Ax [p])) ; /* i exists in C(:,j) already */
    }
    return (nz) ;
}


cs *cs_multiply_2 (const cs *A, const cs *B)
{
    csi p, j, nz = 0, anz, *Cp, *Ci, *Bp, m, n, bnz, *w, values, *Bi ;
    double *x, *Bx, *Cx ;
    cs *C ;
    if (!CS_CSC (A) || !CS_CSC (B)) return (NULL) ;      /* check inputs */
    if (A->n != B->m) return (NULL) ;
    m = A->m ; anz = A->p [A->n] ;
    n = B->n ; Bp = B->p ; Bi = B->i ; Bx = B->x ; bnz = Bp [n] ;
    w = cs_calloc (m, sizeof (csi)) ;                    /* get workspace */
    values = (A->x != NULL) && (Bx != NULL) ;
    x = values ? cs_malloc (m, sizeof (double)) : NULL ; /* get workspace */
    C = cs_spalloc (m, n, anz + bnz, values, 0) ;        /* allocate result */
    if (!C || !w || (values && !x)) return (cs_done (C, w, x, 0)) ;
    Cp = C->p ;
    for (j = 0 ; j < n ; j++)
    {
        if (nz + m > C->nzmax && !cs_sprealloc (C, 2*(C->nzmax)+m))
        {
            return (cs_done (C, w, x, 0)) ;             /* out of memory */
        } 
        Ci = C->i ; Cx = C->x ;         /* C->i and C->x may be reallocated */
        Cp [j] = nz ;                   /* column j of C starts here */
        for (p = Bp [j] ; p < Bp [j+1] ; p++)
        {
            nz = cs_scatter_2 (A, Bi [p], Bx ? Bx [p] : 999999, w, x, j+1, C, nz) ;
        }
        if (values) for (p = Cp [j] ; p < nz ; p++) Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    cs_sprealloc (C, 0) ;               /* remove extra space from C */
    return (cs_done (C, w, x, 1)) ;     /* success; free workspace, return C */
}

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

cs *cs_load_2 (FILE *f, double columns)
{
    double i, j ;   /* use double for integers to avoid csi conflicts */
    double x ;
    int esta=0;

    cs *T ;
    if (!f) return (NULL) ;                             /* check inputs */
    T = cs_spalloc (0, 0, 1, 1, 1) ;                    /* allocate result */
    while (fscanf (f, "%lg %lg %lg\n", &i, &j, &x) == 3)
    {
        if(x==columns) esta=1;
        if (!cs_entry (T, (csi) i, (csi) j, x)) return (cs_spfree (T)) ;
    }
    if(esta==0) // No esta la entrada la pongo a mano;
              cs_entry (T,(csi)columns,(csi)0,(double) 999999);
    return (T) ;
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
    columns = (AC->m)-1;
    B = cs_load_2 (g,columns);
    BC = cs_compress (B) ;


    C = cs_multiply_2(AC,BC);

    cs_print_2(C, 0) ;

    cs_spfree (A) ;                     
    cs_spfree (B) ;
    cs_spfree (C) ;
    fclose(f);
    fclose(g);
    return (0) ;
}
