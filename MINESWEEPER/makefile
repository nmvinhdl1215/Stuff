#----------Implicit constant------------
# Shell program
SHELL	:=/usr/bin/bash
# Compilers
CCX		:=g++
# CPP flags
CXXFLAGS:=-Wall -O2
# Output flags
OFLAGS	:=-o
# Assemble flag (but not link)
CCFLAGS	:=-c
# C preprocessor flag
CPPFLAGS:=
# Linker flag
LDFLAGS	:= -lsfml-window -lsfml-graphics -lsfml-system
#------------------------------------------

#----------Directories-------------------
# Build directory
BUILD	:=./build
# Output program
TARGET	:=main
# Output directory
APP_DIR	:=.

# Debug directory
DEB_DIR	:=$(BUILD)/debug
# Object files directory
OBJ_DIR	:=$(BUILD)/obj

# Include flags
INC		:=-I .
# Soruce files
SRC_DIR	:= .
SRCS	:=$(shell find $(SRC_DIR) -name '*.cpp')
OBJ		:=$(SRCS:%=$(OBJ_DIR)/%.o)		#Object file(s)

#-----------Content----------------------

all: build $(APP_DIR)/$(TARGET)			#all: target  './main'

#Build from Cpp source
$(OBJ_DIR)/%.cpp.o: %.cpp
		@mkdir -p $(@D)
		$(CCX) $(CXXFLAGS) $(INC) $(CCFLAGS) $< $(OFLAGS) $@ 	


#The final build step
$(APP_DIR)/$(TARGET): $(OBJ)
		$(CCX) $(CFLAGS) $(OFLAGS) $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build debug execute clean
build:
		@mkdir -p $(APP_DIR)
		@mkdir -p $(OBJ_DIR)

debug: NFLAGS+=-g
debug: all

execute :all
execute	:
		setsid $(APP_DIR)/$(TARGET)

clean:
		-@rm -rf $(BUILD)
		-@rm -rf $(APP_DIR)/$(TARGET)
