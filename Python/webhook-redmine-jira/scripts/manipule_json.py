import json

#teste = '{"payload":{"action":"opened","issue":{"id":6,"subject":"Testando ","description":"","created_on":"2019-04-23T16:51:16.988Z","updated_on":"2019-04-23T16:51:16.988Z","closed_on":"2019-04-23T16:51:16.988Z","root_id":6,"parent_id":null,"done_ratio":0,"start_date":"2019-04-23","due_date":null,"estimated_hours":null,"is_private":false,"lock_version":0,"custom_field_values":[{"custom_field_id":1,"custom_field_name":"Campo de teste 1","value":"Valor campo 1"},{"custom_field_id":2,"custom_field_name":"Campo de teste 2","value":"2019-04-23"},{"custom_field_id":3,"custom_field_name":"Campo de teste 3","value":"123.2"},{"custom_field_id":4,"custom_field_name":"Campo de teste 4","value":""}],"project":{"id":1,"identifier":"projeto-teste","name":"Projeto-Teste","description":"","created_on":"2019-04-22T22:42:37.460Z","homepage":""},"status":{"id":1,"name":"Aberta"},"tracker":{"id":1,"name":"Tarefa-Teste"},"priority":{"id":1,"name":"Alta"},"author":{"id":1,"login":"admin","mail":"admin@example.net","firstname":"Redmine","lastname":"Admin","identity_url":null,"icon_url":"//www.gravatar.com/avatar/cb4f282fed12016bd18a879c1f27ff97?rating=PG\u0026size=50"},"assignee":null,"watchers":[]},"url":"http://localhost:3000/issues/6"}}'

def get_fields_values(webhook_json):
    val = webhook_json
    issue = val['payload']['issue']
    custom_fields = issue['custom_field_values']
    summary = issue['subject']
    description = issue['description']
    priority = issue['priority']['name']

    fields_value = []

    for custom_field in custom_fields:
        if(custom_field['custom_field_id'] == 1 or custom_field['custom_field_id'] == 2 or custom_field['custom_field_id'] == 3 or custom_field['custom_field_id'] == 4):
            fields_value.append(custom_field['value'])    
            

    return summary,description,priority,fields_value




    #print(summary,description,priority,fields_value)