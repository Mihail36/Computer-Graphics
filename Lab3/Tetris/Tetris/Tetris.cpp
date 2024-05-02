#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib> 
#include <time.h> 

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int HEIGHT_CUP = 27;
const int WIDTH_CUP = 16;
const int SQUARE_SIZE = 40;

const int ACTION_WIDTH = WIDTH / 2;
const int ACTION_HEIGHT = HEIGHT - SQUARE_SIZE;

const int TETRAMINO_SIZE = SQUARE_SIZE/2;
const int STEP_DEFAULT = TETRAMINO_SIZE;

const vector<vector<int>> COLORS = { {1,0,0}, {0,1,0}, {0,0,1}, {1,1,0}, {1,0,1}, {0,1,1} };

struct Coord {
	int x;
	int y;
};

struct Figure {
	vector<Coord> tetramino;
	vector<int> color;
	string typeTetramino;
};

const vector<Figure> ALL_FIGURES_DATA = { {{{0, 0}, {0, 1}, {0, 2}, {1, 2}}, {}, "L"}, {{{0, 0}, {1, 0}, {2, 0}, {1, 1}}, {}, "T"},
	{{{0, 0}, {0, 1}, {0, 2}, {-1, 2}}, {}, "J"}, {{{0, 0}, {-1, 0}, {-1, 1}, {-2, 1}}, {}, "S"}, {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, {}, "Z"},
	{{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, {}, "I"}, {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, {}, "O"} };

int score = 0;
int maxLinesLeft = 5;
int linesLeft = maxLinesLeft;
int level = 1;
int step = STEP_DEFAULT;

bool* keyStates = new bool[256];
bool gameOver = false;

int delay = 1000;

int indexNextFigure;
Figure nextFigure;
vector<Figure> allFigures;
// управление вниз более отзывчивое сделать
//избавиться от глобальных переменных
//Имена функций стилем ООП
void checkForGameOver() {

	for (int i = 0; i < allFigures.size(); i++) {
		for (int j = 0; j < allFigures[i].tetramino.size(); j++) {
			if (allFigures[i].tetramino[j].y == 0)
			{
				gameOver = true;
				delay = 1000;
				maxLinesLeft = 5;
				linesLeft = maxLinesLeft;
				break;
			}
		}
		if (gameOver)
			break;
	}
}

void checkForNextLevel() {
	if (linesLeft <= 0)
	{
		level++;
		delay -= 100;
		allFigures.clear();
		maxLinesLeft += 1;
		linesLeft = maxLinesLeft;

	}
}

void checkForNewScore(int countLines) {
	if (countLines == 1)
	{
		score += 10;
	}
	else if (countLines == 2) {
		score += 30;
	}
	else if (countLines == 3) {
		score += 70;
	}
	else if (countLines == 4) {
		score += 150;
	}
	else if (countLines > 4){
		score += (HEIGHT_CUP - countLines) * 10;
	}
}

Figure getRandFigure() {

	indexNextFigure = rand() % ALL_FIGURES_DATA.size();
	vector<int> newColor = COLORS[rand() % COLORS.size()];
	Figure resTetramino = ALL_FIGURES_DATA[indexNextFigure];
	resTetramino.color = newColor;

	return resTetramino;
}

void initFigure() {

	int startX = SQUARE_SIZE * 6;
	int step = TETRAMINO_SIZE;
	int x, y;

	for (int i = 0; i < ALL_FIGURES_DATA[indexNextFigure].tetramino.size(); i++) {

		if (i != 0) {
			if (ALL_FIGURES_DATA[indexNextFigure].tetramino[i].x > ALL_FIGURES_DATA[indexNextFigure].tetramino[i - 1].x) {
				x += step;
			}
			else if (ALL_FIGURES_DATA[indexNextFigure].tetramino[i].x == ALL_FIGURES_DATA[indexNextFigure].tetramino[i - 1].x) {
				x = x;
			}
			else if (ALL_FIGURES_DATA[indexNextFigure].tetramino[i].x < ALL_FIGURES_DATA[indexNextFigure].tetramino[i - 1].x) {
				x -= step;
			}

			if (ALL_FIGURES_DATA[indexNextFigure].tetramino[i].y > ALL_FIGURES_DATA[indexNextFigure].tetramino[i - 1].y) {
				y += step;
			}
			else if (ALL_FIGURES_DATA[indexNextFigure].tetramino[i].y == ALL_FIGURES_DATA[indexNextFigure].tetramino[i - 1].y) {
				y = y;
			}
			else if (ALL_FIGURES_DATA[indexNextFigure].tetramino[i].y < ALL_FIGURES_DATA[indexNextFigure].tetramino[i - 1].y) {
				y -= step;
			}
		}
		else {
			x = startX;
			y = -SQUARE_SIZE;
		}

		nextFigure.tetramino[i].x = x;
		nextFigure.tetramino[i].y = y;
	}

}

void createNewFigure() {
	nextFigure = getRandFigure();
	initFigure();
}

void addNewFigure() {
	
	allFigures.push_back(nextFigure);

}

bool checkCollisionFall(Coord &currentFigure, string collisionType) {

	bool isCollision = false;

	if (collisionType == "floor") {

		if (currentFigure.y + TETRAMINO_SIZE == ACTION_HEIGHT)
			isCollision = true;
	}
	else {
		for (int i = 0; i < allFigures.size() - 1; i++) {
			for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

				if (currentFigure.y + TETRAMINO_SIZE == allFigures[i].tetramino[j].y && currentFigure.x == allFigures[i].tetramino[j].x) {
					isCollision = true;
					break;
				}
			}
			if (isCollision)
				break;
		}
	}

	return isCollision;
}

