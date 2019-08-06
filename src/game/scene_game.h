#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "../engine/scene.h"
#include "piece.h"
#include "pieces.h"
#include "board.h"

#define SPEED 500

class SceneGame : public Scene
{
public:
	static SceneGame* Instance() {
		return &sceneGame;
	}
	void load();
	void clean();
	void pause();
	void resume();
	void handleEvent();
	void update(unsigned int dt);
	void draw(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer);

	void createNewPiece();

	Piece currentPiece;
protected:
	SceneGame() {};
private:
	int getRand(int a, int b);

	Pieces *pieces;
	Board *board;
	unsigned int counter;
	int screenHeight;

	Piece nextPiece;

	void drawPiece(Piece piece, SpriteRenderer *renderer);
	void drawBoard(SpriteRenderer *renderer, GeometryRenderer *gRenderer);

	static SceneGame sceneGame;
};

#endif