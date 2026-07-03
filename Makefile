# 1. Variabile pentru compilator și flag-uri SFML 2
CXX = g++
CXXFLAGS = -I/opt/sfml2/include -std=c++17
LDFLAGS = -L/opt/sfml2/lib -Wl,-rpath,/opt/sfml2/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# 2. Găsește automat toate fișierele .cpp din folderul src/
SRC = $(wildcard src/*.cpp)

# 3. Numele programului final
TARGET = joc

# 4. Regula principală de compilare
all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS) $(LIBS)

# 5. Regulă opțională ca să ștergi executabilul vechi cu "make clean"
clean:
	rm -f $(TARGET)