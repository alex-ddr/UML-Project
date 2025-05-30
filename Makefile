# Répertoires
INCLUDES = -Iinclude
SRC_DIR = src
BUILD_DIR = build

# Compilateur
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(INCLUDES)

# Fichiers
SRCS = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/maintest.cpp,$(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
MAIN_OBJ = $(BUILD_DIR)/main.o
MAINTEST_OBJ = $(BUILD_DIR)/maintest.o

# Exécutables
TARGET = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/test

# Règle par défaut
all: $(TARGET)

# Crée build/ si nécessaire
$(TARGET): | $(BUILD_DIR)
$(TEST_TARGET): | $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(OBJS) $(MAINTEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation de temp seul avec son main
temp: src/temp.cpp
	$(CXX) $(CXXFLAGS) -DCOMPILE_TEMP_MAIN -o build/temp src/temp.cpp


test: $(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)/*

run: $(TARGET)
	./$(TARGET)

runtest: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run test runtest
