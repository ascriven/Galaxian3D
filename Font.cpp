#ifndef HEADER
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <fstream>
#include <string>
#include "cDirect3D.h"
#include "Font.h"
using namespace std;
struct TEXTUREVERTEX{float X, Y, Z;float TU, TV;};//define texture vertex structure
#include "cPoly3D.h"
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)//for Textures
#endif

/*void Font::loadFile(LPCSTR filename,TEXTUREDATA** current)
{	

	TEXTUREDATA* cur=*current;
	FILE* f = fopen( filename, "rb" );
	
	fseek( f, 0, SEEK_END );
	cur->size = ftell( f );
	fseek( f, 0, SEEK_SET );
	
	cur->pVoid = malloc(cur->size);
	
	fread( (cur->pVoid), 1, cur->size, f );
	fclose(f);
	current=&cur;
					
}*/
void Font::loadTextures()
{
	//well it's kind of uneccassary to load these files first and then load them to textures...but what's done is done I suppose
	//I'm just leaving this in as a relic of my pain
	/*for(int i=0;i<10;i++)
		num[i]=new TEXTUREDATA;
	
	loadFile("Font/0.png",&num[0]);	
	loadFile("Font/1.png",&num[1]);
	loadFile("Font/2.png",&num[2]);
	loadFile("Font/3.png",&num[3]);
	loadFile("Font/4.png",&num[4]);
	loadFile("Font/5.png",&num[5]);
	loadFile("Font/6.png",&num[6]);
	loadFile("Font/7.png",&num[7]);
	loadFile("Font/8.png",&num[8]);
	loadFile("Font/9.png",&num[9]);	
   	for(int i=0;i<26;i++)
		letter[i]=new TEXTUREDATA;
	loadFile("Font/a.png",&letter[0]);
	loadFile("Font/b.png",&letter[1]);
	loadFile("Font/c.png",&letter[2]);
	loadFile("Font/d.png",&letter[3]);
	loadFile("Font/e.png",&letter[4]);
	loadFile("Font/f.png",&letter[5]);
	loadFile("Font/g.png",&letter[6]);
	loadFile("Font/h.png",&letter[7]);
	loadFile("Font/i.png",&letter[8]);
	loadFile("Font/j.png",&letter[9]);
	loadFile("Font/k.png",&letter[10]);
	loadFile("Font/l.png",&letter[11]);
	loadFile("Font/m.png",&letter[12]);
	loadFile("Font/n.png",&letter[13]);
	loadFile("Font/o.png",&letter[14]);
	loadFile("Font/p.png",&letter[15]);
	loadFile("Font/q.png",&letter[16]);
	loadFile("Font/r.png",&letter[17]);
	loadFile("Font/s.png",&letter[18]);
	loadFile("Font/t.png",&letter[19]);
	loadFile("Font/u.png",&letter[20]);
	loadFile("Font/v.png",&letter[21]);
	loadFile("Font/w.png",&letter[22]);
	loadFile("Font/x.png",&letter[23]);
	loadFile("Font/y.png",&letter[24]);
	loadFile("Font/z.png",&letter[25]);	
	  for(int i=0;i<2;i++)
		punct[i]=new TEXTUREDATA;
	 loadFile("Font/period.png",&punct[0]);	
	 loadFile("Font/colon.png",&punct[1]);*/

	titleTex=new LPDIRECT3DTEXTURE9;
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/logo2.png", (titleTex) );
	for(int i=0;i<10;i++)
		numTex[i]=new LPDIRECT3DTEXTURE9;
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/0.png", (numTex[0]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/1.png", (numTex[1]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/2.png", (numTex[2]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/3.png", (numTex[3]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/4.png", (numTex[4]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/5.png", (numTex[5]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/6.png", (numTex[6]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/7.png", (numTex[7]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/8.png", (numTex[8]) );
	D3DXCreateTextureFromFileA( dev->d3ddev, "Font/9.png", (numTex[9]) );

	for(int i=0;i<26;i++)
		letterTex[i]=new LPDIRECT3DTEXTURE9;
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/a.png",letterTex[0]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/b.png",letterTex[1]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/c.png",letterTex[2]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/d.png",letterTex[3]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/e.png",letterTex[4]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/f.png",letterTex[5]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/g.png",letterTex[6]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/h.png",letterTex[7]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/i.png",letterTex[8]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/j.png",letterTex[9]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/k.png",letterTex[10]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/l.png",letterTex[11]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/m.png",letterTex[12]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/n.png",letterTex[13]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/o.png",letterTex[14]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/p.png",letterTex[15]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/q.png",letterTex[16]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/r.png",letterTex[17]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/s.png",letterTex[18]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/t.png",letterTex[19]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/u.png",letterTex[20]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/v.png",letterTex[21]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/w.png",letterTex[22]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/x.png",letterTex[23]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/y.png",letterTex[24]);
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/z.png",letterTex[25]);	

	for(int i=0;i<2;i++)
		punctTex[i]=new LPDIRECT3DTEXTURE9;
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/period.png",punctTex[0]);	
	D3DXCreateTextureFromFileA( dev->d3ddev,"Font/colon.png",punctTex[1]);

}
void Font::symbol(double xPos,double yPos,double zPos, LPCSTR filename)
{
			dev->d3ddev->SetFVF(TEXTUREFVF);
			D3DXCreateTextureFromFileA( (dev->d3ddev), filename, &(dev->t_buffer) );

			dev->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
			dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);//modulate tells Direct3D to blend the textures colors with the scenes colors
			//if SetTextureStageState is not set to DISABLE then this will continue on into your other objects
			struct TEXTUREVERTEX vertices[] =
			{
				0.0 ,0.0 ,0.0 ,0.01 ,0.01 ,
				48.0 ,0.0 ,0.0 ,0.99 ,0.01 ,
				0.0 ,63.0 ,0.0 ,0.01 ,0.99 ,
				48.0 ,63.0 ,0.0 ,0.99 ,0.99 ,
			};
			dev->d3ddev->CreateVertexBuffer((4)*sizeof(TEXTUREVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

		VOID* pVoid;    // a void pointer
	

		//lock dev->v_buffer and load the vertices into it
		dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, vertices, (4)*sizeof(TEXTUREVERTEX));
		dev->v_buffer->Unlock();

		short indices[] =
		{
			0,1,2,
			1,2,3,
		};

		dev->d3ddev->CreateIndexBuffer(6*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

		// lock dev->i_buffer and load the indices into it
		dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, 6*sizeof(short));
		dev->i_buffer->Unlock(); 

		D3DXMATRIX matFlipX;
		D3DXMATRIX matFlipY;
		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
			
		D3DXMatrixScaling(&matScale,0.2,0.2,0.2);
		static float index = 0.0f; index+=0.0f; // an ever-increasing float value
		D3DXMatrixRotationX(&matFlipX, (D3DXToRadian(180.0)+index));
		D3DXMatrixRotationY(&matFlipY, (D3DXToRadian(180.0)+index));
		D3DXMatrixTranslation(&matTranslate,xPos,yPos,zPos);

		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matScale*matFlipX*matFlipY*matTranslate));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetTexture( 0, dev->t_buffer );//display the texture
				dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(TEXTUREVERTEX));
				dev->d3ddev->SetIndices(dev->i_buffer);
				// draw
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 6);
				
				dev->cleanBuffers();
				dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_DISABLE);//necassary to prevent blending
				
				dev->d3ddev->SetFVF(CUSTOMFVF);
				
}


