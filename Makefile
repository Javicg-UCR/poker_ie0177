## Makefile para el proyecto

CC = gcc

# Tags de compilación de GTK
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk +-3.0`

SRC = ./src/ # Carpeta "source" (src)
INCLUDE = ./include/ # Carpeta "include" (include)
TEST = test # Ejecutable de prueba
MAIN = main # Ejecutable principal
FUNC1 = func1 # Ejecutable función 1

test:
	$(CC) $(CFLAGS) $(TEST).c -o $(TEST) $(LIBS) -I $(INCLUDE) -c $(SRC)
func1
	$(CC) $(CFLAGS) $(FUNC1).c -o $(FUNC1) $(LIBS) -I $(INCLUDE) -c $(SRC)
clean:
	rm -f *.o $(EXE) $(func1)
