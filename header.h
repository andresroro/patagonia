/**
 * \file  header.h
 * \brief Header for xmachine data structures and transition functions.
 */
#ifndef _HEADER_H
#define _HEADER_H

#ifdef _DEBUG_MODE
    #define ERRCHECK
#else
    #define NDEBUG
#endif

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "mboard.h"

#define FLAME_TEST_PRINT_START_AND_END_OF_MODEL_FUNCTIONS 0
#define FLAME_TEST_PRINT_START_AND_END_OF_LIBMBOARD_CALLS 0
#define FLAME_USE_FILTERS_IN_SYNC 1


/* Checking macros */
#ifdef CHECK_MEMORY
#define CHECK_POINTER(PT) if(PT==NULL){printf("**** ERROR in Memory check 1\n");exit(1);}
#else
#define CHECK_POINTER(PT)
#endif


/** \def MAX_MANADA
 * \brief Provide access to environment variables in uppercase. */
#define MAX_MANADA (FLAME_get_environment_variable_max_manada())
/** \def MAX_FAMILIA
 * \brief Provide access to environment variables in uppercase. */
#define MAX_FAMILIA (FLAME_get_environment_variable_max_familia())
/** \def CAL_ADULTO
 * \brief Provide access to environment variables in uppercase. */
#define CAL_ADULTO (FLAME_get_environment_variable_cal_adulto())
/** \def ARRAY_BLOCK_SIZE
 * \brief The block size to allocate to dynamic arrays. */
#define ARRAY_BLOCK_SIZE 10
/** \def ARRAY_GROWTH_RATE
 * \brief Growth ratio to scale size of dynamic arrays. 
 * Use golden ratio. This makes for a Fibonacci sequence, so the next allocation size 
 * is the sum of the current size and the previous size thus improving the chance of 
 * memory block reuse. It also allows for moderate rate of growth.
 */
#define ARRAY_GROWTH_RATE 1.618034
/** \def START_INFORMATION_MESSAGE_LOOP
 * \brief Start of loop to process information messages. */
#define START_INFORMATION_MESSAGE_LOOP  for(information_message = get_first_information_message(); information_message != NULL; information_message = get_next_information_message(information_message)) {
/** \def FINISH_INFORMATION_MESSAGE_LOOP
 * \brief Finish of loop to process information messages. */
#define FINISH_INFORMATION_MESSAGE_LOOP }
/** \def START_INDGETCALORIES_MESSAGE_LOOP
 * \brief Start of loop to process indgetcalories messages. */
#define START_INDGETCALORIES_MESSAGE_LOOP  for(indgetcalories_message = get_first_indgetcalories_message(); indgetcalories_message != NULL; indgetcalories_message = get_next_indgetcalories_message(indgetcalories_message)) {
/** \def FINISH_INDGETCALORIES_MESSAGE_LOOP
 * \brief Finish of loop to process indgetcalories messages. */
#define FINISH_INDGETCALORIES_MESSAGE_LOOP }
/** \def START_LEADER_MESSAGE_LOOP
 * \brief Start of loop to process leader messages. */
#define START_LEADER_MESSAGE_LOOP  for(leader_message = get_first_leader_message(); leader_message != NULL; leader_message = get_next_leader_message(leader_message)) {
/** \def FINISH_LEADER_MESSAGE_LOOP
 * \brief Finish of loop to process leader messages. */
#define FINISH_LEADER_MESSAGE_LOOP }
/** \def START_CLAN_INFO_MESSAGE_LOOP
 * \brief Start of loop to process clan_info messages. */
#define START_CLAN_INFO_MESSAGE_LOOP  for(clan_info_message = get_first_clan_info_message(); clan_info_message != NULL; clan_info_message = get_next_clan_info_message(clan_info_message)) {
/** \def FINISH_CLAN_INFO_MESSAGE_LOOP
 * \brief Finish of loop to process clan_info messages. */
#define FINISH_CLAN_INFO_MESSAGE_LOOP }
/** \def START_CLANGETCALORIES_MESSAGE_LOOP
 * \brief Start of loop to process clangetcalories messages. */
#define START_CLANGETCALORIES_MESSAGE_LOOP  for(clangetcalories_message = get_first_clangetcalories_message(); clangetcalories_message != NULL; clangetcalories_message = get_next_clangetcalories_message(clangetcalories_message)) {
/** \def FINISH_CLANGETCALORIES_MESSAGE_LOOP
 * \brief Finish of loop to process clangetcalories messages. */
#define FINISH_CLANGETCALORIES_MESSAGE_LOOP }
/** \def START_CALGUANACOS_MESSAGE_LOOP
 * \brief Start of loop to process calguanacos messages. */
#define START_CALGUANACOS_MESSAGE_LOOP  for(calguanacos_message = get_first_calguanacos_message(); calguanacos_message != NULL; calguanacos_message = get_next_calguanacos_message(calguanacos_message)) {
/** \def FINISH_CALGUANACOS_MESSAGE_LOOP
 * \brief Finish of loop to process calguanacos messages. */
#define FINISH_CALGUANACOS_MESSAGE_LOOP }


struct FLAME_output
{
	int type; /* 0=snapshot 1=indv 2=clan 3=patch 4=manada_guanacos */
	int format; /* 0=XML */
	char * location;
	int period;
	int phase;
	int flag; /* Used when outputting to show it has been used */

	struct FLAME_output * next;
};
typedef struct FLAME_output FLAME_output;

/** \struct int_array
 * \brief Dynamic array to hold integers.
 *
 * Holds a pointer to an integer array and values for size and memory size.
 */
struct int_array
{
	int size;
	int total_size;

	int * array;
};

