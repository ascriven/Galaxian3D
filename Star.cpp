#ifndef HEADER
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include "cDirect3D.h"
#include "Star.h"
struct CUSTOMVERTEX {FLOAT X, Y, Z; DWORD COLOR;};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif
star::star(void)
{
}

star::star(cDirect3D* d3ddev,float x,float y,int distance)
	{
		dev=d3ddev;
		
		xStar=x;
		yStar=y;
		twinkle=0;
		tFlag=true;

		switch(distance){
			case 1:scale=.5;
				break;
			case 2:scale=.25;
				break;
			case 3:scale=.125;
				break;
			default:scale=.5;
				break;
		}

	}
void star::initStar(cDirect3D* d3ddev,float x,float y,int distance)
	{
		dev=d3ddev;
		
		xStar=x;
		yStar=y;		
		twinkle=0;
		tFlag=true;

		switch(distance){
			case 1:scale=.5;
				break;
			case 2:scale=.25;
				break;
			case 3:scale=.125;
				break;
			default:scale=.5;
				break;
		}

	}
void star::starBase(void)//draws the stars main body
{
    // create the vertices using the CUSTOMVERTEX
	float dubble=1.5f;
    struct CUSTOMVERTEX vertices[] =
    {
        //Front Points starts top right and goes clockwise
        { 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },//0 midpoint

		{ 1.0f*dubble, sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },//1 right side
		{ sqrt(3.0f)*dubble, 1.0f*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ sqrt(3.0f)*dubble, -1.0f*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ 1.0f*dubble, -sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },

		{ -1.0f*dubble, -sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },//5 left side
		{ -sqrt(3.0f)*dubble, -1.0f*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ -sqrt(3.0f)*dubble, 1.0f*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ -1.0f*dubble, sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },

		{ 0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },//9 midpoint

		{ 1.0f*dubble, sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },//10 right side
		{ sqrt(3.0f)*dubble, 1.0f*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ sqrt(3.0f)*dubble, -1.0f*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ 1.0f*dubble, -sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },

		{ -1.0f*dubble, -sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },//14 left side
		{ -sqrt(3.0f)*dubble, -1.0f*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ -sqrt(3.0f)*dubble, 1.0f*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },
		{ -1.0f*dubble, sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },

    };

    // create a vertex buffer interface called dev->v_buffer
    dev->d3ddev->CreateVertexBuffer(18*sizeof(CUSTOMVERTEX),
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
        0, 1, 2,//front 8
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1,
		9, 10, 11,//back 8
		9, 11, 12,
		9, 12, 13,
		9, 13, 14,
		9, 14, 15,
		9, 15, 16,
		9, 16, 17,
		9, 17, 10,
		8, 1, 17,//top 2
		17, 10, 1,
		1, 2, 10,//right top 2
		10, 11, 2,
		2, 3, 11,//right 2
		11, 12, 3,
		3, 4, 12,//right bottom 2
		12, 13, 4,
		5, 4, 14,//bottom 2
		14, 13, 4,
		6, 5, 15,//left bottom 2
		15, 14, 5,
		7, 6, 16,//left 2
		16, 15, 6,
		7, 8, 16,//left top 2
		16, 17, 8,


    };
	    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(32*3*sizeof(short),
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

void star::starHV(void)//draws the points on the vertical and horizontal
{
	    // create the vertices using the CUSTOMVERTEX
	float dubble=1.5f;
    struct CUSTOMVERTEX vertices[] =
    {
        { 1.0f*dubble, sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },//0 base
		{ 1.0f*dubble, -sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },
        { 1.0f*dubble, sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },//2 back base
		{ 1.0f*dubble, -sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },

		{ 8.0f, 0.0f, -0.5f, D3DCOLOR_XRGB(100, 0, 255), },

    };

    // create a vertex buffer interface called dev->v_buffer
    dev->d3ddev->CreateVertexBuffer(5*sizeof(CUSTOMVERTEX),
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
	    0, 1, 4,//pyramid
		0, 2, 4,
		1, 3, 4,
		2, 3, 4,

    };
	    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(4*3*sizeof(short),
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
void star::starAngle(void)//draws the points on the diagonal
{
	    // create the vertices using the CUSTOMVERTEX
	float dubble=1.5f;
    struct CUSTOMVERTEX vertices[] =
    {
        { 1.0f*dubble, sqrt(3.0f)*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },//0 base
		{ sqrt(3.0f)*dubble, 1.0f*dubble, 0.0f, D3DCOLOR_XRGB(100, 255, 255), },
        { 1.0f*dubble, sqrt(3.0f)*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },//2 base
		{ sqrt(3.0f)*dubble, 1.0f*dubble, -1.0f, D3DCOLOR_XRGB(100, 255, 255), },

		{ 4*sqrt(2.0f), 4*sqrt(2.0f), -0.5f, D3DCOLOR_XRGB(100, 0, 255), },//4

    };

    // create a vertex buffer interface called dev->v_buffer
    dev->d3ddev->CreateVertexBuffer(5*sizeof(CUSTOMVERTEX),
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
        0, 1, 4,//pyramid
		0, 2, 4,
		1, 3, 4,
		2, 3, 4,
    };
	    // create a index buffer interface called dev->i_buffer
    dev->d3ddev->CreateIndexBuffer(4*3*sizeof(short),
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
void star::starDraw(void)//this draws a Star to the Background will eventually include arguments to set stars X Y coords, size and color of star
{

	
	D3DXMATRIX matTranslateStar;    // a matrix to store the translation information
	D3DXMATRIX matSpikeRotation;	//matrix used to rotate drawn spikes
	D3DXMATRIX matScaleStar;			//matrix used to scale stars down
	D3DXMATRIX matTwinkle;

	starTwinkle();
	
	D3DXMatrixTranslation(&matTranslateStar, xStar, yStar, -5.0f);//set star transformation here
	D3DXMatrixScaling(&matScaleStar,scale,scale,scale);
	D3DXMatrixRotationZ(&matTwinkle,D3DXToRadian(twinkle));

	starBase();
	// set the world transform

	
    dev->d3ddev->SetTransform(D3DTS_WORLD, &(matScaleStar*matTwinkle*matTranslateStar));    // set the world transform
	
	// select the vertex buffer to display
    dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
    dev->d3ddev->SetIndices(dev->i_buffer);
	// draw
    dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 18, 0, 32);
	dev->cleanBuffers();


	starAngle();
	for(float i=0;i<=3;i+=1)//draws 4 spikes at equal areas
	{
	// set the world transform
	D3DXMatrixRotationZ(&matSpikeRotation, D3DXToRadian(90*i));
    dev->d3ddev->SetTransform(D3DTS_WORLD, &(matSpikeRotation*matScaleStar*matTwinkle*matTranslateStar));    // set the world transform
	 
	// select the vertex buffer to display
    dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
    dev->d3ddev->SetIndices(dev->i_buffer);
	// draw
    dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
	}
	dev->cleanBuffers();

	starHV();
	for(float i=0;i<=3;i+=1)//draws 4 spikes at equal areas
	{
	// set the world transform
	D3DXMatrixRotationZ(&matSpikeRotation, D3DXToRadian(90*i));
    dev->d3ddev->SetTransform(D3DTS_WORLD, &(matSpikeRotation*matScaleStar*matTwinkle*matTranslateStar));    // set the world transform
	
	// select the vertex buffer to display
    dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(CUSTOMVERTEX));
    dev->d3ddev->SetIndices(dev->i_buffer);
	// draw
    dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 4);
	}
	dev->cleanBuffers();


	return;
}
void star::starTwinkle(void)//controls the stars twinkle
{
	if(tFlag==true)
		twinkle=twinkle-1;
	else
		twinkle=twinkle+1;

	if(tFlag==true&&twinkle<-10)
		tFlag=false;
	if(tFlag==false&&twinkle>10)
		tFlag=true;
}