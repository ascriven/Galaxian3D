
class star
{
private:
	cDirect3D *dev;//pointer to the direct3d device class used for drawing
	
	float xStar, yStar, scale;
	float twinkle;
	bool  tFlag;

	void starBase(void);//draws stars base
	void starHV(void);//draws stars horizontal and vertical points
	void starAngle(void);//draws stars diagonal points
	void starTwinkle(void);
	
public://to do
	star();
	star(cDirect3D* d3ddev,float x,float y,int distance);//points to cDirect3D must be done and sets stars x, y co-ords and distance(1,2 or 3)
	void initStar(cDirect3D* d3ddev,float x,float y,int distance);//same as constructor
	void starDraw(void);//renders star
};