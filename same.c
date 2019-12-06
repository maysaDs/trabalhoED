#include <stdio.h>
#include <stdlib.h>


struct posicao{
    int l;
    int c;
};
//fila de posições
struct filaP{
    struct posicao elem[50];
    int inicio;
    int fim;
    int tamMax;
};
//fila de inteiros
struct filaI{
    int elem[50];
    int inicio;
    int fim;
    int tamMax;
};
//inicializa fila de posições
void inicializaFilaP(struct filaP *q){
    q->inicio = -1;
    q->fim = -1;
}
//inicializa fila de inteiros
void inicializaFilaI(struct filaI *q){
    q->inicio = -1;
    q->fim = -1;
}
//verifica se a fila de posiçoes ta vazia
int filaVaziaP(struct filaP *q){
    return q->inicio == q->fim;

}
//verifica se a fila de inteiros ta vazia
int filaVaziaI(struct filaI *q){
    return q->inicio == q->fim;

}
int filaCheiaI(struct filaI *q){
    return q->fim == q->tamMax;
}
int filaCheiaP(struct filaP *q){
    return q->fim == q->tamMax;
}
//desloca fila de posições
void deslocaFilaP(struct filaP *q){
    int desloc = q->inicio + 1;
    for (int i = desloc; i < q->fim; i++){
        q->elem[i-desloc] = q->elem[i];
    }
    q->inicio = -1;
    q->fim = q->fim-desloc;
}
//desloca fila de inteiros
void deslocaFilaI(struct filaI *q){
    int desloc = q->inicio + 1;
    for (int i = desloc; i < q->fim; i++){
        q->elem[i-desloc] = q->elem[i];
    }
    q->inicio = -1;
    q->fim = q->fim-desloc;
}
//insere na fila de posições
void insereFilaP(struct filaP *q, struct posicao *x){
    if(!filaCheiaP(q)){
        if(q->fim == q->tamMax){
            deslocaFilaP(q);
        }
        q->fim = q->fim+1;
        q->elem[q->fim] = *x;
    }
}
//insere na fila de inteiros
void insereFilaI(struct filaI *q, int x){
    if(!filaCheiaI(q)){
        if(q->fim == q->tamMax){
            deslocaFilaI(q);
        }
        q->fim = q->fim+1;
        q->elem[q->fim] = x;
    }
}
//remove na fila de posições
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
//remove na fila de inteiros
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
//retorna o primeiro da fila de posiçoes
struct posicao primeiroDaFilaP(struct filaP *q){
    if(!filaVaziaP(q)){
        return q->elem[q->inicio+1];
    }else{
        printf("erro");
    }
}
//retorna o primeiro da fila de inteiros
int primeiroDaFilaI(struct filaI *q){
    if(!filaVaziaI(q)){
        return q->elem[q->inicio+1];
    }else{
        printf("erro");
    }
}
//funcao q realiza a busca e "limpa" o tabuleiro do jogo
void busca(int m[12][16], int par, int l, int c){
    struct filaP a;
    struct filaP *q = &a;
    q->tamMax = 12*16;
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
            if(b->c + 1 < 16){
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
//função que realoca as linhas
void realocaLinhas(int m[12][16]){
    struct filaI teste;
    struct filaI *a = &teste;
    int cont = 0;
    a->tamMax = 20;
    inicializaFilaI(a);
    for (int j = 15; j >= 0; j--){
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
//função que realoca as colunas
void realocaColunas(int m[12][16]){
    struct filaI teste;
    struct filaI *a = &teste;
    int cont = 0;
    int aux = 0;
    a->tamMax = 12;
    inicializaFilaI(a);
    while(aux < 16){
        if(m[11][cont]==0){
            for (int j = 0; j < 12; j++){
               for (int k = cont; k < 15; k++){
                   m[j][k] = m[j][k+1];
               }
               
            }
            for (int l = 0; l< 12;l++){
                   m[l][15] = 0;
               }
               aux ++;
            
        }else{
            cont++;
            aux++;
        }
        
    }
}
//função que popula o tabuleiro do jogo de forma randomica
void populaMatriz(int m[12][16]){
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
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
//função que imprime a matriz
void imprime(int m[12][16]){
	printf("\033[0mX  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            if(j == 0){
                if(i<10){
                	printf("\033[0m%i  ",i);
                }else {
                    printf("\033[0m%i ", i);
                }
            }
            if(j > 11){
              if(m[i][j] == 1){
                	printf("\033[0;31m\u29E0  ");
              } else if(m[i][j] == 2){
                	printf("\033[0;34m\u29E0  ");
              } else if(m[i][j] == 3) {
                  	printf("\033[0;32m\u29E0  ");
              } else {
              		printf("   ");
              }
         	} else {
            	if(m[i][j] == 1){
					//vermelho
            	    printf("\033[0;31m\u29E0  ");
            	} else if(m[i][j] == 2){
					//azul
                	printf("\033[0;34m\u29E0  ");
            	} else if(m[i][j] == 3) {
					//verde
                 	printf("\033[0;32m\u29E0  ");
            	} else {
            		printf("   ");
          		}
        	}
    	}
    	printf("\033[0m\n");
	}
}
//funcao responsavel por realizar e gerencias as jogadas
void jogada(int m[12][16]){
    int l;
    int c;
    imprime(m);
    printf("DIGITE A LINHA DEPOIS A COLUNA \n");
    scanf("%d", &l);
    scanf("%d", &c);
    if(l>11 || c > 15){
        printf("posição invalida, tente novamente");
    }else{
        busca(m,m[l][c],l,c);
        realocaLinhas(m);
        realocaColunas(m);
    }

}
//função que percorre a matriz e ve se o jogo acabou
int fimDeJogo(int m[12][16]){
    int a = 0;
    for (int i = 0; i <12; i++){
        for (int j = 0; j < 16; j++){
            if (m[i][j]!=0){
                if (m[i][j] == m[i][j+1] || m[i][j] == m[i+1][j]){
                    a = 1;
                } 
            } 
        }
    }
    return a;
}
//função que determina se o jogador ganhou ou perdeu
void vencedor(int m[12][16]){
    int a = 0;
    for (int i = 0; i <12; i++){
        for (int j = 0; j < 16; j++){
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
    int m[12][16];
    populaMatriz(m);
    while(fimDeJogo(m))
    {
       jogada(m);
    }
    printf("FIM DE JOGO");
    imprime(m);
    vencedor(m);

    return 0;

}