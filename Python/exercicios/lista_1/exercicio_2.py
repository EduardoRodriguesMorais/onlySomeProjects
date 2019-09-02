# -*- coding: utf-8 -*-
"""
Created on Sat Aug 24 00:40:38 2019

@author: Eduardo Morais
"""


def verifica(qtd_numeros_primos, numero, max_primo):    
    if qtd_numeros_primos <= numero and max_primo <= numero:
        dic_result['maior_primo'] = max_primo
        dic_result['qtd_num_primos_menorigual'] = qtd_numeros_primos
        print(dic_result)
      
def get_valores(primos):
    max_primo = max(primos)
    maior_primo = 0
    qtd_numeros_primos = len(primos)
    if maior_primo < max_primo :
        maior_primo = max_primo
        verifica(qtd_numeros_primos, numero, maior_primo)

def get_maior_primo(numero):
    primos = ()
    for x in range( numero + 1):
        primos = get_primos(x)
        if primos is not None:     
            get_valores(primos)
                
def get_primos(numero):
    divisivel = 0
    primos = ()
    for x in range(1, numero + 1):
        if  numero % x == 0  :      
            primos = primos + (x ,)
            divisivel += 1
    
    if divisivel == 2:
        print("Primos: {}".format(primos))
        return  primos 
    return None



dic_result = {'maior_primo': 0, 'qtd_num_primos_menorigual': 0}

if __name__ == "__main__":     
    numero = int (input("Informe o numéro: "))
    get_maior_primo( numero)
    print("\nMaior numéro primo {}\nQuantidade de numéros primos menores ou iguais a {}: {}".format(dic_result['maior_primo'], numero, dic_result['qtd_num_primos_menorigual']))
    
    
    
    