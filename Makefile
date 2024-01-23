CXX = g++
CXXFLAGS = -g -Wall -std=gnu++23
SRC = client
COMMON_SRC = common
LIBS = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network
INCLUDE = -Icommon
BUILD = build
OBJ = $(BUILD)/obj
TARGET = $(BUILD)/client
ASSETS = $(BUILD)/assets
CONFIG = $(BUILD)/config

SRC_FILES = $(wildcard $(SRC)/*.cpp) $(wildcard $(COMMON_SRC)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC)/%.cpp=$(OBJ)/%.o)

all: $(BUILD) $(ASSETS) $(CONFIG) $(OBJ) $(TARGET)

$(BUILD):
	mkdir -p $@

$(OBJ):
	mkdir -p $@

$(ASSETS):
	cp -r assets $(BUILD)

$(CONFIG):
	mkdir -p $@
	cp $(SRC)/c_config.txt $(CONFIG)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf $(BUILD)
