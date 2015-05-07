class cDirect3D{//class contains all necessary functions and variables for working with direct3d
public:
		LPDIRECT3D9 d3d;
		LPDIRECT3DDEVICE9 d3ddev;
		LPDIRECT3DVERTEXBUFFER9 v_buffer;    // the pointer to the vertex buffer
		LPDIRECT3DINDEXBUFFER9 i_buffer;    // the pointer to the index buffer
		LPDIRECT3DTEXTURE9 t_buffer;	//pointer to the texture buffer
		LPDIRECT3DTEXTURE9 *pt_buffer;

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		DWORD CUSTOMFVF;//original FVF for xyz color
		DWORD CUSTOMFVF2;//secondory for xyz+text1

		cDirect3D(int width,int height,DWORD FVF)
		{
			SCREEN_WIDTH=width;
			SCREEN_HEIGHT=height;
			CUSTOMFVF=FVF;
		}
		void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	

    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);

   
    d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
    d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // turn off culling originally set to no culling D3DCULL_NONE
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
}

		void begin_frame()
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();

    d3ddev->SetFVF(CUSTOMFVF);

    // set the view transform
    D3DXMATRIX matView;    // the view transform matrix
    D3DXMatrixLookAtLH(&matView,
    &D3DXVECTOR3 (0.0f, 8.0f, 275.0f),    // the camera position was 0,8,250
    &D3DXVECTOR3 (0.0f, -15.0f, 0.0f),      // the look-at position was 0,0,0
    &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction
    d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView 

	 
	

    // set the projection transform
    D3DXMATRIX matProjection;    // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),    // the horizontal field of view
                               (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
                               100.0f,   // the near view-plane
                               400.0f);    // the far view-plane
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection); // set the projection
}



		void end_frame()
{
	d3ddev->EndScene(); 
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//cleanBuffers();
}
		void cleanBuffers(void)//buffers must be released after the creation of each object otherwise program allocates huge amounts of memory(a leak)
{
	if(v_buffer!=NULL)
		v_buffer->Release();
	if(i_buffer!=NULL)
		i_buffer->Release();
	if(pt_buffer!=NULL)
		pt_buffer=NULL;
	else if(t_buffer!=NULL)
	{
		t_buffer->Release();
		t_buffer=NULL;
	}

}

		void cleanD3D(void)
{
    v_buffer->Release();
    i_buffer->Release();	
	if(!t_buffer==NULL)
		t_buffer->Release();
    d3ddev->Release();
    d3d->Release();
}


};
