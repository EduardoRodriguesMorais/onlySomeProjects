# -*- coding: utf-8 -*-
"""
Created on Tue Apr  2 12:07:52 2019

@author: Eduardo
"""

import pandas as pd 
import keras
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras.wrappers.scikit_learn import KerasClassifier

previsores = pd.read_csv("dataset/entradas-breast.csv")
classes = pd.read_csv("dataset/saidas-breast.csv")

def criaModelo(optimizer, loos, kernel_initializer, activation, neurons):
    model = Sequential()
    #Adiciona forma a novo modelo. 16 camadas de profundidade, função de ativação relu, inicialização randômica, 30 camadas de entrada. 
    model.add(Dense(units = neurons, activation = activation, kernel_initializer = kernel_initializer, input_dim = 30))
    model.add(Dropout(0.3))
    model.add(Dense(units = 32, activation = activation, kernel_initializer = kernel_initializer))
    model.add(Dropout(0.3))
    #Adiciona camada de saída. 1 neurônio de saída, função de ativação sigmoid 
    model.add(Dense(units = 1, activation = 'sigmoid'))
    #Configuta o modelo para treinamento. Calculo de ajuste dos pesos(Descida do Gradiente Adam), classificação binária, métrica para avaliação do modelo
    model.compile(optimizer = optimizer, loos = loos, metrics = ['binary_accuracy'])
    return model