/** \struct float_array
 * \brief Dynamic array to hold floats.
 *
 * Holds a pointer to an float array and values for size and memory size.
 */
struct float_array
{
	int size;
	int total_size;

	float * array;
};

/** \struct double_array
 * \brief Dynamic array to hold doubles.
 *
 * Holds a pointer to a double array and values for size and memory size.
 */
struct double_array
{
	int size;
	int total_size;

	double * array;
};

/** \struct char_array
 * \brief Dynamic array to hold chars.
 *
 * Holds a pointer to a char array and values for size and memory size.
 */
struct char_array
{
	int size;
	int total_size;

	char * array;
};

/** \typedef struct int_array int_array
 * \brief Typedef for int_array struct.
 */
typedef struct int_array int_array;
/** \typedef struct float_array float_array
 * \brief Typedef for float_array struct.
 */
typedef struct float_array float_array;
/** \typedef struct double_array double_array
 * \brief Typedef for double_array struct.
 */
typedef struct double_array double_array;
/** \typedef struct char_array char_array
 * \brief Typedef for char_array struct.
 */
typedef struct char_array char_array;

/** \struct members_needs
 * \brief Structure to remember how many calories each member of the clan needs to survive.
 *
 * Structure to remember how many calories each member of the clan needs to survive.
 */
struct members_needs
{
	int id_list[100];	/**< Datatype memory variable id_list of type int. */
	int cal_list[100];	/**< Datatype memory variable cal_list of type int. */
	int age[100];	/**< Datatype memory variable age of type int. */
};

/** \struct members_needs_array
 * \brief Dynamic array to hold members_needss
 */
struct members_needs_array
{
	int size;
	int total_size;

	struct members_needs * array;
};

/** \var typedef members_needs members_needs
 * \brief Typedef for members_needs struct.
 */
typedef struct members_needs members_needs;
/** \var typedef members_needs_array members_needs_array
 * \brief Typedef for members_needs_array struct.
 */
typedef struct members_needs_array members_needs_array;

/** \struct xmachine_memory_indv
 * \brief Holds memory of xmachine indv.
 */
struct xmachine_memory_indv
{
	int indvID;	/**< X-machine memory variable indvID of type int. */
	int cID;	/**< X-machine memory variable cID of type int. */
	int cal_needs;	/**< X-machine memory variable cal_needs of type int. */
	int icalories;	/**< X-machine memory variable icalories of type int. */
	int patchID;	/**< X-machine memory variable patchID of type int. */
	int age;	/**< X-machine memory variable age of type int. */
	int sex;	/**< X-machine memory variable sex of type int. */
	int pregnant;	/**< X-machine memory variable pregnant of type int. */
	int lead;	/**< X-machine memory variable lead of type int. */
};

/** \struct xmachine_memory_indv_holder
 * \brief Holds struct of memory of xmachine indv.
 */
struct xmachine_memory_indv_holder
{
	/*@dependent@*/ struct xmachine_memory_indv * agent;	/**< Pointer to X-machine memory indv. */

	/*@dependent@*/ struct xmachine_memory_indv_holder * prev;	/**< Pointer to previous indv agent in the list.  */
	/*@dependent@*/ struct xmachine_memory_indv_holder * next;	/**< Pointer to next indv agent in the list.  */
};

/** \struct xmachine_memory_indv_holder
 * \brief Holds struct of memory of xmachine indv.
 */
struct xmachine_memory_indv_state
{
	/*@dependent@*/ struct xmachine_memory_indv_holder * agents;	/**< Pointer to X-machine memory indv. */

	int count;	/**< Number of agents that were in this state.  */
};

/** \struct xmachine_memory_clan
 * \brief Holds memory of xmachine clan.
 */
struct xmachine_memory_clan
{
	int cID;	/**< X-machine memory variable cID of type int. */
	int cal_need;	/**< X-machine memory variable cal_need of type int. */
	int cal_got;	/**< X-machine memory variable cal_got of type int. */
	int cal_stored;	/**< X-machine memory variable cal_stored of type int. */
	int xcord;	/**< X-machine memory variable xcord of type int. */
	int ycord;	/**< X-machine memory variable ycord of type int. */
	int tcalories;	/**< X-machine memory variable tcalories of type int. */
	int leaderID;	/**< X-machine memory variable leaderID of type int. */
	members_needs mneeds;	/**< X-machine memory variable mneeds of type members_needs. */
};

/** \struct xmachine_memory_clan_holder
 * \brief Holds struct of memory of xmachine clan.
 */
struct xmachine_memory_clan_holder
{
	/*@dependent@*/ struct xmachine_memory_clan * agent;	/**< Pointer to X-machine memory clan. */

	/*@dependent@*/ struct xmachine_memory_clan_holder * prev;	/**< Pointer to previous clan agent in the list.  */
	/*@dependent@*/ struct xmachine_memory_clan_holder * next;	/**< Pointer to next clan agent in the list.  */
};

/** \struct xmachine_memory_clan_holder
 * \brief Holds struct of memory of xmachine clan.
 */
struct xmachine_memory_clan_state
{
	/*@dependent@*/ struct xmachine_memory_clan_holder * agents;	/**< Pointer to X-machine memory clan. */

	int count;	/**< Number of agents that were in this state.  */
};

/** \struct xmachine_memory_patch
 * \brief Holds memory of xmachine patch.
 */
struct xmachine_memory_patch
{
	int patchID;	/**< X-machine memory variable patchID of type int. */
	int pcalories;	/**< X-machine memory variable pcalories of type int. */
	float repo;	/**< X-machine memory variable repo of type float. */
	int tpatch;	/**< X-machine memory variable tpatch of type int. */
	int xcord;	/**< X-machine memory variable xcord of type int. */
	int ycord;	/**< X-machine memory variable ycord of type int. */
	float repows;	/**< X-machine memory variable repows of type float. */
	float repods;	/**< X-machine memory variable repods of type float. */
	int season;	/**< X-machine memory variable season of type int. */
};

