# -*- coding: utf-8 -*-
"""
Created on Mon Apr  1 23:08:33 2019

@author: Eduardo
"""

import pandas as pd 
import keras
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import cross_val_score

previsores = pd.read_csv("dataset/entradas-breast.csv")
classes = pd.read_csv("dataset/saidas-breast.csv")

def criaModelo():
    model = Sequential()
    #Adiciona forma a novo modelo. 16 camadas de profundidade, função de ativação relu, inicialização randômica, 30 camadas de entrada. 
    model.add(Dense(units = 16, activation = 'relu', kernel_initializer = 'random_uniform', input_dim = 30))
    model.add(Dropout(0.3))
    model.add(Dense(units = 32, activation = 'relu', kernel_initializer = 'random_uniform'))
    model.add(Dropout(0.3))
    #Adiciona camada de saída. 1 neurônio de saída, função de ativação sigmoid 
    model.add(Dense(units = 1, activation = 'sigmoid'))
    optimizer = keras.optimizers.Adam(lr = 0.001, decay = 0.00001, clipvalue = 0.5)
    #Configuta o modelo para treinamento. Calculo de ajuste dos pesos(Descida do Gradiente Adam), classificação binária, métrica para avaliação do modelo
    model.compile(optimizer = optimizer, loss = 'binary_crossentropy',
                          metrics = ['binary_accuracy'])
    return model

classificador = KerasClassifier(build_fn = criaModelo, epochs = 100, batch_size = 10)

resultados = cross_val_score(estimator = classificador, X = previsores, y = classes, cv = 10, scoring = 'accuracy')

media = resultados.mean()
desvio = resultados.std()