from chatterbot import ChatBot
from chatterbot.trainers import ListTrainer

import os
jenkins = ChatBot('Teste')
jenkins.set_trainer(ListTrainer)

for _file in os.listdir('chat'):
    c = open('chat/'+_file,'r').readlines()

jenkins.train(c)
while True:
    quest = input('Você: ')
    response = jenkins.get_response(quest)
    if quest == 'Sair':
        print('Jenkins: Desconectando.')
        break
    print('Jenkins: ',response)
