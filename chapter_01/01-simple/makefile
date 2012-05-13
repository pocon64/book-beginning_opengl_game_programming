SOURCE=simple.cpp
MYPROGRAM=simple
MYINCLUDES=/usr/include
CPP=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	g++ -I/usr/include simple.cpp -oDebug/01-simple -lglut -lGLU -lSDL -lSDLmain

clean:

	rm -f simple
