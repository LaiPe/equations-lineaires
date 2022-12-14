#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define M 3 //Taille des matrices statiques (A_1,A_2,A_3,A_4)

#define N 3 //Taille de la matrice sélectionnée ou voulue

//OUTILS
float puiss(float x,int puiss){
    float result=1;
    if (puiss>=0){
        for (int i=0;i<puiss;i++){
            result=result*x;
        }
    }
    else{
        for (int i=0;i>puiss;i--){
            result=result/x;
        }
    }
    return result;
}
char * souligne(int n){
    n=n*4;
    char * X=malloc((n)*sizeof(char));
    if (X==NULL){return NULL;}
    for (int i=0;i<n;i++){
        X[i]='=';
    }
    X[n]='\0';
    return X;
}

//MATRICES TEST ET VALEURS DE B
void A_5(float ** A,int n){
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (i==0){
                A[0][j]=puiss(2,(1-(j+1)));
            }
            A[j][0]=puiss(2,(1-(j+1)));
        }
        A[i][i]=1;
    }
}
void A_6(float ** A,int n){
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (j==i+1 && i<(n-1)){
                A[i][j]=-1;
            }
            else if (j==i-1 && i>0){
                A[i][j]=-2;
            }
        }
        A[i][i]=3;
    }
}
float * valdeB(float ** A,float * B,int taille){
    for (int i=0;i<taille;i++){
        float somm=0;
        for (int y=0;y<taille;y++){
            somm+=A[i][y];
        }
        B[i]=somm;
    }
    return B;
}

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
void initMatrice(float ** tab,float val[][M],int taille){
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

//AFFICHAGE/ECRITURE
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
    printf("\n");
}
void ecritVect(FILE * fd,float * t,int taille){
    for (int i=0;i<taille;i++){
        fprintf(fd,"%g \n",t[i]);
    }
    fprintf(fd,"%s\n",souligne(taille));
}
void ecritMatrice(FILE * fd,float ** t,float taille){
    for (int i=0;i<taille;i++){
        for (int y=0;y<taille;y++){
            fprintf(fd,"%g ",t[i][y]);
        }
        fprintf(fd,"\n");
    }
    fprintf(fd,"%s\n",souligne(taille));
}

