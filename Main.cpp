#define HEADER
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
//custom include files
#include "cDirect3D.h"
#include "Ship.h"
#include "Star.h"
#include "enemyShip.h"
#include "Font.h"
//openAL include files
//#include "al.h" 
//#include "alc.h"
//#include "alut.h"
//#include "xram.h"

using namespace std;

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")



// define the screen resolution and keyboard macros
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)//for Textures

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//game management class

bool enemyDirection=TRUE;//this tells which direction the enemy ships are going
int attackCounter=0;//a counter used to determine when enemy ships attack
int lives=3;//keeps track of the players lives
long score=0;//the score value
long scoreTrack=0;//to compare if score is bigger than 10000
int enemyNumbers=35;//keeps track of the number of enemies left
int level=1;//keeps track of what level the player is on 1-10
double attackPace=0;//keeps track of the speed at which enemies attack goes up by .25 per level
int attackChance1,attackChance2,attackChance3;//keeps track of the percent of enemies attacks
bool checkBoxes(float box1[],float box2[]);//checks for collisions
int randomNumber(int lowest, int highest);//creates a random number
string pName;//holds the players name

bool title=true;//show title screen
bool hiscore=false;//show high score screen?
bool game=true;//or play game?
bool newgame=false;

void freeLife();//gives a free life if score is greater than 10000
void setLevel();//sets up the level modifiers such as attack chance and attackPace
void setEnemies(cDirect3D* pDev,enemyShip myEnemyArray[]);
void runEnemies(ship* myShip,enemyShip myEnemyArray[]);
void moveEnemies(enemyShip myEnemyArray[]);
void attackEnemies(enemyShip myEnemyArray[]);
void newLife(ship* myShip,enemyShip myEnemyArray[]);
void starGen(cDirect3D* pDev, star myStar[]);//generates the random star positions
void starDraw(cDirect3D* pDev, star myStar[]);//draws the stars
void renderScore(Font* myFont,enemyShip hiScoreArray[]);//draws the high score screen
void initScore(cDirect3D* pDev,enemyShip hiScoreArray[]);//sets up the enemies for the high score screen
bool scoreCheck();//checks to see if there is a new high score
void scoreScreen(cDirect3D* pDev,star myStar[],Font* myFont);//handles high score updating after a game is over
void scoreUpdate();//updates the highscore file
void bubbleSort(int arr[], int n,string sarr[])//sorts the scores and names
{
      bool swapped = true;
      int j = 0;
	  string stmp;
      int tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] < arr[i+1]) {
                        tmp = arr[i];
						stmp=sarr[i];
                        arr[i] = arr[i + 1];
						sarr[i] = sarr[i + 1];
                        arr[i + 1] = tmp;
						sarr[i + 1] = stmp;
                        swapped = true;
                  }
            }
      }
}//bubblesort algorithm
struct CUSTOMVERTEX {FLOAT X, Y, Z; DWORD COLOR;};//define custom vertex structure
struct TEXTUREVERTEX{float X, Y, Z;float TU, TV;};//define texture vertex structure
#include "cPoly3D.h"//uses texturevertex.....must refine




cDirect3D dev(SCREEN_WIDTH,SCREEN_HEIGHT,CUSTOMFVF);


//function prototypes go here






// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;
	ShowCursor(FALSE);//do not show windows mouse cursor

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL, L"WindowClass", L"Galaxian 3D",
                          WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                          NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    dev.initD3D(hWnd);

    MSG msg;

	srand((unsigned)time(0)); //seeds the random numbers
	cDirect3D* pDev= &dev;//pointer to the cDirect3D class used for external file classes
	ship myShip(pDev);//players ship
	Font myFont(pDev);
	star myStar[40];

	myFont.loadTextures();//loads textures into memory
	enemyShip myEnemyArray[35];	//build an array to hold the enemy objects

	enemyShip hiScoreArray[14];//an array of enemy objects for the high score screen
	enemyShip enemyStart[2];//an array for enemy selectors
	enemyStart[0].initShip(pDev,55,-3,4);
	enemyStart[1].initShip(pDev,-65,-3,4);

	initScore(pDev,hiScoreArray);
	starGen(pDev,myStar);//part of high score or main screen
