# Project
EXE := tracker

# Compiler
CXX := g++
CXXFLAGS := -MMD -D _DEBUG -c -g -Wall -std=c++11

INC_DIR := inc/
SRC_DIR := src/
BIN_DIR := obj/

SUBFOLDERS := $(sort $(dir $(wildcard $(SRC_DIR)*/)))

SRCS := $(foreach sdir,$(SUBFOLDERS),$(wildcard $(sdir)*.cc))
BINS := $(patsubst $(SRC_DIR)%.cc,$(BIN_DIR)%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)%.cc,$(BIN_DIR)%.d,$(SRCS))

all: $(EXE)

$(EXE): $(BINS)
	@echo $@
	@$(CXX) -o $@ $^ $(ALLEG)

$(BIN_DIR)%.o: $(SRC_DIR)%.cc
	@echo $(subst src/,"",$<)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INC_DIR)

clean:
	@rm -rf $(BIN_DIR) hc.o

run:
	@./hc.o

debug:
	@gdb -d $(SRC_DIR) -ex run -ex quit -q ./$(EXE)

-include $(DEPS)