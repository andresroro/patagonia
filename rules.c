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


/** \fn int FLAME_condition_patch_snregenerate_3_end(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_snregenerate_3_end(xmachine_memory_patch *a)
{
	if((iteration_loop%180 == 6)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_patch_idle_patch_3_end(xmachine_memory_patch *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_patch_idle_patch_3_end(xmachine_memory_patch *a)
{
	if(!(iteration_loop%180 == 6)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_manada_guanacos_manada_idle_1_2(xmachine_memory_manada_guanacos *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_manada_guanacos_manada_idle_1_2(xmachine_memory_manada_guanacos *a)
{
	if(!(iteration_loop%10 == 10)) return 1;
	else return 0;
}


/** \fn int FLAME_condition_manada_guanacos_move_1_2(xmachine_memory_manada_guanacos *a)
 * \brief The condition function for an agent function.
 * \param a The agent memory.
 * \return The success (1) or failure (0) of the condition.
 */
int FLAME_condition_manada_guanacos_move_1_2(xmachine_memory_manada_guanacos *a)
{
	if((iteration_loop%10 == 10)) return 1;
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

/** \fn int FLAME_filter_clan_new_leader_03_end_leader(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_clan_new_leader_03_end_leader(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_clan_new_leader_03_end_leader(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_leader *m = (m_leader*)msg;
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

/** \fn int FLAME_filter_patch_regenerate_2_3_calguanacos(const void *msg, const void *params)
 * \brief The filter function for a message input used in serial for each agent.
 * \param msg The pointer to the message to be filtered.
 * \param params The pointer to the agent memory.
 * \return The success (1) or failure (0) of the filter on the message.
 */
int FLAME_filter_patch_regenerate_2_3_calguanacos(const void *msg, const void *params)
{
	//printf("**** FLAME_filter_patch_regenerate_2_3_calguanacos(const void *msg, const void *params)\n");
	
	/* Cast the message pointer to the correct message type */
	m_calguanacos *m = (m_calguanacos*)msg;
	/* Cast the params pointer to the correct agent type */
	xmachine_memory_patch *a = (xmachine_memory_patch *)params;

	/* The filter */
	if(((a->xcord == m->xcord) && (a->ycord == m->ycord))) return 1;
	else return 0;
}



