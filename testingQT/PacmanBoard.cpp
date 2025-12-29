#include <QtGui>

#include "auxiliaryFunctions.cpp"
#include <cstdlib> 
#include <ctime> 
#include "PacmanBoard.h"

PacmanBoard::PacmanBoard(QWidget *parent): QFrame(parent)
{	
	coinsInMap = 0;

	pacman = new Pacman;

	ga = new Ghost(1, 9, 3, 1);
	gb = new Ghost(1, 18, 1, 3);
	gc = new Ghost(13, 9, 3, 1);
	gd = new Ghost(13, 18, 1, 3);

	board = readingBoard();
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();

	win = 0;

	// Initialization of the random seed
	srand((unsigned)time(0)); 

	timer = new QTimer(this);
 	connect(timer, SIGNAL(timeout()), this, SLOT(updateLogic()));
 	timer->start(30);
}

void PacmanBoard::start()
{
	if (isPaused)
        return;

    isStarted = true;
	
	QSound::play("../res/pacman_beginning.wav");

    score = 0;
    lifes = 2;
    clearBoard();

    emit scoreChanged(score);
    emit lifesChanged(lifes);
}

void PacmanBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {

    } else {

    }
    update();
}

void PacmanBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
	
	for(int j = 0; j < 15; j++)
	{
		for(int i = 0; i < 30; i++)
		{
			int inside = board.at(j).at(i);

			if(inside == 0)
			{
				painter.setBrush(QColor(0, 0, 0));
				painter.drawRect(i * 20 + 1, j * 20 + 1, 20, 20);
			}else if(inside == 1)
			{
				painter.setBrush(QColor(0, 0, 0));
				painter.drawRect(i * 20 + 1, j * 20 + 1, 20, 20);
				QPixmap sprite("../res/coin.png");
			    painter.drawPixmap(i * 20 + 8, j * 20 + 8, 4 , 4, sprite);
			}else if(inside == 2)
			{
				painter.setBrush(QColor(0, 0, 0));
				painter.drawRect(i * 20 + 1, j * 20 + 1, 20, 20);
				QPixmap sprite("../res/invencibility.png");
			    painter.drawPixmap(i * 20 + 4, j * 20 + 4, 16 , 16, sprite);
			}else if(inside == 5)
			{
				QPixmap sprite("../res/wall.png");
				painter.drawPixmap(i * 20 + 1, j * 20 + 1, 20, 20, sprite);
			}else if(inside == 6)
			{
				painter.setBrush(QColor(255, 255, 255));
				painter.drawRect(i * 20 + 1, j * 20 + 1, 20, 20);
			}
			
		}
		ga->drawGhost(&painter);
		gb->drawGhost(&painter);
		gc->drawGhost(&painter);
		gd->drawGhost(&painter);	

		pacman->drawPacman(&painter);
	}
	
}

void PacmanBoard::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) 
	{
	    case Qt::Key_Left:
			pacman->keyLeft = 0;	
	        break;
    	case Qt::Key_Right:
			pacman->keyRight = 0;		
	        break;
     	case Qt::Key_Down:
			pacman->keyDown = 0;	
         	break;
     	case Qt::Key_Up:
			pacman->keyUp = 0;	
        	break;
     	default:
        	QFrame::keyPressEvent(event);

	}
}

void PacmanBoard::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) 
	{
	    case Qt::Key_Left:
			pacman->facing = 3;
			pacman->keyLeft = 1;	
	        break;
    	case Qt::Key_Right:
			pacman->facing = 1;
			pacman->keyRight = 1;		
	        break;
     	case Qt::Key_Down:
			pacman->facing = 2;
			pacman->keyDown = 1;	
         	break;
     	case Qt::Key_Up:
			pacman->facing = 0;
			pacman->keyUp = 1;	
        	break;
     	default:
        	QFrame::keyPressEvent(event);

	}

}