/** \struct xmachine_memory_patch_holder
 * \brief Holds struct of memory of xmachine patch.
 */
struct xmachine_memory_patch_holder
{
	/*@dependent@*/ struct xmachine_memory_patch * agent;	/**< Pointer to X-machine memory patch. */

	/*@dependent@*/ struct xmachine_memory_patch_holder * prev;	/**< Pointer to previous patch agent in the list.  */
	/*@dependent@*/ struct xmachine_memory_patch_holder * next;	/**< Pointer to next patch agent in the list.  */
};

/** \struct xmachine_memory_patch_holder
 * \brief Holds struct of memory of xmachine patch.
 */
struct xmachine_memory_patch_state
{
	/*@dependent@*/ struct xmachine_memory_patch_holder * agents;	/**< Pointer to X-machine memory patch. */

	int count;	/**< Number of agents that were in this state.  */
};

/** \struct xmachine_memory_manada_guanacos
 * \brief Holds memory of xmachine manada_guanacos.
 */
struct xmachine_memory_manada_guanacos
{
	int id;	/**< X-machine memory variable id of type int. */
	int familia;	/**< X-machine memory variable familia of type int. */
	int xcord;	/**< X-machine memory variable xcord of type int. */
	int ycord;	/**< X-machine memory variable ycord of type int. */
	int count;	/**< X-machine memory variable count of type int. */
	int calorias;	/**< X-machine memory variable calorias of type int. */
	int adultos;	/**< X-machine memory variable adultos of type int. */
};

/** \struct xmachine_memory_manada_guanacos_holder
 * \brief Holds struct of memory of xmachine manada_guanacos.
 */
struct xmachine_memory_manada_guanacos_holder
{
	/*@dependent@*/ struct xmachine_memory_manada_guanacos * agent;	/**< Pointer to X-machine memory manada_guanacos. */

	/*@dependent@*/ struct xmachine_memory_manada_guanacos_holder * prev;	/**< Pointer to previous manada_guanacos agent in the list.  */
	/*@dependent@*/ struct xmachine_memory_manada_guanacos_holder * next;	/**< Pointer to next manada_guanacos agent in the list.  */
};

/** \struct xmachine_memory_manada_guanacos_holder
 * \brief Holds struct of memory of xmachine manada_guanacos.
 */
struct xmachine_memory_manada_guanacos_state
{
	/*@dependent@*/ struct xmachine_memory_manada_guanacos_holder * agents;	/**< Pointer to X-machine memory manada_guanacos. */

	int count;	/**< Number of agents that were in this state.  */
};

/** \struct xmachine
 * \brief Holds xmachines.
 */
struct xmachine
{
	/*@dependent@*/ /*@null@*/ /*@out@*/ struct xmachine_memory_indv * xmachine_indv;	/**< Pointer to X-machine memory of type indv.  */
	/*@dependent@*/ /*@null@*/ /*@out@*/ struct xmachine_memory_clan * xmachine_clan;	/**< Pointer to X-machine memory of type clan.  */
	/*@dependent@*/ /*@null@*/ /*@out@*/ struct xmachine_memory_patch * xmachine_patch;	/**< Pointer to X-machine memory of type patch.  */
	/*@dependent@*/ /*@null@*/ /*@out@*/ struct xmachine_memory_manada_guanacos * xmachine_manada_guanacos;	/**< Pointer to X-machine memory of type manada_guanacos.  */
};

/** \var void* FLAME_m_information_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_information_composite_params;

/** \struct m_information
 * \brief Holds message of type information_message.
 */
struct m_information
{
	int id;	/**< Message memory variable id of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int cal;	/**< Message memory variable cal of type int. */
	int age;	/**< Message memory variable age of type int. */
	int pregnant;	/**< Message memory variable pregnant of type int. */
};

/** \var void* FLAME_m_indgetcalories_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_indgetcalories_composite_params;

/** \struct m_indgetcalories
 * \brief Holds message of type indgetcalories_message.
 */
struct m_indgetcalories
{
	int icalories;	/**< Message memory variable icalories of type int. */
	int indvID;	/**< Message memory variable indvID of type int. */
};

/** \var void* FLAME_m_leader_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_leader_composite_params;

/** \struct m_leader
 * \brief Holds message of type leader_message.
 */
struct m_leader
{
	int id;	/**< Message memory variable id of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int leader;	/**< Message memory variable leader of type int. */
	int sex;	/**< Message memory variable sex of type int. */
	int age;	/**< Message memory variable age of type int. */
};

/** \var void* FLAME_m_clan_info_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_clan_info_composite_params;

/** \struct m_clan_info
 * \brief Holds message of type clan_info_message.
 */
struct m_clan_info
{
	int px;	/**< Message memory variable px of type int. */
	int py;	/**< Message memory variable py of type int. */
	int cID;	/**< Message memory variable cID of type int. */
	int wf;	/**< Message memory variable wf of type int. */
	int maxcc;	/**< Message memory variable maxcc of type int. */
};

/** \var void* FLAME_m_clangetcalories_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_clangetcalories_composite_params;

/** \struct m_clangetcalories
 * \brief Holds message of type clangetcalories_message.
 */
struct m_clangetcalories
{
	int cID;	/**< Message memory variable cID of type int. */
	int clcalories;	/**< Message memory variable clcalories of type int. */
};

