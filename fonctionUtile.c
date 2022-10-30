#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "fonctionUtile.h"


////////////// FONCTION UTILITAIRE ///////////////////////////////////////////////////////////////////////////////////////////

//------------CREATION ET LIBERATION MATRICE ---------------------------------
float **matrice2D(int taille)
{
    float **mat = malloc(sizeof(float *) * taille);
    for (int i = 0; i < taille; i++)
    {
        mat[i] = malloc(sizeof(float) * taille);
        for (int j = 0; j < taille; j++)
        {
            mat[i][j] = 0;
        }
    }
    return mat;
}

//
float ** matriceIdentite(int taille)
{
  float ** mat = malloc(sizeof(float*) * taille);
  for(int i = 0; i < taille;i++)
    {
      mat[i] = malloc(sizeof(float)*taille);
      for(int j = 0;j<taille;j++)
	{
	  if(i != j)
	    {
	      mat[i][j] = 0;
	    }
	  else
	    {
	      mat[i][j] = 1;
	    }
	}
    }
  return mat;
}

//
void freeMatrice2D(float **mat, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        free(mat[i]);
    }
    free(mat);
}
//
//------------AFFICHAGE MATRICE ---------------------------------
void AffichageMat(float *mat, int taille)
{
    for (int j = 0; j < taille; j++)
    {
        printf("|%f|", mat[j]);
    }
    printf("\n");
}
//
void AffichageMat2D(float **mat, int taille)
{
    for (int j = 0; j < taille; j++)
    {
        AffichageMat(mat[j], taille);
    }
    printf("\n");
}

//
float** prodMatrice2D(float ** matA, float ** matB, int taille)
{
  float ** mat2 = matrice2D(taille);
  for (int i =0 ; i< taille ; i++)
	{
	  for (int j= 0; j  < taille; j++)
	    {
	     int somme = 0;
	      for (int k = 0; k < taille; k++)
	      {
		somme += matA[i][k] * matB[k][j];
	      }
	      mat2[i][j] = somme;	      
	    }
	}
  return mat2;
}

float calculDeLaTrace(float ** matA, int taille)
{
    float trace = 0;
      for (int y = 0; y < taille; y++)
	{
	  trace += matA[y][y];
	}
      return trace;
}

float ** multiplicationExterneMatrice2D(float ** mat, float x, int taille)
{
  float ** M = matrice2D(taille);
  for(int i = 0; i < taille; i++)
    {
      for(int j = 0; j < taille; j++)
	{
	  M[i][j] = mat[i][j] * x;
	}
    }
  return M;
}

float ** AdditionMatrice(float ** matA, float ** matB, char c, int taille)
{
  float ** M = matrice2D(taille);
  
    if (c == '+')
    {
      for (int i = 0; i < taille;i++)
	{
	  for(int j = 0; j < taille; j++)
	    {
	      M[i][j] = matA[i][j] + matB[i][j];
	    }
	}
     
    }
   
   else if (c == '-')
    {
      for (int i = 0; i < taille;i++)
	{
	  for(int j = 0; j < taille; j++)
	    {
	      M[i][j] = matA[i][j] - matB[i][j];
	    }
	}
     
    }
   else
     {
       printf("ERROR PAS DE MATRICE");
     }
     return M;
}

//
////////////// FONCTION UTILITAIRE ///////////////////////////////////////////////////////////////////////////////////////////

////////////// MATRICE TEST///////////////////////////////////////////////////////////////////////////////////////////

//
void matHilbertNegCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            mat[x][y] = (float)1 / ((x + 1) + (y + 1) - 1);
        }
    }
}
//
void matDingDongCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            mat[x][y] = 1 / (2 * (taille - (x + 1) - (y + 1) + 1.5));
        }
    }
}
//
void matFrancCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            if (x >= y + 2)
            {
                mat[x][y] = 0;
            }
            else if (x >= y)
            {
                mat[x][y] = (y + 1);
            }
            else
            {
                mat[x][y] = (x + 1);
            }
        }
    }
}
//
void matHilbertPosCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            mat[x][y] = (float)1 / ((x + 1) + (y + 1) + 1);
        }
    }
}
//
void matKmsCarree(float **mat, int taille, float p)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            mat[x][y] = pow(p, fabs(x + 1 - y + 1));
        }
    }
}
//
void matLehmerCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            if (x <= y)
            {
                mat[x][y] = (float)(x + 1) / (y + 1);
            }
            else
            {
                mat[x][y] = (float)(y + 1) / (x + 1);
            }
        }
    }
}
//
void matLotkinCarree(float **mat, int taille)
{
    for (int y = 0; y < taille; y++)
    {
        mat[0][y] = 1;
    }

    for (int x = 1; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            mat[x][y] = (float)1 / ((x + 1) + (y + 1) - 1);
        }
    }
}
//
void matMolerCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            if (x == y)
            {
                mat[x][y] = (x + 1);
            }
            else if (x >= y)
            {
                mat[x][y] = (y + 1) - 2;
            }
            else
            {
                mat[x][y] = (x + 1) - 2;
            }
        }
    }
}
//
void matABordCarree(float **mat, int taille)
{
    for (int x = 0; x < taille; x++)
    {
        for (int y = 0; y < taille; y++)
        {
            if (x == y)
            {
                mat[x][y] = 1;
            }
            else if (x == taille - 1 || y == taille - 1)
            {
                int temp;
                if (x == taille - 1)
                {
                    temp = y;
                }
                else
                {
                    temp = x;
                }
                mat[x][y] = 1 << (taille - (temp + 1));
            }
            else
            {
                mat[x][y] = 0;
            }
        }
    }
}
////////////// MATRICE TEST///////////////////////////////////////////////////////////////////////////////////////////


