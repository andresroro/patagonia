/**
 * \file  memory.c
 * \brief Holds memory functions.
 */

#include "header.h"


void unittest_indvInformation_start_01()
{
	
	
	//return indvInformation();
}

void unittest_extractcalories_01_02()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_indgetcalories, &i_indgetcalories, &FLAME_filter_indv_extractcalories_01_02_indgetcalories, current_xmachine_indv);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'indgetcalories'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'indgetcalories' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'indgetcalories' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return extractcalories();
}

void unittest_getolder_02_03()
{
	
	
	//return getolder();
}

void unittest_idle_indv_02_03()
{
	
	
	//return idle_indv();
}

void unittest_survive_03_end()
{
	
	
	//return survive();
}

void unittest_clan_Information_start_01()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_information, &i_information, &FLAME_filter_clan_clan_Information_start_01_information, current_xmachine_clan);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'information'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'information' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'information' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return clan_Information();
}

void unittest_clan_extract_calories_01_02()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_clangetcalories, &i_clangetcalories, &FLAME_filter_clan_clan_extract_calories_01_02_clangetcalories, current_xmachine_clan);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'clangetcalories'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'clangetcalories' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clangetcalories' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return clan_extract_calories();
}

void unittest_distribute_calories_02_03()
{
	
	
	//return distribute_calories();
}

void unittest_new_leader_03_end()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_leader, &i_leader, &FLAME_filter_clan_new_leader_03_end_leader, current_xmachine_clan);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'leader'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'leader' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'leader' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return new_leader();
}

void unittest_patchtype_start_1()
{
	
	
	//return patchtype();
}

void unittest_patchcalories_1_2()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_clan_info, &i_clan_info, &FLAME_filter_patch_patchcalories_1_2_clan_info, current_xmachine_patch);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'clan_info'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'clan_info' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clan_info' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return patchcalories();
}

void unittest_regenerate_2_3()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_adultospatch, &i_adultospatch, &FLAME_filter_patch_regenerate_2_3_adultospatch, current_xmachine_patch);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'adultospatch'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'adultospatch' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'adultospatch' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return regenerate();
}

void unittest_snregenerate_3_end()
{
	int rc;
	
	rc = MB_Iterator_CreateFiltered(b_reproduccionguanacos, &i_reproduccionguanacos, &FLAME_filter_patch_snregenerate_3_end_reproduccionguanacos, current_xmachine_patch);
	
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not create Iterator for 'reproduccionguanacos'\n");
	   switch(rc) {
	       case MB_ERR_INVALID:
	           fprintf(stderr, "\t reason: 'reproduccionguanacos' board is invalid\n");
	           break;
	       case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'reproduccionguanacos' board is locked\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	   }
	}
	#endif
	
	//return snregenerate();
}

void unittest_idle_patch_3_end()
{
	
	
	//return idle_patch();
}

void unittest_manadaInfo_start_1()
{
	
	
	//return manadaInfo();
}

void unittest_manada_idle_1_2()
{
	
	
	//return manada_idle();
}

void unittest_move_1_2()
{
	
	
	//return move();
}

void unittest_reproduccion_2_end()
{
	
	
	//return reproduccion();
}

void unittest_manada_idle2_2_end()
{
	
	
	//return manada_idle2();
}


void free_messages()
{
	int rc;
	
	    rc = MB_Clear(b_information);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'information' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'information' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'information' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	    rc = MB_Clear(b_indgetcalories);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'indgetcalories' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'indgetcalories' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'indgetcalories' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	    rc = MB_Clear(b_leader);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'leader' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'leader' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'leader' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	    rc = MB_Clear(b_clan_info);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'clan_info' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'clan_info' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'clan_info' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	    rc = MB_Clear(b_clangetcalories);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'clangetcalories' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'clangetcalories' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'clangetcalories' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	    rc = MB_Clear(b_adultospatch);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'adultospatch' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'adultospatch' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'adultospatch' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	    rc = MB_Clear(b_reproduccionguanacos);
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not clear 'reproduccionguanacos' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: 'reproduccionguanacos' board is invalid\n");
	               break;
	           case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'reproduccionguanacos' board is locked\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Clear returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
}

/** \fn void initialise_pointers()
 * \brief Initialises pointers to xmachine, message, and node lists.
 */
