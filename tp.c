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

//Triangulation
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
    float * X=declTab(taille);
    /*for (int n;n=taille;n++){
        ;
    }*/
}

int main(){
    float ** A=declMatrice(N); //Déclaration de la Matrice A
    float * B=declTab(N); //Déclaration du Vecteur B
    float A_1[][N]={{1,2,2},{1,3,3},{3,7,8}}; //Valeurs de A
    float B_1[]={2,2,8}; //Valeurs de B
    initMatrice(A,A_1,N); //Ecriture des valeurs de A 
    initTab(B,B_1,N); //Ecriture des valeurs de B

    //Affichage initial (avant traitement)
    afficheMatrice(A,N);
    printf("\n");
    afficheVect(B,N);

    gauss(A,B,N); //traitement avec l'algorithme de gauss
    printf("============\n");

    //Affichage final (après traitement)
    afficheMatrice(A,N);
    printf("\n");
    afficheVect(B,N);

    return 0;
}