void PacmanBoard::movePacman()
{
	// Pacman values
	int a = pacman->x();
	int b = pacman->x2();
	int c = pacman->y();
	int d = pacman->y2();

	/**************************************** KEY LEFT ************************************************/

	if(pacman->keyLeft == 1)
	{
		if(board.at(a/20).at(c/20 - 1) != 5 && board.at(a/20).at(c/20 - 1) != 6) 
		{
			if(board.at(b/20).at(c/20 - 1) != 5 && board.at(b/20).at(c/20 - 1) != 6)
			{
				pacman->setY(c - pacman->velocity);
			}else{
				int wall = (c/20 - 1) * 20 + 20;
				if(c - pacman->velocity >= wall)
				{
					pacman->setY(c - pacman->velocity);
				}		
			}
		}else{
			int wall = (c/20 - 1) * 20 + 20;
			if(c - pacman->velocity >= wall)
			{
				pacman->setY(c - pacman->velocity);
			}		
		}
	}

	/**************************************** KEY RIGHT ************************************************/

	if(pacman->keyRight == 1)
	{

		if(board.at(a/20).at(d/20 + 1) != 5 && board.at(a/20).at(d/20 + 1) != 6) 
		{
			if(board.at(b/20).at(d/20 + 1) != 5 && board.at(b/20).at(d/20 + 1) != 6)
			{
				pacman->setY(c + pacman->velocity);
			}else{
				int wall = ((d)/20 + 1) * 20;
				if(d + pacman->velocity < wall)
				{
					pacman->setY(c + pacman->velocity);
				}		
			}
		}else{
			int wall = ((d)/20 + 1) * 20;
			if(d + pacman->velocity < wall)
			{
				pacman->setY(c + pacman->velocity);
			}		
		}
	}

	/**************************************** KEY UP ************************************************/

	if(pacman->keyUp == 1)
	{
		if(board.at(a/20 - 1).at(c/20) != 5 && board.at(a/20 - 1).at(c/20) != 6) 
		{
			if(board.at(a/20 - 1).at(d/20) != 5 && board.at(a/20 - 1).at(d/20) != 6)
			{
				pacman->setX(a - pacman->velocity);
			}else{
				int wall = (a/20 - 1) * 20 + 20;

				if(a - pacman->velocity >= wall)
				{
					pacman->setX(a - pacman->velocity);
				}
			}		
		}else{
			int wall = (a/20 - 1) * 20 + 20;

			if(a - pacman->velocity >= wall)
			{
				pacman->setX(a - pacman->velocity);
			}
		}
	} 

	/**************************************** KEY DOWN ************************************************/

	if(pacman->keyDown == 1)
	{
		if(board.at(b/20 + 1).at(c/20) != 5 && board.at(b/20 + 1).at(c/20) != 6) 
		{
			if(board.at(b/20 + 1).at(d/20) != 5 && board.at(b/20 + 1).at(d/20) != 6)
			{
				pacman->setX(a + pacman->velocity);
			}else{
				int wall = (b/20 + 1) * 20;

				if(b + pacman->velocity < wall)
				{
					pacman->setX(a + pacman->velocity);
				}
			}		
		}else{
			int wall = (b/20 + 1) * 20;

			if(b + pacman->velocity < wall)
			{
				pacman->setX(a + pacman->velocity);
			}
		}
	} 	

	update();
}