/** \var void* FLAME_m_calguanacos_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_calguanacos_composite_params;

/** \struct m_calguanacos
 * \brief Holds message of type calguanacos_message.
 */
struct m_calguanacos
{
	int xcord;	/**< Message memory variable xcord of type int. */
	int ycord;	/**< Message memory variable ycord of type int. */
	int calorias;	/**< Message memory variable calorias of type int. */
};

/** \typedef struct xmachine xmachine
 * \brief Typedef for xmachine struct.
 */
typedef struct xmachine xmachine;
/** \var typedef xmachine_memory_indv xmachine_memory_indv
 * \brief Typedef for xmachine_memory_indv struct.
 */
typedef struct xmachine_memory_indv xmachine_memory_indv;
/** \var typedef xmachine_memory_indv xmachine_memory_indv
 * \brief Typedef for xmachine_memory_indv struct.
 */
typedef struct xmachine_memory_indv_holder xmachine_memory_indv_holder;
/** \var typedef xmachine_memory_indv xmachine_memory_indv
 * \brief Typedef for xmachine_memory_indv struct.
 */
typedef struct xmachine_memory_indv_state xmachine_memory_indv_state;
/** \var typedef xmachine_memory_clan xmachine_memory_clan
 * \brief Typedef for xmachine_memory_clan struct.
 */
typedef struct xmachine_memory_clan xmachine_memory_clan;
/** \var typedef xmachine_memory_clan xmachine_memory_clan
 * \brief Typedef for xmachine_memory_clan struct.
 */
typedef struct xmachine_memory_clan_holder xmachine_memory_clan_holder;
/** \var typedef xmachine_memory_clan xmachine_memory_clan
 * \brief Typedef for xmachine_memory_clan struct.
 */
typedef struct xmachine_memory_clan_state xmachine_memory_clan_state;
/** \var typedef xmachine_memory_patch xmachine_memory_patch
 * \brief Typedef for xmachine_memory_patch struct.
 */
typedef struct xmachine_memory_patch xmachine_memory_patch;
/** \var typedef xmachine_memory_patch xmachine_memory_patch
 * \brief Typedef for xmachine_memory_patch struct.
 */
typedef struct xmachine_memory_patch_holder xmachine_memory_patch_holder;
/** \var typedef xmachine_memory_patch xmachine_memory_patch
 * \brief Typedef for xmachine_memory_patch struct.
 */
typedef struct xmachine_memory_patch_state xmachine_memory_patch_state;
/** \var typedef xmachine_memory_manada_guanacos xmachine_memory_manada_guanacos
 * \brief Typedef for xmachine_memory_manada_guanacos struct.
 */
typedef struct xmachine_memory_manada_guanacos xmachine_memory_manada_guanacos;
/** \var typedef xmachine_memory_manada_guanacos xmachine_memory_manada_guanacos
 * \brief Typedef for xmachine_memory_manada_guanacos struct.
 */
typedef struct xmachine_memory_manada_guanacos_holder xmachine_memory_manada_guanacos_holder;
/** \var typedef xmachine_memory_manada_guanacos xmachine_memory_manada_guanacos
 * \brief Typedef for xmachine_memory_manada_guanacos struct.
 */
typedef struct xmachine_memory_manada_guanacos_state xmachine_memory_manada_guanacos_state;
/** \typedef m_information m_information
 * \brief Typedef for m_information struct.
 */
typedef struct m_information m_information;

/** \typedef m_indgetcalories m_indgetcalories
 * \brief Typedef for m_indgetcalories struct.
 */
typedef struct m_indgetcalories m_indgetcalories;

/** \typedef m_leader m_leader
 * \brief Typedef for m_leader struct.
 */
typedef struct m_leader m_leader;

/** \typedef m_clan_info m_clan_info
 * \brief Typedef for m_clan_info struct.
 */
typedef struct m_clan_info m_clan_info;

/** \typedef m_clangetcalories m_clangetcalories
 * \brief Typedef for m_clangetcalories struct.
 */
typedef struct m_clangetcalories m_clangetcalories;

/** \typedef m_calguanacos m_calguanacos
 * \brief Typedef for m_calguanacos struct.
 */
typedef struct m_calguanacos m_calguanacos;


/** \struct location
 * \brief Holds location for calculating space partitioning .
 */
struct location
{
	double point;		/**< Point on an axis. */

	struct location * next;	/**< Pointer to next location on the list. */
};

/** \struct node_information
 * \brief Holds node information .
 */
struct node_information
{
	int node_id;	/**< Node ID. */
	double partition_data[6];	/**< Defines bounding box. */
	int agents_in_halo;	/**< Number of agents in the halo region. */
	int agent_total;	/**< Total number of agents on the node. */
	struct xmachine * agents;	/**< Pointer to list of X-machines. */
	struct m_information * information_messages;	/**< Pointer to information message list. */
	struct m_indgetcalories * indgetcalories_messages;	/**< Pointer to indgetcalories message list. */
	struct m_leader * leader_messages;	/**< Pointer to leader message list. */
	struct m_clan_info * clan_info_messages;	/**< Pointer to clan_info message list. */
	struct m_clangetcalories * clangetcalories_messages;	/**< Pointer to clangetcalories message list. */
	struct m_calguanacos * calguanacos_messages;	/**< Pointer to calguanacos message list. */

	struct node_information * next;	/**< Pointer to next node on the list. */
};


/** \typedef struct location location
 * \brief Typedef for location struct.
 */
typedef struct location location;
/** \typedef struct node_information node_information
 * \brief Typedef for node_information struct.
 */
typedef struct node_information node_information;

