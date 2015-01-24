/**
 * \file  main.c
 * \brief Holds main function of the program.
 */

#include "header.h"
#define COMPACT_PRINTOUT_P_THRESHOLD 8

/** \fn int main(int argc, char * argv[])
 * \brief Main program loop.
 * \param argc Argument count.
 * \param argv Pointer Pointer to Argument vector.
 */
int main(int argc, char * argv[])
{
	/* Timing variables */
	double start, stop, interval;
	FILE *file;
	char data[100];
	char logfilepath[1000];
	char inputpath[1000];
	char * c;
	int lastd = 0;
	int i;
	int rc;
	int iteration_number = 0;
	int iteration_total;
	int * p_iteration_number = &iteration_number;
	//xmachine_memory_indv * temp_xmachine_indv;
	//xmachine_memory_clan * temp_xmachine_clan;
	//xmachine_memory_patch * temp_xmachine_patch;
	//xmachine_memory_manada_guanacos * temp_xmachine_manada_guanacos;

	int FLAME_information_message_board_write;
	int FLAME_information_message_board_read;
	int FLAME_indgetcalories_message_board_write;
	int FLAME_indgetcalories_message_board_read;
	int FLAME_leader_message_board_write;
	int FLAME_leader_message_board_read;
	int FLAME_ancestor_message_board_write;
	int FLAME_ancestor_message_board_read;
	int FLAME_peticionID_message_board_write;
	int FLAME_peticionID_message_board_read;
	int FLAME_family_message_board_write;
	int FLAME_family_message_board_read;
	int FLAME_death_message_board_write;
	int FLAME_death_message_board_read;
	int FLAME_widow_message_board_write;
	int FLAME_widow_message_board_read;
	int FLAME_informationDivide_message_board_write;
	int FLAME_informationDivide_message_board_read;
	int FLAME_clan_info_message_board_write;
	int FLAME_clan_info_message_board_read;
	int FLAME_clangetcalories_message_board_write;
	int FLAME_clangetcalories_message_board_read;
	int FLAME_freeGirls_message_board_write;
	int FLAME_freeGirls_message_board_read;
	MBt_SearchTree tree_ptr_2d_freeGirls;
	int FLAME_propuesta_message_board_write;
	int FLAME_propuesta_message_board_read;
	int FLAME_confirProp_message_board_write;
	int FLAME_confirProp_message_board_read;
	int FLAME_marriage_message_board_write;
	int FLAME_marriage_message_board_read;
	int FLAME_respuestaID_message_board_write;
	int FLAME_respuestaID_message_board_read;
	int FLAME_lmarriage_message_board_write;
	int FLAME_lmarriage_message_board_read;
	int FLAME_warningDivide_message_board_write;
	int FLAME_warningDivide_message_board_read;
	int FLAME_clanspatch_message_board_write;
	int FLAME_clanspatch_message_board_read;
	MBt_SearchTree tree_ptr_2d_clanspatch;
	int FLAME_adultospatch_message_board_write;
	int FLAME_adultospatch_message_board_read;
	int FLAME_reproduccionguanacos_message_board_write;
	int FLAME_reproduccionguanacos_message_board_read;

	/* Particle cloud data */
	double cloud_data[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
	/* Count to debug function branches */
	int FLAME_debug_count;

/* For partition method. Makes geometric (-g flag) the default but may be overridden with -r for round-robin */
	int partition_method=1;



	/* Output frequency is 1 as default */
	output_frequency = 1;
	/* Set random seed */
	srand(time(NULL));

	

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
    
	/* For backwards compatabilty allocate current_xmachine */
	current_xmachine = (xmachine *)malloc(sizeof(xmachine));
	if(current_xmachine == NULL) {printf("**** ERROR in Memory check current_xmachine\n");exit(EXIT_FAILURE);}
	/*CHECK_POINTER(current_xmachine);*/

	/* Initialise pointers */
	initialise_pointers();


	printf("FLAME Application: GlobalDefs \n");


	printf("Debug mode enabled \n");
FLAME_debug_count = 0;
/* Use to stop compiler warnings if not used */
if(FLAME_debug_count == 0) {}




if(argc < 2)
	{

		printf("Usage: %s <number of iterations> [<states_directory>]/<init_state> <partitions> [-f # | -f #+#]\n",argv[0]);
		printf("\t-f\tOutput frequency, 1st # is frequency, 2nd # is the offset if required\n");



		exit(0);
	}
	iteration_total = atoi(argv[1]);
printf("Iterations: %i\n", iteration_total);

	/* Read initial states of x-machines */
	if(argc < 3)
	{
		printf("Need two parameters\n");
		exit(0);
	}
	strcpy(inputpath, argv[2]);
/*printf("Initial states: %s\n", inputpath);*/

	i = 0;
	lastd = -1;
	while(inputpath[i] != '\0')
	{
		/* For windows directories */
		if(inputpath[i] == '\\') lastd=i;
		/* For unix directories */
		if(inputpath[i] == '/') lastd=i;
		i++;
	}
	strcpy(outputpath, inputpath);
	outputpath[lastd+1] = '\0';

/*printf("Ouput dir: %s\n", outputpath);*/


	/* Read number of space partitions (1 by default) */
	totalnodes = 1;
	if(argc > 3)
	{
		totalnodes = atoi(argv[3]);
	}


	i = 3;
	while(argc > i)
	{
		if(strcmp(argv[i],"-f") == 0)
		{
			if(argc > (i+1))
			{
				output_offset = 0;
				/* Find offset, separated by the char '+' */
				c = strchr(argv[(i+1)], '+');
				if(c == NULL)
				{
					output_frequency = atoi(argv[(i+1)]);
					printf("Using output frequency of: %d\n", output_frequency);
				}
				else
				{
					output_offset = atoi(argv[(i+1)]+(c-argv[(i+1)])+1);
					argv[(i+1)][c-argv[(i+1)]] = '\0';
					output_frequency = atoi(argv[(i+1)]);
					printf("Using output frequency of: %d with offset %d\n", output_frequency, output_offset);
				}

				if(output_frequency == 0)
				{
					printf("Output frequency cannot be zero\n");
					exit(0);
				}

				i++;
			}
			else
			{
				printf("Output frequency number not defined\n");
				exit(0);
			}
		}
		/* Partitioning method: -g = geometric, -r = round-robin */
		if(strcmp(argv[i],"-g") == 0) partition_method = 1;
		if(strcmp(argv[i],"-r") == 0) partition_method = 2;
		i++;
	}


	    /* Read initial data into p_xmachine  */

       //agent_list = p_xmachine;
       readinitialstates(inputpath, outputpath, p_iteration_number, cloud_data, partition_method, 0);
       /* Generate partitions */
       generate_partitions(cloud_data,totalnodes,partition_method);
       save_partition_data();





    /* Partition data */
    /* stc: no partitions in serial */
	//partition_data(totalnodes, agent_list, cloud_data, partition_method);



/* Use MB_IndexMap routines from libmboard v0.2 */
/* For each agent constant (that is used in a filter(?))
 * declare an index map handle */



		/*i = 0;
		current_node = *p_node_info;
		while(current_node)
		{
			printf("No of agents on partition %d: %d\n", current_node->node_id, current_node->agent_total);
			i += current_node->agent_total;
			current_node = current_node->next;
		}
		printf("Agent total check: %d\n", i);*/

        /* restore current_node pointer */
		//current_node = *p_node_info;



	/* Start log file (now so that xvisualiser can read straight away) */

	/* Write log file */
	sprintf(logfilepath, "%slog.xml", outputpath);
	if((file = fopen(logfilepath, "w"))==NULL)
	{
		printf("Error: cannot open file '%s' for writing\n", logfilepath);
		exit(0);
	}
	(void)fputs("<model_run>\n", file);
	(void)fputs("<codetype>", file);
	(void)fputs("serial", file);

	(void)fputs("</codetype>\n", file);
	(void)fputs("<nodes>", file);
	sprintf(data, "%i", totalnodes);
	(void)fputs(data, file);
	(void)fputs("</nodes>\n", file);

	/* print timer into */
	(void)fputs("<!-- <time> unit: milliseconds -->\n", file);

	sprintf(data, "unspecified");
	
	(void)fputs("<!-- <time> timer resolution: ", file);
	(void)fputs(data, file);
	(void)fputs(")-->\n", file);

	start = get_time();
	stop = get_time();
	sprintf(data, "%.2e ms", (stop - start) * 1000.0);
	(void)fputs("<!-- <time> timer overhead: ~", file);
	(void)fputs(data, file);
	(void)fputs(")-->\n", file);


	(void)fclose(file);


	/* For each message check if their exists agents that input/output the message */
	FLAME_information_message_board_write = 0;
	FLAME_information_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_information_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_information_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_information_message_board_write == 0 &&
		FLAME_information_message_board_read == 0)
			rc = MB_SetAccessMode(b_information, MB_MODE_IDLE);
	if(FLAME_information_message_board_write == 1 &&
		FLAME_information_message_board_read == 0)
			rc = MB_SetAccessMode(b_information, MB_MODE_WRITEONLY);
	if(FLAME_information_message_board_write == 0 &&
		FLAME_information_message_board_read == 1)
			rc = MB_SetAccessMode(b_information, MB_MODE_READONLY);
	if(FLAME_information_message_board_write == 1 &&
		FLAME_information_message_board_read == 1)
			rc = MB_SetAccessMode(b_information, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'information' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_indgetcalories_message_board_write = 0;
	FLAME_indgetcalories_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_indgetcalories_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_indgetcalories_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_indgetcalories_message_board_write == 0 &&
		FLAME_indgetcalories_message_board_read == 0)
			rc = MB_SetAccessMode(b_indgetcalories, MB_MODE_IDLE);
	if(FLAME_indgetcalories_message_board_write == 1 &&
		FLAME_indgetcalories_message_board_read == 0)
			rc = MB_SetAccessMode(b_indgetcalories, MB_MODE_WRITEONLY);
	if(FLAME_indgetcalories_message_board_write == 0 &&
		FLAME_indgetcalories_message_board_read == 1)
			rc = MB_SetAccessMode(b_indgetcalories, MB_MODE_READONLY);
	if(FLAME_indgetcalories_message_board_write == 1 &&
		FLAME_indgetcalories_message_board_read == 1)
			rc = MB_SetAccessMode(b_indgetcalories, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'indgetcalories' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_leader_message_board_write = 0;
	FLAME_leader_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_leader_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_leader_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_leader_message_board_write == 0 &&
		FLAME_leader_message_board_read == 0)
			rc = MB_SetAccessMode(b_leader, MB_MODE_IDLE);
	if(FLAME_leader_message_board_write == 1 &&
		FLAME_leader_message_board_read == 0)
			rc = MB_SetAccessMode(b_leader, MB_MODE_WRITEONLY);
	if(FLAME_leader_message_board_write == 0 &&
		FLAME_leader_message_board_read == 1)
			rc = MB_SetAccessMode(b_leader, MB_MODE_READONLY);
	if(FLAME_leader_message_board_write == 1 &&
		FLAME_leader_message_board_read == 1)
			rc = MB_SetAccessMode(b_leader, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'leader' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_ancestor_message_board_write = 0;
	FLAME_ancestor_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_ancestor_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_ancestor_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_ancestor_message_board_write == 0 &&
		FLAME_ancestor_message_board_read == 0)
			rc = MB_SetAccessMode(b_ancestor, MB_MODE_IDLE);
	if(FLAME_ancestor_message_board_write == 1 &&
		FLAME_ancestor_message_board_read == 0)
			rc = MB_SetAccessMode(b_ancestor, MB_MODE_WRITEONLY);
	if(FLAME_ancestor_message_board_write == 0 &&
		FLAME_ancestor_message_board_read == 1)
			rc = MB_SetAccessMode(b_ancestor, MB_MODE_READONLY);
	if(FLAME_ancestor_message_board_write == 1 &&
		FLAME_ancestor_message_board_read == 1)
			rc = MB_SetAccessMode(b_ancestor, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'ancestor' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'ancestor' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_peticionID_message_board_write = 0;
	FLAME_peticionID_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_peticionID_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_peticionID_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_peticionID_message_board_write == 0 &&
		FLAME_peticionID_message_board_read == 0)
			rc = MB_SetAccessMode(b_peticionID, MB_MODE_IDLE);
	if(FLAME_peticionID_message_board_write == 1 &&
		FLAME_peticionID_message_board_read == 0)
			rc = MB_SetAccessMode(b_peticionID, MB_MODE_WRITEONLY);
	if(FLAME_peticionID_message_board_write == 0 &&
		FLAME_peticionID_message_board_read == 1)
			rc = MB_SetAccessMode(b_peticionID, MB_MODE_READONLY);
	if(FLAME_peticionID_message_board_write == 1 &&
		FLAME_peticionID_message_board_read == 1)
			rc = MB_SetAccessMode(b_peticionID, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'peticionID' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'peticionID' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_family_message_board_write = 0;
	FLAME_family_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_family_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_family_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_family_message_board_write == 0 &&
		FLAME_family_message_board_read == 0)
			rc = MB_SetAccessMode(b_family, MB_MODE_IDLE);
	if(FLAME_family_message_board_write == 1 &&
		FLAME_family_message_board_read == 0)
			rc = MB_SetAccessMode(b_family, MB_MODE_WRITEONLY);
	if(FLAME_family_message_board_write == 0 &&
		FLAME_family_message_board_read == 1)
			rc = MB_SetAccessMode(b_family, MB_MODE_READONLY);
	if(FLAME_family_message_board_write == 1 &&
		FLAME_family_message_board_read == 1)
			rc = MB_SetAccessMode(b_family, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'family' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'family' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'family' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_death_message_board_write = 0;
	FLAME_death_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_death_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_death_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_death_message_board_write == 0 &&
		FLAME_death_message_board_read == 0)
			rc = MB_SetAccessMode(b_death, MB_MODE_IDLE);
	if(FLAME_death_message_board_write == 1 &&
		FLAME_death_message_board_read == 0)
			rc = MB_SetAccessMode(b_death, MB_MODE_WRITEONLY);
	if(FLAME_death_message_board_write == 0 &&
		FLAME_death_message_board_read == 1)
			rc = MB_SetAccessMode(b_death, MB_MODE_READONLY);
	if(FLAME_death_message_board_write == 1 &&
		FLAME_death_message_board_read == 1)
			rc = MB_SetAccessMode(b_death, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'death' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'death' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'death' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_widow_message_board_write = 0;
	FLAME_widow_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_widow_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_widow_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_widow_message_board_write == 0 &&
		FLAME_widow_message_board_read == 0)
			rc = MB_SetAccessMode(b_widow, MB_MODE_IDLE);
	if(FLAME_widow_message_board_write == 1 &&
		FLAME_widow_message_board_read == 0)
			rc = MB_SetAccessMode(b_widow, MB_MODE_WRITEONLY);
	if(FLAME_widow_message_board_write == 0 &&
		FLAME_widow_message_board_read == 1)
			rc = MB_SetAccessMode(b_widow, MB_MODE_READONLY);
	if(FLAME_widow_message_board_write == 1 &&
		FLAME_widow_message_board_read == 1)
			rc = MB_SetAccessMode(b_widow, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'widow' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'widow' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'widow' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_informationDivide_message_board_write = 0;
	FLAME_informationDivide_message_board_read = 0;
	/* Sending agents */
	if(indv_start_state->agents != NULL) FLAME_informationDivide_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_informationDivide_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_informationDivide_message_board_write == 0 &&
		FLAME_informationDivide_message_board_read == 0)
			rc = MB_SetAccessMode(b_informationDivide, MB_MODE_IDLE);
	if(FLAME_informationDivide_message_board_write == 1 &&
		FLAME_informationDivide_message_board_read == 0)
			rc = MB_SetAccessMode(b_informationDivide, MB_MODE_WRITEONLY);
	if(FLAME_informationDivide_message_board_write == 0 &&
		FLAME_informationDivide_message_board_read == 1)
			rc = MB_SetAccessMode(b_informationDivide, MB_MODE_READONLY);
	if(FLAME_informationDivide_message_board_write == 1 &&
		FLAME_informationDivide_message_board_read == 1)
			rc = MB_SetAccessMode(b_informationDivide, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'informationDivide' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'informationDivide' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_clan_info_message_board_write = 0;
	FLAME_clan_info_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_clan_info_message_board_write = 1;
	
	/* Reading agents */
	if(patch_start_state->agents != NULL) FLAME_clan_info_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_clan_info_message_board_write == 0 &&
		FLAME_clan_info_message_board_read == 0)
			rc = MB_SetAccessMode(b_clan_info, MB_MODE_IDLE);
	if(FLAME_clan_info_message_board_write == 1 &&
		FLAME_clan_info_message_board_read == 0)
			rc = MB_SetAccessMode(b_clan_info, MB_MODE_WRITEONLY);
	if(FLAME_clan_info_message_board_write == 0 &&
		FLAME_clan_info_message_board_read == 1)
			rc = MB_SetAccessMode(b_clan_info, MB_MODE_READONLY);
	if(FLAME_clan_info_message_board_write == 1 &&
		FLAME_clan_info_message_board_read == 1)
			rc = MB_SetAccessMode(b_clan_info, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'clan_info' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_clangetcalories_message_board_write = 0;
	FLAME_clangetcalories_message_board_read = 0;
	/* Sending agents */
	if(patch_start_state->agents != NULL) FLAME_clangetcalories_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_clangetcalories_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_clangetcalories_message_board_write == 0 &&
		FLAME_clangetcalories_message_board_read == 0)
			rc = MB_SetAccessMode(b_clangetcalories, MB_MODE_IDLE);
	if(FLAME_clangetcalories_message_board_write == 1 &&
		FLAME_clangetcalories_message_board_read == 0)
			rc = MB_SetAccessMode(b_clangetcalories, MB_MODE_WRITEONLY);
	if(FLAME_clangetcalories_message_board_write == 0 &&
		FLAME_clangetcalories_message_board_read == 1)
			rc = MB_SetAccessMode(b_clangetcalories, MB_MODE_READONLY);
	if(FLAME_clangetcalories_message_board_write == 1 &&
		FLAME_clangetcalories_message_board_read == 1)
			rc = MB_SetAccessMode(b_clangetcalories, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'clangetcalories' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_freeGirls_message_board_write = 0;
	FLAME_freeGirls_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_freeGirls_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_freeGirls_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_freeGirls_message_board_write == 0 &&
		FLAME_freeGirls_message_board_read == 0)
			rc = MB_SetAccessMode(b_freeGirls, MB_MODE_IDLE);
	if(FLAME_freeGirls_message_board_write == 1 &&
		FLAME_freeGirls_message_board_read == 0)
			rc = MB_SetAccessMode(b_freeGirls, MB_MODE_WRITEONLY);
	if(FLAME_freeGirls_message_board_write == 0 &&
		FLAME_freeGirls_message_board_read == 1)
			rc = MB_SetAccessMode(b_freeGirls, MB_MODE_READONLY);
	if(FLAME_freeGirls_message_board_write == 1 &&
		FLAME_freeGirls_message_board_read == 1)
			rc = MB_SetAccessMode(b_freeGirls, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'freeGirls' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'freeGirls' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_propuesta_message_board_write = 0;
	FLAME_propuesta_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_propuesta_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_propuesta_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_propuesta_message_board_write == 0 &&
		FLAME_propuesta_message_board_read == 0)
			rc = MB_SetAccessMode(b_propuesta, MB_MODE_IDLE);
	if(FLAME_propuesta_message_board_write == 1 &&
		FLAME_propuesta_message_board_read == 0)
			rc = MB_SetAccessMode(b_propuesta, MB_MODE_WRITEONLY);
	if(FLAME_propuesta_message_board_write == 0 &&
		FLAME_propuesta_message_board_read == 1)
			rc = MB_SetAccessMode(b_propuesta, MB_MODE_READONLY);
	if(FLAME_propuesta_message_board_write == 1 &&
		FLAME_propuesta_message_board_read == 1)
			rc = MB_SetAccessMode(b_propuesta, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'propuesta' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'propuesta' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_confirProp_message_board_write = 0;
	FLAME_confirProp_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_confirProp_message_board_write = 1;
	
	/* Reading agents */
	if(clan_start_state->agents != NULL) FLAME_confirProp_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_confirProp_message_board_write == 0 &&
		FLAME_confirProp_message_board_read == 0)
			rc = MB_SetAccessMode(b_confirProp, MB_MODE_IDLE);
	if(FLAME_confirProp_message_board_write == 1 &&
		FLAME_confirProp_message_board_read == 0)
			rc = MB_SetAccessMode(b_confirProp, MB_MODE_WRITEONLY);
	if(FLAME_confirProp_message_board_write == 0 &&
		FLAME_confirProp_message_board_read == 1)
			rc = MB_SetAccessMode(b_confirProp, MB_MODE_READONLY);
	if(FLAME_confirProp_message_board_write == 1 &&
		FLAME_confirProp_message_board_read == 1)
			rc = MB_SetAccessMode(b_confirProp, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'confirProp' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'confirProp' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_marriage_message_board_write = 0;
	FLAME_marriage_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_marriage_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_marriage_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_marriage_message_board_write == 0 &&
		FLAME_marriage_message_board_read == 0)
			rc = MB_SetAccessMode(b_marriage, MB_MODE_IDLE);
	if(FLAME_marriage_message_board_write == 1 &&
		FLAME_marriage_message_board_read == 0)
			rc = MB_SetAccessMode(b_marriage, MB_MODE_WRITEONLY);
	if(FLAME_marriage_message_board_write == 0 &&
		FLAME_marriage_message_board_read == 1)
			rc = MB_SetAccessMode(b_marriage, MB_MODE_READONLY);
	if(FLAME_marriage_message_board_write == 1 &&
		FLAME_marriage_message_board_read == 1)
			rc = MB_SetAccessMode(b_marriage, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'marriage' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'marriage' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_respuestaID_message_board_write = 0;
	FLAME_respuestaID_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_respuestaID_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_respuestaID_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_respuestaID_message_board_write == 0 &&
		FLAME_respuestaID_message_board_read == 0)
			rc = MB_SetAccessMode(b_respuestaID, MB_MODE_IDLE);
	if(FLAME_respuestaID_message_board_write == 1 &&
		FLAME_respuestaID_message_board_read == 0)
			rc = MB_SetAccessMode(b_respuestaID, MB_MODE_WRITEONLY);
	if(FLAME_respuestaID_message_board_write == 0 &&
		FLAME_respuestaID_message_board_read == 1)
			rc = MB_SetAccessMode(b_respuestaID, MB_MODE_READONLY);
	if(FLAME_respuestaID_message_board_write == 1 &&
		FLAME_respuestaID_message_board_read == 1)
			rc = MB_SetAccessMode(b_respuestaID, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'respuestaID' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'respuestaID' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_lmarriage_message_board_write = 0;
	FLAME_lmarriage_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_lmarriage_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_lmarriage_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_lmarriage_message_board_write == 0 &&
		FLAME_lmarriage_message_board_read == 0)
			rc = MB_SetAccessMode(b_lmarriage, MB_MODE_IDLE);
	if(FLAME_lmarriage_message_board_write == 1 &&
		FLAME_lmarriage_message_board_read == 0)
			rc = MB_SetAccessMode(b_lmarriage, MB_MODE_WRITEONLY);
	if(FLAME_lmarriage_message_board_write == 0 &&
		FLAME_lmarriage_message_board_read == 1)
			rc = MB_SetAccessMode(b_lmarriage, MB_MODE_READONLY);
	if(FLAME_lmarriage_message_board_write == 1 &&
		FLAME_lmarriage_message_board_read == 1)
			rc = MB_SetAccessMode(b_lmarriage, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'lmarriage' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'lmarriage' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_warningDivide_message_board_write = 0;
	FLAME_warningDivide_message_board_read = 0;
	/* Sending agents */
	if(clan_start_state->agents != NULL) FLAME_warningDivide_message_board_write = 1;
	
	/* Reading agents */
	if(indv_start_state->agents != NULL) FLAME_warningDivide_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_warningDivide_message_board_write == 0 &&
		FLAME_warningDivide_message_board_read == 0)
			rc = MB_SetAccessMode(b_warningDivide, MB_MODE_IDLE);
	if(FLAME_warningDivide_message_board_write == 1 &&
		FLAME_warningDivide_message_board_read == 0)
			rc = MB_SetAccessMode(b_warningDivide, MB_MODE_WRITEONLY);
	if(FLAME_warningDivide_message_board_write == 0 &&
		FLAME_warningDivide_message_board_read == 1)
			rc = MB_SetAccessMode(b_warningDivide, MB_MODE_READONLY);
	if(FLAME_warningDivide_message_board_write == 1 &&
		FLAME_warningDivide_message_board_read == 1)
			rc = MB_SetAccessMode(b_warningDivide, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'warningDivide' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'warningDivide' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_clanspatch_message_board_write = 0;
	FLAME_clanspatch_message_board_read = 0;
	/* Sending agents */
	if(patch_start_state->agents != NULL) FLAME_clanspatch_message_board_write = 1;
	
	/* Reading agents */
	if(manada_guanacos_start_state->agents != NULL) FLAME_clanspatch_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_clanspatch_message_board_write == 0 &&
		FLAME_clanspatch_message_board_read == 0)
			rc = MB_SetAccessMode(b_clanspatch, MB_MODE_IDLE);
	if(FLAME_clanspatch_message_board_write == 1 &&
		FLAME_clanspatch_message_board_read == 0)
			rc = MB_SetAccessMode(b_clanspatch, MB_MODE_WRITEONLY);
	if(FLAME_clanspatch_message_board_write == 0 &&
		FLAME_clanspatch_message_board_read == 1)
			rc = MB_SetAccessMode(b_clanspatch, MB_MODE_READONLY);
	if(FLAME_clanspatch_message_board_write == 1 &&
		FLAME_clanspatch_message_board_read == 1)
			rc = MB_SetAccessMode(b_clanspatch, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'clanspatch' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'clanspatch' board is locked\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_adultospatch_message_board_write = 0;
	FLAME_adultospatch_message_board_read = 0;
	/* Sending agents */
	if(manada_guanacos_start_state->agents != NULL) FLAME_adultospatch_message_board_write = 1;
	
	/* Reading agents */
	if(patch_start_state->agents != NULL) FLAME_adultospatch_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_adultospatch_message_board_write == 0 &&
		FLAME_adultospatch_message_board_read == 0)
			rc = MB_SetAccessMode(b_adultospatch, MB_MODE_IDLE);
	if(FLAME_adultospatch_message_board_write == 1 &&
		FLAME_adultospatch_message_board_read == 0)
			rc = MB_SetAccessMode(b_adultospatch, MB_MODE_WRITEONLY);
	if(FLAME_adultospatch_message_board_write == 0 &&
		FLAME_adultospatch_message_board_read == 1)
			rc = MB_SetAccessMode(b_adultospatch, MB_MODE_READONLY);
	if(FLAME_adultospatch_message_board_write == 1 &&
		FLAME_adultospatch_message_board_read == 1)
			rc = MB_SetAccessMode(b_adultospatch, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'adultospatch' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	FLAME_reproduccionguanacos_message_board_write = 0;
	FLAME_reproduccionguanacos_message_board_read = 0;
	/* Sending agents */
	if(manada_guanacos_start_state->agents != NULL) FLAME_reproduccionguanacos_message_board_write = 1;
	
	/* Reading agents */
	if(patch_start_state->agents != NULL) FLAME_reproduccionguanacos_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_reproduccionguanacos_message_board_write == 0 &&
		FLAME_reproduccionguanacos_message_board_read == 0)
			rc = MB_SetAccessMode(b_reproduccionguanacos, MB_MODE_IDLE);
	if(FLAME_reproduccionguanacos_message_board_write == 1 &&
		FLAME_reproduccionguanacos_message_board_read == 0)
			rc = MB_SetAccessMode(b_reproduccionguanacos, MB_MODE_WRITEONLY);
	if(FLAME_reproduccionguanacos_message_board_write == 0 &&
		FLAME_reproduccionguanacos_message_board_read == 1)
			rc = MB_SetAccessMode(b_reproduccionguanacos, MB_MODE_READONLY);
	if(FLAME_reproduccionguanacos_message_board_write == 1 &&
		FLAME_reproduccionguanacos_message_board_read == 1)
			rc = MB_SetAccessMode(b_reproduccionguanacos, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'reproduccionguanacos' board\n");
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
		   default:
			   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }
		   
		   exit(rc);
	}
	#endif
	
	
	/* Start timing */
	start = get_time();

	for(iteration_loop=iteration_number+1; iteration_loop < iteration_number+iteration_total+1; iteration_loop++)
	{
		interval = get_time();

		/* Print out iteration number */
		
		fprintf(stdout, "Iteration - %d\n", iteration_loop);
		(void)fflush(stdout);
        
		/* START OF ITERATION */
		
		/* Start sync message boards that don't write */
		if(FLAME_information_message_board_write == 0)
		{
			/*printf("%d> information message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_information)\n");
			rc = MB_SyncStart(b_information);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_information)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'information' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_indgetcalories_message_board_write == 0)
		{
			/*printf("%d> indgetcalories message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_indgetcalories)\n");
			rc = MB_SyncStart(b_indgetcalories);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_indgetcalories)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'indgetcalories' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_leader_message_board_write == 0)
		{
			/*printf("%d> leader message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_leader)\n");
			rc = MB_SyncStart(b_leader);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_leader)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'leader' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_ancestor_message_board_write == 0)
		{
			/*printf("%d> ancestor message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_ancestor)\n");
			rc = MB_SyncStart(b_ancestor);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_ancestor)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'ancestor' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'ancestor' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_peticionID_message_board_write == 0)
		{
			/*printf("%d> peticionID message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_peticionID)\n");
			rc = MB_SyncStart(b_peticionID);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_peticionID)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'peticionID' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'peticionID' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_family_message_board_write == 0)
		{
			/*printf("%d> family message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_family)\n");
			rc = MB_SyncStart(b_family);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_family)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'family' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'family' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'family' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_death_message_board_write == 0)
		{
			/*printf("%d> death message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_death)\n");
			rc = MB_SyncStart(b_death);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_death)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'death' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'death' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'death' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_widow_message_board_write == 0)
		{
			/*printf("%d> widow message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_widow)\n");
			rc = MB_SyncStart(b_widow);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_widow)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'widow' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'widow' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'widow' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_informationDivide_message_board_write == 0)
		{
			/*printf("%d> informationDivide message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_informationDivide)\n");
			rc = MB_SyncStart(b_informationDivide);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_informationDivide)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'informationDivide' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'informationDivide' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_clan_info_message_board_write == 0)
		{
			/*printf("%d> clan_info message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_clan_info)\n");
			rc = MB_SyncStart(b_clan_info);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_clan_info)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'clan_info' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_clangetcalories_message_board_write == 0)
		{
			/*printf("%d> clangetcalories message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_clangetcalories)\n");
			rc = MB_SyncStart(b_clangetcalories);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_clangetcalories)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'clangetcalories' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_freeGirls_message_board_write == 0)
		{
			/*printf("%d> freeGirls message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_freeGirls)\n");
			rc = MB_SyncStart(b_freeGirls);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_freeGirls)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'freeGirls' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'freeGirls' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_propuesta_message_board_write == 0)
		{
			/*printf("%d> propuesta message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_propuesta)\n");
			rc = MB_SyncStart(b_propuesta);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_propuesta)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'propuesta' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'propuesta' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_confirProp_message_board_write == 0)
		{
			/*printf("%d> confirProp message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_confirProp)\n");
			rc = MB_SyncStart(b_confirProp);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_confirProp)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'confirProp' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'confirProp' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_marriage_message_board_write == 0)
		{
			/*printf("%d> marriage message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_marriage)\n");
			rc = MB_SyncStart(b_marriage);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_marriage)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'marriage' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'marriage' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_respuestaID_message_board_write == 0)
		{
			/*printf("%d> respuestaID message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_respuestaID)\n");
			rc = MB_SyncStart(b_respuestaID);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_respuestaID)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'respuestaID' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'respuestaID' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_lmarriage_message_board_write == 0)
		{
			/*printf("%d> lmarriage message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_lmarriage)\n");
			rc = MB_SyncStart(b_lmarriage);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_lmarriage)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'lmarriage' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'lmarriage' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_warningDivide_message_board_write == 0)
		{
			/*printf("%d> warningDivide message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_warningDivide)\n");
			rc = MB_SyncStart(b_warningDivide);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_warningDivide)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'warningDivide' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'warningDivide' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_clanspatch_message_board_write == 0)
		{
			/*printf("%d> clanspatch message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_clanspatch)\n");
			rc = MB_SyncStart(b_clanspatch);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_clanspatch)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'clanspatch' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'clanspatch' board is locked\n");
					   break;
				   case MB_ERR_MEMALLOC:
					   fprintf(stderr, "\t reason: out of memory\n");
					   break;
				   case MB_ERR_INTERNAL:
					   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
					   break;
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_adultospatch_message_board_write == 0)
		{
			/*printf("%d> adultospatch message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_adultospatch)\n");
			rc = MB_SyncStart(b_adultospatch);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_adultospatch)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'adultospatch' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		/* Start sync message boards that don't write */
		if(FLAME_reproduccionguanacos_message_board_write == 0)
		{
			/*printf("%d> reproduccionguanacos message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_reproduccionguanacos)\n");
			rc = MB_SyncStart(b_reproduccionguanacos);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_reproduccionguanacos)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'reproduccionguanacos' board\n");
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
				   default:
					   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
					   break;
			   }
			   
					   
					   exit(rc);
			   }
			   #endif
		}
		
		
	/* DEBUG: States with branching functions */
		current_xmachine_patch_holder = patch_start_state->agents;
		while(current_xmachine_patch_holder)
		{
			FLAME_debug_count = 0;
			/* Function: infoClansInPatch */
			if(FLAME_condition_patch_infoClansInPatch_start_1(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: patchtype */
			if(FLAME_condition_patch_patchtype_start_1(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'patch' leaving state 'start'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_patch_holder = current_xmachine_patch_holder->next;
		}
		/* DEBUG: States with branching functions */
		current_xmachine_manada_guanacos_holder = manada_guanacos_start_state->agents;
		while(current_xmachine_manada_guanacos_holder)
		{
			FLAME_debug_count = 0;
			/* Function: seasonSwitch */
			if(FLAME_condition_manada_guanacos_seasonSwitch_start_1(current_xmachine_manada_guanacos_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: manadaInfo */
			if(FLAME_condition_manada_guanacos_manadaInfo_start_1(current_xmachine_manada_guanacos_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'manada_guanacos' leaving state 'start'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start infoClansInPatch\n");
	current_xmachine_patch_holder = patch_start_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_1_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_infoClansInPatch_start_1(current_xmachine_patch)==1)
		{

		

			i = infoClansInPatch();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_start_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_start_state, patch_1_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish infoClansInPatch\n");

	if(FLAME_clanspatch_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_clanspatch)\n");
		rc = MB_SyncStart(b_clanspatch);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_clanspatch)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'clanspatch' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'clanspatch' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start indvInformation\n");
	current_xmachine_indv_holder = indv_start_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_01_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		

		

			i = indvInformation();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_start_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_start_state, indv_01_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish indvInformation\n");

	if(FLAME_information_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_information)\n");
		rc = MB_SyncStart(b_information);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_information)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'information' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start seasonSwitch\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_start_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_1_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		if(FLAME_condition_manada_guanacos_seasonSwitch_start_1(current_xmachine_manada_guanacos)==1)
		{

		

			i = seasonSwitch();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state, manada_guanacos_1_state);
			}
		}

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish seasonSwitch\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start manadaInfo\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_start_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_1_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		if(FLAME_condition_manada_guanacos_manadaInfo_start_1(current_xmachine_manada_guanacos)==1)
		{

		

			i = manadaInfo();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state, manada_guanacos_1_state);
			}
		}

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish manadaInfo\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start patchtype\n");
	current_xmachine_patch_holder = patch_start_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_1_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_patchtype_start_1(current_xmachine_patch)==1)
		{

		

			i = patchtype();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_start_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_start_state, patch_1_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish patchtype\n");


/* End of layer number 0 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

	/* DEBUG: States with branching functions */
		current_xmachine_manada_guanacos_holder = manada_guanacos_1_state->agents;
		while(current_xmachine_manada_guanacos_holder)
		{
			FLAME_debug_count = 0;
			/* Function: move */
			if(FLAME_condition_manada_guanacos_move_1_2(current_xmachine_manada_guanacos_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: manada_idle */
			if(FLAME_condition_manada_guanacos_manada_idle_1_2(current_xmachine_manada_guanacos_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'manada_guanacos' leaving state '1'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		}
	
	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_clanspatch_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_clanspatch)\n");
		rc = MB_SyncComplete(b_clanspatch);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_clanspatch)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'clanspatch' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    /* Built 2d tree */
    rc = MB_SearchTree_Create2D(b_clanspatch, &tree_ptr_2d_clanspatch,
                           &clanspatch_message_extract_x,
                           &clanspatch_message_extract_y);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not create MB_SearchTree_Create2D for 'clanspatch'\n");
       
       exit(rc);
    }
    #endif
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start move\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_1_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_2_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		if(FLAME_condition_manada_guanacos_move_1_2(current_xmachine_manada_guanacos)==1)
		{

		
		
          /* MB_Iterator 2d tree */
          rc = MB_SearchTree_Search2D(tree_ptr_2d_clanspatch, &i_clanspatch,
                           (double)current_xmachine_manada_guanacos->x - (double)2.0,
                           (double)current_xmachine_manada_guanacos->x + (double)2.0,
                           (double)current_xmachine_manada_guanacos->y - (double)2.0,
                           (double)current_xmachine_manada_guanacos->y + (double)2.0);
                  
          
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'clanspatch'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'clanspatch' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = move();

		
		    rc = MB_Iterator_Delete(&i_clanspatch);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'clanspatch' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'clanspatch' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_1_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_1_state, manada_guanacos_2_state);
			}
		}

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish move\n");

	if(FLAME_adultospatch_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_adultospatch)\n");
		rc = MB_SyncStart(b_adultospatch);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_adultospatch)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'adultospatch' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start manada_idle\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_1_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_2_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		if(FLAME_condition_manada_guanacos_manada_idle_1_2(current_xmachine_manada_guanacos)==1)
		{

		

			i = manada_idle();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_1_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_1_state, manada_guanacos_2_state);
			}
		}

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish manada_idle\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_information_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_information)\n");
		rc = MB_SyncComplete(b_information);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_information)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'information' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'information' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start clan_Information\n");
	current_xmachine_clan_holder = clan_start_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_01_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = clan_Information();

		
		    rc = MB_Iterator_Delete(&i_information);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'information' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'information' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_start_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_start_state, clan_01_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish clan_Information\n");

	if(FLAME_clan_info_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_clan_info)\n");
		rc = MB_SyncStart(b_clan_info);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_clan_info)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'clan_info' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 1 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_information_message_board_read == 0)
{
	/*printf("%d> information message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_information)\n");
	rc = MB_SyncComplete(b_information);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_information)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'information' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'information' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

if(FLAME_clanspatch_message_board_read == 0)
{
	/*printf("%d> clanspatch message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_clanspatch)\n");
	rc = MB_SyncComplete(b_clanspatch);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_clanspatch)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'clanspatch' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */
    rc = MB_SearchTree_Delete(&tree_ptr_2d_clanspatch);

    rc = MB_Clear(b_clanspatch);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'clanspatch' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clanspatch' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clanspatch' board is locked\n");
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

	/* DEBUG: States with branching functions */
		current_xmachine_manada_guanacos_holder = manada_guanacos_2_state->agents;
		while(current_xmachine_manada_guanacos_holder)
		{
			FLAME_debug_count = 0;
			/* Function: manada_idle2 */
			if(FLAME_condition_manada_guanacos_manada_idle2_2_3(current_xmachine_manada_guanacos_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: reproduccion */
			if(FLAME_condition_manada_guanacos_reproduccion_2_3(current_xmachine_manada_guanacos_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'manada_guanacos' leaving state '2'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		}
	
	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_clan_info_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_clan_info)\n");
		rc = MB_SyncComplete(b_clan_info);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_clan_info)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'clan_info' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'clan_info' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start patchcalories\n");
	current_xmachine_patch_holder = patch_1_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_2_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		

		
		
          
                  
          
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = patchcalories();

		
		    rc = MB_Iterator_Delete(&i_clan_info);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'clan_info' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'clan_info' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_1_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_1_state, patch_2_state);
			}
		

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish patchcalories\n");

	if(FLAME_clangetcalories_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_clangetcalories)\n");
		rc = MB_SyncStart(b_clangetcalories);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_clangetcalories)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'clangetcalories' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start reproduccion\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_2_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_3_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		if(FLAME_condition_manada_guanacos_reproduccion_2_3(current_xmachine_manada_guanacos)==1)
		{

		

			i = reproduccion();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state, manada_guanacos_3_state);
			}
		}

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish reproduccion\n");

	if(FLAME_reproduccionguanacos_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_reproduccionguanacos)\n");
		rc = MB_SyncStart(b_reproduccionguanacos);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_reproduccionguanacos)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'reproduccionguanacos' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start manada_idle2\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_2_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_3_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		if(FLAME_condition_manada_guanacos_manada_idle2_2_3(current_xmachine_manada_guanacos)==1)
		{

		

			i = manada_idle2();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state, manada_guanacos_3_state);
			}
		}

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish manada_idle2\n");


