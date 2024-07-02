# Nombre del ejecutable
TARGET = sudoku

# Archivos fuente
SOURCES = main.c

# Archivos objeto
OBJECTS = main.o

# Flags de compilación necesarios para compilar con GTK
CFLAGS = -g `pkg-config --cflags gtk+-3.0`

# Flags de enlace para obtener las bibliotecas necesarias para enlazar con GTK
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Compilador a utilizar 
CC = gcc

# Regla por defecto 
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Regla para compilar main.c a main.o
main.o: main.c sudoku_boards.h sudoku_solver.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGET) $(OBJECTS)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)
