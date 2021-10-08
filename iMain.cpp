/*
	CSE 1200: Software Development Lab: Gaming Project
	Project name: CAR MANIA
	Project members: 200104052, 200104060, 200104071

*/
#include "iGraphics.h"
#include <stdio.h>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;

boolean pause = false;
boolean music1 = true;

int menuPage, modePage, difficultyPage, instructionPage, creditPage, highscorePage, gameoverPage, loadingbg, nitro, step, coins;
int playButton, modeButton, difficultyButton, instructionButton, creditButton, highscoreButton, exitButton, greenButton, levelup, boom, extralife;
int cursorMX, cursorMY, clickMX, clickMY;

double speedMultiple = 1;
int gameState = 0;
int mode = 0;
int nos = 1;
int difficultyLevel = 0;
int counter = 0;
char keyAssign;

//level
int currentLevel = 1;
char currentLevelText[10];
void level()
{
	sprintf_s( currentLevelText, 10, "%d", currentLevel );
	iSetColor(255, 255, 255);
	iFilledRectangle(15,540, 100, 25);
	iShowImage(20, 540, 25, 25, step);
	iSetColor(0, 0, 0);
	//iText(20, 545, "Level:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(70, 545, currentLevelText, GLUT_BITMAP_TIMES_ROMAN_24);
	if(keyAssign != 'p')
	{
		counter++;
	}
	if(counter == 1000)
	{
		currentLevel += 1;
		iShowImage(300, 300, 300, 150, levelup);
		counter = 0;
		speedMultiple = speedMultiple+3;
	}
}

//life
boolean extraL = false;
int remainingLife = 5;
char remainingLifeText[10];
void life()
{
	sprintf_s( remainingLifeText, 10, "%d", remainingLife );
	iSetColor(255, 255, 255);
	iFilledRectangle(15,510, 100, 25);
	iSetColor(0, 0, 0);
	iShowImage(20, 510, 25, 25, extralife); 
	//iText(20, 515, "Life:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(70, 515, remainingLifeText, GLUT_BITMAP_TIMES_ROMAN_24);
	if(remainingLife == 2)
	{
		extraL = true;
	}
}

//extra life
int extraLifeXpos = 250+rand()%300;
int extraLifeYpos = 600;
void extraLife()
{
	extraLifeYpos -=10;
	if(extraLifeYpos == -50)
	{
		extraL == false;
		extraLifeXpos = 250+rand()%300;
		extraLifeYpos = 600;
	}
}

//boost up----Faysal
int boostUp= 5;
char boostUpText[10];
void boost()
{
	sprintf_s(boostUpText,10,"%d",boostUp);
	iSetColor(255, 255, 255);
	iFilledRectangle(15,480, 100, 25);
	iShowImage(20, 480, 25, 25, nitro);
	iSetColor(0, 0, 0);
	//iText(20, 485, "BoostUp: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(70, 485, boostUpText, GLUT_BITMAP_TIMES_ROMAN_24);
}

//highscore sort
vector < pair<int,string> > v;
string toString(int n)
{
	ostringstream ost;
	ost << n;
	ost.flush();
	return ost.str();
}

int toNumber(string s)
{
	stringstream numStr(s);
	int numInt;
	numStr>>numInt;
	return numInt;
}

//high score file	 --   (Hridi)
FILE *fp;
char name[20] = {}, point[10] = {};
int pointInt[10];

//high score name input
char nameStr[20] = {}, nameStr2[20] = {};
int nameLength = 0, nameMode = 0, thanks = 0;

//score
int myScore = 0, myScoreCopy;
char myScoreText[10];
void score()
{
	sprintf_s( myScoreText, 10, "%d", myScore );
	iSetColor(255, 255, 255);
	iFilledRectangle(15, 570, 100, 25);
	iShowImage(20, 570, 25, 25, coins);
	iSetColor(0, 0, 0);
	//iText(20, 575, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(70, 575, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	myScoreCopy = myScore;
}

