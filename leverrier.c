#include <stdio.h>
#include <stdlib.h>
#include "fonctionUtile.h"


float ** calculPuissanceEtTrace(float ** matA, int taille,float * trace, int degre)
{
  if (degre == 1)
    {
      trace[0] = calculDeLaTrace(matA,taille);
      printf("La trace pour matA de puissance %d est : %f \n", degre,trace[degre-1]);
      return matA;
    
    }
  else
    {
      float ** matB = calculPuissanceEtTrace(matA,taille,trace,degre-1);
      float ** matC = prodMatrice2D(matA,matB,taille);
      
      if(degre != 2)
	{
	  freeMatrice2D(matB,taille);
	}
      trace[degre-1] = calculDeLaTrace(matC,taille);
      printf("La trace pour matA de puissance %d est : %f \n", degre,trace[degre-1]);
      return matC;
    }
}

float* Leverrier(float * ensembleTrace, int taille)
{
  float coeff;
  float* polynome = malloc(sizeof(float)*(taille+1));
  polynome[0] = taille%2 ?-1:1;
  for(int i = 1; i < taille+1; i++)
    {
      coeff = 0;
	for(int j = 0; j < i; j++)
	{
	  coeff -= polynome[j]*ensembleTrace[i-(j+1)];
	}
	polynome[i] = (float) coeff/i;
    }
  free(ensembleTrace);
  return polynome;
}

int main()
{
  int taille;
 
  printf("Donner la taille de la matrice\n");
  scanf("%d",&taille);
   float** matA = matrice2D(taille);
  for (int i = 0; i < taille ; i++)
    {
        for (int j = 0; j < taille ; j++)
	  {
	    printf("Donner la valeur pour la case [%d][%d] : ",i,j);
	    scanf("%f",&matA[i][j]);
	  }
    }
  AffichageMat2D(matA,taille);

  float * ensembleTrace = malloc(sizeof(float)*taille);
  
  float ** matAFinale = calculPuissanceEtTrace(matA,taille,ensembleTrace,taille);
  
  free(matAFinale);
  free(matA);

  float * polynome = Leverrier(ensembleTrace,taille);
  
  printf("\n\n On a donc comme polynôme :");
    for(int i = 0; i < taille+1; i++)
	     {
	       printf(taille-i?"%.2fX**%d ":"%.2f",polynome[i],taille-i);
	     }
  printf("\n\n");

  free(polynome);
  return 0;
}



/* Calcul de la trace de façon non récursif
float * calculTrace(float ** matA, int taille)
{
  float * ensembleTrace = malloc(sizeof (float) * taille);
  float trace;
 
  float *** ensemblePuissanceMatA = malloc(sizeof(float**)*3);
 
  ensemblePuissanceMatA[0] = matA;
  
  float ** id = matriceIdentite(taille);
  

  ensemblePuissanceMatA[2] = id;

 
  for (int t = 0; t < taille; t++)
    {
      printf("%d,%d\n",t%2+1,(t+1)%2+1);
      ensemblePuissanceMatA[t%2+1] = prodMatrice2D(ensemblePuissanceMatA[(t+1)%2+1],ensemblePuissanceMatA[0],taille);

      AffichageMat2D(ensemblePuissanceMatA[t%2+1],taille);
      freeMatrice2D(ensemblePuissanceMatA[(t+1)%2+1],taille);
	
      trace = 0;
      for (int y = 0; y < taille; y++)
	{
	  trace += ensemblePuissanceMatA[t%2+1][y][y];
	}
      printf("La trace pour matA de puissance %d est : %f \n", t+1,trace);
      ensembleTrace[t] = trace;

      if(t == taille -1)
	{
	  freeMatrice2D(ensemblePuissanceMatA[t%2+1],taille);
	}
    }
 
  freeMatrice2D(ensemblePuissanceMatA[0],taille);
  free(ensemblePuissanceMatA);
  return ensembleTrace;
}
*/
