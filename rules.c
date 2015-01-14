/**
 * \file rules.c
 * \brief Functions created from tagged condition and filter rules.
 */

#include "header.h"

/** \fn int FLAME_integer_in_array(int a, int * b, int size)
 * \brief Returns 1 if an integer is a member of an integer array, else 0
 * \param a The integer to check.
 * \param b Pointer to the integer array.
 * \param size The size of the array
 * \return 1 for true, 0 for false.
 */
int FLAME_integer_in_array(int a, int * b, int size)
{
	int i;
	
	for(i = 0; i < size; i++)
	{
		if(a == b[i]) return 1;
	}
	
	return 0;
}

/** \fn void* cparams_create(int agent_number, int * agent_count, size_t * agent_struct_size, size_t * cparam_size)
 * \brief Create memory to hold agent filter variables for every agent using the filter on the current node.
 * \param agent_number The number of agent types.
 * \param agent_count List of the number of agents of each agent type.
 * \param agent_struct_size The struct size needed for each agent type.
 * \param cparam_size The size of the memory created.
 * \return Pointer to the created memory.
 */
void* cparams_create(int agent_number, int * agent_count, size_t * agent_struct_size, size_t * cparam_size)
{
	/* Pointer to the memory created that is going to be returned */
	void *data;
	/* Variable used in for loops */
	int i;
	/* Variable to hold total size of memory required for agent structures */
	size_t total_param_size = 0;

	/* For each agent type add required memory for agent structures */
	for(i = 0; i < agent_number; i++)
	{
		total_param_size += agent_count[i] * agent_struct_size[i];
	}

	//assert(count > 0);
	//assert(total_param_size > 0);
	/* Does libmboard free this memory? */
	
	/* Allocate required memory, where memory holds the number
	 * of each agent type, in order, and the total required
	 * memory for agent structures */
	data = malloc(agent_number*sizeof(int) + total_param_size);
	/* Make the memory size parameter equal to the actual memory size */
	*cparam_size = agent_number*sizeof(int) + total_param_size;
	/* Assert that the created memory was successfully created and not null */
	assert(data != NULL);

	/* Return the pointer to the created memory */
	return data;
}


