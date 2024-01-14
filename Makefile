CXX = g++
CXXFLAGS = -g -Wall -std=gnu++23
SRC = client
LIBS = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network
BUILD = build
OBJ = build/obj
TARGET = build/client

SRC_FILES = $(wildcard $(SRC)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC)/%.cpp=$(OBJ)/%.o)

all: $(BUILD) $(OBJ) $(TARGET)

$(BUILD):
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf $(BUILD)