//METHODE DIRECTE (GAUSS)
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
void gaussDet(float ** A,float * B,int taille){
    FILE * ope=fopen("./bin/operations.log","w+");
    FILE * evoMatA=fopen("./bin/evolutionMatriceA.log","w+");
    FILE * evoVectB=fopen("./bin/evolutionVecteurB.log","w+");
    
    fprintf(ope,"Début Gauss\n");

    fprintf(evoMatA,"Début Gauss\n%s\nMATRICE A:\n%s\n",souligne(taille),souligne(taille));
    ecritMatrice(evoMatA,A,taille);

    fprintf(evoVectB,"Début Gauss\n%s\nVECTEUR B:\n%s\n",souligne(taille),souligne(taille));
    ecritVect(evoVectB,B,taille);

    for (int k=0;k<taille-1;k++){
        fprintf(ope,"k=%d\n",k);
        for (int i=k+1;i<taille;i++){
            fprintf(ope,"    i=%d\n",i);
            float piv=A[i][k]/A[k][k];
            fprintf(ope,"        piv=A[%d][%d]/A[%d][%d]=%g/%g=%g\n",i,k,k,k,A[i][k],A[k][k],piv);
            for (int j=k;j<taille;j++){
                fprintf(ope,"        j=%d\n",j);
                fprintf(ope,"            A[%d][%d]-=piv*A[%d][%d]\n",i,j,k,j);
                fprintf(ope,"            %g-=%g*%g\n",A[i][j],piv,A[k][j]);
                fprintf(ope,"            %g-=%g\n",A[i][j],piv*A[k][j]);
                A[i][j]-=piv*A[k][j];
                fprintf(ope,"            =%g\n",A[i][j]);

                fprintf(evoMatA,"k=%d,i=%d,j=%d\n%s\n",k,i,j,souligne(taille));
                ecritMatrice(evoMatA,A,taille);
            }
            fprintf(ope,"        B[%d]-=piv*B[%d]\n",i,k);
            fprintf(ope,"        %g-=%g*%g\n",B[i],piv,B[k]);
            fprintf(ope,"        %g-=%g\n",B[i],piv*B[k]);
            B[i]-=piv*B[k];
            fprintf(ope,"        =%g\n",B[i]);

            fprintf(evoVectB,"k=%d,i=%d\n%s\n",k,i,souligne(taille));
            ecritVect(evoVectB,B,taille);
        }
    }
    fprintf(evoMatA,"Fin Gauss");
    fprintf(evoVectB,"Fin Gauss");
    fprintf(ope,"Fin Gauss\n");

    fclose(ope);
    fclose(evoMatA);
    fclose(evoVectB);
}
float * ResTrigSup(float ** A,float * B,int taille){
    float * X=declTab(taille);
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
//METHODES ITERATIVES (JACOBI,GAUSS-SEIDEL)
float E(float ** A,float * X,float * B,int taille){
    float norme=0;
    float v=0;
    for (int i=0;i<taille;i++){
        //Produit Vectoriel A*X
        float AXi=0; //Somme du produit A[i]*X[i]
        for (int j=0;j<taille;j++){
            AXi+=A[i][j]*X[i];
        }
        v=AXi-B[i]; // v représente le produit vectoriel AX de la i-ème ligne auquel on soustrait B[i]
        norme+=puiss(v,2); //somme des v de toutes les lignes ("taille" lignes) au carré
    }
    return sqrtf(norme); // <=> ||AX-B||
}

float * jacobi(float e,float ** A,float * B,int taille){
    //initialisation de X (x0)
    float * X=declTab(taille);
    for (int y=0;y<taille;y++){
        X[y]=0; //vecteur nul
    }
    //algo jacobi
    //RAPPEL: Ax=b <=> A=D-E-F
    int k=1;
    while (E(A,X,B,taille)>=(1/e)){
        for (int i=0;i<taille;i++){
            //Produit Vectoriel -((E+F)*x) pour la i-ème ligne
            float somm=0;
            for (int j=0;j<taille;j++){
                if (j!=i){
                    somm+=A[i][j]*X[j];
                }
            }
            //
            X[i]=((1/A[i][i])*(B[i]-somm)); // <=> D-1 * (B-(-(E+F)*x))
        }
        k++;
    }
    printf("k=%d\n",k); //affichage du nombre d'itérations
    return X;
}
float * gauss_seidel(float e,float ** A,float * B,int taille){
    //initialisation de X (x1)
    float * X0=declTab(taille);
    float * X1=declTab(taille);
    for (int y=0;y<taille;y++){
        X1[y]=0; //vecteur nul
        X0[y]=0;
    }
    //algo gauss_seidel
    int k=1;
    while (E(A,X1,B,taille)>=(1/e)){
        for (int i=0;i<taille;i++){
            float somm=0;
            for (int j=0;j<i;j++){
                somm+=A[i][j]*X1[j];
            }
            for (int j=i+1;j<taille;j++){
                somm+=A[i][j]*X0[j];
            }
            //
            X0[i]=X1[i];
            X1[i]=((1/A[i][i])*(B[i]-somm));
            
        }
        k++;
    }
    printf("k=%d\n",k); //affichage du nombre d'itérations
    return X1;
}


int main(int argc, char ** argv){

    float ** A=declMatrice(N); //Déclaration de la Matrice A
    float * B=declTab(N); //Déclaration du Vecteur B
    //Valeurs de A
    float A_1[][M]={{8,0,0},{0,20,-2},{0,1,10}};
    float A_2[][M]={{-3,3,-6},{-4,7,8},{5,7,-9}};
    float A_3[][M]={{4,1,1},{2,-9,0},{0,-8,6}};
    float A_4[][M]={{7,6,9},{4,5,-4},{-7,-3,8}};
    //Valeurs de B
    float B_1[]={7,13,2};
    float B_2[]={-6,11,3};
    float B_3[]={6,-7,-2};
    float B_4[]={22,5,-2};

    initMatrice(A,A_3,N); //Ecriture des valeurs de A (A_1,A_2,A_3,A_4)
    //ou bien
    //A_6(A,N); //Génération des valeurs de A (A_5,A_6)

    initTab(B,B_3,N); //Ecriture des valeurs de B
    //ou bien
    //valdeB(A,B,N); //Génération des valeurs de B tel que Xi=1


    //Affichage initial (avant traitement)
    printf("============\n");
    printf("A=\n");
    printf("============\n");
    afficheMatrice(A,N);
    printf("============\n");
    printf("B=\n");
    printf("============\n");
    afficheVect(B,N);


    //METHODE GAUSS
    if (argc>1 && strcmp(argv[1],"G")==0){
        if (argc>2 && strcmp(argv[2],"det")==0){
            gaussDet(A,B,N); //Traitement avec l'algorithme de gauss avec écriture des logs
        }
        else{
            gauss(A,B,N); //traitement avec l'algorithme de gauss
        }
        float * Xg=ResTrigSup(A,B,N); //traitement de la matrice triangulaire supp

        //Affichage final (solution de AX=B)
        printf("============\n");
        printf("X=\n");
        printf("============\n");
        afficheVect(Xg,N);
    }

    //METHODE JACOBI
    else if (argc>1 && strcmp(argv[1],"J")==0){
        int conti=1;
        while (conti==1){
            float e;
            printf("précision (>1)?:");
            scanf("%f",&e);
            if (e>1){
                float * Xj=jacobi(e,A,B,N);
                //Affichage final (solution de AX=B)
                printf("============\n");
                printf("X=\n");
                printf("============\n");
                afficheVect(Xj,N);
                conti=0;
            }
            else{
                printf("Veuillez entrer une valeur valide.\n");
            }
        }
    }
    //METHODE GAUSS-SEIDEL
    else if (argc>1 && strcmp(argv[1],"GS")==0){
        int conti=1;
        while (conti==1){
            float e;
            printf("précision (>1)?:");
            scanf("%f",&e);
            if (e>1){
                float * Xj=gauss_seidel(e,A,B,N);
                //Affichage final (solution de AX=B)
                printf("============\n");
                printf("X=\n");
                printf("============\n");
                afficheVect(Xj,N);
                conti=0;
            }
            else{
                printf("Veuillez entrer une valeur valide.\n");
            }
        }
    }

    else{
        printf("Aucune méthode de résolution valable renseigné.\nVeuillez vous reporter au README pour des informations relatives à la syntaxe.\n");
    }
    return 0;
}