void deleteLines(vector<int> deleteTetramino) {

	for (int k = deleteTetramino.size() - 1; k >= 0; k--) {
		vector<vector<int>> needToDelete;
		for (int i = 0; i < allFigures.size(); i++) {
			vector<int> needToDeleteHandler;
			for (int j = 0; j < allFigures[i].tetramino.size(); j++) {
				if (allFigures[i].tetramino[j].y == deleteTetramino[k]) {

					needToDeleteHandler.push_back(j);
				}
			}
			needToDelete.push_back(needToDeleteHandler);
		}
		for (int i = needToDelete.size()-1; i >= 0; i--) {
			for (int j = needToDelete[i].size()-1; j >= 0; j--) {
				allFigures[i].tetramino.erase(allFigures[i].tetramino.begin() + needToDelete[i][j]);
			}
		}

		for (int i = 0; i < allFigures.size(); i++) {
			for (int j = 0; j < allFigures[i].tetramino.size(); j++) {
				if (allFigures[i].tetramino[j].y < deleteTetramino[k]) {
					allFigures[i].tetramino[j].y += TETRAMINO_SIZE;
				}
			}
		}
	}
	linesLeft -= deleteTetramino.size();
}

void checkForDeleteLine() {

	vector <int> deleteIndex;
	for (int i = HEIGHT_CUP * TETRAMINO_SIZE; i >= 0; i -= TETRAMINO_SIZE) {
		int countSquares = 0;
		for (int j = 0; j < allFigures.size(); j++) {
			for (int k = 0; k < allFigures[j].tetramino.size(); k++) {
				if (i == allFigures[j].tetramino[k].y) {
					countSquares++;
				}
			}
		}
		if (countSquares == 16) {
			deleteIndex.push_back(i);
		}
	}
	deleteLines(deleteIndex);
	checkForNewScore(deleteIndex.size());
	checkForNextLevel();
}

void checkForNewFigure() {

	Figure currentFigure = allFigures[allFigures.size() - 1];
	bool alredyCollision = false;
	for (int i = 0; i < currentFigure.tetramino.size(); i++) {

		if (checkCollisionFall(currentFigure.tetramino[i], "floor")) {
			alredyCollision = true;
		}
	}

	if (!alredyCollision) {

		for (int i = 0; i < currentFigure.tetramino.size(); i++) {

			if (checkCollisionFall(currentFigure.tetramino[i], "figure")) {
				alredyCollision = true;
			}
		}
	}

	if (alredyCollision) {

		checkForGameOver();

		if (!gameOver) {
			checkForDeleteLine();
			addNewFigure();
			createNewFigure();
		}
	}
}

bool checkCollisionBorder(Coord currentTetramino, string direction) {

	bool isCollision = false;

	if (direction == "left") {
		if (currentTetramino.x - TETRAMINO_SIZE == SQUARE_SIZE)
			isCollision = true;
		if (!isCollision) {
			for (int i = 0; i < allFigures.size() - 1; i++) {
				for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

					if (currentTetramino.x - TETRAMINO_SIZE == allFigures[i].tetramino[j].x && currentTetramino.y == allFigures[i].tetramino[j].y) {
						isCollision = true;
						break;
					}
				}
				if (isCollision)
					break;
			}
		}
	}
	else {
		if (currentTetramino.x + TETRAMINO_SIZE == ACTION_WIDTH - TETRAMINO_SIZE)
			isCollision = true;
		if (!isCollision) {
			for (int i = 0; i < allFigures.size() - 1; i++) {
				for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

					if (currentTetramino.x + TETRAMINO_SIZE == allFigures[i].tetramino[j].x && currentTetramino.y == allFigures[i].tetramino[j].y) {
						isCollision = true;
						break;
					}
				}
				if (isCollision)
					break;
			}
		}
	}


	return isCollision;
}

