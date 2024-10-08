CC = gcc
CFLAGS = -Wall -Wextra -g
OBJDIR = ./obj
SRCDIR = ./src
INCDIR = ./include
BINDIR =  # Diretório do binário está vazio, indicando o diretório atual

# Define os arquivos objetos
_OBJS = main.o file_io.o boyer_moore.o time.o kmp.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

# Pasta padrão para includes
CPPFLAGS = -I$(INCDIR)

# Diretiva all para compilar o programa principal
all: tp3

# Linkagem dos arquivos objetos para gerar o executável tp1
tp3: $(OBJS)  
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada arquivo objeto individualmente
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Cria a pasta obj se ela não existir
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJDIR)/*.o tp3

.PHONY: all clean