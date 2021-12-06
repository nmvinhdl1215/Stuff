CCX		:=g++
NFLAGS	:=-Wall -O
OFLAGS	:=-o 
CCFLAGS	:=-c
LFLAGS	:= -lsfml-graphics -lsfml-window -lsfml-system
BUILD	:=./build
TARGET	:=main
APP_DIR	:=.
DEB_DIR	:=$(BUILD)/debug
OBJ_DIR	:=$(BUILD)/obj
INC		:=-I . -I ../include/
SRC_DIR	:=.
SRC		:=$(wildcard ./*.cpp)
OBJ		:=$(SRC:%.cpp=$(OBJ_DIR)/%.o)
EX 		:=./ex_obj
all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
		@mkdir -p $(@D)
		$(CCX) $(NFLAGS) $(INC) $(CCFLAGS) $< $(OFLAGS) $@

$(APP_DIR)/$(TARGET):$(OBJ)
		@mkdir -p $(@D)
		$(CCX) $(NFLAGS) $(OFLAGS) $(APP_DIR)/$(TARGET) $^  $(LFLAGS)
	 
.PHONY: all build debug execute clean
build:
		@mkdir -p $(APP_DIR)
		@mkdir -p $(OBJ_DIR)


debug: NFLAGS+=-g
debug: all

execute :all
execute: $(APP_DIR)/$(TARGET)

clean:
		-@rm -r $(OBJ_DIR)/source/*.o