void Font::symbol(double xPos,double yPos,double zPos, LPDIRECT3DTEXTURE9** cur)
{
			dev->d3ddev->SetFVF(TEXTUREFVF);
		
			dev->pt_buffer=*cur;
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
			dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);//modulate tells Direct3D to blend the textures colors with the scenes colors
			//if SetTextureStageState is not set to DISABLE then this will continue on into your other objects
			struct TEXTUREVERTEX vertices[] =
			{
				0.0 ,0.0 ,0.0 ,0.01 ,0.01 ,
				48.0 ,0.0 ,0.0 ,0.99 ,0.01 ,
				0.0 ,63.0 ,0.0 ,0.01 ,0.99 ,
				48.0 ,63.0 ,0.0 ,0.99 ,0.99 ,
			};
			dev->d3ddev->CreateVertexBuffer((4)*sizeof(TEXTUREVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

		VOID* pVoid;    // a void pointer
	

		//lock dev->v_buffer and load the vertices into it
		dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, vertices, (4)*sizeof(TEXTUREVERTEX));
		dev->v_buffer->Unlock();

		short indices[] =
		{
			0,1,2,
			1,2,3,
		};

		dev->d3ddev->CreateIndexBuffer(6*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

		// lock dev->i_buffer and load the indices into it
		dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, 6*sizeof(short));
		dev->i_buffer->Unlock(); 

		D3DXMATRIX matFlipX;
		D3DXMATRIX matFlipY;
		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
			
		D3DXMatrixScaling(&matScale,0.2,0.2,0.2);
		static float index = 0.0f; index+=0.0f; // an ever-increasing float value
		D3DXMatrixRotationX(&matFlipX, (D3DXToRadian(180.0)+index));
		D3DXMatrixRotationY(&matFlipY, (D3DXToRadian(180.0)+index));
		D3DXMatrixTranslation(&matTranslate,xPos,yPos,zPos);

		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matScale*matFlipX*matFlipY*matTranslate));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetTexture( 0, *dev->pt_buffer );//display the texture
				dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(TEXTUREVERTEX));
				dev->d3ddev->SetIndices(dev->i_buffer);
				// draw
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
				
				dev->cleanBuffers();
				dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_DISABLE);//necassary to prevent blending
				
				dev->d3ddev->SetFVF(CUSTOMFVF);
				
}