//game playing background
int gamebg[2];
int gamebg1Ypos[2] = {0, 0};
int gamebg2Ypos[2] = {600, 600};
void gameBackground()
{
	gamebg1Ypos[mode] -= 5*nos;
	if(gamebg1Ypos[mode] <= -600)
	{
		gamebg1Ypos[mode] += 1200;
	}
	   
	gamebg2Ypos[mode] -= 5*nos;
	if(gamebg2Ypos[mode] <= -600)
	{
		gamebg2Ypos[mode] += 1200;
	}	
}

//player move
int player;
int playerXpos = 375;
int playerYpos = 30;
void playerMove()
{
	if(playerYpos > 30)
		playerYpos-= 2;
}

//traffic move-----(Hridi)
int directionChange[3] = {-1, 1, -1};
int traffic[3];
int trafficXpos[3] = {206, 526, 306};
int trafficYpos[3] = {  0, 400, 800};
void trafficMove()
{
	if(difficultyLevel == 0)
	{
		for(int i=0; i<3; i++)
		{
			trafficYpos[i] -= nos*10+speedMultiple;
			if(trafficYpos[i] <= -100)
			{
				trafficYpos[i] = 1200+trafficYpos[i];
				trafficXpos[i] = (rand()%350)+200;
			}
		}
	}
	if(difficultyLevel == 1)
	{
		for(int i=0; i<3; i++)
		{			
			trafficXpos[i] += 3*directionChange[i];
			if(trafficXpos[i] <= 200 || trafficXpos[i] >= 550)
			{
				directionChange[i] = (-1)*directionChange[i];
			}

			trafficYpos[i] -= nos*10+speedMultiple;
			if(trafficYpos[i] <= -100)
			{
				trafficYpos[i] = 1200+trafficYpos[i];
				trafficXpos[i] = (rand()%350)+200;
			}
		}
	}
}

//coin
int coin[4];
int coinXpos[4] = {226, 326, 426, 526};
int coinYpos[4] = {176, 376, 576, 776};
void coinMove()
{
	for(int i=0; i<4; i++)
	{
		coinYpos[i] -= 5*nos;
		if(coinYpos[i] <= -50)
		{
			coinYpos[i] = 1200+coinYpos[i];
		}
	}
}

//car-car collision, car-coin collision, car-extra life collision (Faysal)
void collision()
{
	for(int i=0; i<6; i++)//car-car collision
	{
		if(playerXpos+45 >= trafficXpos[i] && playerXpos <= trafficXpos[i]+45 && playerYpos+95 >= trafficYpos[i] && playerYpos <= trafficYpos[i]+95)
		{
			iShowImage(trafficXpos[i]-50,trafficYpos[i], 100, 100, boom);
			trafficYpos[i] = 1200 + trafficYpos[i];
			if(gameState == 1)
			{
				remainingLife--;
			}
			else if(gameState == 10)
			{
				myScore += 30;
			}
		}
	}
	for(int i=0; i<4; i++)//car-coin collision
	{
		if(playerXpos+45 >= coinXpos[i] && playerXpos <= coinXpos[i]+45 && playerYpos+95 >= coinYpos[i] && playerYpos <= coinYpos[i]+45)
		{
			coinYpos[i] = 1200 + coinYpos[i];
			if(i==0 || i==3)//gold coin
				myScore += 20;
			else//silver coin
				myScore +=10;
		}
	}
	if(playerXpos+45>=extraLifeXpos && playerXpos<=extraLifeXpos+45 && playerYpos+95 >= extraLifeYpos && playerYpos <= extraLifeYpos+45 && extraL ==true)
	{
		remainingLife++;
		extraLifeXpos = 250+rand()%300;
		extraLifeYpos = 600;
		extraL = false;
	}
}

