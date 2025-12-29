#ifndef PACMANBOARD_H
#define PACMANBOARD_H

#include <iostream>
#include <vector>
using namespace std;

#include <QFrame>
#include <QPointer>

#include "Pacman.h"
#include "ghost.h"

class QLabel;

class PacmanBoard : public QFrame
{
	Q_OBJECT

	public:
	    PacmanBoard(QWidget *parent = 0);

	public slots:
		void start();
		void pause();
		void updateLogic();

	signals:
		void lifesChanged(int score);
		void scoreChanged(int level);

	protected:
		void paintEvent(QPaintEvent *event);
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
 
	private:
		int win;

		void movePacman();

		QTimer *timer;

		int chooseDirectionToMoveGhost(Ghost *g);
		void moveGhosts(Ghost *g);
		void clearBoard();

		bool isStarted;
		bool isPaused;
		int score;
		int lifes;

		int coinsInMap;

		Pacman *pacman;

		// 4 ghosts
		Ghost *ga;
		Ghost *gb;
		Ghost *gc;
		Ghost *gd;

		vector< vector<int> > board;
				
};

#endif
