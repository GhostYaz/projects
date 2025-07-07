# Makefile for EnhancePokemonSFML project
# Adjust paths if your SFML location is different

# Compiler and flags
CXX = g++
CXXFLAGS = -DSFML_DYNAMIC -std=c++17 -g

# SFML directories
SFML_INCLUDE = -IC:/Users/raiyann_khan/Documents/SFML/SFML-2.5.1/include
SFML_LIB = -LC:/Users/raiyann_khan/Documents/SFML/SFML-2.5.1/lib

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

# Source files
SRCS = main_sfml.cpp
OUT = main.exe

# Test files
TEST_POKEMON_SRC = test_Pokemon.cpp
TEST_POKEMON_OUT = test_pokemon.exe

TEST_GAME_SRC = test_Game.cpp
TEST_GAME_OUT = test_game.exe

all: $(OUT)

$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(SFML_INCLUDE) $(SFML_LIB) $(SFML_LIBS) -o $(OUT)

test_pokemon: $(TEST_POKEMON_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_POKEMON_SRC) -o $(TEST_POKEMON_OUT)

test_game: $(TEST_GAME_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_GAME_SRC) -o $(TEST_GAME_OUT)

clean:
	del /Q *.exe *.o

# Optionally run tests with "make run_tests"
run_tests: test_pokemon test_game
	.\$(TEST_POKEMON_OUT)
	.\$(TEST_GAME_OUT)
