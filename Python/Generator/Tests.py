import random, pygame, sys
from pygame.locals import *

from Generator import *
pygame.init()

FPS = 6
fpsClock = pygame.time.Clock()

DISPLAYSURF = pygame.display.set_mode((800, 600),0,32)
pygame.display.set_caption('Test')
BLACK = ( 0, 0, 0)
WHITE = (255, 255, 255)
EMPTY = (255, 255, 255, 0)
RED = (255, 0, 0)
DARKRED = (100, 0, 0)
GREEN = ( 0, 255, 0)
BLUE = ( 0, 0, 255)
DISPLAYSURF.fill(WHITE)

def testGEN(tex,kolory):
    tex.addColors(kolory)
    tex.generate()
    print("Wygenerowano");
    return tex
def testLoadIMG(tex,img):
    IMG = pygame.image.load(img);
    tex.setSurface(IMG)
    print("Wczytano obraz",img);
    return tex
def testSaveIMG(surf,img):
    pygame.image.save(surf,img);
    print("Zapisano obraz",img);
    return 0
def testDrawParabola(tex,surf):
    tex.drawFunc(surf,(0.01,0.01,1),-125,BLACK,2);
    print("Parabola narysowana");
    return surf
def testEnlarge(tex,surf,a):
    for i in range(a): surf = tex.enlarge(surf)
    print("Obraz powiekszony");
    return surf
def testEnlarge2(tex,surf,a):
    for i in range(a): surf = tex.enlarge2(surf,10)
    print("Obraz powiekszony2");
    return surf
def testGenNoise(tex,surf):
    tex.genNoise(surf,20)
    print("Szum wygenerowany");
    return surf

Kolory1=[((0,150,0),50,10),((0,100,0),50,10)]
Kolory2=[((255,0,0),50,20),((200,0,0),50,20)]
Kolory3=[((150,120,0),20,60),((180,150,0),20,20),((120,90,0),20,20)]

TEX2 = randomTexture(256,256,WHITE)
testGEN(TEX2,Kolory2)
#testLoadIMG(TEX2,"minecraft.jpg")

GRASS1 = TEX2.getSurface()
GRASS1 = testDrawParabola(TEX2,GRASS1)
GRASS1 = testEnlarge(TEX2,GRASS1,1)
#GRASS1 = testGenNoise(TEX2,GRASS1)

DISPLAYSURF.blit(GRASS1, (0, 0)) #RYSUJ
#testSaveIMG(GRASS1,"tester.png")

pygame.display.update()
print("Koniec programu")
while True: # main game loop
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()
    fpsClock.tick(FPS)
