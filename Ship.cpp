#ifndef HEADER
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include "cDirect3D.h"
#include "Ship.h"
struct CUSTOMVERTEX {FLOAT X, Y, Z; DWORD COLOR;};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif

ship::ship(cDirect3D* d3ddev)
{
		dev=d3ddev;//pointer to direct3D device

		xPosition=0.0f;//these are used to modify the ships position
		yPosition=-90.0f;
		zPosition=0.0f;
		pivot=0.0f;

		exist=TRUE;
		explode=FALSE;
		increment=0.0;
		explodeRotate=0.0;

		bulletFired=FALSE;//this variable is used to tell whether the bullet is being fired
		bulletDistance=yPosition;//this is the bullets current distance away from it's rest position
		bulletMaxDistance=100.0f;//this is the end of the screen if the bullet hits here it resets
		bulletSpeed=2.0f;

		shipAngle=0;//used to control gyrations in high score screen
		shipAngleDirection=TRUE;
}


void ship::resetShip()//resets the ship after death
{
		xPosition=0.0f;
		bulletFired=FALSE;
		exist=TRUE;
		explode=FALSE;
		increment=0.0;
		explodeRotate=0.0;
		pivot=0;
		bulletDistance=yPosition;
}
void ship::renderShip(void)//renders all the ships parts and controls where they go
{
	D3DXMATRIX shipMove;//moves entire ship
	D3DXMATRIX shipPivot;
	D3DXMATRIX shipResize;
	D3DXMatrixTranslation(&shipMove,xPosition,yPosition,0.0f);
	D3DXMatrixRotationY(&shipPivot,D3DXToRadian(pivot));
	D3DXMatrixScaling(&shipResize,1.35,1.35,1.35);//had to resize the ship

	shipMove=shipResize*shipMove;//easier this way
	//explosion matrices
	D3DXMATRIX matDMain;
	D3DXMATRIX matDRightWing;
	D3DXMATRIX matDLeftWing;
	D3DXMATRIX matRotateY; 
	D3DXMatrixTranslation(&matDMain, 0, 0, 0);//default these
	D3DXMatrixTranslation(&matDRightWing, 0, 0, 0);
	D3DXMatrixTranslation(&matDLeftWing, 0, 0, 0);
	D3DXMatrixRotationX(&matRotateY, explodeRotate);

	if(explode)//explode animation
	{
		if(increment<=60)
		{
			D3DXMatrixTranslation(&matDMain, 0, increment, increment);
			D3DXMatrixTranslation(&matDRightWing, increment, increment*.5, 0);
			D3DXMatrixTranslation(&matDLeftWing, -increment, increment*.5, 0);
		}
		else
		{
			exist=FALSE;
		}
		explodeRotate+=0.1;
		increment+=1.0;
		//matDMain=matDMain*matExplodeRotation;
		//matDRightWing=matDRightWing*matExplodeRotation;
		//matDLeftWing=matDLeftWing*matExplodeRotation;
	}
	
	if(exist==true)
	{
		ShipGraphic();
		// set the world transform
		D3DXMATRIX matTranslate;    // a matrix to store the translation information
		D3DXMatrixTranslation(&matTranslate, -0.5f, 2.0f, 0.5f);
		static float index = 0.0f; index+=0.00f; // an ever-increasing float value
		   // a matrix to store the rotation for each triangle
		  // the rotation matrix
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslate*matRotateY*shipPivot*shipMove*matDMain));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 28);
		dev->cleanBuffers();


		Engine();
		// set the world transform
		D3DXMATRIX matTranslateEngine1;    // a matrix to store the translation information
		D3DXMatrixTranslation(&matTranslateEngine1, -3.0f, -3.5f, 1.0f);
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateEngine1*matRotateY*shipPivot*shipMove*matDLeftWing));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();

	
		Engine();
		// set the world transform
		D3DXMATRIX matTranslateEngine2;    // a matrix to store the translation information
		D3DXMATRIX matEngineFlip;
		D3DXMatrixRotationY(&matEngineFlip, D3DXToRadian(180.0f));
		D3DXMatrixTranslation(&matTranslateEngine2, 3.0f, -3.5f, -1.0f);
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matEngineFlip*matTranslateEngine2*matRotateY*shipPivot*shipMove*matDRightWing));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();
	

		Bullet();

		D3DXMATRIX matTranslateBullet;//matrix for translation
		D3DXMATRIX matBulletSpin;	//matrix for the bullets spin
		D3DXMATRIX matBulletFired;
		static float index2 = 0.0f; index2+=0.06f; // an ever-increasing float value
	
		D3DXMatrixTranslation(&matTranslateBullet, -0.5f, 4.0f, 0.5f);
		D3DXMatrixRotationY(&matBulletSpin, index2 );
		// tell Direct3D about our matrix		
		if(bulletFired==TRUE)//handles drawing the bullet whether fired or not
		{	
			D3DXMatrixTranslation(&matBulletFired, xBulletPosition, bulletDistance, 0.0f);
			dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateBullet*matBulletSpin*shipResize*matBulletFired));
			handleBulletMove();
		}
		else
		{
			dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateBullet*matBulletSpin*matRotateY*shipMove*matDMain));
		
		}
		dev->d3ddev->SetIndices(dev->i_buffer);
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));

		// draw the Bullet
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 9, 0, 14);
		dev->cleanBuffers();
	}
	return;
}


