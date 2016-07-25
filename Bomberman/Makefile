COMPILER=g++
FLAGS=-g -std=c++11

all: Bomberman

Bomberman: Animator.o Bomb.o Game.o Level.o LevelView.o main.o GUI.o PhysicalBody.o PhysicsEngine.o Player.o Ray.o TextureAtlas.o BombManager.o Button.o Menu.o Option.o Slider.o
	$(COMPILER) $(FLAGS) *.o -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Animator.o: Animator.cpp
	$(COMPILER) -c $(FLAGS) Animator.cpp

Bomb.o: Bomb.cpp
	$(COMPILER) -c $(FLAGS) Bomb.cpp

Button.o: Button.cpp
	$(COMPILER) -c $(FLAGS) Button.cpp

Game.o: Game.cpp
	$(COMPILER) -c $(FLAGS) Game.cpp

Level.o: Level.cpp
	$(COMPILER) -c $(FLAGS) Level.cpp

LevelView.o: LevelView.cpp
	$(COMPILER) -c $(FLAGS) LevelView.cpp

main.o: main.cpp
	$(COMPILER) -c $(FLAGS) main.cpp

Menu.o: Menu.cpp
	$(COMPILER) -c $(FLAGS) Menu.cpp

PhysicalBody.o: PhysicalBody.cpp
	$(COMPILER) -c $(FLAGS) PhysicalBody.cpp

PhysicsEngine.o: PhysicsEngine.cpp
	$(COMPILER) -c $(FLAGS) PhysicsEngine.cpp

Player.o: Player.cpp
	$(COMPILER) -c $(FLAGS) Player.cpp

Ray.o: Ray.cpp
	$(COMPILER) -c $(FLAGS) Ray.cpp

Option.o: Option.cpp
	$(COMPILER) -c $(FLAGS) Option.cpp

TextureAtlas.o: TextureAtlas.cpp
	$(COMPILER) -c $(FLAGS) TextureAtlas.cpp

GUI.o: GUI.cpp
	$(COMPILER) -c $(FLAGS) GUI.cpp

BombManager.o: BombManager.cpp
	$(COMPILER) -c $(FLAGS) BombManager.cpp

Slider.o: Slider.cpp
	$(COMPILER) -c $(FLAGS) Slider.cpp
clean: *.o
	rm *.o

rebuild: *.cpp
	$(COMPILER) -g $(FLAGS) *.cpp -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system
