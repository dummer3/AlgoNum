#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fonctionUtile.h"

// Renvoie la transposee de mat dans mat
void transposee(float ** mat,int taille)
{
  float tempo;
  for (int i = 0; i < taille;i++)
    {
      for(int j = i+1; j<taille;j++)
	{
	  tempo = mat[i][j];
	  mat[i][j] = mat[j][i];
	  mat[j][i] = tempo;
	}
    }
}

void remplissageAleatoire2DSym(float ** mat, int taille)
{

    for (int i = 0; i < (taille/2)+1; i++)
      {
	for( int j = 0;j < (taille/2)+1; j++)
	  {
	    float alea = rand()%100;
	    if(alea >= 70)
	      {
		mat[i][j] = 0;
		mat[j][i] = 0;
	      }
	    else
	      {
		mat[i][j] = alea;
		mat[j][i] = alea;
	      }
	  }
      }
}

void remplissageAleatoire(float * mat,int taille)
{
    for (int i = 0; i < (taille/2)+1; i++)
      {
	float alea = rand()%100;
	mat[i] = alea;
      }

}
// Cette fonction applique la méthode de choleski sur la marice matA en enregistre le réultat dans la matrice C1
// Renvoie 1 (true) si l'algorithme c'est passé sans aucun problème, 0 (false) sinon.
int Choleski(float ** matA,float ** C1, int taille)
{
  
  /* matA correspond à notre matrice A dans le système Ax = B
     C1 est la matrice obtenue après que Choleski est travaillé avec matA
     taille représente la longueur de la matrice carrée A et C1 */

  int occurence = 0;
  
  for (int i = 0; i < taille; i++) //On parcours chaque ligne de la matrice matA
    {
      float t = matA[i][i];
      for(int l = 0; l<i ; l++)
	{
	  t -= pow(C1[l][i],2);
	  occurence++;
	}
      // Si t inférieure à 0, alors on renvoie 0 (erreur);
      if(t <= 0)
	{
	  printf("Algorithme de Choleski impossible\n");
	  return 0;
	}
      // Sinon on peut continuer d'appliquer Choleski sans problème
      else
	{
	  C1[i][i] = sqrtf(t);
	  occurence++;
	  for(int j = i+1;j < taille;j++)
	    {
	    
	      float s=0;
	      for (int l = 0; l < i; l++)
		{
		    
		  s += C1[l][i] * C1[l][j] ;
		  occurence+= 2;
		}
	      // De même si on divise par 0 Choleski renvoie une erreur
	      if(C1[i][i] == 0)
		{
		  printf("Division par 0\n");
		  return 0;
		}
	      else
		{
		  C1[i][j] = (matA[i][j] - s)/C1[i][i];
		  occurence += 2;
		}
	    }
	}
    }
  printf("Il y a eu %d occurences\n",occurence);
  return 1;
}


// Resout C*x = matB en fonction de si C et la matrice obtenue via Choleski (estTransposee = 'n') ou sa transposée
// Renvoie 0 (false) si l'algorithme divise par 0, 1 (true) si l'algorithme s'exécute sans problème
int resolution(float * matB,float ** C,int taille, char estTransposee)
{
  if(estTransposee == 'n')
    {
      for (int i = taille-1; i>=0;i--)
	{
	  float s = 0;
	 
	  for(int j = taille-1; j > i;j--)
	    {
	      s -= matB[j]*C[i][j] ;
	    }
	  if(C[i][i] == 0)
	    {
	      printf("Division par 0\n");
	      return 0;
	    }
	  else
	    {
	      matB[i] = (matB[i] + s)/C[i][i];
	    }
	}
    }
  else
    {
      for (int i = 0; i < taille ; i++)
	{
	  float s = 0;
	  
	  for(int j = 0; j < i;j++)
	    {
	      s -= matB[j]*C[i][j] ;
	    }
	 
	  if(C[i][i] == 0)
	    {
	      printf("Division par 0\n");
	      return 0;
	    }
	  else
	    {
	      matB[i] = (matB[i] + s)/C[i][i];
	    }


	}
    }
  return 1;
}