void initialise_pointers()
{
int rc;

	/* Initialise message sync composite params as NULL */
	FLAME_m_information_composite_params = NULL;

	    rc = MB_Create(&b_information, sizeof(m_information));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'information' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	/* Initialise message sync composite params as NULL */
	FLAME_m_indgetcalories_composite_params = NULL;

	    rc = MB_Create(&b_indgetcalories, sizeof(m_indgetcalories));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'indgetcalories' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	/* Initialise message sync composite params as NULL */
	FLAME_m_leader_composite_params = NULL;

	    rc = MB_Create(&b_leader, sizeof(m_leader));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'leader' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	/* Initialise message sync composite params as NULL */
	FLAME_m_clan_info_composite_params = NULL;

	    rc = MB_Create(&b_clan_info, sizeof(m_clan_info));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'clan_info' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	/* Initialise message sync composite params as NULL */
	FLAME_m_clangetcalories_composite_params = NULL;

	    rc = MB_Create(&b_clangetcalories, sizeof(m_clangetcalories));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'clangetcalories' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	/* Initialise message sync composite params as NULL */
	FLAME_m_adultospatch_composite_params = NULL;

	    rc = MB_Create(&b_adultospatch, sizeof(m_adultospatch));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'adultospatch' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	/* Initialise message sync composite params as NULL */
	FLAME_m_reproduccionguanacos_composite_params = NULL;

	    rc = MB_Create(&b_reproduccionguanacos, sizeof(m_reproduccionguanacos));
	    #ifdef ERRCHECK
	    if (rc != MB_SUCCESS)
	    {
	       fprintf(stderr, "ERROR: Could not create 'reproduccionguanacos' board\n");
	       switch(rc) {
	           case MB_ERR_INVALID:
	               fprintf(stderr, "\t reason: Invalid message size\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
                   fprintf(stderr, "\t MB_Create returned error code: %d (see libmboard docs for details)\n", rc);
                   break;
	       }

	       
       	   exit(rc);
	    }
	    #endif
	
	indv_end_state = init_indv_state();

	indv_03_state = init_indv_state();

	indv_02_state = init_indv_state();

	indv_01_state = init_indv_state();

	indv_start_state = init_indv_state();

	clan_end_state = init_clan_state();

	clan_03_state = init_clan_state();

	clan_02_state = init_clan_state();

	clan_01_state = init_clan_state();

	clan_start_state = init_clan_state();

	patch_end_state = init_patch_state();

	patch_3_state = init_patch_state();

	patch_2_state = init_patch_state();

	patch_1_state = init_patch_state();

	patch_start_state = init_patch_state();

	manada_guanacos_end_state = init_manada_guanacos_state();

	manada_guanacos_2_state = init_manada_guanacos_state();

	manada_guanacos_1_state = init_manada_guanacos_state();

	manada_guanacos_start_state = init_manada_guanacos_state();

	temp_node_info = NULL;
	p_node_info = &temp_node_info;
}

/** \fn void initialise_unit_testing()
 * \brief Initialises framework for unit testing.
 */
void initialise_unit_testing()
{
	int rc;

	rc = MB_Env_Init();
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Failed to initialise Message Board environment\n");
	   switch(rc) {
	       case MB_ERR_MPI:
	           fprintf(stderr, "\t reason: MPI library not initialised\n");
	           break;
	       case MB_ERR_MEMALLOC:
	           fprintf(stderr, "\t reason: out of memory\n");
	           break;
	       default:
               fprintf(stderr, "\t MB_Env_Init returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);

	}
	#endif

	initialise_pointers();
}

FLAME_output * add_FLAME_output(FLAME_output ** outputs)
{
	FLAME_output * current;

	current = (FLAME_output *)malloc(sizeof(FLAME_output));
	CHECK_POINTER(current);
	current->next = *outputs;
	*outputs = current;

	current->type = -1;
	current->format = -1;
	current->location = NULL;
	current->period = -1;
	current->phase = -1;
	current->flag = 0;

	return current;
}

void free_FLAME_outputs(FLAME_output ** outputs)
{
	FLAME_output * current, * next;

	current = *outputs;
	while(current)
	{
		next = current->next;
		free(current->location);
		free(current);
		current = next;
	}
	*outputs = NULL;
}

/* add_location */
/** \fn void add_location(double point, location ** p_location)
 * \brief Adds a location in order into the location list.
 * \param point Position of an agent.
 * \param p_location Pointer Pointer to the location list.
 */
void add_location(double point, location ** p_location)
{
	location * current = *p_location;
	location * tmp = NULL;
	location * newlocation = NULL;
	int found = 0;

	while(found == 0)
	{
		if(current == NULL) found = 1;
		else if(point > current->point) found = 1;
		else
		{
			tmp = current;
			current = current->next;
		}
	}

	newlocation = (location *)malloc(sizeof(location));
	CHECK_POINTER(newlocation);
	if(tmp)
	{
		tmp->next = newlocation;
	}
	else
	{
		*p_location = newlocation;
	}

	newlocation->next = current;
	newlocation->point = point;
}

/* freelocations */
/** \fn void freelocations(location ** p_location)
 * \brief Free locations from the location list.
 * \param p_location Pointer Pointer to the location list.
 */
void freelocations(location ** p_location)
{
	location * head = *p_location;
	location * tmp = NULL;

	while(head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}

	*p_location = NULL;
}

void init_int_static_array(/*@out@*/ int * array, int size)
{
	int i;

	for(i = 0; i < size; i++) array[i] = 0;
}

void init_float_static_array(/*@out@*/ float * array, int size)
{
	int i;

	for(i = 0; i < size; i++) array[i] = 0.0;
}

void init_double_static_array(/*@out@*/ double* array, int size)
{
	int i;

	for(i = 0; i < size; i++) array[i] = 0.0;
}

void init_char_static_array(/*@out@*/ char * array, int size)
{
	int i;

	for(i = 0; i < size; i++) array[i] = '\0';
}



void init_members_needs(/*@out@*/ members_needs * temp)
{
	init_int_static_array((*temp).id_list, 100);
	init_int_static_array((*temp).cal_list, 100);
	init_int_static_array((*temp).age, 100);

}

void init_members_needs_static_array(/*@out@*/ members_needs * array, int size)
{
	int i;

	for(i = 0; i < size; i++) init_members_needs(&array[i]);
}

void free_members_needs(members_needs * temp)
{

}

void free_members_needs_static_array(members_needs * array, int size)
{
	int i;

	for(i = 0; i < size; i++) free_members_needs(&array[i]);
}

void copy_members_needs(members_needs * from, members_needs * to)
{
	memcpy((*to).id_list, (*from).id_list, 100*sizeof(int));
	memcpy((*to).cal_list, (*from).cal_list, 100*sizeof(int));
	memcpy((*to).age, (*from).age, 100*sizeof(int));
}

void copy_members_needs_static_array(members_needs * from, members_needs * to, int size)
{
	int i;

	for(i = 0; i < size; i++)
	{
		copy_members_needs(&from[i], &to[i]);
	}
}



xmachine_memory_indv_state * init_indv_state()
{
	xmachine_memory_indv_state * current = (xmachine_memory_indv_state *)malloc(sizeof(xmachine_memory_indv_state));
	CHECK_POINTER(current);

	current->agents = NULL;
	current->count = 0;

	return current;
}

xmachine_memory_indv * init_indv_agent()
{
	xmachine_memory_indv * current = (xmachine_memory_indv *)malloc(sizeof(xmachine_memory_indv));
	CHECK_POINTER(current);

	current->indvID = 0;
	current->cID = 0;
	current->cal_needs = 0;
	current->icalories = 0;
	current->patchID = 0;
	current->age = 0;
	current->sex = 0;
	current->pregnant = 0;
	current->lead = 0;

	return current;
}

void free_indv_agent(xmachine_memory_indv_holder * tmp, xmachine_memory_indv_state * state)
{
	if(tmp->prev == NULL) state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	

	free(tmp->agent);
	free(tmp);
}

void unittest_init_indv_agent()
{
	current_xmachine_indv = (xmachine_memory_indv *)malloc(sizeof(xmachine_memory_indv));
	CHECK_POINTER(current);

		current_xmachine_indv->indvID = 0;
		current_xmachine_indv->cID = 0;
		current_xmachine_indv->cal_needs = 0;
		current_xmachine_indv->icalories = 0;
		current_xmachine_indv->patchID = 0;
		current_xmachine_indv->age = 0;
		current_xmachine_indv->sex = 0;
		current_xmachine_indv->pregnant = 0;
		current_xmachine_indv->lead = 0;
	
}

void unittest_free_indv_agent()
{
	
	free(current_xmachine_indv);
}

void free_indv_agents()
{
	current_xmachine_indv_holder = indv_end_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		free_indv_agent(current_xmachine_indv_holder, indv_end_state);
		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	indv_end_state->count = 0;
	current_xmachine_indv_holder = indv_03_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		free_indv_agent(current_xmachine_indv_holder, indv_03_state);
		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	indv_03_state->count = 0;
	current_xmachine_indv_holder = indv_02_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		free_indv_agent(current_xmachine_indv_holder, indv_02_state);
		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	indv_02_state->count = 0;
	current_xmachine_indv_holder = indv_01_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		free_indv_agent(current_xmachine_indv_holder, indv_01_state);
		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	indv_01_state->count = 0;
	current_xmachine_indv_holder = indv_start_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		free_indv_agent(current_xmachine_indv_holder, indv_start_state);
		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	indv_start_state->count = 0;
}

void free_indv_states()
{
	free(indv_end_state);
	free(indv_03_state);
	free(indv_02_state);
	free(indv_01_state);
	free(indv_start_state);
}

void transition_indv_agent(xmachine_memory_indv_holder * tmp, xmachine_memory_indv_state * from_state, xmachine_memory_indv_state * to_state)
{
	if(tmp->prev == NULL) from_state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	add_indv_agent_internal(tmp->agent, to_state);
	free(tmp);
}

void add_indv_agent_internal(xmachine_memory_indv * agent, xmachine_memory_indv_state * state)
{
	xmachine_memory_indv_holder * current = (xmachine_memory_indv_holder *)malloc(sizeof(xmachine_memory_indv_holder));
	CHECK_POINTER(current);

	current->next = state->agents;
	current->prev = NULL;
	state->agents = current;
	if(current->next != NULL) current->next->prev = current;
	current->agent = agent;

	state->count++;

}

/** \fn void add_indv_agent(int indvID, int cID, int cal_needs, int icalories, int patchID, int age, int sex, int pregnant, int lead)
 * \brief Add indv X-machine to the current being used X-machine list.
 * \param indvID Variable for the X-machine memory.
 * \param cID Variable for the X-machine memory.
 * \param cal_needs Variable for the X-machine memory.
 * \param icalories Variable for the X-machine memory.
 * \param patchID Variable for the X-machine memory.
 * \param age Variable for the X-machine memory.
 * \param sex Variable for the X-machine memory.
 * \param pregnant Variable for the X-machine memory.
 * \param lead Variable for the X-machine memory.
 */
void add_indv_agent(int indvID, int cID, int cal_needs, int icalories, int patchID, int age, int sex, int pregnant, int lead)
{
	xmachine_memory_indv * current;

	current = init_indv_agent();
	/* new line added to handle dynamic agent creation*/
	current_xmachine_indv_next_state = indv_start_state;
	add_indv_agent_internal(current, current_xmachine_indv_next_state);

	current->indvID = indvID;
	current->cID = cID;
	current->cal_needs = cal_needs;
	current->icalories = icalories;
	current->patchID = patchID;
	current->age = age;
	current->sex = sex;
	current->pregnant = pregnant;
	current->lead = lead;
}

xmachine_memory_clan_state * init_clan_state()
{
	xmachine_memory_clan_state * current = (xmachine_memory_clan_state *)malloc(sizeof(xmachine_memory_clan_state));
	CHECK_POINTER(current);

	current->agents = NULL;
	current->count = 0;

	return current;
}

xmachine_memory_clan * init_clan_agent()
{
	xmachine_memory_clan * current = (xmachine_memory_clan *)malloc(sizeof(xmachine_memory_clan));
	CHECK_POINTER(current);

	current->cID = 0;
	current->cal_need = 0;
	current->cal_got = 0;
	current->cal_stored = 0;
	current->xcord = 0;
	current->ycord = 0;
	current->tcalories = 0;
	current->leaderID = 0;
	init_members_needs(&current->mneeds);

	return current;
}

void free_clan_agent(xmachine_memory_clan_holder * tmp, xmachine_memory_clan_state * state)
{
	if(tmp->prev == NULL) state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	free_members_needs(&tmp->agent->mneeds);
	

	free(tmp->agent);
	free(tmp);
}

void unittest_init_clan_agent()
{
	current_xmachine_clan = (xmachine_memory_clan *)malloc(sizeof(xmachine_memory_clan));
	CHECK_POINTER(current);

		current_xmachine_clan->cID = 0;
		current_xmachine_clan->cal_need = 0;
		current_xmachine_clan->cal_got = 0;
		current_xmachine_clan->cal_stored = 0;
		current_xmachine_clan->xcord = 0;
		current_xmachine_clan->ycord = 0;
		current_xmachine_clan->tcalories = 0;
		current_xmachine_clan->leaderID = 0;
		init_members_needs(&current_xmachine_clan->mneeds);
	
}

void unittest_free_clan_agent()
{
	free_members_needs(&current_xmachine_clan->mneeds);
	
	free(current_xmachine_clan);
}

void free_clan_agents()
{
	current_xmachine_clan_holder = clan_end_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		free_clan_agent(current_xmachine_clan_holder, clan_end_state);
		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	clan_end_state->count = 0;
	current_xmachine_clan_holder = clan_03_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		free_clan_agent(current_xmachine_clan_holder, clan_03_state);
		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	clan_03_state->count = 0;
	current_xmachine_clan_holder = clan_02_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		free_clan_agent(current_xmachine_clan_holder, clan_02_state);
		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	clan_02_state->count = 0;
	current_xmachine_clan_holder = clan_01_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		free_clan_agent(current_xmachine_clan_holder, clan_01_state);
		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	clan_01_state->count = 0;
	current_xmachine_clan_holder = clan_start_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		free_clan_agent(current_xmachine_clan_holder, clan_start_state);
		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	clan_start_state->count = 0;
}

void free_clan_states()
{
	free(clan_end_state);
	free(clan_03_state);
	free(clan_02_state);
	free(clan_01_state);
	free(clan_start_state);
}

void transition_clan_agent(xmachine_memory_clan_holder * tmp, xmachine_memory_clan_state * from_state, xmachine_memory_clan_state * to_state)
{
	if(tmp->prev == NULL) from_state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	add_clan_agent_internal(tmp->agent, to_state);
	free(tmp);
}

void add_clan_agent_internal(xmachine_memory_clan * agent, xmachine_memory_clan_state * state)
{
	xmachine_memory_clan_holder * current = (xmachine_memory_clan_holder *)malloc(sizeof(xmachine_memory_clan_holder));
	CHECK_POINTER(current);

	current->next = state->agents;
	current->prev = NULL;
	state->agents = current;
	if(current->next != NULL) current->next->prev = current;
	current->agent = agent;

	state->count++;

}

/** \fn void add_clan_agent(int cID, int cal_need, int cal_got, int cal_stored, int xcord, int ycord, int tcalories, int leaderID, members_needs * mneeds)
 * \brief Add clan X-machine to the current being used X-machine list.
 * \param cID Variable for the X-machine memory.
 * \param cal_need Variable for the X-machine memory.
 * \param cal_got Variable for the X-machine memory.
 * \param cal_stored Variable for the X-machine memory.
 * \param xcord Variable for the X-machine memory.
 * \param ycord Variable for the X-machine memory.
 * \param tcalories Variable for the X-machine memory.
 * \param leaderID Variable for the X-machine memory.
 * \param mneeds Variable for the X-machine memory.
 */
void add_clan_agent(int cID, int cal_need, int cal_got, int cal_stored, int xcord, int ycord, int tcalories, int leaderID, members_needs mneeds)
{
	xmachine_memory_clan * current;

	current = init_clan_agent();
	/* new line added to handle dynamic agent creation*/
	current_xmachine_clan_next_state = clan_start_state;
	add_clan_agent_internal(current, current_xmachine_clan_next_state);

	current->cID = cID;
	current->cal_need = cal_need;
	current->cal_got = cal_got;
	current->cal_stored = cal_stored;
	current->xcord = xcord;
	current->ycord = ycord;
	current->tcalories = tcalories;
	current->leaderID = leaderID;
	copy_members_needs(&mneeds, &current->mneeds);
}

xmachine_memory_patch_state * init_patch_state()
{
	xmachine_memory_patch_state * current = (xmachine_memory_patch_state *)malloc(sizeof(xmachine_memory_patch_state));
	CHECK_POINTER(current);

	current->agents = NULL;
	current->count = 0;

	return current;
}

xmachine_memory_patch * init_patch_agent()
{
	xmachine_memory_patch * current = (xmachine_memory_patch *)malloc(sizeof(xmachine_memory_patch));
	CHECK_POINTER(current);

	current->patchID = 0;
	current->pcalories = 0;
	current->repo = 0.0;
	current->tpatch = 0;
	current->xcord = 0;
	current->ycord = 0;
	current->repows = 0.0;
	current->repods = 0.0;
	current->season = 0;
	current->adultos = 0;

	return current;
}

void free_patch_agent(xmachine_memory_patch_holder * tmp, xmachine_memory_patch_state * state)
{
	if(tmp->prev == NULL) state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	

	free(tmp->agent);
	free(tmp);
}

void unittest_init_patch_agent()
{
	current_xmachine_patch = (xmachine_memory_patch *)malloc(sizeof(xmachine_memory_patch));
	CHECK_POINTER(current);

		current_xmachine_patch->patchID = 0;
		current_xmachine_patch->pcalories = 0;
		current_xmachine_patch->repo = 0.0;
		current_xmachine_patch->tpatch = 0;
		current_xmachine_patch->xcord = 0;
		current_xmachine_patch->ycord = 0;
		current_xmachine_patch->repows = 0.0;
		current_xmachine_patch->repods = 0.0;
		current_xmachine_patch->season = 0;
		current_xmachine_patch->adultos = 0;
	
}

void unittest_free_patch_agent()
{
	
	free(current_xmachine_patch);
}

void free_patch_agents()
{
	current_xmachine_patch_holder = patch_end_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		free_patch_agent(current_xmachine_patch_holder, patch_end_state);
		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	patch_end_state->count = 0;
	current_xmachine_patch_holder = patch_3_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		free_patch_agent(current_xmachine_patch_holder, patch_3_state);
		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	patch_3_state->count = 0;
	current_xmachine_patch_holder = patch_2_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		free_patch_agent(current_xmachine_patch_holder, patch_2_state);
		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	patch_2_state->count = 0;
	current_xmachine_patch_holder = patch_1_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		free_patch_agent(current_xmachine_patch_holder, patch_1_state);
		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	patch_1_state->count = 0;
	current_xmachine_patch_holder = patch_start_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		free_patch_agent(current_xmachine_patch_holder, patch_start_state);
		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	patch_start_state->count = 0;
}

void free_patch_states()
{
	free(patch_end_state);
	free(patch_3_state);
	free(patch_2_state);
	free(patch_1_state);
	free(patch_start_state);
}

void transition_patch_agent(xmachine_memory_patch_holder * tmp, xmachine_memory_patch_state * from_state, xmachine_memory_patch_state * to_state)
{
	if(tmp->prev == NULL) from_state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	add_patch_agent_internal(tmp->agent, to_state);
	free(tmp);
}

void add_patch_agent_internal(xmachine_memory_patch * agent, xmachine_memory_patch_state * state)
{
	xmachine_memory_patch_holder * current = (xmachine_memory_patch_holder *)malloc(sizeof(xmachine_memory_patch_holder));
	CHECK_POINTER(current);

	current->next = state->agents;
	current->prev = NULL;
	state->agents = current;
	if(current->next != NULL) current->next->prev = current;
	current->agent = agent;

	state->count++;

}

/** \fn void add_patch_agent(int patchID, int pcalories, float repo, int tpatch, int xcord, int ycord, float repows, float repods, int season, int adultos)
 * \brief Add patch X-machine to the current being used X-machine list.
 * \param patchID Variable for the X-machine memory.
 * \param pcalories Variable for the X-machine memory.
 * \param repo Variable for the X-machine memory.
 * \param tpatch Variable for the X-machine memory.
 * \param xcord Variable for the X-machine memory.
 * \param ycord Variable for the X-machine memory.
 * \param repows Variable for the X-machine memory.
 * \param repods Variable for the X-machine memory.
 * \param season Variable for the X-machine memory.
 * \param adultos Variable for the X-machine memory.
 */
void add_patch_agent(int patchID, int pcalories, float repo, int tpatch, int xcord, int ycord, float repows, float repods, int season, int adultos)
{
	xmachine_memory_patch * current;

	current = init_patch_agent();
	/* new line added to handle dynamic agent creation*/
	current_xmachine_patch_next_state = patch_start_state;
	add_patch_agent_internal(current, current_xmachine_patch_next_state);

	current->patchID = patchID;
	current->pcalories = pcalories;
	current->repo = repo;
	current->tpatch = tpatch;
	current->xcord = xcord;
	current->ycord = ycord;
	current->repows = repows;
	current->repods = repods;
	current->season = season;
	current->adultos = adultos;
}

xmachine_memory_manada_guanacos_state * init_manada_guanacos_state()
{
	xmachine_memory_manada_guanacos_state * current = (xmachine_memory_manada_guanacos_state *)malloc(sizeof(xmachine_memory_manada_guanacos_state));
	CHECK_POINTER(current);

	current->agents = NULL;
	current->count = 0;

	return current;
}

xmachine_memory_manada_guanacos * init_manada_guanacos_agent()
{
	xmachine_memory_manada_guanacos * current = (xmachine_memory_manada_guanacos *)malloc(sizeof(xmachine_memory_manada_guanacos));
	CHECK_POINTER(current);

	current->id = 0;
	current->familia = 0;
	current->xcord = 0;
	current->ycord = 0;
	current->count = 0;
	current->calorias = 0;
	current->adultos = 0;

	return current;
}

void free_manada_guanacos_agent(xmachine_memory_manada_guanacos_holder * tmp, xmachine_memory_manada_guanacos_state * state)
{
	if(tmp->prev == NULL) state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	

	free(tmp->agent);
	free(tmp);
}

void unittest_init_manada_guanacos_agent()
{
	current_xmachine_manada_guanacos = (xmachine_memory_manada_guanacos *)malloc(sizeof(xmachine_memory_manada_guanacos));
	CHECK_POINTER(current);

		current_xmachine_manada_guanacos->id = 0;
		current_xmachine_manada_guanacos->familia = 0;
		current_xmachine_manada_guanacos->xcord = 0;
		current_xmachine_manada_guanacos->ycord = 0;
		current_xmachine_manada_guanacos->count = 0;
		current_xmachine_manada_guanacos->calorias = 0;
		current_xmachine_manada_guanacos->adultos = 0;
	
}

void unittest_free_manada_guanacos_agent()
{
	
	free(current_xmachine_manada_guanacos);
}

void free_manada_guanacos_agents()
{
	current_xmachine_manada_guanacos_holder = manada_guanacos_end_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_end_state);
		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	manada_guanacos_end_state->count = 0;
	current_xmachine_manada_guanacos_holder = manada_guanacos_2_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state);
		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	manada_guanacos_2_state->count = 0;
	current_xmachine_manada_guanacos_holder = manada_guanacos_1_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_1_state);
		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	manada_guanacos_1_state->count = 0;
	current_xmachine_manada_guanacos_holder = manada_guanacos_start_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state);
		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	manada_guanacos_start_state->count = 0;
}

