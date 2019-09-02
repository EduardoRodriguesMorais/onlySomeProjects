# -*- coding: utf-8 -*-
"""
Created on Sat Aug 24 00:40:38 2019

@author: Eduardo Morais
"""



def olamundo(dic1, dic2):
    return str(L1[2]['k1'][2][2]['k3']) + " "+ str(D1['c1']['c1'][2]['c4'])


L1 = [ 0, 2, { 'k1' : [ 32, 0, [ 1, 2, { 'k2' : 2, 'k3' : 'Olá' } ] ] } ]
D1 = { 'c1' : { 'c1' : [ 0, 21, { 'c2' : 'oi', 'c4' : 'Mundo' }, 4 ] },'c3':35 }

if __name__ == "__main__":    
    print(olamundo(L1, D1))