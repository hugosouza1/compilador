CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# pastas
BUILD_DIR = build

# arquivos
SRC = analisador_lexico.cpp leitorArquivo.cpp tokenHandler.cpp
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
EXEC = compilador

# regra principal
all: $(EXEC)
	./$(EXEC)

# linkagem
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# cria a pasta build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# compilação
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# limpeza
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

# rebuild completo
rebuild: clean all