/*
	//This is the sound initialization point for now
	//float listenerPos[]={0.0,0.0,4.0};
	//float listenerVel[]={0.0,0.0,0.0};
	//float listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};

	//ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
	//ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

	//ALuint soundBuffer[1];
	//ALuint soundListener[1];
	//ALuint sountSource[1];

	//ALsizei size,freq;
	//ALenum  format;
	//ALvoid  *data;
	//ALboolean al_bool;

	//alListenerfv(AL_POSITION,listenerPos);
    //alListenerfv(AL_VELOCITY,listenerVel);
    //alListenerfv(AL_ORIENTATION,listenerOri);
	
	//alGetError();
	//alGenBuffers(1,soundBuffer);
	if(alGetError() != AL_NO_ERROR) 
	{
     MessageBox(hWnd,L"Error",L"Whatever",MB_OK);
    }
    else
    {
        MessageBox(hWnd,L"No Error",L"Whatever",MB_OK);	
    }

	alutLoadWAVFile("cymble.wav",&format,&data,&size,&freq,&al_bool);
    alBufferData(soundBuffer[0],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);*/
	
	//MessageBox(hWnd,L"Text here","Whatever",MB_OK);

	int counter=0;	//this variable is used to make sure screens aren't skipped
	while(true)//main game loop
	{
		newgame=true;
	    counter=0;	
		/*while(true)
		{
			dev.begin_frame();
				myFont.renderWord("SOUND CHECK",45,0);
			dev.end_frame();
			if(KEY_DOWN(0x0D))
				break;
		}*/
		while(title)
		{
			if(newgame)//makes sure game is selected at the beginning of title screen shown
			{
				enemyStart[0].initShip(pDev,55,-3,4);
				enemyStart[1].initShip(pDev,-65,-3,4);
				hiscore=false;
				game=true;
				newgame=false;
			}
			counter++;
			dev.begin_frame();
				myFont.renderTitle();
				myFont.renderWord("START GAME",45,0);
				myFont.renderWord("HIGH SCORES",50,-20);
				enemyStart[0].renderEnemyShip();
				enemyStart[1].renderEnemyShip();
				starDraw(pDev,myStar);
			dev.end_frame();
			if(KEY_DOWN(VK_DOWN))
			{
				enemyStart[0].initShip(pDev,60,-23,4);
				enemyStart[1].initShip(pDev,-70,-23,4);
				hiscore=true;
				game=false;
			}
			if(KEY_DOWN(VK_UP))
			{
				enemyStart[0].initShip(pDev,55,-3,4);
				enemyStart[1].initShip(pDev,-65,-3,4);
				hiscore=false;
				game=true;
			}
			if(KEY_DOWN(VK_ESCAPE)&&counter>10)
			{
				game=false;
				hiscore=false;
				PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
			if(KEY_DOWN(0x0D)&&counter>10)
				break;
		}
		
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(game==false&&hiscore==false)
			break;
		if(msg.message == WM_QUIT)//exit game
			break;

		counter=0;	
		while(hiscore)//hi score screen
		{
			counter++;
			dev.begin_frame();			
				//myFont.renderScore(2500,130,100);
				//myFont.renderWord("ALEX",-50,50);			
				renderScore(&myFont,hiScoreArray);
				myShip.renderScore(110,60);
				starDraw(pDev,myStar);
			dev.end_frame();
			if(KEY_DOWN(0x0D)&&counter>10)
			{
				game=false;
				title=true;
				break;
			}
			if(KEY_DOWN(VK_ESCAPE)&&counter>10)
			{
				game=false;
				title=true;
				break;
			}
		}



	lives=3;
	level=1;
	score=0;
	scoreTrack=0;
	while(game)//this is the actual game screen
	{
	setLevel();
	starGen(pDev,myStar);
	enemyNumbers=35;
	setEnemies(pDev,myEnemyArray);//set the area full of enemy objects
	//intermission screen
	counter=0;	
	while(game)
	{
		counter++;
		dev.begin_frame();	
			myShip.returnBullet();
			myFont.renderIntermission(level);
			myShip.showLives(lives);
			myFont.renderScore((int)score);
			myFont.pressEnter(0,-20);
			starDraw(pDev,myStar);
			myShip.renderShip();
			runEnemies(&myShip,myEnemyArray);
		dev.end_frame();
			if(KEY_DOWN(0x0D)&&counter>10)
				break;
			if(KEY_DOWN(VK_ESCAPE)&&counter>10)
			{
				break;
			}
	}

	//MessageBox (NULL, L"Initialized" , L"Hello", 0);
    while(lives>=0&&enemyNumbers>0)//main game loop changed to lives used to be 0
    {		
        dev.begin_frame();//do polygon rendering between these 2 functions		
			
			myShip.showLives(lives);
			starDraw(pDev,myStar);
			myFont.renderLevel(level);
			myFont.renderScore((int)score);
			myShip.renderShip();
			moveEnemies(myEnemyArray);
			runEnemies(&myShip,myEnemyArray);
			freeLife();
			if(myShip.explode!=true)
			{
				attackEnemies(myEnemyArray);
			}
			else
			{
				myFont.pressEnter(0,-20);
			}
		dev.end_frame();
			
		if(KEY_DOWN(VK_RIGHT))//movement originally 1.5
			myShip.shipMove(-2.0f);
		if(KEY_DOWN(VK_LEFT))
			myShip.shipMove(2.0f);
		if((KEY_UP(VK_RIGHT))&&(KEY_UP(VK_LEFT)))
		{
			myShip.shipMove(0.0f);
		}
		if(KEY_DOWN(VK_CONTROL))
			myShip.fire();
		if(KEY_DOWN(0x0D))//enter key
		{
			newLife(&myShip,myEnemyArray);
		}
		if(KEY_DOWN(VK_ESCAPE))
		{
			game=false;
			break;
		}
	}
	if(lives<0)
	{
		if(scoreCheck())
		{
			scoreScreen(pDev,myStar,&myFont);
			scoreUpdate();
			title=false;
			hiscore=true;
		}
		break;
	}
	if(level!=10)
		level=level+1;
	if(game==false)
	{
		break;
	}
	}

	}
	
     dev.cleanD3D();

    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}


