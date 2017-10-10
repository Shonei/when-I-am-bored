import pygame 
from functools import partial
from random import randint
from math import ceil, nan

class Viz:
    def __init__(self, algo, comp, **kwargs):
        pygame.init()
        pygame.display.set_caption('Main')
        self.algo = algo
        self.framerate = 5
        self.comp = comp
        self.list = []
        self.optional = []
        self.w = 800
        self.h = 400
        self.line_width = 0
        self.screen = pygame.display.set_mode([self.w,self.h])
        self.draw_line = partial(pygame.draw.line, self.screen)
        self.clock = pygame.time.Clock()

        if 'name' in kwargs:
            pygame.display.set_caption(kwargs['name'])

        if 'framerate' in kwargs:
            self.framerate = int(kwargs['framerate'])
    
    def load_data(self, arr, *args):

        min, max = arr[0], arr[0]
        for i in arr:
            if i > max:
                max = i
            if i < min:
                min = i

        f_norm = lambda x: abs(ceil((x-min)/(max-min)*(self.h-0)+0)) 
        if len(args) >= 1:
            self.optional = list(args)
            self.optional[0] = f_norm(self.optional[0])
        
        a = map(f_norm , arr)
        self.list = list(a)
        self.line_width = ceil(self.w / len(self.list))
    
    def compare(self, arr, h, j):
        self.clock.tick(self.framerate)

        for event in pygame.event.get(): 
            if event.type == pygame.QUIT: 
                pygame.quit() 
                quit()

        self.screen.fill((0,0,0))
        line_pos = 0

        for i in range(0, len(self.list)):
            color = (255,255,255)
            if i == h:
                color = (180,0,0)
            elif i == j and len(self.optional) < 1:
                color = (0,180,0)
            self.draw_line(color, (line_pos,self.h),(line_pos,self.h-self.list[i]), self.line_width)
            
            line_pos += self.line_width
        pygame.display.flip()
        
        return self.comp(arr, h, j)

    def run(self):
        if len(self.optional) >= 1:
            arr = self.algo(self.list, self.compare, self.optional[0])
        else:
            arr = self.algo(self.list, self.compare)

        done = False
        highlight_index = nan

        if type(arr) == tuple:
            highlight_index = arr[1]
            arr = arr[0]

        while not done:
            for event in pygame.event.get(): 
                if event.type == pygame.QUIT: 
                    done=True 
            
            self.screen.fill((0,0,0))
            line_pos = 0
            for i in range(0, len(arr)):
                color = (255,255,255)
                if i == highlight_index:
                    color = (0,180,0)
                self.draw_line(color, (line_pos,self.h),(line_pos,self.h-arr[i]), self.line_width)
            
                line_pos += self.line_width

            pygame.display.flip()

        pygame.quit()