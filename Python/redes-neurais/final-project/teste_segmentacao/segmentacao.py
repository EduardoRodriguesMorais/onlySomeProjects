# -*- coding: utf-8 -*-
"""
Created on Sun Mar 17 23:18:13 2019

@author: Eduardo
"""

import numpy as np
import cv2
import os
import mahotas

def transfer_image_to_folder(folder, img):
	cv2.imwrite(folder, img, [int(cv2.IMWRITE_JPEG_QUALITY), 90])
	

def mostra_img(nomeJanela, img):
    cv2.imshow(nomeJanela, img)
    cv2.waitKey(0)

def gera_mascara(img):
    #Passo 1: Calculo liniar de acordo com o metodo Otsu 
    T = mahotas.thresholding.otsu(img)
    #Passo 2: Cópia da matriz binária
    bin = img.copy()
    #Passo 3: Utiliza linear para formar imagem 
    bin[bin > T] = 255
    bin[bin < 255] = 0
    #Passo 4: Inverte cada bit da matriz 
    bin = cv2.bitwise_not(bin)
    #Passo 5: Empilha a matriz em sequência horizontal 
    masc = np.hstack([bin])
    mostra_img('Masc', masc)
    return masc

def realiza_segmentacao(img):
    #Passo 1: Conversão para tons de cinza
    img_color = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  
    #Passo 2: Blur/Suavização da imagem
    img_suave = cv2.blur(img_color, (100, 100)) 
    #Passo 3: Binarização resultando em pixels brancos e pretos
    new_mask = gera_mascara(img_suave)
    #Passo 4: Realiza conjunção bit a bit da imageme da mascara 
    img_com_mascara = cv2.bitwise_and(img, img, mask = new_mask)
    
    return img_com_mascara
    
def aplica_efeitos(img):
    th = 200
    max_val = 255 
    ret, o1 = cv2.threshold(img, th, max_val, cv2.THRESH_BINARY )
    ret, o2 = cv2.threshold(img, th, max_val, cv2.THRESH_BINARY_INV )
    ret, o3 = cv2.threshold(img, th, max_val, cv2.THRESH_TOZERO )
    ret, o4 = cv2.threshold(img, th, max_val, cv2.THRESH_TOZERO_INV )
    ret, o5 = cv2.threshold(img, th, max_val, cv2.THRESH_TRUNC)
    
    return o5



img = cv2.imread('ISIC_0024408.jpg')
ret = aplica_efeitos(img)
segmentacao = realiza_segmentacao(ret)
mostra_img('Teste', segmentacao)



images_test = ['ISIC_0024308.jpg','ISIC_0024310.jpg','ISIC_0024315.jpg','ISIC_0024319.jpg','ISIC_0024349.jpg','ISIC_0024385.jpg','ISIC_0024408.jpg','ISIC_0024443.jpg','ISIC_0024447.jpg','ISIC_0024623.jpg']

for image in images_test:
    img = cv2.imread(image)
    segmentacao = realiza_segmentacao(img)
    source_path = os.path.join('segmentacao', image)
    transfer_image_to_folder(source_path,segmentacao)
   
   # aplica_efeitos(img)
   
   
   
   
