/* End of layer number 2 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_clan_info_message_board_read == 0)
{
	/*printf("%d> clan_info message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_clan_info)\n");
	rc = MB_SyncComplete(b_clan_info);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_clan_info)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'clan_info' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'clan_info' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

	/* DEBUG: States with branching functions */
		current_xmachine_patch_holder = patch_2_state->agents;
		while(current_xmachine_patch_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle_patch */
			if(FLAME_condition_patch_idle_patch_2_3(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: regenerate */
			if(FLAME_condition_patch_regenerate_2_3(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'patch' leaving state '2'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_patch_holder = current_xmachine_patch_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start surviveGuanacos\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_3_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		current_xmachine_manada_guanacos = current_xmachine_manada_guanacos_holder->agent;
		current_xmachine_manada_guanacos_next_state = manada_guanacos_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_manada_guanacos = current_xmachine_manada_guanacos;

		

		

			i = surviveGuanacos();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_3_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_3_state, manada_guanacos_end_state);
			}
		

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish surviveGuanacos\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle_patch\n");
	current_xmachine_patch_holder = patch_2_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_3_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_idle_patch_2_3(current_xmachine_patch)==1)
		{

		

			i = idle_patch();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_2_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_2_state, patch_3_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle_patch\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start regenerate\n");
	current_xmachine_patch_holder = patch_2_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_3_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_regenerate_2_3(current_xmachine_patch)==1)
		{

		

			i = regenerate();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_2_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_2_state, patch_3_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish regenerate\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_clangetcalories_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_clangetcalories)\n");
		rc = MB_SyncComplete(b_clangetcalories);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_clangetcalories)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'clangetcalories' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'clangetcalories' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start clan_extract_calories\n");
	current_xmachine_clan_holder = clan_01_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_02_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = clan_extract_calories();

		
		    rc = MB_Iterator_Delete(&i_clangetcalories);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'clangetcalories' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'clangetcalories' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_01_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_01_state, clan_02_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish clan_extract_calories\n");


/* End of layer number 3 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_clangetcalories_message_board_read == 0)
{
	/*printf("%d> clangetcalories message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_clangetcalories)\n");
	rc = MB_SyncComplete(b_clangetcalories);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_clangetcalories)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'clangetcalories' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'clangetcalories' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

	/* DEBUG: States with branching functions */
		current_xmachine_patch_holder = patch_3_state->agents;
		while(current_xmachine_patch_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle_patch */
			if(FLAME_condition_patch_idle_patch_3_4(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: snregenerate */
			if(FLAME_condition_patch_snregenerate_3_4(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'patch' leaving state '3'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_patch_holder = current_xmachine_patch_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start distribute_calories\n");
	current_xmachine_clan_holder = clan_02_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_03_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		

			i = distribute_calories();

		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_02_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_02_state, clan_03_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish distribute_calories\n");

	if(FLAME_indgetcalories_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_indgetcalories)\n");
		rc = MB_SyncStart(b_indgetcalories);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_indgetcalories)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'indgetcalories' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle_patch\n");
	current_xmachine_patch_holder = patch_3_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_4_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_idle_patch_3_4(current_xmachine_patch)==1)
		{

		

			i = idle_patch();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_3_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_3_state, patch_4_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle_patch\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start snregenerate\n");
	current_xmachine_patch_holder = patch_3_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_4_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_snregenerate_3_4(current_xmachine_patch)==1)
		{

		

			i = snregenerate();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_3_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_3_state, patch_4_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish snregenerate\n");


/* End of layer number 4 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_adultospatch_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_adultospatch)\n");
		rc = MB_SyncComplete(b_adultospatch);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_adultospatch)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'adultospatch' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'adultospatch' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start guanacos_move\n");
	current_xmachine_patch_holder = patch_4_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_5_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_adultospatch, &i_adultospatch, &FLAME_filter_patch_guanacos_move_4_5_adultospatch, current_xmachine_patch);
		    
		  
		
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = guanacos_move();

		
		    rc = MB_Iterator_Delete(&i_adultospatch);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'adultospatch' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'adultospatch' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_4_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_4_state, patch_5_state);
			}
		

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish guanacos_move\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_indgetcalories_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_indgetcalories)\n");
		rc = MB_SyncComplete(b_indgetcalories);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_indgetcalories)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'indgetcalories' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'indgetcalories' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start extractcalories\n");
	current_xmachine_indv_holder = indv_01_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_02_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		

		
		
          
                  
          
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = extractcalories();

		
		    rc = MB_Iterator_Delete(&i_indgetcalories);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'indgetcalories' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'indgetcalories' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_01_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_01_state, indv_02_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish extractcalories\n");


/* End of layer number 5 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_indgetcalories_message_board_read == 0)
{
	/*printf("%d> indgetcalories message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_indgetcalories)\n");
	rc = MB_SyncComplete(b_indgetcalories);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_indgetcalories)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'indgetcalories' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'indgetcalories' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

if(FLAME_adultospatch_message_board_read == 0)
{
	/*printf("%d> adultospatch message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_adultospatch)\n");
	rc = MB_SyncComplete(b_adultospatch);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_adultospatch)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'adultospatch' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'adultospatch' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_02_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle_indv */
			if(FLAME_condition_indv_idle_indv_02_03(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: getolder */
			if(FLAME_condition_indv_getolder_02_03(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '02'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
		/* DEBUG: States with branching functions */
		current_xmachine_patch_holder = patch_5_state->agents;
		while(current_xmachine_patch_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle_patch */
			if(FLAME_condition_patch_idle_patch_5_end(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: reproduccion_guanacos */
			if(FLAME_condition_patch_reproduccion_guanacos_5_end(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'patch' leaving state '5'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_patch_holder = current_xmachine_patch_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle_patch\n");
	current_xmachine_patch_holder = patch_5_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_idle_patch_5_end(current_xmachine_patch)==1)
		{

		

			i = idle_patch();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_5_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_5_state, patch_end_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle_patch\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle_indv\n");
	current_xmachine_indv_holder = indv_02_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_03_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_indv_02_03(current_xmachine_indv)==1)
		{

		

			i = idle_indv();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_02_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_02_state, indv_03_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle_indv\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start getolder\n");
	current_xmachine_indv_holder = indv_02_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_03_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_getolder_02_03(current_xmachine_indv)==1)
		{

		

			i = getolder();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_02_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_02_state, indv_03_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish getolder\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_reproduccionguanacos_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_reproduccionguanacos)\n");
		rc = MB_SyncComplete(b_reproduccionguanacos);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_reproduccionguanacos)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'reproduccionguanacos' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'reproduccionguanacos' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start reproduccion_guanacos\n");
	current_xmachine_patch_holder = patch_5_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		current_xmachine_patch = current_xmachine_patch_holder->agent;
		current_xmachine_patch_next_state = patch_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_reproduccion_guanacos_5_end(current_xmachine_patch)==1)
		{

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_reproduccionguanacos, &i_reproduccionguanacos, &FLAME_filter_patch_reproduccion_guanacos_5_end_reproduccionguanacos, current_xmachine_patch);
		    
		  
		
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = reproduccion_guanacos();

		
		    rc = MB_Iterator_Delete(&i_reproduccionguanacos);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'reproduccionguanacos' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'reproduccionguanacos' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_5_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_5_state, patch_end_state);
			}
		}

		current_xmachine_patch = NULL;

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish reproduccion_guanacos\n");


/* End of layer number 6 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_reproduccionguanacos_message_board_read == 0)
{
	/*printf("%d> reproduccionguanacos message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_reproduccionguanacos)\n");
	rc = MB_SyncComplete(b_reproduccionguanacos);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_reproduccionguanacos)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'reproduccionguanacos' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'reproduccionguanacos' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_03_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_indv_idle_03_06(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: freeIndv */
			if(FLAME_condition_indv_freeIndv_03_04(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '03'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start freeIndv\n");
	current_xmachine_indv_holder = indv_03_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_04_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_freeIndv_03_04(current_xmachine_indv)==1)
		{

		

			i = freeIndv();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_03_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_03_state, indv_04_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish freeIndv\n");

	if(FLAME_ancestor_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_ancestor)\n");
		rc = MB_SyncStart(b_ancestor);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_ancestor)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'ancestor' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'ancestor' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_indv_holder = indv_03_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_06_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_03_06(current_xmachine_indv)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_03_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_03_state, indv_06_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


/* End of layer number 7 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_04_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: casamiento_male */
			if(FLAME_condition_indv_casamiento_male_04_06(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: casamiento_female */
			if(FLAME_condition_indv_casamiento_female_04_05(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '04'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_ancestor_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_ancestor)\n");
		rc = MB_SyncComplete(b_ancestor);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_ancestor)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'ancestor' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start marriable_indv\n");
	current_xmachine_clan_holder = clan_03_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_04_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_ancestor, &i_ancestor, &FLAME_filter_clan_marriable_indv_03_04_ancestor, current_xmachine_clan);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'ancestor'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'ancestor' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = marriable_indv();

		
		    rc = MB_Iterator_Delete(&i_ancestor);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'ancestor' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'ancestor' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_03_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_03_state, clan_04_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish marriable_indv\n");


/* End of layer number 8 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_ancestor_message_board_read == 0)
{
	/*printf("%d> ancestor message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_ancestor)\n");
	rc = MB_SyncComplete(b_ancestor);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_ancestor)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'ancestor' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_ancestor);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'ancestor' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'ancestor' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'ancestor' board is locked\n");
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


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start send_girls\n");
	current_xmachine_clan_holder = clan_04_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_05_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		

			i = send_girls();

		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_04_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_04_state, clan_05_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish send_girls\n");

	if(FLAME_freeGirls_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_freeGirls)\n");
		rc = MB_SyncStart(b_freeGirls);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_freeGirls)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'freeGirls' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'freeGirls' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 9 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_freeGirls_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_freeGirls)\n");
		rc = MB_SyncComplete(b_freeGirls);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_freeGirls)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'freeGirls' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    /* Built 2d tree */
    rc = MB_SearchTree_Create2D(b_freeGirls, &tree_ptr_2d_freeGirls,
                           &freeGirls_message_extract_x,
                           &freeGirls_message_extract_y);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not create MB_SearchTree_Create2D for 'freeGirls'\n");
       
       exit(rc);
    }
    #endif
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start match\n");
	current_xmachine_clan_holder = clan_05_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_06_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          /* MB_Iterator 2d tree */
          rc = MB_SearchTree_Search2D(tree_ptr_2d_freeGirls, &i_freeGirls,
                           (double)current_xmachine_clan->x - (double)15.0,
                           (double)current_xmachine_clan->x + (double)15.0,
                           (double)current_xmachine_clan->y - (double)15.0,
                           (double)current_xmachine_clan->y + (double)15.0);
                  
          
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'freeGirls'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'freeGirls' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = match();

		
		    rc = MB_Iterator_Delete(&i_freeGirls);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'freeGirls' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'freeGirls' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_05_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_05_state, clan_06_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish match\n");

	if(FLAME_propuesta_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_propuesta)\n");
		rc = MB_SyncStart(b_propuesta);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_propuesta)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'propuesta' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'propuesta' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 10 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_freeGirls_message_board_read == 0)
{
	/*printf("%d> freeGirls message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_freeGirls)\n");
	rc = MB_SyncComplete(b_freeGirls);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_freeGirls)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'freeGirls' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */
    rc = MB_SearchTree_Delete(&tree_ptr_2d_freeGirls);

    rc = MB_Clear(b_freeGirls);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'freeGirls' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'freeGirls' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'freeGirls' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_propuesta_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_propuesta)\n");
		rc = MB_SyncComplete(b_propuesta);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_propuesta)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'propuesta' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start aceptar_prop\n");
	current_xmachine_clan_holder = clan_06_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_07_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_propuesta, &i_propuesta, &FLAME_filter_clan_aceptar_prop_06_07_propuesta, current_xmachine_clan);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'propuesta'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'propuesta' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = aceptar_prop();

		
		    rc = MB_Iterator_Delete(&i_propuesta);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'propuesta' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'propuesta' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_06_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_06_state, clan_07_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish aceptar_prop\n");

	if(FLAME_confirProp_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_confirProp)\n");
		rc = MB_SyncStart(b_confirProp);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_confirProp)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'confirProp' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'confirProp' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 11 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_propuesta_message_board_read == 0)
{
	/*printf("%d> propuesta message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_propuesta)\n");
	rc = MB_SyncComplete(b_propuesta);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_propuesta)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'propuesta' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_propuesta);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'propuesta' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'propuesta' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'propuesta' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_confirProp_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_confirProp)\n");
		rc = MB_SyncComplete(b_confirProp);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_confirProp)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'confirProp' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start recive_conf\n");
	current_xmachine_clan_holder = clan_07_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_08_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_confirProp, &i_confirProp, &FLAME_filter_clan_recive_conf_07_08_confirProp, current_xmachine_clan);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'confirProp'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'confirProp' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = recive_conf();

		
		    rc = MB_Iterator_Delete(&i_confirProp);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'confirProp' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'confirProp' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_07_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_07_state, clan_08_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish recive_conf\n");

	if(FLAME_marriage_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_marriage)\n");
		rc = MB_SyncStart(b_marriage);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_marriage)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'marriage' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'marriage' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 12 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_confirProp_message_board_read == 0)
{
	/*printf("%d> confirProp message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_confirProp)\n");
	rc = MB_SyncComplete(b_confirProp);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_confirProp)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'confirProp' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_confirProp);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'confirProp' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'confirProp' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'confirProp' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_marriage_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_marriage)\n");
		rc = MB_SyncComplete(b_marriage);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_marriage)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'marriage' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start casamiento_male\n");
	current_xmachine_indv_holder = indv_04_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_06_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_casamiento_male_04_06(current_xmachine_indv)==1)
		{

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_marriage, &i_marriage, &FLAME_filter_indv_casamiento_male_04_06_marriage, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'marriage'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'marriage' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = casamiento_male();

		
		    rc = MB_Iterator_Delete(&i_marriage);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'marriage' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'marriage' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_04_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_04_state, indv_06_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish casamiento_male\n");

	if(FLAME_family_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_family)\n");
		rc = MB_SyncStart(b_family);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_family)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'family' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'family' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'family' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start casamiento_female\n");
	current_xmachine_indv_holder = indv_04_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_05_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_casamiento_female_04_05(current_xmachine_indv)==1)
		{

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_marriage, &i_marriage, &FLAME_filter_indv_casamiento_female_04_05_marriage, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'marriage'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'marriage' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = casamiento_female();

		
		    rc = MB_Iterator_Delete(&i_marriage);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'marriage' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'marriage' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_04_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_04_state, indv_05_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish casamiento_female\n");


/* End of layer number 13 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_marriage_message_board_read == 0)
{
	/*printf("%d> marriage message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_marriage)\n");
	rc = MB_SyncComplete(b_marriage);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_marriage)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'marriage' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_marriage);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'marriage' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'marriage' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'marriage' board is locked\n");
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

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_05_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_indv_idle_05_06(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: info_husband */
			if(FLAME_condition_indv_info_husband_05_06(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '05'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_indv_holder = indv_05_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_06_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_05_06(current_xmachine_indv)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_05_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_05_state, indv_06_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_family_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_family)\n");
		rc = MB_SyncComplete(b_family);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_family)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'family' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'family' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start info_husband\n");
	current_xmachine_indv_holder = indv_05_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_06_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_info_husband_05_06(current_xmachine_indv)==1)
		{

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_family, &i_family, &FLAME_filter_indv_info_husband_05_06_family, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'family'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'family' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'family' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = info_husband();

		
		    rc = MB_Iterator_Delete(&i_family);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'family' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'family' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_05_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_05_state, indv_06_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish info_husband\n");


/* End of layer number 14 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_family_message_board_read == 0)
{
	/*printf("%d> family message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_family)\n");
	rc = MB_SyncComplete(b_family);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_family)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'family' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'family' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_family);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'family' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'family' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'family' board is locked\n");
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

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_06_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_indv_idle_06_07(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: pregnancy */
			if(FLAME_condition_indv_pregnancy_06_09(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '06'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_indv_holder = indv_06_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_07_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_06_07(current_xmachine_indv)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_06_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_06_state, indv_07_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start pregnancy\n");
	current_xmachine_indv_holder = indv_06_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_09_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_pregnancy_06_09(current_xmachine_indv)==1)
		{

		

			i = pregnancy();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_06_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_06_state, indv_09_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish pregnancy\n");


/* End of layer number 15 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_07_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_indv_idle_07_09(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: child_inf */
			if(FLAME_condition_indv_child_inf_07_08(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '07'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start child_inf\n");
	current_xmachine_indv_holder = indv_07_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_08_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_child_inf_07_08(current_xmachine_indv)==1)
		{

		

			i = child_inf();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_07_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_07_state, indv_08_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish child_inf\n");

	if(FLAME_peticionID_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_peticionID)\n");
		rc = MB_SyncStart(b_peticionID);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_peticionID)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'peticionID' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'peticionID' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_indv_holder = indv_07_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_09_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_07_09(current_xmachine_indv)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_07_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_07_state, indv_09_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


/* End of layer number 16 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_peticionID_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_peticionID)\n");
		rc = MB_SyncComplete(b_peticionID);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_peticionID)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'peticionID' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start repartir_id\n");
	current_xmachine_clan_holder = clan_08_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_09_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_peticionID, &i_peticionID, &FLAME_filter_clan_repartir_id_08_09_peticionID, current_xmachine_clan);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'peticionID'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'peticionID' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = repartir_id();

		
		    rc = MB_Iterator_Delete(&i_peticionID);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'peticionID' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'peticionID' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_08_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_08_state, clan_09_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish repartir_id\n");

	if(FLAME_respuestaID_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_respuestaID)\n");
		rc = MB_SyncStart(b_respuestaID);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_respuestaID)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'respuestaID' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'respuestaID' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 17 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_peticionID_message_board_read == 0)
{
	/*printf("%d> peticionID message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_peticionID)\n");
	rc = MB_SyncComplete(b_peticionID);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_peticionID)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'peticionID' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_peticionID);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'peticionID' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'peticionID' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'peticionID' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_respuestaID_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_respuestaID)\n");
		rc = MB_SyncComplete(b_respuestaID);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_respuestaID)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'respuestaID' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start birth\n");
	current_xmachine_indv_holder = indv_08_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_09_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_respuestaID, &i_respuestaID, &FLAME_filter_indv_birth_08_09_respuestaID, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'respuestaID'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'respuestaID' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = birth();

		
		    rc = MB_Iterator_Delete(&i_respuestaID);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'respuestaID' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'respuestaID' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_08_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_08_state, indv_09_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish birth\n");


/* End of layer number 18 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_respuestaID_message_board_read == 0)
{
	/*printf("%d> respuestaID message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_respuestaID)\n");
	rc = MB_SyncComplete(b_respuestaID);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_respuestaID)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'respuestaID' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_respuestaID);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'respuestaID' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'respuestaID' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'respuestaID' board is locked\n");
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


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start survive\n");
	current_xmachine_indv_holder = indv_09_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_10_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		

		

			i = survive();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_09_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_09_state, indv_10_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish survive\n");

	if(FLAME_death_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_death)\n");
		rc = MB_SyncStart(b_death);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_death)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'death' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'death' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'death' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    

	if(FLAME_leader_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_leader)\n");
		rc = MB_SyncStart(b_leader);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_leader)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'leader' board\n");
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
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 19 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_death_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_death)\n");
		rc = MB_SyncComplete(b_death);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_death)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'death' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'death' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start update_status\n");
	current_xmachine_indv_holder = indv_10_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_11_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_death, &i_death, &FLAME_filter_indv_update_status_10_11_death, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'death'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'death' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'death' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = update_status();

		
		    rc = MB_Iterator_Delete(&i_death);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'death' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'death' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_10_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_10_state, indv_11_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish update_status\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_leader_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_leader)\n");
		rc = MB_SyncComplete(b_leader);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_leader)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'leader' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'leader' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start new_leader\n");
	current_xmachine_clan_holder = clan_09_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_10_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_leader, &i_leader, &FLAME_filter_clan_new_leader_09_10_leader, current_xmachine_clan);
		    
		  
		
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
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = new_leader();

		
		    rc = MB_Iterator_Delete(&i_leader);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'leader' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'leader' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_09_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_09_state, clan_10_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish new_leader\n");


/* End of layer number 20 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_leader_message_board_read == 0)
{
	/*printf("%d> leader message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_leader)\n");
	rc = MB_SyncComplete(b_leader);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_leader)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'leader' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'leader' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

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

if(FLAME_death_message_board_read == 0)
{
	/*printf("%d> death message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_death)\n");
	rc = MB_SyncComplete(b_death);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_death)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'death' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'death' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_death);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'death' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'death' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'death' board is locked\n");
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

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_11_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_indv_idle_11_12(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: husband_request */
			if(FLAME_condition_indv_husband_request_11_12(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '11'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start husband_request\n");
	current_xmachine_indv_holder = indv_11_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_12_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_husband_request_11_12(current_xmachine_indv)==1)
		{

		

			i = husband_request();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_11_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_11_state, indv_12_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish husband_request\n");

	if(FLAME_widow_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_widow)\n");
		rc = MB_SyncStart(b_widow);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_widow)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'widow' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'widow' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'widow' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_indv_holder = indv_11_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_12_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_11_12(current_xmachine_indv)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_11_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_11_state, indv_12_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


/* End of layer number 21 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

	/* DEBUG: States with branching functions */
		current_xmachine_indv_holder = indv_12_state->agents;
		while(current_xmachine_indv_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_indv_idle_12_13(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: local_marriage */
			if(FLAME_condition_indv_local_marriage_12_13(current_xmachine_indv_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'indv' leaving state '12'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_indv_holder = current_xmachine_indv_holder->next;
		}
	
	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_widow_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_widow)\n");
		rc = MB_SyncComplete(b_widow);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_widow)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'widow' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'widow' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start again_marriable\n");
	current_xmachine_clan_holder = clan_10_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_11_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_widow, &i_widow, &FLAME_filter_clan_again_marriable_10_11_widow, current_xmachine_clan);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'widow'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'widow' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'widow' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = again_marriable();

		
		    rc = MB_Iterator_Delete(&i_widow);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'widow' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'widow' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_10_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_10_state, clan_11_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish again_marriable\n");

	if(FLAME_lmarriage_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_lmarriage)\n");
		rc = MB_SyncStart(b_lmarriage);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_lmarriage)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'lmarriage' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'lmarriage' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_indv_holder = indv_12_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_13_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_idle_12_13(current_xmachine_indv)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_12_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_12_state, indv_13_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


/* End of layer number 22 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_widow_message_board_read == 0)
{
	/*printf("%d> widow message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_widow)\n");
	rc = MB_SyncComplete(b_widow);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_widow)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'widow' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'widow' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_widow);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'widow' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'widow' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'widow' board is locked\n");
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

	/* DEBUG: States with branching functions */
		current_xmachine_clan_holder = clan_11_state->agents;
		while(current_xmachine_clan_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_clan_idle_11_13(current_xmachine_clan_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: dividir_clan */
			if(FLAME_condition_clan_dividir_clan_11_12(current_xmachine_clan_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'clan' leaving state '11'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_clan_holder = current_xmachine_clan_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start dividir_clan\n");
	current_xmachine_clan_holder = clan_11_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_12_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		if(FLAME_condition_clan_dividir_clan_11_12(current_xmachine_clan)==1)
		{

		

			i = dividir_clan();

		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_11_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_11_state, clan_12_state);
			}
		}

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish dividir_clan\n");

	if(FLAME_warningDivide_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_warningDivide)\n");
		rc = MB_SyncStart(b_warningDivide);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_warningDivide)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'warningDivide' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'warningDivide' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_clan_holder = clan_11_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_13_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		if(FLAME_condition_clan_idle_11_13(current_xmachine_clan)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_11_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_11_state, clan_13_state);
			}
		}

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_lmarriage_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_lmarriage)\n");
		rc = MB_SyncComplete(b_lmarriage);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_lmarriage)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'lmarriage' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start local_marriage\n");
	current_xmachine_indv_holder = indv_12_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_13_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		if(FLAME_condition_indv_local_marriage_12_13(current_xmachine_indv)==1)
		{

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_lmarriage, &i_lmarriage, &FLAME_filter_indv_local_marriage_12_13_lmarriage, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'lmarriage'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'lmarriage' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = local_marriage();

		
		    rc = MB_Iterator_Delete(&i_lmarriage);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'lmarriage' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'lmarriage' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_12_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_12_state, indv_13_state);
			}
		}

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish local_marriage\n");


/* End of layer number 23 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_lmarriage_message_board_read == 0)
{
	/*printf("%d> lmarriage message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_lmarriage)\n");
	rc = MB_SyncComplete(b_lmarriage);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_lmarriage)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'lmarriage' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_lmarriage);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'lmarriage' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'lmarriage' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'lmarriage' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_warningDivide_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_warningDivide)\n");
		rc = MB_SyncComplete(b_warningDivide);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_warningDivide)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'warningDivide' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start dividir_info\n");
	current_xmachine_indv_holder = indv_13_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		current_xmachine_indv = current_xmachine_indv_holder->agent;
		current_xmachine_indv_next_state = indv_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_indv = current_xmachine_indv;

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_warningDivide, &i_warningDivide, &FLAME_filter_indv_dividir_info_13_end_warningDivide, current_xmachine_indv);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'warningDivide'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'warningDivide' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = dividir_info();

		
		    rc = MB_Iterator_Delete(&i_warningDivide);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'warningDivide' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'warningDivide' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_13_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_13_state, indv_end_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish dividir_info\n");

	if(FLAME_informationDivide_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_informationDivide)\n");
		rc = MB_SyncStart(b_informationDivide);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_informationDivide)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'informationDivide' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'informationDivide' board is locked\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncStart returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }

			
			exit(rc);
		}
		#endif
    }
    


/* End of layer number 24 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_warningDivide_message_board_read == 0)
{
	/*printf("%d> warningDivide message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_warningDivide)\n");
	rc = MB_SyncComplete(b_warningDivide);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_warningDivide)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'warningDivide' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_warningDivide);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'warningDivide' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'warningDivide' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'warningDivide' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_informationDivide_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_informationDivide)\n");
		rc = MB_SyncComplete(b_informationDivide);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_informationDivide)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'informationDivide' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
				   break;
			   case MB_ERR_MEMALLOC:
				   fprintf(stderr, "\t reason: out of memory\n");
				   break;
			   case MB_ERR_INTERNAL:
				   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
				   break;
			   default:
				   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
				   break;
		   }
	
		   
		   exit(rc);
		}
		#endif
    
    
    
	}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start creacion_clan\n");
	current_xmachine_clan_holder = clan_12_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_13_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		

		
		
          
                  
          
		    
		    rc = MB_Iterator_CreateFilteredSorted(b_informationDivide, &i_informationDivide, &FLAME_filter_clan_creacion_clan_12_13_informationDivide, current_xmachine_clan, &FLAME_sort_clan_creacion_clan_12_13_informationDivide);
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'informationDivide'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'informationDivide' board is locked\n");
	               break;
	           case MB_ERR_MEMALLOC:
	               fprintf(stderr, "\t reason: out of memory\n");
	               break;
	           case MB_ERR_INTERNAL:
	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
	               break;
	           default:
	           
                   fprintf(stderr, "\t MB_Iterator_CreateFiltered returned error code: %d (see libmboard docs for details)\n", rc);
               
               
                   break;
		   }

		   
           exit(rc);
		}
		#endif
		
		

			i = creacion_clan();

		
		    rc = MB_Iterator_Delete(&i_informationDivide);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'informationDivide' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'informationDivide' iterator is invalid\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
		           default:
                       fprintf(stderr, "\t MB_Iterator_Delete returned error code: %d (see libmboard docs for details)\n", rc);
                       break;
		       }

		       
               exit(rc);
		    }
		    #endif
		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_12_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_12_state, clan_13_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish creacion_clan\n");


/* End of layer number 25 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */

if(FLAME_informationDivide_message_board_read == 0)
{
	/*printf("%d> informationDivide message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_informationDivide)\n");
	rc = MB_SyncComplete(b_informationDivide);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_informationDivide)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'informationDivide' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
			   break;
		   case MB_ERR_MEMALLOC:
			   fprintf(stderr, "\t reason: out of memory\n");
			   break;
		   case MB_ERR_INTERNAL:
			   fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			   break;
		   default:
			   fprintf(stderr, "\t MB_SyncComplete returned error code: %d (see libmboard docs for details)\n", rc);
			   break;
	   }

	   
	   exit(rc);
	}
	#endif
}

    /* Delete any search trees */

    rc = MB_Clear(b_informationDivide);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'informationDivide' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'informationDivide' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'informationDivide' board is locked\n");
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

	/* DEBUG: States with branching functions */
		current_xmachine_clan_holder = clan_13_state->agents;
		while(current_xmachine_clan_holder)
		{
			FLAME_debug_count = 0;
			/* Function: idle */
			if(FLAME_condition_clan_idle_13_end(current_xmachine_clan_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: vocabulary_review */
			if(FLAME_condition_clan_vocabulary_review_13_end(current_xmachine_clan_holder->agent)==1)
			{ FLAME_debug_count++; }
			/*printf("FLAME_debug_count = %d\n", FLAME_debug_count);*/
			if(FLAME_debug_count != 1)
			{
				fprintf(stderr, "ERROR: A function condition test has failed for agent type 'clan' leaving state '13'\n");
				if(FLAME_debug_count > 1)
					fprintf(stderr, "\t reason: there was more than one possible outgoing transition function\n");
				if(FLAME_debug_count == 0)
					fprintf(stderr, "\t reason: there was no possible outgoing transition function\n");
			}
			
			current_xmachine_clan_holder = current_xmachine_clan_holder->next;
		}
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start idle\n");
	current_xmachine_clan_holder = clan_13_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		if(FLAME_condition_clan_idle_13_end(current_xmachine_clan)==1)
		{

		

			i = idle();

		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_13_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_13_state, clan_end_state);
			}
		}

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish idle\n");


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start vocabulary_review\n");
	current_xmachine_clan_holder = clan_13_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		current_xmachine_clan = current_xmachine_clan_holder->agent;
		current_xmachine_clan_next_state = clan_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_clan = current_xmachine_clan;

		if(FLAME_condition_clan_vocabulary_review_13_end(current_xmachine_clan)==1)
		{

		

			i = vocabulary_review();

		

			if(i == 1)
			{
				free_clan_agent(current_xmachine_clan_holder, clan_13_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_13_state, clan_end_state);
			}
		}

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish vocabulary_review\n");


/* End of layer number 26 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */



	/*printf("indv_end_state->count = %d\n", indv_end_state->count);*/
	indv_end_state->count = 0;

	/*printf("indv_13_state->count = %d\n", indv_13_state->count);*/
	indv_13_state->count = 0;

	/*printf("indv_12_state->count = %d\n", indv_12_state->count);*/
	indv_12_state->count = 0;

	/*printf("indv_11_state->count = %d\n", indv_11_state->count);*/
	indv_11_state->count = 0;

	/*printf("indv_10_state->count = %d\n", indv_10_state->count);*/
	indv_10_state->count = 0;

	/*printf("indv_08_state->count = %d\n", indv_08_state->count);*/
	indv_08_state->count = 0;

	/*printf("indv_07_state->count = %d\n", indv_07_state->count);*/
	indv_07_state->count = 0;

	/*printf("indv_09_state->count = %d\n", indv_09_state->count);*/
	indv_09_state->count = 0;

	/*printf("indv_05_state->count = %d\n", indv_05_state->count);*/
	indv_05_state->count = 0;

	/*printf("indv_06_state->count = %d\n", indv_06_state->count);*/
	indv_06_state->count = 0;

	/*printf("indv_04_state->count = %d\n", indv_04_state->count);*/
	indv_04_state->count = 0;

	/*printf("indv_03_state->count = %d\n", indv_03_state->count);*/
	indv_03_state->count = 0;

	/*printf("indv_02_state->count = %d\n", indv_02_state->count);*/
	indv_02_state->count = 0;

	/*printf("indv_01_state->count = %d\n", indv_01_state->count);*/
	indv_01_state->count = 0;

	/*printf("indv_start_state->count = %d\n", indv_start_state->count);*/
	indv_start_state->count = 0;

	/*printf("clan_end_state->count = %d\n", clan_end_state->count);*/
	clan_end_state->count = 0;

	/*printf("clan_13_state->count = %d\n", clan_13_state->count);*/
	clan_13_state->count = 0;

	/*printf("clan_12_state->count = %d\n", clan_12_state->count);*/
	clan_12_state->count = 0;

	/*printf("clan_11_state->count = %d\n", clan_11_state->count);*/
	clan_11_state->count = 0;

	/*printf("clan_10_state->count = %d\n", clan_10_state->count);*/
	clan_10_state->count = 0;

	/*printf("clan_09_state->count = %d\n", clan_09_state->count);*/
	clan_09_state->count = 0;

	/*printf("clan_08_state->count = %d\n", clan_08_state->count);*/
	clan_08_state->count = 0;

	/*printf("clan_07_state->count = %d\n", clan_07_state->count);*/
	clan_07_state->count = 0;

	/*printf("clan_06_state->count = %d\n", clan_06_state->count);*/
	clan_06_state->count = 0;

	/*printf("clan_05_state->count = %d\n", clan_05_state->count);*/
	clan_05_state->count = 0;

	/*printf("clan_04_state->count = %d\n", clan_04_state->count);*/
	clan_04_state->count = 0;

	/*printf("clan_03_state->count = %d\n", clan_03_state->count);*/
	clan_03_state->count = 0;

	/*printf("clan_02_state->count = %d\n", clan_02_state->count);*/
	clan_02_state->count = 0;

	/*printf("clan_01_state->count = %d\n", clan_01_state->count);*/
	clan_01_state->count = 0;

	/*printf("clan_start_state->count = %d\n", clan_start_state->count);*/
	clan_start_state->count = 0;

	/*printf("patch_end_state->count = %d\n", patch_end_state->count);*/
	patch_end_state->count = 0;

	/*printf("patch_5_state->count = %d\n", patch_5_state->count);*/
	patch_5_state->count = 0;

	/*printf("patch_4_state->count = %d\n", patch_4_state->count);*/
	patch_4_state->count = 0;

	/*printf("patch_3_state->count = %d\n", patch_3_state->count);*/
	patch_3_state->count = 0;

	/*printf("patch_2_state->count = %d\n", patch_2_state->count);*/
	patch_2_state->count = 0;

	/*printf("patch_1_state->count = %d\n", patch_1_state->count);*/
	patch_1_state->count = 0;

	/*printf("patch_start_state->count = %d\n", patch_start_state->count);*/
	patch_start_state->count = 0;

	/*printf("manada_guanacos_end_state->count = %d\n", manada_guanacos_end_state->count);*/
	manada_guanacos_end_state->count = 0;

	/*printf("manada_guanacos_3_state->count = %d\n", manada_guanacos_3_state->count);*/
	manada_guanacos_3_state->count = 0;

	/*printf("manada_guanacos_2_state->count = %d\n", manada_guanacos_2_state->count);*/
	manada_guanacos_2_state->count = 0;

	/*printf("manada_guanacos_1_state->count = %d\n", manada_guanacos_1_state->count);*/
	manada_guanacos_1_state->count = 0;

	/*printf("manada_guanacos_start_state->count = %d\n", manada_guanacos_start_state->count);*/
	manada_guanacos_start_state->count = 0;

	/* Move agents to their start states */

	current_xmachine_indv_holder = indv_end_state->agents;
	while(current_xmachine_indv_holder)
	{
		temp_xmachine_indv_holder = current_xmachine_indv_holder->next;
		transition_indv_agent(current_xmachine_indv_holder, indv_end_state, indv_start_state);

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}

	current_xmachine_clan_holder = clan_end_state->agents;
	while(current_xmachine_clan_holder)
	{
		temp_xmachine_clan_holder = current_xmachine_clan_holder->next;
		transition_clan_agent(current_xmachine_clan_holder, clan_end_state, clan_start_state);

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}

	current_xmachine_patch_holder = patch_end_state->agents;
	while(current_xmachine_patch_holder)
	{
		temp_xmachine_patch_holder = current_xmachine_patch_holder->next;
		transition_patch_agent(current_xmachine_patch_holder, patch_end_state, patch_start_state);

		current_xmachine_patch_holder = temp_xmachine_patch_holder;
	}

	current_xmachine_manada_guanacos_holder = manada_guanacos_end_state->agents;
	while(current_xmachine_manada_guanacos_holder)
	{
		temp_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
		transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_end_state, manada_guanacos_start_state);

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}

    if(iteration_loop%output_frequency == output_offset)
    {
        saveiterationdata(iteration_loop);
    }

		/* Calculate if any agents need to jump S.P. */
		/* propagate_agents(); */
	/* Save iteration time to log file */

		if((file = fopen(logfilepath, "a"))==NULL)
		{
			printf("Error: cannot open file '%s' for writing\n", logfilepath);
			exit(0);
		}
		(void)fputs("<iteration><no>", file);
		sprintf(data, "%i", iteration_loop);
		(void)fputs(data, file);
		(void)fputs("</no><time>", file);
		sprintf(data, "%d", (int)((get_time() - interval) * 1000) );
		(void)fputs(data, file);
		(void)fputs("</time></iteration>\n", file);
		(void)fclose(file);

	}

    

	/* Stop timing and print total time */
	stop = get_time();
	total_time = stop - start;
	printf("Execution time - %d:%02d:%03d [mins:secs:msecs]\n",
       (int)(total_time/60), ((int)total_time)%60, (((int)(total_time * 1000.0)) % 1000));

	clean_up(0);

	/* Exit successfully by returning zero to Operating System */
	return 0;
}
