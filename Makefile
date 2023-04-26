# Nombre del ejecutable
EXE = muons

# Opciones de compilación
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 `root-config --cflags`
LDFLAGS = `root-config --libs`

# Reglas
all: $(EXE)

$(EXE): muons.cpp
	$(CXX) $(CXXFLAGS) muons.cpp -o $(EXE) $(LDFLAGS)

clean:
	rm -f $(EXE)