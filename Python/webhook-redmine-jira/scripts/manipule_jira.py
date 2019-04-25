# -*- coding: utf-8 -*-

from jira import JIRA
from manipule_json import get_fields_values

jira = JIRA(server='https://sgotst.basis.com.br', basic_auth=('jelly.service', '7_tL4}y *5~Oc[J'))

def cerate_dic_fields(webhook_json):
    summary, description, priority, fields_value = get_fields_values(webhook_json)

    print('___________'+ summary, description, priority, str(fields_value) + '___________')
    print(summary)

    dic_field = {
        'project': {'key': 'TSTBASIS'},
        'summary': summary,
        'description': description,
        'issuetype': {'id': '3'},
        'customfield_25253': 'N/A',                 #Subtipo
        'customfield_25254': 'Revisar',             #Ação
        'customfield_25348': 'Arquitetura',         #Departamento
        'customfield_25252': 'Código'               #Objeto da Tarefa
    }

    return dic_field

def create_new_issue(dic_field):
    return jira.create_issue(dic_field, prefetch = True)




#jira.add_comment('TSTCLIENTE-90', 'Hello World!')