def marque_atacadas(tabuleiro, posicao_X, posicao_Y):
    """
    Altera tab marcando as posicoes atacadas por R com X
    """
    #Anda horizontal direita
    for y in range(posicao_Y+1, len(tabuleiro)): 
        tabuleiro[posicao_X][y] = '|\033[1;31m M \033[0;0m' 

    #Anda horizontal esquerda
    for y in range(0, posicao_Y): 
        tabuleiro[posicao_X][y] = '|\033[1;31m M \033[0;0m' 

    #Anda vertical subindo
    for x in range(posicao_X-1, -1, -1):
        tabuleiro[x][posicao_Y] = '|\033[1;31m M \033[0;0m' 
    
    #Anda vertical descendo
    for x in range(posicao_X+1, 8, 1):
        tabuleiro[x][posicao_Y] = '|\033[1;31m M \033[0;0m' 
    
    #Anda diagonal direita descendo    
    y_rainha = posicao_Y
    for x in range(posicao_X+1, 8, 1):    
        y_rainha += 1
        if y_rainha < 0 or y_rainha > 7:
            break
        tabuleiro[x][y_rainha] = '|\033[1;31m M \033[0;0m'

    #Anda diagonal esquerda subindo
    y_rainha = posicao_Y
    for x in range(posicao_X-1, -1, -1 ):  
        y_rainha -= 1
        if y_rainha < 0:
            break
        tabuleiro[x][y_rainha] = '|\033[1;31m M \033[0;0m' 

    #Anda diagonal esquerda descendo
    y_rainha = posicao_Y
    for x in range(posicao_X+1, 8, 1):    
        y_rainha -= 1
        if y_rainha < 0 or y_rainha > 7:
            break
        tabuleiro[x][y_rainha] = '|\033[1;31m M \033[0;0m'

    #Anda diagonal direita subindo
    y_rainha = posicao_Y
    for x in range(posicao_X-1, -1, -1 ):  
        y_rainha += 1
        if y_rainha < 0 or y_rainha > 7:
            break
        tabuleiro[x][y_rainha] = '|\033[1;31m M \033[0;0m' 


def define_rainha(tabuleiro, posicao_X, posicao_Y):
    tabuleiro[posicao_X][posicao_Y] = '|\033[1;32m R \033[0;0m'
    
def imprime_tabuleiro(tabuleiro):
    for x in range(len(tabuleiro)):
        print(" ---------------------------------")
        for y in range(len(tabuleiro)):
            print(tabuleiro[x][y], end="")
        print("| \n")
    
def main():
    posicao_X = int(input("Informe a posição X: "))-1
    posicao_Y = int(input("Informe a posição Y: "))-1
    
    x = ('| x ','| x ','| x ','| x ','| x ','| x ','| x ','| x ')

    tabuleiro= [list(x),
                list(x),
                list(x),
                list(x),
                list(x),
                list(x),
                list(x),
                list(x)]
    
    define_rainha(tabuleiro, posicao_X, posicao_Y)
    
    marque_atacadas(tabuleiro, posicao_X, posicao_Y)
        
    imprime_tabuleiro(tabuleiro)

if __name__ == "__main__":
    main()