/** \fn int FLAME_condition_indv_getolder_02_03(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_getolder_02_03(xmachine_memory_indv *a)
{
	if((iteration_loop%30 == 29)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_indv_02_03(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_indv_02_03(xmachine_memory_indv *a)
{
	if(!(iteration_loop%30 == 29)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_freeIndv_03_04(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_freeIndv_03_04(xmachine_memory_indv *a)
{
	if((((a->marriable == 1) && (a->married == 0)) && (a->widow == 0))) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_03_06(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_03_06(xmachine_memory_indv *a)
{
	if(!(((a->marriable == 1) && (a->married == 0)) && (a->widow == 0))) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_casamiento_female_04_05(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_casamiento_female_04_05(xmachine_memory_indv *a)
{
	if((a->sex == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_casamiento_male_04_06(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_casamiento_male_04_06(xmachine_memory_indv *a)
{
	if((a->sex == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_info_husband_05_06(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_info_husband_05_06(xmachine_memory_indv *a)
{
	if((a->married == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_05_06(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_05_06(xmachine_memory_indv *a)
{
	if(!(a->married == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_pregnancy_06_09(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_pregnancy_06_09(xmachine_memory_indv *a)
{
	if((a->embarazable == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_06_07(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_06_07(xmachine_memory_indv *a)
{
	if(!(a->embarazable == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_child_inf_07_08(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_child_inf_07_08(xmachine_memory_indv *a)
{
	if((a->month == 9)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_07_09(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_07_09(xmachine_memory_indv *a)
{
	if(!(a->month == 9)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_husband_request_11_12(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_husband_request_11_12(xmachine_memory_indv *a)
{
	if((a->widow == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_11_12(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_11_12(xmachine_memory_indv *a)
{
	if(!(a->widow == 1)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_local_marriage_12_13(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_local_marriage_12_13(xmachine_memory_indv *a)
{
	if((a->married == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_indv_idle_12_13(xmachine_memory_indv *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_indv_idle_12_13(xmachine_memory_indv *a)
{
	if(!(a->married == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_clan_dividir_clan_11_12(xmachine_memory_clan *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_clan_dividir_clan_11_12(xmachine_memory_clan *a)
{
	if((a->members >= 10)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_clan_idle_11_13(xmachine_memory_clan *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_clan_idle_11_13(xmachine_memory_clan *a)
{
	if(!(a->members >= 10)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_clan_vocabulary_review_13_end(xmachine_memory_clan *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_clan_vocabulary_review_13_end(xmachine_memory_clan *a)
{
	if((iteration_loop%360 == 348)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_clan_idle_13_end(xmachine_memory_clan *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_clan_idle_13_end(xmachine_memory_clan *a)
{
	if(!(iteration_loop%360 == 348)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_regenerate_2_3(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_regenerate_2_3(xmachine_memory_patch *a)
{
	if((iteration_loop%7 == 6)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_idle_patch_2_3(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_idle_patch_2_3(xmachine_memory_patch *a)
{
	if(!(iteration_loop%7 == 6)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_snregenerate_3_4(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_snregenerate_3_4(xmachine_memory_patch *a)
{
	if((iteration_loop%180 == 6)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_idle_patch_3_4(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_idle_patch_3_4(xmachine_memory_patch *a)
{
	if(!(iteration_loop%180 == 6)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_reproduccion_guanacos_5_end(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_reproduccion_guanacos_5_end(xmachine_memory_patch *a)
{
	if((iteration_loop%360 == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_idle_patch_5_end(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_idle_patch_5_end(xmachine_memory_patch *a)
{
	if(!(iteration_loop%360 == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_manada_guanacos_manada_idle_1_2(xmachine_memory_manada_guanacos *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_manada_guanacos_manada_idle_1_2(xmachine_memory_manada_guanacos *a)
{
	if(!(iteration_loop%10 == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_manada_guanacos_move_1_2(xmachine_memory_manada_guanacos *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_manada_guanacos_move_1_2(xmachine_memory_manada_guanacos *a)
{
	if((iteration_loop%10 == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_manada_guanacos_reproduccion_2_end(xmachine_memory_manada_guanacos *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_manada_guanacos_reproduccion_2_end(xmachine_memory_manada_guanacos *a)
{
	if((iteration_loop%360 == 0)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_manada_guanacos_manada_idle2_2_end(xmachine_memory_manada_guanacos *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_manada_guanacos_manada_idle2_2_end(xmachine_memory_manada_guanacos *a)
{
	if(!(iteration_loop%360 == 0)) return 1;
	else return 0;
}



/** \fn int FLAME_filter_indv_extractcalories_01_02_indgetcalories(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_extractcalories_01_02_indgetcalories(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_extractcalories_01_02_indgetcalories(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_indgetcalories *m = (m_indgetcalories*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if((a->indvID == m->indvID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_casamiento_female_04_05_marriage(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_casamiento_female_04_05_marriage(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_casamiento_female_04_05_marriage(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_marriage *m = (m_marriage*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if(((a->indvID == m->girlID) && (a->cID == m->oclanID))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_casamiento_male_04_06_marriage(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_casamiento_male_04_06_marriage(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_casamiento_male_04_06_marriage(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_marriage *m = (m_marriage*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if(((a->indvID == m->manID) && (a->cID == m->clanID))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_info_husband_05_06_family(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_info_husband_05_06_family(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_info_husband_05_06_family(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_family *m = (m_family*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if(((a->indvID == m->wife) && (a->cID == m->clanID))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_birth_08_09_respuestaID(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_birth_08_09_respuestaID(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_birth_08_09_respuestaID(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_respuestaID *m = (m_respuestaID*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if(((a->indvID == m->indvID) && (a->cID == m->clanID))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_update_status_10_11_death(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_update_status_10_11_death(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_update_status_10_11_death(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_death *m = (m_death*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if(((a->indvID == m->parejaID) && (a->cID == m->clanID))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_local_marriage_12_13_lmarriage(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_local_marriage_12_13_lmarriage(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_local_marriage_12_13_lmarriage(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_lmarriage *m = (m_lmarriage*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if((((a->indvID == m->girlID) || (a->indvID == m->manID)) && (a->cID == m->clanID))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_indv_dividir_info_13_end_warningDivide(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_indv_dividir_info_13_end_warningDivide(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_indv_dividir_info_13_end_warningDivide(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_warningDivide *m = (m_warningDivide*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_indv *a = (xmachine_memory_indv *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_clan_Information_start_01_information(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_clan_Information_start_01_information(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_clan_Information_start_01_information(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_information *m = (m_information*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_clan_extract_calories_01_02_clangetcalories(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_clan_extract_calories_01_02_clangetcalories(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_clan_extract_calories_01_02_clangetcalories(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_clangetcalories *m = (m_clangetcalories*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->cID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_marriable_indv_03_04_ancestor(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_marriable_indv_03_04_ancestor(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_marriable_indv_03_04_ancestor(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_ancestor *m = (m_ancestor*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_aceptar_prop_06_07_propuesta(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_aceptar_prop_06_07_propuesta(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_aceptar_prop_06_07_propuesta(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_propuesta *m = (m_propuesta*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->dclanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_recive_conf_07_08_confirProp(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_recive_conf_07_08_confirProp(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_recive_conf_07_08_confirProp(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_confirProp *m = (m_confirProp*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_repartir_id_08_09_peticionID(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_repartir_id_08_09_peticionID(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_repartir_id_08_09_peticionID(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_peticionID *m = (m_peticionID*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_new_leader_09_10_leader(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_new_leader_09_10_leader(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_new_leader_09_10_leader(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_leader *m = (m_leader*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_again_marriable_10_11_widow(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_again_marriable_10_11_widow(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_again_marriable_10_11_widow(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_widow *m = (m_widow*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_clan_creacion_clan_12_13_informationDivide(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_creacion_clan_12_13_informationDivide(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_creacion_clan_12_13_informationDivide(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_informationDivide *m = (m_informationDivide*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_clan *a = (xmachine_memory_clan *)params;

	/* The filter */
	if((a->cID == m->clanID)) return 1;
	else return 0;
}

