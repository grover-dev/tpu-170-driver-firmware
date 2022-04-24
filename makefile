# makefile based on https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 
INC =./inc
CC=arm-none-eabi-gcc
CFLAGS=-Og -mcpu=cortex-m0 -mthumb -I$(INC) -gdwarf-4  
LIB=./lib

SRC := ./src
OBJ := ./obj


LPC822_LINKER = ./lib/lpc822.ld
# no-std-lib flag was previously used here to solve an issue, currently removed
LDFLAGS = -T $(LPC822_LINKER) --specs=nosys.specs  -Xlinker --gc-sections 


SOURCES := $(wildcard $(SRC)/*.c) 
INCLUDES := $(wildcard $(INC)/*.h)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(LIB) -I$(INC)  -c $< -o $@ $(CFLAGS)


all: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ -Xlinker -Map="all.map"


#$(CC) $(OBJ)/%.o -o out.elf


.PHONY: clean
# *~ core $(INCDIR)/*~
clean:
	rm -f $(OBJ)/*.o
	rm all
	#rm lpc822.elf
	rm lpc822