bool checkCollisionRotate(Coord &currentTetramino, Coord centralTetramino) {

	bool isCollision = false;

	int centerDiferenceX = centralTetramino.x - currentTetramino.x;
	int centerDiferenceY = centralTetramino.y - currentTetramino.y;
	int currentDiferenceX = currentTetramino.x - centralTetramino.x;
	int currentDiferenceY = currentTetramino.y - centralTetramino.y;

	if (currentTetramino.x > centralTetramino.x) {
		if (currentTetramino.y == centralTetramino.y) {
			if (currentTetramino.y + currentDiferenceX == ACTION_HEIGHT)
				isCollision = true;
			if (!isCollision) {
				for (int i = 0; i < allFigures.size() - 1; i++) {

					for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

						if (currentTetramino.x - currentDiferenceX == allFigures[i].tetramino[j].x && currentTetramino.y + currentDiferenceX == allFigures[i].tetramino[j].y) {
							isCollision = true;
							break;
						}
					}
					if (isCollision)
						break;
				}
			}
		}
		else if (currentTetramino.y > centralTetramino.y) {
			if (currentTetramino.x - TETRAMINO_SIZE * 2 == SQUARE_SIZE)
				isCollision = true;
			if (!isCollision) {
				for (int i = 0; i < allFigures.size() - 1; i++) {
					for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

						if (currentTetramino.x - TETRAMINO_SIZE * 2 == allFigures[i].tetramino[j].x && currentTetramino.y == allFigures[i].tetramino[j].y) {
							isCollision = true;
							break;
						}
					}
					if (isCollision)
						break;
				}
			}
		}
		else if (currentTetramino.y < centralTetramino.y) {
			if (currentTetramino.y + TETRAMINO_SIZE * 2 == ACTION_HEIGHT)
				isCollision = true;
			if (!isCollision) {
				for (int i = 0; i < allFigures.size() - 1; i++) {
					for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

						if (currentTetramino.x == allFigures[i].tetramino[j].x && currentTetramino.y + TETRAMINO_SIZE * 2 == allFigures[i].tetramino[j].y) {
							isCollision = true;
							break;
						}
					}
					if (isCollision)
						break;
				}
			}
		}

	}
	else if (currentTetramino.x < centralTetramino.x) {
		if (currentTetramino.y == centralTetramino.y) {
			for (int i = 0; i < allFigures.size() - 1; i++) {
				for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

					if (currentTetramino.x + centerDiferenceX == allFigures[i].tetramino[j].x && currentTetramino.y - centerDiferenceX == allFigures[i].tetramino[j].y) {
						isCollision = true;
						break;
					}
				}
				if (isCollision)
					break;
			}
		}
		else if (currentTetramino.y > centralTetramino.y) {
			for (int i = 0; i < allFigures.size() - 1; i++) {
				for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

					if (currentTetramino.x == allFigures[i].tetramino[j].x && currentTetramino.y - TETRAMINO_SIZE * 2 == allFigures[i].tetramino[j].y) {
						isCollision = true;
						break;
					}
				}
				if (isCollision)
					break;
			}
		}
		else if (currentTetramino.y < centralTetramino.y) {
			if (currentTetramino.x + TETRAMINO_SIZE * 2 == ACTION_WIDTH - TETRAMINO_SIZE)
				isCollision = true;
			if (!isCollision) {
				for (int i = 0; i < allFigures.size() - 1; i++) {
					for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

						if (currentTetramino.x + TETRAMINO_SIZE * 2 == allFigures[i].tetramino[j].x && currentTetramino.y == allFigures[i].tetramino[j].y) {
							isCollision = true;
							break;
						}
					}
					if (isCollision)
						break;
				}
			}
		}

	}
	else if (currentTetramino.x == centralTetramino.x) {
		if (currentTetramino.y < centralTetramino.y) {
			if (currentTetramino.x + centerDiferenceY == ACTION_WIDTH - TETRAMINO_SIZE)
				isCollision = true;
			if (!isCollision) {
				for (int i = 0; i < allFigures.size() - 1; i++) {
					for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

						if (currentTetramino.x + centerDiferenceY == allFigures[i].tetramino[j].x && currentTetramino.y + centerDiferenceY == allFigures[i].tetramino[j].y) {
							isCollision = true;
							break;
						}
					}
					if (isCollision)
						break;
				}
			}
		}
		else if (currentTetramino.y > centralTetramino.y) {
			if (currentTetramino.x - currentDiferenceY == SQUARE_SIZE)
				isCollision = true;
			if (!isCollision) {
				for (int i = 0; i < allFigures.size() - 1; i++) {
					for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

						if (currentTetramino.x - currentDiferenceY == allFigures[i].tetramino[j].x && currentTetramino.y - currentDiferenceY == allFigures[i].tetramino[j].y) {
							isCollision = true;
							break;
						}
					}
					if (isCollision)
						break;
				}
			}
		}
	}

	return isCollision;
}

