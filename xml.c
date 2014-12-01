/**
 * \file  xml.c
 * \brief Holds xml reading and writing functions.
 */

#include "header.h"

/** \fn void read_int_static_array(char * buffer, int * j, int ** int_static_array)
 * \brief Reads integer static array.
 */
int read_int_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, int * int_static_array, int /*@unused@*/ size)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		if (arraycount < size) int_static_array[arraycount] = atoi(arraydata);
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	if (arraycount > size)
	{
				fprintf(stderr, "WARNING: %d 'int' values provided for static array of size %d. Surplus values ignored.\n",
				arraycount, size);
	}
	
	(*j)++;
	return 0;
}

/** \fn void read_float_static_array(char * buffer, int * (*j), int ** float_static_array)
 * \brief Reads float static array.
 */
int read_float_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, float * float_static_array, int /*@unused@*/ size)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		if (arraycount < size) float_static_array[arraycount] = (float)atof(arraydata);
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}
	
	if (arraycount > size)
	{
				fprintf(stderr, "WARNING: %d 'float' values provided for static array of size %d. Surplus values ignored.\n",
				arraycount, size);
	}
	
	(*j)++;
	return 0;
}

/** \fn void read_double_static_array(char * buffer, int * (*j), int ** double_static_array)
 * \brief Reads double static array.
 */
int read_double_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, double * double_static_array, int /*@unused@*/ size)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		if (arraycount < size) double_static_array[arraycount] = atof(arraydata);		
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	if (arraycount > size)
	{
		fprintf(stderr, "WARNING: %d 'double' values provided for static array of size %d. Surplus values ignored.\n",
				arraycount, size);
	}
	
	(*j)++;
	return 0;
}

/** \fn void read_char_static_array(char * buffer, int * (*j), int ** char_static_array)
 * \brief Reads char static array.
 */
int read_char_static_array(char * buffer, int /*@unused@*/ buffer_size, int * j, char * char_static_array, int size)
{
	int arraycount;
	
	while(buffer[(*j)] == ' ')
	{
		(*j)++;
	}
	
	for(arraycount = 0; arraycount < size; arraycount++)
	{
		char_static_array[arraycount] = buffer[(*j)];
		(*j)++;
	}

	//(*j)++;
	return 0;
}

/** \fn void read_int_dynamic_array(char * buffer, int * (*j), int ** int_dynamic_array)
 * \brief Reads integer dynamic array.
 */
int read_int_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, int_array * int_dynamic_array)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		add_int(int_dynamic_array, atoi(arraydata));
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	(*j)++;
	return 0;
}

/** \fn void read_float_dynamic_array(char * buffer, int * (*j), int ** float_dynamic_array)
 * \brief Reads float dynamic array.
 */
int read_float_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, float_array * float_dynamic_array)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		add_float(float_dynamic_array, (float)atof(arraydata));
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	(*j)++;
	return 0;
}

/** \fn void read_double_dynamic_array(char * buffer, int * (*j), int ** double_dynamic_array)
 * \brief Reads double dynamic array.
 */
int read_double_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, double_array * double_dynamic_array)
{
	int arraycount = 0;
	int array_k;
	char arraydata[100000];

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '}')
	{
		array_k = 0;
		while(buffer[(*j)] != ',' && buffer[(*j)] != '}')
		{
			if(buffer[(*j)] == '\0') return -1;
			arraydata[array_k] = buffer[(*j)];
			array_k++;
			(*j)++;
		}
		arraydata[array_k] = '\0';
		add_double(double_dynamic_array, atof(arraydata));
		arraycount++;
		if(buffer[(*j)] != '}') (*j)++;
	}

	(*j)++;
	return 0;
}

/** \fn void read_char_dynamic_array(char * buffer, int * (*j), int ** char_dynamic_array)
 * \brief Reads char dynamic array.
 */
int read_char_dynamic_array(char * buffer, int /*@unused@*/ buffer_size, int * j, char_array * char_dynamic_array)
{
	if(*j > buffer_size) return -1;
	
	while(buffer[(*j)] == ' ')
	{
		(*j)++;
	}
	
	while(buffer[(*j)] != '\0' && buffer[(*j)] != ',' && buffer[(*j)] != '}')
	{
		add_char(char_dynamic_array, buffer[(*j)]);
		(*j)++;
	}
	
	return 0;
}


/** \fn void read_members_needs(char * buffer, int * j, members_needs * temp_datatype)
 * \brief Reads members_needs datatype.
 */
int read_members_needs(char * buffer, int /*@unused@*/ buffer_size, int * j, members_needs * temp_datatype)
{
	
	int rc;
	
	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;


	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		while(buffer[*j] != '{') (*j)++;
		rc = read_int_static_array(buffer, buffer_size, j, (*temp_datatype).id_list, 100);
		if(rc != 0) { printf("Error: reading variable 'id_list' of type 'int'\n"); return -1; }
	}
	
	(*j)++;

	while(buffer[*j] != ',')
	{
		if(buffer[(*j)] == '\0') return -1;
		while(buffer[*j] != '{') (*j)++;
		rc = read_int_static_array(buffer, buffer_size, j, (*temp_datatype).cal_list, 100);
		if(rc != 0) { printf("Error: reading variable 'cal_list' of type 'int'\n"); return -1; }
	}
	
	(*j)++;

	while(buffer[*j] != '}')
	{
		if(buffer[(*j)] == '\0') return -1;
		while(buffer[*j] != '{') (*j)++;
		rc = read_int_static_array(buffer, buffer_size, j, (*temp_datatype).age, 100);
		if(rc != 0) { printf("Error: reading variable 'age' of type 'int'\n"); return -1; }
	}
	
	(*j)++;

	return 0;
}

int read_members_needs_dynamic_array(char * buffer, int buffer_size, int * j, members_needs_array * temp_datatype_array)
{
	int arraycount = 0;
	int rc;
	
	int id_list[100];
# ifndef S_SPLINT_S
	init_int_static_array(id_list, 100);
# endif
	
	int cal_list[100];
# ifndef S_SPLINT_S
	init_int_static_array(cal_list, 100);
# endif
	
	int age[100];
# ifndef S_SPLINT_S
	init_int_static_array(age, 100);
# endif
	

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	while(buffer[(*j)] != '\0' && buffer[(*j)] != '}')
	{
		if(buffer[(*j)] == '{')
		{
			add_members_needs(temp_datatype_array, id_list, cal_list, age);
			rc = read_members_needs(buffer, buffer_size, j, &(*temp_datatype_array).array[arraycount]);
			if(rc != 0) { printf("Error: reading variable 'members_needs' of type '\n"); return -1; }
			arraycount++;
			(*j)++;
		}
		while(buffer[(*j)] != '}' && buffer[(*j)] != '\0' && buffer[(*j)] != '{') { (*j)++; }
	}

	
	
	return 0;
}

