all: compile clean

compile:
	g++ -c tinyxml2.cpp
	g++ -o test *.cpp -lGL -lGLU -lglut

clean:
	@rm -f *.o
