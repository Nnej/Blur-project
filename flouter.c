//
//  flouter.c
//  Flou
//
//  Created by Jennifer Guiard on 17/05/12.
//  Copyright (c) 2012 Jennifer Guiard. All rights reserved.
//

#include "flou.h"

typedef enum {ROUGE,VERT,BLEU} Composante;

int filtre_gaussien [3][3] = { 1,2,1,2,4,2,1,2,1 };
int filtre_pondere [3][3] = { 0,1,0,1,4,1,0,1,0 }; 
int filtre_carre [3][3] = { 0,1,0,1,1,1,0,1,0 }; 
int filtre_octogonal [3][3] = { 1,1,1,1,1,1,1,1,1 }; 
int filtre_estampage[3][3] = { -2,0,0,0,1,0,0,0,2 };
int filtre_repoussage[3][3] = { -2,-1,0,-1,1,1,0,1,2};

//Fonction qui calcule la moyenne pour chaque composante ou couleur du masque 3x3
float moyenne(Image * im, int x, int y, int composante ,int n_filtre){
	int i,j,pos;
    float moy = 0;
    int size = im->sizeX*im->sizeY*3;
    
	for(j = -1; j < 2; j++){
		for(i= -1; i < 2; i++){
            pos = (x+i) * 3 + (y+j) * (im->sizeX * 3);
            if (pos>=0 && pos <= size) {
                moy += im->data[pos+composante] * choixFiltre(n_filtre,i,j);
            }
        }
	}
    return moy/= choixDiviseur(n_filtre);
}

//Fonction de selection du filtre a utiliser
int choixFiltre (int f,int i,int j){
    int fi;
        switch (f) {
            case 0:
                fi = filtre_gaussien[i+1][j+1];
                break;
            case 1:
                fi = filtre_pondere[i+1][j+1];
                break;
            case 2:
                fi = filtre_carre[i+1][j+1];
                break;
            case 3:
                fi = filtre_octogonal[i+1][j+1];
                break;
            case 4:
                fi = filtre_estampage[i+1][j+1]; 
                break;
            case 5:
                fi = filtre_repoussage[i+1][j+1]; 
                break;
            default:
                break;
        }
    return fi;
}

//Fonction de selection du diviseur a utiliser
int choixDiviseur(int n){
    int div;
    switch (n) {
        case 0:
            div = 16;
            break;
        case 1:
            div = 8;
            break;
        case 2:
            div = 5;
            break;
        case 3:
            div = 9;
            break;
        case 4:
        case 5:
            div = 1;
            break;
        default:
            break;
    }
    return div;
}

// Test de verification pour que les valeurs des pixels appartiennent à [0;255]
int test_intervalle (float x){
    if(x < 0){
        x = 0;
    }
    else if( x > 255){
        x = 255;
    }
    return x;
}

// Fonction qui effectue l'operation de floutage 
Image * flouter(Image *im, int filtre){
    Image * new;
    int x,y,size,pos_pix;
    float moyR,moyG,moyB;
    
    size = im->sizeX * im->sizeY * 3;
    
    //Allocations pour la nouvelle image
    new = (Image *) malloc(sizeof(Image));
    new->data = (GLubyte *) malloc(size);
    new->sizeX = im->sizeX;
    new->sizeY = im->sizeY;
    
    for (y = 0 ; y < new->sizeY ; y++ ) {
        for (x = 0 ; x < new->sizeX ; x++ ) {
            moyR = moyenne(im, x, y, ROUGE, filtre);
            moyG = moyenne(im, x, y, VERT, filtre);
            moyB = moyenne(im, x, y, BLEU, filtre);
            
            pos_pix = x * 3 + y * (im->sizeX * 3);
            
            new->data[pos_pix] = (GLubyte) test_intervalle(moyR);
            new->data[pos_pix+1] = (GLubyte) test_intervalle(moyG);
            new->data[pos_pix+2] = (GLubyte) test_intervalle(moyB);
        }
    } 
    
    free(im);
    return new;
}

// Fonction effet1 filtre octogonal + estampage
Image * effet1 (Image *im){
     Image * tmp;
    int size;
    size = im->sizeX * im->sizeY * 3;
    
    //allocations pour l'image tampon 1
    tmp = (Image *) malloc(sizeof(Image));
    tmp->data = (GLubyte *) malloc(size);
    tmp->sizeX = im->sizeX;
    tmp->sizeY = im->sizeY;
    //On apllique 3 fois le filtre octogonal
    tmp = flouter(flouter(flouter(im,3),3),3);
    // et une fois le filtre estampage
    return flouter(tmp,4);
}

// Fonction effet2 filtre gaussien + repoussage
Image * effet2 (Image *im){
    Image * tmp;
    int size;
    size = im->sizeX * im->sizeY * 3;
    
    //allocations pour l'image tampon 1
    tmp = (Image *) malloc(sizeof(Image));
    tmp->data = (GLubyte *) malloc(size);
    tmp->sizeX = im->sizeX;
    tmp->sizeY = im->sizeY;
    //On apllique 3 fois le filtre gaussien
    tmp = flouter(flouter(flouter(im,0),0),0);
    // et une fois le filtre repoussage
    return flouter(tmp,5);
}