int read_members_needs_static_array(char * buffer, int buffer_size, int * j, members_needs * temp_datatype_array, int size)
{
	int arraycount;
	int rc;

	while(buffer[(*j)] != '{')
	{
		if(buffer[(*j)] != ' ') return -1;
		else if(buffer[(*j)] == '\0') return -1;
		else (*j)++;
	}
	(*j)++;

	for(arraycount = 0; arraycount < size; arraycount++)
	{
		rc = read_members_needs(buffer, buffer_size, j, &temp_datatype_array[arraycount]);
		if(rc != 0) { printf("Error: reading variable 'members_needs' of type '\n"); return -1; }
		if(arraycount < (size-1)) while(buffer[(*j)] != '{') { (*j)++; }
	}

	(*j)++;
	return 0;
}



int readEnvironmentXML(char * location)
{
	FILE * file;
	char c = '\0';
	char buffer[100000];
	int index = 0;
	int in_environment = 0;
	int in_max_manada = 0;
	int in_max_familia = 0;
	int in_cal_adulto = 0;
	

	buffer[0] = '\0';

	/* Open file */
	if((file = fopen(location, "r"))==NULL)
	{
		printf("Error: cannot open import xml file '%s'\n", location);
		exit(0);
	}
	printf("Reading environment data from: %s\n", location);
	/* Keep reading file until EOF */
	while(c != (char)EOF)
	{
		/* Get the next char from the file */
		c = (char)fgetc(file);
		if(c == '>')
		{
			buffer[index] = '\0';
			if(strcmp(buffer, "environment") == 0) in_environment = 1;
			if(strcmp(buffer, "/environment") == 0) in_environment = 0;
			if(strcmp(buffer, "max_manada") == 0) in_max_manada = 1;
			if(strcmp(buffer, "/max_manada") == 0) in_max_manada = 0;
			if(strcmp(buffer, "max_familia") == 0) in_max_familia = 1;
			if(strcmp(buffer, "/max_familia") == 0) in_max_familia = 0;
			if(strcmp(buffer, "cal_adulto") == 0) in_cal_adulto = 1;
			if(strcmp(buffer, "/cal_adulto") == 0) in_cal_adulto = 0;
			
			index = 0;
			buffer[index] = '\0';
		}
		else if(c == '<')
		{
			buffer[index] = '\0';
			if(in_environment == 1)
			{
				if(in_max_manada == 1) { FLAME_environment_variable_max_manada = atoi(buffer); }
				if(in_max_familia == 1) { FLAME_environment_variable_max_familia = atoi(buffer); }
				if(in_cal_adulto == 1) { FLAME_environment_variable_cal_adulto = atoi(buffer); }
				
			}
			index = 0;
			buffer[index] = '\0';
		}
		else
		{
			buffer[index] = c;
			if(index < 999) index++;
		}
	}
	/* Close file */
	(void)fclose(file);

	return 0;
}