int PacmanBoard::chooseDirectionToMoveGhost(Ghost *g)
{
	/*
		Generate one random number from 0 to 100, for each direction check that:
			· the random number is below 25 ( < 25 for up), 
			50 ( < 50 for right), 75 ( < 75 for down), 100 ( < 100 for left)
			· ghost is not coming from that direction
			· the next position in that direction doesn't belong to a wall

		If we check all the positions and in everything something fails, create a new random number
		but now from 0 to 75 and check again all, everytime we check all, create a new random number
		25 units lower.

		If the number reach < 0, choose the first direction without a wall AND the one which is 
		not where the ghost came from.
	*/	

	int range = 100;

 	// Random integer between 0 and 100
    int random_integer = (rand()%range)+1; 

	int loop = 1;

	cout << "x: " << g->x() << " x2: " << g->x2() << " y: " << g->y() << " y2: " << g->y2() << endl;

	while(loop)
	{
		if(pacman->counterInv == 0)
		{
			if((g->comingFrom != 0 && board.at(g->x()/20 - 1).at(g->y()/20) != 5) && (abs(pacman->x()/20 - g->x()/20 + 1) < abs(pacman->x()/20 - g->x()/20)))
			{
				g->comingFrom = 2;
				return 0;
			}else if((g->comingFrom != 1 && board.at(g->x()/20).at(g->y()/20 + 1) != 5) && (abs(pacman->y()/20 - g->y()/20 - 1) < abs(pacman->y()/20 - g->y()/20)))
			{
			

				g->comingFrom = 3;
				return 1;
			}else if((g->comingFrom != 2 && board.at(g->x()/20 + 1).at(g->y()/20) != 5) && (abs(pacman->x()/20 - g->x()/20 - 1) < abs(pacman->x()/20 - g->x()/20)))
			{
				g->comingFrom = 0;
				return 2;
			}else if((g->comingFrom != 3 && board.at(g->x()/20).at(g->y()/20 - 1) != 5) && (abs(pacman->y()/20 - g->y()/20 + 1) < abs(pacman->y()/20 - g->y()/20)))
			{
				g->comingFrom = 1;
				return 3;
			}	
		

			if(range > 0 && range - 25 > 0 )
			{
				range -= 25;

				random_integer = (rand()%range)+1; 
			}else{
				if(g->comingFrom != 0 && board.at(g->x()/20 - 1).at(g->y()/20) != 5)
				{
					g->comingFrom = 2;
					return 0;
				}else if(g->comingFrom != 1 && board.at(g->x()/20).at(g->y()/20 + 1) != 5)
				{
					g->comingFrom = 3;
					return 1;
				}else if(g->comingFrom != 2 && board.at(g->x()/20 + 1).at(g->y()/20) != 5)
				{
					g->comingFrom = 0;
					return 2;
				}else if(g->comingFrom != 3 && board.at(g->x()/20).at(g->y()/20 - 1) != 5)
				{
					g->comingFrom = 1;
					return 3;
				}	
			}

		}else{
			if((board.at(g->x()/20 - 1).at(g->y()/20) != 5) && (abs(pacman->x()/20 - g->x()/20 + 1) > abs(pacman->x()/20 - g->x()/20)))
			{
				g->comingFrom = 2;
				return 0;
			}else if((board.at(g->x()/20).at(g->y()/20 + 1) != 5) && (abs(pacman->y()/20 - g->y()/20 - 1) > abs(pacman->y()/20 - g->y()/20)))
			{
				g->comingFrom = 3;
				return 1;
			}else if((board.at(g->x()/20 + 1).at(g->y()/20) != 5) && (abs(pacman->x()/20 - g->x()/20 - 1) > abs(pacman->x()/20 - g->x()/20)))
			{
				g->comingFrom = 0;
				return 2;
			}else if((board.at(g->x()/20).at(g->y()/20 - 1) != 5) && (abs(pacman->y()/20 - g->y()/20 + 1) > abs(pacman->y()/20 - g->y()/20)))
			{
				g->comingFrom = 1;
				return 3;
			}	

			if(board.at(g->x()/20 - 1).at(g->y()/20) != 5)
			{
				g->comingFrom = 2;
				return 0;
			}else if(board.at(g->x()/20).at(g->y()/20 + 1) != 5)
			{
				g->comingFrom = 3;
				return 1;
			}else if(board.at(g->x()/20 + 1).at(g->y()/20) != 5)
			{
				g->comingFrom = 0;
				return 2;
			}else if(board.at(g->x()/20).at(g->y()/20 - 1) != 5)
			{
				g->comingFrom = 1;
				return 3;
			}	
		}
		
	}
	return -1;

}

void PacmanBoard::moveGhosts(Ghost *g)
{
	// Ghost values
	int a = g->x();
	int b = g->x2();
	int c = g->y();
	int d = g->y2();

	/**************************************** DIRECTION LEFT ************************************************/

	if(g->goingTo == 3)
	{
		if(board.at(a/20).at(c/20 - 1) != 5 && board.at(a/20).at(c/20 - 1) != 6) 
		{
			if(board.at(b/20).at(c/20 - 1) != 5 && board.at(b/20).at(c/20 - 1) != 6)
			{
				g->setY(c - g->velocity);
			}else{
				int wall = (c/20 - 1) * 20 + 20;
				if(c - g->velocity >= wall)
				{
					g->setY(c - g->velocity);
				}		
			}
		}else{
			int wall = (c/20 - 1) * 20 + 20;
			if(c - g->velocity >= wall)
			{
				g->setY(c - g->velocity);
			}		
		}
	}

	/**************************************** DIRECTION RIGHT ************************************************/

	if(g->goingTo == 1)
	{

		if(board.at(a/20).at(d/20 + 1) != 5 && board.at(a/20).at(d/20 + 1) != 6) 
		{
			if(board.at(b/20).at(d/20 + 1) != 5 && board.at(b/20).at(d/20 + 1) != 6)
			{
				g->setY(c + g->velocity);
			}else{
				int wall = ((d)/20 + 1) * 20;
				if(d + g->velocity < wall)
				{
					g->setY(c + g->velocity);
				}		
			}
		}else{
			int wall = ((d)/20 + 1) * 20;
			if(d + g->velocity < wall)
			{
				g->setY(c + g->velocity);
			}		
		}
	}

	/**************************************** DIRECTION UP ************************************************/

	if(g->goingTo == 0)
	{
		if(board.at(a/20 - 1).at(c/20) != 5 && board.at(a/20 - 1).at(c/20) != 6) 
		{
			if(board.at(a/20 - 1).at(d/20) != 5 && board.at(a/20 - 1).at(d/20) != 6)
			{
				g->setX(a - g->velocity);
			}else{
				int wall = (a/20 - 1) * 20 + 20;

				if(a - g->velocity >= wall)
				{
					g->setX(a - g->velocity);
				}
			}		
		}else{
			int wall = (a/20 - 1) * 20 + 20;

			if(a - g->velocity >= wall)
			{
				g->setX(a - g->velocity);
			}
		}
	} 

	/**************************************** DIRECTION DOWN ************************************************/

	if(g->goingTo == 2)
	{
		if(board.at(b/20 + 1).at(c/20) != 5 && board.at(b/20 + 1).at(c/20) != 6) 
		{
			if(board.at(b/20 + 1).at(d/20) != 5 && board.at(b/20 + 1).at(d/20) != 6)
			{
				g->setX(a + g->velocity);
			}else{
				int wall = (b/20 + 1) * 20;

				if(b + g->velocity < wall)
				{
					g->setX(a + g->velocity);
				}
			}		
		}else{
			int wall = (b/20 + 1) * 20;

			if(b + g->velocity < wall)
			{
				g->setX(a + g->velocity);
			}
		}
	} 	

}

