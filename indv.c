#include <math.h>
#include "header.h"
#include "indv_agent_header.h"

/* posting individual information*/
int indvInformation()
{
	int cal=get_cal_needs(), ID=get_indvID(), ageX=get_age(), cIDX=get_cID(), pregX=get_pregnant();


	set_icalories(cal);
        add_information_message(ID,cIDX,cal,ageX,pregX);
        return 0;
}

/* extracting calories */
int extractcalories()
{
	int cal, myneed=get_icalories();

	START_INDGETCALORIES_MESSAGE_LOOP

		cal=indgetcalories_message->icalories;
 		myneed=myneed-cal;
		set_icalories(myneed);

	FINISH_INDGETCALORIES_MESSAGE_LOOP

	return 0;
}

int getolder()
{
	int age = get_age(), caln = get_cal_needs();

	age++;

	switch( age ){
		case 1: //toddler?
			break;
		case 36: //child?
			break;
		case 144: //fertile girls - marriable girls and boys?
			set_cal_needs( caln + 500 );
			break;
		case 240: //adult - male could be leader?
			set_cal_needs( caln + 1000 );
			break;
		case 480: //old?
			set_cal_needs( caln - 500 );
			break;
		case 600: //very old?
			set_cal_needs( caln - 500 );
			break;
	}
	set_age(age);
	return 0;
}

int idle_indv()
{
	return 0;
}

int survive()
{
	int die, age = get_age(), sex = get_sex(), cal = get_icalories();
	float p = 0.001;

	if ( age <= 36 ) p += 0.005;
	if ( age >= 480 ) p += 0.005;
	if ( age >= 600 ) p += 0.01;
	if ( age >= 720 ) p += 0.1 + (age - 720)*0.01;
	if ( age >= 840 ) p += 0.2 + (age - 840)*0.01;

	if ( sex == 0 ) p += 0.005;

	if ( cal > 0 ) p = p + (0.000001 * cal);

        die = ((1.0*rand())/(RAND_MAX+1.0)) < p;

	if( !die ) add_leader_message( get_indvID(), get_cID(), get_lead(), get_sex(), get_age() );

	return die; 
}
