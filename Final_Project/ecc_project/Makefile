# Executables
ECC_TARGET = ecc_simulation
CHACHA_TARGET = chacha_simulation

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lsodium

# Directories
SRCDIR = src
RESULTS_DIR = results

# Source Files and objects
ECC_SOURCES = $(SRCDIR)/ecc_simulation.cpp $(SRCDIR)/main.cpp
CHACHA_SOURCES = $(SRCDIR)/chacha_simulation.cpp $(SRCDIR)/main_chacha.cpp

ECC_OBJECTS = $(ECC_SOURCES:.cpp=.o)
CHACHA_OBJECTS = $(CHACHA_SOURCES:.cpp=.o)

# Default Rule
all: $(ECC_TARGET) $(CHACHA_TARGET)

$(ECC_TARGET): $(ECC_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(CHACHA_TARGET): $(CHACHA_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(ECC_TARGET) $(CHACHA_TARGET)

dist-clean: clean
	rm -f $(RESULTS_DIR)/*.csv
