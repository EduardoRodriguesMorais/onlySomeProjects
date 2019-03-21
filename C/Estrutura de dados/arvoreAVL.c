// Sintese
//   objetivostruct nodo: Arvore Binaria de Busca Balanceada (AVL): Inclusao, pesquisa, caminhamento (in, pre, pos-order), desenho, delecao
//   autor...: Eduardo Rodrigues de Morais
//  

#include <stdio.h>
#include <stdlib.h>

// Declaracao do no/nodo
typedef struct tNodo
{
    int dado;
    struct tNodo *esq;
    struct tNodo *dir;
};

// Prototipo das funcoes
int menu(void);
void incluir(struct tNodo **, int);
void excluir(struct tNodo **, int);
struct tNodo *menor(struct tNodo *);
void desenharParentese(struct tNodo *);
void desenhar(struct tNodo *);
void desenharMontarMatriz(char[9][16], struct tNodo *, int, int, int);
void desenharMatriz(char[9][16]);
int altura(struct tNodo *);
void balancear(struct tNodo **);
int fatorBalanceamento(struct tNodo *);
void rotacaoSimplesDireita(struct tNodo **);
void rotacaoSimplesEsquerda(struct tNodo **);
void rotacaoDuplaDireita(struct tNodo **);
void rotacaoDuplaEsquerda(struct tNodo **);
struct tNodo *pesquisar(struct tNodo *, int);
void inOrder(struct tNodo *);
void preOrder(struct tNodo *);
void posOrder(struct tNodo *);
void destruir(struct tNodo *);

int main(void)
{
    struct tNodo *raiz = NULL;
    int op, valor;
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            printf("\n\n*** INCLUIR ***\n\n");
            printf("Digite o valor: ");
            scanf("%d", &valor);
            incluir(&raiz, valor);
            desenhar(raiz);
            break;
        case 2:
            printf("\n\n*** EXCLUIR ***\n\n");
            printf("Digite o valor: ");
            scanf("%d", &valor);
            excluir(&raiz, valor);
            desenhar(raiz);
            break;
        case 3:
            printf("\n\n*** DESENHAR COM PARENTESES ***\n\n");
            printf("Altura: %d\n", altura(raiz));
            printf("Valor entre colchetes e o Fator de Balanceamento\n\n");
            desenharParentese(raiz);
            break;
        case 4:
            printf("\n\n*** DESENHAR ***\n\n");
            desenhar(raiz);
            break;
        case 5:
            printf("\n\n*** PESQUISAR ***\n\n");
            printf("Digite o valor: ");
            scanf("%d", &valor);
            if (pesquisar(raiz, valor))
                printf("ACHOU");
            else
                printf("NAO ACHOU");
            break;
        case 6:
            printf("\n\n*** MOSTRAR - IN-ORDER ***\n\n");
            inOrder(raiz);
            break;
        case 7:
            printf("\n\n*** MOSTRAR - PRE-ORDER ***\n\n");
            preOrder(raiz);
            break;
        case 8:
            printf("\n\n*** MOSTRAR - POST-ORDER ***\n\n");
            posOrder(raiz);
        }
    } while (op != 0);
    destruir(raiz);
    return 0;
}

int menu(void)
{
    int op;
    do
    {
        printf("\n\n*** MENU ***\n\n");
        printf("1. Incluir\n");
        printf("2. Excluir\n");
        printf("3. Desenhar com parenteses\n");
        printf("4. Desenhar\n");
        printf("5. Pesquisar\n");
        printf("6. Mostrar - in-order\n");
        printf("7. Mostrar - pre-order\n");
        printf("8. Mostrar - pos-order\n");
        printf("0. Sair\n\n");
        printf("Digite sua opcao: ");
        scanf("%d", &op);
        if ((op < 0) || (op > 8))
            printf("Opcao invalida!\n\n");
    } while ((op < 0) || (op > 8));
    return op;
}

void incluir(struct tNodo **p, int v){
    if ((*p) == NULL){
        (*p) = (struct tNodo *)malloc(sizeof(struct tNodo));
        (*p)->dado = v;
        (*p)->esq = (*p)->dir = NULL;
    }
    else{

        if (v < (*p)->dado){
            incluir(&((*p)->esq), v);
        }
            
        if (v > (*p)->dado){
            incluir(&((*p)->dir), v);
        }
            
        balancear(p);
    }
}

void balancear(struct tNodo **p){

    int fb = fatorBalanceamento(*p);
    if ((fb == 2) && (fatorBalanceamento((*p)->dir) == 1)){
        rotacaoSimplesEsquerda(&(*p));
    }
        
    if ((fb == 2) && (fatorBalanceamento((*p)->dir) == -1)){
        rotacaoDuplaEsquerda(&(*p));
    }
        
    if ((fb == -2) && (fatorBalanceamento((*p)->esq) == -1)){
        rotacaoSimplesDireita(&(*p));
    }
        
    if ((fb == -2) && (fatorBalanceamento((*p)->esq) == 1)){
        rotacaoDuplaDireita(&(*p));
    }
        
}

