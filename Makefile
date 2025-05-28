# Répertoires
INCLUDES = -Iinclude
SRC_DIR = src
BUILD_DIR = Build

# Compilateur
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(INCLUDES)

# Fichiers sources communs (sans le main)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Noms des exécutables
TARGET = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/test

# Règle par défaut
all: $(TARGET)

# Création du répertoire Build si besoin
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilation de l'app principale avec main.cpp
$(TARGET): $(BUILD_DIR) $(SRCS) main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) main.cpp

# Compilation des tests avec maintest.cpp
$(TEST_TARGET): $(BUILD_DIR) $(SRCS) maintest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) maintest.cpp

# Règle explicite pour build de test
test: $(TEST_TARGET)

# Nettoyer
clean:
	rm -f $(BUILD_DIR)/app $(BUILD_DIR)/test

# Exécuter l'app
run: $(TARGET)
	./$(TARGET)

# Exécuter les tests
runtest: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run test runtest