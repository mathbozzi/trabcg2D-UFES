all: compile 

compile:
	g++ -c tinyxml2.cpp
	g++ -o trabalhocg *.cpp -lGL -lGLU -lglut

clean:
	@rm -f *.o trabalhocg
