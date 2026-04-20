CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -pedantic -march=native -lm
TARGET = experimento
SRC = experimento.c
DATA = resultados.dat
PNG = grafica.png
PLOT = plot.gp

all: $(PNG)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

$(DATA): $(TARGET)
	./$(TARGET) > $(DATA)

$(PNG): $(DATA) $(PLOT)
	gnuplot $(PLOT)

clean:
	rm -f $(TARGET) $(DATA) $(PNG)