void checkForRotate(Coord &currentTetramino, Coord centralTetramino) {

	int centerDiferenceX;
	int centerDiferenceY;
	int currentDiferenceX;
	int currentDiferenceY;
	int offsetXandY;

	if (step != 0) {
		centerDiferenceX = centralTetramino.x - currentTetramino.x;
		centerDiferenceY = centralTetramino.y - currentTetramino.y;
		currentDiferenceX = currentTetramino.x - centralTetramino.x;
		currentDiferenceY = currentTetramino.y - centralTetramino.y;
		offsetXandY = TETRAMINO_SIZE * 2;
	}
	else {
		centerDiferenceX = 0;
		centerDiferenceY = 0;
		currentDiferenceX = 0;
		currentDiferenceY = 0;
		offsetXandY = 0;
	}

	if (currentTetramino.x > centralTetramino.x) {
		if (currentTetramino.y == centralTetramino.y) {
			currentTetramino.x -= currentDiferenceX;
			currentTetramino.y += currentDiferenceX;
		} else if (currentTetramino.y > centralTetramino.y) {
			currentTetramino.x -= offsetXandY;
		} else if (currentTetramino.y < centralTetramino.y) {
			currentTetramino.y += offsetXandY;
		}

	} else if (currentTetramino.x < centralTetramino.x) {
		if (currentTetramino.y == centralTetramino.y) {
			currentTetramino.x += centerDiferenceX;
			currentTetramino.y -= centerDiferenceX;
		} else if (currentTetramino.y > centralTetramino.y) {
			currentTetramino.y -= offsetXandY;
		} else if (currentTetramino.y < centralTetramino.y) {
			currentTetramino.x += offsetXandY;
		}

	} else if (currentTetramino.x == centralTetramino.x) {
		if (currentTetramino.y < centralTetramino.y) {
			currentTetramino.x += centerDiferenceY;
			currentTetramino.y += centerDiferenceY;
		} else if (currentTetramino.y > centralTetramino.y) {
			currentTetramino.x -= currentDiferenceY;
			currentTetramino.y -= currentDiferenceY;
		}
	}
}

void keyStatesDefault(void) {
	keyStates['s'] = false;
	keyStates['a'] = false;
	keyStates['d'] = false;
	keyStates['w'] = false;
	keyStates['p'] = false;
	keyStates['r'] = false;
}

