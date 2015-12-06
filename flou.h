//
//  flou.h
//  Flou
//
//  Created by Jennifer Guiard on 17/05/12.
//  Copyright (c) 2012 Jennifer Guiard. All rights reserved.
//
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
	

struct Image {
    unsigned int sizeX;
    unsigned int sizeY;
    GLubyte *data;
};
typedef struct Image Image;

//bmp.c
int ImageLoad(char *filename, Image *image);
int ImageSave(char *filename, Image *image);

//flouter.c
float moyenne(Image * im, int x, int y, int composante ,int n_filtre);
int choixFiltre (int f, int i, int j);
int choixDiviseur(int n);
Image * flouter(Image *im, int filtre);
int test_intervalle (float x);
Image * effet1 (Image *im);
Image * effet2 (Image *im);

//main.c
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
int Init(char *s);
void Afficher(void);
void Display(void);
void Reshape(int w, int h);
void menuFunc(int item);