// this is the function that puts the 3D models into video RAM
void ship::Bullet(void)
{
    // create the vertices using the CUSTOMVERTEX
    struct CUSTOMVERTEX vertices[] =
    {
        //Bottom Square
        { 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 100), },//0
        { 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 100), },
        { 0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 255, 100), },
        { 1.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(255, 255, 100), },

        //Top Square
        { 0.0f, 0.5f, 0.0f, D3DCOLOR_XRGB(255, 255, 200), },//4
        { 1.0f, 0.5f, 0.0f, D3DCOLOR_XRGB(255, 255, 200), },
        { 0.0f, 0.5f, -1.0f, D3DCOLOR_XRGB(255, 255, 200), },
		{ 1.0f, 0.5f, -1.0f, D3DCOLOR_XRGB(255, 255, 200), },

		//Tip
        { 0.5f, 2.0f, -0.5f, D3DCOLOR_XRGB(50, 100, 50), },//8
    };

    // create a vertex buffer interface called dev->v_buffer
    dev->d3ddev->CreateVertexBuffer(9*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock dev->v_buffer and load the vertices into it
    dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    dev->v_buffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,//bottom   
        2, 1, 3,
        0, 1, 4,//front
        4, 5, 1,
        0, 4, 2,//left  
        4, 6, 2,
		1, 3, 5,//right
		5, 7, 3,
		2, 3, 6,//top
		6 ,7, 3,
		4, 8, 5,//pyramid
		4, 6, 8,
		7, 8, 6,
		7, 8, 5,
    };

    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(14*3*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock dev->i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    dev->i_buffer->Unlock(); 
}