void Font::symbol(double xPos,double yPos,double zPos, LPCSTR filename, double factor)
{
			dev->d3ddev->SetFVF(TEXTUREFVF);
			D3DXCreateTextureFromFileA( (dev->d3ddev), filename, &(dev->t_buffer) );

			dev->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
			dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);//modulate tells Direct3D to blend the textures colors with the scenes colors
			//if SetTextureStageState is not set to DISABLE then this will continue on into your other objects
			struct TEXTUREVERTEX vertices[] =
			{
				0.0 ,0.0 ,0.0 ,0.01 ,0.01 ,
				48.0 ,0.0 ,0.0 ,0.99 ,0.01 ,
				0.0 ,63.0 ,0.0 ,0.01 ,0.99 ,
				48.0 ,63.0 ,0.0 ,0.99 ,0.99 ,
			};
			dev->d3ddev->CreateVertexBuffer((4)*sizeof(TEXTUREVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

		VOID* pVoid;    // a void pointer
	

		//lock dev->v_buffer and load the vertices into it
		dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, vertices, (4)*sizeof(TEXTUREVERTEX));
		dev->v_buffer->Unlock();

		short indices[] =
		{
			0,1,2,
			1,2,3,
		};

		dev->d3ddev->CreateIndexBuffer(6*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

		// lock dev->i_buffer and load the indices into it
		dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, 6*sizeof(short));
		dev->i_buffer->Unlock(); 

		D3DXMATRIX matFlipX;
		D3DXMATRIX matFlipY;
		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
			
		D3DXMatrixScaling(&matScale,0.2*factor,0.2*factor,0.2*factor);
		static float index = 0.0f; index+=0.0f; // an ever-increasing float value
		D3DXMatrixRotationX(&matFlipX, (D3DXToRadian(180.0)+index));
		D3DXMatrixRotationY(&matFlipY, (D3DXToRadian(180.0)+index));
		D3DXMatrixTranslation(&matTranslate,xPos,yPos,zPos);

		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matFlipX*matFlipY*matScale*matTranslate));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetTexture( 0, dev->t_buffer );//display the texture
				dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(TEXTUREVERTEX));
				dev->d3ddev->SetIndices(dev->i_buffer);
				// draw
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 6);
				
				dev->cleanBuffers();
				dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_DISABLE);//necassary to prevent blending
				
				dev->d3ddev->SetFVF(CUSTOMFVF);
}

