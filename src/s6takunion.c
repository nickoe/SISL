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
 * $Id: s6takunion.c,v 1.1 1994-04-21 12:10:42 boh Exp $
 *
 */


#define S6TAKEUNION

#include "sislP.h"

#if defined(SISLNEEDPROTOTYPES)
void s6takeunion(double evec1[],int ielem1,double evec2[],int ielem2,
		 double **gunion,int *jnmbelem,int *jstat)
#else	 
void s6takeunion(evec1,ielem1,evec2,ielem2,gunion,jnmbelem,jstat)
     int ielem1,ielem2,*jnmbelem,*jstat;
     double evec1[],evec2[],**gunion;
#endif     
/*
*********************************************************************
*                                                                   
* PURPOSE    : Take the union between two sorted double vectors. Identical 
*              elements in the two vectors are only represented once. 
*              If several elements in one array are equal, all are
*              represented.
*
*
* INPUT      : evec1    - First vector.
*              ielem1   - Number of elements of evec1.
*              evec2    - Second vector.
*              ielem2   - Number of elements of evec2.
*                       
*
* OUTPUT     : gunion   - Union vector.
*              jnmbelem - Number of elements of gunion.
*              jstat    - status messages  
*                                         > 0      : warning
*                                         = 0      : ok
*                                         < 0      : error
*
*
* METHOD     : 
*
* REFERENCES : 
*
* USE        : 
*
*-
* CALLS      : 
*
* WRITTEN BY : Vibeke Skytt, SI, 06.90.
*
*********************************************************************
*/
{
  int knelem;
  int knunion;
  double *sunion = NULL;
  double *s1,*s1stop;
  double *s2,*s2stop;
  
  /* Make local array to store the union of the vectors.  */

  knelem = ielem1 + ielem2;
  if ((sunion = newarray(knelem,DOUBLE)) == NULL) goto err101;
  
  /* Produce union vector. */

  for (s1=evec1,s1stop=s1+ielem1,s2=evec2,s2stop=s2+ielem2,knunion=0; 
       s1<s1stop && s2<s2stop;)
      {
	if (*s1 < *s2)
	  sunion[knunion++] = *s1++;
	else if (*s2 < *s1)
	  sunion[knunion++] = *s2++;
	else
	  {
	    sunion[knunion++] = *s1++;
	    s2++;
	  }
      }

  for (; s1<s1stop; s1++,knunion++)
    sunion[knunion] = *s1;

  for (; s2<s2stop; s2++,knunion++)
    sunion[knunion] = *s2;
  
  /* Allocate scratch for output union vector.  */

  *gunion = NULL;
  if ((*gunion = newarray(knunion,DOUBLE)) == NULL) goto err101;
  
  /* Copy union vector to output vector.  */

  memcopy(*gunion,sunion,knunion,DOUBLE);
  *jnmbelem = knunion;
  
  /* Union found.  */

  *jstat = 0;
  goto out;
  
  /* Error in scratch allocation.  */

  err101 :
    *jstat = -101;
  goto out;
  
  out :
    /* Free scratch occupied by local array.  */

    if (sunion != NULL) freearray(sunion);
  
  return;
}