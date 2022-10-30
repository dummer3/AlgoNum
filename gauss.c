#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
//------------CHECK MATRICE--------------------------------------
void verif(float **matA, float *matX, int taille)
{
  float temp = 0;
  float tempMAX = 0;
  int ligneTemp = -1; //-1 pour voir plus facilement si il y a une erreur
  for (int i = 0; i < taille; i++)
  {
    temp = 0;
    for (int j = 0; j < taille; j++)
    {
      temp += matA[i][j] * matX[j];
    }
    if (i == 0 || i == taille - 1)
    {
      printf("\nLigne num %d || B = 1 || AX = %f", i, temp); //à la fin de l'algo B = X trouvé donc on a plus le B initiale et j'ai pas envie de le sauvegarder.
      if (fabs(0 - tempMAX) <= fabs(0 - temp))
      {
        tempMAX = temp;
        ligneTemp = i;
      }
    }
  }
  printf("\nLigne erreur max %d || B = 1 || AX = %f", ligneTemp, tempMAX);
}
////////////// FONCTION UTILITAIRE ///////////////////////////////////////////////////////////////////////////////////////////

////////////// MATRICE TEST///////////////////////////////////////////////////////////////////////////////////////////
void matriceCreuseDiagDomi(float **mat, int taille);
//
void matriceCreuse(float **mat, int taille);
//
void matHilbertNegCarree(float **mat, int taille);
//
void matDingDongCarree(float **mat, int taille);
//
void matFrancCarree(float **mat, int taille);
//
void matHilbertPosCarree(float **mat, int taille);
//
void matKmsCarree(float **mat, int taille, float p);
//
void matLehmerCarree(float **mat, int taille);
//
void matLotkinCarree(float **mat, int taille);
//
void matMolerCarree(float **mat, int taille);
//
void matABordCarre(float **mat, int taille);
////////////// MATRICE TEST///////////////////////////////////////////////////////////////////////////////////////////

////////////// FONCTION GAUSS ///////////////////////////////////////////////////////////////////////////////////////////
int inverseLigne(float **matA, float matB[], int taille, int numPivot);
//
int triangulation(float **matA, float matB[], int taille);
//
void resolutionMatTriangSup(float **matA, float matB[], int taille);
/////////////FONCTION GAUSS FIN /////////////////////////////////////////////////////////////////////////

int main()
{
  /////////////////////DEFINITION DES VARIABLES ET MATRICES//////////////////////////////////////////////

  //CREATION DES MATRICES
  //printf("\nQuelle est la taille des matrices ?");
  int taille; //scanf("%d", &taille);
  taille = 3;
  float **matA = matrice2D(taille);
  float **matAPass = matrice2D(taille);
  float *matB = malloc(sizeof(float) * taille);

  //DEFINITION DES MATRICES
  matriceCreuse(matA, taille);
  for (int i = 0; i < taille; i++)
  {
    matB[i] = 1;
  }

  //COPIE DE matA
  for (int i = 0; i < taille; i++)
  {
    for (int j = 0; j < taille; j++)
    {
      matAPass[i][j] = matA[i][j];
    }
  }

  //INITIALISATION PARCEQUE C'EST JOLIE
  printf("Calcule des matrices suivantes par la methode de Gauss \n");
  printf("Matrice A =\n");
  AffichageMat2D(matA, taille);
  printf("Matrice B =\n");
  AffichageMat(matB, taille);
  printf("\ncalcule en cours...");
  ////////////////////////GAUSS/////////////////////////////////////////////////////////////////
  //On triangule la matrice A en changeant B en consequence


  if (!triangulation(matA, matB, taille))
  {
    //Si on a un pivot nul qui ne peut etre echanger avec une autre ligne alors la matrice contient une infinite de solution
    //Et ne peut donc pas etre resolue par gauss directement
    printf("\nIl y a un nombre infinie ou aucune nombre de solution");
  }
  else
  {
    printf("\nApres triangulation :\n");
    printf("Matrice A =\n");
    AffichageMat2D(matA, taille);
    printf("Matrice B =\n");
    AffichageMat(matB, taille);

    //On resout le système d'equation
    printf("\nResolution du systeme :");
    resolutionMatTriangSup(matA, matB, taille);
    printf("\n\nVERIFICATION :");
    verif(matAPass, matB, taille);
  }
  freeMatrice2D(matA, taille);
  freeMatrice2D(matAPass, taille);
  free(matB);
}

