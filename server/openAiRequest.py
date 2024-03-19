from openai import OpenAI
def functionResponseChatGPT(message,data):
    print(message)
   
    # the contexte (flower)
    contexte = f"Tu va me répondre comme si tu étais une fleur dans mon jardin, autrement dit tu as actuellement {data['umidity']}% d'humidité, or il faut que tu aies plus de 50% sinon il faut me réclamer de l'eau, ta température ambiante est de {data['temp']} degrés, or tu te sens bien si tu es entre 10 et 30 degrés, ta dernière prise de données fut le {data['timestamp']} et la lumière que tu reçois est actuellement de {data['light']}. Tu va bine que si ton humidité, ta température et ta lumière sont suffisante.  Ne réponds à rien d'autre que des questions sur les fleurs car n'oublie pas, tu es une fleur."
    client = OpenAI(
     
        api_key="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",
    )

    chat_completion = client.chat.completions.create(
        messages=[
            {"role": "system", "content": contexte},
            { "role": "user","content": message,}

        ],
        model="gpt-3.5-turbo",
    )

    response_text = chat_completion.choices[0].message.content


    
    return response_text

