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
# La syntaxe target: | prerequisite indique une dépendance d'ordre uniquement ("order-only prerequisite").
# Cela signifie que $(TARGET) et $(TEST_TARGET) doivent être construits après $(BUILD_DIR) (s'il n'existe pas).
$(TARGET): | $(BUILD_DIR)
$(TEST_TARGET): | $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilation

# Pour chaque fichier .cpp dans src/ (ex: src/foo.cpp), génère un .o dans build/ (ex: build/foo.o)
# $< = fichier source (ex: src/foo.cpp)
# $@ = cible (ex: build/foo.o)
# Compile sans linker (-c)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


#Pour créer l’exécutable principal ($(TARGET), ex: build/app)
# Linke tous les objets communs $(OBJS) + objet du main $(MAIN_OBJ)
# $^ = tous les prérequis (tous les .o)
# $@ = cible (l’exécutable)
$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(OBJS) $(MAINTEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@



# commande 'make run' pour compiler et exécuter l'app 
run: $(TARGET)
	./$(TARGET)

# commande 'make test' pour compiler les tests
test: $(TEST_TARGET)

# commande 'make runtest' pour compiler et lancer les tests
runtest: $(TEST_TARGET)
	./$(TEST_TARGET)

# commande 'make clean'
clean:
	rm -rf $(BUILD_DIR)/*

# .PHONY ignore tous les fichiers qui s'appelleraient 'all', 'clean', ... 
.PHONY: all clean run test runtest
