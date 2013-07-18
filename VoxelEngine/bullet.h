

class Bullet
{
public:

	float x, y, z;
	float dX, dY;

	int side;

	Bullet(float xPos, float yPos, float zPos, float dirX, float dirY, int s)
	{
		x = xPos;
		y = yPos;
		z = zPos;

		dX = dirX;
		dY = dirY;

		side = s;

	}

	void Draw()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		cam.Render();

		glTranslatef(x, y, z);

		float size = 0.5f;

		float h = 0.5f;

		float col[] = {1.0f, 1.0f, 1.0f, 1.0f};


		glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

		glBegin(GL_QUADS);


		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0,  size);	// Point 1 (Front)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( size, 0,  size);	// Point 2 (Front)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size*h,  size);	// Point 3 (Front)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  size*h,  size);	// Point 4 (Front)


		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);	// Point 1 (Back)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0,  size*h, 0);	// Point 2 (Back)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size*h, 0);	// Point 3 (Back)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size, 0, 0);	// Point 4 (Back)


		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  size*h, 0);	// Point 1 (Top)
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0,  size*h,  size);	// Point 2 (Top)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size*h,  size);	// Point 3 (Top)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size*h, 0);	// Point 4 (Top)


		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0);	// Point 1 (Bottom)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( size, 0, 0);	// Point 2 (Bottom)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size, 0,  size);	// Point 3 (Bottom)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0,  size);	// Point 4 (Bottom)


		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(1.0f, 0.0f); glVertex3f( size, 0, 0);	// Point 1 (Right)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size*h, 0);	// Point 2 (Right)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size*h,  size);	// Point 3 (Right)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size, 0,  size);	// Point 4 (Right)


		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);	// Point 1 (Left)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0,  size);	// Point 2 (Left)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0,  size*h,  size);	// Point 3 (Left)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  size*h, 0);	// Point 4 (Left)



		glEnd();
	}

	int Update(float dt);
};

list<Bullet*> b = list<Bullet*>();

int Bullet::Update(float dt)
{
	if(x < 0)
	{
		b.remove(this);
		return 0;
	}
	if(z < 0)
	{
		b.remove(this);
		return 0;
	}
	if(x > MAP_LENGTH-1)
	{
		b.remove(this);
		return 0;
	}
	if(z > MAP_WIDTH-1)
	{
		b.remove(this);
		return 0;
	}
	if(y > 0)
	{
		y = 0;
	}

	if(type[(int)x][-(int)y][(int)z])
	{
		SetSphere(x,-y,z,3,0);

		BuildVis();
		BuildLight();

		exp1->play();

		b.remove(this);
		return 0;
	}


	float move = 20;

	x += move*dt*dX;
	z += move*dt*dY;


	return 1;
}