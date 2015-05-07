class enemyShip
{
private:
		cDirect3D *dev;//pointer to the direct3d device class used for drawing

		float xPosition;//these are used to modify the ships position
		float yPosition;
		float zPosition;
		float shipAngle;//angle of the ship in z direction 
		bool  shipAngleDirection;//true=right false=left
		float rotIndex;//controls angle and rotation of enemy ship in x direction
		float boundBox[4];//bound box of enemy ship

		float attackX;//co-ordinates during movement
		float attackY;
		float attackXMove;//speed
		float attackYMove;

		 
		float increment;

		int colorTip[3];//these contain the values of the colors, the middle tip
		int colorMid[3];//outside edges of middle/inside edges of wings
		int colorOut[3];//outside edges of wings

		float bulletTrig1;//tells when the first bullet should be fired during an attack
		float bulletTrig2;//tells when the second bullet should be fired during an attack
		float bulletDistance1;//this is the bullets current distance away from it's rest position
		float bulletDistance2;
		float bulletMaxDistance;//this is the end of the screen if the bullet hits here it resets
		float bulletX1;//when the bullet is fired xposition is stored
		float bulletX2;
		float bulletBox1[4];//bullet bounding box
		float bulletBox2[4];


		void colorSet(int color);
		int score;//holds the score value for this enemy
		void attackControl(void);
		void RotateControl(void);
		void bulletControl(void);

		void enemyShipMain(void);//graphics
		void enemyShipWing(void);
		void enemyBullet(void);//enemy bullet graphic


public:
		bool exist;//does the ship still exist?
		bool explode;//variables for explosion
		bool attack;//is this ship attacking?
		bool endattack;//the ships attack is over
		bool bulletFlag1;//this variable is used to tell whether the bullet is being fired
		bool bulletFlag2;

		enemyShip();//empty constructor
		int returnScore();//returns the enemies score value
		void initShip(cDirect3D* d3ddev,float x,float y, int color);//constructor
		void renderEnemyShip(void);//renders the enemy ship		
		float* returnBulletBox1(void);
		float* returnBulletBox2(void);
		void enemyExplode(void);
		void enemyFire(void);//tells the enemy to shoot a bullet from it's current position
		float* returnBoundBox(void);//calculates bound box and returns a pointer to an array
		float getX(void);//returns x position
		void  enemyShipMove(float x);//moves the enemyShip
		void initAttack(double bullet1,double bullet2);//initiate attack animation
};