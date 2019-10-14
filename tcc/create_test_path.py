import shutil
import os
from random import randint

def calcula_porcentagem(vlr, prtg):
    return vlr *(prtg/100)

def move_files(lista_len, oldAdress, newAdress):
    lista = os.listdir(oldAdress)
    list_indices = []

    while len(list_indices) < lista_len:         
        img = randint(0,lista_len)
        if img not in list_indices:
            caminhoCompleto_old = oldAdress + lista[img] #variável recebe caminho + arquivo, conforme indice
            caminhoCompleto_new = newAdress + lista[img] 
            list_indices.append(img)
            
            print(f"[{img}] De: {caminhoCompleto_old} ----para----> {caminhoCompleto_new}")
            #shutil.move(caminhoCompleto_old, caminhoCompleto_new) #módulo 'shutil.move()' move os arquivos

def create_path(skin, qtd_imgs, oldAdress, newAdress):
    loc = f'{oldAdress}/{skin}/'
    dest = f'{newAdress}/{skin}/'
    
    move_files(qtd_imgs , loc, dest)



if __name__ == "__main__":

    skins_lesions = {
        'akiec': 0,
        'bcc': 0,
        'bkl': 0,
        'df': 0,
        'mel': 0,
        'nv': 0, 
        'vasc': 0
    }

    trainAdress = 'D:/Projetos/TCC/dataset/skin-cancer/dataset/train' #pasta origem
    tstAdress = 'D:/Projetos/TCC/dataset/skin-cancer/dataset/teste' #pasta destino
    valAdress = 'D:/Projetos/TCC/dataset/skin-cancer/dataset/valid' #pasta destino

    lista = os.listdir(trainAdress) #lista separando apenas os arquivos do caminho.

    qtd_total= 0
    for skin in skins_lesions:
        qtd_total = int (len(os.listdir(f'{trainAdress}/{skin}')))
        vlrprt =int(calcula_porcentagem(qtd_total, 30)) 
        print(qtd_total, vlrprt)
        
        create_path(skin, vlrprt, trainAdress, valAdress)