/** \fn int FLAME_filter_patch_patchcalories_1_2_clan_info(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_patch_patchcalories_1_2_clan_info(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_patch_patchcalories_1_2_clan_info(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_clan_info *m = (m_clan_info*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_patch *a = (xmachine_memory_patch *)params;

	/* The filter */
	if(((a->xcord == m->px) && (a->ycord == m->py))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_patch_guanacos_move_4_5_adultospatch(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_patch_guanacos_move_4_5_adultospatch(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_patch_guanacos_move_4_5_adultospatch(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_adultospatch *m = (m_adultospatch*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_patch *a = (xmachine_memory_patch *)params;

	/* The filter */
	if(((a->xcord == m->xcord) && (a->ycord == m->ycord))) return 1;
	else return 0;
}

/** \fn int FLAME_filter_patch_reproduccion_guanacos_5_end_reproduccionguanacos(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_patch_reproduccion_guanacos_5_end_reproduccionguanacos(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_patch_reproduccion_guanacos_5_end_reproduccionguanacos(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_reproduccionguanacos *m = (m_reproduccionguanacos*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_patch *a = (xmachine_memory_patch *)params;

	/* The filter */
	if(((a->xcord == m->xcord) && (a->ycord == m->ycord))) return 1;
	else return 0;
}


int FLAME_sort_clan_creacion_clan_12_13_informationDivide(const void *x, const void *y)
{
	if( ((m_informationDivide *)x)->age > ((m_informationDivide *)y)->age ) return -1;
	else if( ((m_informationDivide *)x)->age < ((m_informationDivide *)y)->age ) return 1;
	else return 0;
}

