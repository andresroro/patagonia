# Makefile template file for FLAME
#
# FLAME is the FLAME source files
# SOURCE is the user source files
#
# The assumption is that the user only provides C files
# and a model files <file>.xml
#
DEFINES       = -DNONE
LIBMBOARD_DIR = ../../libmboard-0.3.1
LIBMBOARD_INC = $(LIBMBOARD_DIR)/include
LIBMBOARD_LIB = $(LIBMBOARD_DIR)/lib

CC      = mpicc
CFLAGS  = -std=c99 -Wall -I$(LIBMBOARD_INC) ${DEFINES}

CFLAGS += -D_DEBUG_MODE -g


LDFLAGS = -L$(LIBMBOARD_LIB)
LIBS    = -lmboard_pd  -lm

#FLAME source files
FLAME   = main.c memory.c xml.c messageboards.c partitioning.c rules.c timing.c

#FLAME auxilary files
AUX 	= stategraph.dot stategraph_colour.dot process_order_graph.dot Doxyfile latex.tex

# FLAME generated model files
SOURCES =  indv.c  clan.c  patch.c  guanacos.c 
HEADERS = header.h low_primes.h mboard.h  indv_agent_header.h  clan_agent_header.h  patch_agent_header.h  manada_guanacos_agent_header.h 

DEPS    = Makefile header.h low_primes.h

OBJECTS = $(SOURCES:.c=.o) $(FLAME:.c=.o)
EXECUTABLE = main
RM = rm -f

all: $(SOURCES) $(FLAME) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

$(OBJECTS): $(DEPS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).exe
vclean:
	$(RM) main $(EXECUTABLE) $(EXECUTABLE).exe $(OBJECTS)  $(FLAME) $(HEADERS)  $(AUX) Makefile
