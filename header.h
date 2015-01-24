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


/** \def PROPEGNANT
 * \brief Provide access to environment variables in uppercase. */
#define PROPEGNANT (FLAME_get_environment_variable_propegnant())
/** \def NANCESTORS
 * \brief Provide access to environment variables in uppercase. */
#define NANCESTORS (FLAME_get_environment_variable_nancestors())
/** \def LEARN
 * \brief Provide access to environment variables in uppercase. */
#define LEARN (FLAME_get_environment_variable_learn())
/** \def FORGET
 * \brief Provide access to environment variables in uppercase. */
#define FORGET (FLAME_get_environment_variable_forget())
/** \def LANG_THRESHOLD
 * \brief Provide access to environment variables in uppercase. */
#define LANG_THRESHOLD (FLAME_get_environment_variable_lang_threshold())
/** \def MAX_MANADA
 * \brief Provide access to environment variables in uppercase. */
#define MAX_MANADA (FLAME_get_environment_variable_max_manada())
/** \def MAX_FAMILIA
 * \brief Provide access to environment variables in uppercase. */
#define MAX_FAMILIA (FLAME_get_environment_variable_max_familia())
/** \def CAL_ADULTO
 * \brief Provide access to environment variables in uppercase. */
#define CAL_ADULTO (FLAME_get_environment_variable_cal_adulto())
/** \def SURVIVECHANCEADULT
 * \brief Provide access to environment variables in uppercase. */
#define SURVIVECHANCEADULT (FLAME_get_environment_variable_surviveChanceAdult())
/** \def SURVIVECHANCECHILD
 * \brief Provide access to environment variables in uppercase. */
#define SURVIVECHANCECHILD (FLAME_get_environment_variable_surviveChanceChild())
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
/** \def START_ANCESTOR_MESSAGE_LOOP
 * \brief Start of loop to process ancestor messages. */
#define START_ANCESTOR_MESSAGE_LOOP  for(ancestor_message = get_first_ancestor_message(); ancestor_message != NULL; ancestor_message = get_next_ancestor_message(ancestor_message)) {
/** \def FINISH_ANCESTOR_MESSAGE_LOOP
 * \brief Finish of loop to process ancestor messages. */
#define FINISH_ANCESTOR_MESSAGE_LOOP }
/** \def START_PETICIONID_MESSAGE_LOOP
 * \brief Start of loop to process peticionID messages. */
#define START_PETICIONID_MESSAGE_LOOP  for(peticionID_message = get_first_peticionID_message(); peticionID_message != NULL; peticionID_message = get_next_peticionID_message(peticionID_message)) {
/** \def FINISH_PETICIONID_MESSAGE_LOOP
 * \brief Finish of loop to process peticionID messages. */
#define FINISH_PETICIONID_MESSAGE_LOOP }
/** \def START_FAMILY_MESSAGE_LOOP
 * \brief Start of loop to process family messages. */
#define START_FAMILY_MESSAGE_LOOP  for(family_message = get_first_family_message(); family_message != NULL; family_message = get_next_family_message(family_message)) {
/** \def FINISH_FAMILY_MESSAGE_LOOP
 * \brief Finish of loop to process family messages. */
#define FINISH_FAMILY_MESSAGE_LOOP }
/** \def START_DEATH_MESSAGE_LOOP
 * \brief Start of loop to process death messages. */
#define START_DEATH_MESSAGE_LOOP  for(death_message = get_first_death_message(); death_message != NULL; death_message = get_next_death_message(death_message)) {
/** \def FINISH_DEATH_MESSAGE_LOOP
 * \brief Finish of loop to process death messages. */
#define FINISH_DEATH_MESSAGE_LOOP }
/** \def START_WIDOW_MESSAGE_LOOP
 * \brief Start of loop to process widow messages. */
#define START_WIDOW_MESSAGE_LOOP  for(widow_message = get_first_widow_message(); widow_message != NULL; widow_message = get_next_widow_message(widow_message)) {
/** \def FINISH_WIDOW_MESSAGE_LOOP
 * \brief Finish of loop to process widow messages. */
#define FINISH_WIDOW_MESSAGE_LOOP }
/** \def START_INFORMATIONDIVIDE_MESSAGE_LOOP
 * \brief Start of loop to process informationDivide messages. */
#define START_INFORMATIONDIVIDE_MESSAGE_LOOP  for(informationDivide_message = get_first_informationDivide_message(); informationDivide_message != NULL; informationDivide_message = get_next_informationDivide_message(informationDivide_message)) {
/** \def FINISH_INFORMATIONDIVIDE_MESSAGE_LOOP
 * \brief Finish of loop to process informationDivide messages. */
#define FINISH_INFORMATIONDIVIDE_MESSAGE_LOOP }
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
/** \def START_FREEGIRLS_MESSAGE_LOOP
 * \brief Start of loop to process freeGirls messages. */
#define START_FREEGIRLS_MESSAGE_LOOP  for(freeGirls_message = get_first_freeGirls_message(); freeGirls_message != NULL; freeGirls_message = get_next_freeGirls_message(freeGirls_message)) {
/** \def FINISH_FREEGIRLS_MESSAGE_LOOP
 * \brief Finish of loop to process freeGirls messages. */
#define FINISH_FREEGIRLS_MESSAGE_LOOP }
/** \def START_PROPUESTA_MESSAGE_LOOP
 * \brief Start of loop to process propuesta messages. */
#define START_PROPUESTA_MESSAGE_LOOP  for(propuesta_message = get_first_propuesta_message(); propuesta_message != NULL; propuesta_message = get_next_propuesta_message(propuesta_message)) {
/** \def FINISH_PROPUESTA_MESSAGE_LOOP
 * \brief Finish of loop to process propuesta messages. */
#define FINISH_PROPUESTA_MESSAGE_LOOP }
/** \def START_CONFIRPROP_MESSAGE_LOOP
 * \brief Start of loop to process confirProp messages. */
#define START_CONFIRPROP_MESSAGE_LOOP  for(confirProp_message = get_first_confirProp_message(); confirProp_message != NULL; confirProp_message = get_next_confirProp_message(confirProp_message)) {
/** \def FINISH_CONFIRPROP_MESSAGE_LOOP
 * \brief Finish of loop to process confirProp messages. */
#define FINISH_CONFIRPROP_MESSAGE_LOOP }
/** \def START_MARRIAGE_MESSAGE_LOOP
 * \brief Start of loop to process marriage messages. */
#define START_MARRIAGE_MESSAGE_LOOP  for(marriage_message = get_first_marriage_message(); marriage_message != NULL; marriage_message = get_next_marriage_message(marriage_message)) {
/** \def FINISH_MARRIAGE_MESSAGE_LOOP
 * \brief Finish of loop to process marriage messages. */
#define FINISH_MARRIAGE_MESSAGE_LOOP }
/** \def START_RESPUESTAID_MESSAGE_LOOP
 * \brief Start of loop to process respuestaID messages. */
#define START_RESPUESTAID_MESSAGE_LOOP  for(respuestaID_message = get_first_respuestaID_message(); respuestaID_message != NULL; respuestaID_message = get_next_respuestaID_message(respuestaID_message)) {
/** \def FINISH_RESPUESTAID_MESSAGE_LOOP
 * \brief Finish of loop to process respuestaID messages. */
