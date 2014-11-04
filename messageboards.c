/**
 * \file  messageboards.c
 * \brief Holds message board functions.
 */

#include "header.h"



/* Box filtering functions */




union pu_information 
{
    m_information *ptr;
    void *ptr_anon;
};

/** \fn void add_information_message(int id, int clanID, int cal, int age, int pregnant)
 * \brief Add information message by calling internal and processing.
 * \param id Message variable.
 * \param clanID Message variable.
 * \param cal Message variable.
 * \param age Message variable.
 * \param pregnant Message variable.
 */
void add_information_message(int id, int clanID, int cal, int age, int pregnant)
{
    int rc;
	m_information msg;
    
    msg.id = id;
    msg.clanID = clanID;
    msg.cal = cal;
    msg.age = age;
    msg.pregnant = pregnant;
    
    
    rc = MB_AddMessage(b_information, &msg);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not add message to 'information' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'information' board has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'information' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_AddMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	   }
	      
	   
       exit(rc);
    }
    #endif
}

inline static m_information* getInternalMessage_information(void)
{
    static m_information *msg_prev = NULL;
    union pu_information msg_pu;
    int rc;
    
    /* deallocate previously returned message */
    if (msg_prev != NULL) 
    {
        free(msg_prev);
    }
    else 
    {
        rc = MB_Iterator_Rewind(i_information); 
        #ifdef ERRCHECK
        if (rc != MB_SUCCESS)
        {
            fprintf(stderr, "ERROR: Could not rewind 'information' Iterator\n");
            switch(rc) {
                case MB_ERR_INVALID:
                    fprintf(stderr, "\t reason: 'information' Iterator has not been created?\n");
                    break;
	            default:
                    fprintf(stderr, "\t MB_Iterator_Rewind returned error code: %d (see libmboard docs for details)\n", rc);
                    break;
	        }
	       
	       
       	   exit(rc);
        }
        #endif
    }
    
    /* get next message from iterator */
    rc = MB_Iterator_GetMessage(i_information, &(msg_pu.ptr_anon));
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not get message from 'information' Iterator\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'information' Iterator has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Iterator_GetMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }
	       
	       
       	   exit(rc);
    }
    #endif
    
    /* store pointer so memory can be deallocated later */
    msg_prev = msg_pu.ptr;
    
    return msg_pu.ptr;
}

/** \fn xmachine_message_information * get_first_information_message()
 * \brief Get the first information message in the information message list.
 * \return The first message in the list.
 */
m_information * get_first_information_message()
{
	return getInternalMessage_information();
}

/** \fn xmachine_message_information * get_next_information_message(xmachine_message_information * current)
 * \brief Get the next information message in the information message list after the current message.
 * \param current The current message in the list.
 * \return The next message in the list.
 */
m_information * get_next_information_message(m_information * current)
{
	return getInternalMessage_information();
}


/* Box filtering functions */




union pu_indgetcalories 
{
    m_indgetcalories *ptr;
    void *ptr_anon;
};

/** \fn void add_indgetcalories_message(int icalories, int indvID)
 * \brief Add indgetcalories message by calling internal and processing.
 * \param icalories Message variable.
 * \param indvID Message variable.
 */
void add_indgetcalories_message(int icalories, int indvID)
{
    int rc;
	m_indgetcalories msg;
    
    msg.icalories = icalories;
    msg.indvID = indvID;
    
    
    rc = MB_AddMessage(b_indgetcalories, &msg);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not add message to 'indgetcalories' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'indgetcalories' board has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'indgetcalories' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_AddMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	   }
	      
	   
       exit(rc);
    }
    #endif
}

inline static m_indgetcalories* getInternalMessage_indgetcalories(void)
{
    static m_indgetcalories *msg_prev = NULL;
    union pu_indgetcalories msg_pu;
    int rc;
    
    /* deallocate previously returned message */
    if (msg_prev != NULL) 
    {
        free(msg_prev);
    }
    else 
    {
        rc = MB_Iterator_Rewind(i_indgetcalories); 
        #ifdef ERRCHECK
        if (rc != MB_SUCCESS)
        {
            fprintf(stderr, "ERROR: Could not rewind 'indgetcalories' Iterator\n");
            switch(rc) {
                case MB_ERR_INVALID:
                    fprintf(stderr, "\t reason: 'indgetcalories' Iterator has not been created?\n");
                    break;
	            default:
                    fprintf(stderr, "\t MB_Iterator_Rewind returned error code: %d (see libmboard docs for details)\n", rc);
                    break;
	        }
	       
	       
       	   exit(rc);
        }
        #endif
    }
    
    /* get next message from iterator */
    rc = MB_Iterator_GetMessage(i_indgetcalories, &(msg_pu.ptr_anon));
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not get message from 'indgetcalories' Iterator\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'indgetcalories' Iterator has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Iterator_GetMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }
	       
	       
       	   exit(rc);
    }
    #endif
    
    /* store pointer so memory can be deallocated later */
    msg_prev = msg_pu.ptr;
    
    return msg_pu.ptr;
}