void free_manada_guanacos_states()
{
	free(manada_guanacos_end_state);
	free(manada_guanacos_2_state);
	free(manada_guanacos_1_state);
	free(manada_guanacos_start_state);
}

void transition_manada_guanacos_agent(xmachine_memory_manada_guanacos_holder * tmp, xmachine_memory_manada_guanacos_state * from_state, xmachine_memory_manada_guanacos_state * to_state)
{
	if(tmp->prev == NULL) from_state->agents = tmp->next;
	else tmp->prev->next = tmp->next;
	if(tmp->next != NULL) tmp->next->prev = tmp->prev;

	add_manada_guanacos_agent_internal(tmp->agent, to_state);
	free(tmp);
}

void add_manada_guanacos_agent_internal(xmachine_memory_manada_guanacos * agent, xmachine_memory_manada_guanacos_state * state)
{
	xmachine_memory_manada_guanacos_holder * current = (xmachine_memory_manada_guanacos_holder *)malloc(sizeof(xmachine_memory_manada_guanacos_holder));
	CHECK_POINTER(current);

	current->next = state->agents;
	current->prev = NULL;
	state->agents = current;
	if(current->next != NULL) current->next->prev = current;
	current->agent = agent;

	state->count++;

}

/** \fn void add_manada_guanacos_agent(int id, int familia, int xcord, int ycord, int count, int calorias, int adultos)
 * \brief Add manada_guanacos X-machine to the current being used X-machine list.
 * \param id Variable for the X-machine memory.
 * \param familia Variable for the X-machine memory.
 * \param xcord Variable for the X-machine memory.
 * \param ycord Variable for the X-machine memory.
 * \param count Variable for the X-machine memory.
 * \param calorias Variable for the X-machine memory.
 * \param adultos Variable for the X-machine memory.
 */
