#include "commons.h"
#include "header.h"

int leviflight(int posX, int posY, int *targetX, int *targetY){
	int r;
	//si estamos en nuestro target recalcular nuevo target
	if(posX == targetX && posY == targetY){
		r = rand() % 100;
		//movimiento largo, aleatorio por todo el mapa
		if(r >= 90){
			r = rand()%GRIDSIZE;
			if(r < 1) r = 1; 
			targetX = r;
			r = rand()%GRIDSIZE;
			targetY = r;
			return 1;
		}
		else{//movimiento corto
			r = rand()%3;
			if(r == 0){
				if(posX > 1){
					targetX = posX-1;
				}
			}
			else if(r == 1){
				targetX = posX+1;
 			}else{ //si no cambiamos el targetX cambiamos si o si el targetY
 				r = rand()%2;
 				targetX = posX;
 				if(r == 0){
 					targetY = posY-1;
 					return 0;
 				}
 				else{
 					targetY = posY+1;
 					return 0;
 				}
 			}
 			r = rand()%3;
 			if(r == 0){
 				targetY = posY-1;
 				return 0;
 			}
 			else if(r == 1){
 				targetY = posY+1;
 				return 0;
 			}
 			else{
 				targetY = posY;
 				return 0;
 			}
		}

	}
}