CXX = g++
CXXFLAGS = -Wall -Wextra

# Diretórios
BUILD_DIR = build

# Pastas dos módulos
LEXICO_DIR = lexico
SINTATICO_DIR = sintatico
SEMANTICO_DIR = semantico

# Arquivos fonte
SRC = \
	main.cpp \
	$(LEXICO_DIR)/analisador_lexico.cpp \
	$(LEXICO_DIR)/leitorArquivo.cpp \
	$(LEXICO_DIR)/tokenHandler.cpp

# Objetos
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

# Executável
EXEC = compilador
ENTRADA = txt.txt

all: $(EXEC)
	./$(EXEC) $(ENTRADA)

# Linkagem
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos .cpp
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

rebuild: clean all