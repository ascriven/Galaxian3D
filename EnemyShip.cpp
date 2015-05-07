#ifndef HEADER
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include "cDirect3D.h"
#include "EnemyShip.h"
struct CUSTOMVERTEX {FLOAT X, Y, Z; DWORD COLOR;};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif


enemyShip::enemyShip()
{
	return;
}
void enemyShip::colorSet(int color)//sets the color based on an integer between 1-4 1:Green 2:Blue 3:Red 4:Yellow
{
	switch(color){//sets the colors for each level of enemy may also be used to designate other variable factors of the different enemies

		case 1:
		colorTip[0]=100;//tips RGB color
		colorTip[1]=255;
		colorTip[2]=100;

		colorMid[0]=0;//mid RGB color
		colorMid[1]=50;
		colorMid[2]=0;

		colorOut[0]=0;//mid RGB color
		colorOut[1]=100;
		colorOut[2]=0;

		attackXMove=1.0;//speed of green ship each ship will have different speeds
		attackYMove=0.5;
		score=10;
			break;

		case 2:
		colorTip[0]=100;//tips RGB color
		colorTip[1]=100;
		colorTip[2]=255;

		colorMid[0]=0;//mid RGB color
		colorMid[1]=0;
		colorMid[2]=50;

		colorOut[0]=0;//mid RGB color
		colorOut[1]=0;
		colorOut[2]=100;

		attackXMove=2.0;//speed of Blue ship each ship will have different speeds
		attackYMove=0.5;
		score=20;
			break;

		case 3:
		colorTip[0]=255;//tips RGB color
		colorTip[1]=100;
		colorTip[2]=100;

		colorMid[0]=50;//mid RGB color
		colorMid[1]=0;
		colorMid[2]=0;

		colorOut[0]=100;//mid RGB color
		colorOut[1]=0;
		colorOut[2]=0;

		attackXMove=2.0;//speed of Red ship each ship will have different speeds
		attackYMove=1.0;
		score=30;
			break;

		case 4:
		colorTip[0]=255;//tips RGB color
		colorTip[1]=255;
		colorTip[2]=100;

		colorMid[0]=50;//mid RGB color
		colorMid[1]=50;
		colorMid[2]=0;

		colorOut[0]=150;//mid RGB color
		colorOut[1]=150;
		colorOut[2]=50;

		attackXMove=2.0;//speed of Yellow ship each ship will have different speeds
		attackYMove=1.0;
		score=40;
			break;


		default:
		colorTip[0]=100;//tips RGB color
		colorTip[1]=255;
		colorTip[2]=100;

		colorMid[0]=0;//mid RGB color
		colorMid[1]=50;
		colorMid[2]=0;

		colorOut[0]=0;//mid RGB color
		colorOut[1]=100;
		colorOut[2]=0;

		attackXMove=1.0;//speed of green ship each ship will have different speeds
		attackYMove=0.5;
			break;
	}

}

