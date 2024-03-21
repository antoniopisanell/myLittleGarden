
from repository import myLittleGardenRepository
import telebot
import openAiRequest
import os 
import json

CURR_DIR = os.path.dirname(os.path.realpath(__file__))

repo = myLittleGardenRepository()

# to ge the last inserted document
# repo.getLastInserted()
data = repo.getLastInserted()

# token for the telegram bot
creds = json.load(open(f'{CURR_DIR}/creds.json'))
BOT_TOKEN = creds['telegramBot-token']

bot = telebot.TeleBot(BOT_TOKEN)


@bot.message_handler(commands=['start', 'hello'])
def send_welcome(message):
    sent_msg = bot.send_message(message.chat.id, "Salut ! Je suis le jumeau numérique de ton Jardin !")
    bot.register_next_step_handler(sent_msg, sendChatGPT)
    

# recup all message and send to chatGPT
@bot.message_handler(func=lambda msg: True)
def echo_all(message):
    sendChatGPT(message)



def sendChatGPT(message):
    bot.send_message(message.chat.id,openAiRequest.functionResponseChatGPT(message.text, repo.getLastInserted()))



bot.infinity_polling()