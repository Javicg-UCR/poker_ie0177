## Makefile para el proyecto
## Instrucciones: cambiar el nombre de lo que se quiere correr en CFILE, EXE y TARGET
## Correr desde la raíz, el ejecutable va a la raíz
## Correr "make clean" después para limpiar la raíz

CC = gcc
FLAGS = -Wall -rdynamic

#-----------------------------------------

## Cambiar estos nombres

#              archivo.c     (nombre del archivo principal)
CFILE = ./test/firsttest.c

#       archivo   (nombre del exe)
EXE = ./firsttest

#        archivo      (nombre del target)
TARGET = firsttest

# -----------------------------------------

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(CFILE)
	$(CC) -Wall -rdynamic `pkg-config --cflags gtk+-3.0` -o $(TARGET) $(CFILE) `pkg-config --libs gtk+-3.0`
clean:
	rm -f $(EXE)

##gcc `pkg-config --cflags gtk+-3.0` -o imagetest imagetest.c `pkg-config --libs gtk+-3.0`