void add_manada_guanacos_agent(int id, int familia, int xcord, int ycord, int count, int calorias, int adultos)
{
	xmachine_memory_manada_guanacos * current;

	current = init_manada_guanacos_agent();
	/* new line added to handle dynamic agent creation*/
	current_xmachine_manada_guanacos_next_state = manada_guanacos_start_state;
	add_manada_guanacos_agent_internal(current, current_xmachine_manada_guanacos_next_state);

	current->id = id;
	current->familia = familia;
	current->xcord = xcord;
	current->ycord = ycord;
	current->count = count;
	current->calorias = calorias;
	current->adultos = adultos;
}


/* freexmachines */
/** \fn void freexmachines()
 * \brief Free the currently being used X-machine list.
 */
void freexmachines()
{
	free_indv_agents();
	free_clan_agents();
	free_patch_agents();
	free_manada_guanacos_agents();
	
}


/** \fn void set_indvID(int indvID)
 * \brief Set indvID memory variable for current X-machine.
 * \param indvID New value for variable.
 */
void set_indvID(int indvID)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).indvID = indvID;
}

/** \fn int get_indvID()
 * \brief Get indvID memory variable from current X-machine.
 * \return Value for variable.
 */
int get_indvID()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).indvID;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_cID(int cID)
 * \brief Set cID memory variable for current X-machine.
 * \param cID New value for variable.
 */
void set_cID(int cID)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).cID = cID;
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).cID = cID;
}

/** \fn int get_cID()
 * \brief Get cID memory variable from current X-machine.
 * \return Value for variable.
 */
int get_cID()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).cID;
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).cID;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_cal_needs(int cal_needs)
 * \brief Set cal_needs memory variable for current X-machine.
 * \param cal_needs New value for variable.
 */
void set_cal_needs(int cal_needs)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).cal_needs = cal_needs;
}

/** \fn int get_cal_needs()
 * \brief Get cal_needs memory variable from current X-machine.
 * \return Value for variable.
 */
int get_cal_needs()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).cal_needs;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_icalories(int icalories)
 * \brief Set icalories memory variable for current X-machine.
 * \param icalories New value for variable.
 */
void set_icalories(int icalories)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).icalories = icalories;
}

/** \fn int get_icalories()
 * \brief Get icalories memory variable from current X-machine.
 * \return Value for variable.
 */
int get_icalories()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).icalories;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_patchID(int patchID)
 * \brief Set patchID memory variable for current X-machine.
 * \param patchID New value for variable.
 */
void set_patchID(int patchID)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).patchID = patchID;
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).patchID = patchID;
}

/** \fn int get_patchID()
 * \brief Get patchID memory variable from current X-machine.
 * \return Value for variable.
 */
int get_patchID()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).patchID;
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).patchID;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_age(int age)
 * \brief Set age memory variable for current X-machine.
 * \param age New value for variable.
 */
void set_age(int age)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).age = age;
}

/** \fn int get_age()
 * \brief Get age memory variable from current X-machine.
 * \return Value for variable.
 */
int get_age()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).age;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_sex(int sex)
 * \brief Set sex memory variable for current X-machine.
 * \param sex New value for variable.
 */
void set_sex(int sex)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).sex = sex;
}

/** \fn int get_sex()
 * \brief Get sex memory variable from current X-machine.
 * \return Value for variable.
 */
int get_sex()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).sex;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_pregnant(int pregnant)
 * \brief Set pregnant memory variable for current X-machine.
 * \param pregnant New value for variable.
 */
void set_pregnant(int pregnant)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).pregnant = pregnant;
}

/** \fn int get_pregnant()
 * \brief Get pregnant memory variable from current X-machine.
 * \return Value for variable.
 */
int get_pregnant()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).pregnant;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_lead(int lead)
 * \brief Set lead memory variable for current X-machine.
 * \param lead New value for variable.
 */
void set_lead(int lead)
{
	if(current_xmachine->xmachine_indv) (*current_xmachine->xmachine_indv).lead = lead;
}

/** \fn int get_lead()
 * \brief Get lead memory variable from current X-machine.
 * \return Value for variable.
 */
int get_lead()
{
	if(current_xmachine->xmachine_indv) return (*current_xmachine->xmachine_indv).lead;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_cal_need(int cal_need)
 * \brief Set cal_need memory variable for current X-machine.
 * \param cal_need New value for variable.
 */
void set_cal_need(int cal_need)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).cal_need = cal_need;
}

/** \fn int get_cal_need()
 * \brief Get cal_need memory variable from current X-machine.
 * \return Value for variable.
 */
int get_cal_need()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).cal_need;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_cal_got(int cal_got)
 * \brief Set cal_got memory variable for current X-machine.
 * \param cal_got New value for variable.
 */
void set_cal_got(int cal_got)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).cal_got = cal_got;
}

/** \fn int get_cal_got()
 * \brief Get cal_got memory variable from current X-machine.
 * \return Value for variable.
 */
int get_cal_got()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).cal_got;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_cal_stored(int cal_stored)
 * \brief Set cal_stored memory variable for current X-machine.
 * \param cal_stored New value for variable.
 */
void set_cal_stored(int cal_stored)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).cal_stored = cal_stored;
}

