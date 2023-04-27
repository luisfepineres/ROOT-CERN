# Nombre del ejecutable
EXE_MUONS = muons
EXE_LIFE = muons_life
# Opciones de compilación
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 `root-config --cflags`
LDFLAGS = `root-config --libs`

# Reglas
all: $(EXE_MUONS) $(EXE_LIFE)

$(EXE_MUONS): muons.cpp
        $(CXX) $(CXXFLAGS) muons.cpp -o $(EXE_MUONS) $(LDFLAGS)

$(EXE_LIFE): muons_life.cpp
        $(CXX) $(CXXFLAGS) muons_life.cpp -o $(EXE_LIFE) $(LDFLAGS)
clean:
        rm -f $(EXE_MUONS) $(EXE_LIFE)