/** \var int max_manada
* \brief A constant variable from the environment. */
int FLAME_environment_variable_max_manada;
/** \var int max_familia
* \brief A constant variable from the environment. */
int FLAME_environment_variable_max_familia;
/** \var int cal_adulto
* \brief A constant variable from the environment. */
int FLAME_environment_variable_cal_adulto;
/** \var xmachine * temp_xmachine
* \brief Pointer to xmachine to initialise linked list. */
xmachine * temp_xmachine;

/** \var m_information * temp_information_message
* \brief Pointer to m_information to initialise linked list. */
m_information * temp_information_message;
/** \var m_indgetcalories * temp_indgetcalories_message
* \brief Pointer to m_indgetcalories to initialise linked list. */
m_indgetcalories * temp_indgetcalories_message;
/** \var m_leader * temp_leader_message
* \brief Pointer to m_leader to initialise linked list. */
m_leader * temp_leader_message;
/** \var m_clan_info * temp_clan_info_message
* \brief Pointer to m_clan_info to initialise linked list. */
m_clan_info * temp_clan_info_message;
/** \var m_clangetcalories * temp_clangetcalories_message
* \brief Pointer to m_clangetcalories to initialise linked list. */
m_clangetcalories * temp_clangetcalories_message;
/** \var m_calguanacos * temp_calguanacos_message
* \brief Pointer to m_calguanacos to initialise linked list. */
m_calguanacos * temp_calguanacos_message;
/** \var node_information * temp_node_info
* \brief Pointer to node_information to initialise linked list. */
node_information * temp_node_info;
/** \var char outputpath[1000]
* \brief Output path for files. */
char outputpath[1000];
/** \var long total_time
* \brief Total time for the simulation run (in seconds) */
double total_time;
/** \var int total_messages
* \brief Total messages sent between nodes for the simulation run */
int total_messages;
/** \var int totalnodes
* \brief Number of nodes */
int totalnodes;
/** \var xmachine ** p_xmachine
* \brief Pointer to first pointer of x-machine memory list */
//xmachine ** p_xmachine;
/** \var xmachine * current_xmachine
* \brief Pointer to current x-machine memory that is being processed */
xmachine * current_xmachine;
/* Pointer to current $agent_name agent */
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_indv * current_xmachine_indv;
/*@dependent@*/ xmachine_memory_indv_holder * temp_xmachine_indv_holder;
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_indv_holder * current_xmachine_indv_holder;
xmachine_memory_indv_state * current_xmachine_indv_next_state; /* New agents added to this state */
/* Pointer to list of indv agents in state end state */
//xmachine_memory_indv * temp_xmachine_indv_end;
xmachine_memory_indv_state * indv_end_state;
/* Pointer to list of indv agents in state 03 state */
//xmachine_memory_indv * temp_xmachine_indv_03;
xmachine_memory_indv_state * indv_03_state;
/* Pointer to list of indv agents in state 02 state */
//xmachine_memory_indv * temp_xmachine_indv_02;
xmachine_memory_indv_state * indv_02_state;
/* Pointer to list of indv agents in state 01 state */
//xmachine_memory_indv * temp_xmachine_indv_01;
xmachine_memory_indv_state * indv_01_state;
/* Pointer to list of indv agents in state start state */
//xmachine_memory_indv * temp_xmachine_indv_start;
xmachine_memory_indv_state * indv_start_state;
/* Pointer to current $agent_name agent */
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_clan * current_xmachine_clan;
/*@dependent@*/ xmachine_memory_clan_holder * temp_xmachine_clan_holder;
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_clan_holder * current_xmachine_clan_holder;
xmachine_memory_clan_state * current_xmachine_clan_next_state; /* New agents added to this state */
/* Pointer to list of clan agents in state end state */
//xmachine_memory_clan * temp_xmachine_clan_end;
xmachine_memory_clan_state * clan_end_state;
/* Pointer to list of clan agents in state 03 state */
//xmachine_memory_clan * temp_xmachine_clan_03;
xmachine_memory_clan_state * clan_03_state;
/* Pointer to list of clan agents in state 02 state */
//xmachine_memory_clan * temp_xmachine_clan_02;
xmachine_memory_clan_state * clan_02_state;
/* Pointer to list of clan agents in state 01 state */
//xmachine_memory_clan * temp_xmachine_clan_01;
xmachine_memory_clan_state * clan_01_state;
/* Pointer to list of clan agents in state start state */
//xmachine_memory_clan * temp_xmachine_clan_start;
xmachine_memory_clan_state * clan_start_state;
/* Pointer to current $agent_name agent */
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_patch * current_xmachine_patch;
/*@dependent@*/ xmachine_memory_patch_holder * temp_xmachine_patch_holder;
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_patch_holder * current_xmachine_patch_holder;
xmachine_memory_patch_state * current_xmachine_patch_next_state; /* New agents added to this state */
/* Pointer to list of patch agents in state end state */
//xmachine_memory_patch * temp_xmachine_patch_end;
xmachine_memory_patch_state * patch_end_state;
/* Pointer to list of patch agents in state 3 state */
//xmachine_memory_patch * temp_xmachine_patch_3;
xmachine_memory_patch_state * patch_3_state;
/* Pointer to list of patch agents in state 2 state */
//xmachine_memory_patch * temp_xmachine_patch_2;
xmachine_memory_patch_state * patch_2_state;
/* Pointer to list of patch agents in state 1 state */
//xmachine_memory_patch * temp_xmachine_patch_1;
xmachine_memory_patch_state * patch_1_state;
/* Pointer to list of patch agents in state start state */
//xmachine_memory_patch * temp_xmachine_patch_start;
xmachine_memory_patch_state * patch_start_state;
/* Pointer to current $agent_name agent */
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_manada_guanacos * current_xmachine_manada_guanacos;
/*@dependent@*/ xmachine_memory_manada_guanacos_holder * temp_xmachine_manada_guanacos_holder;
/*@dependent@*/ /*@null@*/ /*@out@*/ xmachine_memory_manada_guanacos_holder * current_xmachine_manada_guanacos_holder;
xmachine_memory_manada_guanacos_state * current_xmachine_manada_guanacos_next_state; /* New agents added to this state */
/* Pointer to list of manada_guanacos agents in state end state */
//xmachine_memory_manada_guanacos * temp_xmachine_manada_guanacos_end;
xmachine_memory_manada_guanacos_state * manada_guanacos_end_state;
/* Pointer to list of manada_guanacos agents in state 2 state */
//xmachine_memory_manada_guanacos * temp_xmachine_manada_guanacos_2;
xmachine_memory_manada_guanacos_state * manada_guanacos_2_state;
/* Pointer to list of manada_guanacos agents in state 1 state */
//xmachine_memory_manada_guanacos * temp_xmachine_manada_guanacos_1;
xmachine_memory_manada_guanacos_state * manada_guanacos_1_state;
/* Pointer to list of manada_guanacos agents in state start state */
//xmachine_memory_manada_guanacos * temp_xmachine_manada_guanacos_start;
xmachine_memory_manada_guanacos_state * manada_guanacos_start_state;



