import random, pygame, sys
from pygame.locals import *

FPS = 15
WINDOWWIDTH = 640
WINDOWHEIGHT = 480
CELLSIZE = 20
assert WINDOWWIDTH % CELLSIZE == 0, "Window width must be a multiple of cell size."
assert WINDOWHEIGHT % CELLSIZE == 0, "Window height must be a multiple of cell size."
CELLWIDTH = int(WINDOWWIDTH / CELLSIZE)
CELLHEIGHT = int(WINDOWHEIGHT / CELLSIZE)

#             R    G    B
WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
YELLOW    = (255, 255,   0)
GREEN     = (  0, 255,   0)
DARKGREEN = (  0, 225,   0)
GRAY      = (245, 245, 245)

BGCOLOR = GRAY
TXCOLOR = BLACK
APPLECOLOR = RED
APPLECOLOR2 = YELLOW
INNERCOLOR = GREEN
OUTERCOLOR = DARKGREEN
TRAPCOLOR = BLACK

UP = 'up'
DOWN = 'down'
LEFT = 'left'
RIGHT = 'right'

HEAD = 0 # index głowy snake'a

def main():
    global FPSCLOCK, DISPLAYSURF, BASICFONT

    pygame.init()
    FPSCLOCK = pygame.time.Clock()
    DISPLAYSURF = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
    BASICFONT = pygame.font.Font('freesansbold.ttf', 18)
    pygame.display.set_caption('Snake')

    showStartScreen()
    while True:
        runGame()
        showGameOverScreen()


def runGame():
    # Losowy punkt początkowy
    startx = random.randint(5, CELLWIDTH - 6)
    starty = random.randint(5, CELLHEIGHT - 6)
    life = 3
    blocks = 0
    target = 5
    win = 30
    wormCoords = [{'x': startx,     'y': starty},
                  {'x': startx - 1, 'y': starty},
                  {'x': startx - 2, 'y': starty}]
    blockCoord = []
    direction = RIGHT

    #Wygeneruj jabłko na losowej pozycji
    apple = getRandomLocation()
    while True: # Główna pętla
        for event in pygame.event.get(): 
            if event.type == QUIT:
                terminate()
            elif event.type == KEYDOWN: #Sprawdzanie co gracz wcisnął
                if (event.key == K_LEFT or event.key == K_a) and direction != RIGHT:
                    direction = LEFT
                elif (event.key == K_RIGHT or event.key == K_d) and direction != LEFT:
                    direction = RIGHT
                elif (event.key == K_UP or event.key == K_w) and direction != DOWN:
                    direction = UP
                elif (event.key == K_DOWN or event.key == K_s) and direction != UP:
                    direction = DOWN
                elif event.key == K_ESCAPE:
                    terminate()

        
        #Dodawanie nowego elementu
        if direction == UP:
            newHead = {'x': wormCoords[HEAD]['x'], 'y': wormCoords[HEAD]['y'] - 1}
        elif direction == DOWN:
            newHead = {'x': wormCoords[HEAD]['x'], 'y': wormCoords[HEAD]['y'] + 1}
        elif direction == LEFT:
            newHead = {'x': wormCoords[HEAD]['x'] - 1, 'y': wormCoords[HEAD]['y']}
        elif direction == RIGHT:
            newHead = {'x': wormCoords[HEAD]['x'] + 1, 'y': wormCoords[HEAD]['y']}
        wormCoords.insert(0, newHead)

        #sprawdzanie kolizji
        
        #Sprawdź czy snake dotknął samego siebie lub krawędzi
        if wormCoords[HEAD]['x'] == -1 or wormCoords[HEAD]['x'] == CELLWIDTH or wormCoords[HEAD]['y'] == -1 or wormCoords[HEAD]['y'] == CELLHEIGHT:
            return # game over
        for wormBody in wormCoords[1:]:
            if wormBody['x'] == wormCoords[HEAD]['x'] and wormBody['y'] == wormCoords[HEAD]['y']:
                return # game over

        # sprawdź czy snake zjadł jabłko
        if wormCoords[HEAD]['x'] == apple['x'] and wormCoords[HEAD]['y'] == apple['y']:
            # don't remove worm's tail segment
            apple = getRandomLocation() # Stworz nowe jablko
        else:
            del wormCoords[-1] # Usun ogon
        
        size = len(wormCoords)
        size2 = size-3;
        if(size == target): #sprawdz czy gracz osiagnal odpowiednia dlugosc by dodac przeszkode
            blocks+=1
            target+=5
            trap = getRandomLocation()
            blockCoord.append(trap)
        if(blocks>0):
            for i in range(len(blockCoord)): #sprawdz kolizje z przeszkoda
                if blockCoord[i]['x'] == wormCoords[HEAD]['x'] and blockCoord[i]['y'] == wormCoords[HEAD]['y']:
                    blockCoord[i] = getRandomLocation()
                    if(size > 2) : del wormCoords[-1] #skroc o 1, gdy jest wiekszy niz 3

        DISPLAYSURF.fill(BGCOLOR)
        drawApple(apple)
        if(blocks>0):drawTraps(blockCoord)
        drawWorm(wormCoords)
        drawScore(len(wormCoords) - 3)
        if(size2 >= win): drawWin()
        pygame.display.update()
        FPSCLOCK.tick(FPS)