////////////// FONCTION GAUSS ///////////////////////////////////////////////////////////////////////////////////////////
int inverseLigne(float **matA, float matB[], int taille, int numPivot)
{
  float temp;
  int on = 0;
  int i = numPivot + 1;
  //On recherche parmis les lignes "en-dessous" de la ligne du pivot une valeur non nul situe dans la meme colonne que notre pivot
  //Si une ligne est trouve on arrete la recherche.
  while (i < taille && on != 1)
  {
    if (matA[i][numPivot] != 0)
    {
      //Si on la trouve alors on echange cette ligne avec celle de la ligne pivot
      for (int j = 0; j < taille; j++)
      {
        temp = matA[numPivot][j];
        matA[numPivot][j] = matA[i][j];
        matA[i][j] = temp;
      }
      temp = matB[numPivot];
      matB[numPivot] = matB[i];
      matB[i] = temp;
      on++;
    }
    i++;
  }
  return on; //La fonction renvoie 0 si elle n'as pas trouve de ligne a echanger ou 1 si elle a trouve.
}

int triangulation(float **matA, float matB[], int taille)
{
  int i, j, numPivot;
  //On regarde chaque pivots possibles de la matrice A.
  for (numPivot = 0; numPivot < taille; numPivot++)
  {
    int ok = 1;
    float pivot = matA[numPivot][numPivot];
    if (pivot == 0.00) //Si le pivot est nul, on cherche a inverse la ligne du pivot avec une autre pour avoir un pivot non nul
    {
      ok = inverseLigne(matA, matB, taille, numPivot);
      if (!ok)
      {
        return ok; //Si on ne trouve pas d'autres potentiels pivot non nul alors la matrice a une infinite de solution
      }
    }
    for (i = numPivot + 1; i < taille; i++) //On regarde les lignes en desous de la ligne du pivot
    {
      //Si dans une ligne la valeur contenue dans la meme colonne du pivot est non nul
      //On soustrait a cette ligne la ligne du pivot multiplier par le pivot divise par la valeur non nul afin de la rendre non nul
      if (matA[i][numPivot] != 0)
      {
        float coeffpivot = matA[i][numPivot] / matA[numPivot][numPivot];
        for (j = numPivot; j < taille; j++)
        {
          matA[i][j] = matA[i][j] - (coeffpivot * matA[numPivot][j]);
        }
        matB[i] = matB[i] - coeffpivot * matB[numPivot]; //On ne n'oublie pas de modifie la matrice B egalement
      }
    }
  }
  return 1; //On retourne 1 pour indiquer que la triangulation s'ait effectue sans probleme
}

void resolutionMatTriangSup(float **matA, float matB[], int taille)
{
  //On  met la dernière ligne de la matrice A a 1
  matB[taille - 1] /= matA[taille - 1][taille - 1];
  //On calcule les solutions ligne par ligne en "remontant" les matrices
  for (int numVar = taille - 2; numVar >= 0; numVar--)
  {
    //On soustrait a la ligne de B les coefficient non nul (sauf le pivot) de la ligne de A multiplie
    //par les solutions des inconnues precedament calcule
    for (int j = numVar + 1; j < taille; j++)
    {
      matB[numVar] -= matA[numVar][j] * matB[j];
    }
    //Puis on divise le tout par le pivot de la ligne de A
    matB[numVar] /= matA[numVar][numVar];
  }
  //Au final on affiche la matrice B contenant les solutions de l'equation
  for (int j = 0; j < taille; j++)
  {
    printf("\nX%d = %f", j + 1, matB[j]);
  }
}

/////////////FONCTION GAUSS FIN /////////////////////////////////////////////////////////////////////////

////////////// MATRICE TEST///////////////////////////////////////////////////////////////////////////////////////////
void matriceCreuseDiagDomi(float **mat, int taille)
{
  srand( time( NULL ) );
  int pourcent = taille * taille * 30 / 100;
  //printf("\npourcent = %d", pourcent);
  int count = 0;
  for (int i = 0; i < taille; i++)
  {
    for (int j = 0; j < taille; j++)
    {
      if (i == j)
      {
        mat[i][j] = taille * 10 + rand() % 10;
      }
      else
      {
        mat[i][j] = 1 + rand() % 10;
      }
    }
  }
  while (count < pourcent)
  {
    int randomX = rand() % taille;
    int randomY = rand() % taille;
    if (randomX == randomY || mat[randomX][randomY] == 0)
    {
      count--;
    }
    else
    {
      mat[randomX][randomY] = 0;
    }
    count++;
  }
}
//
void matriceCreuse(float **mat, int taille)
{
  srand( time( NULL ) );
  int pourcent = taille * taille * 30 / 100;
  //printf("\npourcent = %d", pourcent);
  int count = 0;
  for (int i = 0; i < taille; i++)
  {
    for (int j = 0; j < taille; j++)
    {
      mat[i][j] = 1 + rand() % 100;
    }
  }
  while (count < pourcent)
  {
    int randomX = rand() % taille;
    int randomY = rand() % taille;
    if (randomX == randomY || mat[randomX][randomY] == 0)
    {
      count--;
    }
    else
    {
      mat[randomX][randomY] = 0;
    }
    count++;
  }
}
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
void matABordCarre(float **mat, int taille)
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
