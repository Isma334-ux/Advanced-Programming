CXX = g++
CXXFLAGS = -std=c++17 -O2 -lsodium
INCLUDE = -Iinclude
SRC = src/main.cpp src/ecc_utils.cpp
OUT = bin/ecc_app

all: create_bin $(OUT)

create_bin:
	mkdir -p bin

$(OUT): $(SRC)
	$(CXX) $(SRC) $(INCLUDE) $(CXXFLAGS) -o $(OUT)

clean:
	rm -rf bin results/*.csv
