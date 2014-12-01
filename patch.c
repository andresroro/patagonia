#include "header.h"
#include "patch_agent_header.h" 
#include "commons.h"
#include <math.h>

/* patch calories and patch information and calorie proportion of ecah clan workforce over the total clans in the patch*/
int patchtype()
{

        int pt=get_tpatch(),pID=get_patchID();
        int px=get_xcord(),py=get_ycord();

        if(px==0){
		set_tpatch(HM);
		set_repows(HMRWS);
		set_repods(HMRDS);
	}
        else if(px==1){
		set_tpatch(LM);
		set_repows(LMRWS);
		set_repods(LMRDS);
	}
        else if ((py==0)||(py==GRIDSIZE-1)||(px==GRIDSIZE-1)){ 
		set_tpatch(C);
		set_repows(CRWS);
		set_repods(CRDS);
	}
        else if ((px<=GRIDSIZE-1)/2){ 
		set_tpatch(DP);
		set_repows(DPRWS);
		set_repods(DPRDS);
	}
        else{ 
		set_tpatch(WP);
		set_repows(WPRWS);
		set_repods(WPRDS);
	}

	set_repo( get_repows() );
        
        return 0;
}

int patchcalories()
{
        int pID = get_patchID(), availc=get_pcalories(), rem_cal=get_pcalories(), cal;
        int twf = 0;
	int i, nc = 0;
	float prop;

        START_CLAN_INFO_MESSAGE_LOOP
		clans_in_patch[nc].cID = clan_info_message->cID;
                clans_in_patch[nc].wf  = clan_info_message->wf; 
                clans_in_patch[nc].maxcc = clan_info_message->maxcc;
		nc++;  
		twf += clans_in_patch[nc].wf;
        FINISH_CLAN_INFO_MESSAGE_LOOP

	for( i = 0; i < nc; i++ ){
		prop = (1.0*clans_in_patch[i].wf)/twf;
		cal = prop*availc;
		if ( cal > clans_in_patch[i].maxcc ) cal = clans_in_patch[i].maxcc;
		rem_cal -= cal;
		add_clangetcalories_message( clans_in_patch[i].cID, cal );
	}

        set_pcalories(rem_cal);
        return 0;
}

int regenerate()
{
	int avail = get_pcalories();
	if ( !avail ) avail = 1000;
	else avail = avail*get_repo();
	set_pcalories( avail );
	return 0;
}
	
int guanacos_move()
{

	int adultos = get_adultos();
	START_ADULTOSPATCH_MESSAGE_LOOP
		if(adultospatch_message->sentido == 1){
			adultos+=adultospatch_message->adultos;
		}
		if(adultospatch_message->sentido == 0){
			adultos-=adultospatch_message->adultos;
		}
	FINISH_ADULTOSPATCH_MESSAGE_LOOP
	set_adultos(adultos);
	set_gcalories(adultos*CAL_ADULTO);
	return 0;
}

int snregenerate()
{
    int pt=get_tpatch();
    int season = get_season(); 

    if (season == DRY){
	set_season( DRY );
	set_repo( get_repods());
    } else {
        set_season( WET );
	set_repo( get_repows());

	return 0;
    }
}

int reproduccion_guanacos()
{

    
	int r, i, aux;
	int familias=0, crias=0, hembras=0, machos=0;


	if( get_adultos() > 0){

	    START_REPRODUCCIONGUANACOS_MESSAGE_LOOP
	    	familias += reproduccionguanacos_message->familia; //cuento las familias
	    	if(reproduccionguanacos_message->familia){
	    		machos += reproduccionguanacos_message->familia; //cuento el macho de cada familia
	    		crias += reproduccionguanacos_message->count; 
	    	}
	    	else machos += reproduccionguanacos_message->count; //si no es familia todos son machos (incluidas las crias)
	    FINISH_REPRODUCCIONGUANACOS_MESSAGE_LOOP

	    crias -= get_adultos(); //sabemos el numero de crias que contiene el patch
	    hembras = familias*(MAX_FAMILIA-1); //calculamos el numero de hembras
	    r = rand();
	    if(crias >0){
	    r = r % crias;
	    r = crias - r;
	    hembras += r; //hembras que eran crias ahora son adultas
	    crias -= r;
	    machos += crias; //nuevos machos
	    } 
	    aux = 1+((hembras-1)/MAX_FAMILIA); //numero de familias nuevas que se crean
	    /*for(i = 0; i < aux; i++){
	    	if(hembras > MAX_FAMILIA-1){
		    	add_manada_guanacos_agent(0, 1, get_xcord(), get_ycord(), (MAX_FAMILIA*2)-1, 0, MAX_FAMILIA); //creamos familias
		    	machos--;
		    	hembras -= MAX_FAMILIA-1;
		    }
		    else{
		    	add_manada_guanacos_agent(0, 1, get_xcord(), get_ycord(), (2*hembras)+1, 0, hembras+1);
		    	hembras = 0;
		    	machos--;
		    }
	    }*/
		while (hembras > MAX_FAMILIA-1){
			add_manada_guanacos_agent(1, get_xcord(), get_ycord(), (MAX_FAMILIA*2)-1, 0, MAX_FAMILIA); //creamos familias
		    machos--;
		    hembras -= MAX_FAMILIA-1;
		}
		if (hembras >= 1){
			add_manada_guanacos_agent(1, get_xcord(), get_ycord(), (hembras*2)+1, 0, hembras+1);
			machos--;
			hembras = 0;
		}

	    while(machos >= MAX_MANADA){
	    	add_manada_guanacos_agent(0, get_xcord(), get_ycord(), MAX_MANADA, 0, MAX_MANADA); //creamos manadas
	    	machos-= MAX_MANADA;
	    }
	    if(machos >= 1){
	    	add_manada_guanacos_agent(0, get_xcord(), get_ycord(), machos, 0, machos); //creamos la manada con los ultimos machos
	    	machos= 0;
	    }
    }
    
    return 0;
}

int idle_patch()
{
	return 0;
}

