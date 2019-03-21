# -*- coding: utf-8 -*-
"""
Created on Sat Mar 16 18:38:39 2019

@author: Eduardo
"""

import pandas as pd 
previsores = pd.read_csv("dataset/entradas-breast.csv")
classes = pd.read_csv("dataset/saidas-breast.csv")


from sklearn.model_selection import train_test_split
previsores_treinamento, previsores_treste, classe_treinamento, classe_teste = train_test_split(previsores, classes, test_size=0.25)            

import keras
from keras.models import Sequential
from keras.layers import Dense

classificador = Sequential()
classificador.add(Dense(units = 16, activation = 'relu', 
                        kernel_initializer = 'random_uniform', input_dim = 30))
classificador.add(Dense(units = 1, activation = 'sigmoid'))

classificador.compile(optimizer = 'adam', loss = 'binary_crossentropy',
                      metrics = ['binary_accuracy'])

classificador.fit(previsores_treinamento, classe_treinamento,
                  batch_size = 10, epochs = 100)