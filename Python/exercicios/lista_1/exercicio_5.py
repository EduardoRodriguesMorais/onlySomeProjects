# -*- coding: utf-8 -*-
"""
Created on Sat Aug 24 00:40:38 2019

@author: Eduardo Morais
"""


def imprime_valores(n, i, j): 
    cont = 0 #conta quantos múltiplos foram impressos.
    cm = 0 #candidato a múltiplo.
    while cont < n:
        if cm%i == 0 or cm%j == 0:
            print(cm , end=" ")
            cont += 1
        cm += 1
    
if __name__ == "__main__":  
    print("Cálculo dos n primeiros múltiplos de i ou de j")
    n = int(input("Digite n: "))
    i = int(input("Digite i: "))
    j = int(input("Digite j: "))  
    imprime_valores(n, i, j)