#define FINISH_RESPUESTAID_MESSAGE_LOOP }
/** \def START_LMARRIAGE_MESSAGE_LOOP
 * \brief Start of loop to process lmarriage messages. */
#define START_LMARRIAGE_MESSAGE_LOOP  for(lmarriage_message = get_first_lmarriage_message(); lmarriage_message != NULL; lmarriage_message = get_next_lmarriage_message(lmarriage_message)) {
/** \def FINISH_LMARRIAGE_MESSAGE_LOOP
 * \brief Finish of loop to process lmarriage messages. */
#define FINISH_LMARRIAGE_MESSAGE_LOOP }
/** \def START_WARNINGDIVIDE_MESSAGE_LOOP
 * \brief Start of loop to process warningDivide messages. */
#define START_WARNINGDIVIDE_MESSAGE_LOOP  for(warningDivide_message = get_first_warningDivide_message(); warningDivide_message != NULL; warningDivide_message = get_next_warningDivide_message(warningDivide_message)) {
/** \def FINISH_WARNINGDIVIDE_MESSAGE_LOOP
 * \brief Finish of loop to process warningDivide messages. */
#define FINISH_WARNINGDIVIDE_MESSAGE_LOOP }
/** \def START_CLANSPATCH_MESSAGE_LOOP
 * \brief Start of loop to process clanspatch messages. */
#define START_CLANSPATCH_MESSAGE_LOOP  for(clanspatch_message = get_first_clanspatch_message(); clanspatch_message != NULL; clanspatch_message = get_next_clanspatch_message(clanspatch_message)) {
/** \def FINISH_CLANSPATCH_MESSAGE_LOOP
 * \brief Finish of loop to process clanspatch messages. */
#define FINISH_CLANSPATCH_MESSAGE_LOOP }
/** \def START_ADULTOSPATCH_MESSAGE_LOOP
 * \brief Start of loop to process adultospatch messages. */
#define START_ADULTOSPATCH_MESSAGE_LOOP  for(adultospatch_message = get_first_adultospatch_message(); adultospatch_message != NULL; adultospatch_message = get_next_adultospatch_message(adultospatch_message)) {
/** \def FINISH_ADULTOSPATCH_MESSAGE_LOOP
 * \brief Finish of loop to process adultospatch messages. */
#define FINISH_ADULTOSPATCH_MESSAGE_LOOP }
/** \def START_REPRODUCCIONGUANACOS_MESSAGE_LOOP
 * \brief Start of loop to process reproduccionguanacos messages. */
#define START_REPRODUCCIONGUANACOS_MESSAGE_LOOP  for(reproduccionguanacos_message = get_first_reproduccionguanacos_message(); reproduccionguanacos_message != NULL; reproduccionguanacos_message = get_next_reproduccionguanacos_message(reproduccionguanacos_message)) {
/** \def FINISH_REPRODUCCIONGUANACOS_MESSAGE_LOOP
 * \brief Finish of loop to process reproduccionguanacos messages. */
#define FINISH_REPRODUCCIONGUANACOS_MESSAGE_LOOP }


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
/** \struct indv_free
 * \brief Structure to remember free member of the clan .
 *
 * Structure to remember free member of the clan .
 */
struct indv_free
{
	int male_list[100];	/**< Datatype memory variable male_list of type int. */
	int female_list[100];	/**< Datatype memory variable female_list of type int. */
	int mancestor_list[600];	/**< Datatype memory variable mancestor_list of type int. */
	int fancestor_list[600];	/**< Datatype memory variable fancestor_list of type int. */
	int mancestorClan_list[600];	/**< Datatype memory variable mancestorClan_list of type int. */
	int fancestorClan_list[600];	/**< Datatype memory variable fancestorClan_list of type int. */
	int numMale;	/**< Datatype memory variable numMale of type int. */
	int numFemale;	/**< Datatype memory variable numFemale of type int. */
};

/** \struct indv_free_array
 * \brief Dynamic array to hold indv_frees
 */
struct indv_free_array
{
	int size;
	int total_size;

	struct indv_free * array;
};

/** \var typedef indv_free indv_free
 * \brief Typedef for indv_free struct.
 */
typedef struct indv_free indv_free;
/** \var typedef indv_free_array indv_free_array
 * \brief Typedef for indv_free_array struct.
 */
typedef struct indv_free_array indv_free_array;

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
	int marriable;	/**< X-machine memory variable marriable of type int. */
	int ancestors[6];	/**< X-machine memory variable ancestors of type int. */
	int ancestorsClan[6];	/**< X-machine memory variable ancestorsClan of type int. */
	int married;	/**< X-machine memory variable married of type int. */
	int pareja;	/**< X-machine memory variable pareja of type int. */
	int embarazable;	/**< X-machine memory variable embarazable of type int. */
	int month;	/**< X-machine memory variable month of type int. */
	int motherID;	/**< X-machine memory variable motherID of type int. */
	int husband_info[4];	/**< X-machine memory variable husband_info of type int. */
	int widow;	/**< X-machine memory variable widow of type int. */
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
	int x;	/**< X-machine memory variable x of type int. */
	int y;	/**< X-machine memory variable y of type int. */
	int tcalories;	/**< X-machine memory variable tcalories of type int. */
	int leaderID;	/**< X-machine memory variable leaderID of type int. */
	members_needs mneeds;	/**< X-machine memory variable mneeds of type members_needs. */
	indv_free ifree;	/**< X-machine memory variable ifree of type indv_free. */
	int indexID;	/**< X-machine memory variable indexID of type int. */
	int members;	/**< X-machine memory variable members of type int. */
	int linguistics[100];	/**< X-machine memory variable linguistics of type int. */
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
	int gcalories;	/**< X-machine memory variable gcalories of type int. */
	float repo;	/**< X-machine memory variable repo of type float. */
	int tpatch;	/**< X-machine memory variable tpatch of type int. */
	int x;	/**< X-machine memory variable x of type int. */
	int y;	/**< X-machine memory variable y of type int. */
	float repows;	/**< X-machine memory variable repows of type float. */
	float repods;	/**< X-machine memory variable repods of type float. */
	int season;	/**< X-machine memory variable season of type int. */
	int adultos;	/**< X-machine memory variable adultos of type int. */
	int pclans;	/**< X-machine memory variable pclans of type int. */
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
	int familia;	/**< X-machine memory variable familia of type int. */
	int x;	/**< X-machine memory variable x of type int. */
	int y;	/**< X-machine memory variable y of type int. */
	int targetX;	/**< X-machine memory variable targetX of type int. */
	int targetY;	/**< X-machine memory variable targetY of type int. */
	int count;	/**< X-machine memory variable count of type int. */
	int calorias;	/**< X-machine memory variable calorias of type int. */
	int adultos;	/**< X-machine memory variable adultos of type int. */
	int season;	/**< X-machine memory variable season of type int. */
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

/** \var void* FLAME_m_ancestor_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_ancestor_composite_params;

/** \struct m_ancestor
 * \brief Holds message of type ancestor_message.
 */