int readAgentXML(char * location,
				double cloud_data[],
				int partition_method,
				int flag,
				int number_partitions,
				int agent_count,
				int * itno)
{
	FILE * file;
	char c = '\0';
	char buffer[100000];
	char agentname[10000];
	int index = 0;
	int j; /* Index for reading arrays */
	int rc;
	int in_itno = 0;
	int FLAME_in_xagent = 0;
	int FLAME_in_name = 0;
	int in_indv_agent = 0;
	int in_clan_agent = 0;
	int in_patch_agent = 0;
	int in_manada_guanacos_agent = 0;
	
	int in_indvID = 0;
	int in_cID = 0;
	int in_cal_needs = 0;
	int in_icalories = 0;
	int in_patchID = 0;
	int in_age = 0;
	int in_sex = 0;
	int in_pregnant = 0;
	int in_lead = 0;
	int in_cal_need = 0;
	int in_cal_got = 0;
	int in_cal_stored = 0;
	int in_xcord = 0;
	int in_ycord = 0;
	int in_tcalories = 0;
	int in_leaderID = 0;
	int in_mneeds = 0;
	int in_pcalories = 0;
	int in_gcalories = 0;
	int in_repo = 0;
	int in_tpatch = 0;
	int in_repows = 0;
	int in_repods = 0;
	int in_season = 0;
	int in_adultos = 0;
	int in_familia = 0;
	int in_count = 0;
	int in_calorias = 0;
	
	xmachine_memory_indv * current_indv_agent = NULL;
	xmachine_memory_clan * current_clan_agent = NULL;
	xmachine_memory_patch * current_patch_agent = NULL;
	xmachine_memory_manada_guanacos * current_manada_guanacos_agent = NULL;
	
	/* Things for round-robin partitioning */
	int geometric = 1;
	int other = 2;
	double posx=0.0, posy=0.0, posz=0.0;

	j = 0;
	rc = 0;
	
	/* Use j and rc to stop compiler warnings if not used */
	if(j == 0 && rc == 0) {}
	
	agentname[0] = '\0';
	buffer[0] = '\0';

	/* Open file */
	if((file = fopen(location, "r"))==NULL)
	{
		printf("Error: cannot open import xml file '%s'\n", location);
		exit(0);
	}
	printf("Reading agent data from: %s\n", location);
	/* Keep reading file until EOF */
	while(c != (char)EOF)
	{
		/* Get the next char from the file */
		c = (char)fgetc(file);
		if(c == '>')
		{
			buffer[index] = '\0';
			if(strcmp(buffer, "itno") == 0) in_itno = 1;
			if(strcmp(buffer, "/itno") == 0) in_itno = 0;
			if(strcmp(buffer, "xagent") == 0)
			{
				FLAME_in_xagent = 1;
				agentname[0] = '\0';
			}
			if(strcmp(buffer, "/xagent") == 0)
			{	
				if(strcmp(agentname, "indv") == 0)
				{
					if(current_indv_agent == NULL) { printf("Memory error reading indv agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_indv_agent_internal(current_indv_agent, indv_start_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_indv_agent_internal(current_indv_agent, indv_start_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_indv_agent_internal(current_indv_agent, indv_start_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "clan") == 0)
				{
					if(current_clan_agent == NULL) { printf("Memory error reading clan agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_clan_agent_internal(current_clan_agent, clan_start_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_clan_agent_internal(current_clan_agent, clan_start_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_clan_agent_internal(current_clan_agent, clan_start_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "patch") == 0)
				{
					if(current_patch_agent == NULL) { printf("Memory error reading patch agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_patch_agent_internal(current_patch_agent, patch_start_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_patch_agent_internal(current_patch_agent, patch_start_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_patch_agent_internal(current_patch_agent, patch_start_state);
							}
							++agent_count;
						}
					}
				}
				else if(strcmp(agentname, "manada_guanacos") == 0)
				{
					if(current_manada_guanacos_agent == NULL) { printf("Memory error reading manada_guanacos agent\n"); exit(0); }
					
					posx = (double)0.0;
					posy = (double)0.0;
					posz = (double)0.0;
					
					/* If flag is zero just read the data. We'll partition later.
					 * If flag is not zero we aleady have partition data so can read and distribute to the current node.*/
					if( flag == 0 )
					{
						/* Next line should be commented out? */
						add_manada_guanacos_agent_internal(current_manada_guanacos_agent, manada_guanacos_start_state);

						/* Update the cloud data */
						if ( posx < cloud_data[0] ) cloud_data[0] = posx;
						if ( posx > cloud_data[1] ) cloud_data[1] = posx;
						if ( posy < cloud_data[2] ) cloud_data[2] = posy;
						if ( posy > cloud_data[3] ) cloud_data[3] = posy;
						if ( posz < cloud_data[2] ) cloud_data[4] = posz;
						if ( posz > cloud_data[3] ) cloud_data[5] = posz;
					}
					else
					{
						if(partition_method == geometric)
						{
							if (
								((current_node->partition_data[0] == SPINF) || (current_node->partition_data[0] != SPINF && posx >= current_node->partition_data[0])) &&
								((current_node->partition_data[1] == SPINF) || (current_node->partition_data[1] != SPINF && posx < current_node->partition_data[1])) &&
								((current_node->partition_data[2] == SPINF) || (current_node->partition_data[2] != SPINF && posy >= current_node->partition_data[2])) &&
								((current_node->partition_data[3] == SPINF) || (current_node->partition_data[3] != SPINF && posy < current_node->partition_data[3])) &&
								((current_node->partition_data[4] == SPINF) || (current_node->partition_data[4] != SPINF && posz >= current_node->partition_data[4])) &&
								((current_node->partition_data[5] == SPINF) || (current_node->partition_data[5] != SPINF && posz < current_node->partition_data[5]))
							)
							{
								add_manada_guanacos_agent_internal(current_manada_guanacos_agent, manada_guanacos_start_state);
							}
						}
						else if (partition_method == other)
						{
							if (agent_count % number_partitions == 0)
							{
								add_manada_guanacos_agent_internal(current_manada_guanacos_agent, manada_guanacos_start_state);
							}
							++agent_count;
						}
					}
				}
				else
				{
					printf("Warning: agent name undefined - '%s'\n", agentname);
					exit(0);
				}
				agentname[0] = '\0';
				FLAME_in_xagent = 0;
				in_indv_agent = 0;
				in_clan_agent = 0;
				in_patch_agent = 0;
				in_manada_guanacos_agent = 0;
				
			}
			if(strcmp(buffer, "name") == 0) FLAME_in_name = 1;
			if(strcmp(buffer, "/name") == 0) FLAME_in_name = 0;
			if(strcmp(buffer, "indvID") == 0) { in_indvID = 1; }
			if(strcmp(buffer, "/indvID") == 0) { in_indvID = 0; }
			if(strcmp(buffer, "cID") == 0) { in_cID = 1; }
			if(strcmp(buffer, "/cID") == 0) { in_cID = 0; }
			if(strcmp(buffer, "cal_needs") == 0) { in_cal_needs = 1; }
			if(strcmp(buffer, "/cal_needs") == 0) { in_cal_needs = 0; }
			if(strcmp(buffer, "icalories") == 0) { in_icalories = 1; }
			if(strcmp(buffer, "/icalories") == 0) { in_icalories = 0; }
			if(strcmp(buffer, "patchID") == 0) { in_patchID = 1; }
			if(strcmp(buffer, "/patchID") == 0) { in_patchID = 0; }
			if(strcmp(buffer, "age") == 0) { in_age = 1; }
			if(strcmp(buffer, "/age") == 0) { in_age = 0; }
			if(strcmp(buffer, "sex") == 0) { in_sex = 1; }
			if(strcmp(buffer, "/sex") == 0) { in_sex = 0; }
			if(strcmp(buffer, "pregnant") == 0) { in_pregnant = 1; }
			if(strcmp(buffer, "/pregnant") == 0) { in_pregnant = 0; }
			if(strcmp(buffer, "lead") == 0) { in_lead = 1; }
			if(strcmp(buffer, "/lead") == 0) { in_lead = 0; }
			if(strcmp(buffer, "cal_need") == 0) { in_cal_need = 1; }
			if(strcmp(buffer, "/cal_need") == 0) { in_cal_need = 0; }
			if(strcmp(buffer, "cal_got") == 0) { in_cal_got = 1; }
			if(strcmp(buffer, "/cal_got") == 0) { in_cal_got = 0; }
			if(strcmp(buffer, "cal_stored") == 0) { in_cal_stored = 1; }
			if(strcmp(buffer, "/cal_stored") == 0) { in_cal_stored = 0; }
			if(strcmp(buffer, "xcord") == 0) { in_xcord = 1; }
			if(strcmp(buffer, "/xcord") == 0) { in_xcord = 0; }
			if(strcmp(buffer, "ycord") == 0) { in_ycord = 1; }
			if(strcmp(buffer, "/ycord") == 0) { in_ycord = 0; }
			if(strcmp(buffer, "tcalories") == 0) { in_tcalories = 1; }
			if(strcmp(buffer, "/tcalories") == 0) { in_tcalories = 0; }
			if(strcmp(buffer, "leaderID") == 0) { in_leaderID = 1; }
			if(strcmp(buffer, "/leaderID") == 0) { in_leaderID = 0; }
			if(strcmp(buffer, "mneeds") == 0) { in_mneeds = 1; }
			if(strcmp(buffer, "/mneeds") == 0) { in_mneeds = 0; }
			if(strcmp(buffer, "pcalories") == 0) { in_pcalories = 1; }
			if(strcmp(buffer, "/pcalories") == 0) { in_pcalories = 0; }
			if(strcmp(buffer, "gcalories") == 0) { in_gcalories = 1; }
			if(strcmp(buffer, "/gcalories") == 0) { in_gcalories = 0; }
			if(strcmp(buffer, "repo") == 0) { in_repo = 1; }
			if(strcmp(buffer, "/repo") == 0) { in_repo = 0; }
			if(strcmp(buffer, "tpatch") == 0) { in_tpatch = 1; }
			if(strcmp(buffer, "/tpatch") == 0) { in_tpatch = 0; }
			if(strcmp(buffer, "repows") == 0) { in_repows = 1; }
			if(strcmp(buffer, "/repows") == 0) { in_repows = 0; }
			if(strcmp(buffer, "repods") == 0) { in_repods = 1; }
			if(strcmp(buffer, "/repods") == 0) { in_repods = 0; }
			if(strcmp(buffer, "season") == 0) { in_season = 1; }
			if(strcmp(buffer, "/season") == 0) { in_season = 0; }
			if(strcmp(buffer, "adultos") == 0) { in_adultos = 1; }
			if(strcmp(buffer, "/adultos") == 0) { in_adultos = 0; }
			if(strcmp(buffer, "familia") == 0) { in_familia = 1; }
			if(strcmp(buffer, "/familia") == 0) { in_familia = 0; }
			if(strcmp(buffer, "count") == 0) { in_count = 1; }
			if(strcmp(buffer, "/count") == 0) { in_count = 0; }
			if(strcmp(buffer, "calorias") == 0) { in_calorias = 1; }
			if(strcmp(buffer, "/calorias") == 0) { in_calorias = 0; }
			
			index = 0;
			buffer[index] = '\0';
		}
		else if(c == '<')
		{
			buffer[index] = '\0';
			
			if(in_itno && FLAME_in_xagent == 0) *itno = atoi(buffer);
			if(FLAME_in_xagent == 1)
			{
				if(FLAME_in_name == 1)
				{
					strcpy(agentname, buffer);

					if(strcmp(agentname, "indv") == 0)
					{
						current_indv_agent = init_indv_agent();
						in_indv_agent = 1;
					}
					else if(strcmp(agentname, "clan") == 0)
					{
						current_clan_agent = init_clan_agent();
						in_clan_agent = 1;
					}
					else if(strcmp(agentname, "patch") == 0)
					{
						current_patch_agent = init_patch_agent();
						in_patch_agent = 1;
					}
					else if(strcmp(agentname, "manada_guanacos") == 0)
					{
						current_manada_guanacos_agent = init_manada_guanacos_agent();
						in_manada_guanacos_agent = 1;
					}
					else
					{
						printf("Warning: agent name undefined - '%s'\n", agentname);
						exit(0);
					}
				}
				else if(in_indv_agent == 1)
				{
					if(in_indvID) { current_indv_agent->indvID = atoi(buffer); }
					if(in_cID) { current_indv_agent->cID = atoi(buffer); }
					if(in_cal_needs) { current_indv_agent->cal_needs = atoi(buffer); }
					if(in_icalories) { current_indv_agent->icalories = atoi(buffer); }
					if(in_patchID) { current_indv_agent->patchID = atoi(buffer); }
					if(in_age) { current_indv_agent->age = atoi(buffer); }
					if(in_sex) { current_indv_agent->sex = atoi(buffer); }
					if(in_pregnant) { current_indv_agent->pregnant = atoi(buffer); }
					if(in_lead) { current_indv_agent->lead = atoi(buffer); }
				 }else if(in_clan_agent == 1)
				{
					if(in_cID) { current_clan_agent->cID = atoi(buffer); }
					if(in_cal_need) { current_clan_agent->cal_need = atoi(buffer); }
					if(in_cal_got) { current_clan_agent->cal_got = atoi(buffer); }
					if(in_cal_stored) { current_clan_agent->cal_stored = atoi(buffer); }
					if(in_xcord) { current_clan_agent->xcord = atoi(buffer); }
					if(in_ycord) { current_clan_agent->ycord = atoi(buffer); }
					if(in_tcalories) { current_clan_agent->tcalories = atoi(buffer); }
					if(in_leaderID) { current_clan_agent->leaderID = atoi(buffer); }
					if(in_mneeds) { j = 0;
						rc = read_members_needs(buffer, index, &j, &current_clan_agent->mneeds);
						if(rc != 0) { printf("Error: reading 'clan' agent variable 'mneeds' of type 'members_needs'\n"); exit(0); } }
				 }else if(in_patch_agent == 1)
				{
					if(in_patchID) { current_patch_agent->patchID = atoi(buffer); }
					if(in_pcalories) { current_patch_agent->pcalories = atoi(buffer); }
					if(in_gcalories) { current_patch_agent->gcalories = atoi(buffer); }
					if(in_repo) { current_patch_agent->repo = atof(buffer); }
					if(in_tpatch) { current_patch_agent->tpatch = atoi(buffer); }
					if(in_xcord) { current_patch_agent->xcord = atoi(buffer); }
					if(in_ycord) { current_patch_agent->ycord = atoi(buffer); }
					if(in_repows) { current_patch_agent->repows = atof(buffer); }
					if(in_repods) { current_patch_agent->repods = atof(buffer); }
					if(in_season) { current_patch_agent->season = atoi(buffer); }
					if(in_adultos) { current_patch_agent->adultos = atoi(buffer); }
				 }else if(in_manada_guanacos_agent == 1)
				{
					if(in_familia) { current_manada_guanacos_agent->familia = atoi(buffer); }
					if(in_xcord) { current_manada_guanacos_agent->xcord = atoi(buffer); }
					if(in_ycord) { current_manada_guanacos_agent->ycord = atoi(buffer); }
					if(in_count) { current_manada_guanacos_agent->count = atoi(buffer); }
					if(in_calorias) { current_manada_guanacos_agent->calorias = atoi(buffer); }
					if(in_adultos) { current_manada_guanacos_agent->adultos = atoi(buffer); }
				 }
			}
			index = 0;
			buffer[index] = '\0';
		}
		else
		{
			buffer[index] = c;
			if(index < 99999) index++;
			else
			{
				printf("Error: agent reading buffer too small\n");
				printf("%s\n", buffer);
				exit(0);
			}
		}
	}
	/* Close file */
	(void)fclose(file);

	return 0;
}

/** \fn void check_location_exists(char * location)
 * \brief Check that a directory exists.
 * \param location The directory location to check.
 */
int check_location_exists(char * location)
{
	/* Save a dummy file to directory and remove.
	 * This checks directory exists and is writable */
	FILE * file;
	char * buffer;

	buffer = (char *)malloc( (strlen(location) + strlen("dummy.temp") + 1) * sizeof(char));
	strcpy(buffer, location);
	strcat(buffer, "dummy.temp");

	if((file = fopen(buffer, "w")) == NULL) return 0;

	(void)fclose(file);
	/* Remove dummy file */
	remove(buffer);

	return 1;
}


/** \fn void readinitialstates(char * filename, int * itno, xmachine ** agent_list, double cloud_data[6], int flag)
 * \brief Read initial X-machine memory starting values from a file.
 * \param filename The path to the file.
 * \param filelocation The directory of the location
 * \param itno Pointer to the iteration number.
 * \param agent_list List of agents in the model to be constructed by this function.
 * \param cloud_data Max and min x,y,z coordinates of agents.
 * \param partition_method Identifies partitioning method: 1 = geometric, 2 = round-robin
 * \param flag Flag for whether to check space partitions.
 */
void readinitialstates(char * filename, char * filelocation, int * itno, double cloud_data[],
					   int partition_method, int flag)
{
	/* Pointer to file */
	FILE *file;
	/* Char and char buffer for reading file to */
	char c = '\0';
	char buffer[100000];
	char FLAME_location[10000];
	char FLAME_format[10000];
	char FLAME_type[10000];
	FLAME_output * current_FLAME_output = NULL;

	/* Things for round-robin partitioning */
	int agent_count = 0;
	int number_partitions = 0;
	int geometric=1;
	int other=2;
	

	/* Cloud data array initialisation */
	# ifndef S_SPLINT_S
	cloud_data[0] = SPINF;
	cloud_data[1] = -SPINF;
	cloud_data[2] = SPINF;
	cloud_data[3] = -SPINF;
	cloud_data[4] = SPINF;
	cloud_data[5] = -SPINF;
	# endif

	/* Temporary node and head of associated agent list to allow adding agents */
	node_information temp_node;

	/* Pointer to x-memory for initial state data */
	/*xmachine * current_xmachine;*/
	/* Variables for checking tags */
	int reading = 1;
	int i = 0;
	int rc;
	int in_tag = 0;
	int in_itno = 0;
	int FLAME_in_imports = 0;
	int FLAME_in_import = 0;
	int FLAME_in_outputs = 0;
	int FLAME_in_output = 0;
	int FLAME_in_location = 0;
	int FLAME_in_format = 0;
	int FLAME_in_type = 0;
	int FLAME_in_time = 0;
	int FLAME_in_period = 0;
	int FLAME_in_phase = 0;
	int FLAME_in_name = 0;

	/* Initialise environment vars */
	FLAME_environment_variable_max_manada = 0;
	FLAME_environment_variable_max_familia = 0;
	FLAME_environment_variable_cal_adulto = 0;
	

	/* Open config file to read-only */
	if((file = fopen(filename, "r"))==NULL)
	{
		printf("Error: opening initial states '%s'\n", filename);
		exit(0);
	}
	
	/* Initialise variables */
    *itno = 0;





	if(partition_method==geometric) printf("xml: Geometric partitioning\n");
	else if(partition_method==other) printf("xml: Round-robin partitioning\n");
	else printf("xml: Error - invalid partitioning method\n");


	/* Set p_xmachine to the agent list passed in then new agents are added to this list
	 * Will be set to agent list for specific node is space partitions are already known (flag=1)
	 */
	/* If we're reading without knowing partitions already then use the dummy current node (it's not in the list of nodes)*/
	if (flag == 0) current_node = &temp_node;

	printf("Reading initial data file: %s\n", filename);
	/* Read file until end of xml */
	while(reading==1)
	{
		/* Get the next char from the file */
		c = (char)fgetc(file);

		/* If the end of a tag */
		if(c == '>')
		{
			/* Place 0 at end of buffer to make chars a string */
			buffer[i] = 0;

			if(strcmp(buffer, "states") == 0) reading = 1;
			if(strcmp(buffer, "/states") == 0) reading = 0;
			if(strcmp(buffer, "itno") == 0) in_itno = 1;
			if(strcmp(buffer, "/itno") == 0) in_itno = 0;
			if(strcmp(buffer, "imports") == 0) FLAME_in_imports = 1;
			if(strcmp(buffer, "/imports") == 0) FLAME_in_imports = 0;
			if(strcmp(buffer, "import") == 0)
			{
				/*FLAME_location[0] = '\0';*/
				strcpy(FLAME_location, filelocation);
				FLAME_format[0] = '\0';
				FLAME_type[0] = '\0';

				FLAME_in_import = 1;
			}
			if(strcmp(buffer, "/import") == 0)
			{
				if(strcmp("agent", FLAME_type) == 0 || strcmp("environment", FLAME_type) == 0)
				{
					if(strcmp("xml", FLAME_format) == 0)
					{
						if(strcmp("agent", FLAME_type) == 0) readAgentXML(FLAME_location, cloud_data, partition_method, flag, number_partitions, agent_count, itno);
						if(strcmp("environment", FLAME_type) == 0) readEnvironmentXML(FLAME_location);
					}
					else
					{
						printf("Error: import format '%s' is unsupported\n", FLAME_format);
						exit(0);
					}
				}
				else
				{
					printf("Error: import type '%s' is not agent or environment\n", FLAME_type);
					exit(0);
				}

				FLAME_in_import = 0;
			}
			if(strcmp(buffer, "location") == 0) FLAME_in_location = 1;
			if(strcmp(buffer, "/location") == 0) FLAME_in_location = 0;
			if(strcmp(buffer, "format") == 0) FLAME_in_format = 1;
			if(strcmp(buffer, "/format") == 0) FLAME_in_format = 0;
			if(strcmp(buffer, "type") == 0) FLAME_in_type = 1;
			if(strcmp(buffer, "/type") == 0) FLAME_in_type = 0;
			if(strcmp(buffer, "outputs") == 0) FLAME_in_outputs = 1;
			if(strcmp(buffer, "/outputs") == 0) FLAME_in_outputs = 0;
			if(strcmp(buffer, "output") == 0)
			{
				if(FLAME_in_outputs == 1)
				{
					current_FLAME_output = add_FLAME_output(&FLAME_outputs);
	
					FLAME_in_output = 1;
				}
			}
			if(strcmp(buffer, "/output") == 0)
			{
				if(FLAME_in_outputs == 1)
				{
					if(current_FLAME_output->type == -1)
					{
						printf("Error: an output type has not been set\n");
						exit(0);
					}
					if(current_FLAME_output->format == -1)
					{
						printf("Error: an output format has not been set\n");
						exit(0);
					}
					if(current_FLAME_output->location == NULL)
					{
						printf("Error: an output location has not been set\n");
						exit(0);
					}
					/* If type is xml check if location exists */
					if(current_FLAME_output->type == 0)
					{
						rc = check_location_exists(current_FLAME_output->location);
						if(rc == 0)
						{
							printf("Error: location directory '%s' does not exist\n", current_FLAME_output->location);
							exit(0);
						}
					}
					/* Period has to be larger than 0 */
					if(current_FLAME_output->period < 1)
					{
						printf("Error: output period is less than 1: '%d'\n", current_FLAME_output->period);
						exit(0);
					}
					/* Phase cannot be equal or larger than period */
					if(current_FLAME_output->phase >= current_FLAME_output->period)
					{
						printf("Error: output phase is more or equal to period: '%d'\n", current_FLAME_output->phase);
						exit(0);
					}
	
					FLAME_in_output = 0;
				}
			}
			if(strcmp(buffer, "time") == 0) FLAME_in_time = 1;
			if(strcmp(buffer, "/time") == 0) FLAME_in_time = 0;
			if(strcmp(buffer, "period") == 0) FLAME_in_period = 1;
			if(strcmp(buffer, "/period") == 0) FLAME_in_period = 0;
			if(strcmp(buffer, "phase") == 0) FLAME_in_phase = 1;
			if(strcmp(buffer, "/phase") == 0) FLAME_in_phase = 0;
			if(strcmp(buffer, "name") == 0) FLAME_in_name = 1;
			if(strcmp(buffer, "/name") == 0) FLAME_in_name = 0;

			/* End of tag and reset buffer */
			in_tag = 0;
			i = 0;
		}
		/* If start of tag */
		else if(c == '<')
		{
			/* Place /0 at end of buffer to end numbers */
			buffer[i] = 0;
			/* Flag in tag */
			in_tag = 1;

			if(in_itno) *itno = atoi(buffer);
			if(FLAME_in_imports == 1)
			{
				if(FLAME_in_import == 1)
				{
					if(FLAME_in_location == 1) strcat(FLAME_location, buffer);
					if(FLAME_in_format == 1) strcpy(FLAME_format, buffer);
					if(FLAME_in_type == 1) strcpy(FLAME_type, buffer);
				}
			}
			if(FLAME_in_outputs == 1)
			{
				if(FLAME_in_output == 1)
				{
					if(FLAME_in_type == 1)
					{
						if(strcmp("snapshot", buffer) == 0) current_FLAME_output->type = 0;
						else if(strcmp("agent", buffer) != 0)
						{
							printf("Error: output type is not 'snapshot' or an 'agent': '%s'\n", buffer);
							exit(0);
						}
					}
					if(FLAME_in_name == 1)
					{
						if(strcmp("indv", buffer) == 0) current_FLAME_output->type = 1;
						else if(strcmp("clan", buffer) == 0) current_FLAME_output->type = 2;
						else if(strcmp("patch", buffer) == 0) current_FLAME_output->type = 3;
						else if(strcmp("manada_guanacos", buffer) == 0) current_FLAME_output->type = 4;
						else 
						{
							printf("Error: output name is not an agent name: '%s'\n", buffer);
							exit(0);
						}
					}
					if(FLAME_in_format == 1)
					{
						if(strcmp("xml", buffer) == 0) current_FLAME_output->format = 0;
						else
						{
							printf("Error: output format is unsupported: '%s'\n", buffer);
							exit(0);
						}
					}
					if(FLAME_in_location == 1)
					{
						current_FLAME_output->location = (char *)malloc( (strlen(filelocation) + strlen(buffer) + 1) * sizeof(char));
						strcpy(current_FLAME_output->location, filelocation);
						strcat(current_FLAME_output->location, buffer);
					}
					if(FLAME_in_time == 1)
					{
						if(FLAME_in_period == 1) current_FLAME_output->period = atoi(buffer);
						if(FLAME_in_phase == 1)  current_FLAME_output->phase = atoi(buffer);
					}
				}
			}
			/* Reset buffer */
			i = 0;
		}
		/* If in tag put read char into buffer */
		else if(in_tag == 1)
		{
			buffer[i] = c;
			i++;
		}
		/* If in data read char into buffer */
		else
		{
			buffer[i] = c;
			i++;
		}
	}

	/* Close the file */
	(void)fclose(file);

	/* Also try and read environment and agents from 0.xml */
	readEnvironmentXML(filename);
	readAgentXML(filename, cloud_data, partition_method, flag, number_partitions, agent_count, itno);

	/* If outputs is empty add default snapshot for every iteration */
	if(FLAME_outputs == NULL)
	{
		current_FLAME_output = add_FLAME_output(&FLAME_outputs);
		current_FLAME_output->type   = 0; /* snapshot */
		current_FLAME_output->format = 0; /* xml */
		current_FLAME_output->location = (char *)malloc( (strlen(filelocation) +  1) * sizeof(char));
		strcpy(current_FLAME_output->location, filelocation); /* location = 0.xml location */
		current_FLAME_output->period = 1; /* every iteration */
		current_FLAME_output->phase  = 0; /* no phase */
	}
	
	/* Print output settings to CLI */
	for(current_FLAME_output = FLAME_outputs; current_FLAME_output != NULL; current_FLAME_output = current_FLAME_output->next)
	{
		printf("output: type='");
		if(current_FLAME_output->type == 0) printf("snapshot");
		else if(current_FLAME_output->type == 1) printf("agent' name='indv");
		else if(current_FLAME_output->type == 2) printf("agent' name='clan");
		else if(current_FLAME_output->type == 3) printf("agent' name='patch");
		else if(current_FLAME_output->type == 4) printf("agent' name='manada_guanacos");
		else printf("undefined");
		printf("' format='");
		if(current_FLAME_output->format == 0) printf("xml");
		else printf("undefined");
		printf("' location='%s'", current_FLAME_output->location);
		printf(" period='%d' phase='%d'\n", current_FLAME_output->period, current_FLAME_output->phase);
	}

	/* Make sure cloud data makes sense if any of x,y,z coords were all the same */
	if ( partition_method == geometric ) {
		if ( cloud_data[0] == cloud_data[1] ) {
			cloud_data[0] = -SPINF;
			cloud_data[1] = SPINF;
		}
		if ( cloud_data[2] == cloud_data[3] ) {
			cloud_data[2] = -SPINF;
			cloud_data[3] = SPINF;
		}
		if ( cloud_data[4] == cloud_data[5] ) {
			cloud_data[4] = -SPINF;
			cloud_data[5] = SPINF;
		}
	}
}

/** \fn void write_int_static_array(FILE *file, $name * temp)
 * \brief Writes int.
 */
void write_int_static_array(FILE *file, int * temp, int size)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%i", temp[i]);
		fputs(data, file);
		if(i < size-1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_float_static_array(FILE *file, float * temp)
 * \brief Writes float.
 */
void write_float_static_array(FILE *file, float * temp, int size)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%f", temp[i]);
		fputs(data, file);
		if(i < size-1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_double_static_array(FILE *file, double * temp)
 * \brief Writes double.
 */
void write_double_static_array(FILE *file, double * temp, int size)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%f", temp[i]);
		fputs(data, file);
		if(i < size-1) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_char_static_array(FILE *file, char * temp)
 * \brief Writes char.
 */
void write_char_static_array(FILE *file, char * temp, int size)
{
	int i;
	char data[1000];

	//fputs("{", file);
	for(i=0; i<size; i++)
	{
		sprintf(data, "%c", temp[i]);
		fputs(data, file);
		//if(i < size-1) fputs(", ", file);
	}
	//fputs("}", file);
}

/** \fn void write_int_dynamic_array(FILE *file, int_array* temp)
 * \brief Writes int.
 */
void write_int_dynamic_array(FILE *file, int_array * temp)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%i", (*temp).array[i]);
		fputs(data, file);
		if(i < ((*temp).size-1)) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_float_dynamic_array(FILE *file, float_array* temp)
 * \brief Writes float.
 */
void write_float_dynamic_array(FILE *file, float_array * temp)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%f", (*temp).array[i]);
		fputs(data, file);
		if(i < ((*temp).size-1)) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_double_dynamic_array(FILE *file, double_array* temp)
 * \brief Writes double.
 */
void write_double_dynamic_array(FILE *file, double_array * temp)
{
	int i;
	char data[1000];

	fputs("{", file);
	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%f", (*temp).array[i]);
		fputs(data, file);
		if(i < ((*temp).size-1)) fputs(", ", file);
	}
	fputs("}", file);
}

/** \fn void write_char_dynamic_array(FILE *file, char_array* temp)
 * \brief Writes char.
 */
void write_char_dynamic_array(FILE *file, char_array * temp)
{
	int i;
	char data[1000];

	for(i=0; i<(*temp).size; i++)
	{
		sprintf(data, "%c", (*temp).array[i]);
		fputs(data, file);
	}
}

/** \fn void write_members_needs(FILE *file, members_needs * temp_datatype)
 * \brief Writes members_needs datatype.
 */
void write_members_needs(FILE *file, members_needs * temp_datatype)
{
	

	fputs("{", file);
	write_int_static_array(file, (*temp_datatype).id_list, 100);
	fputs(", ", file);	write_int_static_array(file, (*temp_datatype).cal_list, 100);
	fputs(", ", file);	write_int_static_array(file, (*temp_datatype).age, 100);
	fputs("}", file);
}

void write_members_needs_static_array(FILE *file, members_needs * temp_datatype, int size)
{
	int i;

	fputs("{", file);
	for(i = 0; i < size; i++)
	{
		write_members_needs(file, &temp_datatype[i]);

		if(i < size - 1) fputs(", ", file);
	}
	fputs("}", file);
}

void write_members_needs_dynamic_array(FILE *file, members_needs_array * temp_datatype)
{
	int i;

	fputs("{", file);
	for(i = 0; i < (*temp_datatype).size; i++)
	{
		write_members_needs(file, &(*temp_datatype).array[i]);

		if(i < (*temp_datatype).size - 1) fputs(", ", file);
	}
	fputs("}", file);
}



void write_indv_agent(FILE *file, xmachine_memory_indv * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>indv</name>\n", file);
		fputs("<indvID>", file);
	sprintf(data, "%i", current->indvID);
	fputs(data, file);
	fputs("</indvID>\n", file);
		fputs("<cID>", file);
	sprintf(data, "%i", current->cID);
	fputs(data, file);
	fputs("</cID>\n", file);
		fputs("<cal_needs>", file);
	sprintf(data, "%i", current->cal_needs);
	fputs(data, file);
	fputs("</cal_needs>\n", file);
		fputs("<icalories>", file);
	sprintf(data, "%i", current->icalories);
	fputs(data, file);
	fputs("</icalories>\n", file);
		fputs("<patchID>", file);
	sprintf(data, "%i", current->patchID);
	fputs(data, file);
	fputs("</patchID>\n", file);
		fputs("<age>", file);
	sprintf(data, "%i", current->age);
	fputs(data, file);
	fputs("</age>\n", file);
		fputs("<sex>", file);
	sprintf(data, "%i", current->sex);
	fputs(data, file);
	fputs("</sex>\n", file);
		fputs("<pregnant>", file);
	sprintf(data, "%i", current->pregnant);
	fputs(data, file);
	fputs("</pregnant>\n", file);
		fputs("<lead>", file);
	sprintf(data, "%i", current->lead);
	fputs(data, file);
	fputs("</lead>\n", file);

	fputs("</xagent>\n", file);
}

void write_clan_agent(FILE *file, xmachine_memory_clan * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>clan</name>\n", file);
		fputs("<cID>", file);
	sprintf(data, "%i", current->cID);
	fputs(data, file);
	fputs("</cID>\n", file);
		fputs("<cal_need>", file);
	sprintf(data, "%i", current->cal_need);
	fputs(data, file);
	fputs("</cal_need>\n", file);
		fputs("<cal_got>", file);
	sprintf(data, "%i", current->cal_got);
	fputs(data, file);
	fputs("</cal_got>\n", file);
		fputs("<cal_stored>", file);
	sprintf(data, "%i", current->cal_stored);
	fputs(data, file);
	fputs("</cal_stored>\n", file);
		fputs("<xcord>", file);
	sprintf(data, "%i", current->xcord);
	fputs(data, file);
	fputs("</xcord>\n", file);
		fputs("<ycord>", file);
	sprintf(data, "%i", current->ycord);
	fputs(data, file);
	fputs("</ycord>\n", file);
		fputs("<tcalories>", file);
	sprintf(data, "%i", current->tcalories);
	fputs(data, file);
	fputs("</tcalories>\n", file);
		fputs("<leaderID>", file);
	sprintf(data, "%i", current->leaderID);
	fputs(data, file);
	fputs("</leaderID>\n", file);
		fputs("<mneeds>", file);
	write_members_needs(file, &current->mneeds);
	fputs("</mneeds>\n", file);

	fputs("</xagent>\n", file);
}

void write_patch_agent(FILE *file, xmachine_memory_patch * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>patch</name>\n", file);
		fputs("<patchID>", file);
	sprintf(data, "%i", current->patchID);
	fputs(data, file);
	fputs("</patchID>\n", file);
		fputs("<pcalories>", file);
	sprintf(data, "%i", current->pcalories);
	fputs(data, file);
	fputs("</pcalories>\n", file);
		fputs("<gcalories>", file);
	sprintf(data, "%i", current->gcalories);
	fputs(data, file);
	fputs("</gcalories>\n", file);
		fputs("<repo>", file);
	sprintf(data, "%f", current->repo);
	fputs(data, file);
	fputs("</repo>\n", file);
		fputs("<tpatch>", file);
	sprintf(data, "%i", current->tpatch);
	fputs(data, file);
	fputs("</tpatch>\n", file);
		fputs("<xcord>", file);
	sprintf(data, "%i", current->xcord);
	fputs(data, file);
	fputs("</xcord>\n", file);
		fputs("<ycord>", file);
	sprintf(data, "%i", current->ycord);
	fputs(data, file);
	fputs("</ycord>\n", file);
		fputs("<repows>", file);
	sprintf(data, "%f", current->repows);
	fputs(data, file);
	fputs("</repows>\n", file);
		fputs("<repods>", file);
	sprintf(data, "%f", current->repods);
	fputs(data, file);
	fputs("</repods>\n", file);
		fputs("<season>", file);
	sprintf(data, "%i", current->season);
	fputs(data, file);
	fputs("</season>\n", file);
		fputs("<adultos>", file);
	sprintf(data, "%i", current->adultos);
	fputs(data, file);
	fputs("</adultos>\n", file);

	fputs("</xagent>\n", file);
}

void write_manada_guanacos_agent(FILE *file, xmachine_memory_manada_guanacos * current)
{
	char data[1000];
	fputs("<xagent>\n" , file);
	fputs("<name>manada_guanacos</name>\n", file);
		fputs("<familia>", file);
	sprintf(data, "%i", current->familia);
	fputs(data, file);
	fputs("</familia>\n", file);
		fputs("<xcord>", file);
	sprintf(data, "%i", current->xcord);
	fputs(data, file);
	fputs("</xcord>\n", file);
		fputs("<ycord>", file);
	sprintf(data, "%i", current->ycord);
	fputs(data, file);
	fputs("</ycord>\n", file);
		fputs("<count>", file);
	sprintf(data, "%i", current->count);
	fputs(data, file);
	fputs("</count>\n", file);
		fputs("<calorias>", file);
	sprintf(data, "%i", current->calorias);
	fputs(data, file);
	fputs("</calorias>\n", file);
		fputs("<adultos>", file);
	sprintf(data, "%i", current->adultos);
	fputs(data, file);
	fputs("</adultos>\n", file);

	fputs("</xagent>\n", file);
}


void FLAME_write_xml(char * location, int iteration_number, int * output_types, int output_type_size)
{
	/* Pointer to file */
	FILE *file;
	char data[1000];
	
		sprintf(data, "%s%i.xml", location, iteration_number);
	
	if((file = fopen(data, "w"))==NULL)
	{
		printf("Error: cannot open file '%s' for writing\n", data);
		exit(0);
	}
	
	
	fputs("<states>\n", file);
	if(FLAME_integer_in_array(0, output_types, output_type_size))
	{
		fputs("<itno>", file);
		sprintf(data, "%i", iteration_number);
		fputs(data, file);
		fputs("</itno>\n", file);
		fputs("<environment>\n" , file);
			fputs("<max_manada>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_manada);
		fputs(data, file);
		fputs("</max_manada>\n", file);
			fputs("<max_familia>", file);
		sprintf(data, "%i", FLAME_environment_variable_max_familia);
		fputs(data, file);
		fputs("</max_familia>\n", file);
			fputs("<cal_adulto>", file);
		sprintf(data, "%i", FLAME_environment_variable_cal_adulto);
		fputs(data, file);
		fputs("</cal_adulto>\n", file);
			fputs("</environment>\n" , file);
	}
	
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(1, output_types, output_type_size))
	{
		current_xmachine_indv_holder = indv_start_state->agents;
			while(current_xmachine_indv_holder)
			{
				write_indv_agent(file, current_xmachine_indv_holder->agent);

				current_xmachine_indv_holder = current_xmachine_indv_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(2, output_types, output_type_size))
	{
		current_xmachine_clan_holder = clan_start_state->agents;
			while(current_xmachine_clan_holder)
			{
				write_clan_agent(file, current_xmachine_clan_holder->agent);

				current_xmachine_clan_holder = current_xmachine_clan_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(3, output_types, output_type_size))
	{
		current_xmachine_patch_holder = patch_start_state->agents;
			while(current_xmachine_patch_holder)
			{
				write_patch_agent(file, current_xmachine_patch_holder->agent);

				current_xmachine_patch_holder = current_xmachine_patch_holder->next;
			}
	}
	
	if(FLAME_integer_in_array(0, output_types, output_type_size) || FLAME_integer_in_array(4, output_types, output_type_size))
	{
		current_xmachine_manada_guanacos_holder = manada_guanacos_start_state->agents;
			while(current_xmachine_manada_guanacos_holder)
			{
				write_manada_guanacos_agent(file, current_xmachine_manada_guanacos_holder->agent);

				current_xmachine_manada_guanacos_holder = current_xmachine_manada_guanacos_holder->next;
			}
	}
	
	fputs("</states>\n" , file);

	/* Close the file */
	(void)fclose(file);
}

/** \fn void saveiterationdata(int iteration_number)
 * \brief Save X-machine memory to a file.
 * \param iteration_number The current iteration number.
 */
void saveiterationdata(int iteration_number)
{
	FLAME_output * current_FLAME_output;
	FLAME_output * current_FLAME_output2;
	int output_types[1000];
	int output_type_size = 0;

	/* For each output */
	for(current_FLAME_output = FLAME_outputs; current_FLAME_output != NULL; current_FLAME_output = current_FLAME_output->next)
	{
		/* If period/phase equates to current iteration */
		if(iteration_number%current_FLAME_output->period == current_FLAME_output->phase)
		{
			/* If output has already been handled */
			if(current_FLAME_output->flag == 0)
			{
				/* Check snapshot */
				if(current_FLAME_output->type == 0)
				{
					//snapshot_location = current_FLAME_output->location;
					output_types[0] = 0;
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, 1);
					/* Set flag to 1 and every output to same location */
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							current_FLAME_output2->flag = 1;
						}
					}
				}
				if(current_FLAME_output->type == 1)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 1;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 2)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 2;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 3)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 3;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}if(current_FLAME_output->type == 4)
				{
					/* Reinitialise agent size */
					output_type_size = 0;
					output_types[0] = 4;
					
					current_FLAME_output->flag = 1;
					for(current_FLAME_output2 = FLAME_outputs; current_FLAME_output2 != NULL; current_FLAME_output2 = current_FLAME_output2->next)
					{
						if(current_FLAME_output2->flag == 0 && strcmp(current_FLAME_output->location, current_FLAME_output2->location) == 0)
						{
							output_types[++output_type_size] = current_FLAME_output2->type;
							
							current_FLAME_output2->flag = 1;
						}
					}
					
					FLAME_write_xml(current_FLAME_output->location, iteration_number, output_types, output_type_size);
				}
			}
		}
	}
	/* Set flags back to 0 */
	for(current_FLAME_output = FLAME_outputs; current_FLAME_output != NULL; current_FLAME_output = current_FLAME_output->next)
	{
		current_FLAME_output->flag = 0;
	}
}