bool checkBoxes(float box1[],float box2[])
{
	
	if(box1[0] > (box2[0]+box2[2])) return false; // box1 is too far right, no collision
	else if((box1[0]+box1[2]) < box2[0]) return false; // box1 is too far left, no collision
	else if(box1[1] > (box2[1]+box2[3])) return false; // box1 is too far down, no collision
	else if((box1[1]+box1[3]) < box2[1]) return false; // box1 is too far up, no collision
	else return true; // there is a collision
}

int randomNumber(int lowest, int highest) 
{ 
    int random_integer; 
    int range=(highest-lowest)+1; 
    random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
    return random_integer;
 } 

void setEnemies(cDirect3D* pDev,enemyShip myEnemyArray[])//sets up the rows for the enemies
{
	float xIncrement=34.3;
	float yIncrement=15.0;
	int Row=0;
	float rowModify=15.0;


	while(Row<3)//builds the first 3 rows ships 0-20
	{
		for(int i=0;i<7;i++)
		{
			myEnemyArray[i+(Row*7)].initShip(pDev,(i*xIncrement)-102.9,(Row*yIncrement)+rowModify,1);
		}
		Row+=1;
	}
	
	//builds 4th Row ships21-27
	for(int i=0;i<7;i++)
	{
		myEnemyArray[i+(Row*7)].initShip(pDev,(i*xIncrement)-102.9,(Row*yIncrement)+rowModify,2);
	}
	Row++;
	
	//builds 5th Row rows28-32
	for(int f=0;f<5;f++)
	{
		myEnemyArray[f+(Row*7)].initShip(pDev,(f*xIncrement)-68.6,(Row*yIncrement)+rowModify,3);
	}
	Row++;
	//last row
	myEnemyArray[33].initShip(pDev,-34.3,(Row*yIncrement)+rowModify,4);
	myEnemyArray[34].initShip(pDev, 34.3,(Row*yIncrement)+rowModify,4);
}

