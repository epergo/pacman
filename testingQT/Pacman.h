#include <string>

#include <QtGui>


using namespace std;


class Pacman
{
	private:
		int posX;
		int posY;

		int posXBoard;
		int posYBoard;

		string pacmanUp1;
		string pacmanUp2;
		string pacmanDown1;
		string pacmanDown2;
		string pacmanLeft1;
		string pacmanLeft2;
		string pacmanRight1;
		string pacmanRight2;

	public:
		int counterInv;		

		int velocity;

		int keyUp;
		int keyDown;
		int keyLeft;
		int keyRight;

		// towards which direction is pacman , 0 up,1 right, 2 down, 3 left
		int facing;
		// Every direction has 2 sprites
		int spriteActive; 

		Pacman()
		{
			counterInv = 0;

			velocity = 2;
	
			facing = 3;
			spriteActive = 0;

			posX = 262;
			posY = 62;

			pacmanUp1 = "../res/pacmanUp1.png";
			pacmanUp2 = "../res/pacmanUp2.png";
			pacmanDown1 = "../res/pacmanDown1.png";
			pacmanDown2 = "../res/pacmanDown2.png";
			pacmanLeft1 = "../res/pacmanLeft1.png";
			pacmanLeft2 = "../res/pacmanLeft2.png";
			pacmanRight1 = "../res/pacmanRight1.png";
			pacmanRight2 = "../res/pacmanRight2.png";

			spriteActive = 0;

			posXBoard = 13;
			posYBoard = 3;

			// 0 release, 1 pressed		
			keyUp = 0;
			keyDown = 0;
			keyLeft = 0;
			keyRight = 0;
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
			return posX + 14;
		}

		int y2() const
		{
			return posY + 14;
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

		void drawPacman(QPainter *painter)
		{
			if(spriteActive < 90 || (keyUp == 0 && keyDown == 0 && keyLeft == 0 && keyRight == 0))
			{
				if(facing == 0)
				{
					QPixmap sprite("../res/pacmanUp1.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);
				}else if(facing == 1){
					QPixmap sprite("../res/pacmanRight1.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);
				}else if(facing == 2){
					QPixmap sprite("../res/pacmanDown1.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);			
				}else if(facing == 3){
					QPixmap sprite("../res/pacmanLeft1.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);
				}
				spriteActive += 1;
			}else if(spriteActive < 140){
				if(facing == 0)
				{
					QPixmap sprite("../res/pacmanUp2.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);
				}else if(facing == 1){
					QPixmap sprite("../res/pacmanRight2.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);
				}else if(facing == 2){
					QPixmap sprite("../res/pacmanDown2.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);			
				}else if(facing == 3){
					QPixmap sprite("../res/pacmanLeft2.png");
					painter->drawPixmap(y() + 3, x() + 3, 14, 14, sprite);
				}
				spriteActive += 1;
			}else{
				spriteActive = 0;
			}		
			
		}

};