struct m_ancestor
{
	int ancest[6];	/**< Message memory variable ancest of type int. */
	int ancestClan[6];	/**< Message memory variable ancestClan of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int indvID;	/**< Message memory variable indvID of type int. */
	int sex;	/**< Message memory variable sex of type int. */
};

/** \var void* FLAME_m_peticionID_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_peticionID_composite_params;

/** \struct m_peticionID
 * \brief Holds message of type peticionID_message.
 */
struct m_peticionID
{
	int clanID;	/**< Message memory variable clanID of type int. */
	int id;	/**< Message memory variable id of type int. */
};

/** \var void* FLAME_m_family_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_family_composite_params;

/** \struct m_family
 * \brief Holds message of type family_message.
 */
struct m_family
{
	int wife;	/**< Message memory variable wife of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int husband;	/**< Message memory variable husband of type int. */
	int info[4];	/**< Message memory variable info of type int. */
};

/** \var void* FLAME_m_death_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_death_composite_params;

/** \struct m_death
 * \brief Holds message of type death_message.
 */
struct m_death
{
	int parejaID;	/**< Message memory variable parejaID of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
};

/** \var void* FLAME_m_widow_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_widow_composite_params;

/** \struct m_widow
 * \brief Holds message of type widow_message.
 */
struct m_widow
{
	int ancestors[6];	/**< Message memory variable ancestors of type int. */
	int Cancestors[6];	/**< Message memory variable Cancestors of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int indvID;	/**< Message memory variable indvID of type int. */
};

/** \var void* FLAME_m_informationDivide_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_informationDivide_composite_params;

/** \struct m_informationDivide
 * \brief Holds message of type informationDivide_message.
 */
struct m_informationDivide
{
	int clanID;	/**< Message memory variable clanID of type int. */
	int indvID;	/**< Message memory variable indvID of type int. */
	int parejaID;	/**< Message memory variable parejaID of type int. */
	int sex;	/**< Message memory variable sex of type int. */
	int momID;	/**< Message memory variable momID of type int. */
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

/** \var void* FLAME_m_freeGirls_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_freeGirls_composite_params;

/** \struct m_freeGirls
 * \brief Holds message of type freeGirls_message.
 */
struct m_freeGirls
{
	int girls[100];	/**< Message memory variable girls of type int. */
	int num_chicas;	/**< Message memory variable num_chicas of type int. */
	int y;	/**< Message memory variable y of type int. */
	int x;	/**< Message memory variable x of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int lancestors[600];	/**< Message memory variable lancestors of type int. */
	int lancestorsClan[600];	/**< Message memory variable lancestorsClan of type int. */
	int linguistic[100];	/**< Message memory variable linguistic of type int. */
};

/** \var void* FLAME_m_propuesta_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_propuesta_composite_params;

/** \struct m_propuesta
 * \brief Holds message of type propuesta_message.
 */
struct m_propuesta
{
	int id_list[100];	/**< Message memory variable id_list of type int. */
	int id_man[100];	/**< Message memory variable id_man of type int. */
	int oclanID;	/**< Message memory variable oclanID of type int. */
	int dclanID;	/**< Message memory variable dclanID of type int. */
	int count;	/**< Message memory variable count of type int. */
};

/** \var void* FLAME_m_confirProp_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_confirProp_composite_params;

/** \struct m_confirProp
 * \brief Holds message of type confirProp_message.
 */
struct m_confirProp
{
	int girlID;	/**< Message memory variable girlID of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int manID;	/**< Message memory variable manID of type int. */
	int oclanID;	/**< Message memory variable oclanID of type int. */
	int linguistic[100];	/**< Message memory variable linguistic of type int. */
};

/** \var void* FLAME_m_marriage_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_marriage_composite_params;

/** \struct m_marriage
 * \brief Holds message of type marriage_message.
 */
struct m_marriage
{
	int girlID;	/**< Message memory variable girlID of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int manID;	/**< Message memory variable manID of type int. */
	int oclanID;	/**< Message memory variable oclanID of type int. */
	int newID;	/**< Message memory variable newID of type int. */
};

/** \var void* FLAME_m_respuestaID_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_respuestaID_composite_params;

/** \struct m_respuestaID
 * \brief Holds message of type respuestaID_message.
 */
struct m_respuestaID
{
	int freeID;	/**< Message memory variable freeID of type int. */
	int indvID;	/**< Message memory variable indvID of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
};

/** \var void* FLAME_m_lmarriage_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_lmarriage_composite_params;

/** \struct m_lmarriage
 * \brief Holds message of type lmarriage_message.
 */
struct m_lmarriage
{
	int manID;	/**< Message memory variable manID of type int. */
	int girlID;	/**< Message memory variable girlID of type int. */
	int clanID;	/**< Message memory variable clanID of type int. */
	int mancestorsID[2];	/**< Message memory variable mancestorsID of type int. */
	int mancestorsCID[2];	/**< Message memory variable mancestorsCID of type int. */
};

/** \var void* FLAME_m_warningDivide_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_warningDivide_composite_params;

/** \struct m_warningDivide
 * \brief Holds message of type warningDivide_message.
 */
struct m_warningDivide
{
	int clanID;	/**< Message memory variable clanID of type int. */
};

/** \var void* FLAME_m_clanspatch_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_clanspatch_composite_params;

/** \struct m_clanspatch
 * \brief Holds message of type clanspatch_message.
 */
struct m_clanspatch
{
	int x;	/**< Message memory variable x of type int. */
	int y;	/**< Message memory variable y of type int. */
	int pclans;	/**< Message memory variable pclans of type int. */
};

/** \var void* FLAME_m_adultospatch_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_adultospatch_composite_params;

/** \struct m_adultospatch
 * \brief Holds message of type adultospatch_message.
 */
struct m_adultospatch
{
	int x;	/**< Message memory variable x of type int. */
	int y;	/**< Message memory variable y of type int. */
	int adultos;	/**< Message memory variable adultos of type int. */
	int sentido;	/**< Message memory variable sentido of type int. */
};

/** \var void* FLAME_m_reproduccionguanacos_composite_params\n
 * \brief Pointer to message sync agent composite params */
void* FLAME_m_reproduccionguanacos_composite_params;

/** \struct m_reproduccionguanacos
 * \brief Holds message of type reproduccionguanacos_message.
 */
struct m_reproduccionguanacos
{
	int x;	/**< Message memory variable x of type int. */
	int y;	/**< Message memory variable y of type int. */
	int count;	/**< Message memory variable count of type int. */
	int familia;	/**< Message memory variable familia of type int. */
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

/** \typedef m_ancestor m_ancestor
 * \brief Typedef for m_ancestor struct.
 */
typedef struct m_ancestor m_ancestor;

/** \typedef m_peticionID m_peticionID
 * \brief Typedef for m_peticionID struct.
 */
typedef struct m_peticionID m_peticionID;

/** \typedef m_family m_family
 * \brief Typedef for m_family struct.
 */
typedef struct m_family m_family;

/** \typedef m_death m_death
 * \brief Typedef for m_death struct.
 */
typedef struct m_death m_death;

/** \typedef m_widow m_widow
 * \brief Typedef for m_widow struct.
 */
typedef struct m_widow m_widow;

/** \typedef m_informationDivide m_informationDivide
 * \brief Typedef for m_informationDivide struct.
 */
typedef struct m_informationDivide m_informationDivide;

/** \typedef m_clan_info m_clan_info
 * \brief Typedef for m_clan_info struct.
 */
typedef struct m_clan_info m_clan_info;

/** \typedef m_clangetcalories m_clangetcalories
 * \brief Typedef for m_clangetcalories struct.
 */
typedef struct m_clangetcalories m_clangetcalories;

/** \typedef m_freeGirls m_freeGirls
 * \brief Typedef for m_freeGirls struct.
 */
typedef struct m_freeGirls m_freeGirls;

/** \typedef m_propuesta m_propuesta
 * \brief Typedef for m_propuesta struct.
 */
typedef struct m_propuesta m_propuesta;

/** \typedef m_confirProp m_confirProp
 * \brief Typedef for m_confirProp struct.
 */
typedef struct m_confirProp m_confirProp;

/** \typedef m_marriage m_marriage
 * \brief Typedef for m_marriage struct.
 */
typedef struct m_marriage m_marriage;

/** \typedef m_respuestaID m_respuestaID
 * \brief Typedef for m_respuestaID struct.
 */
typedef struct m_respuestaID m_respuestaID;

/** \typedef m_lmarriage m_lmarriage
 * \brief Typedef for m_lmarriage struct.
 */
typedef struct m_lmarriage m_lmarriage;

/** \typedef m_warningDivide m_warningDivide
 * \brief Typedef for m_warningDivide struct.
 */
typedef struct m_warningDivide m_warningDivide;

/** \typedef m_clanspatch m_clanspatch
 * \brief Typedef for m_clanspatch struct.
 */
typedef struct m_clanspatch m_clanspatch;

/** \typedef m_adultospatch m_adultospatch
 * \brief Typedef for m_adultospatch struct.
 */
typedef struct m_adultospatch m_adultospatch;

/** \typedef m_reproduccionguanacos m_reproduccionguanacos
 * \brief Typedef for m_reproduccionguanacos struct.
 */
typedef struct m_reproduccionguanacos m_reproduccionguanacos;


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
	struct m_ancestor * ancestor_messages;	/**< Pointer to ancestor message list. */
	struct m_peticionID * peticionID_messages;	/**< Pointer to peticionID message list. */
	struct m_family * family_messages;	/**< Pointer to family message list. */
	struct m_death * death_messages;	/**< Pointer to death message list. */
	struct m_widow * widow_messages;	/**< Pointer to widow message list. */
	struct m_informationDivide * informationDivide_messages;	/**< Pointer to informationDivide message list. */
	struct m_clan_info * clan_info_messages;	/**< Pointer to clan_info message list. */
	struct m_clangetcalories * clangetcalories_messages;	/**< Pointer to clangetcalories message list. */
	struct m_freeGirls * freeGirls_messages;	/**< Pointer to freeGirls message list. */
	struct m_propuesta * propuesta_messages;	/**< Pointer to propuesta message list. */
	struct m_confirProp * confirProp_messages;	/**< Pointer to confirProp message list. */
	struct m_marriage * marriage_messages;	/**< Pointer to marriage message list. */
	struct m_respuestaID * respuestaID_messages;	/**< Pointer to respuestaID message list. */
	struct m_lmarriage * lmarriage_messages;	/**< Pointer to lmarriage message list. */
	struct m_warningDivide * warningDivide_messages;	/**< Pointer to warningDivide message list. */
	struct m_clanspatch * clanspatch_messages;	/**< Pointer to clanspatch message list. */
	struct m_adultospatch * adultospatch_messages;	/**< Pointer to adultospatch message list. */
	struct m_reproduccionguanacos * reproduccionguanacos_messages;	/**< Pointer to reproduccionguanacos message list. */

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

/** \var int propegnant
* \brief A constant variable from the environment. */
int FLAME_environment_variable_propegnant;
/** \var int nancestors
* \brief A constant variable from the environment. */
int FLAME_environment_variable_nancestors;
/** \var int learn
* \brief A constant variable from the environment. */
int FLAME_environment_variable_learn;
/** \var int forget
* \brief A constant variable from the environment. */
int FLAME_environment_variable_forget;
/** \var int lang_threshold
* \brief A constant variable from the environment. */
int FLAME_environment_variable_lang_threshold;
/** \var int max_manada
* \brief A constant variable from the environment. */
int FLAME_environment_variable_max_manada;
/** \var int max_familia
* \brief A constant variable from the environment. */
int FLAME_environment_variable_max_familia;
/** \var int cal_adulto
* \brief A constant variable from the environment. */
int FLAME_environment_variable_cal_adulto;
/** \var int surviveChanceAdult
* \brief A constant variable from the environment. */
int FLAME_environment_variable_surviveChanceAdult;
/** \var int surviveChanceChild
* \brief A constant variable from the environment. */
int FLAME_environment_variable_surviveChanceChild;
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
/** \var m_ancestor * temp_ancestor_message
* \brief Pointer to m_ancestor to initialise linked list. */
m_ancestor * temp_ancestor_message;
/** \var m_peticionID * temp_peticionID_message
* \brief Pointer to m_peticionID to initialise linked list. */
m_peticionID * temp_peticionID_message;
/** \var m_family * temp_family_message
* \brief Pointer to m_family to initialise linked list. */
m_family * temp_family_message;
/** \var m_death * temp_death_message
* \brief Pointer to m_death to initialise linked list. */
m_death * temp_death_message;
/** \var m_widow * temp_widow_message
* \brief Pointer to m_widow to initialise linked list. */
m_widow * temp_widow_message;
/** \var m_informationDivide * temp_informationDivide_message
* \brief Pointer to m_informationDivide to initialise linked list. */
m_informationDivide * temp_informationDivide_message;
/** \var m_clan_info * temp_clan_info_message
* \brief Pointer to m_clan_info to initialise linked list. */
m_clan_info * temp_clan_info_message;
/** \var m_clangetcalories * temp_clangetcalories_message
* \brief Pointer to m_clangetcalories to initialise linked list. */
m_clangetcalories * temp_clangetcalories_message;
/** \var m_freeGirls * temp_freeGirls_message
* \brief Pointer to m_freeGirls to initialise linked list. */
m_freeGirls * temp_freeGirls_message;
/** \var m_propuesta * temp_propuesta_message
* \brief Pointer to m_propuesta to initialise linked list. */
m_propuesta * temp_propuesta_message;
/** \var m_confirProp * temp_confirProp_message
* \brief Pointer to m_confirProp to initialise linked list. */
m_confirProp * temp_confirProp_message;
/** \var m_marriage * temp_marriage_message
* \brief Pointer to m_marriage to initialise linked list. */
m_marriage * temp_marriage_message;
/** \var m_respuestaID * temp_respuestaID_message
* \brief Pointer to m_respuestaID to initialise linked list. */
m_respuestaID * temp_respuestaID_message;
/** \var m_lmarriage * temp_lmarriage_message
* \brief Pointer to m_lmarriage to initialise linked list. */
m_lmarriage * temp_lmarriage_message;
/** \var m_warningDivide * temp_warningDivide_message
* \brief Pointer to m_warningDivide to initialise linked list. */
m_warningDivide * temp_warningDivide_message;
/** \var m_clanspatch * temp_clanspatch_message
* \brief Pointer to m_clanspatch to initialise linked list. */
m_clanspatch * temp_clanspatch_message;
/** \var m_adultospatch * temp_adultospatch_message
* \brief Pointer to m_adultospatch to initialise linked list. */
m_adultospatch * temp_adultospatch_message;
/** \var m_reproduccionguanacos * temp_reproduccionguanacos_message
* \brief Pointer to m_reproduccionguanacos to initialise linked list. */
m_reproduccionguanacos * temp_reproduccionguanacos_message;
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
/* Pointer to list of indv agents in state 13 state */
//xmachine_memory_indv * temp_xmachine_indv_13;
xmachine_memory_indv_state * indv_13_state;
/* Pointer to list of indv agents in state 12 state */
//xmachine_memory_indv * temp_xmachine_indv_12;
xmachine_memory_indv_state * indv_12_state;
/* Pointer to list of indv agents in state 11 state */
//xmachine_memory_indv * temp_xmachine_indv_11;
xmachine_memory_indv_state * indv_11_state;
/* Pointer to list of indv agents in state 10 state */
//xmachine_memory_indv * temp_xmachine_indv_10;
xmachine_memory_indv_state * indv_10_state;
/* Pointer to list of indv agents in state 08 state */
//xmachine_memory_indv * temp_xmachine_indv_08;
xmachine_memory_indv_state * indv_08_state;
/* Pointer to list of indv agents in state 07 state */
//xmachine_memory_indv * temp_xmachine_indv_07;
xmachine_memory_indv_state * indv_07_state;
/* Pointer to list of indv agents in state 09 state */
//xmachine_memory_indv * temp_xmachine_indv_09;
xmachine_memory_indv_state * indv_09_state;
/* Pointer to list of indv agents in state 05 state */
//xmachine_memory_indv * temp_xmachine_indv_05;
xmachine_memory_indv_state * indv_05_state;
/* Pointer to list of indv agents in state 06 state */
//xmachine_memory_indv * temp_xmachine_indv_06;
xmachine_memory_indv_state * indv_06_state;
/* Pointer to list of indv agents in state 04 state */
//xmachine_memory_indv * temp_xmachine_indv_04;
xmachine_memory_indv_state * indv_04_state;
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
/* Pointer to list of clan agents in state 13 state */
//xmachine_memory_clan * temp_xmachine_clan_13;
xmachine_memory_clan_state * clan_13_state;
/* Pointer to list of clan agents in state 12 state */
//xmachine_memory_clan * temp_xmachine_clan_12;
xmachine_memory_clan_state * clan_12_state;
/* Pointer to list of clan agents in state 11 state */
//xmachine_memory_clan * temp_xmachine_clan_11;
xmachine_memory_clan_state * clan_11_state;
/* Pointer to list of clan agents in state 10 state */
//xmachine_memory_clan * temp_xmachine_clan_10;
xmachine_memory_clan_state * clan_10_state;
/* Pointer to list of clan agents in state 09 state */
//xmachine_memory_clan * temp_xmachine_clan_09;
xmachine_memory_clan_state * clan_09_state;
/* Pointer to list of clan agents in state 08 state */
//xmachine_memory_clan * temp_xmachine_clan_08;
xmachine_memory_clan_state * clan_08_state;
/* Pointer to list of clan agents in state 07 state */
//xmachine_memory_clan * temp_xmachine_clan_07;
xmachine_memory_clan_state * clan_07_state;
/* Pointer to list of clan agents in state 06 state */
//xmachine_memory_clan * temp_xmachine_clan_06;
xmachine_memory_clan_state * clan_06_state;
/* Pointer to list of clan agents in state 05 state */
//xmachine_memory_clan * temp_xmachine_clan_05;
xmachine_memory_clan_state * clan_05_state;
/* Pointer to list of clan agents in state 04 state */
//xmachine_memory_clan * temp_xmachine_clan_04;
xmachine_memory_clan_state * clan_04_state;
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
/* Pointer to list of patch agents in state 5 state */
//xmachine_memory_patch * temp_xmachine_patch_5;
xmachine_memory_patch_state * patch_5_state;
/* Pointer to list of patch agents in state 4 state */
//xmachine_memory_patch * temp_xmachine_patch_4;
xmachine_memory_patch_state * patch_4_state;
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
/* Pointer to list of manada_guanacos agents in state 3 state */
//xmachine_memory_manada_guanacos * temp_xmachine_manada_guanacos_3;
xmachine_memory_manada_guanacos_state * manada_guanacos_3_state;
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

MBt_Board b_ancestor;
MBt_Iterator i_ancestor;

MBt_Board b_peticionID;
MBt_Iterator i_peticionID;

MBt_Board b_family;
MBt_Iterator i_family;

MBt_Board b_death;
MBt_Iterator i_death;

MBt_Board b_widow;
MBt_Iterator i_widow;

MBt_Board b_informationDivide;
MBt_Iterator i_informationDivide;

MBt_Board b_clan_info;
MBt_Iterator i_clan_info;

MBt_Board b_clangetcalories;
MBt_Iterator i_clangetcalories;

MBt_Board b_freeGirls;
MBt_Iterator i_freeGirls;

MBt_Board b_propuesta;
MBt_Iterator i_propuesta;

MBt_Board b_confirProp;
MBt_Iterator i_confirProp;

MBt_Board b_marriage;
MBt_Iterator i_marriage;

MBt_Board b_respuestaID;
MBt_Iterator i_respuestaID;

MBt_Board b_lmarriage;
MBt_Iterator i_lmarriage;

MBt_Board b_warningDivide;
MBt_Iterator i_warningDivide;

MBt_Board b_clanspatch;
MBt_Iterator i_clanspatch;

MBt_Board b_adultospatch;
MBt_Iterator i_adultospatch;

MBt_Board b_reproduccionguanacos;
MBt_Iterator i_reproduccionguanacos;


/** \var m_information * information_message
* \brief Pointer to message struct for looping through information message list */
m_information * information_message;
/** \var m_indgetcalories * indgetcalories_message
* \brief Pointer to message struct for looping through indgetcalories message list */
m_indgetcalories * indgetcalories_message;
/** \var m_leader * leader_message
* \brief Pointer to message struct for looping through leader message list */
m_leader * leader_message;
/** \var m_ancestor * ancestor_message
* \brief Pointer to message struct for looping through ancestor message list */
m_ancestor * ancestor_message;
/** \var m_peticionID * peticionID_message
* \brief Pointer to message struct for looping through peticionID message list */
m_peticionID * peticionID_message;
/** \var m_family * family_message
* \brief Pointer to message struct for looping through family message list */
m_family * family_message;
/** \var m_death * death_message
* \brief Pointer to message struct for looping through death message list */
m_death * death_message;
/** \var m_widow * widow_message
* \brief Pointer to message struct for looping through widow message list */
m_widow * widow_message;
/** \var m_informationDivide * informationDivide_message
* \brief Pointer to message struct for looping through informationDivide message list */
m_informationDivide * informationDivide_message;
/** \var m_clan_info * clan_info_message
* \brief Pointer to message struct for looping through clan_info message list */
m_clan_info * clan_info_message;
/** \var m_clangetcalories * clangetcalories_message
* \brief Pointer to message struct for looping through clangetcalories message list */
m_clangetcalories * clangetcalories_message;
/** \var m_freeGirls * freeGirls_message
* \brief Pointer to message struct for looping through freeGirls message list */
m_freeGirls * freeGirls_message;
/** \var m_propuesta * propuesta_message
* \brief Pointer to message struct for looping through propuesta message list */
m_propuesta * propuesta_message;
/** \var m_confirProp * confirProp_message
* \brief Pointer to message struct for looping through confirProp message list */
m_confirProp * confirProp_message;
/** \var m_marriage * marriage_message
* \brief Pointer to message struct for looping through marriage message list */
m_marriage * marriage_message;
/** \var m_respuestaID * respuestaID_message
* \brief Pointer to message struct for looping through respuestaID message list */
m_respuestaID * respuestaID_message;
/** \var m_lmarriage * lmarriage_message
* \brief Pointer to message struct for looping through lmarriage message list */
m_lmarriage * lmarriage_message;
/** \var m_warningDivide * warningDivide_message
* \brief Pointer to message struct for looping through warningDivide message list */
m_warningDivide * warningDivide_message;
/** \var m_clanspatch * clanspatch_message
* \brief Pointer to message struct for looping through clanspatch message list */
m_clanspatch * clanspatch_message;
/** \var m_adultospatch * adultospatch_message
* \brief Pointer to message struct for looping through adultospatch message list */
m_adultospatch * adultospatch_message;
/** \var m_reproduccionguanacos * reproduccionguanacos_message
* \brief Pointer to message struct for looping through reproduccionguanacos message list */
m_reproduccionguanacos * reproduccionguanacos_message;
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

void init_indv_free_array(indv_free_array * array);
void reset_indv_free_array(indv_free_array * array);
void free_indv_free_array(indv_free_array * array);
void copy_indv_free_array(indv_free_array * from, indv_free_array * to);
void add_indv_free(indv_free_array * array, /*@out@*/ int * male_list, /*@out@*/ int * female_list, /*@out@*/ int * mancestor_list, /*@out@*/ int * fancestor_list, /*@out@*/ int * mancestorClan_list, /*@out@*/ int * fancestorClan_list,  int numMale,  int numFemale);
void remove_indv_free(indv_free_array * array, int index);

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
void init_indv_free(/*@out@*/ indv_free * temp);
void init_indv_free_static_array(/*@out@*/ indv_free * array, int size);
int read_indv_free(char * buffer, int buffer_size, int * j, indv_free * temp_datatype);
int read_indv_free_dynamic_array(char * buffer, int buffer_size, int * j, indv_free_array * temp_datatype_array);
int read_indv_free_static_array(char * buffer, int buffer_size, int * j, indv_free * temp_datatype_array, int size);
void write_indv_free(FILE *file, indv_free * temp_datatype);
void write_indv_free_static_array(FILE *file, indv_free * temp_datatype, int size);
void write_indv_free_dynamic_array(FILE *file, indv_free_array * temp_datatype);

void readinitialstates(char * filename, char * filelocation, int * itno, double cloud_data[],
					   int partition_method, int flag);
void saveiterationdata(int iteration_number);

void free_members_needs(members_needs * temp);
void free_members_needs_static_array(members_needs * array, int size);
void copy_members_needs(members_needs * from, members_needs * to);
void copy_members_needs_static_array(members_needs * from, members_needs * to, int size);
void free_indv_free(indv_free * temp);
void free_indv_free_static_array(indv_free * array, int size);
void copy_indv_free(indv_free * from, indv_free * to);
void copy_indv_free_static_array(indv_free * from, indv_free * to, int size);

xmachine_memory_indv_state * init_indv_state();
xmachine_memory_indv * init_indv_agent();
void free_indv_agent(xmachine_memory_indv_holder * tmp, xmachine_memory_indv_state * state);
void transition_indv_agent(xmachine_memory_indv_holder * tmp, xmachine_memory_indv_state * from_state, xmachine_memory_indv_state * to_state);
void add_indv_agent_internal(xmachine_memory_indv * agent, xmachine_memory_indv_state * state);
void add_indv_agent(int indvID, int cID, int cal_needs, int icalories, int patchID, int age, int sex, int pregnant, int lead, int marriable, int ancestors[], int ancestorsClan[], int married, int pareja, int embarazable, int month, int motherID, int husband_info[], int widow);
void unittest_init_indv_agent();
void unittest_free_indv_agent();
xmachine_memory_clan_state * init_clan_state();
xmachine_memory_clan * init_clan_agent();
void free_clan_agent(xmachine_memory_clan_holder * tmp, xmachine_memory_clan_state * state);
void transition_clan_agent(xmachine_memory_clan_holder * tmp, xmachine_memory_clan_state * from_state, xmachine_memory_clan_state * to_state);
void add_clan_agent_internal(xmachine_memory_clan * agent, xmachine_memory_clan_state * state);
void add_clan_agent(int cID, int cal_need, int cal_got, int cal_stored, int x, int y, int tcalories, int leaderID, members_needs mneeds, indv_free ifree, int indexID, int members, int linguistics[]);
void unittest_init_clan_agent();
void unittest_free_clan_agent();
xmachine_memory_patch_state * init_patch_state();
xmachine_memory_patch * init_patch_agent();
void free_patch_agent(xmachine_memory_patch_holder * tmp, xmachine_memory_patch_state * state);
void transition_patch_agent(xmachine_memory_patch_holder * tmp, xmachine_memory_patch_state * from_state, xmachine_memory_patch_state * to_state);
void add_patch_agent_internal(xmachine_memory_patch * agent, xmachine_memory_patch_state * state);
void add_patch_agent(int patchID, int pcalories, int gcalories, float repo, int tpatch, int x, int y, float repows, float repods, int season, int adultos, int pclans);
void unittest_init_patch_agent();
void unittest_free_patch_agent();
xmachine_memory_manada_guanacos_state * init_manada_guanacos_state();
xmachine_memory_manada_guanacos * init_manada_guanacos_agent();
void free_manada_guanacos_agent(xmachine_memory_manada_guanacos_holder * tmp, xmachine_memory_manada_guanacos_state * state);
void transition_manada_guanacos_agent(xmachine_memory_manada_guanacos_holder * tmp, xmachine_memory_manada_guanacos_state * from_state, xmachine_memory_manada_guanacos_state * to_state);
void add_manada_guanacos_agent_internal(xmachine_memory_manada_guanacos * agent, xmachine_memory_manada_guanacos_state * state);
void add_manada_guanacos_agent(int familia, int x, int y, int targetX, int targetY, int count, int calorias, int adultos, int season);
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

void add_ancestor_message(int ancest[], int ancestClan[], int clanID, int indvID, int sex);
m_ancestor * add_ancestor_message_internal(void);
m_ancestor * get_first_ancestor_message(void);
m_ancestor * get_next_ancestor_message(m_ancestor * current);
void freeancestormessages(void);

void add_peticionID_message(int clanID, int id);
m_peticionID * add_peticionID_message_internal(void);
m_peticionID * get_first_peticionID_message(void);
m_peticionID * get_next_peticionID_message(m_peticionID * current);
void freepeticionIDmessages(void);

void add_family_message(int wife, int clanID, int husband, int info[]);
m_family * add_family_message_internal(void);
m_family * get_first_family_message(void);
m_family * get_next_family_message(m_family * current);
void freefamilymessages(void);

void add_death_message(int parejaID, int clanID);
m_death * add_death_message_internal(void);
m_death * get_first_death_message(void);
m_death * get_next_death_message(m_death * current);
void freedeathmessages(void);

void add_widow_message(int ancestors[], int Cancestors[], int clanID, int indvID);
m_widow * add_widow_message_internal(void);
m_widow * get_first_widow_message(void);
m_widow * get_next_widow_message(m_widow * current);
void freewidowmessages(void);

void add_informationDivide_message(int clanID, int indvID, int parejaID, int sex, int momID, int age);
m_informationDivide * add_informationDivide_message_internal(void);
m_informationDivide * get_first_informationDivide_message(void);
m_informationDivide * get_next_informationDivide_message(m_informationDivide * current);
void freeinformationDividemessages(void);

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

void add_freeGirls_message(int girls[], int num_chicas, int y, int x, int clanID, int lancestors[], int lancestorsClan[], int linguistic[]);
m_freeGirls * add_freeGirls_message_internal(void);
m_freeGirls * get_first_freeGirls_message(void);
m_freeGirls * get_next_freeGirls_message(m_freeGirls * current);
void freefreeGirlsmessages(void);

void add_propuesta_message(int id_list[], int id_man[], int oclanID, int dclanID, int count);
m_propuesta * add_propuesta_message_internal(void);
m_propuesta * get_first_propuesta_message(void);
m_propuesta * get_next_propuesta_message(m_propuesta * current);
void freepropuestamessages(void);

void add_confirProp_message(int girlID, int clanID, int manID, int oclanID, int linguistic[]);
m_confirProp * add_confirProp_message_internal(void);
m_confirProp * get_first_confirProp_message(void);
m_confirProp * get_next_confirProp_message(m_confirProp * current);
void freeconfirPropmessages(void);

void add_marriage_message(int girlID, int clanID, int manID, int oclanID, int newID);
m_marriage * add_marriage_message_internal(void);
m_marriage * get_first_marriage_message(void);
m_marriage * get_next_marriage_message(m_marriage * current);
void freemarriagemessages(void);

void add_respuestaID_message(int freeID, int indvID, int clanID);
m_respuestaID * add_respuestaID_message_internal(void);
m_respuestaID * get_first_respuestaID_message(void);
m_respuestaID * get_next_respuestaID_message(m_respuestaID * current);
void freerespuestaIDmessages(void);

void add_lmarriage_message(int manID, int girlID, int clanID, int mancestorsID[], int mancestorsCID[]);
m_lmarriage * add_lmarriage_message_internal(void);
m_lmarriage * get_first_lmarriage_message(void);
m_lmarriage * get_next_lmarriage_message(m_lmarriage * current);
void freelmarriagemessages(void);

void add_warningDivide_message(int clanID);
m_warningDivide * add_warningDivide_message_internal(void);
m_warningDivide * get_first_warningDivide_message(void);
m_warningDivide * get_next_warningDivide_message(m_warningDivide * current);
void freewarningDividemessages(void);

void add_clanspatch_message(int x, int y, int pclans);
m_clanspatch * add_clanspatch_message_internal(void);
m_clanspatch * get_first_clanspatch_message(void);
m_clanspatch * get_next_clanspatch_message(m_clanspatch * current);
void freeclanspatchmessages(void);

void add_adultospatch_message(int x, int y, int adultos, int sentido);
m_adultospatch * add_adultospatch_message_internal(void);
m_adultospatch * get_first_adultospatch_message(void);
m_adultospatch * get_next_adultospatch_message(m_adultospatch * current);
void freeadultospatchmessages(void);

void add_reproduccionguanacos_message(int x, int y, int count, int familia);
m_reproduccionguanacos * add_reproduccionguanacos_message_internal(void);
m_reproduccionguanacos * get_first_reproduccionguanacos_message(void);
m_reproduccionguanacos * get_next_reproduccionguanacos_message(m_reproduccionguanacos * current);
void freereproduccionguanacosmessages(void);


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
void set_marriable(int marriable);
int get_marriable();
int * get_ancestors();
int * get_ancestorsClan();
void set_married(int married);
int get_married();
void set_pareja(int pareja);
int get_pareja();
void set_embarazable(int embarazable);
int get_embarazable();
void set_month(int month);
int get_month();
void set_motherID(int motherID);
int get_motherID();
int * get_husband_info();
void set_widow(int widow);
int get_widow();
void set_cal_need(int cal_need);
int get_cal_need();
void set_cal_got(int cal_got);
int get_cal_got();
void set_cal_stored(int cal_stored);
int get_cal_stored();
void set_x(int x);
int get_x();
void set_y(int y);
int get_y();
void set_tcalories(int tcalories);
int get_tcalories();
void set_leaderID(int leaderID);
int get_leaderID();
members_needs * get_mneeds();
indv_free * get_ifree();
void set_indexID(int indexID);
int get_indexID();
void set_members(int members);
int get_members();
int * get_linguistics();
void set_pcalories(int pcalories);
int get_pcalories();
void set_gcalories(int gcalories);
int get_gcalories();
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
void set_adultos(int adultos);
int get_adultos();
void set_pclans(int pclans);
int get_pclans();
void set_familia(int familia);
int get_familia();
void set_targetX(int targetX);
int get_targetX();
void set_targetY(int targetY);
int get_targetY();
void set_count(int count);
int get_count();
void set_calorias(int calorias);
int get_calorias();
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



m_ancestor * get_next_message_ancestor_in_range(m_ancestor * current);



m_peticionID * get_next_message_peticionID_in_range(m_peticionID * current);



m_family * get_next_message_family_in_range(m_family * current);



m_death * get_next_message_death_in_range(m_death * current);



m_widow * get_next_message_widow_in_range(m_widow * current);



m_informationDivide * get_next_message_informationDivide_in_range(m_informationDivide * current);



m_clan_info * get_next_message_clan_info_in_range(m_clan_info * current);



m_clangetcalories * get_next_message_clangetcalories_in_range(m_clangetcalories * current);



m_freeGirls * get_next_message_freeGirls_in_range(m_freeGirls * current);
double freeGirls_message_extract_x(void *msg_ptr);
double freeGirls_message_extract_y(void *msg_ptr);

m_propuesta * get_next_message_propuesta_in_range(m_propuesta * current);



m_confirProp * get_next_message_confirProp_in_range(m_confirProp * current);



m_marriage * get_next_message_marriage_in_range(m_marriage * current);



m_respuestaID * get_next_message_respuestaID_in_range(m_respuestaID * current);



m_lmarriage * get_next_message_lmarriage_in_range(m_lmarriage * current);



m_warningDivide * get_next_message_warningDivide_in_range(m_warningDivide * current);



m_clanspatch * get_next_message_clanspatch_in_range(m_clanspatch * current);
double clanspatch_message_extract_x(void *msg_ptr);
double clanspatch_message_extract_y(void *msg_ptr);

m_adultospatch * get_next_message_adultospatch_in_range(m_adultospatch * current);



m_reproduccionguanacos * get_next_message_reproduccionguanacos_in_range(m_reproduccionguanacos * current);




/* memory.c */
xmachine * add_xmachine(void);
int FLAME_get_environment_variable_propegnant();
int FLAME_get_environment_variable_nancestors();
int FLAME_get_environment_variable_learn();
int FLAME_get_environment_variable_forget();
int FLAME_get_environment_variable_lang_threshold();
int FLAME_get_environment_variable_max_manada();
int FLAME_get_environment_variable_max_familia();
int FLAME_get_environment_variable_cal_adulto();
int FLAME_get_environment_variable_surviveChanceAdult();
int FLAME_get_environment_variable_surviveChanceChild();


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
int freeIndv(void);
int FLAME_condition_indv_freeIndv_03_04(xmachine_memory_indv *a);

int FLAME_condition_indv_idle_03_06(xmachine_memory_indv *a);
int casamiento_female(void);
int FLAME_condition_indv_casamiento_female_04_05(xmachine_memory_indv *a);
int FLAME_filter_indv_casamiento_female_04_05_marriage(const void *msg, const void *params);
int casamiento_male(void);
int FLAME_condition_indv_casamiento_male_04_06(xmachine_memory_indv *a);
int FLAME_filter_indv_casamiento_male_04_06_marriage(const void *msg, const void *params);
int info_husband(void);
int FLAME_condition_indv_info_husband_05_06(xmachine_memory_indv *a);
int FLAME_filter_indv_info_husband_05_06_family(const void *msg, const void *params);

int FLAME_condition_indv_idle_05_06(xmachine_memory_indv *a);
int pregnancy(void);
int FLAME_condition_indv_pregnancy_06_09(xmachine_memory_indv *a);

int FLAME_condition_indv_idle_06_07(xmachine_memory_indv *a);
int child_inf(void);
int FLAME_condition_indv_child_inf_07_08(xmachine_memory_indv *a);

int FLAME_condition_indv_idle_07_09(xmachine_memory_indv *a);
int birth(void);
int FLAME_filter_indv_birth_08_09_respuestaID(const void *msg, const void *params);
int survive(void);
int update_status(void);
int FLAME_filter_indv_update_status_10_11_death(const void *msg, const void *params);
int husband_request(void);
int FLAME_condition_indv_husband_request_11_12(xmachine_memory_indv *a);

int FLAME_condition_indv_idle_11_12(xmachine_memory_indv *a);
int local_marriage(void);
int FLAME_condition_indv_local_marriage_12_13(xmachine_memory_indv *a);
int FLAME_filter_indv_local_marriage_12_13_lmarriage(const void *msg, const void *params);

int FLAME_condition_indv_idle_12_13(xmachine_memory_indv *a);
int dividir_info(void);
int FLAME_filter_indv_dividir_info_13_end_warningDivide(const void *msg, const void *params);
int clan_Information(void);
int FLAME_filter_clan_clan_Information_start_01_information(const void *msg, const void *params);
int clan_extract_calories(void);
int FLAME_filter_clan_clan_extract_calories_01_02_clangetcalories(const void *msg, const void *params);
int distribute_calories(void);
int marriable_indv(void);
int FLAME_filter_clan_marriable_indv_03_04_ancestor(const void *msg, const void *params);
int send_girls(void);
int match(void);
int FLAME_filter_clan_match_05_06_freeGirls(const void *msg, const void *params);
int aceptar_prop(void);
int FLAME_filter_clan_aceptar_prop_06_07_propuesta(const void *msg, const void *params);
int recive_conf(void);
int FLAME_filter_clan_recive_conf_07_08_confirProp(const void *msg, const void *params);
int repartir_id(void);
int FLAME_filter_clan_repartir_id_08_09_peticionID(const void *msg, const void *params);
int new_leader(void);
int FLAME_filter_clan_new_leader_09_10_leader(const void *msg, const void *params);
int again_marriable(void);
int FLAME_filter_clan_again_marriable_10_11_widow(const void *msg, const void *params);
int dividir_clan(void);
int FLAME_condition_clan_dividir_clan_11_12(xmachine_memory_clan *a);

int FLAME_condition_clan_idle_11_13(xmachine_memory_clan *a);
int creacion_clan(void);
int FLAME_filter_clan_creacion_clan_12_13_informationDivide(const void *msg, const void *params);
int FLAME_sort_clan_creacion_clan_12_13_informationDivide();
int vocabulary_review(void);
int FLAME_condition_clan_vocabulary_review_13_end(xmachine_memory_clan *a);

int FLAME_condition_clan_idle_13_end(xmachine_memory_clan *a);
int patchtype(void);
int FLAME_condition_patch_patchtype_start_1(xmachine_memory_patch *a);
int infoClansInPatch(void);
int FLAME_condition_patch_infoClansInPatch_start_1(xmachine_memory_patch *a);
int patchcalories(void);
int FLAME_filter_patch_patchcalories_1_2_clan_info(const void *msg, const void *params);
int regenerate(void);
int FLAME_condition_patch_regenerate_2_3(xmachine_memory_patch *a);
int idle_patch(void);
int FLAME_condition_patch_idle_patch_2_3(xmachine_memory_patch *a);
int snregenerate(void);
int FLAME_condition_patch_snregenerate_3_4(xmachine_memory_patch *a);
int idle_patch(void);
int FLAME_condition_patch_idle_patch_3_4(xmachine_memory_patch *a);
int guanacos_move(void);
int FLAME_filter_patch_guanacos_move_4_5_adultospatch(const void *msg, const void *params);
int reproduccion_guanacos(void);
int FLAME_condition_patch_reproduccion_guanacos_5_end(xmachine_memory_patch *a);
int FLAME_filter_patch_reproduccion_guanacos_5_end_reproduccionguanacos(const void *msg, const void *params);
int idle_patch(void);
int FLAME_condition_patch_idle_patch_5_end(xmachine_memory_patch *a);
int manadaInfo(void);
int FLAME_condition_manada_guanacos_manadaInfo_start_1(xmachine_memory_manada_guanacos *a);
int seasonSwitch(void);
int FLAME_condition_manada_guanacos_seasonSwitch_start_1(xmachine_memory_manada_guanacos *a);
int manada_idle(void);
int FLAME_condition_manada_guanacos_manada_idle_1_2(xmachine_memory_manada_guanacos *a);
int move(void);
int FLAME_condition_manada_guanacos_move_1_2(xmachine_memory_manada_guanacos *a);
int FLAME_filter_manada_guanacos_move_1_2_clanspatch(const void *msg, const void *params);
int reproduccion(void);
int FLAME_condition_manada_guanacos_reproduccion_2_3(xmachine_memory_manada_guanacos *a);
int manada_idle2(void);
int FLAME_condition_manada_guanacos_manada_idle2_2_3(xmachine_memory_manada_guanacos *a);
int surviveGuanacos(void);
#endif