void ship::ShipGraphic(void)
{
    // create the vertices using the CUSTOMVERTEX
    struct CUSTOMVERTEX vertices[] =
    {
        //Bullet Square
        { 0.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(200, 100, 0), },//0
        { 1.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(200, 100, 0), },
        { 0.0f, 2.0f, -1.0f, D3DCOLOR_XRGB(200, 100, 0), },
		{ 1.0f, 2.0f, -1.0f, D3DCOLOR_XRGB(200, 100, 0), },

		        //Middle Square
        { -0.5f, 0.0f, 0.5f, D3DCOLOR_XRGB(100, 50, 50), },//4
        { 1.5f, 0.0f,  0.5f, D3DCOLOR_XRGB(100, 50, 50), },
        { -0.5f, 0.0f, -1.5f, D3DCOLOR_XRGB(100, 50, 50), },
        { 1.5f, 0.0f, - 1.5f, D3DCOLOR_XRGB(100, 50, 50), },
		
		//Left Top
        { -1.5f, 0.0f, 0.5f, D3DCOLOR_XRGB(100, 50, 50), },//8
		{ -1.5f, 0.0f, -1.5f, D3DCOLOR_XRGB(100, 50, 50), },
		//Right Top
		{ 2.5f, 0.0f,  0.5f, D3DCOLOR_XRGB(100, 50, 50), },//10
		{ 2.5f, 0.0f,  -1.5f, D3DCOLOR_XRGB(100, 50, 50), },

		//bottom Square
		{ -0.5f, -7.0f, 0.5f, D3DCOLOR_XRGB(220, 110, 0), },//12
        { 1.5f, -7.0f,  0.5f, D3DCOLOR_XRGB(220, 110, 0), },
        { -0.5f, -7.0f, -1.5f, D3DCOLOR_XRGB(220, 110, 0), },
        { 1.5f, -7.0f, - 1.5f, D3DCOLOR_XRGB(220, 110, 0), },
    };

    // create a vertex buffer interface called dev->v_buffer
    dev->d3ddev->CreateVertexBuffer(16*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock dev->v_buffer and load the vertices into it
    dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    dev->v_buffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
		//top area 18 primitives
        0, 1, 2,//top
		1, 2, 3,
		8, 9, 2,//top left
		2, 0, 8,
		10,11,3,//top right
		3, 1,10,
		4, 0, 1,//top front
		1, 5, 4,
		6, 2, 3,//top back
		3, 7, 6,
		8, 0, 4,//fill in triangles left
		9, 6, 2,
		5,10, 1,//fill in triangles right
		7,11, 3,
		8, 4, 6,//bottom left
		6, 9, 8,
		5,10,11,//bottom right
		11,7, 5,
		//Bottom Stick(fuselage) 10 primitives
		12, 13, 14,//very bottom
		14, 15, 13,
		12, 14,  6,//left side
		6,   4, 12,
		12, 13,  5,//front side
		5,   4, 12,
		13, 15,  7,//right side
		7,   5, 13,
		14, 15,  6,//back side
		6,   7, 15,
   
    };

    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(28*3*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock dev->i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    dev->i_buffer->Unlock(); 
}

void ship::Engine(void)
{
    // create the vertices using the CUSTOMVERTEX
    struct CUSTOMVERTEX vertices[] =
    {
        //Small Square Top
        { 0.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(120, 60, 50), },//0
        { 2.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(120, 60, 50), },
        { 0.0f, 2.0f, -2.0f, D3DCOLOR_XRGB(120, 60, 50), },
        { 2.0f, 2.0f, -2.0f, D3DCOLOR_XRGB(120, 60, 50), },

        //Small Square Bottom
        { 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(200, 100, 0), },//4
        { 2.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(200, 100, 0), },
        { 0.0f, 0.0f, -2.0f, D3DCOLOR_XRGB(200, 100, 0), },
		{ 2.0f, 0.0f, -2.0f, D3DCOLOR_XRGB(200, 100, 0), },

		//Long Square Top
        { -2.0f, 4.0f, 0.0f, D3DCOLOR_XRGB(100, 50, 50), },//8
        { 0.0f, 4.0f, 0.0f, D3DCOLOR_XRGB(100, 50, 50), },
        { -2.0f, 4.0f, -2.0f, D3DCOLOR_XRGB(100, 50, 50), },
        { 0.0f, 4.0f, -2.0f, D3DCOLOR_XRGB(100, 50, 50), },

        //Long Square Bottom
        { -2.0f, -6.0f, 0.0f, D3DCOLOR_XRGB(255, 150, 0), },//12
        { 0.0f, -6.0f, 0.0f, D3DCOLOR_XRGB(255, 150, 0), },
        { -2.0f, -6.0f, -2.0f, D3DCOLOR_XRGB(255, 150, 0), },
		{ 0.0f, -6.0f, -2.0f, D3DCOLOR_XRGB(255, 150, 0), },
		
    };

    // create a vertex buffer interface called dev->v_buffer
    dev->d3ddev->CreateVertexBuffer(16*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock dev->v_buffer and load the vertices into it
    dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    dev->v_buffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
		//small
        0, 1, 2,//top 
		2, 3, 1,
		4, 5, 6,//bottom 
		6, 7, 5,
		0, 4, 5,//front 
		5, 1, 0,
		5, 7, 1,//right 
		1, 3, 7,
		6, 2, 7,//back 
		7, 3, 2,
		//large
		8, 9, 10,//top
		10, 11, 9,
		12, 13, 14,//bottom
		14, 15, 13,
		12, 13, 8,//front
		8, 9, 13,
		12, 14, 8,//left side
		8, 10, 14,
		14, 15, 10,//back
		10, 11, 15,
		9, 11, 0,//right side top
		0, 2, 11,
		4, 6, 15,//right side bottom
		15, 13, 4,
    };

    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(24*3*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock dev->i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    dev->i_buffer->Unlock(); 
}

void ship::shipMove(float x)//makes sure xPosition is valid and then moves it also controls ship tilting animation
{
	

	if(x<0)//the pitch
	{
		if(pivot>-30)
			pivot+=-2;
	}
	else if(x>0)
	{
		if(pivot<30)
			pivot+=2;
	}
	else
	{
		if(pivot<0)
			pivot+=2;
		else if(pivot>0)
			pivot+=-2;
	}
	float temp=xPosition+x;
	if((temp<=140)&&(temp>=-140))
		xPosition=temp;
	return;
}
void ship::fire(void)
{
	if(bulletFired!=TRUE)
	{
		xBulletPosition=xPosition;
		bulletFired=TRUE;
	}
}
void ship::returnBullet(void)//resets the bullet(eg. after a hit)
{
	bulletDistance=yPosition;
	bulletFired=FALSE;
}
void ship::handleBulletMove(void)//makes the bullet move until it reaches max distance then resets bulletDistance and bulletFired flag
{	
			if(bulletDistance<=bulletMaxDistance)
			{
				bulletDistance+=bulletSpeed;
				return;
			}
		else
			{
				bulletDistance=yPosition;
				bulletFired=FALSE;
				return;
			}
	
}




float* ship::returnBulletBox(void)//calculates bullet box and returns a pointer to an array
{//be careful - and + may be screwy here but it shouldn't matter
	bulletBox[0]=xBulletPosition-0.5;
	bulletBox[1]=bulletDistance-0.5+4.0;
	bulletBox[2]=1.0;
	bulletBox[3]=1.0;

	return bulletBox;
}
float* ship::returnShipBox(void)//calculates ship box
{//be careful - and + may be screwy here but it shouldn't matter
	shipBox[0]=xPosition-6.0;
	shipBox[1]=yPosition-9.0;
	shipBox[2]=12.0;
	shipBox[3]=18.0;

	return shipBox;
}
void ship::showLives(int lives)
{
	switch(lives)
	{
	case 1:renderLife(140,-115);
		break;
	case 2:	renderLife(140,-115);
			renderLife(130,-115);
			break;
	case 3:	renderLife(140,-115);
		renderLife(130,-115);
		renderLife(120,-115);
		break;
	case 4:	renderLife(140,-115);
		renderLife(130,-115);
		renderLife(120,-115);
		renderLife(110,-115);
		break;
	case 5:	renderLife(140,-115);
		renderLife(130,-115);
		renderLife(120,-115);
		renderLife(110,-115);
		renderLife(100,-115);
		break;
	}
}
void ship::renderLife(int x, int y)
{
	D3DXMATRIX shipMove;//moves entire ship
	D3DXMATRIX shipPivot;
	D3DXMATRIX shipResize;
	D3DXMatrixTranslation(&shipMove,x,y,0.0f);
	
	D3DXMatrixScaling(&shipResize,0.75,0.75,0.75);//had to resize the ship

	shipMove=shipResize*shipMove;//easier this way
	//explosion matrices
	D3DXMATRIX matDMain;
	D3DXMATRIX matDRightWing;
	D3DXMATRIX matDLeftWing;
	D3DXMATRIX matRotateY; 
	D3DXMatrixTranslation(&matDMain, 0, 0, 0);//default these
	D3DXMatrixTranslation(&matDRightWing, 0, 0, 0);
	D3DXMatrixTranslation(&matDLeftWing, 0, 0, 0);
	

	ShipGraphic();
		// set the world transform
		D3DXMATRIX matTranslate;    // a matrix to store the translation information
		D3DXMatrixTranslation(&matTranslate, -0.5f, 2.0f, 0.5f);
		static float index = 0.0f; index+=0.00f; // an ever-increasing float value
		   // a matrix to store the rotation for each triangle
		  // the rotation matrix
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslate*shipMove*matDMain));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 28);
		dev->cleanBuffers();


		Engine();
		// set the world transform
		D3DXMATRIX matTranslateEngine1;    // a matrix to store the translation information
		D3DXMatrixTranslation(&matTranslateEngine1, -3.0f, -3.5f, 1.0f);
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateEngine1*shipMove*matDLeftWing));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();

	
		Engine();
		// set the world transform
		D3DXMATRIX matTranslateEngine2;    // a matrix to store the translation information
		D3DXMATRIX matEngineFlip;
		D3DXMatrixRotationY(&matEngineFlip, D3DXToRadian(180.0f));
		D3DXMatrixTranslation(&matTranslateEngine2, 3.0f, -3.5f, -1.0f);
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matEngineFlip*matTranslateEngine2*shipMove*matDRightWing));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();
}
void ship::renderScore(int x,int y)
{
	D3DXMATRIX shipMove;//moves entire ship
	D3DXMATRIX shipPivot;
	D3DXMATRIX shipResize;
	D3DXMatrixTranslation(&shipMove,x,y,0.0f);
	
	if(shipAngleDirection==TRUE)
		shipAngle-=2.0;
	else
		shipAngle+=2.0;

	if(shipAngle>=30)
		shipAngleDirection=TRUE;
	if(shipAngle<=-30)
		shipAngleDirection=FALSE;

	D3DXMatrixRotationY(&shipPivot, D3DXToRadian(shipAngle));
	D3DXMatrixScaling(&shipResize,1.00,1.00,1.00);//had to resize the ship

	shipMove=shipResize*shipMove;//easier this way
	//explosion matrices
	D3DXMATRIX matDMain;
	D3DXMATRIX matDRightWing;
	D3DXMATRIX matDLeftWing;
	D3DXMATRIX matRotateY; 
	D3DXMatrixTranslation(&matDMain, 0, 0, 0);//default these
	D3DXMatrixTranslation(&matDRightWing, 0, 0, 0);
	D3DXMatrixTranslation(&matDLeftWing, 0, 0, 0);
	

	ShipGraphic();
		// set the world transform
		D3DXMATRIX matTranslate;    // a matrix to store the translation information
		D3DXMatrixTranslation(&matTranslate, -0.5f, 2.0f, 0.5f);
		static float index = 0.0f; index+=0.00f; // an ever-increasing float value
		   // a matrix to store the rotation for each triangle
		  // the rotation matrix
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslate*shipPivot*shipMove*matDMain));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 28);
		dev->cleanBuffers();


		Engine();
		// set the world transform
		D3DXMATRIX matTranslateEngine1;    // a matrix to store the translation information
		D3DXMatrixTranslation(&matTranslateEngine1, -3.0f, -3.5f, 1.0f);
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateEngine1*shipPivot*shipMove*matDLeftWing));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();

	
		Engine();
		// set the world transform
		D3DXMATRIX matTranslateEngine2;    // a matrix to store the translation information
		D3DXMATRIX matEngineFlip;
		D3DXMatrixRotationY(&matEngineFlip, D3DXToRadian(180.0f));
		D3DXMatrixTranslation(&matTranslateEngine2, 3.0f, -3.5f, -1.0f);
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matEngineFlip*matTranslateEngine2*shipPivot*shipMove*matDRightWing));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();

		
		D3DXMATRIX matTranslateShip2;
		D3DXMatrixTranslation(&matTranslateShip2, -90.0f, 0.0f, 0.0f);
		ShipGraphic();
		// set the world transform

		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslate*shipPivot*shipMove*matDMain*matTranslateShip2));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 28);
		dev->cleanBuffers();


		Engine();
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateEngine1*shipPivot*shipMove*matDLeftWing*matTranslateShip2));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();

	
		Engine();
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matEngineFlip*matTranslateEngine2*shipPivot*shipMove*matDRightWing*matTranslateShip2));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 24);
		dev->cleanBuffers();
}