void Font::symbol(double xPos,double yPos,double zPos, LPDIRECT3DTEXTURE9** cur, double factor)
{
			dev->d3ddev->SetFVF(TEXTUREFVF);
			//D3DXCreateTextureFromFileInMemory( dev->d3ddev, cur->pVoid, (UINT)cur->size, &(dev->t_buffer) );

			dev->pt_buffer=*cur;			
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
			dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);//modulate tells Direct3D to blend the textures colors with the scenes colors
			//if SetTextureStageState is not set to DISABLE then this will continue on into your other objects
			struct TEXTUREVERTEX vertices[] =
			{
				0.0 ,0.0 ,0.0 ,0.01 ,0.01 ,
				48.0 ,0.0 ,0.0 ,0.99 ,0.01 ,
				0.0 ,63.0 ,0.0 ,0.01 ,0.99 ,
				48.0 ,63.0 ,0.0 ,0.99 ,0.99 ,
			};
			dev->d3ddev->CreateVertexBuffer((4)*sizeof(TEXTUREVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

		VOID* pVoid;    // a void pointer
	

		//lock dev->v_buffer and load the vertices into it
		dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, vertices, (4)*sizeof(TEXTUREVERTEX));
		dev->v_buffer->Unlock();

		short indices[] =
		{
			0,1,2,
			1,2,3,
		};

		dev->d3ddev->CreateIndexBuffer(6*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

		// lock dev->i_buffer and load the indices into it
		dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, 6*sizeof(short));
		dev->i_buffer->Unlock(); 

		D3DXMATRIX matFlipX;
		D3DXMATRIX matFlipY;
		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
			
		D3DXMatrixScaling(&matScale,0.2*factor,0.2*factor,0.2*factor);
		static float index = 0.0f; index+=0.0f; // an ever-increasing float value
		D3DXMatrixRotationX(&matFlipX, (D3DXToRadian(180.0)+index));
		D3DXMatrixRotationY(&matFlipY, (D3DXToRadian(180.0)+index));
		D3DXMatrixTranslation(&matTranslate,xPos,yPos,zPos);

		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matFlipX*matFlipY*matScale*matTranslate));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetTexture( 0, *dev->pt_buffer );//display the texture
				dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(TEXTUREVERTEX));
				dev->d3ddev->SetIndices(dev->i_buffer);
				// draw
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
				
				dev->cleanBuffers();
				dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_DISABLE);//necassary to prevent blending
				
				dev->d3ddev->SetFVF(CUSTOMFVF);
}

void Font::titleSymbol(double xPos,double yPos,double zPos, LPDIRECT3DTEXTURE9** cur)
{
			dev->d3ddev->SetFVF(TEXTUREFVF);
		
			
			dev->pt_buffer=*cur;
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			dev->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
			dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);//modulate tells Direct3D to blend the textures colors with the scenes colors
			//if SetTextureStageState is not set to DISABLE then this will continue on into your other objects
			struct TEXTUREVERTEX vertices[] =
			{
				0.0 ,0.0 ,0.0 ,0.0 ,0.0 ,
				821.0 ,0.0 ,0.0 ,1.00 ,0.0 ,
				0.0 ,84.0 ,0.0 ,0.0 ,1.00 ,
				821.0 ,84.0 ,0.0 ,1.00 ,1.00 ,
			};
			dev->d3ddev->CreateVertexBuffer((4)*sizeof(TEXTUREVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

		VOID* pVoid;    // a void pointer
	

		//lock dev->v_buffer and load the vertices into it
		dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, vertices, (4)*sizeof(TEXTUREVERTEX));
		dev->v_buffer->Unlock();

		short indices[] =
		{
			0,1,2,
			1,2,3,
		};

		dev->d3ddev->CreateIndexBuffer(6*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

		// lock dev->i_buffer and load the indices into it
		dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, 6*sizeof(short));
		dev->i_buffer->Unlock(); 

		D3DXMATRIX matFlipX;
		D3DXMATRIX matFlipY;
		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;
			
		D3DXMatrixScaling(&matScale,0.3,0.3,0.3);
		static float index = 0.0f; index+=0.0f; // an ever-increasing float value
		D3DXMatrixRotationX(&matFlipX, (D3DXToRadian(180.0)+index));
		D3DXMatrixRotationY(&matFlipY, (D3DXToRadian(180.0)+index));
		D3DXMatrixTranslation(&matTranslate,xPos,yPos,zPos);

		dev->d3ddev->SetTransform(D3DTS_WORLD, &(matScale*matFlipX*matFlipY*matTranslate));    // set the world transform
	
		// select the vertex buffer to display
		dev->d3ddev->SetTexture( 0, *dev->pt_buffer );//display the texture
				dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(TEXTUREVERTEX));
				dev->d3ddev->SetIndices(dev->i_buffer);
				// draw
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
				
				dev->cleanBuffers();
				dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_DISABLE);//necassary to prevent blending
				
				dev->d3ddev->SetFVF(CUSTOMFVF);
				
}

