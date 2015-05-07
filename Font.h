#pragma once
#include<string>
using namespace std;
/*struct TEXTUREDATA{
	void* pVoid;
	int size;
};*/

class Font
{
private:
	cDirect3D *dev;
	/*TEXTUREDATA *num[10]; 
	TEXTUREDATA *letter[26];
	TEXTUREDATA *punct[2];*/
	LPDIRECT3DTEXTURE9 *titleTex;
	LPDIRECT3DTEXTURE9 *numTex[10];
	LPDIRECT3DTEXTURE9 *letterTex[26];
	LPDIRECT3DTEXTURE9 *punctTex[2];
	//void loadFile(LPCSTR filename,TEXTUREDATA **cur);//this loads a texture file to memory to speed up performance...outdated and useless for now
	//symbol functions actually draw the symbols to the screen
	void symbol(double xPos,double yPos,double zPos, LPCSTR filename);//loads from file
	void symbol(double xPos,double yPos,double zPos, LPDIRECT3DTEXTURE9** cur);//loads from a prerendered texture
	//void symbol(double xPos,double yPos,double zPos, TEXTUREDATA* cur);//loads from main memory
	void symbol(double xPos,double yPos,double zPos, LPCSTR filename,double factor);//loads from file
	void symbol(double xPos,double yPos,double zPos, LPDIRECT3DTEXTURE9** cur,double factor);//loads from main memory
	void titleSymbol(double xPos,double yPos,double zPos, LPDIRECT3DTEXTURE9** cur);//loads title from a prerendered texture
public:
	Font(cDirect3D *d3ddev)
	{
		dev=d3ddev;
	}
	void loadTextures();//loads all textures into main memory
	void renderScore(int score);//shows the score
	void renderScore(int score,double x,double y);//shows the score and allows you to place it
	void renderLevel(int level);//shows the level number
	void renderIntermission(int level);//does the intermission level number
	void pressEnter(double x,double y);//says press enter to begin...
	void renderWord(string name,double x,double y);//displays a word
	void renderLetter(string letter,double x, double y);//displays a single letter at x, y
	void renderTitle();//renders the title

};