void keyOperations(void) {

	if (keyStates['s']) {
		delay = 100;
	}
	else if (!keyStates['s']) {
		delay = 1000;
	}

	if (keyStates['p']) {
		step = 0;
	}
	else if (!keyStates['p']) {
		step = STEP_DEFAULT;
	}

	if (keyStates['r'] && gameOver) {
		allFigures.clear();
		step = STEP_DEFAULT;
		gameOver = false;
		keyStatesDefault();
		createNewFigure();
		addNewFigure();
		createNewFigure();
		level = 1;
		score = 0;
		keyStates['r'] = false;
	} 

	if (keyStates['r'] && !gameOver){
		keyStates['r'] = false;
	}

	if (keyStates['a']) {
		Figure currentFigure = allFigures[allFigures.size() - 1];
		bool alredyCollision = false;

		for (int i = 0; i < currentFigure.tetramino.size(); i++) {
			if (checkCollisionBorder(currentFigure.tetramino[i] , "left")) {
				alredyCollision = true;
			}
		}
		if (!alredyCollision) {
			for (int i = 0; i < currentFigure.tetramino.size(); i++) {
				currentFigure.tetramino[i].x -= step;
			}
			allFigures[allFigures.size() - 1] = currentFigure;
		}
	}
	if (keyStates['d']) {

		Figure currentFigure = allFigures[allFigures.size() - 1];
		bool alredyCollision = false;

		for (int i = 0; i < currentFigure.tetramino.size(); i++) {
			if (checkCollisionBorder(currentFigure.tetramino[i], "right")) {
				alredyCollision = true;
			}
		}
		if (!alredyCollision) {
			for (int i = 0; i < currentFigure.tetramino.size(); i++) {
				currentFigure.tetramino[i].x += step;
			}
			allFigures[allFigures.size() - 1] = currentFigure;
		}
	}
	if (keyStates['w']) {

		Figure currentFigure = allFigures[allFigures.size() - 1];
		bool alredyCollision = false;

		if (!(currentFigure.typeTetramino == "O")) {
			for (int i = 0; i < currentFigure.tetramino.size(); i++) {

				if (i == 1) {
					continue;
				}
				else {
					if (checkCollisionRotate(currentFigure.tetramino[i], currentFigure.tetramino[1]))
						alredyCollision = true;
				}
			}
			if (!alredyCollision) {
				for (int i = 0; i < currentFigure.tetramino.size(); i++) {

					if (i == 1) {
						continue;
					}
					else {
						checkForRotate(currentFigure.tetramino[i], currentFigure.tetramino[1]);
						allFigures[allFigures.size() - 1] = currentFigure;
					}
				}
			}
			
		}
		keyStates['w'] = false;
	}
}

void drawTetramino(int x, int y, vector<int> color) {
	
		glBegin(GL_QUADS);
		glColor3f(color[0], color[1], color[2]); 
		glVertex2f(x - TETRAMINO_SIZE, y); 
		glVertex2f(x - TETRAMINO_SIZE, y + TETRAMINO_SIZE); 
		glVertex2f(x, y + TETRAMINO_SIZE); 
		glVertex2f(x, y); 
		glEnd();

}

void drawFigure(string typeDraw) {

	int x, y;

	if (typeDraw == "action") {
		for (int i = 0; i < allFigures.size(); i++) {
			for (int j = 0; j < allFigures[i].tetramino.size(); j++) {

				x = allFigures[i].tetramino[j].x;
				y = allFigures[i].tetramino[j].y;
				drawTetramino(x, y, allFigures[i].color);

			}
		}
	}
	else if (typeDraw == "panel")
	{
		int offSetX, offSetY;

		if (nextFigure.typeTetramino == "S") {
			offSetX = WIDTH * 0.63;
			offSetY = HEIGHT * 0.4;
		} else if (nextFigure.typeTetramino == "Z") {
			offSetX = WIDTH * 0.57;
			offSetY = HEIGHT * 0.4;
		} else if (nextFigure.typeTetramino == "J") {
			offSetX = WIDTH * 0.6;
			offSetY = HEIGHT * 0.38;
		} else if (nextFigure.typeTetramino == "L") {
			offSetX = WIDTH * 0.58;
			offSetY = HEIGHT * 0.38;
		} else if (nextFigure.typeTetramino == "O") {
			offSetX = WIDTH * 0.58;
			offSetY = HEIGHT * 0.4;
		} else if (nextFigure.typeTetramino == "I") {
			offSetX = WIDTH * 0.58;
			offSetY = HEIGHT * 0.44;
		} else if (nextFigure.typeTetramino == "T") {
			offSetX = WIDTH * 0.58;
			offSetY = HEIGHT * 0.4;
		}
		
		for (int j = 0; j < nextFigure.tetramino.size(); j++) {

			x = nextFigure.tetramino[j].x + offSetX;
			y = nextFigure.tetramino[j].y + offSetY;
			drawTetramino(x, y, nextFigure.color);

		}
	}
	
}

void drawCup() {

	glViewport(0, 0, ACTION_WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ACTION_WIDTH, HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0); 
	for (int x = 0; x <= ACTION_WIDTH; x++) {
		for (int y = 0; y <= ACTION_HEIGHT; y++) {
			if (x == 0) {
				glVertex2f(x, y);
				glVertex2f(x, y + SQUARE_SIZE); 
				glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE); 
				glVertex2f(x + SQUARE_SIZE, y); 
			}
			else if (x == ACTION_WIDTH - SQUARE_SIZE) {
				glVertex2f(x, y); 
				glVertex2f(x, y + SQUARE_SIZE); 
				glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE); 
				glVertex2f(x + SQUARE_SIZE, y);
			}
			if (y == ACTION_HEIGHT) {
				glVertex2f(x, y); 
				glVertex2f(x, y + SQUARE_SIZE); 
				glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE); 
				glVertex2f(x + SQUARE_SIZE, y); 
			}

		}
	}
	glEnd();

}