void PacmanBoard::clearBoard()
{
	if(win == 1)
	{
		isStarted = false;

		lifes = 2;
		score = 0;

		board = readingBoard();

		lifesChanged(lifes);
		scoreChanged(score);

		pacman = new Pacman;

		ga = new Ghost(1, 9, 3, 1);
		gb = new Ghost(1, 18, 1, 3);
		gc = new Ghost(13, 9, 3, 1);
		gd = new Ghost(13, 18, 1, 3);

		QDialog *youWin = new QDialog;
		youWin->setWindowTitle ("You have won");
		youWin->setGeometry(300,400,240,60);
		QPushButton *playAgain;
		playAgain = new QPushButton(tr("&Play again"));
		playAgain->setFocusPolicy(Qt::NoFocus);
		QPushButton *exit;
		exit = new QPushButton(tr("&Exit game"));
		exit->setFocusPolicy(Qt::NoFocus);
		connect(playAgain, SIGNAL(clicked()), this, SLOT(start()));
		connect(playAgain, SIGNAL(clicked()), youWin, SLOT(close()));
		connect(exit , SIGNAL(clicked()), qApp, SLOT(quit()));

		QGridLayout *layout = new QGridLayout;
		layout->addWidget(playAgain, 2, 0);
		layout->addWidget(exit, 4, 0);
		youWin->setLayout(layout);

    	youWin->show();
	}else if(lifes >= 0)
	{
		pacman = new Pacman;

		ga = new Ghost(1, 9, 3, 1);
		gb = new Ghost(1, 18, 1, 3);
		gc = new Ghost(13, 9, 3, 1);
		gd = new Ghost(13, 18, 1, 3);
	}else{
		isStarted = false;

		lifes = 2;
		score = 0;

		board = readingBoard();

		lifesChanged(lifes);
		scoreChanged(score);

		pacman = new Pacman;

		ga = new Ghost(1, 9, 3, 1);
		gb = new Ghost(1, 18, 1, 3);
		gc = new Ghost(13, 9, 3, 1);
		gd = new Ghost(13, 18, 1, 3);

		QDialog *gameOver = new QDialog;
		gameOver->setWindowTitle ("Game over");
		gameOver->setGeometry(300,400,240,60);
		QPushButton *playAgain;
		playAgain = new QPushButton(tr("&Play again"));
		playAgain->setFocusPolicy(Qt::NoFocus);
		QPushButton *exit;
		exit = new QPushButton(tr("&Exit game"));
		exit->setFocusPolicy(Qt::NoFocus);
		connect(playAgain, SIGNAL(clicked()), this, SLOT(start()));
		connect(playAgain, SIGNAL(clicked()), gameOver, SLOT(close()));
		connect(exit , SIGNAL(clicked()), qApp, SLOT(quit()));

		QGridLayout *layout = new QGridLayout;
		layout->addWidget(playAgain, 2, 0);
		layout->addWidget(exit, 4, 0);
		gameOver->setLayout(layout);

    	gameOver->show();
	}

	

}

