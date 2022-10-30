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
//------------CHECK MATRICE--------------------------------------
void verif(float **matA, float *matX, float *matB, int taille)
{
    float temp = 0;
    int ligneTemp = -1; //-1 pour voir plus facilement si il y a une erreur
    float tempMAX = 0;
    for (int i = 0; i < taille; i++)
    {
        temp = 0;
        for (int j = 0; j < taille; j++)
        {
            temp += matA[i][j] * matX[j];
        }
        if (i == 0 || i == taille - 1)
        {
            printf("\nLigne num %d || B = %f || AX = %f", i, matB[i], temp);
        }
        if (fabs(0 - tempMAX) <= fabs(0 - temp))
        {
            tempMAX = temp;
            ligneTemp = i;
        }
    }
    printf("\nLigne erreur max %d|| B = %f || AX = %f",ligneTemp, matB[ligneTemp], tempMAX);
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


int main()
{
    /////////////////////DEFINITION DES VARIABLES ET MATRICES//////////////////////////////////////////////
    //printf("\nQuelle est la taille des matrices ?");
    int taille; //scanf("%d", &taille);
    taille = 3;
    float **matA = matrice2D(taille);
    float *matB = malloc(sizeof(float) * taille);
    float erreur = 1.0;
    float erreurPalier;
    float *matX = malloc(sizeof(float) * taille);
    for (int i = 0; i < taille; i++)
    {
        matX[i] = 0;
    }
    float *matXPass = malloc(sizeof(float) * taille);
    matriceCreuseDiagDomi(matA, taille);
    printf("\nmatrice A : \n");
    AffichageMat2D(matA, taille);
    for (int i = 0; i < taille; i++)
    {
        matB[i] = 1.0;
    }
    erreurPalier = 0.00001;
    ////////////////////////JACOBI//////////////////////////////////////////////////////////////////
    int count = 1;
    for (int i = 0; i < taille; i++)
    {
        int sommeSansDiag = 0;
        for (int j = 0; j < taille; j++)
        {
            if (i != j)
            {
                sommeSansDiag += fabs(matA[i][j]);
            }
        }
        if (fabs(matA[i][i]) <= sommeSansDiag)
        {
            printf("Ellen'est pas diagonale strictement dominante");
            count = 2000;
        }
    }
    while (erreur >= erreurPalier && count <= 1000)
    {
        count++;
        //SAUVEGARDE DE Xk
        for (int i = 0; i < taille; i++)
        {
            matXPass[i] = matX[i];
        }
        //CALCULE DE Xk+1
        for (int i = 0; i < taille; i++)
        {
            float sommeProdMatSansDiag = 0;
            for (int j = 0; j < taille; j++)
            {
                if (i != j)
                {
                    sommeProdMatSansDiag = sommeProdMatSansDiag + matA[i][j] * matXPass[j];
                }
            }
            matX[i] = (matB[i] - sommeProdMatSansDiag) / matA[i][i];
        }
        //CALCULE DE LA NORME ||Xk - Xk+1 ||
        erreur = 0;
        for (int i = 0; i < taille; i++)
        {
            erreur += (matXPass[i] - matX[i]) * (matXPass[i] - matX[i]);
        }
        erreur = sqrt(erreur);
    }
    if (count != 2000)
    {
        printf("\nCalcule terminer...\n");
        printf("Les solutions a l'equation sont :\n");
        AffichageMat(matX, taille);
        printf("\nVERIFICATION :");
        verif(matA, matX, matB, taille);
    }
    printf("\n\n------------------FIN------------------\n");
    freeMatrice2D(matA, taille);
    free(matXPass);
    free(matB);
    free(matX);
    return 0;
}

/////////////////////////JACOBI///////////////////////////////////////////////////////////////////////////


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
