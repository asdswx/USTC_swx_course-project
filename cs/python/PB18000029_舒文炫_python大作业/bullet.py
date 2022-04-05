import pygame
from pygame.sprite import Sprite

class Bullet(Sprite):
    def __init__(self,game_settings,screen,keqing):
        super(Bullet,self).__init__()
        self.screen=screen

        self.rect=pygame.Rect(0,0,game_settings.bullet_width,game_settings.bullet_height) ##create bullet rect and initialize it
        self.rect.centerx=keqing.rect.centerx
        self.rect.top=keqing.rect.top
        self.y=float(self.rect.y)
        self.color=game_settings.bullet_color
        self.speed_factor=game_settings.bullet_speed_factor
    def update(self):
        self.y-=self.speed_factor
        self.rect.y=self.y

    def draw_bullet(self):
        pygame.draw.rect(self.screen,self.color,self.rect)