MBt_Board b_information;
MBt_Iterator i_information;

MBt_Board b_indgetcalories;
MBt_Iterator i_indgetcalories;

MBt_Board b_leader;
MBt_Iterator i_leader;

MBt_Board b_clan_info;
MBt_Iterator i_clan_info;

MBt_Board b_clangetcalories;
MBt_Iterator i_clangetcalories;

MBt_Board b_calguanacos;
MBt_Iterator i_calguanacos;


/** \var m_information * information_message
* \brief Pointer to message struct for looping through information message list */
m_information * information_message;
/** \var m_indgetcalories * indgetcalories_message
* \brief Pointer to message struct for looping through indgetcalories message list */
m_indgetcalories * indgetcalories_message;
/** \var m_leader * leader_message
* \brief Pointer to message struct for looping through leader message list */
m_leader * leader_message;
/** \var m_clan_info * clan_info_message
* \brief Pointer to message struct for looping through clan_info message list */
m_clan_info * clan_info_message;
/** \var m_clangetcalories * clangetcalories_message
* \brief Pointer to message struct for looping through clangetcalories message list */
m_clangetcalories * clangetcalories_message;
/** \var m_calguanacos * calguanacos_message
* \brief Pointer to message struct for looping through calguanacos message list */
m_calguanacos * calguanacos_message;
/** \var FLAME_output ** FLAME_outputs
* \brief Pointer to list of outputs */
FLAME_output * FLAME_outputs;
/** \var node_information * p_node_info
* \brief Pointer to first pointer of node list */
node_information ** p_node_info;
/** \var node_information * current_node
* \brief Pointer to current node */
node_information * current_node;

/** \var int iteration_loop
* \brief The current iteration number */
int iteration_loop;
/** \var int output_frequency
* \brief Frequency to output results */
int output_frequency;
/** \var int output_offset
* \brief Offset to output results */
int output_offset;

/** \def SPINF
* \brief Dummy inf value for space partition data. */
#define SPINF 999999.123456
/** \def RELEASE
* \brief Used to kill an agent via 'return RELEASE;'. */
#define RELEASE 1
/** \def kill_me_now
* \brief Used to kill an agent via 'kill_me_now'. */
#define kill_me_now return 1

void initialise_pointers(void);
void initialise_unit_testing(void);
FLAME_output * add_FLAME_output(FLAME_output ** outputs);
void free_FLAME_outputs(FLAME_output ** outputs);
void add_location(double point, location ** p_location);
void freelocations(location ** p_location);
void add_node(int node_id, double minx, double maxx, double miny, double maxy, double minz, double maxz);
void clean_up(int code);
void propagate_agents(void);
void propagate_messages_init(void);
void propagate_messages_complete(void);
void create_partitions(char * filename, int * itno);
void free_node_info(void);
void free_agent(void);
void freexmachines(void);
/* model datatypes */

void init_members_needs_array(members_needs_array * array);
void reset_members_needs_array(members_needs_array * array);
void free_members_needs_array(members_needs_array * array);
void copy_members_needs_array(members_needs_array * from, members_needs_array * to);
void add_members_needs(members_needs_array * array, /*@out@*/ int * id_list, /*@out@*/ int * cal_list, /*@out@*/ int * age);
void remove_members_needs(members_needs_array * array, int index);

