# -*- coding: utf-8 -*-
"""
Created on Sat Aug 24 00:40:38 2019

@author: Eduardo Morais
"""

def get_tupla(cidade, codigo, populacao):
    tupla = ()
    tupla = tupla + (cidade ,codigo, populacao, )
    return tupla

def get_dic(tupla):
    dic =  {'Cidade': tupla[0], 'Codigo': tupla[1], 'Populacao': tupla[2]}
    return dic

def return_a(dic): 
    print("\n\n\nItens informados\nCidade: {} \nCódigo: {} \nPopulação: {}".format(dic['Cidade'], dic['Codigo'], dic['Populacao']))    

if __name__ == "__main__": 
    cidade = input("Cidade: ")
    codigo = input("Código: ")
    populacao = input("População: ")
    
    tupla = get_tupla(cidade, codigo, populacao)
    dic = get_dic(tupla)
    return_a(dic)