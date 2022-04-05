
import pygame
from settings import Settings
from kq import Kq
import game_functions as gf
from pygame.sprite import Group
from pm import PM
def run_game():
    pygame.init()
    game_settings=Settings()

    screen=pygame.display.set_mode((game_settings.width,game_settings.height)) ##the screen is (800width 800height)
    pygame.display.set_caption("刻晴大战派蒙")
    keqing=Kq(game_settings,screen)  ##your character
    bullets=Group()                     ##your weapon
    pimeng=Group()                   ##your enemy
    gf.create_fleet(game_settings,screen,pimeng)


    while True:

        gf.check_events(game_settings,screen,keqing,bullets) ##check the input
        keqing.update()      ##update 
        gf.update_bullets(bullets)
        gf.update_pm(game_settings,pimeng)
        gf.update_screen(game_settings,screen,keqing,bullets,pimeng)
run_game()