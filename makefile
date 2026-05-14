# Exec name
EXEC = exec/orderbook

# Directories
SRC_DIR = code/src
INC_DIR = code/include

SRC_EXT = cpp
OBJ_EXT = o

SRCS = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS = $(SRCS:$(SRC_DIR)/%.$(SRC_EXT)=$(SRC_DIR)/%.$(OBJ_EXT))

# Options
CXX = g++
CXXFLAGS = -I$(INC_DIR) -std=c++17

# Default rule
all: $(EXEC)

# Generate exec
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

$(SRC_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.$(OBJ_EXT) $(EXEC)

.PHONY: all clean