void excluir(struct tNodo **p, int v){
    struct tNodo *q;
    
    if ((*p) == NULL){
        return;
    } 

    if (v < (*p)->dado){
        excluir(&((*p)->esq), v);
    }else{
        if (v > (*p)->dado){
            excluir(&((*p)->dir), v);
        }else{ 
            if (((*p)->esq == NULL) && ((*p)->dir == NULL)){ // (v == (*p)->dado) == Excluir
                free(*p);
                (*p) = NULL;
            }else{
                if ((*p)->esq == NULL){
                    q = (*p);
                    (*p) = q->dir;
                    free(q);
                }else{
                    if ((*p)->dir == NULL){
                        q = (*p);
                        (*p) = q->esq;
                        free(q);
                    }else{ // tem 2 filhos
                        q = menor((*p)->dir);
                        (*p)->dado = q->dado;
                        excluir(&((*p)->dir), q->dado);
                    }
                }
            }
        }
    }
    balancear(p);
}

struct tNodo *menor(struct tNodo *p){
    if (p == NULL){
        return NULL;
    }
        
    if (p->esq == NULL){
        return p;
    }
        
    return menor(p->esq);
}

void desenharParentese(struct tNodo *p){
    if (p != NULL){
        printf("%d[%d](", p->dado, fatorBalanceamento(p));
        desenharParentese(p->esq);
        printf(",");
        desenharParentese(p->dir);
        printf(")");
    }
}

void desenhar(struct tNodo *p){
    char matrizDesenho[9][16]; // lxc
    int l, c;
    for (l = 0; l < 9; l++){
        for (c = 0; c < 16; c++){
            matrizDesenho[l][c] = -1;
        }
    }
    desenharMontarMatriz(matrizDesenho, p, 0, 15, 0);
    desenharMatriz(matrizDesenho);
}

void desenharMontarMatriz(char mat[9][16], struct tNodo *p, int colIni, int colFim, int lin){
    int colMeio = (colIni + colFim) / 2;
    if (p == NULL){
        return;
    }
    mat[lin][colMeio] = p->dado;
    if (p->esq != NULL){
        mat[lin + 1][(((colIni + colMeio) / 2) + colMeio) / 2] = '/';
        desenharMontarMatriz(mat, p->esq, colIni, colMeio, lin + 2);
    }
    if (p->dir != NULL){
        mat[lin + 1][(((colMeio + colFim) / 2) + colMeio) / 2] = '\\';
        desenharMontarMatriz(mat, p->dir, colMeio, colFim, lin + 2);
    }
}

void desenharMatriz(char mat[9][16]){
    int l, c;
    for (l = 0; l < 9; l++){
        for (c = 0; c < 16; c++){
            if (mat[l][c] == -1){
                printf("    ");
            }else if ((mat[l][c] == '\\') || (mat[l][c] == '/')){
                printf("  %c ", mat[l][c]);
            }else{
                printf("(%2d)", mat[l][c]);
            }
        }    
        printf("\n");
    }
}

int altura(struct tNodo *p){
    int dir, esq;
    if (p == NULL){
        return 0;
    }
        
    dir = altura(p->esq);
    esq = altura(p->dir);
    
    if (dir > esq){
        return dir + 1;
    }

    return esq + 1;
}

int fatorBalanceamento(struct tNodo *p){
    if (p == NULL){
        return 0;
    }

    return altura(p->dir) - altura(p->esq);
}

void rotacaoSimplesDireita(struct tNodo **p){
    struct tNodo *q, *temp;
    q = (*p)->esq;
    temp = q->dir;
    q->dir = (*p);
    (*p)->esq = temp;
    (*p) = q;
}

void rotacaoSimplesEsquerda(struct tNodo **p){
    struct tNodo *q, *temp;
    q = (*p)->dir;
    temp = q->esq;
    q->esq = (*p);
    (*p)->dir = temp;
    (*p) = q;
}

void rotacaoDuplaDireita(struct tNodo **p){
    rotacaoSimplesEsquerda(&(*p)->esq);
    rotacaoSimplesDireita(&(*p));
}

void rotacaoDuplaEsquerda(struct tNodo **p){
    rotacaoSimplesDireita(&((*p)->dir));
    rotacaoSimplesEsquerda(&(*p));
}

struct tNodo *pesquisar(struct tNodo *p, int v){
    if (p == NULL){
        return NULL;
    }
        
    printf("%d - ", p->dado);

    if (v == p->dado){
        return p;
    }
        
    if (v < p->dado){
        return pesquisar(p->esq, v);
    }
        
    return pesquisar(p->dir, v);
}

void inOrder(struct tNodo *p){
    if (p != NULL){
        inOrder(p->esq);
        printf("%d - ", p->dado);
        inOrder(p->dir);
    }
}

void preOrder(struct tNodo *p){
    if (p != NULL){
        printf("%d - ", p->dado);
        preOrder(p->esq);
        preOrder(p->dir);
    }
}

void posOrder(struct tNodo *p){
    if (p != NULL){
        posOrder(p->esq);
        posOrder(p->dir);
        printf("%d - ", p->dado);
    }
}

void destruir(struct tNodo *p){
    if (p != NULL){
        destruir(p->esq);
        destruir(p->dir);
        free(p);
    }
}