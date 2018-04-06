#makefile battle
CFLAGS=-w -O2 -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

#cible:dependances
#	(tabulation) commandes

all: main.o GameEngine.o introductionStage.o keyboardStage.o heart.o boss.o eagle.o bullet.o bullets.o eaglesp.o ship.o animFrame.o Scores.o gameStage.o conclusionStage.o
	g++ main.o GameEngine.o introductionStage.o keyboardStage.o heart.o boss.o eagle.o bullet.o bullets.o eaglesp.o ship.o animFrame.o Scores.o gameStage.o conclusionStage.o -o battle.x $(CFLAGS)
	
#
main.o: main.c GameEngine.c introductionStage.c
	g++ -c main.c -o main.o
	
#
GameEngine.o:GameEngine.c
	g++ -c GameEngine.c -o GameEngine.o

#
keyboardStage.o:keyboardStage.c GameEngine.c
	g++ -c keyboardStage.c -o keyboardStage.o
#
introductionStage.o:introductionStage.c GameEngine.c eaglesp.c bullet.c ship.c
	g++ -c introductionStage.c -o introductionStage.o

#
eagle.o:eagle.c GameEngine.c
	g++ -c eagle.c -o eagle.o
		
#
eaglesp.o:eaglesp.c eagle.c GameEngine.c
	g++ -c eaglesp.c -o eaglesp.o
#	
boss.o:boss.c GameEngine.c
	g++ -c boss.c -o boss.o
#
heart.o:heart.c GameEngine.c
	g++ -c heart.c -o heart.o
	
#
bullet.o:bullet.c GameEngine.c
	g++ -c bullet.c -o bullet.o
	
#
bullets.o:bullets.c bullet.c GameEngine.c
	g++ -c bullets.c -o bullets.o
#
ship.o:ship.c GameEngine.c animFrame.c
	g++ -c ship.c -o ship.o

#
animFrame.o:animFrame.c GameEngine.c	
	g++ -c animFrame.c -o animFrame.o
	
#
Scores.o:Scores.c GameEngine.c
	g++ -c Scores.c -o Scores.o
#
gameStage.o:gameStage.c GameEngine.c eaglesp.c ship.c boss.c
	g++ -c gameStage.c -o gameStage.o
#
conclusionStage.o:conclusionStage.c GameEngine.c Scores.c
	g++ -c conclusionStage.c -o conclusionStage.o
#
#clean fichiers obj
clean:
	rm -rf *.o
#

