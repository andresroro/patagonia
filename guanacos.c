#include "header.h"
#include "manada_guanacos_agent_header.h"
#include "commons.h"
#include <time.h>

//variables

int familia, xcord, ycord, count, calorias, adultos, season;

int manadaInfo(){

	familia=get_familia();
	xcord = get_xcord();
	ycord = get_ycord();
	count = get_count();
	calorias = get_calorias();
	adultos = get_adultos();
	season = get_season();

	return 0;
}

int seasonSwitch(){
	familia=get_familia();
	xcord = get_xcord();
	ycord = get_ycord();
	count = get_count();
	calorias = get_calorias();
	adultos = get_adultos();
	season = get_season();
	if(season == 0){
		set_season(1);
	}else set_season(0);
	season = get_season();

	return 0;
}

int manada_idle(){
	return 0;
}

int move(){
	int r, targetX, targetY, season, nextX, nextY;
	r = rand();	
	season = get_season();
	targetX = get_targetX();
	targetY = get_targetY();
	nextX = get_xcord();
	nextY = get_ycord();
	add_adultospatch_message(get_xcord(), get_ycord(), get_adultos(), 0);

	if(leviflight(get_xcord(), get_ycord(), &targetX, &targetY)){
		//no estamos en la posicion, calcular nueva posicion segun target
		if(targetX < get_xcord()){
			nextX = get_xcord()-1;
		}else if(targetX > get_xcord()){
			nextX = get_xcord()+1;
		}
		if(targetY < get_ycord()){
			nextY = get_ycord()-1;
		}else if(targetY > get_ycord()){
			nextY = get_ycord()+1;
		}
	}else{ //movimiento corto
		if(targetY < 0){
			targetY = 0;
		}
		else if(targetY > GRIDSIZE-1){
			targetY = GRIDSIZE-1;
		}
		if(targetX < 1){
			targetX = 1;
		}
		else if(targetX > GRIDSIZE-1){
			targetX = GRIDSIZE-1;
		}
		nextX = targetX;
		nextY = targetY;
		//movernos a la posicion target
	}
	if (season==1){
		if(get_ycord() <= ((GRIDSIZE-1)/2)){
			targetY = 0;
		}
		else targetY = GRIDSIZE-1;
	}
	set_targetX(targetX);
	set_targetY(targetY);
	set_ycord(nextY);
	set_xcord(nextX);
	/*if (season==DRY){
		if(ycord <= (GRIDSIZE/2)){
			switch(r%3){
				case 0:
					if(xcord > 1){
						set_xcord(xcord-1);
					}
					if(ycord > 0){
						set_ycord(ycord-1);
					}
					break;
				case 1:
					if(ycord>0){
						set_ycord(ycord-1);
					}
					break;
				case 2:
					if(xcord < (GRIDSIZE-2)){
						set_xcord(xcord+1);
					}
					if(ycord > 0){
						set_ycord(ycord-1);
					}
					break; 
			}
		}else{
			switch(r%3){
				case 0:
					if(xcord > 1){
						set_xcord(xcord-1);
					}
					if(ycord < (GRIDSIZE-1)){
						set_ycord(ycord+1);
					}
					break;
				case 1:
					if(ycord < (GRIDSIZE-1)){
						set_ycord(ycord+1);
					}
					break;
				case 2:
					if(xcord < (GRIDSIZE-2)){
						set_xcord(xcord+1);
					}
					if(ycord < (GRIDSIZE-1)){
						set_ycord(ycord+1);
					}
					break; 
			}
		}
	}else{
		switch(r%8){
			case 0:
				if(xcord > 1){
					set_xcord(xcord-1);
				}
				if(ycord > 0){
					set_ycord(ycord-1);
				}
				break;
			case 1:
				if(ycord>0){
					set_ycord(ycord-1);
				}
				break;
			case 2:
				if(xcord < (GRIDSIZE-2)){
					set_xcord(xcord+1);
				}
				if(ycord > 0){
					set_ycord(ycord-1);
				}
				break;
			case 3:
				if(xcord < (GRIDSIZE-2)){
					set_xcord(xcord+1);
				}
				break;
			case 4:
				if(xcord < (GRIDSIZE-2)){
					set_xcord(xcord+1);
				}
				if(ycord < (GRIDSIZE-1)){
					set_ycord(ycord+1);
				}
				break;
			case 5:
				if(ycord < (GRIDSIZE-1)){
					set_ycord(ycord+1);
				}
				break;
			case 6:
				if(xcord > 1){
					set_xcord(xcord-1);
				}
				if(ycord < (GRIDSIZE-1)){
					set_ycord(ycord+1);
				}
				break;
			case 7:
				if(xcord > 1){
					set_xcord(xcord-1);
				}
				break;
		}
	}*/
	add_adultospatch_message(get_xcord(), get_ycord(), get_adultos(), 1);
	return 0;
}


/*
int post_calorias(){
	add_calguanacos_message(xcord, ycord, calorias);
	return 0;
}*/

int reproduccion(){
	add_reproduccionguanacos_message(get_xcord(), get_ycord(), get_count(), get_familia());
	return 1;
}

int manada_idle2(){
	return 0;
}

int leviflight(int posX, int posY, int *targetX, int *targetY){
	int r;
	//si estamos en nuestro target recalcular nuevo target
	if(posX == *targetX && posY == *targetY){
		r = rand() % 100;
		//movimiento largo, aleatorio por todo el mapa
		if(r >= 90){
			r = rand()%GRIDSIZE;
			if(r < 1) r = 1; 
			*targetX = r;
			r = rand()%GRIDSIZE;
			*targetY = r;
			return 1;
		}
		else{//movimiento corto
			r = rand()%3;
			if(r == 0){
				if(posX > 1){
					*targetX = posX-1;
				}
			}
			else if(r == 1){
				*targetX = posX+1;
 			}else{ //si no cambiamos el targetX cambiamos si o si el targetY
 				r = rand()%2;
 				*targetX = posX;
 				if(r == 0){
 					*targetY = posY-1;
 					return 0;
 				}
 				else{
 					*targetY = posY+1;
 					return 0;
 				}
 			}
 			r = rand()%3;
 			if(r == 0){
 				*targetY = posY-1;
 				return 0;
 			}
 			else if(r == 1){
 				*targetY = posY+1;
 				return 0;
 			}
 			else{
 				*targetY = posY;
 				return 0;
 			}
		}
	}
	else return 1;
}