#include <string>

#include <QtGui>

using namespace std;


class Ghost
{
	private:
		int posX;
		int posY;

		int posXBoard;
		int posYBoard;

		string ghostL1;
		string ghostL2;
		string ghostR1;
		string ghostR2;

	public:
		int ghostScared;

		int prevPosX;
		int prevPosY;

		int goingTo;
		int velocity;

		// towards which direction is the ghost , 0 left,1 right
		int facing;
		// Ghost has 2 sprites
		int spriteActive; 

		int comingFrom;

		Ghost(int a, int b, int c, int g)
		{
			velocity = 2;
			spriteActive = 0;
			facing = 0;
			spriteActive = 0;

			goingTo = g;

			comingFrom = c;

			posX = a * 20;
			posY = b * 20;

			prevPosX = a * 20;;
			prevPosY = b * 20;;

			ghostL1 = "../res/ghostLeft1.png";
			ghostL2 = "../res/ghostLeft2.png";
			ghostR1 = "../res/ghostRight1.png";
			ghostR2 = "../res/ghostRight2.png";

			spriteActive = 0;

			posXBoard = a;
			posYBoard = b;

		}

		int x() const 
		{
			return posX;
		}

		int y() const
		{
			return posY;
		}

		int x2() const 
		{
			return posX + 18;
		}

		int y2() const
		{
			return posY + 18;
		}

		void setX(int x) 
		{
			posX = x;
		}

		void setY(int y)
		{
			posY = y;
		}

		double xBoard() const 
		{
			return posX / 20;
		}

		double yBoard() const
		{
			return posY / 20;
		}

		void setXBoard(double x) 
		{
			posXBoard = x;
		}

		void setYBoard(double y)
		{
			posYBoard = y;
		}

		void drawGhost(QPainter *painter)
		{
			if(ghostScared == 0)
			{
				if(spriteActive < 90)
				{
					if(facing == 0)
					{
						QPixmap sprite("../res/ghostLeft1.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}else if(facing == 1){
						QPixmap sprite("../res/ghostRight1.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}
					spriteActive += 1;
				}else if(spriteActive < 140){
					if(facing == 0)
					{
						QPixmap sprite("../res/ghostLeft2.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}else if(facing == 1){
						QPixmap sprite("../res/ghostRight2.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}
					spriteActive += 1;
				}else{
					spriteActive = 0;
				}		
			}else{
				if(spriteActive < 90)
				{
					if(facing == 0)
					{
						QPixmap sprite("../res/ghostScared1.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}else if(facing == 1){
						QPixmap sprite("../res/ghostScared1.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}
					spriteActive += 1;
				}else if(spriteActive < 140){
					if(facing == 0)
					{
						QPixmap sprite("../res/ghostScared2.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}else if(facing == 1){
						QPixmap sprite("../res/ghostScared2.png");
						painter->drawPixmap(y() + 1, x() + 1, 20, 20,sprite);
					}
					spriteActive += 1;
				}else{
					spriteActive = 0;
				}		
			
			}
			
			
		}

};
