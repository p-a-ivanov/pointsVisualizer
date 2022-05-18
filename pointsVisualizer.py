import pygame
from pygame.locals import *
import sys

from OpenGL.GL import *
from OpenGL.GLU import *

def axis():

    glClear( GL_COLOR_BUFFER_BIT)

    glLineWidth(0.1)
    glBegin(GL_LINES)

    glColor3f(1, 0, 0)
    glVertex3f(-1, 0, 0)
    glVertex3f(1, 0, 0)

    glColor3f(0, 1, 0)
    glVertex3f(0, -1, 0)
    glVertex3f(0, 1, 0)

    glColor3f(0, 0, 1)
    glVertex3f(0, 0, -1)
    glVertex3f(0, 0, 1)

    glEnd()

def goodPoints(goodPoints):

    glBegin(GL_POINTS)

    glColor3f(0, 0.75, 0.25)

    with open('./../outputs/' + str(goodPoints)) as gP:
        
        gLines = gP.readlines()
        for line in gLines:
            point = line.split()
            glVertex3f(float(point[0]), float(point[1]), float(point[2]))
    glEnd()

def wrongPoints(wrongPoints):

    glBegin(GL_POINTS)

    glColor3f(0.75, 0, 0.25)

    with open('./../outputs/' + str(wrongPoints)) as wP:
        
        gLines = wP.readlines()
        for line in gLines:
            point = line.split()
            glVertex3f(float(point[0]), float(point[1]), float(point[2]))
    glEnd()

def main():

    gPointsName = str(sys.argv[1])
    wPointsName = str(sys.argv[2])
    
    pygame.init()
    display = (800,600)
    pygame.display.set_mode(display, DOUBLEBUF|OPENGL)

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    glTranslatef(0.0,0.0, -5)
    glRotatef(15, 30, 0, 0)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        glRotatef(1, 0, 1, 0)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        axis()

        goodPoints(gPointsName)
        wrongPoints(wPointsName)
        pygame.display.flip()


main() 