void Font::renderScore(int score)
{
	int temp;//used to store temporary value
	int digit;//the actual digit to be displayed
	symbol(-140,-110,0,&numTex[0]);

		temp=score%100;
		digit=temp/10;
	switch(digit)//first digit
	{
	case 1:symbol(-130,-110,0,&numTex[1]);
		break;
	case 2:symbol(-130,-110,0,&numTex[2]);
		break;
	case 3:symbol(-130,-110,0,&numTex[3]);
		break;
	case 4:symbol(-130,-110,0,&numTex[4]);
		break;
	case 5:symbol(-130,-110,0,&numTex[5]);
		break;
	case 6:symbol(-130,-110,0,&numTex[6]);
		break;
	case 7:symbol(-130,-110,0,&numTex[7]);
		break;
	case 8:symbol(-130,-110,0,&numTex[8]);
		break;
	case 9:symbol(-130,-110,0,&numTex[9]);
		break;
	case 0:symbol(-130,-110,0,&numTex[0]);
		break;
	}

	score=score-temp;
	temp=score%1000;
	digit=temp/100;
	switch(digit)//second digit
	{
	case 1:symbol(-120,-110,0,&numTex[1]);
		break;
	case 2:symbol(-120,-110,0,&numTex[2]);
		break;
	case 3:symbol(-120,-110,0,&numTex[3]);
		break;
	case 4:symbol(-120,-110,0,&numTex[4]);
		break;
	case 5:symbol(-120,-110,0,&numTex[5]);
		break;
	case 6:symbol(-120,-110,0,&numTex[6]);
		break;
	case 7:symbol(-120,-110,0,&numTex[7]);
		break;
	case 8:symbol(-120,-110,0,&numTex[8]);
		break;
	case 9:symbol(-120,-110,0,&numTex[9]);
		break;
	case 0:symbol(-120,-110,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	temp=score%10000;
	digit=temp/1000;
		switch(digit)//second digit
	{
	case 1:symbol(-110,-110,0,&numTex[1]);
		break;
	case 2:symbol(-110,-110,0,&numTex[2]);
		break;
	case 3:symbol(-110,-110,0,&numTex[3]);
		break;
	case 4:symbol(-110,-110,0,&numTex[4]);
		break;
	case 5:symbol(-110,-110,0,&numTex[5]);
		break;
	case 6:symbol(-110,-110,0,&numTex[6]);
		break;
	case 7:symbol(-110,-110,0,&numTex[7]);
		break;
	case 8:symbol(-110,-110,0,&numTex[8]);
		break;
	case 9:symbol(-110,-110,0,&numTex[9]);
		break;
	case 0:symbol(-110,-110,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	temp=score%100000;
	digit=temp/10000;
			switch(digit)//second digit
	{
	case 1:symbol(-100,-110,0,&numTex[1]);
		break;
	case 2:symbol(-100,-110,0,&numTex[2]);
		break;
	case 3:symbol(-100,-110,0,&numTex[3]);
		break;
	case 4:symbol(-100,-110,0,&numTex[4]);
		break;
	case 5:symbol(-100,-110,0,&numTex[5]);
		break;
	case 6:symbol(-100,-110,0,&numTex[6]);
		break;
	case 7:symbol(-100,-110,0,&numTex[7]);
		break;
	case 8:symbol(-100,-110,0,&numTex[8]);
		break;
	case 9:symbol(-100,-110,0,&numTex[9]);
		break;
	case 0:symbol(-100,-110,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	temp=score%1000000;
	digit=temp/100000;
				switch(digit)//second digit
	{
	case 1:symbol(-90,-110,0,&numTex[1]);
		break;
	case 2:symbol(-90,-110,0,&numTex[2]);
		break;
	case 3:symbol(-90,-110,0,&numTex[3]);
		break;
	case 4:symbol(-90,-110,0,&numTex[4]);
		break;
	case 5:symbol(-90,-110,0,&numTex[5]);
		break;
	case 6:symbol(-90,-110,0,&numTex[6]);
		break;
	case 7:symbol(-90,-110,0,&numTex[7]);
		break;
	case 8:symbol(-90,-110,0,&numTex[8]);
		break;
	case 9:symbol(-90,-110,0,&numTex[9]);
		break;
	case 0:symbol(-90,-110,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	digit=score/1000000;
					switch(digit)//second digit
	{
		
	case 1:symbol(-80,-110,0,&numTex[1]);
		break;
	case 2:symbol(-80,-110,0,&numTex[2]);
		break;
	case 3:symbol(-80,-110,0,&numTex[3]);
		break;
	case 4:symbol(-80,-110,0,&numTex[4]);
		break;
	case 5:symbol(-80,-110,0,&numTex[5]);
		break;
	case 6:symbol(-80,-110,0,&numTex[6]);
		break;
	case 7:symbol(-80,-110,0,&numTex[7]);
		break;
	case 8:symbol(-80,-110,0,&numTex[8]);
		break;
	case 9:symbol(-80,-110,0,&numTex[9]);
		break;
	case 0:symbol(-80,-110,0,&numTex[0]);
		break;
	}	
}

void Font::renderScore(int score,double x,double y)
{
	int temp;//used to store temporary value
	int digit;//the actual digit to be displayed
	symbol(-140+x,-110+y,0,&numTex[0]);

		temp=score%100;
		digit=temp/10;
	switch(digit)//first digit
	{
	case 1:symbol(-130+x,-110+y,0,&numTex[1]);
		break;
	case 2:symbol(-130+x,-110+y,0,&numTex[2]);
		break;
	case 3:symbol(-130+x,-110+y,0,&numTex[3]);
		break;
	case 4:symbol(-130+x,-110+y,0,&numTex[4]);
		break;
	case 5:symbol(-130+x,-110+y,0,&numTex[5]);
		break;
	case 6:symbol(-130+x,-110+y,0,&numTex[6]);
		break;
	case 7:symbol(-130+x,-110+y,0,&numTex[7]);
		break;
	case 8:symbol(-130+x,-110+y,0,&numTex[8]);
		break;
	case 9:symbol(-130+x,-110+y,0,&numTex[9]);
		break;
	case 0:symbol(-130+x,-110+y,0,&numTex[0]);
		break;
	}

	score=score-temp;
	temp=score%1000;
	digit=temp/100;
	switch(digit)//second digit
	{
	case 1:symbol(-120+x,-110+y,0,&numTex[1]);
		break;
	case 2:symbol(-120+x,-110+y,0,&numTex[2]);
		break;
	case 3:symbol(-120+x,-110+y,0,&numTex[3]);
		break;
	case 4:symbol(-120+x,-110+y,0,&numTex[4]);
		break;
	case 5:symbol(-120+x,-110+y,0,&numTex[5]);
		break;
	case 6:symbol(-120+x,-110+y,0,&numTex[6]);
		break;
	case 7:symbol(-120+x,-110+y,0,&numTex[7]);
		break;
	case 8:symbol(-120+x,-110+y,0,&numTex[8]);
		break;
	case 9:symbol(-120+x,-110+y,0,&numTex[9]);
		break;
	case 0:symbol(-120+x,-110+y,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	temp=score%10000;
	digit=temp/1000;
		switch(digit)//second digit
	{
	case 1:symbol(-110+x,-110+y,0,&numTex[1]);
		break;
	case 2:symbol(-110+x,-110+y,0,&numTex[2]);
		break;
	case 3:symbol(-110+x,-110+y,0,&numTex[3]);
		break;
	case 4:symbol(-110+x,-110+y,0,&numTex[4]);
		break;
	case 5:symbol(-110+x,-110+y,0,&numTex[5]);
		break;
	case 6:symbol(-110+x,-110+y,0,&numTex[6]);
		break;
	case 7:symbol(-110+x,-110+y,0,&numTex[7]);
		break;
	case 8:symbol(-110+x,-110+y,0,&numTex[8]);
		break;
	case 9:symbol(-110+x,-110+y,0,&numTex[9]);
		break;
	case 0:symbol(-110+x,-110+y,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	temp=score%100000;
	digit=temp/10000;
			switch(digit)//second digit
	{
	case 1:symbol(-100+x,-110+y,0,&numTex[1]);
		break;
	case 2:symbol(-100+x,-110+y,0,&numTex[2]);
		break;
	case 3:symbol(-100+x,-110+y,0,&numTex[3]);
		break;
	case 4:symbol(-100+x,-110+y,0,&numTex[4]);
		break;
	case 5:symbol(-100+x,-110+y,0,&numTex[5]);
		break;
	case 6:symbol(-100+x,-110+y,0,&numTex[6]);
		break;
	case 7:symbol(-100+x,-110+y,0,&numTex[7]);
		break;
	case 8:symbol(-100+x,-110+y,0,&numTex[8]);
		break;
	case 9:symbol(-100+x,-110+y,0,&numTex[9]);
		break;
	case 0:symbol(-100+x,-110+y,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	temp=score%1000000;
	digit=temp/100000;
				switch(digit)//second digit
	{
	case 1:symbol(-90+x,-110+y,0,&numTex[1]);
		break;
	case 2:symbol(-90+x,-110+y,0,&numTex[2]);
		break;
	case 3:symbol(-90+x,-110+y,0,&numTex[3]);
		break;
	case 4:symbol(-90+x,-110+y,0,&numTex[4]);
		break;
	case 5:symbol(-90+x,-110+y,0,&numTex[5]);
		break;
	case 6:symbol(-90+x,-110+y,0,&numTex[6]);
		break;
	case 7:symbol(-90+x,-110+y,0,&numTex[7]);
		break;
	case 8:symbol(-90+x,-110+y,0,&numTex[8]);
		break;
	case 9:symbol(-90+x,-110+y,0,&numTex[9]);
		break;
	case 0:symbol(-90+x,-110+y,0,&numTex[0]);
		break;
	}	
	score=score-temp;
	digit=score/1000000;
					switch(digit)//second digit
	{
		
	case 1:symbol(-80+x,-110+y,0,&numTex[1]);
		break;
	case 2:symbol(-80+x,-110+y,0,&numTex[2]);
		break;
	case 3:symbol(-80+x,-110+y,0,&numTex[3]);
		break;
	case 4:symbol(-80+x,-110+y,0,&numTex[4]);
		break;
	case 5:symbol(-80+x,-110+y,0,&numTex[5]);
		break;
	case 6:symbol(-80+x,-110+y,0,&numTex[6]);
		break;
	case 7:symbol(-80+x,-110+y,0,&numTex[7]);
		break;
	case 8:symbol(-80+x,-110+y,0,&numTex[8]);
		break;
	case 9:symbol(-80+x,-110+y,0,&numTex[9]);
		break;
	case 0:symbol(-80+x,-110+y,0,&numTex[0]);
		break;
	}	
}

void Font::renderLevel(int level)
{
	symbol(20,-110,0,&letterTex[11]);
	symbol(10,-116,0,&letterTex[21],0.5);
	switch(level)//first digit
	{
		case 1:symbol(4,-110,0,&numTex[1]);
		break;
	case 2:symbol(4,-110,0,&numTex[2]);
		break;
	case 3:symbol(4,-110,0,&numTex[3]);
		break;
	case 4:symbol(4,-110,0,&numTex[4]);
		break;
	case 5:symbol(4,-110,0,&numTex[5]);
		break;
	case 6:symbol(4,-110,0,&numTex[6]);
		break;
	case 7:symbol(4,-110,0,&numTex[7]);
		break;
	case 8:symbol(4,-110,0,&numTex[8]);
		break;
	case 9:symbol(4,-110,0,&numTex[9]);
		break;
	case 10:symbol(8,-110,0,&numTex[1]);
		symbol(-2,-110,0,&numTex[0]);
		break;
	}

}
void Font::renderIntermission(int level)
{
	symbol(20,-0,0,&letterTex[11]);
	symbol(10,-6,0,&letterTex[21],0.5);
	switch(level)//first digit
	{
		case 1:symbol(4,0,0,&numTex[1]);
		break;
	case 2:symbol(4,0,0,&numTex[2]);
		break;
	case 3:symbol(4,0,0,&numTex[3]);
		break;
	case 4:symbol(4,0,0,&numTex[4]);
		break;
	case 5:symbol(4,0,0,&numTex[5]);
		break;
	case 6:symbol(4,0,0,&numTex[6]);
		break;
	case 7:symbol(4,0,0,&numTex[7]);
		break;
	case 8:symbol(4,0,0,&numTex[8]);
		break;
	case 9:symbol(4,0,0,&numTex[9]);
		break;
	case 10:symbol(8,0,0,&numTex[1]);
		symbol(-2,0,0,&numTex[0]);
		break;
	}

}
void Font::pressEnter(double x,double y)
{
	symbol(-35+x,0+y,0,&punctTex[0]);
	symbol(-45+x,0+y,0,&punctTex[0]);
	symbol(-55+x,0+y,0,&punctTex[0]);
	symbol(50+x,0+y,0,&letterTex[15]);
	symbol(40+x,-6+y,0,&letterTex[17],0.5);
	symbol(32+x,-6+y,0,&letterTex[4],0.5);
	symbol(24+x,-6+y,0,&letterTex[18],0.5);
	symbol(16+x,-6+y,0,&letterTex[18],0.5);
	symbol(4+x,0+y,0,&letterTex[4]);
	symbol(-6+x,-6+y,0,&letterTex[13],0.5);
	symbol(-14+x,-6+y,0,&letterTex[19],0.5);
	symbol(-22+x,-6+y,0,&letterTex[4],0.5);
	symbol(-30+x,-6+y,0,&letterTex[17],0.5);

}

void Font::renderWord(string name,double x,double y)
{
	for(int i=0;i<name.length();i++)
	{
		renderLetter(name.substr(i,1),x-(10*i),y);
	}
}

void Font::renderLetter(string letter,double x, double y)
{
	char* cLetter;
	cLetter=new char;
	strcpy(cLetter,letter.c_str());
	switch(*cLetter)
	{
	case 'A':symbol(x,y,0,&letterTex[0]);
		break;
	case 'a':symbol(x,y,0,&letterTex[0],0.5);
		break;

	case 'B':symbol(x,y,0,&letterTex[1]);
		break;
	case 'b':symbol(x,y,0,&letterTex[1],0.5);
		break;

	case 'C':symbol(x,y,0,&letterTex[2]);
		break;
	case 'c':symbol(x,y,0,&letterTex[2],0.5);
		break;

	case 'D':symbol(x,y,0,&letterTex[3]);
		break;
	case 'd':symbol(x,y,0,&letterTex[3],0.5);
		break;

	case 'E':symbol(x,y,0,&letterTex[4]);
		break;
	case 'e':symbol(x,y,0,&letterTex[4],0.5);
		break;

	case 'F':symbol(x,y,0,&letterTex[5]);
		break;
	case 'f':symbol(x,y,0,&letterTex[5],0.5);
		break;

	case 'G':symbol(x,y,0,&letterTex[6]);
		break;
	case 'g':symbol(x,y,0,&letterTex[6],0.5);
		break;

	case 'H':symbol(x,y,0,&letterTex[7]);
		break;
	case 'h':symbol(x,y,0,&letterTex[7],0.5);
		break;

	case 'I':symbol(x,y,0,&letterTex[8]);
		break;
	case 'i':symbol(x,y,0,&letterTex[8],0.5);
		break;

	case 'J':symbol(x,y,0,&letterTex[9]);
		break;
	case 'j':symbol(x,y,0,&letterTex[9],0.5);
		break;

	case 'K':symbol(x,y,0,&letterTex[10]);
		break;
	case 'k':symbol(x,y,0,&letterTex[10],0.5);
		break;

	case 'L':symbol(x,y,0,&letterTex[11]);
		break;
	case 'l':symbol(x,y,0,&letterTex[11],0.5);
		break;

	case 'M':symbol(x,y,0,&letterTex[12]);
		break;
	case 'm':symbol(x,y,0,&letterTex[12],0.5);
		break;

	case 'N':symbol(x,y,0,&letterTex[13]);
		break;
	case 'n':symbol(x,y,0,&letterTex[13],0.5);
		break;

	case 'O':symbol(x,y,0,&letterTex[14]);
		break;
	case 'o':symbol(x,y,0,&letterTex[14],0.5);
		break;

	case 'P':symbol(x,y,0,&letterTex[15]);
		break;
	case 'p':symbol(x,y,0,&letterTex[15],0.5);
		break;

	case 'Q':symbol(x,y,0,&letterTex[16]);
		break;
	case 'q':symbol(x,y,0,&letterTex[16],0.5);
		break;

	case 'R':symbol(x,y,0,&letterTex[17]);
		break;
	case 'r':symbol(x,y,0,&letterTex[17],0.5);
		break;

	case 'S':symbol(x,y,0,&letterTex[18]);
		break;
	case 's':symbol(x,y,0,&letterTex[18],0.5);
		break;

	case 'T':symbol(x,y,0,&letterTex[19]);
		break;
	case 't':symbol(x,y,0,&letterTex[19],0.5);
		break;

	case 'U':symbol(x,y,0,&letterTex[20]);
		break;
	case 'u':symbol(x,y,0,&letterTex[20],0.5);
		break;

	case 'V':symbol(x,y,0,&letterTex[21]);
		break;
	case 'v':symbol(x,y,0,&letterTex[21],0.5);
		break;

	case 'W':symbol(x,y,0,&letterTex[22]);
		break;
	case 'w':symbol(x,y,0,&letterTex[22],0.5);
		break;

	case 'X':symbol(x,y,0,&letterTex[23]);
		break;
	case 'x':symbol(x,y,0,&letterTex[23],0.5);
		break;

	case 'Y':symbol(x,y,0,&letterTex[24]);
		break;
	case 'y':symbol(x,y,0,&letterTex[24],0.5);
		break;

	case 'Z':symbol(x,y,0,&letterTex[25]);
		break;
	case 'z':symbol(x,y,0,&letterTex[25],0.5);
		break;

	case ':':symbol(x,y,0,&punctTex[1]);
		break;
	case '.':symbol(x,y,0,&punctTex[0]);
		break;

	default:break;
	}
}
void Font::renderTitle()
{
	titleSymbol(120,50,0,&titleTex);
}