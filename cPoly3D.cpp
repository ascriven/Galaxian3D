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
using namespace std;
struct TEXTUREVERTEX{float X, Y, Z;float TU, TV;};//define texture vertex structure
#include "cPoly3D.h"
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_TEX1)//for Textures
#endif

void cPoly3D::readFile()
	{
		string line;//the string for line
		string partline;//to break up line to more manageable parts
		char * pEnd;//points to the end of string where last double was found
		ifstream objectfile(filename.c_str());//ifstream object
	
	if (objectfile.is_open())//handles file reading
	{
		while (! objectfile.eof() )
		{
		 getline (objectfile,line);
		if(line[0]=='v')//do vertices functions
		{
			partline=line.substr(3,line.length());//this area here is repeated in the indices section what it does is takes the line and 
												//converts it to partline containing only the double values beginnging at the double values
		
			aVertices[iVertices]=strtod(partline.c_str(),&pEnd);//then it's converted to a cstring which is converted to doubles and stored in aVertices array
			iVertices++;
			aVertices[iVertices]=strtod(pEnd,&pEnd);
			iVertices++;
			aVertices[iVertices]=strtod(pEnd,NULL);
			iVertices++;//index will be 1 bigger than necassary

		}
		else if(line[0]=='f')//do indices functions
		{
			 partline=line.substr(2,line.length());
			
			aIndices[iIndices]=short(strtod(partline.c_str(),&pEnd))-1;
			iIndices++;
			aIndices[iIndices]=short(strtod(pEnd,&pEnd))-1;
			iIndices++;
			aIndices[iIndices]=short(strtod(pEnd,NULL))-1;
			iIndices++;//same here index will be 1 bigger than necassary
		}
		else
		{
		}
      
		}
		objectfile.close();
	}
	else
	{
	}

	xAlign=aVertices[0], yAlign=aVertices[1], zAlign=aVertices[2];//must start at a real vertex value assign a value
	TEXTUREVERTEX hold;
	int counter=0;
  
	while(counter<(iVertices/3))
	{
	  
		hold.X=float(aVertices[(counter*3)]);
		hold.Y=float(aVertices[(counter*3)+1]);
		hold.Z=float(aVertices[(counter*3)+2]);
		hold.TU=0;
		hold.TV=0;
		vertices[counter]= hold ;
		 //Need to find the largest x, y and z coords of this object so we can translate it to the center later
		 if(xAlign<hold.X)
		 {
			  xAlign=hold.X;
		 }
		 	  if(yAlign<hold.Y)
		 {
			  yAlign=hold.Y;
		 }
		 if(zAlign<hold.Z)
		 {
			  zAlign=hold.Z;
		 }

		 counter+=1;
	 }

	}
void cPoly3D::prepPoly()
	{
		
		dev->d3ddev->CreateVertexBuffer((iVertices/3)*sizeof(TEXTUREVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &dev->v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer
	

    // lock dev->v_buffer and load the vertices into it
    dev->v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, (iVertices/3)*sizeof(TEXTUREVERTEX));
    dev->v_buffer->Unlock();


	dev->d3ddev->CreateIndexBuffer(iIndices*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &dev->i_buffer,
                              NULL);

    // lock dev->i_buffer and load the indices into it
    dev->i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, aIndices, iIndices*sizeof(short));
    dev->i_buffer->Unlock(); 
	}
void cPoly3D::renderPoly()
	{
			dev->d3ddev->SetFVF(TEXTUREFVF);
			loadTexture();//prepare the texture
			
			prepPoly();
			
			D3DXMATRIX matTranslate;    // a matrix to store the translation information
			D3DXMATRIX matFlip;
			D3DXMATRIX matScale;
			D3DXMatrixScaling(&matScale,01.1,01.1,01.1);

			D3DXMatrixTranslation(&matTranslate, -xAlign, -yAlign, -zAlign);
			static float index = 0.0f; index+=0.00f; // an ever-increasing float value
				D3DXMatrixRotationY(&matFlip, (D3DXToRadian(180.0)+index));
				// the rotation matrix
				dev->d3ddev->SetTransform(D3DTS_WORLD, &(matTranslate*matFlip*matScale));    // set the world transform
	
				// select the vertex buffer to display
				dev->d3ddev->SetTexture( 0, dev->t_buffer );//display the texture
				dev->d3ddev->SetStreamSource(0, dev->v_buffer, 0, sizeof(TEXTUREVERTEX));
				dev->d3ddev->SetIndices(dev->i_buffer);
				// draw
				dev->d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (iVertices/3), 0, (iIndices/3));
				
				dev->cleanBuffers();
				dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_DISABLE);//necassary to prevent blending
				
				dev->d3ddev->SetFVF(CUSTOMFVF);
				
	}
void cPoly3D::loadTexture( void )
	{
		D3DXCreateTextureFromFileA( (dev->d3ddev), "Font\9.png", &(dev->t_buffer) );

		dev->d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		dev->d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		dev->d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
		dev->d3ddev->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);//modulate tells Direct3D to blend the textures colors with the scenes colors
		//if SetTextureStageState is not set to DISABLE then this will continue on into your other objects
	}