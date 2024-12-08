## Makefile para el proyecto
## Instrucciones: cambiar el nombre de lo que se quiere correr en CFILE, EXE y TARGET
## Correr desde la raíz, el ejecutable va a la raíz
## Correr "make clean" después para limpiar la raíz

CC = gcc
FLAGS = -Wall -rdynamic
INCLUDE_PATH = -I./include

#-----------------------------------------

## Cambiar estos nombres

#              archivo.c     (nombre del archivo principal)
CFILE = ./test/imagetest.c

#       archivo   (nombre del exe)
EXE = ./imagetest

#        archivo      (nombre del target)
TARGET = imagetest

C_INCLUDE = ./test/include.c

C_INCLUDE_EXE = ./test/include

C_INCLUDE_TARGET = include

H_INCLUDE = ./test/include.h

# -----------------------------------------

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(CFILE)
	$(CC) $(FLAGS) $(INCLUDE_PATH) `pkg-config --cflags gtk+-3.0` -o $(TARGET) $(CFILE) $(C_INCLUDE) `pkg-config --libs gtk+-3.0`

clean:
	rm -f $(EXE)

run:
	$(EXE)

##gcc `pkg-config --cflags gtk+-3.0` -o imagetest imagetest.c `pkg-config --libs gtk+-3.0`
