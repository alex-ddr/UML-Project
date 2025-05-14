# Répertoires
INCLUDES = -Iinclude
SRC_DIR = src
OBJ_DIR = build

# Compilateur
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(INCLUDES)

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = app

# Règle par défaut
all: $(TARGET)

# Lier l’exécutable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Nettoyer les fichiers objets et l’exécutable
clean:
	rm -f $(TARGET) $(OBJS)

# Juste l’exécutable
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run