/** \fn xmachine_message_indgetcalories * get_first_indgetcalories_message()
 * \brief Get the first indgetcalories message in the indgetcalories message list.
 * \return The first message in the list.
 */
m_indgetcalories * get_first_indgetcalories_message()
{
	return getInternalMessage_indgetcalories();
}

/** \fn xmachine_message_indgetcalories * get_next_indgetcalories_message(xmachine_message_indgetcalories * current)
 * \brief Get the next indgetcalories message in the indgetcalories message list after the current message.
 * \param current The current message in the list.
 * \return The next message in the list.
 */
m_indgetcalories * get_next_indgetcalories_message(m_indgetcalories * current)
{
	return getInternalMessage_indgetcalories();
}


/* Box filtering functions */




union pu_leader 
{
    m_leader *ptr;
    void *ptr_anon;
};

/** \fn void add_leader_message(int id, int clanID, int leader, int sex, int age)
 * \brief Add leader message by calling internal and processing.
 * \param id Message variable.
 * \param clanID Message variable.
 * \param leader Message variable.
 * \param sex Message variable.
 * \param age Message variable.
 */
void add_leader_message(int id, int clanID, int leader, int sex, int age)
{
    int rc;
	m_leader msg;
    
    msg.id = id;
    msg.clanID = clanID;
    msg.leader = leader;
    msg.sex = sex;
    msg.age = age;
    
    
    rc = MB_AddMessage(b_leader, &msg);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not add message to 'leader' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'leader' board has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'leader' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_AddMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	   }
	      
	   
       exit(rc);
    }
    #endif
}

inline static m_leader* getInternalMessage_leader(void)
{
    static m_leader *msg_prev = NULL;
    union pu_leader msg_pu;
    int rc;
    
    /* deallocate previously returned message */
    if (msg_prev != NULL) 
    {
        free(msg_prev);
    }
    else 
    {
        rc = MB_Iterator_Rewind(i_leader); 
        #ifdef ERRCHECK
        if (rc != MB_SUCCESS)
        {
            fprintf(stderr, "ERROR: Could not rewind 'leader' Iterator\n");
            switch(rc) {
                case MB_ERR_INVALID:
                    fprintf(stderr, "\t reason: 'leader' Iterator has not been created?\n");
                    break;
	            default:
                    fprintf(stderr, "\t MB_Iterator_Rewind returned error code: %d (see libmboard docs for details)\n", rc);
                    break;
	        }
	       
	       
       	   exit(rc);
        }
        #endif
    }
    
    /* get next message from iterator */
    rc = MB_Iterator_GetMessage(i_leader, &(msg_pu.ptr_anon));
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not get message from 'leader' Iterator\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'leader' Iterator has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Iterator_GetMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }
	       
	       
       	   exit(rc);
    }
    #endif
    
    /* store pointer so memory can be deallocated later */
    msg_prev = msg_pu.ptr;
    
    return msg_pu.ptr;
}

/** \fn xmachine_message_leader * get_first_leader_message()
 * \brief Get the first leader message in the leader message list.
 * \return The first message in the list.
 */
m_leader * get_first_leader_message()
{
	return getInternalMessage_leader();
}

/** \fn xmachine_message_leader * get_next_leader_message(xmachine_message_leader * current)
 * \brief Get the next leader message in the leader message list after the current message.
 * \param current The current message in the list.
 * \return The next message in the list.
 */
m_leader * get_next_leader_message(m_leader * current)
{
	return getInternalMessage_leader();
}


/* Box filtering functions */




union pu_clan_info 
{
    m_clan_info *ptr;
    void *ptr_anon;
};

/** \fn void add_clan_info_message(int px, int py, int cID, int wf, int maxcc)
 * \brief Add clan_info message by calling internal and processing.
 * \param px Message variable.
 * \param py Message variable.
 * \param cID Message variable.
 * \param wf Message variable.
 * \param maxcc Message variable.
 */