void init_int_static_array(/*@out@*/ int * array, int size);
void init_int_array(int_array * array);
void reset_int_array(int_array * array);
void free_int_array(int_array * array);
void copy_int_array(int_array * from, int_array * to);
//void sort_int_array(int_array array);
//int quicksort_int(int array, int elements);
void add_int(int_array * array, int new_int);
void remove_int(int_array * array, int index);
void print_int_array(int_array * array);
void init_float_static_array(float * array, int size);
void init_float_array(float_array * array);
void reset_float_array(float_array * array);
void free_float_array(float_array * array);
void copy_float_array(float_array * from, float_array * to);
//void sort_float_array(float_array array);
//int quicksort_float(float array, int elements);
void add_float(float_array * array, float new_float);
void remove_float(float_array * array, int index);
void print_float_array(float_array * array);
void init_double_static_array(/*@out@*/ double* array, int size);
void init_double_array(double_array * array);
void reset_double_array(double_array * array);
void free_double_array(double_array * array);
void copy_double_array(double_array * from, double_array * to);
//void sort_double_array(double_array array);
//int quicksort_double(double array, int elements);
void add_double(double_array * array, double new_double);
void remove_double(double_array * array, int index);
void print_double_array(double_array * array);
void init_char_static_array(/*@out@*/ char * array, int size);
void init_char_array(char_array * array);
void reset_char_array(char_array * array);
void free_char_array(char_array * array);
void copy_char_array(char_array * from, char_array * to);
void add_char(char_array * array, char new_char);
void remove_char(char_array * array, int index);
char * copy_array_to_str(char_array * array);
void print_char_array(char_array * array);
int idle(void);
/* xml.c */
int read_int_static_array(char * buffer, int buffer_size, int * j, int * int_static_array, int size);
int read_float_static_array(char * buffer, int buffer_size, int * j, float * float_static_array, int size);
int read_double_static_array(char * buffer, int buffer_size, int * j, double * double_static_array, int size);
int read_char_static_array(char * buffer, int buffer_size, int * j, char * char_static_array, int size);
int read_int_dynamic_array(char * buffer, int buffer_size, int * j, int_array * int_dynamic_array);
int read_float_dynamic_array(char * buffer, int buffer_size, int * j, float_array * float_dynamic_array);
int read_double_dynamic_array(char * buffer, int buffer_size, int * j, double_array * double_dynamic_array);
int read_char_dynamic_array(char * buffer, int buffer_size, int * j, char_array * char_dynamic_array);

void init_members_needs(/*@out@*/ members_needs * temp);
void init_members_needs_static_array(/*@out@*/ members_needs * array, int size);
int read_members_needs(char * buffer, int buffer_size, int * j, members_needs * temp_datatype);
int read_members_needs_dynamic_array(char * buffer, int buffer_size, int * j, members_needs_array * temp_datatype_array);
int read_members_needs_static_array(char * buffer, int buffer_size, int * j, members_needs * temp_datatype_array, int size);
void write_members_needs(FILE *file, members_needs * temp_datatype);
void write_members_needs_static_array(FILE *file, members_needs * temp_datatype, int size);
void write_members_needs_dynamic_array(FILE *file, members_needs_array * temp_datatype);

void readinitialstates(char * filename, char * filelocation, int * itno, double cloud_data[],
					   int partition_method, int flag);
void saveiterationdata(int iteration_number);

void free_members_needs(members_needs * temp);
void free_members_needs_static_array(members_needs * array, int size);
void copy_members_needs(members_needs * from, members_needs * to);
void copy_members_needs_static_array(members_needs * from, members_needs * to, int size);

xmachine_memory_indv_state * init_indv_state();
xmachine_memory_indv * init_indv_agent();
void free_indv_agent(xmachine_memory_indv_holder * tmp, xmachine_memory_indv_state * state);
void transition_indv_agent(xmachine_memory_indv_holder * tmp, xmachine_memory_indv_state * from_state, xmachine_memory_indv_state * to_state);
void add_indv_agent_internal(xmachine_memory_indv * agent, xmachine_memory_indv_state * state);
void add_indv_agent(int indvID, int cID, int cal_needs, int icalories, int patchID, int age, int sex, int pregnant, int lead);
void unittest_init_indv_agent();
void unittest_free_indv_agent();
xmachine_memory_clan_state * init_clan_state();
xmachine_memory_clan * init_clan_agent();
void free_clan_agent(xmachine_memory_clan_holder * tmp, xmachine_memory_clan_state * state);
void transition_clan_agent(xmachine_memory_clan_holder * tmp, xmachine_memory_clan_state * from_state, xmachine_memory_clan_state * to_state);
void add_clan_agent_internal(xmachine_memory_clan * agent, xmachine_memory_clan_state * state);
void add_clan_agent(int cID, int cal_need, int cal_got, int cal_stored, int xcord, int ycord, int tcalories, int leaderID, members_needs mneeds);
void unittest_init_clan_agent();
void unittest_free_clan_agent();
xmachine_memory_patch_state * init_patch_state();
xmachine_memory_patch * init_patch_agent();
void free_patch_agent(xmachine_memory_patch_holder * tmp, xmachine_memory_patch_state * state);
void transition_patch_agent(xmachine_memory_patch_holder * tmp, xmachine_memory_patch_state * from_state, xmachine_memory_patch_state * to_state);
void add_patch_agent_internal(xmachine_memory_patch * agent, xmachine_memory_patch_state * state);
void add_patch_agent(int patchID, int pcalories, float repo, int tpatch, int xcord, int ycord, float repows, float repods, int season);
void unittest_init_patch_agent();
void unittest_free_patch_agent();
xmachine_memory_manada_guanacos_state * init_manada_guanacos_state();
xmachine_memory_manada_guanacos * init_manada_guanacos_agent();
void free_manada_guanacos_agent(xmachine_memory_manada_guanacos_holder * tmp, xmachine_memory_manada_guanacos_state * state);
void transition_manada_guanacos_agent(xmachine_memory_manada_guanacos_holder * tmp, xmachine_memory_manada_guanacos_state * from_state, xmachine_memory_manada_guanacos_state * to_state);
void add_manada_guanacos_agent_internal(xmachine_memory_manada_guanacos * agent, xmachine_memory_manada_guanacos_state * state);
void add_manada_guanacos_agent(int id, int familia, int xcord, int ycord, int count, int calorias, int adultos);
void unittest_init_manada_guanacos_agent();
void unittest_free_manada_guanacos_agent();

void add_information_message(int id, int clanID, int cal, int age, int pregnant);
m_information * add_information_message_internal(void);
m_information * get_first_information_message(void);
m_information * get_next_information_message(m_information * current);
void freeinformationmessages(void);

