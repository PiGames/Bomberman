
FLAGS=-g -std=c++11

all: Bomberman

Bomberman: Animator.o Bomb.o Game.o Level.o LevelView.o main.o GUI.o PhysicalBody.o PhysicsEngine.o Player.o Ray.o TextureAtlas.o BombManager.o Button.o Menu.o Option.o
	g++ $(FLAGS) *.o -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Animator.o: Animator.cpp
	g++ -c $(FLAGS) Animator.cpp

Bomb.o: Bomb.cpp
	g++ -c $(FLAGS) Bomb.cpp

Button.o: Button.cpp
	g++ -c $(FLAGS) Button.cpp

Game.o: Game.cpp
	g++ -c $(FLAGS) Game.cpp

Level.o: Level.cpp
	g++ -c $(FLAGS) Level.cpp

LevelView.o: LevelView.cpp
	g++ -c $(FLAGS) LevelView.cpp

main.o: main.cpp
	g++ -c $(FLAGS) main.cpp

Menu.o: Menu.cpp
	g++ -c $(FLAGS) Menu.cpp

PhysicalBody.o: PhysicalBody.cpp
	g++ -c $(FLAGS) PhysicalBody.cpp

PhysicsEngine.o: PhysicsEngine.cpp
	g++ -c $(FLAGS) PhysicsEngine.cpp

Player.o: Player.cpp
	g++ -c $(FLAGS) Player.cpp

Ray.o: Ray.cpp
	g++ -c $(FLAGS) Ray.cpp

Option.o: Option.cpp
	g++ -c $(FLAGS) Option.cpp

TextureAtlas.o: TextureAtlas.cpp
	g++ -c $(FLAGS) TextureAtlas.cpp

GUI.o: GUI.cpp
	g++ -c $(FLAGS) GUI.cpp

BombManager.o: BombManager.cpp
	g++ -c $(FLAGS) BombManager.cpp
clean: *.o
	rm *.o

rebuild: *.cpp
	g++ -g -std=c++11 *.cpp -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system