//images
void imageLoad()
{
	menuPage = iLoadImage("images\\menuPage.jpg");
	loadingbg = iLoadImage("images\\loadingbg.jpg");
	modePage = iLoadImage("images\\modePage.jpg");
	difficultyPage =  iLoadImage("images\\difficultyPage.jpg");
	instructionPage = iLoadImage("images\\instructionPage.jpg");
	creditPage = iLoadImage("images\\creditPage.jpg");
	highscorePage =  iLoadImage("images\\highscorePage.jpg");
	gameoverPage =  iLoadImage("images\\gameoverPage.jpg");

	playButton =  iLoadImage("images\\playButton.png");
	modeButton =  iLoadImage("images\\modeButton.png");
	difficultyButton = iLoadImage("images\\difficultyButton.png");
	instructionButton = iLoadImage("images\\instructionButton.png");
	creditButton =  iLoadImage("images\\creditButton.png");
	highscoreButton =  iLoadImage("images\\highscoreButton.png");
	exitButton =  iLoadImage("images\\exitButton.png");
	greenButton =  iLoadImage("images\\greenButton.png");
	levelup =  iLoadImage("images\\levelup.png");
	extralife = iLoadImage("images\\extralife.png");
	nitro = iLoadImage("images\\nitro.png");
	step = iLoadImage("images\\step.png");
	coins = iLoadImage("images\\coins.png");

	player = iLoadImage("images\\player.png");
	gamebg[0] = iLoadImage("images\\gamebgday.jpg");
	gamebg[1] = iLoadImage("images\\gamebgnight.jpg");
	traffic[0]= iLoadImage("images\\traffic1.png");
	traffic[1]= iLoadImage("images\\traffic2.png");
	traffic[2]= iLoadImage("images\\traffic3.png");

	coin[0]= iLoadImage("images\\coin2.png");//gold
	coin[1]= iLoadImage("images\\coin1.png");//silver
	coin[2]= iLoadImage("images\\coin1.png");//silver
	coin[3]= iLoadImage("images\\coin2.png");//gold

	boom = iLoadImage("images\\boom.png");
}

