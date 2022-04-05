import pygame

class Kq():

    def __init__(self,game_settings,screen):
        self.screen=screen
        self.game_settings=game_settings
        self.image=pygame.image.load('images/kq.bmp') ##load the image
        self.rect=self.image.get_rect()      #the rectangular of the image
        self.screen_rect=screen.get_rect()   #the rectangular of the screen
        self.rect.centerx=self.screen_rect.centerx
        self.rect.bottom=self.screen_rect.bottom
        self.centerx=float(self.rect.centerx)
        self.top=float(self.rect.top)
        self.moving_right=False   ##to show the character is moving or not
        self.moving_left=False
        self.moving_up=False
        self.moving_down=False
    def update(self):
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.centerx+=self.game_settings.kq_speed_factor
        if self.moving_left and self.rect.left>0:
            self.centerx-=self.game_settings.kq_speed_factor
        if self.moving_up and self.rect.top>self.screen_rect.top:
            self.top-=self.game_settings.kq_speed_factor
        if self.moving_down and self.rect.bottom<self.screen_rect.bottom:
            self.top+=self.game_settings.kq_speed_factor  
        self.rect.centerx=self.centerx
        self.rect.top=self.top
    def blitme(self):
        self.screen.blit(self.image,self.rect)