void add_clan_info_message(int px, int py, int cID, int wf, int maxcc)
{
    int rc;
	m_clan_info msg;
    
    msg.px = px;
    msg.py = py;
    msg.cID = cID;
    msg.wf = wf;
    msg.maxcc = maxcc;
    
    
    rc = MB_AddMessage(b_clan_info, &msg);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not add message to 'clan_info' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clan_info' board has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clan_info' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_AddMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	   }
	      
	   
       exit(rc);
    }
    #endif
}

inline static m_clan_info* getInternalMessage_clan_info(void)
{
    static m_clan_info *msg_prev = NULL;
    union pu_clan_info msg_pu;
    int rc;
    
    /* deallocate previously returned message */
    if (msg_prev != NULL) 
    {
        free(msg_prev);
    }
    else 
    {
        rc = MB_Iterator_Rewind(i_clan_info); 
        #ifdef ERRCHECK
        if (rc != MB_SUCCESS)
        {
            fprintf(stderr, "ERROR: Could not rewind 'clan_info' Iterator\n");
            switch(rc) {
                case MB_ERR_INVALID:
                    fprintf(stderr, "\t reason: 'clan_info' Iterator has not been created?\n");
                    break;
	            default:
                    fprintf(stderr, "\t MB_Iterator_Rewind returned error code: %d (see libmboard docs for details)\n", rc);
                    break;
	        }
	       
	       
       	   exit(rc);
        }
        #endif
    }
    
    /* get next message from iterator */
    rc = MB_Iterator_GetMessage(i_clan_info, &(msg_pu.ptr_anon));
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not get message from 'clan_info' Iterator\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clan_info' Iterator has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Iterator_GetMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }
	       
	       
       	   exit(rc);
    }
    #endif
    
    /* store pointer so memory can be deallocated later */
    msg_prev = msg_pu.ptr;
    
    return msg_pu.ptr;
}

/** \fn xmachine_message_clan_info * get_first_clan_info_message()
 * \brief Get the first clan_info message in the clan_info message list.
 * \return The first message in the list.
 */
m_clan_info * get_first_clan_info_message()
{
	return getInternalMessage_clan_info();
}

/** \fn xmachine_message_clan_info * get_next_clan_info_message(xmachine_message_clan_info * current)
 * \brief Get the next clan_info message in the clan_info message list after the current message.
 * \param current The current message in the list.
 * \return The next message in the list.
 */
m_clan_info * get_next_clan_info_message(m_clan_info * current)
{
	return getInternalMessage_clan_info();
}


/* Box filtering functions */




union pu_clangetcalories 
{
    m_clangetcalories *ptr;
    void *ptr_anon;
};

/** \fn void add_clangetcalories_message(int cID, int clcalories)
 * \brief Add clangetcalories message by calling internal and processing.
 * \param cID Message variable.
 * \param clcalories Message variable.
 */
void add_clangetcalories_message(int cID, int clcalories)
{
    int rc;
	m_clangetcalories msg;
    
    msg.cID = cID;
    msg.clcalories = clcalories;
    
    
    rc = MB_AddMessage(b_clangetcalories, &msg);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not add message to 'clangetcalories' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clangetcalories' board has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'clangetcalories' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_AddMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	   }
	      
	   
       exit(rc);
    }
    #endif
}

inline static m_clangetcalories* getInternalMessage_clangetcalories(void)
{
    static m_clangetcalories *msg_prev = NULL;
    union pu_clangetcalories msg_pu;
    int rc;
    
    /* deallocate previously returned message */
    if (msg_prev != NULL) 
    {
        free(msg_prev);
    }
    else 
    {
        rc = MB_Iterator_Rewind(i_clangetcalories); 
        #ifdef ERRCHECK
        if (rc != MB_SUCCESS)
        {
            fprintf(stderr, "ERROR: Could not rewind 'clangetcalories' Iterator\n");
            switch(rc) {
                case MB_ERR_INVALID:
                    fprintf(stderr, "\t reason: 'clangetcalories' Iterator has not been created?\n");
                    break;
	            default:
                    fprintf(stderr, "\t MB_Iterator_Rewind returned error code: %d (see libmboard docs for details)\n", rc);
                    break;
	        }
	       
	       
       	   exit(rc);
        }
        #endif
    }
    
    /* get next message from iterator */
    rc = MB_Iterator_GetMessage(i_clangetcalories, &(msg_pu.ptr_anon));
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not get message from 'clangetcalories' Iterator\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'clangetcalories' Iterator has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Iterator_GetMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }
	       
	       
       	   exit(rc);
    }
    #endif
    
    /* store pointer so memory can be deallocated later */
    msg_prev = msg_pu.ptr;
    
    return msg_pu.ptr;
}

