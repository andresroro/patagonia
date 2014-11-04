#include "header.h"
#include "manada_guanacos_agent_header.h"

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
	srand(time(NULL));
	r = rand();	
	if (season==DRY){
		if(ycord <= 7){
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
					if(xcord < 13){
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
					if(ycord < 14){
						set_ycord(ycord+1);
					}
					break;
				case 1:
					if(ycord < 14){
						set_ycord(ycord+1);
					}
					break;
				case 2:
					if(xcord < 13){
						set_xcord(xcord+1);
					}
					if(ycord < 14){
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
				if(xcord < 13){
					set_xcord(xcord+1);
				}
				if(ycord > 0){
					set_ycord(ycord-1);
				}
				break;
			case 3:
				if(xcord < 13){
					set_xcord(xcord+1);
				}
				break;
			case 4:
				if(xcord < 13){
					set_xcord(xcord+1);
				}
				if(ycord < 14){
					set_ycord(ycord+1);
				}
				break;
			case 5:
				if(ycord < 14){
					set_ycord(ycord+1);
				}
				break;
			case 6:
				if(xcord > 1){
					set_xcord(xcord-1);
				}
				if(ycord < 14){
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
	return 0;
}

int post_calorias(){
	add_calguanacos_message(xcord, ycord, calorias);
	return 0;
}