void enemyShip::initShip(cDirect3D* d3ddev,float x,float y, int color)
{
	dev=d3ddev;//Direct3D device

	xPosition=x;//position
	yPosition=y;
	zPosition=0;
	shipAngle=0;
	if(y==30||y==60)
		shipAngleDirection=TRUE;
	else
		shipAngleDirection=FALSE;
	
	
	exist=TRUE;//does exist at creation
	explode = FALSE;//not exploding at creation
	attack = FALSE;//not attacking at creation
	endattack=FALSE;//not ending attack at creation

	increment=0;//increment for explosion
	rotIndex = -0.5;

	bulletDistance1=0.0f;//not exist at creation
	bulletDistance2=0.0f;
	bulletX1=0.0f;//variables store xPosition at time of fire
	bulletX2=0.0f;
	bulletMaxDistance=-110;//bullet will stop existing after this point
	bulletFlag1=false;//not shooting at creation
	bulletFlag2=false;

	colorSet(color);//color 1-4


	

}
void enemyShip::renderEnemyShip(void)//draws the enemy ship will eventually include x, y position and color arguments
{

	D3DXMATRIX matTranslate;    // a matrix to store the translation information
	D3DXMATRIX matTranslateShip;	//for ship so bullet does not have the back and forth motion
	D3DXMATRIX matRotation;			//matrix to rotate triangle to make hexagon
	D3DXMATRIX matMainRotation;			//matrix to rotate triangle to make hexagon

	//matrixes to handle destruction could be reorganized later
	D3DXMATRIX matDMain;
	D3DXMATRIX matDRightWing;
	D3DXMATRIX matDLeftWing;
	D3DXMatrixTranslation(&matDMain, 0, 0, 0);//default these
	D3DXMatrixTranslation(&matDRightWing, 0, 0, 0);
	D3DXMatrixTranslation(&matDLeftWing, 0, 0, 0);
	D3DXMatrixTranslation(&matTranslate, xPosition, yPosition, zPosition);
	D3DXMatrixRotationX(&matRotation, rotIndex);

		//rotations
	
	D3DXMATRIX matARotate;


	if(explode)//explode animation
	{
		D3DXMatrixTranslation(&matDMain, 0, -increment*.5, increment);
		D3DXMatrixTranslation(&matDRightWing, increment, -increment*.5, 0);
		D3DXMatrixTranslation(&matDLeftWing, -increment, -increment*.5, 0);
		rotIndex+=0.1;
		increment+=1.0;
		if(!attack)
		{
			D3DXMatrixTranslation(&matTranslate, xPosition, yPosition, zPosition);
			D3DXMatrixRotationX(&matRotation, rotIndex);
			matTranslateShip=matRotation*matTranslate;
		}
		else
		{
			D3DXMatrixRotationX(&matRotation, rotIndex);
			D3DXMatrixTranslation(&matTranslate, attackX, attackY, zPosition);
			D3DXMatrixRotationZ(&matARotate, D3DXToRadian(shipAngle));
			matTranslateShip=matARotate*matTranslate;
		}
	}
	else if(attack)//attack animation
	{

		attackControl();

		D3DXMatrixTranslation(&matTranslate, attackX, attackY, zPosition);
		D3DXMatrixRotationZ(&matARotate, D3DXToRadian(shipAngle));
		matTranslateShip=matARotate*matTranslate;

	}
	else//only rotate back and forth if not attacking
	{
		RotateControl();
		D3DXMatrixRotationZ(&matARotate, D3DXToRadian(shipAngle));
		matTranslateShip=matARotate*matTranslate;

	}

	
	if(explode&&(increment>=50.0)&&!bulletFlag1)//if the ship has exploded and the increment is above 50.0f it no longer exists and it is no longer attacking
	{		
		attack=FALSE;
		exist=FALSE;
	}



	
	enemyShipMain();



	for(float i=0;i<=5;i+=1)//draws hexagon out of triangle
	{
		D3DXMatrixRotationZ(&matMainRotation, D3DXToRadian(60*i));
		
		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matMainRotation*matRotation*matTranslateShip*matDMain));    // set the world transform
		// select the vertex buffer to display
		dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
		dev->d3ddev->SetIndices(dev->i_buffer);
		// draw
		dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 4);
	}

	D3DXMATRIX matRotateSecondWing;		//matrix used to rotate image to create 2nd wing
	D3DXMATRIX matTranslateSecondWing;	//matrix used to reposition second wing properly

	

	dev->cleanBuffers();
	enemyShipWing();
	dev->d3ddev->SetTransform(D3DTS_WORLD, &(matRotation*matTranslateShip*matDRightWing));    // set the world transform
	// select the vertex buffer to display
	dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
	dev->d3ddev->SetIndices(dev->i_buffer);
	// draw
	dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 11, 0, 16);

	D3DXMatrixTranslation(&matTranslateSecondWing, 0.0f, 0.0f, -2.0f);
	D3DXMatrixRotationY(&matRotateSecondWing,D3DXToRadian(180) );
	dev->cleanBuffers();
	enemyShipWing();

	dev->d3ddev->SetTransform(D3DTS_WORLD, &(matRotateSecondWing*matTranslateSecondWing*matRotation*matTranslateShip*matDLeftWing));    // set the world transform
	// select the vertex buffer to display
	dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
	dev->d3ddev->SetIndices(dev->i_buffer);
	// draw
	dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 11, 0, 16);
	dev->cleanBuffers();

	bulletControl();
	if(attack)
	{
		if(bulletFlag1)
		{
			enemyBullet();
			D3DXMATRIX matBulletFire;
			D3DXMATRIX matBulletExpand;
			D3DXMATRIX matBulletRotate;
	

			D3DXMatrixScaling(&matBulletExpand,1.0,2.0,1.0);
			D3DXMatrixRotationZ(&matBulletRotate,D3DXToRadian(180));
			D3DXMatrixTranslation(&matBulletFire, bulletX1, bulletDistance1, 0.0f);
			dev->d3ddev->SetTransform(D3DTS_WORLD, &(matBulletExpand*matBulletRotate*matBulletFire));
			dev->d3ddev->SetIndices(dev->i_buffer);
			// select the vertex buffer to display
			dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));

				// draw the Bullet
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 9, 0, 14);
		dev->cleanBuffers();
		}
	}
	
	if(attack)
	{
		if(bulletFlag2)
		{
			enemyBullet();
			D3DXMATRIX matBulletFire;
			D3DXMATRIX matBulletExpand;
			D3DXMATRIX matBulletRotate;
	

			D3DXMatrixScaling(&matBulletExpand,1.0,2.0,1.0);
			D3DXMatrixRotationZ(&matBulletRotate,D3DXToRadian(180));
			D3DXMatrixTranslation(&matBulletFire, bulletX2, bulletDistance2, 0.0f);
			dev->d3ddev->SetTransform(D3DTS_WORLD, &(matBulletExpand*matBulletRotate*matBulletFire));
			dev->d3ddev->SetIndices(dev->i_buffer);
			// select the vertex buffer to display
			dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));

				// draw the Bullet
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 9, 0, 14);
		dev->cleanBuffers();
		}
	}
	


}
void enemyShip::enemyShipMain(void)//enemy ship main body
{
	    // create the vertices using the CUSTOMVERTEX
    struct CUSTOMVERTEX vertices[] =
    {
		{ 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(colorTip[0], colorTip[1], colorTip[2]), },//0 front
		{ 2*sqrt(3.0f), 2.0f, 0.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },
		{ 2*sqrt(3.0f), -2.0f, 0.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },

		{ 0.0f, 0.0f, -2.0f, D3DCOLOR_XRGB(colorTip[0], colorTip[1], colorTip[2]), },//3 back
        { 2*sqrt(3.0f), 2.0f, -2.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },
		{ 2*sqrt(3.0f), -2.0f, -2.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },


    };

    // create a vertex buffer interface called v_buffer
    dev->d3ddev->CreateVertexBuffer(6*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    dev->v_buffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,//front face 1
		3, 4, 5,//back face 1
		1, 2, 4,//side 2
		4, 5, 2,

    };
	    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(4*3*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    dev->i_buffer->Unlock();
	return;
}

void enemyShip::enemyShipWing(void)//enemy ship wing
{
	    // create the vertices using the CUSTOMVERTEX
    struct CUSTOMVERTEX vertices[] =
    {
		
        { 2*sqrt(3.0f), 2.0f, 0.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },//0 front right side
		{ 2*sqrt(3.0f), -2.0f, 0.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },

        { 2*sqrt(3.0f), 2.0f, -2.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },//2 back right side
		{ 2*sqrt(3.0f), -2.0f, -2.0f, D3DCOLOR_XRGB(colorMid[0], colorMid[1], colorMid[2]), },

		{ (2*sqrt(3.0f)+1.0f), 2.0f, 0.0f, D3DCOLOR_XRGB(40, 40, 40), },//4 front left side
		{ (2*sqrt(3.0f)+1.0f), -2.0f, 0.0f, D3DCOLOR_XRGB(80, 80, 80), },

        { (2*sqrt(3.0f)+1.0f), 2.0f, -2.0f, D3DCOLOR_XRGB(40, 40, 40), },//6 back left side
		{ (2*sqrt(3.0f)+1.0f), -2.0f, -2.0f, D3DCOLOR_XRGB(80, 80, 80), },

		{ (2*sqrt(3.0f)+4.0f), 1.0f, -1.0f, D3DCOLOR_XRGB(colorOut[0], colorOut[1], colorOut[2]), },//8 left tips
		{ (2*sqrt(3.0f)+4.0f), -1.0f, -1.0f, D3DCOLOR_XRGB(colorOut[0], colorOut[1], colorOut[2]), },

		{ (2*sqrt(3.0f)+2.5f), -6.0f, -1.0f, D3DCOLOR_XRGB(colorOut[0], colorOut[1], colorOut[2]), },//10 tip


    };

    // create a vertex buffer interface called v_buffer
    dev->d3ddev->CreateVertexBuffer(11*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    dev->v_buffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
        0, 4, 5,//front face 2
		5, 1, 0,
		6, 7, 2,//back face 2
		2, 3, 7,
		5, 7, 3,//bottom face 2
		3, 1, 5,
		4, 6, 2,//top face 2
		2, 0, 4,
		4, 6, 8,//top left face 1
		4, 5, 9,//front left face 2
		9, 8, 4,
		6, 7, 9,//back left face 2
		9, 8, 6,
		5, 7, 10,//tip 3
		9, 5, 10,
		9, 7, 10,

    };
	    // create a index buffer interface called i_buffer
    dev->d3ddev->CreateIndexBuffer(16*3*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    dev->i_buffer->Unlock();

	return;
}//wings fo
void enemyShip::enemyBullet(void)
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

    // create a vertex buffer interface called v_buffer
    dev->d3ddev->CreateVertexBuffer(9*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
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

    // create a index buffer interface called i_buffer
    dev->d3ddev->CreateIndexBuffer(14*3*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    dev->i_buffer->Unlock(); 
	return;
}


void enemyShip::enemyExplode(void)//simply tells renderEnemyShip that the explosion animation should play
{
	explode=TRUE;
}
float* enemyShip::returnBoundBox(void)//calculates bullet box and returns a pointer to an array
{//must modify positions negatively and distances positively this is a good example
	if(!attack)
	{
		boundBox[0]=xPosition-7.0;
		boundBox[1]=yPosition-1;
		boundBox[2]=14;
		boundBox[3]=2;
	}
	else
	{
		boundBox[0]=attackX-7.0;
		boundBox[1]=attackY-1;
		boundBox[2]=14;
		boundBox[3]=2;
	}

	return boundBox;
}

void enemyShip::enemyShipMove(float x)
{
	xPosition+=x;
}
float enemyShip::getX(void)
{
	return xPosition;
}
void enemyShip::initAttack(double bullet1,double bullet2)//initiaites an attack and sets the bullet firing in motion these should be random numbers between 1 and 50
//bulletMaxDistance+yPosition
{
	bulletTrig1=-bullet1+10;
	bulletTrig2=-bullet2+10;
	attack=TRUE;
	attackX=xPosition;
	attackY=yPosition;
	bulletFlag1=false;
	bulletFlag2=false;
}
void enemyShip::attackControl(void)//controls the attack animation
{
	if(attackY>-110&&!endattack)
	{
		if(zPosition<10)//initial sequence
		{
			zPosition+=1;
			if(shipAngleDirection)
			{
				shipAngle -=4.5;
			}
			else
			{
				shipAngle +=4.5;
			}
		}


		else if(shipAngleDirection)//movements
		{
			attackY-=attackYMove;

			if(shipAngle>-45)
			{
				shipAngle-=4.5;
			}

			if(attackX>=-140)//control x movement
				attackX-=attackXMove;
			else
			{
				shipAngleDirection=!shipAngleDirection;
			}
		}
		else
		{
			attackY-=attackYMove;

			if(shipAngle<45)
			{
				shipAngle+=4.5;
			}

			if(attackX<=140)//control x movement
				attackX+=attackXMove;
			else
			{
				shipAngleDirection=!shipAngleDirection;
			}
		}
	}
	else if(endattack)
	{
		if(shipAngle!=0)
			shipAngle=0;
		if(attackX!=xPosition)
			attackX=xPosition;

		if(attackY>yPosition)
			attackY-=1.0;

		if(((attackX<=xPosition+1)||(attackX>=xPosition-1))&&attackY==yPosition)
			if(zPosition>0)
				zPosition-=0.25;
			else//finish up an attack
			{
				endattack=FALSE;
				attack=FALSE;
			}
	
	}
	else if(attackY<=-110)
	{
		endattack=TRUE;
		attackY=100;
		bulletFlag1=false;
		bulletFlag2=false;
	}
	else
	{
		attack=FALSE;
	}
	

		

}
void enemyShip::RotateControl(void)
{
	if(shipAngleDirection==TRUE)
		shipAngle-=1.0;
	else
		shipAngle+=1.0;

	if(shipAngle>=15)
		shipAngleDirection=TRUE;
	if(shipAngle<=-15)
		shipAngleDirection=FALSE;
}
void enemyShip::bulletControl(void)//controls the bullets for the attack sequence
{
		//bullettriggers are handled here

	if((bulletTrig1==attackY)&&(!bulletFlag1))//at the trigger position and hasn't already been fired
	{
		bulletFlag1=true;//bullet is fired at this point
		bulletX1=attackX;//bullet must remain at this xPosition
		bulletDistance1=attackY;
	}

	if((bulletTrig2==attackY)&&(!bulletFlag2))
	{
		bulletFlag2=true;
		bulletX2=attackX;
		bulletDistance2=attackY;
	}
	if(bulletFlag1)//&&(attackY<bulletTrig1))
	{
		bulletDistance1-=1.0f;
	}
	if(bulletFlag2)//&&(attackY<bulletTrig2))
	{
		bulletDistance2-=1.0f;
	}

	if(bulletDistance1<-110)
	{
		bulletFlag1=false;
	}
	if(bulletDistance2<-110)
	{
		bulletFlag2=false;
	}
}
float* enemyShip::returnBulletBox1(void)
{
	bulletBox1[0]=bulletX1-0.5;
	bulletBox1[1]=bulletDistance1-0.5+4.0;
	bulletBox1[2]=1.0;
	bulletBox1[3]=1.0;

	return bulletBox1;
}
float* enemyShip::returnBulletBox2(void)
{
	bulletBox2[0]=bulletX2-0.5;
	bulletBox2[1]=bulletDistance2-0.5+4.0;
	bulletBox2[2]=1.0;
	bulletBox2[3]=1.0;

	return bulletBox2;
}
int enemyShip::returnScore()
{
	if(attack)
		return score*2;
	else
		return score;
}