void runEnemies(ship* myShip,enemyShip myEnemyArray[])//checks for enemy collisions, handles collisions and draws existing enemies to the screen
{
			for(int i=0;i<35;i++)
			{
				if(myEnemyArray[i].exist)//check if enemy exists before checking it's boxes
				{
					myEnemyArray[i].renderEnemyShip();
					if(!myEnemyArray[i].explode&&myShip->bulletFired==true)//check if its exploded already otherwise no need to check bound boxes
						if(checkBoxes(myShip->returnBulletBox(),myEnemyArray[i].returnBoundBox()))
							{//if a collision is detected explode the enemy, return the bullet, and get rid of one enemy number
								myEnemyArray[i].enemyExplode();
								score=score+myEnemyArray[i].returnScore();
								myShip->returnBullet();
								enemyNumbers=enemyNumbers-1;
							}
					if(myEnemyArray[i].attack)//if it's attacking check for collision with player ship
					{
						if(!myShip->explode)//if the players ship has exploded don't check boxes
						{
							if(checkBoxes(myShip->returnShipBox(),myEnemyArray[i].returnBoundBox()))//player and enemy explode if true
							{
							myEnemyArray[i].enemyExplode();
							score=score+myEnemyArray[i].returnScore();
							myShip->explode=TRUE;
							enemyNumbers=enemyNumbers-1;
							}
							//if its attacking and either bullet is shot check for a collision
							if(myEnemyArray[i].bulletFlag1)
							{
								if(checkBoxes(myShip->returnShipBox(),myEnemyArray[i].returnBulletBox1()))//player and enemy explode if true
								{
									myEnemyArray[i].bulletFlag1=FALSE;
									myShip->explode=TRUE;
								}
							}
							if(myEnemyArray[i].bulletFlag2)
							{
								if(checkBoxes(myShip->returnShipBox(),myEnemyArray[i].returnBulletBox2()))//player and enemy explode if true
								{
									myEnemyArray[i].bulletFlag2=FALSE;
									myShip->explode=TRUE;
								}
							}
						}
					}

				}
			}
}

void moveEnemies(enemyShip myEnemyArray[])//moves enemies back and forth
{
	bool conLoop=TRUE;
	

	for(int a=0;a<35;a++)
	{

		if(myEnemyArray[a].exist)
		{
			if((myEnemyArray[a].getX()<=140) && (myEnemyArray[a].getX()>=-140))
			{
			}
			else
			{
				enemyDirection=!enemyDirection;
				conLoop=FALSE;
			}
		}
		if(!conLoop)
			break;
	}


	if(enemyDirection)
	{
		for(int i=0;i<35;i++)
		{
			if(myEnemyArray[i].exist)
			{
				myEnemyArray[i].enemyShipMove(-0.35);
			}
		}

	}
	else	
	{
		for(int i=0;i<35;i++)
		{
			if(myEnemyArray[i].exist)
			{
				myEnemyArray[i].enemyShipMove(0.35);
			}

		}
	}
}

