CXX = g++
CXXFLAGS = -Wall -Wextra 

# pasta .o
BUILD_DIR = build

SRC = analisador_lexico.cpp leitorArquivo.cpp tokenHandler.cpp
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
EXEC = compilador
ENTRADA = txt.txt

all: $(EXEC)
	./$(EXEC) $(ENTRADA)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

rebuild: clean all