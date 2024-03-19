
from repository import myLittleGardenRepository
import telebot
import openAiRequest
import os 
repo = myLittleGardenRepository()

# to ge the last inserted document
# repo.getLastInserted()
data = repo.getLastInserted()

# token for the telegram bot
BOT_TOKEN = "6595840467:AAGvq5x109q3yhsnyIQQbxDD27ToAlbLMng"

bot = telebot.TeleBot(BOT_TOKEN)


@bot.message_handler(commands=['start', 'hello'])
def send_welcome(message):
    sent_msg = bot.send_message(message.chat.id, "Salut ! Je suis le jumeau numérique de ton Jardin !")
    bot.register_next_step_handler(sent_msg, get_daily_horoscope)
    


@bot.message_handler(func=lambda msg: True)
def echo_all(message):
    get_daily_horoscope(message)



def get_daily_horoscope(message):
    
    bot.send_message(message.chat.id,openAiRequest.functionResponseChatGPT(message.text,data))





bot.infinity_polling()