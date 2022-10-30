#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "fonctionUtile.h"
#include "string.h"

float ValeurPropre(float ** mat, float * vp, int taille)
{
  float resultat;
  float numerateur = 0;
  float denominateur = 0;
  
  float * tempo = malloc(sizeof(float)*taille);
  for(int i = 0; i < taille; i++)
    {
      resultat = 0;
      for(int j = 0; j < taille; j++)
	{
	  resultat += vp[j]*mat[i][j];
	}
      tempo[i] = resultat;
    }

  
  for(int i = 0; i < taille; i++)
    {
      numerateur += tempo[i]*vp[i]; 
    }
  
  for(int i = 0; i < taille; i++)
    {
      denominateur += pow(vp[i],2);
    }

  return (numerateur/denominateur);
  
}


float * puissance(float ** mat, float incertitude,int taille)
{
  int securite = 0;
  int incertitudeVerifier = 0;
  float resultat;
  int rangDuDiviseur = taille-1;
  
  float * pointDeDepart = malloc(sizeof(float)*taille);
  float * pointSuivant = malloc(sizeof(float)*taille);
  float * pointDeDepart2 = malloc(sizeof(float)*taille);
  float * pointSuivant2 = malloc(sizeof(float)*taille);
  
  for (int i = 0; i < taille; i++)
    {
      pointDeDepart[i] = 1;
      pointDeDepart2[i] = 1;
    }
  while(!incertitudeVerifier && securite < 10000)
    {
      for (int i = 0; i <taille;i++)
	{
	  resultat = 0;
	  for(int j = 0; j < taille; j++)
	    {
	      resultat += pointDeDepart[j]*mat[i][j];
	    }
	  pointSuivant[i] = resultat;
	}

      while(!pointSuivant[rangDuDiviseur] && rangDuDiviseur >=0)
	{
	  rangDuDiviseur--;
	}
      if(rangDuDiviseur == -1)
	{
	  printf("ERROR AUCUNE DIVISION POSSIBLE\n\n");
	}
      for (int l = taille-1; l>=0;l--)
	{
	
	  pointSuivant2[l] = pointSuivant[l] / pointSuivant[rangDuDiviseur]; 
	}
      incertitudeVerifier = 1;
      for(int v = 0; v < taille; v++)
	{
	  if(fabs(pointDeDepart2[v]-pointSuivant2[v]) >= incertitude)
	    {
	      incertitudeVerifier = 0;
	    }
	}
      memcpy(pointDeDepart, pointSuivant2, taille*sizeof(float));
      memcpy(pointDeDepart2, pointSuivant2,taille*sizeof(float));
      securite++;
    }
  if(securite == 10000)
    {
      printf("ERROR BOUCLE INFINIE\n\n");
    }
  return pointDeDepart;
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

  float * vecteurPropre = puissance(matA,0.001,taille);

  printf("On a comme vecteur propre :\n");
  AffichageMat(vecteurPropre,taille);

  float valeurPropre = ValeurPropre(matA,vecteurPropre,taille);
  printf("La valeur propre est %f:", valeurPropre);
  
  return 0;
}