/** \fn xmachine_message_clangetcalories * get_first_clangetcalories_message()
 * \brief Get the first clangetcalories message in the clangetcalories message list.
 * \return The first message in the list.
 */
m_clangetcalories * get_first_clangetcalories_message()
{
	return getInternalMessage_clangetcalories();
}

/** \fn xmachine_message_clangetcalories * get_next_clangetcalories_message(xmachine_message_clangetcalories * current)
 * \brief Get the next clangetcalories message in the clangetcalories message list after the current message.
 * \param current The current message in the list.
 * \return The next message in the list.
 */
m_clangetcalories * get_next_clangetcalories_message(m_clangetcalories * current)
{
	return getInternalMessage_clangetcalories();
}


/* Box filtering functions */




union pu_calguanacos 
{
    m_calguanacos *ptr;
    void *ptr_anon;
};

/** \fn void add_calguanacos_message(int xcord, int ycord, int calorias)
 * \brief Add calguanacos message by calling internal and processing.
 * \param xcord Message variable.
 * \param ycord Message variable.
 * \param calorias Message variable.
 */
void add_calguanacos_message(int xcord, int ycord, int calorias)
{
    int rc;
	m_calguanacos msg;
    
    msg.xcord = xcord;
    msg.ycord = ycord;
    msg.calorias = calorias;
    
    
    rc = MB_AddMessage(b_calguanacos, &msg);
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not add message to 'calguanacos' board\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'calguanacos' board has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
           case MB_ERR_LOCKED:
               fprintf(stderr, "\t reason: 'calguanacos' board is locked\n");
               break;
           case MB_ERR_INTERNAL:
               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
               break;
	       default:
               fprintf(stderr, "\t MB_AddMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	   }
	      
	   
       exit(rc);
    }
    #endif
}

inline static m_calguanacos* getInternalMessage_calguanacos(void)
{
    static m_calguanacos *msg_prev = NULL;
    union pu_calguanacos msg_pu;
    int rc;
    
    /* deallocate previously returned message */
    if (msg_prev != NULL) 
    {
        free(msg_prev);
    }
    else 
    {
        rc = MB_Iterator_Rewind(i_calguanacos); 
        #ifdef ERRCHECK
        if (rc != MB_SUCCESS)
        {
            fprintf(stderr, "ERROR: Could not rewind 'calguanacos' Iterator\n");
            switch(rc) {
                case MB_ERR_INVALID:
                    fprintf(stderr, "\t reason: 'calguanacos' Iterator has not been created?\n");
                    break;
	            default:
                    fprintf(stderr, "\t MB_Iterator_Rewind returned error code: %d (see libmboard docs for details)\n", rc);
                    break;
	        }
	       
	       
       	   exit(rc);
        }
        #endif
    }
    
    /* get next message from iterator */
    rc = MB_Iterator_GetMessage(i_calguanacos, &(msg_pu.ptr_anon));
    #ifdef ERRCHECK
    if (rc != MB_SUCCESS)
    {
       fprintf(stderr, "ERROR: Could not get message from 'calguanacos' Iterator\n");
       switch(rc) {
           case MB_ERR_INVALID:
               fprintf(stderr, "\t reason: 'calguanacos' Iterator has not been created?\n");
               break;
           case MB_ERR_MEMALLOC:
               fprintf(stderr, "\t reason: out of memory\n");
               break;
	       default:
               fprintf(stderr, "\t MB_Iterator_GetMessage returned error code: %d (see libmboard docs for details)\n", rc);
               break;
	       }
	       
	       
       	   exit(rc);
    }
    #endif
    
    /* store pointer so memory can be deallocated later */
    msg_prev = msg_pu.ptr;
    
    return msg_pu.ptr;
}

/** \fn xmachine_message_calguanacos * get_first_calguanacos_message()
 * \brief Get the first calguanacos message in the calguanacos message list.
 * \return The first message in the list.
 */
m_calguanacos * get_first_calguanacos_message()
{
	return getInternalMessage_calguanacos();
}

/** \fn xmachine_message_calguanacos * get_next_calguanacos_message(xmachine_message_calguanacos * current)
 * \brief Get the next calguanacos message in the calguanacos message list after the current message.
 * \param current The current message in the list.
 * \return The next message in the list.
 */
m_calguanacos * get_next_calguanacos_message(m_calguanacos * current)
{
	return getInternalMessage_calguanacos();
}

