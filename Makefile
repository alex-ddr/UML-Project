# Répertoires
INCLUDES = -Iinclude
SRC_DIR = src

# Compilateur
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(INCLUDES)

# Fichiers sources communs (sans le main)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Nom des exécutables
TARGET = app
TEST_TARGET = test

# Règle par défaut
all: $(TARGET)

# Compilation de l'app normale avec main.cpp
$(TARGET): $(SRCS) main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des tests avec maintest.cpp
test: $(SRCS) maintest.cpp
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^

# Nettoyer
clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Exécuter l'app
run: $(TARGET)
	./$(TARGET)

# Exécuter les tests
runtest: test
	./$(TEST_TARGET)

.PHONY: all clean run test runtest