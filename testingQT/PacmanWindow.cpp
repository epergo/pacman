#include <QtGui>

#include "PacmanBoard.h"
#include "PacmanWindow.h"

PacmanWindow::PacmanWindow()
{
	board = new PacmanBoard;
	scoreLcd = new QLCDNumber(5);
	scoreLcd->setSegmentStyle(QLCDNumber::Filled);
	lifesLcd = new QLCDNumber(5);
	lifesLcd->setSegmentStyle(QLCDNumber::Filled);

	startButton = new QPushButton(tr("&Start"));
	startButton->setFocusPolicy(Qt::NoFocus);
	quitButton = new QPushButton(tr("&Quit"));
	quitButton->setFocusPolicy(Qt::NoFocus);
	pauseButton = new QPushButton(tr("&Pause"));
	pauseButton->setFocusPolicy(Qt::NoFocus);

	connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
	connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
	connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
	connect(board, SIGNAL(lifesChanged(int)), lifesLcd, SLOT(display(int)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(createLabel(tr("SCORE")), 0, 0);
	layout->addWidget(scoreLcd, 0, 0);
	layout->addWidget(createLabel(tr("LIFES")), 1, 0);
	layout->addWidget(lifesLcd, 1, 0);
	layout->addWidget(startButton, 2, 0);
	layout->addWidget(quitButton, 4, 0);
	layout->addWidget(pauseButton, 3, 0);
	layout->addWidget(board, 0, 1, 5, 1);
	layout->setColumnMinimumWidth(1,200);
	layout->setColumnStretch(1,1);
	setLayout(layout);

	setWindowTitle(tr("Pacman"));
	resize(720, 330);
}

QLabel *PacmanWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	return lbl;
}





