void PacmanBoard::updateLogic()
{
	if (!isStarted || isPaused)
	{
        return;
    }

	if(pacman->counterInv > 0)
	{
		ga->ghostScared = 1;
		gb->ghostScared = 1;
		gc->ghostScared = 1;
		gd->ghostScared = 1;

		pacman->counterInv -= 1;
	}else{
		ga->ghostScared = 0;
		gb->ghostScared = 0;
		gc->ghostScared = 0;
		gd->ghostScared = 0;
	}

	movePacman();

	if(pacman->x()/20 == pacman->x2()/20 && pacman->y()/20 == pacman->y2()/20)
	{
		if(board.at(pacman->x2()/20).at(pacman->y2()/20) == 1)
		{
			board.at(pacman->x2()/20).at(pacman->y2()/20) = 0;
			coinsInMap += 1;
			score += 50;
			scoreChanged(score);
		}else if(board.at(pacman->x2()/20).at(pacman->y2()/20) == 2)
		{
			pacman->counterInv = 167;

			board.at(pacman->x2()/20).at(pacman->y2()/20) = 0;
			score += 150;
			scoreChanged(score);
		}
	}

	int aux = 0;

	if((ga->x()/20 == ga->x2()/20 && ga->prevPosX != ga->x()/20) 
		|| (ga->y()/20 == ga->y2()/20 && ga->prevPosY != ga->y()/20))
	{
		ga->prevPosX = ga->x()/20;
		ga->prevPosY = ga->y()/20;

		
		aux = chooseDirectionToMoveGhost(ga);

		ga->goingTo = aux;
	}

	if((gb->x()/20 == gb->x2()/20 && gb->prevPosX != gb->x()/20) 
		|| (gb->y()/20 == gb->y2()/20 && gb->prevPosY != gb->y()/20))
	{
		gb->prevPosX = gb->x()/20;
		gb->prevPosY = gb->y()/20;

		aux = chooseDirectionToMoveGhost(gb);

		gb->goingTo = aux;
	}

	if((gc->x()/20 == gc->x2()/20 && gc->prevPosX != gc->x()/20) 
		|| (gc->y()/20 == gc->y2()/20 && gc->prevPosY != gc->y()/20))
	{
		gc->prevPosX = gc->x()/20;
		gc->prevPosY = gc->y()/20;
		
		aux = chooseDirectionToMoveGhost(gc);

		gc->goingTo = aux;
	}

	if((gd->x()/20 == gd->x2()/20 && gd->prevPosX != gd->x()/20) 
		|| (gd->y()/20 == gd->y2()/20 && gd->prevPosY != gd->y()/20))
	{
		gd->prevPosX = gd->x()/20;
		gd->prevPosY = gd->y()/20;

		aux = chooseDirectionToMoveGhost(gd);

		gd->goingTo = aux;
	}

	moveGhosts(ga);
	moveGhosts(gb);
	moveGhosts(gc);
	moveGhosts(gd);

	if((ga->x2()/20 == pacman->x2()/20 && ga->y()/20 == pacman->y()/20)
		|| (ga->x()/20 == pacman->x()/20 && ga->y2()/20 == pacman->y2()/20))
	{
		if(ga->ghostScared == 0)
		{
			lifes -= 1;
			lifesChanged(lifes);
			clearBoard();
		}else{
			score += 200;
			scoreChanged(score);

			ga = new Ghost(1, 9, 3, 1);
		}

		
	}

	if((gb->x2()/20 == pacman->x2()/20 && gb->y()/20 == pacman->y()/20)
		|| (gb->x()/20 == pacman->x()/20 && gb->y2()/20 == pacman->y2()/20))
	{
		
			
		if(gb->ghostScared == 0)
		{
			lifes -= 1;
			lifesChanged(lifes);
			clearBoard();
		}else{
			score += 200;
			scoreChanged(score);

			gb = new Ghost(1, 18, 1, 3);
		}

}

	if((gc->x2()/20 == pacman->x2()/20 && gc->y()/20 == pacman->y()/20)
		|| (gc->x()/20 == pacman->x()/20 && gc->y2()/20 == pacman->y2()/20))
	{
		if(gb->ghostScared == 0)
		{
			lifes -= 1;
			lifesChanged(lifes);
			clearBoard();
		}else{
			score += 200;
			scoreChanged(score);

			gc = new Ghost(13, 9, 3, 1);
		}
	}

	if((gd->x2()/20 == pacman->x2()/20 && gd->y()/20 == pacman->y()/20)
		|| (gd->x()/20 == pacman->x()/20 && gd->y2()/20 == pacman->y2()/20))
	{
		

		if(gb->ghostScared == 0)
		{
			lifes -= 1;
		lifesChanged(lifes);
		clearBoard();
		}else{
			score += 200;
			scoreChanged(score);

			gd = new Ghost(13, 18, 1, 3);
		}
	}
	

	if(coinsInMap == 219)
	{
		win = 1;
		clearBoard();
	}


}	
