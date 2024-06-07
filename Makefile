# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall

# Arquivos de origem
SRCS = qualFilme.c trie.c

# Arquivo de saída
TARGET = qualFilme

# Arquivos objeto
OBJS = qualFilme.o trie.o

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regras para criar os arquivos objeto
qualFilme.o: qualFilme.c trie.h
	$(CC) $(CFLAGS) -c qualFilme.c -o qualFilme.o

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c -o trie.o

# Regra para limpar arquivos de compilação
clean:
	rm -f $(TARGET) $(OBJS)

# Regra para rodar o programa com os arquivos de entrada e saída
run: $(TARGET)
	./$(TARGET) filmes.txt < consultas.txt > saida.txt
