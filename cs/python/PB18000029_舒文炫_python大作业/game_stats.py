class GameStats():
    def __init__(self,game_settings):
        self.game_settings=game_settings
        self.reset_stats()
        self.game_active=False  ##the game is over when it is False
    def reset_stats(self):
        self.keqing_left=self.game_settings.keqing_limit