def drawPressKeyMsg():
    pressKeySurf = BASICFONT.render('Wcisnij dowolny klawisz.', True, TXCOLOR)
    pressKeyRect = pressKeySurf.get_rect()
    pressKeyRect.topleft = (WINDOWWIDTH - 250, WINDOWHEIGHT - 30)
    DISPLAYSURF.blit(pressKeySurf, pressKeyRect)


def checkForKeyPress():
    if len(pygame.event.get(QUIT)) > 0:
        terminate()

    keyUpEvents = pygame.event.get(KEYUP)
    if len(keyUpEvents) == 0:
        return None
    if keyUpEvents[0].key == K_ESCAPE:
        terminate()
    return keyUpEvents[0].key


def showStartScreen():
    titleFont = pygame.font.Font('freesansbold.ttf', 100)
    titleSurf = titleFont.render('Snake', True, DARKGREEN)

    while True:
        DISPLAYSURF.fill(BGCOLOR)
        titleRect = titleSurf.get_rect()
        titleRect.topleft = (WINDOWWIDTH/4,WINDOWHEIGHT/3)
        
        DISPLAYSURF.blit(titleSurf, titleRect)

        drawPressKeyMsg()

        if checkForKeyPress():
            pygame.event.get() # clear event queue
            return
        pygame.display.update()
        FPSCLOCK.tick(FPS)


def terminate():
    pygame.quit()
    sys.exit()


def getRandomLocation():
    return {'x': random.randint(0, CELLWIDTH - 1), 'y': random.randint(0, CELLHEIGHT - 1)}


def showGameOverScreen():
    gameOverFont = pygame.font.Font('freesansbold.ttf', 100)
    gameSurf = gameOverFont.render('Koniec', True, TXCOLOR)
    overSurf = gameOverFont.render('Gry', True, TXCOLOR)
    gameRect = gameSurf.get_rect()
    overRect = overSurf.get_rect()
    gameRect.midtop = (WINDOWWIDTH / 2, WINDOWHEIGHT / 4)
    overRect.midtop = (WINDOWWIDTH / 2, gameRect.height + WINDOWHEIGHT / 4 + 25)

    DISPLAYSURF.blit(gameSurf, gameRect)
    DISPLAYSURF.blit(overSurf, overRect)
    drawPressKeyMsg()
    pygame.display.update()
    pygame.time.wait(500)
    checkForKeyPress() # clear out any key presses in the event queue

    while True:
        if checkForKeyPress():
            pygame.event.get() # clear event queue
            return

def drawScore(score):
    scoreSurf = BASICFONT.render('Punkty: %s' % (score), True, TXCOLOR)
    scoreRect = scoreSurf.get_rect()
    scoreRect.topleft = (WINDOWWIDTH - 120, 10)
    DISPLAYSURF.blit(scoreSurf, scoreRect)

def drawWin():
    winSurf = BASICFONT.render('Wygrales', True, TXCOLOR)
    winRect = winSurf.get_rect()
    winRect.topleft = (int(WINDOWWIDTH/2)-80, 10)
    DISPLAYSURF.blit(winSurf, winRect)

def drawWorm(wormCoords):
    for coord in wormCoords:
        x = coord['x'] * CELLSIZE
        y = coord['y'] * CELLSIZE
        cell = int(CELLSIZE/2)
        pygame.draw.circle(DISPLAYSURF, OUTERCOLOR, (x+cell,y+cell), cell)
        pygame.draw.circle(DISPLAYSURF, INNERCOLOR, (x+cell,y+cell), int(cell/1.3))

def drawTraps(blockCoords):
    for block in blockCoords:
        x = block['x'] * CELLSIZE
        y = block['y'] * CELLSIZE
        blockRect = pygame.Rect(x, y, CELLSIZE, CELLSIZE)
        pygame.draw.rect(DISPLAYSURF, TRAPCOLOR, blockRect)

def drawApple(coord):
    x = coord['x'] * CELLSIZE
    y = coord['y'] * CELLSIZE
    cell = int(CELLSIZE/2)
    pygame.draw.circle(DISPLAYSURF, APPLECOLOR, (x+cell,y+cell), cell)
    pygame.draw.circle(DISPLAYSURF, APPLECOLOR2, (x+cell,y+cell), int(cell/1.3))

if __name__ == '__main__':
    main()
