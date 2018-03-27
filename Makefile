all: main.o libPhysicsBox.a
	g++ main.o libPhysicsBox.a -framework GLUT -framework OpenGL -o test

main.o: main.cpp
	g++ -c main.cpp

libPhysicsBox.a: PhysicsBox/figure.o PhysicsBox/line.o PhysicsBox/vec.o PhysicsBox/determinant.o
	ar rvs libPhysicsBox.a PhysicsBox/figure.o PhysicsBox/line.o PhysicsBox/vec.o PhysicsBox/determinant.o

figure.o: PhysicsBox/figure.cpp
	g++ -c PhysicsBox/figure.cpp

line.o: PhysicsBox/line.cpp
	g++ -c PhysicsBox/line.cpp

vec.o: PhysicsBox/vec.cpp
	g++ -c PhysicsBox/vec.cpp

determinant.o: PhysicsBox/determinant.cpp
	g++ -c PhysicsBox/determinant.cpp

clean:
	rm *.o *.gch *.a PhysicsBox/*.o PhysicsBox/*.gch PhysicsBox/*.a