/** \fn int get_cal_stored()
 * \brief Get cal_stored memory variable from current X-machine.
 * \return Value for variable.
 */
int get_cal_stored()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).cal_stored;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_xcord(int xcord)
 * \brief Set xcord memory variable for current X-machine.
 * \param xcord New value for variable.
 */
void set_xcord(int xcord)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).xcord = xcord;
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).xcord = xcord;
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).xcord = xcord;
}

/** \fn int get_xcord()
 * \brief Get xcord memory variable from current X-machine.
 * \return Value for variable.
 */
int get_xcord()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).xcord;
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).xcord;
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).xcord;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_ycord(int ycord)
 * \brief Set ycord memory variable for current X-machine.
 * \param ycord New value for variable.
 */
void set_ycord(int ycord)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).ycord = ycord;
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).ycord = ycord;
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).ycord = ycord;
}

/** \fn int get_ycord()
 * \brief Get ycord memory variable from current X-machine.
 * \return Value for variable.
 */
int get_ycord()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).ycord;
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).ycord;
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).ycord;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_tcalories(int tcalories)
 * \brief Set tcalories memory variable for current X-machine.
 * \param tcalories New value for variable.
 */
void set_tcalories(int tcalories)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).tcalories = tcalories;
}

/** \fn int get_tcalories()
 * \brief Get tcalories memory variable from current X-machine.
 * \return Value for variable.
 */
int get_tcalories()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).tcalories;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_leaderID(int leaderID)
 * \brief Set leaderID memory variable for current X-machine.
 * \param leaderID New value for variable.
 */
void set_leaderID(int leaderID)
{
	if(current_xmachine->xmachine_clan) (*current_xmachine->xmachine_clan).leaderID = leaderID;
}

/** \fn int get_leaderID()
 * \brief Get leaderID memory variable from current X-machine.
 * \return Value for variable.
 */
int get_leaderID()
{
	if(current_xmachine->xmachine_clan) return (*current_xmachine->xmachine_clan).leaderID;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn members_needs get_mneeds()
 * \brief Get mneeds memory variable from current X-machine.
 * \return Value for variable.
 */
members_needs * get_mneeds()
{
	if(current_xmachine->xmachine_clan) return &(*current_xmachine->xmachine_clan).mneeds;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return NULL;
}

/** \fn void set_pcalories(int pcalories)
 * \brief Set pcalories memory variable for current X-machine.
 * \param pcalories New value for variable.
 */
void set_pcalories(int pcalories)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).pcalories = pcalories;
}

/** \fn int get_pcalories()
 * \brief Get pcalories memory variable from current X-machine.
 * \return Value for variable.
 */
int get_pcalories()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).pcalories;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_repo(float repo)
 * \brief Set repo memory variable for current X-machine.
 * \param repo New value for variable.
 */
void set_repo(float repo)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).repo = repo;
}

/** \fn float get_repo()
 * \brief Get repo memory variable from current X-machine.
 * \return Value for variable.
 */
float get_repo()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).repo;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (float)0;
}

/** \fn void set_tpatch(int tpatch)
 * \brief Set tpatch memory variable for current X-machine.
 * \param tpatch New value for variable.
 */
void set_tpatch(int tpatch)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).tpatch = tpatch;
}

/** \fn int get_tpatch()
 * \brief Get tpatch memory variable from current X-machine.
 * \return Value for variable.
 */
int get_tpatch()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).tpatch;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_repows(float repows)
 * \brief Set repows memory variable for current X-machine.
 * \param repows New value for variable.
 */
void set_repows(float repows)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).repows = repows;
}

/** \fn float get_repows()
 * \brief Get repows memory variable from current X-machine.
 * \return Value for variable.
 */
float get_repows()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).repows;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (float)0;
}

/** \fn void set_repods(float repods)
 * \brief Set repods memory variable for current X-machine.
 * \param repods New value for variable.
 */
void set_repods(float repods)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).repods = repods;
}

/** \fn float get_repods()
 * \brief Get repods memory variable from current X-machine.
 * \return Value for variable.
 */
float get_repods()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).repods;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (float)0;
}

/** \fn void set_season(int season)
 * \brief Set season memory variable for current X-machine.
 * \param season New value for variable.
 */
void set_season(int season)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).season = season;
}

/** \fn int get_season()
 * \brief Get season memory variable from current X-machine.
 * \return Value for variable.
 */
int get_season()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).season;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_adultos(int adultos)
 * \brief Set adultos memory variable for current X-machine.
 * \param adultos New value for variable.
 */
void set_adultos(int adultos)
{
	if(current_xmachine->xmachine_patch) (*current_xmachine->xmachine_patch).adultos = adultos;
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).adultos = adultos;
}

/** \fn int get_adultos()
 * \brief Get adultos memory variable from current X-machine.
 * \return Value for variable.
 */
int get_adultos()
{
	if(current_xmachine->xmachine_patch) return (*current_xmachine->xmachine_patch).adultos;
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).adultos;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_id(int id)
 * \brief Set id memory variable for current X-machine.
 * \param id New value for variable.
 */
void set_id(int id)
{
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).id = id;
}

/** \fn int get_id()
 * \brief Get id memory variable from current X-machine.
 * \return Value for variable.
 */
int get_id()
{
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).id;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_familia(int familia)
 * \brief Set familia memory variable for current X-machine.
 * \param familia New value for variable.
 */
void set_familia(int familia)
{
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).familia = familia;
}

/** \fn int get_familia()
 * \brief Get familia memory variable from current X-machine.
 * \return Value for variable.
 */
int get_familia()
{
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).familia;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_count(int count)
 * \brief Set count memory variable for current X-machine.
 * \param count New value for variable.
 */
void set_count(int count)
{
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).count = count;
}

/** \fn int get_count()
 * \brief Get count memory variable from current X-machine.
 * \return Value for variable.
 */
int get_count()
{
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).count;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}

/** \fn void set_calorias(int calorias)
 * \brief Set calorias memory variable for current X-machine.
 * \param calorias New value for variable.
 */
void set_calorias(int calorias)
{
	if(current_xmachine->xmachine_manada_guanacos) (*current_xmachine->xmachine_manada_guanacos).calorias = calorias;
}

/** \fn int get_calorias()
 * \brief Get calorias memory variable from current X-machine.
 * \return Value for variable.
 */
int get_calorias()
{
	if(current_xmachine->xmachine_manada_guanacos) return (*current_xmachine->xmachine_manada_guanacos).calorias;

    // suppress compiler warning by returning dummy value /
    // this statement should rightfully NEVER be reached /
    return (int)0;
}


/** \fn double agent_get_range()
 * \brief Fixed routine to get the range from current X-machine
  * \return Value of range
  */
double agent_get_range()
{
    double value = 0.0;
    /*if (current_xmachine->xmachine_indv) value = current_xmachine->xmachine_indv->;*/
    /*if (current_xmachine->xmachine_clan) value = current_xmachine->xmachine_clan->;*/
    /*if (current_xmachine->xmachine_patch) value = current_xmachine->xmachine_patch->;*/
    /*if (current_xmachine->xmachine_manada_guanacos) value = current_xmachine->xmachine_manada_guanacos->;*/

    return value;
}

/** \fn int agent_get_id()
 * \brief Fixed routine to get the id for the current X-machine
  * \return Value of agent id
  */
int agent_get_id()
{
    int value = 0;
    /*if (current_xmachine->xmachine_indv) value = current_xmachine->xmachine_indv->;*/
    /*if (current_xmachine->xmachine_clan) value = current_xmachine->xmachine_clan->;*/
    /*if (current_xmachine->xmachine_patch) value = current_xmachine->xmachine_patch->;*/
    /*if (current_xmachine->xmachine_manada_guanacos) value = current_xmachine->xmachine_manada_guanacos->id;*/

    return value;
}

/** \fn double agent_get_x()
 * \brief Fixed routine to get the x coordinate from current X-machine
  * \return Value of x coordinate
  */
double agent_get_x()
{
    double value = 0.0;
    /*if (current_xmachine->xmachine_indv) value = current_xmachine->xmachine_indv->0.0;*/
    /*if (current_xmachine->xmachine_clan) value = current_xmachine->xmachine_clan->0.0;*/
    /*if (current_xmachine->xmachine_patch) value = current_xmachine->xmachine_patch->0.0;*/
    /*if (current_xmachine->xmachine_manada_guanacos) value = current_xmachine->xmachine_manada_guanacos->0.0;*/

    return value;
}
/** \fn double agent_get_y()
 * \brief Fixed routine to get the y coordinate from current X-machine
  * \return Value of y coordinate
  */
