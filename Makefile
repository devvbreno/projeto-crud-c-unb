# Variáveis de compilação
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=bin/%.o)
TARGET = bin/programa

# Alvo principal: compila tudo e gera o executável
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compila os arquivos .c em objetos .o dentro da pasta bin
bin/%.o: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos temporários e o executável
clean:
	rm -rf bin/*.o $(TARGET)

# Atalho para compilar e rodar o programa direto
run: all
	./$(TARGET)
