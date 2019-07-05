# -*- coding: utf-8 -*-
"""
Created on Sat Jun 29 12:43:52 2019

@author: dudu_
"""

from scipy.spatial import distance as dist
from imutils import perspective
from imutils import contours
import numpy as np
from preprocess import generate_mask,apply_effects
import imutils
import cv2

def midpoint(ptA, ptB):
	return ((ptA[0] + ptB[0]) * 0.5, (ptA[1] + ptB[1]) * 0.5)

def contours_individually(image, cnts):
    pixelsPerMetric = None
    orig = image.copy()
    #Loop individual por canto
    for c in cnts:
        #Se os cantos nao forem suficiente mente largos. Ignora        
        if cv2.contourArea(c) < 100:
            continue
        
        #Calcula a caixa delimitadora gerada do contorno
        #Define uma estrutura Box2D
        box = cv2.minAreaRect(c)
        #Define os cantos do retângulo
        box = cv2.cv.boxPoints(box) if imutils.is_cv2() else cv2.boxPoints(box)
        box = np.array(box, dtype="int")
        box = perspective.order_points(box)
        
        #Desenha estrutura da caixa
        cv2.drawContours(orig, [box.astype("int")], -1, (0, 255, 0), 2)
        
        #Desenha os pontos
        orig = original_points(box, orig)
        
        (tl, tr, br, bl) = box
        (tltrX, tltrY) = midpoint(tl, tr)
        (blbrX, blbrY) = midpoint(bl, br)
        
        (tlblX, tlblY) = midpoint(tl, bl)
        (trbrX, trbrY) = midpoint(tr, br)
        
        #desenhe os pontos médios na imagem
        cv2.circle(orig, (int(tltrX), int(tltrY)), 5, (255, 0, 0), -1)
        cv2.circle(orig, (int(blbrX), int(blbrY)), 5, (255, 0, 0), -1)
        cv2.circle(orig, (int(tlblX), int(tlblY)), 5, (255, 0, 0), -1)
        cv2.circle(orig, (int(trbrX), int(trbrY)), 5, (255, 0, 0), -1)
        # Desenha linhas entre os pontos médios
        cv2.line(orig, (int(tltrX), int(tltrY)), (int(blbrX), int(blbrY)),(255, 0, 255), 2)
        cv2.line(orig, (int(tlblX), int(tlblY)), (int(trbrX), int(trbrY)),(255, 0, 255), 2)
        
        #Calcular a distância Euclidiana entre os pontos médios
        dA = dist.euclidean((tltrX, tltrY), (blbrX, blbrY))
        dB = dist.euclidean((tlblX, tlblY), (trbrX, trbrY))
        
        
        # Se os pixels por métrica não foram inicializados, então
        # calcula como a proporção de pixels para a métrica fornecida
        # (neste caso, polegadas)
        if pixelsPerMetric is None:
            pixelsPerMetric = dB / 0.8
            
        # Calcula o tamanho do objeto
        dimA = dA / pixelsPerMetric
        dimB = dB / pixelsPerMetric
        print(dimA)
        print(dimB)
        
        # Desenha os tamanhos dos objetos na imagem
        cv2.putText(orig, "{:.1f}cm".format(dimA),(int(tltrX - 15), int(tltrY - 10)), cv2.FONT_HERSHEY_SIMPLEX, 0.65, (255, 255, 255), 2)
        cv2.putText(orig, "{:.1f}cm".format(dimB),(int(trbrX + 10), int(trbrY)), cv2.FONT_HERSHEY_SIMPLEX, 0.65, (255, 255, 255), 2)
    
    
    return orig.copy()

def original_points(box, tst):
	for (x, y) in box:
		cv2.circle(tst, (int(x), int(y)), 5, (0, 0, 255), -1)
	return tst

def defocus_image(img):
    #Deixa a imagem cinza 
    img_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    #Desfoca a imagm usando filtro gaussiano
    img_gray = cv2.GaussianBlur(img_gray, (7, 7), 0)
    return img_gray

# Realiza detecção de bordas, então realiza uma dilatação para fechar lacunas entre as bordas do objeto
def find_valors_contours(gray_img):
    #Realiza detecção de bordas 
    edged_img = cv2.Canny(gray_img, 50, 100)
    #Realiza dilatação da imagem
    edged_img = cv2.dilate(edged_img, None, iterations=1)
    #Realiza a correção da imagem utilizando áreas de uma viziança de pixels 
    edged_img = cv2.erode(edged_img, None, iterations=1)    
    return edged_img

def find_image_countours(edged_img):
    #Encontrar contornos no mapa de borda
    cnts_img = cv2.findContours(edged_img.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    #Pega o valor apropriado da tupla 
    cnts_img = imutils.grab_contours(cnts_img)
     #Classifica os contornos da esquerda para a direita e inicialize a variável de calibração de "pixels por métrica"
    (contours_image, _) = imutils.contours.sort_contours(cnts_img)
    return contours_image

def get_contours(image):
    image_defocus = defocus_image(image)
    vlrs_contours = find_valors_contours(image_defocus)
    contours_image = find_image_countours(vlrs_contours)
    return contours_image

if __name__ == "__main__":
    # load the image, convert it to grayscale, and blur it slightly
    image = cv2.imread("dataset/melanoma/DermMel/test/melanoma/AUG_0_45.jpeg")
    
    image = generate_mask(image)
    
    cntr_ndarray  = get_contours(image)
    result = contours_individually(image, cntr_ndarray)
    
    cv2.startWindowThread()
    cv2.imshow("Image", result)    
    cv2.waitKey(2)   