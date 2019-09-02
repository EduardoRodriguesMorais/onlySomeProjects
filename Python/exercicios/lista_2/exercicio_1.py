#def movimento_rainha():
#    for(i=i+9; i<64 && i+9==VAZIO; i+=9)// diagonal esquerda superior
#        peca[i+9]==RAINHA
#
#    for(i=i-9; i>=0 && i-9==VAZIO; i-=9)// diagonal direita inferior
#        peca[i-9]==RAINHA
#
#    for(i=i+7; i<64 && i+7==VAZIO; i+=7)// diagonal direita superior
#        peca[i+7]==RAINHA
#
#    for(i=i-7; i>=0 && i-7==VAZIO; i-=7)// diagonal esquerda inferior
#        peca[i-7]==RAINHA
#
#    for(i=i+8; i<64 && i+8==VAZIO; i+=8)// frente superior
#        peca[i+8]==RAINHA
#
#    for(i=i-8; i>=0 && i-8==VAZIO; i-=8)// diagonal direita inferior
#        peca[i-8]==RAINHA
#
#    for(i=i+1; i<64 && i+1==VAZIO; i+=1)// diagonal direita superior
#        peca[i+1]==RAINHA
#
#    for(i=i-1; i>=0 && i-1==VAZIO; i-=1)// diagonal esquerda inferior
#        peca[i-1]==RAINHA


def marque_atacadas(tab):
    """
    Altera tab marcando as posicoes atacadas por R com X
    """
    # escreva a sua funcao aqui
def main():
    
    x = ('| x ','| x ','| x ','| x ','| x ','| x ','| x ','| x ')

    tabuleiro = [ list(x),
                    list(x),
                    list(x),
                    list(x),
                    list(x),
                    list(x),
                    list(x),
                    list(x) ]
    
    marque_atacadas(tabuleiro)
    
    define_rainha(tabuleiro, 7, 3)
    
    imprime_tabuleiro(tabuleiro)
    

def define_rainha(tabuleiro, posicao_X, posicao_Y):
    tabuleiro[posicao_X][posicao_Y] = '| R '
    
def imprime_tabuleiro(tabuleiro):
    for x in range(len(tabuleiro)):
        print("-------------------------------")
        for y in range(len(tabuleiro)):
            print(tabuleiro[x][y], end="")
        print("| \n")

if __name__ == "__main__":
    main()
