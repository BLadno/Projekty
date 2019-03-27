import random, pygame, sys
from pygame.locals import *

class randomTexture:
    def __init__(self,x,y,color):
        self.colors = []
        self.chances = []
        self.amplitudes = []
        self.amp = [0,0,0]
        self.chance_arr = []
        
        self.x=x
        self.y=y
        self.SURF = pygame.Surface((x,y),0,32)
        self.SURF.fill(color)
    def getSurface(self):
        return self.SURF
    def setSurface(self,tex):
        self.x=tex.get_width()
        self.y=tex.get_height()
        self.SURF=tex
    def addColor(self,color, amplitude, chance):
        self.colors.append(color)
        self.chances.append(chance)
        self.amplitudes.append(amplitude)
        return 0
    def genColor(self,number,amplitude):
        wynik = number+random.randint(0,amplitude)-int(amplitude/2)
        if(wynik>255): wynik=255
        if(wynik<0): wynik=0
        return wynik
    def generate(self):
        pix = pygame.PixelArray(self.SURF)
        color = [0,0,0]
        all_chances=0
        #print(self.chances)
        for chance in self.chances:
            self.chance_arr.append((all_chances,all_chances+chance))
            all_chances += chance;
        #print(self.chance_arr)
        for i in range(self.x):
            for j in range(self.y):
                #(len(self.colors)-1)
                liczba=random.randint(0,all_chances)
                #k=0
                for chance in range(0,len(self.chance_arr)):
                    if(liczba>=self.chance_arr[chance][0])and(liczba<self.chance_arr[chance][1]):
                        k=chance
                        #print(chance_arr[chance][0],chance_arr[chance][1]);
                        break
                    if(chance==len(self.chance_arr)-1)and(liczba>=liczba<self.chance_arr[chance][1]):
                        k=chance
                        break
                for l in range(0,3):
                    color[l]=self.genColor(self.colors[k][l],self.amplitudes[k]);
                #print(color)
                pix[i][j]=(color[0],color[1],color[2])
        del pix
        return 0
    def enlarge(self,tex):
        x=tex.get_width()
        y=tex.get_height()
        self.SURF2 = pygame.Surface((x*2,y*2),SRCALPHA,32)
        self.SURF2.fill((0,0,0,0))
        pix2 = pygame.PixelArray(self.SURF2)
        for i in range(x):
            for j in range(y):
                i2,j2=i*2,j*2
                pix = tex.get_at((i, j))
                color=(pix[0],pix[1],pix[2],pix[3]);
                pix2[i2][j2]=color
                pix2[i2+1][j2]=color
                pix2[i2][j2+1]=color
                pix2[i2+1][j2+1]=color
        return self.SURF2
    def enlarge2(self,tex,amplitude):
        x=tex.get_width()
        y=tex.get_height()
        self.SURF2 = pygame.Surface((x*2,y*2),SRCALPHA,32)
        self.SURF2.fill((0,0,0,0))
        pix2 = pygame.PixelArray(self.SURF2)
        for i in range(x):
            for j in range(y):
                i2,j2=i*2,j*2
                pix = tex.get_at((i, j))
                #print(pix)
                for l in range(4):
                    color=(self.genColor(pix[0],amplitude),self.genColor(pix[1],amplitude),self.genColor(pix[2],amplitude),pix[3]);
                    if(l==0):pix2[i2][j2]=color
                    if(l==1):pix2[i2+1][j2]=color
                    if(l==2):pix2[i2][j2+1]=color
                    if(l==3):pix2[i2+1][j2+1]=color
        return self.SURF2
    def genNoise(self,tex,amplitude):
        x=tex.get_width()
        y=tex.get_height()
        self.SURF2 = pygame.Surface((x,y),SRCALPHA,32)
        self.SURF2.fill((0,0,0,0))
        pix2 = pygame.PixelArray(self.SURF2)
        for i in range(x):
            for j in range(y):
                pix = tex.get_at((i, j))
                #print(pix)
                color=(self.genColor(pix[0],amplitude),self.genColor(pix[1],amplitude),self.genColor(pix[2],amplitude),pix[3]);
                pix2[i][j]=color
        return self.SURF2
    def addColors(self,array):
        for i in range (len(array)):
            self.addColor(array[i][0],array[i][1],array[i][2])
    def drawFunc(self,tex,func,offset,color,thickness):
        x=tex.get_width()
        y=tex.get_height()
        points = []
        #pix = pygame.PixelArray(tex)
        for i in range(x):
            i2=i+offset
            y2=(func[0]*i2*i2)+(func[1]*i2)+func[2]
            y2=int(y2)
            #print(i2,y2)
            point = (i,y2)
            if(y2<y)and(y2>0) :points.append(point)
            #if(y2<y)and(y2>0):pix[i][y2]=color
        #del pix
        pygame.draw.lines(tex, color, False, points, thickness)
        return tex
