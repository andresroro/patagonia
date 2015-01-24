#include "header.h"
#include "manada_guanacos_agent_header.h"
#include "commons.h"
#include <time.h>

struct clansAround {
	int x;
	int y;
	int clans;
};

//variables

int familia, x, y, count, calorias, adultos, season;

int manadaInfo(){

	familia=get_familia();
	x = get_x();
	y = get_y();
	count = get_count();
	calorias = get_calorias();
	adultos = get_adultos();
	season = get_season();

	return 0;
}

int seasonSwitch(){
	familia=get_familia();
	x = get_x();
	y = get_y();
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
	int r, targetX, targetY, season, nextX, nextY, i, j, fleed;
	struct clansAround clanes[9] = {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
	r = rand();	
	fleed = 1;
	season = get_season();
	targetX = get_targetX();
	targetY = get_targetY();
	nextX = get_x();
	nextY = get_y();
	add_adultospatch_message(get_x(), get_y(), get_adultos(), 0);

	START_CLANSPATCH_MESSAGE_LOOP
		if(clanspatch_message->x == get_x() -1){
			if(clanspatch_message->y == get_y() -1){
				clanes[0].x = clanspatch_message->x;
				clanes[0].y = clanspatch_message->y;
				clanes[0].clans = clanspatch_message->pclans;
			}if(clanspatch_message->y == get_y()){
				clanes[3].x = clanspatch_message->x;
				clanes[3].y = clanspatch_message->y;
				clanes[3].clans = clanspatch_message->pclans;
			}if(clanspatch_message->y == get_y() +1){
				clanes[6].x = clanspatch_message->x;
				clanes[6].y = clanspatch_message->y;
				clanes[6].clans = clanspatch_message->pclans;
			}
		}
		if(clanspatch_message->x == get_x()){
			if(clanspatch_message->y == get_y() -1){
				clanes[1].x = clanspatch_message->x;
				clanes[1].y = clanspatch_message->y;
				clanes[1].clans = clanspatch_message->pclans;
			}if(clanspatch_message->y == get_y()){
				clanes[4].x = clanspatch_message->x;
				clanes[4].y = clanspatch_message->y;
				clanes[4].clans = clanspatch_message->pclans;
			}if(clanspatch_message->y == get_y() +1){
				clanes[7].x = clanspatch_message->x;
				clanes[7].y = clanspatch_message->y;
				clanes[7].clans = clanspatch_message->pclans;
			}
		}
		if(clanspatch_message->x == get_x() +1){
			if(clanspatch_message->y == get_y() -1){
				clanes[2].x = clanspatch_message->x;
				clanes[2].y = clanspatch_message->y;
				clanes[2].clans = clanspatch_message->pclans;
			}if(clanspatch_message->y == get_y()){
				clanes[5].x = clanspatch_message->x;
				clanes[5].y = clanspatch_message->y;
				clanes[5].clans = clanspatch_message->pclans;
			}if(clanspatch_message->y == get_y() +1){
				clanes[8].x = clanspatch_message->x;
				clanes[8].y = clanspatch_message->y;
				clanes[8].clans = clanspatch_message->pclans;
			}
		}
	FINISH_CLANSPATCH_MESSAGE_LOOP

	if(leviflight(get_x(), get_y(), &targetX, &targetY)){
		//no estamos en la posicion, calcular nueva posicion segun target
		if(targetX < get_x()){
			nextX = get_x()-1;
		}else if(targetX > get_x()){
			nextX = get_x()+1;
		}
		if(targetY < get_y()){
			nextY = get_y()-1;
		}else if(targetY > get_y()){
			nextY = get_y()+1;
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
		
		i = (1+(targetX -get_x()))+(3+(3*(targetY-get_y())));
		if(clanes[i].clans > 0){ 
			printf("%d, %d, %d \n", clanes[i].x, clanes[i].y, clanes[i].clans);
			fleed = 0;
			j = (i+1)%9;
			while(fleed == 0 && j != i){
				printf("%d, %d, %d \n", clanes[j].x, clanes[j].y, clanes[j].clans);
				if(j == 4) j++;
				if(clanes[j].clans == 0){
					fleed = 1;
					targetX = clanes[j].x;
					targetY = clanes[j].y;
				}
				j = (j+1)%9;

			}
		}
		
		nextX = targetX;
		nextY = targetY;
		//movernos a la posicion target
	}
	if (season==1){
		if(get_y() <= ((GRIDSIZE-1)/2)){
			targetY = 0;
		}
		else targetY = GRIDSIZE-1;
	}
	set_targetX(targetX);
	set_targetY(targetY);
	set_y(nextY);
	set_x(nextX);

	add_adultospatch_message(get_x(), get_y(), get_adultos(), 1);
	return 0;
}


/*
int post_calorias(){
	add_calguanacos_message(x, y, calorias);
	return 0;
}*/

int reproduccion(){
	add_reproduccionguanacos_message(get_x(), get_y(), get_count(), get_familia());
	return 1;
}

int manada_idle2(){
	return 0;
}

int surviveGuanacos(){
	int r;
	r = rand() % 100;
	if(r >= SURVIVECHANCEADULT){
		if(get_adultos() > 0){
			set_adultos(get_adultos()-1);
			set_count(get_count()-1);
		}
	}else if(r >= SURVIVECHANCECHILD){
		if(get_count() > get_adultos()){
			set_count(get_count()-1);
		}
	}
	if(get_count() == 0){
		return 1;
	}else return 0;
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