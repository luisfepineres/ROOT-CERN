# Nombre del ejecutable
MUONS_EXE = muons
MUONS_LIFE_EXE = muons_life

# Opciones de compilación
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 `root-config --cflags`
LDFLAGS = `root-config --libs`

# Reglas
all: $(MUONS_EXE) $(MUONS_LIFE_EXE)

$(MUONS_EXE): muons.cpp
	        $(CXX) $(CXXFLAGS) muons.cpp -o $(MUONS_EXE) $(LDFLAGS)

$(MUONS_LIFE_EXE): muon_life.cpp
	        $(CXX) $(CXXFLAGS) muon_life.cpp -o $(MUONS_LIFE_EXE) $(LDFLAGS)

clean:
	        rm -f $(MUONS_EXE) $(MUONS_LIFE_EXE)