void attackEnemies(enemyShip myEnemyArray[])//controls what enemies attack,when and how often
{
	int random,random2;//holds random numbers
	bool allset=false;//used to control loops
	double bullet1, bullet2;

	//the first thing this function does is to check if there are less than 5 enemies in which case
	//all enemies will attack over and over this is known as sudden death
	if(enemyNumbers>3)
	{	
	//1.check if it's time to attack
		if(attackCounter>=400)
		{		

		//2.if it's time to attack then generate a random number between 0 and 100
			random=randomNumber(0,100);
		//3.use the random number to determine what type of attack to initiate
	//4.types of attacks
	//		a)type 1 attack only 1 ship attacks
	//		randomly pick a ship that exists and make it attack
			if(random<attackChance1)
			{
				while(allset==false)
				{
					random=randomNumber(0,34);
					if(myEnemyArray[random].exist==true&&myEnemyArray[random].attack==false)
					{
						bullet1=(double)randomNumber(0,50);
						bullet2=(double)randomNumber(0,50);
						myEnemyArray[random].initAttack(bullet1,bullet2);
						allset=true;
					}
				}

			
			}
		//		b)type 2 attack 2 ships attack
		//		randomly pick 2 ships that exist to attack
			else if(random<attackChance1+attackChance2)
			{
				while(allset==false)
				{
					random=randomNumber(0,34);
					if(myEnemyArray[random].exist==true&&myEnemyArray[random].attack==false)
					{
						allset=true;
					}				
				}
				allset=false;
				while(allset==false)
				{
					random2=randomNumber(0,34);
					if(myEnemyArray[random2].exist==true&&myEnemyArray[random2].attack==false)
					{
						allset=true;
					}				
				}
				bullet1=(double)randomNumber(0,50);
				bullet2=(double)randomNumber(0,50);
				myEnemyArray[random].initAttack(bullet1,bullet2);
				bullet1=(double)randomNumber(0,50);
				bullet2=(double)randomNumber(0,50);
				myEnemyArray[random2].initAttack(bullet1,bullet2);
			}
	//		c)type 3 attack does 3 at a time
	//		randomly pick 1 yellow ship that exists and 2 blue ships that exist
			else
			{
					random=randomNumber(33,34);

					if(myEnemyArray[random].exist==true&&myEnemyArray[random].attack==false)
					{
						bullet1=(double)randomNumber(0,50);
						bullet2=(double)randomNumber(0,50);
						myEnemyArray[random].initAttack(bullet1,bullet2);
						allset=true;
					}
					allset=false;
					random2=randomNumber(28,32);
					while(allset==false)
					{
						random=randomNumber(28,32);
						if(random!=random2)
							allset=true;
					}

					if(myEnemyArray[random].exist==true&&myEnemyArray[random].attack==false)
					{
						bullet1=(double)randomNumber(0,50);
						bullet2=(double)randomNumber(0,50);
						myEnemyArray[random].initAttack(bullet1,bullet2);
						allset=true;
					}
					if(myEnemyArray[random2].exist==true&&myEnemyArray[random2].attack==false)
					{
						bullet1=(double)randomNumber(0,50);
						bullet2=(double)randomNumber(0,50);
						myEnemyArray[random2].initAttack(bullet1,bullet2);
						allset=true;
					}			
			}
	//5.if an attack just took place reset the counter
			attackCounter=0;
		}
	}
	else//sudden death
	{
		for(int w=0;w<35;w++)
		{
			if(myEnemyArray[w].exist==true&&myEnemyArray[w].attack==false)
			{
				bullet1=(double)randomNumber(0,50);
				bullet2=(double)randomNumber(0,50);
				myEnemyArray[w].initAttack(bullet1,bullet2);
			}
		}

	}
	//6.append a value to the attack counter
	attackCounter=attackCounter+1+attackPace;
}
void newLife(ship* myShip,enemyShip myEnemyArray[])//uses a new life and resets the allied ship
{
	bool enemyships=true;
	//1. iff the ship is dead
	if(myShip->exist==false)
	{
	//2. iff all enemy ships are at rest 

		for(int i=0;i<35;i++)
		{
			if(myEnemyArray[i].attack==true)
			{
				enemyships=false;
			}
		}
	//3. then reset the ship and subtract a life
		if(enemyships)
		{
			lives=lives-1;
			myShip->resetShip();
		}
	}
}

