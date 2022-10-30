extern float ** matrice2D(int);

extern void AffichageMat(float*,int);

extern void AffichageMat2D(float**,int);

extern void freeMatrice2D(float**,int);

extern float ** matriceIdentite(int taille);

extern float** prodMatrice2D(float**, float**, int);

extern float calculDeLaTrace(float**, int);

extern float ** AdditionMatrice(float**, float**, char, int);

extern float ** multiplicationExterneMatrice2D(float**, float, int);


//
extern void matFrancCarree(float **mat, int taille);
//
extern void matHilbertPosCarree(float **mat, int taille);
//
extern void matKmsCarree(float **mat, int taille, float p);
//
extern void matLehmerCarree(float **mat, int taille);
//
extern void matLotkinCarree(float **mat, int taille);
//
extern void matMolerCarree(float **mat, int taille);
//
extern void matABordCarree(float **mat, int taille);

extern void matDingDongCarree(float **mat, int taille);

extern void matHilbertNegCarree(float **mat, int taille);
