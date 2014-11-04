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
	int FLAME_clan_info_message_board_write;
	int FLAME_clan_info_message_board_read;
	int FLAME_clangetcalories_message_board_write;
	int FLAME_clangetcalories_message_board_read;
	int FLAME_calguanacos_message_board_write;
	int FLAME_calguanacos_message_board_read;

	/* Particle cloud data */
	double cloud_data[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
	/* Count to debug function branches */
	int FLAME_debug_count;

/* For partition method. Makes geometric (-g flag) the default but may be overridden with -r for round-robin */
	int partition_method=1;



	/* Output frequency is 1 as default */
	output_frequency = 1;
	/* Set random seed */
/*	srand(time(NULL)); */

	

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
	FLAME_calguanacos_message_board_write = 0;
	FLAME_calguanacos_message_board_read = 0;
	/* Sending agents */
	if(manada_guanacos_start_state->agents != NULL) FLAME_calguanacos_message_board_write = 1;
	
	/* Reading agents */
	if(patch_start_state->agents != NULL) FLAME_calguanacos_message_board_read = 1;
	
	/* Call message board library with details */
	if(FLAME_calguanacos_message_board_write == 0 &&
		FLAME_calguanacos_message_board_read == 0)
			rc = MB_SetAccessMode(b_calguanacos, MB_MODE_IDLE);
	if(FLAME_calguanacos_message_board_write == 1 &&
		FLAME_calguanacos_message_board_read == 0)
			rc = MB_SetAccessMode(b_calguanacos, MB_MODE_WRITEONLY);
	if(FLAME_calguanacos_message_board_write == 0 &&
		FLAME_calguanacos_message_board_read == 1)
			rc = MB_SetAccessMode(b_calguanacos, MB_MODE_READONLY);
	if(FLAME_calguanacos_message_board_write == 1 &&
		FLAME_calguanacos_message_board_read == 1)
			rc = MB_SetAccessMode(b_calguanacos, MB_MODE_READWRITE);
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not set access mode of 'calguanacos' board\n");
	   switch(rc) {
		   case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
			   break;
		   case MB_ERR_LOCKED:
			   fprintf(stderr, "\t reason: 'calguanacos' board is locked\n");
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
		if(FLAME_calguanacos_message_board_write == 0)
		{
			/*printf("%d> calguanacos message board sync start early as no agents sending any messages of this type\n", node_number);*/
			
			/* ********** sync message board here **********  */
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_calguanacos)\n");
			rc = MB_SyncStart(b_calguanacos);
			if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_calguanacos)\n");
			#ifdef ERRCHECK
			if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not start sync of 'calguanacos' board\n");
			   switch(rc) {
				   case MB_ERR_INVALID:
					   fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
					   break;
				   case MB_ERR_LOCKED:
					   fprintf(stderr, "\t reason: 'calguanacos' board is locked\n");
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

		

		

			i = manadaInfo();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_start_state, manada_guanacos_1_state);
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

		

		

			i = patchtype();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_start_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_start_state, patch_1_state);
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

		

			i = move();

		

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


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start post_calorias\n");
	current_xmachine_manada_guanacos_holder = manada_guanacos_2_state->agents;
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

		

		

			i = post_calorias();

		

			if(i == 1)
			{
				free_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state);
			}
			else
			{
				transition_manada_guanacos_agent(current_xmachine_manada_guanacos_holder, manada_guanacos_2_state, manada_guanacos_end_state);
			}
		

		current_xmachine_manada_guanacos = NULL;

		current_xmachine_manada_guanacos_holder = temp_xmachine_manada_guanacos_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish post_calorias\n");

	if(FLAME_calguanacos_message_board_write == 1)
	{

		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncStart(b_calguanacos)\n");
		rc = MB_SyncStart(b_calguanacos);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finish MB_SyncStart(b_calguanacos)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not start sync of 'calguanacos' board\n");
		   switch(rc) {
			   case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
				   break;
			   case MB_ERR_LOCKED:
				   fprintf(stderr, "\t reason: 'calguanacos' board is locked\n");
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


	/* If mb is not read then leave sync complete until last possible moment */
	if(FLAME_calguanacos_message_board_read == 1)
	{
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_calguanacos)\n");
		rc = MB_SyncComplete(b_calguanacos);
		if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_calguanacos)\n");
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not complete sync of 'calguanacos' board\n");
		   switch(rc) {
				case MB_ERR_INVALID:
				   fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
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

		

		
		
          
                  
          
		    rc = MB_Iterator_CreateFiltered(b_calguanacos, &i_calguanacos, &FLAME_filter_patch_regenerate_2_3_calguanacos, current_xmachine_patch);
		    
		  
		
		#ifdef ERRCHECK
		if (rc != MB_SUCCESS)
		{
		   fprintf(stderr, "ERROR: Could not create Iterator for 'calguanacos'\n");
		   switch(rc) {
		       case MB_ERR_INVALID:
		           fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
		           break;
		       case MB_ERR_LOCKED:
	               fprintf(stderr, "\t reason: 'calguanacos' board is locked\n");
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
		
		

			i = regenerate();

		
		    rc = MB_Iterator_Delete(&i_calguanacos);
		    #ifdef ERRCHECK
		    if (rc != MB_SUCCESS)
		    {
		       fprintf(stderr, "ERROR: Could not delete 'calguanacos' iterator\n");
		       switch(rc) {
		           case MB_ERR_INVALID:
		               fprintf(stderr, "\t reason: 'calguanacos' iterator is invalid\n");
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
				free_patch_agent(current_xmachine_patch_holder, patch_2_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_2_state, patch_3_state);
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

if(FLAME_calguanacos_message_board_read == 0)
{
	/*printf("%d> calguanacos message board sync complete late as no agents reading any messages of this type\n", node_number);*/
	
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("start MB_SyncComplete(b_calguanacos)\n");
	rc = MB_SyncComplete(b_calguanacos);
	if(FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS) printf("finsh MB_SyncComplete(b_calguanacos)\n");
	#ifdef ERRCHECK
	if (rc != MB_SUCCESS)
	{
	   fprintf(stderr, "ERROR: Could not complete sync of 'calguanacos' board\n");
	   switch(rc) {
			case MB_ERR_INVALID:
			   fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
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

    rc = MB_Clear(b_calguanacos);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not clear 'calguanacos' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'calguanacos' board is invalid\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'calguanacos' board is locked\n");
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
			if(FLAME_condition_patch_idle_patch_3_end(current_xmachine_patch_holder->agent)==1)
			{ FLAME_debug_count++; }
			/* Function: snregenerate */
			if(FLAME_condition_patch_snregenerate_3_end(current_xmachine_patch_holder->agent)==1)
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
		current_xmachine_patch_next_state = patch_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_idle_patch_3_end(current_xmachine_patch)==1)
		{

		

			i = idle_patch();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_3_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_3_state, patch_end_state);
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
		current_xmachine_patch_next_state = patch_end_state;
		/* For backwards compatibility set current_xmachine */
		current_xmachine->xmachine_indv = NULL;
		current_xmachine->xmachine_clan = NULL;
		current_xmachine->xmachine_patch = NULL;
		current_xmachine->xmachine_manada_guanacos = NULL;
		current_xmachine->xmachine_patch = current_xmachine_patch;

		if(FLAME_condition_patch_snregenerate_3_end(current_xmachine_patch)==1)
		{

		

			i = snregenerate();

		

			if(i == 1)
			{
				free_patch_agent(current_xmachine_patch_holder, patch_3_state);
			}
			else
			{
				transition_patch_agent(current_xmachine_patch_holder, patch_3_state, patch_end_state);
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


/* End of layer number 6 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */


	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("start survive\n");
	current_xmachine_indv_holder = indv_03_state->agents;
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

		

		

			i = survive();

		

			if(i == 1)
			{
				free_indv_agent(current_xmachine_indv_holder, indv_03_state);
			}
			else
			{
				transition_indv_agent(current_xmachine_indv_holder, indv_03_state, indv_end_state);
			}
		

		current_xmachine_indv = NULL;

		current_xmachine_indv_holder = temp_xmachine_indv_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish survive\n");

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
    


/* End of layer number 7 */

/* Clear message boards that have finished being used
 * and sync complete if doing late sync complete */


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
	current_xmachine_clan_holder = clan_03_state->agents;
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
				free_clan_agent(current_xmachine_clan_holder, clan_03_state);
			}
			else
			{
				transition_clan_agent(current_xmachine_clan_holder, clan_03_state, clan_end_state);
			}
		

		current_xmachine_clan = NULL;

		current_xmachine_clan_holder = temp_xmachine_clan_holder;
	}
	if(FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS) printf("finish new_leader\n");


/* End of layer number 8 */

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



	/*printf("indv_end_state->count = %d\n", indv_end_state->count);*/
	indv_end_state->count = 0;

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