void setLevel()//contains the info for level difficulties
{
	switch(level)
	{
	case 1:attackPace=.25;
		attackChance1=70;
		attackChance2=25;
		attackChance3=5;
		break;
	case 2:attackPace=.5;
		attackChance1=65;
		attackChance2=30;
		attackChance3=5;
		break;
	case 3:attackPace=.75;
		attackChance1=60;
		attackChance2=30;
		attackChance3=10;
		break;
	case 4:attackPace=1.0;
		attackChance1=55;
		attackChance2=35;
		attackChance3=10;
		break;
	case 5:attackPace=1.25;
		attackChance1=50;
		attackChance2=35;
		attackChance3=15;
		break;
	case 6:attackPace=1.5;
		attackChance1=45;
		attackChance2=40;
		attackChance3=15;
		break;
	case 7:attackPace=1.75;
		attackChance1=40;
		attackChance2=45;
		attackChance3=15;
		break;
	case 8:attackPace=2.0;
		attackChance1=35;
		attackChance2=50;
		attackChance3=15;
		break;
	case 9:attackPace=2.25;
		attackChance1=30;
		attackChance2=55;
		attackChance3=15;
		break;
	case 10:attackPace=2.5;
		attackChance1=25;
		attackChance2=60;
		attackChance3=15;
		break;
	}

}
void starGen(cDirect3D* pDev,star myStar[])
{
	for(int i=0;i<0;i++)
	{
		myStar[i].initStar(pDev,randomNumber(-140,140),randomNumber(-100,100),1);
	}
		for(int i=0;i<15;i++)
	{
		myStar[i].initStar(pDev,randomNumber(-140,140),randomNumber(-100,100),2);
	}
	for(int i=15;i<40;i++)
	{
		myStar[i].initStar(pDev,randomNumber(-140,140),randomNumber(-100,100),3);
	}
}
void starDraw(cDirect3D* pDev, star myStar[])
{
	for(int i=0;i<40;i++)
	{
		myStar[i].starDraw();
	}
}

void freeLife()
{
	if(score-scoreTrack>=10000)
	{
		lives=lives+1;
		scoreTrack+=10000;
	}
}
void renderScore(Font* myFont,enemyShip hiScoreArray[])
{
	for(int e=0;e<14;e++)
	{
		hiScoreArray[e].renderEnemyShip();
	}
	string line;
	ifstream objectfile("scores.dat");
	myFont->renderWord("HIGH SCORES:",70,90);
	if (objectfile.is_open())//handles file reading
	{
		for(int x=0;x<2;x++)
		{
			for(int i=0;i<4;i++)
			{
				getline(objectfile,line);
				myFont->renderWord(line,100-(x*140),70-(i*50));
				getline(objectfile,line);
				myFont->renderScore(atoi(line.c_str()),180-(x*140),160-(i*50));
			}
		}
	objectfile.close();
	}
	
}
void initScore(cDirect3D* pDev,enemyShip hiScoreArray[])
{
	//2nd place
	hiScoreArray[0].initShip(pDev,110,10,4);
	hiScoreArray[1].initShip(pDev,20,10,4);
	//3rd place
	hiScoreArray[2].initShip(pDev,110,-40,3);
	hiScoreArray[3].initShip(pDev,20,-40,3);
	//4th place
	hiScoreArray[4].initShip(pDev,110,-90,2);
	hiScoreArray[5].initShip(pDev,20,-90,2);
	//5th
	hiScoreArray[6].initShip(pDev,-30,60,1);
	hiScoreArray[7].initShip(pDev,-120,60,1);
	//6th
	hiScoreArray[8].initShip(pDev,-30,10,1);
	hiScoreArray[9].initShip(pDev,-120,10,1);
	//7th
	hiScoreArray[10].initShip(pDev,-30,-40,1);
	hiScoreArray[11].initShip(pDev,-120,-40,1);
	//8th
	hiScoreArray[12].initShip(pDev,-30,-90,1);
	hiScoreArray[13].initShip(pDev,-120,-90,1);
}

