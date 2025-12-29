#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H


#include <QFrame>
#include <QWidget>

#include "PacmanBoard.h"

class QLCDNumber;
class QLabel;
class QPushButton;

class PacmanBoard;

class PacmanWindow : public QWidget
{
	Q_OBJECT
	
	public:
		PacmanWindow();

	private:
    	QLabel *createLabel(const QString &text);

		PacmanBoard *board;

		QLCDNumber *scoreLcd;
		QLCDNumber *lifesLcd;

		QPushButton *startButton;
		QPushButton *quitButton;
		QPushButton *pauseButton;
 };

#endif