double agent_get_y()
{
    double value = 0.0;
    /*if (current_xmachine->xmachine_indv) value = current_xmachine->xmachine_indv->0.0;*/
    /*if (current_xmachine->xmachine_clan) value = current_xmachine->xmachine_clan->0.0;*/
    /*if (current_xmachine->xmachine_patch) value = current_xmachine->xmachine_patch->0.0;*/
    /*if (current_xmachine->xmachine_manada_guanacos) value = current_xmachine->xmachine_manada_guanacos->0.0;*/

    return value;
}
/** \fn double agent_get_z()
 * \brief Fixed routine to get the z coordinate from current X-machine
  * \return Value of z coordinate
  */
double agent_get_z()
{
    double value = 0.0;

    return value;
}

/** \fn void add_node(int node_id, double minx, double maxx, double miny, double maxy, double minz, double maxz)
 * \brief Add a node to the node list.
 * \param node_id The node ID.
 * \param minx The minumum value on the x-axis of the bounding volume.
 * \param maxx The maximum value on the x-axis of the bounding volume.
 * \param miny The minumum value on the y-axis of the bounding volume.
 * \param maxy The maximum value on the y-axis of the bounding volume.
 * \param minz The minumum value on the z-axis of the bounding volume.
 * \param maxz The maximum value on the z-axis of the bounding volume.
 */
void add_node(int node_id, double minx, double maxx, double miny, double maxy, double minz, double maxz)
{
	node_information * current = *p_node_info;
	node_information * tmp = NULL;

	while(current)
	{
		tmp = current;
		current = current->next;
	}

	current = (node_information *)malloc(sizeof(node_information));
		CHECK_POINTER(current);

	if(tmp)
	{
		tmp->next = current;
	}
	else
	{
		*p_node_info = current;
	}

	current->next = NULL;
	current->node_id = node_id;
	current->agents_in_halo = 0;
	current->agent_total = 0;
	current->agents = NULL;
	current->information_messages = NULL;
	current->indgetcalories_messages = NULL;
	current->leader_messages = NULL;
	current->clan_info_messages = NULL;
	current->clangetcalories_messages = NULL;
	current->adultospatch_messages = NULL;
	current->reproduccionguanacos_messages = NULL;


	current->partition_data[0] = minx;
	current->partition_data[1] = maxx;
	current->partition_data[2] = miny;
	current->partition_data[3] = maxy;
	current->partition_data[4] = minz;
	current->partition_data[5] = maxz;
}

/**\fn void free_node_info()
 * \brief Free the node list.
 */
void free_node_info()
{
	node_information * tmp, * head;
	head = *p_node_info;

	while(head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}

	*p_node_info = NULL;
}

/** \fn void clean_up(int code)
 * \brief Add a node to the node list.
 * \param code The error code (zero is no error).
 */
