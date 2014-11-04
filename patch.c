#include "header.h"
#include "patch_agent_header.h" 
#include "commons.h"

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
	/*int avail = get_pcalories();
	if ( !avail ) avail = 1000;
	else avail = avail*get_repo();
	set_pcalories( avail );*/
	int cals =0;
	START_CALGUANACOS_MESSAGE_LOOP
		cals+=calguanacos_message->calorias;
	FINISH_CALGUANACOS_MESSAGE_LOOP
	set_pcalories(cals);
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
    }
    
    return 0;
}

int idle_patch()
{
	return 0;
}

