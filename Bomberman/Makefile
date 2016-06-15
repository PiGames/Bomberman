
FLAGS=-g -std=c++11

all: Bomberman

Bomberman: Animator.o Bomb.o Game.o Level.o LevelView.o main.o GUI.o PhysicalBody.o PhysicsEngine.o Player.o Ray.o TextureAtlas.o
	g++ -g -std=c++11 *.o -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system

Animator.o: Animator.cpp
	g++ -c $(FLAGS) Animator.cpp

Bomb.o: Bomb.cpp
	g++ -c $(FLAGS) Bomb.cpp

Game.o: Game.cpp
	g++ -c $(FLAGS) Game.cpp

Level.o: Level.cpp
	g++ -c $(FLAGS) Level.cpp

LevelView.o: LevelView.cpp
	g++ -c $(FLAGS) LevelView.cpp

main.o: main.cpp
	g++ -c $(FLAGS) main.cpp

PhysicalBody.o: PhysicalBody.cpp
	g++ -c $(FLAGS) PhysicalBody.cpp

PhysicsEngine.o: PhysicsEngine.cpp
	g++ -c $(FLAGS) PhysicsEngine.cpp

Player.o: Player.cpp
	g++ -c $(FLAGS) Player.cpp

Ray.o: Ray.cpp
	g++ -c $(FLAGS) Ray.cpp

TextureAtlas.o: TextureAtlas.cpp
	g++ -c $(FLAGS) TextureAtlas.cpp

GUI.o: GUI.cpp
	g++ -c $(FLAGS) GUI.cpp

rebuild: *.cpp
	g++ -g -std=c++11 *.cpp -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system

