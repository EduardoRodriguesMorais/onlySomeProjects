#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 10 14:40:46 2019
@author: eduardo-morais
    Objetivo: Encontrar melhor peso. Reconhece operador XOR 
   (Problema Não Linearmente Separável)
"""

import numpy as np

def sigmoid(soma):
    return 1 / (1 + np.exp(-soma))

entradas = np.array([ [0,0],
                      [0,1],
                      [1,0],
                      [1,1]])
saidas = np.array([ [0],[1],[1],[0] ])
pesos0 = np.array([ [] 
                  ])