int main()
{
  clock_t t1,t2;
  
  srand(time(NULL));

  // Obtiens la taille voulue des matrices
  int taille;
  printf("Donner un entier pour la taille du tableau\n");
  scanf("%d", &taille);

  // On créer le tableau matA avec malloc 
  float ** matA = matrice2D(taille);

  // Création de matB
  float * matB = malloc(sizeof(float)*taille);
  remplissageAleatoire(matB,taille);
  float ** C1 = matrice2D(taille);


  // On demande à l'utilisateur si il veut une matrice de test ou une matrice creuse générée aléatoirement.
  printf("Matrice spéciale ?\n (o ou n)");
  char c;
  scanf(" %c",&c);


  // l'utilisateur choisi sa matrice test dans un catalogue de 9 choix
  if (c == 'o')
    {
      int i;
      printf("Quelle Matrice ?\n 1) pour Bord\n2) pour Ding Dong\n3) pour Franc\n4) pour Hilbert (i + j - 1)\n5) pour Hilbert (i + j + 1)\n6) pour kms\n7) pour Lehmer\n8) pour Lotkin\n9) pour Moler\n");
      do
	{
	  scanf("%d",&i);
	}while(i < 1 || i > 9);
   
      switch(i)
	{
	case 1 : matABordCarree(matA,taille); break;
	case 2 : matDingDongCarree(matA,taille); break;
	case 3 : matFrancCarree(matA,taille); break;
	case 4 : matHilbertNegCarree(matA,taille); break;
	case 5 : matHilbertPosCarree(matA,taille); break;
	case 7 : matLehmerCarree(matA,taille); break;
	case 8 : matLotkinCarree(matA,taille); break;
	case 9 : matMolerCarree(matA,taille); break;
	case 6 :
	 
	  printf("parametre p (strictement supérieure à 0 et strictement inférieure à 1):\n");
	  float p;
	  do
	    {
	      scanf("%f",&p);
	    }while(p <= 0 || p >= 1);
	  matKmsCarree(matA,taille,p); break;
	}
    }

  // Création de la matrice creuse
  else
    {
      remplissageAleatoire2DSym(matA,taille);  
    }
 

  printf("\nmatA avant choleski\n");
  AffichageMat2D(matA,taille);

  // Si Choleski est bon on continue en sachant que C1 est la matrice obtenue, sinon on s'arrête là
  t1 = clock();
  if(Choleski(matA,C1,taille))
    {
      t2 = clock();
      // On affiche matA arès Choleski

      printf("Choleski c'est exécuté en %.6f sec \n\n",(float)(t2-t1)/CLOCKS_PER_SEC);
      printf("matA après choleski\n");
      AffichageMat2D(C1,taille);

      // On affiche la transposée de matA
      transposee(C1,taille);
      printf("\n transposee de matA\n");
      AffichageMat2D(C1,taille);

      // On affiche matB
      printf("matB avant résolution\n");
      AffichageMat(matB,taille);

      // Si la première résolution (transposée(C) * y= matB) est possible on continue 
      if(resolution(matB,C1,taille,'o'))
	{
	  // On affiche la matrice obtenue
	  printf("\nmatB après 1 résolution\n");
	  AffichageMat(matB,taille);

	  transposee(C1,taille);

	  // On fait de même une seconde fois avec cette fois ci (C*x = y)
	  if(resolution(matB,C1,taille,'n'))
	    {
	      printf("\nmatB après 2 résolution\n");
	      AffichageMat(matB,taille);
	    }
	}

      //Libère toutes les matrices 
      free(matB);
      freeMatrice2D(matA,taille);
      freeMatrice2D(C1,taille);

    }
  return 0;
}

