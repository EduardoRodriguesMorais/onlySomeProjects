
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
        for y in range(len(tabuleiro)):
            print(tabuleiro[x][y], end="")
        print("| \n")

if __name__ == "__main__":
    main()