#include <stdlib.h>
#include <stdio.h>

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
    for (int i=0;i<n;i++){
        X[i]='=';
    }
    X[n]='\0';
    return X;
}

//MATRICES TEST
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

//RESOLUTIONS FACILES
float * trigSup(float ** A,float * B,int taille){
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
//METHODE GAUSS
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
            fprintf(ope,"        piv=%g/%g=%g\n",A[i][k],A[k][k],piv);
            for (int j=k;j<taille;j++){
                fprintf(ope,"        j=%d\n",j);
                fprintf(ope,"            %g-=%g*%g\n",A[i][j],piv,A[k][j]);
                fprintf(ope,"            %g-=%g\n",A[i][j],piv*A[k][j]);
                A[i][j]-=piv*A[k][j];
                fprintf(ope,"            =%g\n",A[i][j]);

                fprintf(evoMatA,"k=%d,i=%d,j=%d\n%s\n",k,i,j,souligne(taille));
                ecritMatrice(evoMatA,A,taille);
            }
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

int main(){
    float ** A=declMatrice(N); //Déclaration de la Matrice A
    float * B=declTab(N); //Déclaration du Vecteur B
    //Valeurs de A
    float A_1[][M]={{3,0,4},{7,4,2},{-1,1,2}};
    float A_2[][M]={{-3,3,-6},{-4,7,8},{5,7,-9}};
    float A_3[][M]={{4,1,1},{2,-9,0},{0,-8,6}};
    float A_4[][M]={{7,6,9},{4,5,-4},{-7,-3,8}};
    //Valeurs de B
    float B_1[]={7,13,2};
    float B_2[]={-6,11,3};
    float B_3[]={6,-7,-2};
    float B_4[]={22,5,-2};

    initMatrice(A,A_1,N); //Ecriture des valeurs de A 
    //initTab(B,B_3,N); //Ecriture des valeurs de B
    //A_6(A,N);
    valdeB(A,B,N); //Ecriture des valeurs de B tel que Xi=1

    //Affichage initial (avant traitement)
    printf("============\n");
    printf("A=\n");
    printf("============\n");
    afficheMatrice(A,N);
    printf("============\n");
    printf("B=\n");
    printf("============\n");
    afficheVect(B,N);

    gaussDet(A,B,N); //traitement avec l'algorithme de gauss
    //Affichage intermédiaire
    printf("============\n");
    printf("A=\n");
    printf("============\n");
    afficheMatrice(A,N);
    printf("============\n");
    printf("B=\n");
    printf("============\n");
    afficheVect(B,N);
    float * X=trigSup(A,B,N); //traitement de la matrice triangulaire supp

    //Affichage final (solution de AX=B)
    printf("============\n");
    printf("X=\n");
    printf("============\n");
    afficheVect(X,N);

    return 0;
}