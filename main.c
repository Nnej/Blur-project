//
//  main.c
//  Flou
//
//  Created by Jennifer Guiard on 17/05/12.
//  Copyright (c) 2012 Jennifer Guiard. All rights reserved.
//

#include <unistd.h>     
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "flou.h"

Image *image;

#define ESCAPE 27

void Keyboard(unsigned char key, int x, int y) {
    switch(key){
        case ESCAPE :
            exit(0);                   
            break;
        default:
            fprintf(stderr, "Unused key\n");
    }
}

void Mouse(int button, int state, int x, int y){
    
    switch(button){
        case GLUT_LEFT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        case GLUT_RIGHT_BUTTON:
            break;    
    }
    glutPostRedisplay();
}

int Init(char *s){
    
    image = (Image *) malloc(sizeof(Image));
    if (image == NULL) {
        fprintf(stderr, "Out of memory\n");
        return(-1);
    }
    if(strstr(s,".bmp")!=NULL){
        if (ImageLoad(s, image)==-1) return(-1);
    }
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glutReshapeWindow(image->sizeX, image->sizeY);
    
    return (0);
}

void Display(void){
    GLint w, h;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, 
                 image->data);
    
    glFlush();
}

void Reshape(int w, int h){ 
    glViewport(0, 0, (GLsizei)w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Afficher(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glutReshapeWindow(image->sizeX, image->sizeY);
    glutPostRedisplay();
}

void menuFunc(int item){
    char s[256];
    switch(item){
        case 0: //Ouvrir
            printf("Entrer le nom \n");
            scanf("%s", &s[0]);
            Init(s);
            glutPostRedisplay();
            break;
        case 1: //Infos
            printf("Taille de l image : %u %u\n", image->sizeX, image->sizeY);
            break;
        case 2: 
            printf("Filtre Gaussien \n");
            image = flouter(image,0); 
            Afficher();
            break;
        case 3: 
            printf("Filtre Pondere\n");
            image = flouter(image,1); 
            Afficher();
            break;
        case 4: 
            printf("Filtre Carre\n");
            image = flouter(image,2); 
            Afficher();
            break;
        case 5: 
            printf("Filtre Octogonal\n");
            image = flouter(image,3); 
            Afficher();
            break;
        case 8: 
            printf("Filtre Estampage\n");
            image = flouter(image,4); 
            Afficher();
            break;
        case 9: 
            printf("Filtre Effet 1\n");
            image = effet1(image);
            Afficher();
            break;
        case 10: 
            printf("Filtre Repoussage\n");
            image = flouter(image,5); 
            Afficher();
            break;
        case 11: 
            printf("Filtre Effet 2\n");
            image = effet2(image);
            Afficher();
            break;
        case 6:
            printf("Entrer le nom pour l'image dans cette taille\n");
            scanf("%s", &s[0]);
            if(strstr(s,".bmp")!=NULL)
                ImageSave(s, image);
            break;
        case 7:
            free(image);
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv){  
    
    if (argc<2) {
        fprintf(stderr, "Usage : flou nom_de_fichier\n");
        exit(0);
    }
    
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640,480);  
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("Projet Flou - Mai 2012");  
    
    Init(argv[1]);
    
    glutCreateMenu(menuFunc);
    glutAddMenuEntry("Ouvrir", 0);
    glutAddMenuEntry("Taille", 1);
    glutAddMenuEntry("Filtre Gaussien", 2);
    glutAddMenuEntry("Filtre Pondere",3);
    glutAddMenuEntry("Filtre Carre",4);
    glutAddMenuEntry("Filtre Octogonal",5);
    glutAddMenuEntry("Filtre Estampage",8);
    glutAddMenuEntry("Filtre Repoussage",10);
    glutAddMenuEntry("Filtre Effet 1",9);
    glutAddMenuEntry("Filtre Effet 2",11);
    glutAddMenuEntry("Sauver", 6);
    glutAddMenuEntry("Quitter", 7);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    
    glutDisplayFunc(Display);  
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    
    glutMouseFunc(Mouse);
    
    glutMainLoop();  
    
    return 1;
}
