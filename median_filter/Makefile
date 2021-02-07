TARG=medfilter
CC=gcc
INCDIR=headers
LINK=-ljpeg
CFLAGS= -I${INCDIR} -g -Wall -Werror

C_SOURCES=$(wildcard src/*.c)
HEADERS=$(wildcard headers/*.h)
OBJ=${C_SOURCES:.c=.o}

all : ${TARG}

${TARG} : ${OBJ}
	${CC} $^ -o ${TARG} ${LINK}

%.o : %.c
	${CC} ${CFLAGS} -c $^ -o $@

clean :
	rm -rf $(TARG) src/*.o
