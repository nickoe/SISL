/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* (c) Copyright 1989,1990,1991,1992 by                                      */
/*     Senter for Industriforskning, Oslo, Norway                            */
/*     All rights reserved. See the copyright.h for more details.            */
/*                                                                           */
/*****************************************************************************/

#include "copyright.h"

/*
 *
 * $Id: s1989.c,v 1.1 1994-04-21 12:10:42 boh Exp $
 *
 */


#define S1989

#include "sislP.h"                                                 


#if defined(SISLNEEDPROTOTYPES)
void s1989(SISLSurf *ps,double **emax,double **emin,int *jstat)
#else
void s1989(ps,emax,emin,jstat)
     SISLSurf *ps;
     double **emax;
     double **emin;
     int   *jstat;
#endif
/*
*********************************************************************
*
*********************************************************************
*                                                                   
* PURPOSE    : Find the bounding box of the SISLSurf. NB. The geometric
*              bounding box is returned also in the rational case, that
*              is the box in homogenous coordinates is NOT computed.
*
*
* INPUT      : ps        - SISLSurface to treat.
*
* OUTPUT     : emin      - Array of dimension idim containing
*                          the minimum values of the bounding box,
*                          i.e. down-left corner of the box.
*              emax      - Array of dimension idim containing
*                          the maximum values of the bounding box,
*                          i.e. top-right corner of the box.
*              jstat     - status messages  
*                                         > 0      : warning
*                                         = 0      : ok
*                                         < 0      : error
*                                                                     
*
*
* METHOD     :
*
*
* REFERENCES :
*
* CALLS      :
*
* WRITTEN BY : Christophe Rene Birkeland, SINTEF Oslo, July 1993.
*
*********************************************************************
*/                                     
{
  int i,j;                          /* Loop control variables    */
  int kpos = 0;                     /* Position of error.        */
  int bsdim;
  int len;
  int in = ps->in1 * ps->in2;
  double *coeff;
  double *minim=NULL;
  double *maxim=NULL;

  /* initialize variables */

  bsdim = ps->idim;
  coeff = ps->ecoef;
  len = bsdim;

  minim = newarray(bsdim, DOUBLE);
  maxim = newarray(bsdim, DOUBLE);
  if(minim == NULL || maxim == NULL) goto err101;

  for(j=0; j<bsdim; j++)
    {
      minim[j] = coeff[j];
      maxim[j] = coeff[j];
    }
  for(i=1, len=bsdim; i<in; i++, len+=bsdim)
    for(j=0; j<bsdim; j++)
      {
	minim[j] = MIN(minim[j], coeff[len+j]);
	maxim[j] = MAX(maxim[j], coeff[len+j]);
      }
  *emin = minim;
  *emax = maxim;      

  /* Success ! */
  
  *jstat = 0;
  goto out;
  
  
  /* Error in space allocation.  */
  
  err101: 
    *jstat = -101;
    s6err("s1989",*jstat,kpos);
    goto out;
  
  out: 
    return;
}