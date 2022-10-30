#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include"fonctionUtile.h"


/////////////////////// Fonction Utilitaire

// Remplit aléatoirement un tableau de dimension 1 de taille "taille"
void remplissageAleatoire(float * mat, int taille)
{
  for (int i = 0; i < taille; i++)
    {
      mat[i] = rand()%100;
    }
  
}

// Remplit une matrice de dimension 2 de façon aléatoire avec plus de 70% de 0
void remplissageAleatoire2D(float ** mat, int taille)
{
  
  for (int i = 0; i < taille; i++)
    {
      for(int j = 0; j <= taille; j++)
	{
	  int alea = rand()%100;
	  if (alea > 30)
	    {
	      alea = 0;
	    }
	  mat[i][j] = alea;
	}

    }
}

// Procédure pour calculer rapidement le produit de la matrice carré de taille "taille" avec la matrice colonne B de même taille 
void produitDeAParX(float * C, float ** A,float * B,int taille)
{
  for(int i = 0; i < taille;i++)
    {
      float somme = 0;
      for(int j = 0; j< taille;j++)
	{
	  somme += A[i][j]*B[j];
	}
      C[i] = somme;
    }
}

/////////////////////// Fin Fonction Utilitaire


// Cette fonction calcul la solution de matA*X = matB en fontion d'une erreurAccepté et d'un tableau contenant les valeurs de recherches, puis stock le résultat dans ce dernier tableau.
// Renvoie 1 (true) si la fonction n'a rencontré aucun problème 0 (false) sinon avec un message d'erreur 
int Gauss_Seidel(float  ** matA, float* matB, int taille, float erreurAccepte, float* valeurActuelle)
{

  /* matA et matB sont les matrices qui écrivent l'équation Ax = B (matA = A, matB = B) matA étant une matrice Carrée et matB une matrice colonne de longueur taille.
     erreurAccepté est la valeur influant sur la marge d'erreur
     valeuActuelle et le point de départ, à chaque itérations valeurActuelle se rapprochera de x (la solution) */

  
  // matA-X et le produit entre matA et notre résultat actuelle, cette matrice va permettre de confronter les résultats obtenu avec les vrais résultats
  float * matA_X = malloc(sizeof(float)*taille);

  // les 2 int qui suivent servent comme test d'arrêt, stop permet d'arrêter la boucle au bout de 100 itérations et valeurProche test si nos résultats sont cohérents (avec une marge d'erreur défini par erreurAccepte)
  int stop = 0;
  int valeurProche = 0;
  
  // Tant que l'un de nos test d'arrêt n'est pas vérifié.
  while (stop < 1000000000 && valeurProche == 0 )
    {
      
      valeurProche = 1;
      //Pour chaque ligne du système
      for(int i = 0; i < taille;i++)
	{
	  
	  // Permet d'éviter les divisions par 0.
	  if(matA[i][i] == 0)
	    {
	      printf("Division par 0\n");
	      // On libère matA_X puisque on en a plus besoin
	      free(matA_X);
	      return 0;
	    }
	  
	  float s = 0;

	  for (int j = 0; j < taille;j++)
	    {
	      if( i != j)
		{
		  s -= matA[i][j] * valeurActuelle[j];
		}
	    }
	  valeurActuelle[i] = (matB[i] + s)/matA[i][i] ;
	}
      
      produitDeAParX(matA_X,matA,valeurActuelle,taille);

      // Cette boucle vérifie si notre résultat et proche de celui attendu (1 si oui 0 sinon)
      for(int i = 0; i < taille;i++)
	{
	  if (fabs(matA_X[i] - matB[i]) > erreurAccepte)
	    {
	      valeurProche = 0;
	    }
	}
      stop++;
    }

  // On libère matA_X puisque on en a plus besoin
  free(matA_X);

  // On retourne faux si on arrête la boucle non pas car le résultat est proche mais à cause du nombre d'itérations important
  if(stop == 1000000000)
    {
      printf("Arrêt de la boucle par sécurité\n");
      return 0;
    }
  printf("Fin de Gauss-Seidel au bout de %d itérations\n",stop);
  return 1;
}



int main()
{
   clock_t t1, t2;
  
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
      remplissageAleatoire2D(matA,taille);  
    }

  // Permet de remplir nous même le point de départ
  float * valeurDeDepart = malloc(sizeof(float)*taille);
  printf("Remplissez la matrice colonne servant comme point de départ pour Gauss Seidel");
  float point;
  for (int i = 0; i < taille;i++)
    {
      printf("\nPour la case n°%d :",i);
      scanf("%f",&point);
      valeurDeDepart[i] = point;
    }

  
  printf("\nMatA :\n");
  AffichageMat2D(matA,taille);
  printf("MatB :\n");
   AffichageMat(matB,taille);
  printf("\n");

    t1 = clock();
    
  // Si Gauss Seidel ne renvoit aucun message d'erreur, on affiche le résultat.
  if(Gauss_Seidel(matA,matB,taille,0.001,valeurDeDepart))
    {
     t2 = clock();
     printf("Gauss Seidel c'est exécuté en %.6f sec\n\n",(float)(t2-t1)/CLOCKS_PER_SEC);
       AffichageMat(valeurDeDepart,taille);
     
    }

  //On libère toute nos matrices
  free(matB);
  freeMatrice2D(matA,taille);
  
  return 0;
}
