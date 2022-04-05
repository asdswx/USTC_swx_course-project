
import pygame
from settings import Settings
from kq import Kq
import game_functions as gf
from pygame.sprite import Group
from pm import PM
from game_stats import GameStats
from button import Button
def run_game():
    pygame.init()
    pygame.mixer.init() ##bgm
    game_settings=Settings()
    pygame.mixer.music.load("music/bgm.ogg")
    pygame.mixer.music.set_volume(0.2)
    screen=pygame.display.set_mode((game_settings.width,game_settings.height)) ##the screen is (800width 800height)
    pygame.display.set_caption("刻晴大战派蒙")
    keqing=Kq(game_settings,screen)
    bullets=Group()
    pimeng=Group()
    gf.create_fleet(game_settings,screen,pimeng)
    stats=GameStats(game_settings)
    play_button=Button(game_settings,screen,"play")


    while True:

        gf.check_events(game_settings,screen,stats,play_button,keqing,pimeng,bullets)
        if pygame.mixer.music.get_busy() == False:
            pygame.mixer.music.play()
        if stats.game_active:
            keqing.update()
            gf.update_bullets(game_settings,screen,bullets,pimeng)
            gf.update_pm(game_settings,stats,screen,keqing,pimeng,bullets)
        gf.update_screen(game_settings,stats,screen,keqing,bullets,pimeng,play_button)
run_game()