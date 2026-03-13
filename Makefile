CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(SRC_DIR)/classi.cpp \
       $(SRC_DIR)/funzioni.cpp \
       $(SRC_DIR)/supermarket_simulator.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/supermarket_simulator.exe

# ── Regola principale ──────────────────────────────────────────
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ── Compilazione oggetti ───────────────────────────────────────
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ── Crea cartelle se non esistono ─────────────────────────────
$(OBJ_DIR):
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(BIN_DIR):
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# ── Pulizia ───────────────────────────────────────────────────
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)

# ── Ricompila tutto da zero ────────────────────────────────────
rebuild: clean all

# ── Esegui direttamente ───────────────────────────────────────
run: all
	$(TARGET) $(CURDIR)

.PHONY: all clean rebuild run