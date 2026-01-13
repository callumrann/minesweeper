# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O0 -g -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRCDIR = src
OBJDIR = build
HDRDIR = include
BINDIR = bin

# Source and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Target executable
TARGET = $(BINDIR)/minesweeper

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile .cpp -> .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# ==================
# What was learnt from this makefile
# ======================
#
# wildcard will use following text as wildcard in bash
# otherwise would be direct text replacement
#
# patsubst first input uses % as stem wildcard (grabs file names)
# second uses % to copy what % grabbed in first (if Game was matched in first, used in second)
# follows: pattern, replacement, text
# with text begin the source it is looking for patterns from
#
# use rule: dependency | other dependency
# things after | must exist
# if doesn't then will look for rule with same name in attempt to create it
# if no rule then fails
