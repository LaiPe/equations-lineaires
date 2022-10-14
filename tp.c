#include <stdlib.h>
#include <stdio.h>

#define N 3

//DECLARATION ET INIT
float ** declMatrice(int taille){
    float ** X=malloc(taille*sizeof(float*));
    if (X==NULL){return NULL;}
    for (int i=0;i<taille;i++){
        X[i]=malloc(taille*sizeof(float));
        if (X[i]==NULL){
            for(int j=0;j<i;j++){
                free(X[j]);
            }
            free(X);
            return NULL;
        }
    }
    return X;
}
void initMatrice(float ** tab,float val[][N],int taille){
    for (int i=0;i<taille;i++){
        for (int y=0;y<taille;y++){
            tab[i][y]=val[i][y];
        }
    } 
}
float * declTab(int taille){
    float * X=malloc(taille*sizeof(float));
    if (X==NULL){return NULL;}
    return X;
}
void initTab(float * tab,float val[],int taille){
    for (int i=0;i<taille;i++){
        tab[i]=val[i];
    }
}

//AFFICHAGE
void afficheVect(float * t,int taille){
    for (int i=0;i<taille;i++){
        printf("%g \n",t[i]);
    }
    printf("\n");
}
void afficheMatrice(float ** t,float taille){
    for (int i=0;i<taille;i++){
        for (int y=0;y<taille;y++){
            printf("%g ",t[i][y]);
        }
        printf("\n");
    }
}

//Gauss et Triangulation
void gauss(float ** A,float * B,int taille){
    for (int k=0;k<taille-1;k++){
        for (int i=k+1;i<taille;i++){
            float piv=A[i][k]/A[k][k];
            for (int j=k;j<taille;j++){
                A[i][j]-=piv*A[k][j];
            }
            B[i]-=piv*B[k];
        }
    }
}
float * trig(float ** A,float * B,int taille){
    float * X=malloc(taille*sizeof(float));
    int n=taille-1;

    X[n]=B[n]/A[n][n];
    for (int i=n-1;i>=0;i--){
        float somm=0;
        for (int j=i+1;j<=n;j++){
            somm+=A[i][j]*X[j];
        }
        X[i]=(1/A[i][i])*(B[i]-somm);
    }
    return X;
}

int main(){
    float ** A=declMatrice(N); //Déclaration de la Matrice A
    float * B=declTab(N); //Déclaration du Vecteur B
    //Valeurs de A
    float A_1[][N]={{3,0,4},{7,4,2},{-1,1,2}};
    float A_2[][N]={{-3,3,-6},{-4,7,8},{5,7,-9}};
    float A_3[][N]={{4,1,1},{2,-9,0},{0,-8,6}};
    float A_4[][N]={{7,6,9},{4,5,-4},{-7,-3,8}};
    //Valeurs de B
    float B_1[]={7,13,2};
    float B_2[]={-6,11,3};
    float B_3[]={6,-7,-2};
    float B_4[]={22,5,-2};

    initMatrice(A,A_4,N); //Ecriture des valeurs de A 
    initTab(B,B_4,N); //Ecriture des valeurs de B


    //Affichage initial (avant traitement)
    printf("============\n");
    afficheMatrice(A,N);
    printf("\n");
    afficheVect(B,N);

    gauss(A,B,N); //traitement avec l'algorithme de gauss
    printf("============\n");

    //Affichage intermediaire (après gauss)
    afficheMatrice(A,N);
    printf("\n");
    afficheVect(B,N);

    float * X=trig(A,B,N); //traitement de la matrice triangulaire supp
    printf("============\n");

    //Affichage Terminal (solution de AX=B)
    afficheVect(X,N);

    return 0;
}