void drawInformationPanel() {

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);

	int x, y;
	string text;

	text = "Level: " + to_string(level);

	x = WIDTH * 0.75 - WIDTH * 0.05;
	y = HEIGHT * 0.2;

	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

	text = "Lines left: " + to_string(linesLeft);

	x -= text.size() ;
	y += HEIGHT * 0.05;

	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

	text = "Score: " + to_string(score);

	x = WIDTH * 0.75 - WIDTH * 0.05;
	y += HEIGHT * 0.1;

	glColor3f(0, 0, 0);
	glRasterPos2i(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

	text = "Next Figure:";

	x -= text.size();
	y += HEIGHT * 0.05;

	glColor3f(0, 0, 0);
	glRasterPos2i(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}
	drawFigure("panel");
}

void drawGameOverPanel() {

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);

	int x, y;

	string text = "Press \"ESC\" to Exit";

	x = WIDTH / 2.5;
	y = HEIGHT / 3.5;

	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

	text = "Press  \"R\"  to Retry";

	x = WIDTH / 2.5;
	y = HEIGHT / 2.7;

	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

	text = "Your Score: " + to_string(score);

	x = WIDTH / 2.3;
	y = HEIGHT / 1.7;

	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

	text = "Your Last Level: " + to_string(level);

	x = WIDTH / 2.5;
	y = HEIGHT / 1.5;

	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char symbol : text) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, symbol);
	}

}

void display() {

	if (!gameOver) {

		keyOperations();
		glClearColor(1.0, 1.0, 1.0, 1.0); 
		glClear(GL_COLOR_BUFFER_BIT); 
		drawCup();
		drawFigure("action");
		drawInformationPanel();
		
	} else {
		keyOperations();
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		drawGameOverPanel();
	}
	glutSwapBuffers();
}

void reshapeFunction(int width, int height) {
	glutReshapeWindow(WIDTH, HEIGHT);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
}
 
void update (int value) {

	checkForNewFigure();

	Figure currentFigure = allFigures[allFigures.size() - 1];
	bool alredyCollision = false;

	for (int i = 0; i < currentFigure.tetramino.size(); i++) {

		if (checkCollisionFall(currentFigure.tetramino[i], "floor")) {
			alredyCollision = true;
		}
	}

	if (!alredyCollision) {

		for (int i = 0; i < currentFigure.tetramino.size(); i++) {

			if (checkCollisionFall(currentFigure.tetramino[i], "figure")) {
				alredyCollision = true;
			}
		}
	}

	if (!alredyCollision) {

		for (int i = 0; i < currentFigure.tetramino.size(); i++) {
			currentFigure.tetramino[i].y += step;
		}

	}

	allFigures[allFigures.size() - 1] = currentFigure;

	glutTimerFunc(delay, update, 0);
		
	glutPostRedisplay();
}

void keyboardFunction(unsigned char key, int x, int y) {

	switch (key) {
	case 's': 
		keyStates[key] = true;
		break;
	case 'a': 
		keyStates[key] = true;
		break;
	case 'd':
		keyStates[key] = true;
		break;
	case 'w': 
		keyStates[key] = true;
		break;
	case 'p':
		if (!keyStates[key])
			keyStates[key] = true;
		else 
			keyStates[key] = false;
		break;
	case 'r': 
		keyStates[key] = true;
		break;
	case 27: 
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay(); 
}

void keyboardUpFunction(unsigned char key, int x, int y) {
	switch (key) {
	case 's': 
		keyStates[key] = false;
	case 'a': 
		keyStates[key] = false;
	case 'd': 
		keyStates[key] = false;
	case 'w': 
		keyStates[key] = false;
		break;
	}
	glutPostRedisplay(); 
}

int main(int argc, char** argv) {

	srand(time(0));
	keyStatesDefault();
	createNewFigure();
	addNewFigure();
	createNewFigure();

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(WIDTH, HEIGHT); 
	glutCreateWindow("GLUT Shapes"); 

	glutDisplayFunc(display); 
	glutReshapeFunc(reshapeFunction); 
	glutKeyboardFunc(keyboardFunction);
	glutKeyboardUpFunc(keyboardUpFunction);
	glutTimerFunc(delay, update, 0);

	glutMainLoop();
	 
	return 0;
}