void scoreUpdate()
{
	string line;
	string names[9];
	ifstream objectfile("scores.dat");
	int scores[9];
	for(int i=1;i<9;i++)
	{
		getline(objectfile,line);
		names[i]=line;
		getline(objectfile,line);
		scores[i]=atoi(line.c_str());
	}
	names[0]=pName;
	scores[0]=score;
	objectfile.close();

	bubbleSort(scores,9,names);

	ofstream file("scores.dat",ios::trunc);
		for(int i=0;i<8;i++)
		{
			file<<names[i]<<endl;
			file<<scores[i]<<endl;
		}
	file.close();
}
bool scoreCheck()
{
	string line;
	int test;
	ifstream objectfile("scores.dat");
	for(int i=0;i<8;i++)
	{
		getline(objectfile,line);
		getline(objectfile,line);
		test=(atoi(line.c_str()));
		
		if(score>(long)test)
		{
			objectfile.close();
			return true;
		}
	}
	objectfile.close();
	return false;
}//fucked up
void scoreScreen(cDirect3D* pDev,star myStar[],Font* myFont)//handles high score updating after a game is over
{
	string name="";
	int counter=0;
	while(true||counter<20)
	{
		counter++;
		pDev->begin_frame();
			myFont->renderWord("YOU EARNED A HIGH SCORE",120,80);
			myFont->renderWord("ENTER NAME:",120,0);
			myFont->renderWord(name,0,0);
			starDraw(pDev,myStar);
		pDev->end_frame();
	if(name.length()<7)
	{
		if(KEY_DOWN(0x41)&&counter>10)
		{
			name=name+"A";
			counter=0;
		}
		if(KEY_DOWN(0x42)&&counter>10)
		{
			name=name+"B";
			counter=0;
		}
		if(KEY_DOWN(0x43)&&counter>10)
		{
			name=name+"C";
		}
		if(KEY_DOWN(0x44)&&counter>10)
		{
			name=name+"D";
			counter=0;
		}
		if(KEY_DOWN(0x45)&&counter>10)
		{
			name=name+"E";
		counter=0;
		}
		if(KEY_DOWN(0x46)&&counter>10)
		{
			name=name+"F";
		counter=0;
		}
		if(KEY_DOWN(0x47)&&counter>10)
		{
			name=name+"G";
		counter=0;
		}
		if(KEY_DOWN(0x48)&&counter>10)
		{
			name=name+"H";
		counter=0;
		}
		if(KEY_DOWN(0x49)&&counter>10)
		{
			name=name+"I";
		counter=0;
		}
		if(KEY_DOWN(0x4A)&&counter>10)
		{
			name=name+"J";
		counter=0;
		}
		if(KEY_DOWN(0x4B)&&counter>10)
		{
			name=name+"K";
		counter=0;
		}
		if(KEY_DOWN(0x4C)&&counter>10)
		{
			name=name+"L";
		counter=0;
		}
		if(KEY_DOWN(0x4D)&&counter>10)
		{
			name=name+"M";
		counter=0;
		}
		if(KEY_DOWN(0x4E)&&counter>10)
		{
			name=name+"N";
		counter=0;
		}
		if(KEY_DOWN(0x4F)&&counter>10)
		{
			name=name+"O";
		counter=0;
		}
		if(KEY_DOWN(0x50)&&counter>10)
		{
			name=name+"P";
		counter=0;
		}
		if(KEY_DOWN(0x51)&&counter>10)
		{
			name=name+"Q";
		counter=0;
		}
		if(KEY_DOWN(0x52)&&counter>10)
		{
			name=name+"R";
		counter=0;
		}
		if(KEY_DOWN(0x53)&&counter>10)
		{
			name=name+"S";
		counter=0;
		}
		if(KEY_DOWN(0x54)&&counter>10)
		{
			name=name+"T";
		counter=0;
		}
		if(KEY_DOWN(0x55)&&counter>10)
		{
			name=name+"U";
		counter=0;
		}
		if(KEY_DOWN(0x56)&&counter>10)
		{
			name=name+"V";
		counter=0;
		}
		if(KEY_DOWN(0x57)&&counter>10)
		{
			name=name+"W";
		counter=0;
		}
		if(KEY_DOWN(0x58)&&counter>10)
		{
			name=name+"X";
		counter=0;
		}
		if(KEY_DOWN(0x59)&&counter>10)
		{
			name=name+"Y";
		counter=0;
		}
		if(KEY_DOWN(0x5A)&&counter>10)
		{
			name=name+"Z";
		counter=0;
		}
	}
		if(KEY_DOWN(VK_BACK)&&counter>10)
		{
			name=name.substr(0,name.length()-1);
			counter=0;
		}


		if(KEY_DOWN(0x0D)&&counter>10)
		{
			pName=name;
			break;
		}
		if(KEY_DOWN(VK_ESCAPE)&&counter>10)
		{
			pName=name;
			break;
		}
	}
	
}