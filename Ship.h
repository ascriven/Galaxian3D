class ship{
	private:
		cDirect3D *dev;//pointer to the direct3d device class used for drawing

		float xPosition;//these are used to modify the ships position
		float yPosition;
		float zPosition;
		float shipBox[4];
		float pivot;//used to pivot the ship to the left or right depending on the direction it's going

		float shipAngle;//used to pivot the ship when displaying the score
		bool shipAngleDirection;

		float increment;
		float explodeRotate;//explosion stuff


		
		float bulletDistance;//this is the bullets current distance away from it's rest position
		float bulletMaxDistance;//this is the end of the screen if the bullet hits here it resets
		float xBulletPosition;//when the bullet is fired xposition is stored
		
		float bulletBox[4];//this holds the bullet boundary box it is calculated when bulletBox() function is called
		float bulletSpeed;//speed of the bullet

		void Bullet(void);
		void ShipGraphic(void);
		void Engine(void);
		void renderLife(int x, int y);

		void handleBulletMove(void);//handles bullet position and resets the bullet distance
	public:
		bool bulletFired;//this variable is used to tell whether the bullet is being fired
		bool explode;//sets the ship to explode
		bool exist;
		
		//initializes all variables to zero
		ship(cDirect3D* d3ddev);
		//graphical implementation
		void resetShip(void);//resets the ship after death
		void renderShip(void);
		void shipMove(float x);//moves the ships locataion by x amount
		void fire(void); //fires the bullet
		void returnBullet(void);
		float* returnBulletBox(void);//calculates bullet box and returns a pointer to an array
		float* returnShipBox(void);//calculates bound box and returns a pointer to an array
		void showLives(int lives);
		void renderScore(int x,int y);
		
};

