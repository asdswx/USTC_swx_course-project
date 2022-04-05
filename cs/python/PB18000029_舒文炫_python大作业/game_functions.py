import sys ##exit the game
import pygame
from bullet import Bullet
from pm import PM
from time import sleep
def check_keydown(event,game_settings,screen,keqing,bullets):
    if event.key==pygame.K_RIGHT:
        keqing.moving_right=True
    if event.key==pygame.K_LEFT:
        keqing.moving_left=True
    if event.key==pygame.K_UP:
        keqing.moving_up=True
    if event.key==pygame.K_DOWN:
        keqing.moving_down=True
    elif event.key==pygame.K_SPACE:
        fire(game_settings,screen,keqing,bullets)
    elif event.key==pygame.K_q:
                sys.exit()
def check_keyup(event,keqing):
    if event.key==pygame.K_RIGHT:
        keqing.moving_right=False
    if event.key==pygame.K_LEFT:
        keqing.moving_left=False
    if event.key==pygame.K_UP:
        keqing.moving_up=False
    if event.key==pygame.K_DOWN:
        keqing.moving_down=False

def fire(game_settings,screen,keqing,bullets): ##shoot the hun, you are allowed to shoot 5 at ine time
    if len(bullets)<game_settings.bullet_allowed:
            new_bullet=Bullet(game_settings,screen,keqing)
            bullets.add(new_bullet)

def check_play_button(game_settings,screen,stats,play_button,keqing,pimeng,bullets,mouse_x,mouse_y):
    if play_button.rect.collidepoint(mouse_x,mouse_y) and not stats.game_active: ##press play key
        stats.reset_stats()
        stats.game_active=True
        pimeng.empty()
        bullets.empty()
        create_fleet(game_settings,screen,pimeng)
        keqing.center_keqing()


def check_events(game_settings,screen,stats,play_button,keqing,pimeng,bullets):
    for event in pygame.event.get():##get the event such as mice and keybox input
            if event.type==pygame.QUIT:
                sys.exit()
            elif event.type==pygame.MOUSEBUTTONDOWN:
                mouse_x,mouse_y=pygame.mouse.get_pos()
                check_play_button(game_settings,screen,stats,play_button,keqing,pimeng,bullets,mouse_x,mouse_y)
            
            elif event.type==pygame.KEYDOWN:  ##to move continuously of you press the buttom
                check_keydown(event,game_settings,screen,keqing,bullets)

            elif event.type==pygame.KEYUP:
                check_keyup(event,keqing)
            
def get_num_pimeng_x(game_settings,pm_width): ##get the max mun one row can supply
    available_spacce_x=game_settings.width-2*pm_width
    num_pimeng_x=int(available_spacce_x/2/pm_width)
    return num_pimeng_x

def create_pm(game_settings,screen,pimeng,pm_num): ##create one pimeng
    pimengs=PM(game_settings,screen)
    pm_width=pimengs.rect.width
    pimengs.x=pm_width+2*pm_width*pm_num
    pimengs.rect.x=pimengs.x
    pimeng.add(pimengs)

def change_fleet_direction(game_settions,pimeng): ##change the direction if pm comes to the edge
    for pimengs in pimeng.sprites():
        pimengs.rect.y+=game_settions.fleet_drop_speed
    game_settions.fleet_direction*=-1


def check_fleet_edges(game_settings,pimeng): ##check whether pm comes to the edge
    for pimengs in pimeng.sprites():
        if pimengs.check_edge():
            change_fleet_direction(game_settings,pimeng)
            break






def create_fleet(game_settings,screen,pimeng): ##creat a group of pimeng
    pimengs=PM(game_settings,screen)
    number_pimeng_x=get_num_pimeng_x(game_settings,pimengs.rect.width)
    for pm_num in range(number_pimeng_x):
        create_pm(game_settings,screen,pimeng,pm_num)

def keqing_hit(game_settings,stats,screen,keqing,pimeng,bullets): ##keqing is hit, then clear the screen and remake.
    if stats.keqing_left>0:
        stats.keqing_left-=1
        pimeng.empty()
        bullets.empty()
        create_fleet(game_settings,screen,pimeng)
        keqing.center_keqing()
        sleep(0.5)
    else:
        stats.game_active=False

def check_pimeng_bottom(game_settings,stats,screen,keqing,pimeng,bullets):
    screen_rect=screen.get_rect()
    for pimengs in pimeng.sprites():
        if pimengs.rect.bottom>=screen_rect.bottom:
            keqing_hit(game_settings,stats,screen,keqing,pimeng,bullets)
            break


def update_pm(game_settings,stats,screen,keqing,pimeng,bullets):  ##update pimeng
    check_fleet_edges(game_settings,pimeng)
    pimeng.update()
    if pygame.sprite.spritecollideany(keqing,pimeng):
        keqing_hit(game_settings,stats,screen,keqing,pimeng,bullets)
    check_pimeng_bottom(game_settings,stats,screen,keqing,pimeng,bullets)


def update_screen(game_settings,stats,screen,keqing,bullets,pimeng,play_button): ##update the screen after do some operation
    screen.fill(game_settings.bg_color)
    for bullet in bullets.sprites():
        bullet.draw_bullet()

    keqing.blitme()
    pimeng.draw(screen)
    if not stats.game_active:
        play_button.draw_button()
    pygame.display.flip()

def update_bullets(game_settings,screen,bullets,pimeng): ##remove the redundent bullets and let you shoot pimeng
    bullets.update()
    for bullet in bullets.copy():
        if bullet.rect.bottom<=0:
            bullets.remove(bullet)
    collisions=pygame.sprite.groupcollide(bullets,pimeng,True,True)
    if len(pimeng)==0: ##regenerate pimeng when there is no pimeng
        bullets.empty()
        create_fleet(game_settings,screen,pimeng)