void clean_up(int code)
{
    int rc;
	FILE *file;
	char data[100];

	free(current_xmachine);
	/* Free x-machine memory */
	freexmachines();
	/* Free space partitions linked list */
	free_node_info();
	/* Free output list */
	free_FLAME_outputs(&FLAME_outputs);
	/* Free agent states */
	free_indv_states();
	free_clan_states();
	free_patch_states();
	free_manada_guanacos_states();


	/* Free index maps */


	/* Free message boards */

	rc = MB_Delete(&b_information);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'information' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'information' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'information' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif

	rc = MB_Delete(&b_indgetcalories);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'indgetcalories' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'indgetcalories' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'indgetcalories' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif

	rc = MB_Delete(&b_leader);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'leader' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'leader' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'leader' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif

	rc = MB_Delete(&b_clan_info);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'clan_info' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clan_info' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clan_info' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif

	rc = MB_Delete(&b_clangetcalories);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'clangetcalories' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clangetcalories' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clangetcalories' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif

	rc = MB_Delete(&b_adultospatch);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'adultospatch' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'adultospatch' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'adultospatch' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif

	rc = MB_Delete(&b_reproduccionguanacos);
	#ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not delete 'reproduccionguanacos' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'reproduccionguanacos' board has not been created?\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'reproduccionguanacos' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_Delete returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif


    rc = MB_Env_Finalise();
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not finalise MB environment\n");
       switch(rc) {
           case MB_ERR_ENV:
               fprintf(stderr, "\t reason: MB environment not yet started?\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Env_Finalise returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }

	       
       	   exit(rc);
    }
    #endif



	/* Write log file */
	sprintf(data, "%slog.xml", outputpath);
	file = fopen(data, "a");
	fputs("<!-- <totaltime> unit: seconds -->\n", file);
	fputs("<totaltime>", file);
	sprintf(data, "%.3f", total_time);
	fputs(data, file);
	fputs("</totaltime>\n", file);
	/*fputs("<totalmessages>", file);
	sprintf(data, "%i", total_messages);
	fputs(data, file);
	fputs("</totalmessages>", file);*/
	fputs("</model_run>", file);
	fclose(file);


	if(code != 0)
	{
		printf("*** Error: ");
		if(code == 100) printf("cannot handle specified number of space partitions");
		if(code == 101) printf("could not find number of space partitions config in file");

		printf(" ***");
		exit(0);
	}
}


/** \fn void propagate_agents()
 * \brief Check agent positions to see if any need to be moved to a another node.
 */
void propagate_agents()
{
/*	node_information * node_info;
	xmachine * before_xmachine, * temp_xmachine;
	xmachine ** p_temp_xmachine;
	double x_xmachine, y_xmachine, z_xmachine;
	current_xmachine = *p_xmachine;
	before_xmachine = NULL;
	while(current_xmachine)
	{
		if(current_xmachine->xmachine_indv != NULL)
		{
			x_xmachine = current_xmachine->xmachine_indv->0.0;
			y_xmachine = current_xmachine->xmachine_indv->0.0;
			z_xmachine = 0.0;
		}
		else if(current_xmachine->xmachine_clan != NULL)
		{
			x_xmachine = current_xmachine->xmachine_clan->0.0;
			y_xmachine = current_xmachine->xmachine_clan->0.0;
			z_xmachine = 0.0;
		}
		else if(current_xmachine->xmachine_patch != NULL)
		{
			x_xmachine = current_xmachine->xmachine_patch->0.0;
			y_xmachine = current_xmachine->xmachine_patch->0.0;
			z_xmachine = 0.0;
		}
		else if(current_xmachine->xmachine_manada_guanacos != NULL)
		{
			x_xmachine = current_xmachine->xmachine_manada_guanacos->0.0;
			y_xmachine = current_xmachine->xmachine_manada_guanacos->0.0;
			z_xmachine = 0.0;
		}

		if(x_xmachine < current_node->partition_data[0] ||
		   x_xmachine > current_node->partition_data[1] ||
		   y_xmachine < current_node->partition_data[2] ||
		   y_xmachine > current_node->partition_data[3] ||
		   z_xmachine < current_node->partition_data[4] ||
		   z_xmachine > current_node->partition_data[5])
		{
			node_info = *p_node_info;
			while(node_info)
			{
				if(node_info->node_id != current_node->node_id &&
				node_info->partition_data[0] < x_xmachine && node_info->partition_data[1] > x_xmachine &&
				node_info->partition_data[2] < y_xmachine && node_info->partition_data[3] > y_xmachine &&
				node_info->partition_data[4] < z_xmachine && node_info->partition_data[5] > z_xmachine)
				{
                    // Remove agent
                    if(before_xmachine) before_xmachine->next = current_xmachine->next;
                    else *p_xmachine = current_xmachine->next;
                    current_node->agent_total--;
                    // Add agent
                    p_temp_xmachine = &node_info->agents;
                    temp_xmachine = *p_temp_xmachine;
                    current_xmachine->next = temp_xmachine;
                    *p_temp_xmachine = current_xmachine;
                    node_info->agent_total++;
                    node_info = NULL;
				}
				else node_info = node_info->next;
				}
			}
			else before_xmachine = current_xmachine;

			if(before_xmachine) current_xmachine = before_xmachine->next;
			else current_xmachine = NULL;
		}*/
}


/** \fn int_array * init_int_array()
 * \brief Allocate memory for a dynamic integer array.
 * \return int_array Pointer to the new dynamic integer array.
 */
void init_int_array(int_array * array)
{
	(*array).size = 0;
	(*array).total_size = ARRAY_BLOCK_SIZE;
	(*array).array = (int *)malloc(ARRAY_BLOCK_SIZE * sizeof(int));
	CHECK_POINTER((*array).array);
}

/** \fn void reset_int_array(int_array * array)
* \brief Reset the int array to hold nothing.
* \param array Pointer to the dynamic integer array.
*/
void reset_int_array(int_array * array)
{
	(*array).size = 0;
}

/** \fn void free_int_array(int_array * array)
* \brief Free the memory of a dynamic integer array.
* \param array Pointer to the dynamic integer array.
*/
void free_int_array(int_array * array)
{
	free((*array).array);
}

void copy_int_array(int_array * from, int_array * to)
{
	int i;
	//to = init_int_array();

	for (i = 0; i < (*from).size; i++)
	{
		add_int(to, (*from).array[i]);
	}
}

/** \fn void sort_int_array(int_array * array)
* \brief Sort the elements of a dynamic integer array with smallest first.
* \param array Pointer to the dynamic integer array.
*/
/*void sort_int_array(int_array * array)
{
	int i, j, temp;

	for(i=0; i<((*array).size-1); i++)
	{
		for(j=0; j<((*array).size-1)-i; j++)
		{
			if(*((*array).array+j+1) < *((*array).array+j))
			{
                temp = *((*array).(*array)+j);
                *((*array).array+j) = *((*array).array+j+1);
                *((*array).array+j+1) = temp;
			}
		}
	}
}*/

/** \fn int quicksort_int(int *array, int elements)
 *  \brief Sorts the elements of the integer array in ascending order.
 *  \param Pointer to integer array
 *  \param Number of elements that must be sorted
 *  \return integer value indicating success(0) or failure(1)
 */
/*int quicksort_int(int array, int elements)
{
	#define  LEVEL  1000
	int  pivot, begin[LEVEL], end[LEVEL], i=0, left, right ;
	begin[0]=0; end[0]=elements;
	while (i>=0)
	{
		left=begin[i]; right=end[i]-1;
		if (left<right)
		{
			pivot=array[left]; if (i==LEVEL-1) return 1;
			while (left<right)
			{
				while (array[right]>=pivot && left<right) right--;
				if (left<right) array[left++]=array[right];
				while (array[left]<=pivot && left<right) left++;
				if (left<right) array[right--]=array[left];
			}
			array[left]=pivot;
			begin[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	    else
	    {
	      i--;
	    }
	}
	return 0;
}*/

/** \fn void add_int(int_array * array, int new_int)
* \brief Add an integer to the dynamic integer array.
* \param array Pointer to the dynamic integer array.
* \param new_int The integer to add
*/
void add_int(int_array * array, int new_int)
{
	if((*array).size == (*array).total_size)
	{
		(*array).total_size = (int)((*array).total_size * ARRAY_GROWTH_RATE);
		(*array).array = (int *)realloc((*array).array, ((*array).total_size * sizeof(int)));
	}
	(*array).array[(*array).size] = new_int;
	(*array).size++;
}

/** \fn void remove_int(int_array * array, int index)
 * \brief Remove an integer from a dynamic integer array.
 * \param array Pointer to the dynamic integer array.
 * \param index The index of the integer to remove.
 */
void remove_int(int_array * array, int index)
{
	int i;

	if(index < (*array).size)
	{
		/* memcopy?? */
		for(i = index; i < (*array).size - 1; i++)
		{
			(*array).array[i] = (*array).array[i+1];
		}
		(*array).size--;
	}
}

/** \fn void print_int_array(int_array * array)
 * \brief Print the elements of a dynamic integer array.
 * \param array Pointer to the dynamic integer array.
 */
void print_int_array(int_array * array)
{
	int i;

	for(i=0; i<(*array).size; i++)
	{
		printf("%d> %d", i, (*array).array[i]);
	}
}

/** \fn float_array * init_float_array()
 * \brief Allocate memory for a dynamic float array.
 * \return float_array Pointer to the new dynamic float array.
 */
void init_float_array(float_array * array)
{
	(*array).size = 0;
	(*array).total_size = ARRAY_BLOCK_SIZE;
	(*array).array = (float *)malloc(ARRAY_BLOCK_SIZE * sizeof(float));
	CHECK_POINTER((*array).array);
}

/** \fn void reset_float_array(float_array * array)
* \brief Reset the float array to hold nothing.
* \param array Pointer to the dynamic float array.
*/
void reset_float_array(float_array * array)
{
	(*array).size = 0;
}

/** \fn void free_float_array(float_array * array)
* \brief Free the memory of a dynamic float array.
* \param array Pointer to the dynamic float array.
*/
void free_float_array(float_array * array)
{
	free((*array).array);
}

void copy_float_array(float_array * from, float_array * to)
{
	int i;
	//to = init_float_array();

	for (i = 0; i < (*from).size; i++)
	{
		add_float(to, (*from).array[i]);
	}
}

/** \fn void sort_float_array(float_array * array)
* \brief Sort the elements of a dynamic float array with smallest first.
* \param array Pointer to the dynamic float array.
*/
/*void sort_float_array(float_array array)
{
	int i, j;
	float temp;
	// Using bubble sorts nested loops //
	for(i=0; i<(array.size-1); i++)
	{
		for(j=0; j<(array.size-1)-i; j++)
		{
			// Comparing the values between neighbours //
			if(*(array.array+j+1) < *(array.array+j))
			{
                // Swap neighbours //
                temp = *(array.array+j);
                *(array.array+j) = *(array.array+j+1);
                *(array.array+j+1) = temp;
			}
		}
	}
}*/

/** \fn int quicksort_float(float *array, int elements)
 *  \brief Sorts the elements of the float array in ascending order.
 *  \param Pointer to float array
 *  \param Number of elements that must be sorted
 *  \return integer value indicating success(0) or failure(1)
 */
/*int quicksort_float(float array, int elements)
{
	#define  LEVEL  1000
	int i=0, left, right ;
	float pivot, begin[LEVEL], end[LEVEL];
	begin[0]=0; end[0]=elements;
	while (i>=0)
	{
		left=begin[i]; right=end[i]-1;
		if (left<right)
		{
			pivot=array[left]; if (i==LEVEL-1) return 1;
			while (left<right)
			{
				while (array[right]>=pivot && left<right) right--;
				if (left<right) array[left++]=array[right];
				while (array[left]<=pivot && left<right) left++;
				if (left<right) array[right--]=array[left];
			}
			array[left]=pivot;
			begin[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	    else
	    {
	      i--;
	    }
	}
	return 0;
}*/

/** \fn void add_float(float_array * array, float new_float)
* \brief Add an floateger to the dynamic float array.
* \param array Pointer to the dynamic float array.
* \param new_float The float to add
*/
void add_float(float_array * array, float new_float)
{
	if((*array).size == (*array).total_size)
	{
		(*array).total_size = (int)((*array).total_size * ARRAY_GROWTH_RATE);
		(*array).array = (float *)realloc((*array).array, ((*array).total_size * sizeof(float)));
	}
	(*array).array[(*array).size] = new_float;
	(*array).size++;
}

/** \fn void remove_float(float_array * array, int index)
 * \brief Remove an floateger from a dynamic float array.
 * \param array Pointer to the dynamic float array.
 * \param index The index of the float to remove.
 */
void remove_float(float_array * array, int index)
{
	int i;

	if(index < (*array).size)
	{
		/* memcopy?? */
		for(i = index; i < (*array).size - 1; i++)
		{
			(*array).array[i] = (*array).array[i+1];
		}
		(*array).size--;
	}
}

/** \fn void print_float_array(float_array * array)
 * \brief Print the elements of a dynamic float array.
 * \param array Pointer to the dynamic float array.
 */
void print_float_array(float_array * array)
{
	int i;
	/* printf(""); // compiler does not like empty prfloats */
	for(i=0; i<(*array).size; i++)
	{
		printf("%d> %f", i, (*array).array[i]);
	}
}

/** \fn double_array * init_double_array()
 * \brief Allocate memory for a dynamic double array.
 * \return double_array Pointer to the new dynamic double array.
 */
void init_double_array(double_array * array)
{
	(*array).size = 0;
	(*array).total_size = ARRAY_BLOCK_SIZE;
	(*array).array = (double *)malloc(ARRAY_BLOCK_SIZE * sizeof(double));
	CHECK_POINTER((*array).array);
}

/** \fn void reset_double_array(double_array * array)
* \brief Reset the double array to hold nothing.
* \param array Pointer to the dynamic double array.
*/
void reset_double_array(double_array * array)
{
	(*array).size = 0;
}

/** \fn void free_double_array(double_array * array)
 * \brief Free the memory of a dynamic double array.
 * \param array Pointer to the dynamic double array.
 */
void free_double_array(double_array * array)
{
	free((*array).array);
}

void copy_double_array(double_array * from, double_array * to)
{
	int i;
	//to = init_double_array();

	for (i = 0; i < (*from).size; i++)
	{
		add_double(to, (*from).array[i]);
	}
}

/** \fn void sort_double_array(double_array * array)
 * \brief Sort the elements of a dynamic double array with smallest first.
 * \param array Pointer to the dynamic double array.
 */
/*void sort_double_array(double_array array)
{
	int i, j;
	double temp;

	// Using bubble sorts nested loops //
	for(i=0; i<(array.size-1); i++)
	{
		for(j=0; j<(array.size-1)-i; j++)
		{
			// Comparing the values between neighbours //
			if(*(array.array+j+1) < *(array.array+j))
			{
                // Swap neighbours //
                temp = *(array.array+j);
                *(array.array+j) = *(array.array+j+1);
                *(array.array+j+1) = temp;
			}
		}
	}
}*/

/** \fn int quicksort_double(double *array, int elements)
 *  \brief Sorts the elements of the double array in ascending order.
 *  \param Pointer to double array
 *  \param Number of elements that must be sorted
 *  \return integer value indicating success(0) or failure(1)
 */
/*int quicksort_double(double array, int elements)
{
	#define  LEVEL  1000
	double pivot, begin[LEVEL], end[LEVEL];
	int  i=0, left, right ;
	begin[0]=0; end[0]=elements;
	while (i>=0)
	{
		left=begin[i]; right=end[i]-1;
		if (left<right)
		{
			pivot=array[left]; if (i==LEVEL-1) return 1;
			while (left<right)
			{
				while (array[right]>=pivot && left<right) right--;
				if (left<right) array[left++]=array[right];
				while (array[left]<=pivot && left<right) left++;
				if (left<right) array[right--]=array[left];
			}
			array[left]=pivot;
			begin[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	    else
	    {
	      i--;
	    }
	}
	return 0;
}*/

/** \fn void add_double(double_array * array, double new_double)
 * \brief Add an double to the dynamic double array.
 * \param array Pointer to the dynamic double array.
 * \param new_double The double to add
 */
void add_double(double_array * array, double new_double)
{
	if((*array).size == (*array).total_size)
	{
		(*array).total_size = (int)((*array).total_size * ARRAY_GROWTH_RATE);
		(*array).array = (double *)realloc((*array).array, ((*array).total_size * sizeof(double)));
	}
	(*array).array[(*array).size] = new_double;
	(*array).size++;
}

/** \fn void remove_double(double_array * array, int index)
 * \brief Remove an double from a dynamic double array.
 * \param array Pointer to the dynamic double array.
 * \param index The index of the double to remove.
 */
void remove_double(double_array * array, int index)
{
	int i;
	if(index < (*array).size)
	{
		/* memcopy?? */
		for(i = index; i < (*array).size - 1; i++)
		{
			(*array).array[i] = (*array).array[i+1];
		}
		(*array).size--;
	}
}

/** \fn void print_double_array(double_array * array)
 * \brief Print the elements of a dynamic double array.
 * \param array Pointer to the dynamic double array.
 */
void print_double_array(double_array * array)
{
	int i;

	for(i=0; i<(*array).size; i++)
	{
		printf("%d> %f", i, (*array).array[i]);
	}
}

/** \fn char_array * init_char_array()
 * \brief Allocate memory for a dynamic char array.
 * \return char_array Pointer to the new dynamic char array.
 */
void init_char_array(char_array * array)
{
	(*array).size = 0;
	(*array).total_size = ARRAY_BLOCK_SIZE;
	(*array).array = (char *)malloc(ARRAY_BLOCK_SIZE * sizeof(char));
	CHECK_POINTER((*array).array);
	(*array).array[0] = '\0';
}

/** \fn void reset_char_array(char_array * array)
* \brief Reset the char array to hold nothing.
* \param array Pointer to the dynamic char array.
*/
void reset_char_array(char_array * array)
{
	(*array).size = 0;
}

/** \fn void free_char_array(char_array * array)
 * \brief Free the memory of a dynamic char array.
 * \param array Pointer to the dynamic char array.
 */
void free_char_array(char_array * array)
{
	free((*array).array);
}

void copy_char_array(char_array * from, char_array * to)
{
	int i;

	for (i = 0; i < (*from).size; i++)
	{
		add_char(to, (*from).array[i]);
	}
}

/** \fn void add_char(char_array * array, char new_char)
 * \brief Add an char to the dynamic char array.
 * \param array Pointer to the dynamic char array.
 * \param new_char The char to add
 */
void add_char(char_array * array, char new_char)
{
	if((*array).size + 1 == (*array).total_size)
	{
		(*array).total_size = (int)((*array).total_size * ARRAY_GROWTH_RATE);
		(*array).array = (char *)realloc((*array).array, ((*array).total_size * sizeof(char)));
	}
	(*array).array[(*array).size] = new_char;
	(*array).array[(*array).size + 1] = '\0';
	(*array).size++;
}

/** \fn void remove_char(char_array * array, int index)
 * \brief Remove an char from a dynamic char array.
 * \param array Pointer to the dynamic char array.
 * \param index The index of the char to remove.
 */
void remove_char(char_array * array, int index)
{
	int i;
	if(index < (*array).size)
	{
		/* memcopy?? */
		for(i = index; i < (*array).size - 1; i++)
		{
			(*array).array[i] = (*array).array[i+1];
		}
		(*array).size--;
	}
}

/** \fn char * copy_array_to_str(char_array * array)
 * \brief Return pointer to string from a char_array.
 * \param array Pointer to the dynamic integer array.
 * \return char Pointer to the new string.
 */
char * copy_array_to_str(char_array * array)
{
	char * new_string = (char *)malloc( ((*array).size + 1) * sizeof(char));
	CHECK_POINTER(new_string);
	return strcpy(new_string, (*array).array);
}

/** \fn void print_char_array(char_array * array)
 * \brief Print the elements of a dynamic char array.
 * \param array Pointer to the dynamic char array.
 */
void print_char_array(char_array * array)
{
	printf("%s", (*array).array);
}

/* Functions for the members_needs datatype */
/** \fn members_needs_array * init_members_needs_array()
 * \brief Allocate memory for a dynamic members_needs array.
 * \return members_needs_array Pointer to the new dynamic members_needs array.
 */
void init_members_needs_array(members_needs_array * array)
{
	(*array).size = 0;
	(*array).total_size = ARRAY_BLOCK_SIZE;
	(*array).array = (members_needs *)malloc(ARRAY_BLOCK_SIZE * sizeof(members_needs));
	CHECK_POINTER((*array).array);
}

/** \fn void reset_members_needs_array(members_needs_array* array)
* \brief Reset the members_needs array to hold nothing.
* \param array Pointer to the dynamic members_needs array.
*/
void reset_members_needs_array(members_needs_array * array)
{
	(*array).size = 0;
}

/** \fn void free_members_needs_array(members_needs_array * array)
* \brief Free the memory of a dynamic members_needs array.
* \param array Pointer to the dynamic members_needs array.
*/
void free_members_needs_array(members_needs_array * array)
{
	int i;
	
	for(i = 0; i < array->size; i++)
	{
		free_members_needs(&(*array).array[i]);
	}
	
	free((*array).array);
}

void copy_members_needs_array(members_needs_array * from, members_needs_array * to)
{
	int i;

	//to = init_members_needs_array();

	for(i = 0; i < (*from).size; i++)
	{
		add_members_needs(to, (*from).array[i].id_list, (*from).array[i].cal_list, (*from).array[i].age);
	}
}

/** \fn void add_members_needs(members_needs_array * array, int id_list, int cal_list, int age)
* \brief Add an members_needs to the dynamic members_needs array.
* \param array Pointer to the dynamic members_needs array.
* \param new_int The members_needs to add
*/
void add_members_needs(members_needs_array * array, /*@out@*/ int * id_list, /*@out@*/ int * cal_list, /*@out@*/ int * age)
{
	if((*array).size == (*array).total_size)
	{
		(*array).total_size = (int)((*array).total_size * ARRAY_GROWTH_RATE);
		(*array).array = (members_needs *)realloc((*array).array, ((*array).total_size * sizeof(members_needs)));
	}
	init_members_needs(&(*array).array[(*array).size]);
	if(id_list != NULL) memcpy((*array).array[(*array).size].id_list, id_list, 100*sizeof(int));
	if(cal_list != NULL) memcpy((*array).array[(*array).size].cal_list, cal_list, 100*sizeof(int));
	if(age != NULL) memcpy((*array).array[(*array).size].age, age, 100*sizeof(int));

	(*array).size++;
}

/** \fn void remove_members_needs(members_needs_array * array, int index)
 * \brief Remove an members_needs from a dynamic members_needs array.
 * \param array Pointer to the dynamic members_needs array.
 * \param index The index of the members_needs to remove.
 */
void remove_members_needs(members_needs_array * array, int index)
{
	int i;

	/* Free element at index index */
	free_members_needs(&(*array).array[index]);

	/* Copy all elements up by one */
	if(index < (*array).size)
	{
		for(i = index; i < (*array).size - 1; i++)
		{
			copy_members_needs(&(*array).array[i+1], &(*array).array[i]);
		}
		(*array).size--;
	}
}

/** \fn int idle()
 * \brief an idle function for use by agents.
 */
int idle()
{
	return 0;
}

int FLAME_get_environment_variable_max_manada()
{
	return FLAME_environment_variable_max_manada;
}
int FLAME_get_environment_variable_max_familia()
{
	return FLAME_environment_variable_max_familia;
}
int FLAME_get_environment_variable_cal_adulto()
{
	return FLAME_environment_variable_cal_adulto;
}