void add_indgetcalories_message(int icalories, int indvID);
m_indgetcalories * add_indgetcalories_message_internal(void);
m_indgetcalories * get_first_indgetcalories_message(void);
m_indgetcalories * get_next_indgetcalories_message(m_indgetcalories * current);
void freeindgetcaloriesmessages(void);

void add_leader_message(int id, int clanID, int leader, int sex, int age);
m_leader * add_leader_message_internal(void);
m_leader * get_first_leader_message(void);
m_leader * get_next_leader_message(m_leader * current);
void freeleadermessages(void);

void add_clan_info_message(int px, int py, int cID, int wf, int maxcc);
m_clan_info * add_clan_info_message_internal(void);
m_clan_info * get_first_clan_info_message(void);
m_clan_info * get_next_clan_info_message(m_clan_info * current);
void freeclan_infomessages(void);

void add_clangetcalories_message(int cID, int clcalories);
m_clangetcalories * add_clangetcalories_message_internal(void);
m_clangetcalories * get_first_clangetcalories_message(void);
m_clangetcalories * get_next_clangetcalories_message(m_clangetcalories * current);
void freeclangetcaloriesmessages(void);

void add_calguanacos_message(int xcord, int ycord, int calorias);
m_calguanacos * add_calguanacos_message_internal(void);
m_calguanacos * get_first_calguanacos_message(void);
m_calguanacos * get_next_calguanacos_message(m_calguanacos * current);
void freecalguanacosmessages(void);


void set_indvID(int indvID);
int get_indvID();
void set_cID(int cID);
int get_cID();
void set_cal_needs(int cal_needs);
int get_cal_needs();
void set_icalories(int icalories);
int get_icalories();
void set_patchID(int patchID);
int get_patchID();
void set_age(int age);
int get_age();
void set_sex(int sex);
int get_sex();
void set_pregnant(int pregnant);
int get_pregnant();
void set_lead(int lead);
int get_lead();
void set_cal_need(int cal_need);
int get_cal_need();
void set_cal_got(int cal_got);
int get_cal_got();
void set_cal_stored(int cal_stored);
int get_cal_stored();
void set_xcord(int xcord);
int get_xcord();
void set_ycord(int ycord);
int get_ycord();
void set_tcalories(int tcalories);
int get_tcalories();
void set_leaderID(int leaderID);
int get_leaderID();
members_needs * get_mneeds();
void set_pcalories(int pcalories);
int get_pcalories();
void set_repo(float repo);
float get_repo();
void set_tpatch(int tpatch);
int get_tpatch();
void set_repows(float repows);
float get_repows();
void set_repods(float repods);
float get_repods();
void set_season(int season);
int get_season();
void set_id(int id);
int get_id();
void set_familia(int familia);
int get_familia();
void set_count(int count);
int get_count();
void set_calorias(int calorias);
int get_calorias();
void set_adultos(int adultos);
int get_adultos();
int agent_get_id(void);
double agent_get_x(void);
double agent_get_y(void);
double agent_get_z(void);
/* partitioning.c */
void partition_data(int totalnodes, xmachine ** agent_list, double cloud_data[], int partition_method);


void save_partition_data(void);
void generate_partitions(double cloud_data[], int partitions, int partition_method);

/* messageboard.c */
m_information * get_next_message_information_in_range(m_information * current);



m_indgetcalories * get_next_message_indgetcalories_in_range(m_indgetcalories * current);



m_leader * get_next_message_leader_in_range(m_leader * current);



m_clan_info * get_next_message_clan_info_in_range(m_clan_info * current);



m_clangetcalories * get_next_message_clangetcalories_in_range(m_clangetcalories * current);



m_calguanacos * get_next_message_calguanacos_in_range(m_calguanacos * current);




/* memory.c */
xmachine * add_xmachine(void);
int FLAME_get_environment_variable_max_manada();
int FLAME_get_environment_variable_max_familia();
int FLAME_get_environment_variable_cal_adulto();


/* rules.c */
int FLAME_integer_in_array(int a, int * b, int size);

/* timing.c */
double get_time(void);

int indvInformation(void);
int extractcalories(void);
int FLAME_filter_indv_extractcalories_01_02_indgetcalories(const void *msg, const void *params);
int getolder(void);
int FLAME_condition_indv_getolder_02_03(xmachine_memory_indv *a);
int idle_indv(void);
int FLAME_condition_indv_idle_indv_02_03(xmachine_memory_indv *a);
int survive(void);
int clan_Information(void);
int FLAME_filter_clan_clan_Information_start_01_information(const void *msg, const void *params);
int clan_extract_calories(void);
int FLAME_filter_clan_clan_extract_calories_01_02_clangetcalories(const void *msg, const void *params);
int distribute_calories(void);
int new_leader(void);
int FLAME_filter_clan_new_leader_03_end_leader(const void *msg, const void *params);
int patchtype(void);
int patchcalories(void);
int FLAME_filter_patch_patchcalories_1_2_clan_info(const void *msg, const void *params);
int regenerate(void);
int FLAME_filter_patch_regenerate_2_3_calguanacos(const void *msg, const void *params);
int snregenerate(void);
int FLAME_condition_patch_snregenerate_3_end(xmachine_memory_patch *a);
int idle_patch(void);
int FLAME_condition_patch_idle_patch_3_end(xmachine_memory_patch *a);
int manadaInfo(void);
int manada_idle(void);
int FLAME_condition_manada_guanacos_manada_idle_1_2(xmachine_memory_manada_guanacos *a);
int move(void);
int FLAME_condition_manada_guanacos_move_1_2(xmachine_memory_manada_guanacos *a);
int post_calorias(void);
#endif