//loading screen
int checkLoading = 1;
long long loadDot = 0;
int loadLine = 0;
int countNOS=0;
void loadingScreen()
{
	iShowImage(0,0,800,600,loadingbg);
	loadDot++;
	loadLine++;

	iSetColor(0, 0, 0);
	iText(320,125,"Loading",GLUT_BITMAP_TIMES_ROMAN_24);
	if(loadDot<50)
	{
	}
	else if(loadDot<10*10)
	{
		iFilledRectangle(420,125,5,5);
	}
	else if(loadDot<15*10)
	{
		iFilledRectangle(420,125,5,5);
		iFilledRectangle(430,125,5,5);
	}
	else if(loadDot<20*10)
	{
		iFilledRectangle(420,125,5,5);
		iFilledRectangle(430,125,5,5);
		iFilledRectangle(440,125,5,5);
		if(loadDot==19*10)
		{
			loadDot=0;
		}
	}
	iRectangle(200,100,400,10);
	iFilledRectangle(201, 102, loadLine,7);
	iSetColor(255, 0, 0);
	iText(540,450,"Press 'p' for pause",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(540,400,"Press 'r' for resume",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(540,350,"Press 'q' for quit",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(540,300,"Press 'SPACE' for nitros",GLUT_BITMAP_TIMES_ROMAN_24);
}

//reset all
void resetAll()
{
	counter = 0;
	myScore = 0;
	nos = 1;
	music1 = true;
	boostUp = 5;
	speedMultiple = 1;
	checkLoading = 1;
	currentLevel = 1;
	remainingLife = 5;
	gamebg1Ypos[mode] = 0;
	gamebg2Ypos[mode] = 600;
	playerXpos = 375;
	playerYpos = 50;

	trafficXpos[0] = 206;
	trafficXpos[1] = 526;
	trafficXpos[2] = 306;

	trafficYpos[0] = 0;
	trafficYpos[1] = 400;
	trafficYpos[2] = 800;

	coinXpos[0] = 226;
	coinXpos[1] = 326;
	coinXpos[2] = 426;
	coinXpos[3] = 526;

	coinYpos[0] = 176;
	coinYpos[1] = 376;
	coinYpos[2] = 576;
	coinYpos[3] = 776;

	extraLifeXpos = 250+rand()%300;
	extraLifeYpos = 600;
	extraL = false;

	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);
	iResumeTimer(3);
	iResumeTimer(4);
}

//iDraw
void iDraw()
{
	iClear();
	if(gameState == 0)//menu page
	{
		resetAll();
		iShowImage(0, 0, 800, 600, menuPage);

		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 340 && cursorMY <= 380)
			iShowImage(50, 340, 200, 40, playButton);
		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 290 && cursorMY <= 330)
			iShowImage(50, 290, 200, 40, modeButton);
		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 240 && cursorMY <= 280)
			iShowImage(50, 240, 200, 40, difficultyButton);
		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 190 && cursorMY <= 230)
			iShowImage(50, 190, 200, 40, instructionButton);
		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 140 && cursorMY <= 180)
			iShowImage(50, 140, 200, 40, highscoreButton);
		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 90 && cursorMY <= 130)
			iShowImage(50, 90, 200, 40, creditButton);
		if(cursorMX >= 50 && cursorMX <= 250 && cursorMY >= 40 && cursorMY <= 80)
			iShowImage(50, 40, 200, 40, exitButton);
	}
	if(gameState == 1)//play page
	{
		if(checkLoading==1)
		{
			loadingScreen();
			if(loadLine == 400)
			{	
				loadLine=0;
				loadDot=0;
				checkLoading=0;
			}
		}
		else if(checkLoading==0)
		{
			if(music1 == true)
			{
				PlaySound("music\\musicone.wav", NULL, SND_ASYNC);
				music1=false;
			}

			iShowImage(0, gamebg1Ypos[mode], 800, 600, gamebg[mode]);
			iShowImage(0, gamebg2Ypos[mode], 800, 600, gamebg[mode]);
			iShowImage(playerXpos, playerYpos, 50, 100, player);

			//coin
			for(int i=0; i<4; i++)
				iShowImage(coinXpos[i], coinYpos[i], 50, 50, coin[i]);
			//traffic
			for(int i=0; i<3; i++)
				iShowImage(trafficXpos[i], trafficYpos[i], 50, 100, traffic[i]);
			//extra life
			if(extraL == true)
			{
					iShowImage(extraLifeXpos, extraLifeYpos, 50, 50, extralife);
			}
			
			collision();
			score();
			life();
			level();
			boost();
			if(remainingLife <= 0)
			{
				gameState = 6;//gameover page
			}
		}
	}
	if(gameState==10 && countNOS<=100 )
	{
		countNOS++;
		nos=3;
		iShowImage(0, gamebg1Ypos[mode], 800, 600, gamebg[mode]);
		iShowImage(0, gamebg2Ypos[mode], 800, 600, gamebg[mode]);
		iShowImage(playerXpos, playerYpos, 50, 100, player);

		//coin
		for(int i=0; i<4; i++)
			iShowImage(coinXpos[i], coinYpos[i], 50, 50, coin[i]);
		//traffic
		for(int i=0; i<3; i++)
			iShowImage(trafficXpos[i], trafficYpos[i], 50, 100, traffic[i]);
		//extra life
		if(extraL == true)
		{
				iShowImage(extraLifeXpos, extraLifeYpos, 50, 50, extralife);
		}

		collision();
		score();
		life();
		level();
		boost();
		if(countNOS>50)
		{
			gameState = 1;
			nos = 1;
		}
	}
	if(gameState == 2)//difficulty page
	{
		iShowImage(0, 0, 800, 600, difficultyPage);
		
		if(difficultyLevel == 0)
		{
			iShowImage(500, 350, 50, 50, greenButton);//level easy
		}
		if(difficultyLevel == 1)
		{
			iShowImage(500, 200, 50, 50, greenButton);//lavel hard
		}
	}
	if(gameState == 3)//instruction page
	{
		iShowImage(0, 0, 800, 600, instructionPage);
	}
	if(gameState == 4)//highscore page
	{
		iShowImage(0, 0, 800, 600, highscorePage);
		iSetColor(0, 0, 0);

		fp= fopen("Highscore file.txt","r");

		while(fscanf(fp, "%s\t%s", point, name)!=EOF)
		{
			int pointInt=toNumber(point);
			v.push_back(make_pair(pointInt,name));
		}
		sort(v.begin(),v.end());
		reverse(v.begin(),v.end());
		fclose(fp);
		int k;
		if(v.size()<5) k=v.size();
		else k=5;
		int nameposition=400;	
		for(int i=0;i<5;i++)
		{
			std::string s1=v[i].second;
			std::string s2=toString(v[i].first);
			char nameCopy[20];
			char pointCopy[10];
			strcpy(nameCopy,s1.c_str());
			strcpy(pointCopy,s2.c_str());
			iText(200, nameposition, nameCopy, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(500, nameposition, pointCopy, GLUT_BITMAP_TIMES_ROMAN_24);
			nameposition-=40;
		}
		v.clear();
	}
	if(gameState == 5)//credit page
	{
		iShowImage(0, 0, 800, 600, creditPage);
	}
	if(gameState == 6)//game over page
	{
		iShowImage(0, 0, 800, 600, gameoverPage);
		iSetColor(255, 255, 255);
		iFilledRectangle(300, 400, 200, 40);
		iFilledCircle(400, 280, 100, 1000);
		iSetColor(150, 150, 150);
		iText(310, 410, "Enter your name...", GLUT_BITMAP_TIMES_ROMAN_24);

		if(nameMode == 1)
		{
			iSetColor(255, 255, 255);
			iFilledRectangle(300, 400, 200, 40);
			iSetColor(0, 0, 0);
			iText(310, 410, nameStr, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if(thanks == 1)
		{
			iShowImage(300, 400, 200, 40, greenButton);
			iSetColor(0, 0, 0);
			iText(330, 410, "THANK YOU", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(0, 0, 0);
		iText(350, 300, "Your Score", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(390, 250, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if(gameState == 7)//mode page ----(Hridi)
	{
		iShowImage(0, 0, 800, 600, modePage);
		iShowImage(50, 200, 300, 200, gamebg[0]);
		iShowImage(450, 200, 300, 200, gamebg[1]);
		if(mode == 0)
		{
			iShowImage(50, 125, 50, 50, greenButton);//day mode
		}
		if(mode == 1)
		{
			iShowImage(450, 125, 50, 50, greenButton);//night mode
		}
	}	
}

void iPassiveMouse(int mx, int my)
{
	cursorMX = mx;
	cursorMY = my;
}

/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{

}

/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouse(int button, int state, int mx, int my)
{
	clickMX = mx;
	clickMY = my;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(gameState == 0)
		{
			if(mx >= 50 && mx <= 250 && my >= 340 && my <= 380)
				gameState = 1;//play
			if(mx >= 50 && mx <= 250 && my >= 290 && my <= 330)
			{
				PlaySound("music\\click.wav", NULL, SND_ASYNC);
				gameState = 7;//mode
			}
			if(mx >= 50 && mx <= 250 && my >= 240 && my <= 280)
			{
				PlaySound("music\\click.wav", NULL, SND_ASYNC);
				gameState = 2;//difficulty
			}
			if(mx >= 50 && mx <= 250 && my >= 190 && my <= 230)
			{
				PlaySound("music\\click.wav", NULL, SND_ASYNC);
				gameState = 3;//instruction
			}
			if(mx >= 50 && mx <= 250 && my >= 140 && my <= 180)
			{
				PlaySound("music\\click.wav", NULL, SND_ASYNC);
				gameState = 4;//highscore
			}
			if(mx >= 50 && mx <= 250 && my >= 90 && my <= 130)
			{
				PlaySound("music\\click.wav", NULL, SND_ASYNC);
				gameState = 5;//credit
			}
			if(mx >= 50 && mx <= 250 && my >= 40 && my <= 80)
				exit(0);//exit
		}
		if(gameState !=0 && gameState !=1 && mx >= 20 && mx <= 70 && my >= 20 && my <= 70)//back button
		{
			PlaySound("music\\click.wav", NULL, SND_ASYNC);
			gameState = 0;//menu page
			thanks = 0;
		}
		if(gameState == 2 && mx >= 500 && mx <= 550 && my >= 350 && my <= 400)
		{
			PlaySound("music\\click.wav", NULL, SND_ASYNC);
			difficultyLevel = 0;//difficulty easy
		}
		if(gameState == 2 && mx >= 500 && mx <= 550 && my >= 200 && my <= 250)
		{
			PlaySound("music\\click.wav", NULL, SND_ASYNC);
			difficultyLevel = 1;//difficulty hard
		}
		if(gameState == 7 && mx >= 50 && mx <= 100 && my >= 125 && my <= 175)
		{
			PlaySound("music\\click.wav", NULL, SND_ASYNC);
			mode = 0;//day mode
		}
		if(gameState == 7 && mx >= 450 && mx <= 500 && my >= 125 && my <= 175)
		{
			PlaySound("music\\click.wav", NULL, SND_ASYNC);
			mode = 1;//night mode
		}
		if(gameState == 6 && mx >= 300 && mx <= 500 && my >= 400 && my <= 440 && nameMode == 0)
		{
			nameMode = 1;//name input on
		}
	}
}

/*
 function iKeyboard() is called whenever the user hits a key in keyboard.
 key- holds the ASCII value of the key pressed.
 */
void iKeyboard(unsigned char key)
{
	if (key == 'p' && gameState == 1)//pause
	{
		PlaySound("music\\click.wav", NULL, SND_ASYNC);
		pause = true;
		iPauseTimer(0);
		iPauseTimer(1);
		iPauseTimer(2);
		iPauseTimer(3);
		iPauseTimer(4);
	}
	if (key == 'r' && gameState == 1)//resume
	{
		music1 = true;
		pause = false;
		iResumeTimer(0);
		iResumeTimer(1);
		iResumeTimer(2);
		iResumeTimer(3);
		iResumeTimer(4);
	}
	if (key == ' ' && (gameState == 1 || gameState==10) && boostUp >=1)//nos
	{
		countNOS=0;
		gameState=10;
		--boostUp;
	}
	if (key == 'q' && gameState == 1)//play screen quit
	{
		PlaySound("music\\click.wav", NULL, SND_ASYNC);
		gameState = 0;
	}
	if(nameMode == 1)
	{
		if( key == '\r' && gameState == 6)
		{
			//file
			fp = fopen("Highscore file.txt","a");
			fprintf(fp,"%s\t%s\n", myScoreText, nameStr);
			fclose(fp);
			
			for(int i=0; i<nameLength; i++)
			{
				nameStr[i] = 0;
			}
			nameLength = 0;
			nameMode = 0;
			thanks = 1;
		}
		else if( key=='\b' && gameState==6)
		{
			nameLength--;
			nameStr[nameLength] = key;
			if( nameLength < 0) 
			{
				nameLength = 0;
			}
			
		}
		else
		{
			nameStr[nameLength] = key;
			nameLength++;
		}
	}
	keyAssign = key;
}

/*
 function iSpecialKeyboard() is called whenver user hits special keys like-
 function keys, home, end, pg up, pg down, arraows etc. you have to use
 appropriate constants to detect them. A list is:
 GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
 GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
 GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
 GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
 */
void iSpecialKeyboard(unsigned char key)
{
	if(pause == false)
	{
		if (key == GLUT_KEY_RIGHT && playerXpos < 540 && (gameState == 1 || gameState == 10))
		{
			playerXpos += 20;
		}
		if (key == GLUT_KEY_LEFT && playerXpos > 210 && (gameState == 1 || gameState == 10))
		{
			playerXpos -= 20;
		}
		if (key == GLUT_KEY_UP && playerYpos <= 480 && (gameState == 1 || gameState == 10))
		{
			playerYpos += 8;
		}
		if (key == GLUT_KEY_DOWN && playerYpos >= 20 && (gameState == 1 || gameState == 10))
		{
			playerYpos -= 8;
		}
	}
}

int main()
{	
	iSetTimer(0, playerMove);
	iSetTimer(50, trafficMove);
	iSetTimer(15, coinMove);
	iSetTimer(25, gameBackground);
	iSetTimer(20, extraLife);
	
	iInitialize(800, 600, "CAR MANIA");
	
	imageLoad();

	iStart();

	return 0;
}
