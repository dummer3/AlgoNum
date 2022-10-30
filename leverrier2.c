#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"fonctionUtile.h"

float* Levrier2(float ** mat,int taille)
{

  float ** matA = matrice2D(taille);
  float ** matB = matrice2D(taille);
  float * polynome = malloc(sizeof(float)*(taille+1));
  polynome[0] = taille%2?-1:1;
  

  //memcpy(matA,mat,sizeof(float)*pow(taille,2));
  
  for (int x=0 ; x < taille; x++)
    {
      for (int y=0 ; y < taille; y++)
	{
	  matA[x][y] = mat[x][y];
	}
    }
  polynome[1] = (float)((taille+1)%2?-1:1)*calculDeLaTrace(matA,taille);

  float ** id = matriceIdentite(taille);
  float ** idFoisTrace = multiplicationExterneMatrice2D(id,polynome[1],taille);
  freeMatrice2D(id,taille);
  
  matB = AdditionMatrice(matA,idFoisTrace,(taille+1)%2?'+':'-',taille);
   
  
  
  for (int i = 2; i <= taille; i++)
    {
      
      float **  tempoMatA = prodMatrice2D(matB,mat,taille);
      freeMatrice2D(matA,taille);
      matA = tempoMatA;

      
      polynome[i] = (float)((taille+1)%2?-1:1)/i*calculDeLaTrace(matA,taille);
    
      float ** id = matriceIdentite(taille);
      float ** idFoisTrace = multiplicationExterneMatrice2D(id,polynome[i],taille);
      freeMatrice2D(id,taille);
  
      float ** tempoMatB = AdditionMatrice(matA,idFoisTrace,(taille+1)%2?'+':'-',taille);
      freeMatrice2D(matB,taille);
      matB = tempoMatB;

      freeMatrice2D(idFoisTrace,taille);

      // AffichageMat2D(matA,taille);
      // AffichageMat2D(matB,taille);
  
    }
 
   return polynome;
}


int main()
{
  int taille;
 
  printf("Donner la taille de la matrice\n");
  scanf("%d",&taille);
   float** mat = matrice2D(taille);
  for (int i = 0; i < taille ; i++)
    {
        for (int j = 0; j < taille ; j++)
	  {
	    printf("Donner la valeur pour la case [%d][%d] : ",i,j);
	    scanf("%f",&mat[i][j]);
	  }
    }
  AffichageMat2D(mat,taille);


  float * polynome = Levrier2(mat,taille);
   
  freeMatrice2D(mat,taille);

   printf("\n\n On a donc comme polynôme :");

    for(int i = 0; i <= taille; i++)
	     {
	       printf(taille-i?"%.2fX**%d ":"%.2f",polynome[i],taille-i);
	     }
  printf("\n\n");

  free(polynome);
  return 0;
}
