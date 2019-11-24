#include <stdio.h>
#include <stdlib.h>


struct posicao{
    int l;
    int c;
};
struct filaP{
    struct posicao elem[50];
    int inicio;
    int fim;
    int tamMax;
};
struct filaI{
    int elem[50];
    int inicio;
    int fim;
    int tamMax;
};
void inicializaFilaP(struct filaP *q){
    q->inicio = -1;
    q->fim = -1;
}
void inicializaFilaI(struct filaI *q){
    q->inicio = -1;
    q->fim = -1;
}
int filaVaziaP(struct filaP *q){
    return q->inicio == q->fim;

}
int filaVaziaI(struct filaI *q){
    return q->inicio == q->fim;

}
int filaCheiaP(struct filaP *q){
    return (q->inicio == -1) && (q->fim == q->tamMax);

}
int filaCheiaI(struct filaI *q){
    return (q->inicio == -1) && (q->fim == q->tamMax);

}
void deslocaFilaP(struct filaP *q){
    int desloc = q->inicio + 1;
    for (int i = desloc; i < q->fim; i++){
        q->elem[i-desloc] = q->elem[i];
    }
    q->inicio = -1;
    q->fim = q->fim-desloc;
}
void deslocaFilaI(struct filaI *q){
    int desloc = q->inicio + 1;
    for (int i = desloc; i < q->fim; i++){
        q->elem[i-desloc] = q->elem[i];
    }
    q->inicio = -1;
    q->fim = q->fim-desloc;
}
void insereFilaP(struct filaP *q, struct posicao *x){
    if(!filaCheiaP(q)){
        if(q->fim == q->tamMax){
            deslocaFilaP(q);
        }
        q->fim = q->fim+1;
        q->elem[q->fim] = *x;
    }
}
void insereFilaI(struct filaI *q, int x){
    if(!filaCheiaI(q)){
        if(q->fim == q->tamMax){
            deslocaFilaI(q);
        }
        q->fim = q->fim+1;
        q->elem[q->fim] = x;
    }
}
struct posicao removeFilaP(struct filaP *q){
    struct posicao x;
    if(!filaVaziaP(q)){
        q->inicio = q->inicio + 1;
        x = q->elem[q->inicio];
        if (filaVaziaP(q)){
            inicializaFilaP(q);
        }
        
    }
    return x;
}
int removeFilaI(struct filaI *q){
    int x;
    if(!filaVaziaI(q)){
        q->inicio = q->inicio + 1;
        x = q->elem[q->inicio];
        if (filaVaziaI(q)){
            inicializaFilaI(q);
        }
        
    }
    return x;
}
struct posicao primeiroDaFilaP(struct filaP *q){
    if(!filaVaziaP(q)){
        return q->elem[q->inicio+1];
    }else{
        printf("erro");
    }
}
int primeiroDaFilaI(struct filaI *q){
    if(!filaVaziaI(q)){
        return q->elem[q->inicio+1];
    }else{
        printf("erro");
    }
}
void busca(int m[12][19], int par, int l, int c){
    struct filaP a;
    struct filaP *q = &a;
    q->tamMax = 12*19;
    inicializaFilaP(q);
    struct posicao ci;
    struct posicao ba;
    struct posicao di;
    struct posicao es;
    struct posicao pri;
    struct posicao *b = &pri;
    struct posicao *cima = &ci;
    struct posicao *baixo = &ba;
    struct posicao *esq = &es;
    struct posicao *dir = &di;
    b->l = l;
    b->c = c;
    insereFilaP(q,b);
    while (!filaVaziaP(q)){
        *b = primeiroDaFilaP(q);
        if(m[b->l][b->c]==par||m[b->l][b->c]==0){
            m[b->l][b->c] = 0;
            if(b->l + 1 < 12){
                cima->l = b->l + 1;
                cima->c = b->c;
                if (m[cima->l][cima->c]==par){
                    m[cima->l][cima->c] = 0;
                    insereFilaP(q, cima);
                } 
            }
            if(b->l - 1 >=0){
                baixo->l = b->l - 1;
                baixo->c = b->c;
                if (m[baixo->l][baixo->c]==par){
                    m[baixo->l][baixo->c] = 0;
                    insereFilaP(q, baixo);
                } 
            }
            if(b->c + 1 < 19){
                dir->l = b->l;
                dir->c = b->c + 1;
                if (m[dir->l][dir->c]==par){
                    m[dir->l][dir->c] = 0;
                    insereFilaP(q, dir);
                } 
            }
            if(b->c - 1 >=0){
                esq->l = b->l;
                esq->c = b->c - 1;
                if (m[esq->l][esq->c]==par){
                    m[esq->l][esq->c] = 0;
                    insereFilaP(q, esq);
                } 
            }
        }
        removeFilaP(q);
    }
}
void realocaColunas(int m[12][19]){
    struct filaI teste;
    struct filaI *a = &teste;
    int cont = 0;
    a->tamMax = 20;
    inicializaFilaI(a);
    for (int j = 18; j >= 0; j--){
        for (int k = 11; k >= 0; k--){
            if(m[k][j]!=0){
                insereFilaI(a,m[k][j]);
            }
        }
        cont = 0;
        for (int i = 0; i < 11-a->fim; i++){
            m[cont][j] = 0;
            cont++;

        }
        for (int i = 11; i >= 11-a->fim; i--){
            m[i][j] = primeiroDaFilaI(a);
            removeFilaI(a);

        }
        inicializaFilaI(a);
        cont = 0;
    }
    
}
void realocaLinhas(int m[12][19]){
    struct filaI teste;
    struct filaI *a = &teste;
    int cont = 0;
    int aux = 0;
    a->tamMax = 12;
    inicializaFilaI(a);
    while(aux < 19){
        if(m[11][cont]==0){
            for (int j = 0; j < 12; j++){
               for (int k = cont; k < 18; k++){
                   m[j][k] = m[j][k+1];
               }
               
            }
            for (int l = 0; l< 12;l++){
                   m[l][18] = 0;
               }
               aux ++;
            
        }else{
            cont++;
            aux++;
        }
        
    }
}
void populaMatriz(int m[12][19]){
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            int a = rand() % 100000;
            if (a<33333)
            {
                m[i][j] = 1;
            }else if(a<66666){
                m[i][j] = 2;
            }else{
                m[i][j] = 3;
            }
            
        }
        
    }
    
}
void imprime(int m[12][19]){
    printf("\n");
    for(int i = 0; i < 12; i++){
       
        for(int j = 0; j < 19; j++){
            printf("%d ", m[i][j]);
        }
         printf("\n");
    
    }
}
void jogada(int m[12][19]){
    int l;
    int c;
    imprime(m);
    printf("DIGITE A LINHA DEPOIS A COLUNA \n");
    scanf("%d", &l);
    scanf("%d", &c);
    if(l>11 || c > 18){
        printf("posição invalida, tente novamente");
    }else{
        busca(m,m[l][c],l,c);
        realocaColunas(m);
        realocaLinhas(m);
    }

}
int fimDeJogo(int m[12][19]){
    int a = 0;
    for (int i = 0; i <12; i++){
        for (int j = 0; j < 19; j++){
            if (m[i][j]!=0){
                if (m[i][j] == m[i][j+1] || m[i][j] == m[i+1][j]){
                    a = 1;
                } 
            } 
        }
    }
    return a;
}
void vencedor(int m[12][19]){
    int a = 0;
    for (int i = 0; i <12; i++){
        for (int j = 0; j < 19; j++){
            if (m[i][j]!=0){
                    a = 1;
            } 
        }
    }
    if (a == 1){
        printf("voce perdeu");
    }else{
        printf("voce perdeu");
    }
    
}
int main(){
    int m[12][19];
    populaMatriz(m);
    while(fimDeJogo(m))
    {
       jogada(m);
    }
    printf("FIM DE JOGO");
    imprime(m);
    vencedor(m);

    
    /*imprime(m);
    busca(m,m[2][2],2,2);
    imprime(m);
    realocaColunas(m);
    imprime(m);
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 19; j++){
            scanf("%d", &m[i][j]);
    }
    }
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 19; j++){
            printf("%d", m[i][j]);
        }
    printf("\n");
    }
    busca(m,1,1,1);
    printf("\n");
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 19; j++){
            printf("%d", m[i][j]);
        }
    printf("\n");
    }
    printf("\n");
    printf("\n");
    realocaColunas(m);
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 19; j++){
            printf("%d", m[i][j]);
        }
    printf("\n");
    }
    printf("\n");
    printf("\n");
    realocaLinhas(m);
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 19; j++){
            printf("%d", m[i][j]);
        }
    printf("\n");
    }*/
    return 0;

}