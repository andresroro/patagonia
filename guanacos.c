#include "header.h"
#include "manada_guanacos_agent_header.h"
#include "commons.h"
#include <time.h>

//variables

int id, familia, xcord, ycord, count, calorias, adultos, season;

int manadaInfo(){

	id= get_id();
	familia=get_familia();
	xcord = get_xcord();
	ycord = get_ycord();
	count = get_count();
	calorias = get_calorias();
	adultos = get_adultos();
	season = get_season();

	return 0;
}

int manada_idle(){
	return 0;
}

int move(){
	int r;
	r = rand();	
	add_adultospatch_message(get_xcord(), get_ycord(), get_adultos(), 0);
	if (season==DRY){
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
	}
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