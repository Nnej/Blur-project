#makefile pour lancer les appli openGL GLUT avec la commande "$ make flou" puis "$ ./flou image.bmp"
CC=gcc
CFLAGS = -O
PRG=flou
OBJ=main.o bmp.o flouter.o
SRC=$(OBJ:.o=.c)

LIBS= -framework GLUT -framework OpenGL
OFLAGS1=

all: $(PRG)

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(OFLAGS1)

flou: $(OBJ)
	$(CC) $(CFLAGS) -o flou $(LIBS) $(OBJ)

clean:
	@rm -f *.o
	@rm -f gmon.out	
	@rm -f core
	@rm -f *~
	@rm -f glutcode