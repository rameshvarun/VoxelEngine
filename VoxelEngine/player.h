


#include "bullet.h"



#include "bot.h"



class Player
{
public:

	float x;
	float y;
	float z;

	float oldX;
	float oldY;
	float oldZ;

	float time1;

	float time2;

	float hp;

	sf::String txt;

	Player(float xPos, float yPos, float zPos)
	{
		x = xPos;
		y = yPos;
		z = zPos;

		oldX = x;
		oldY = y;
		oldZ = z;

		time1 = 0;

		time2 = 0;

		hp = MAXHP;

		stringstream h;
		h << "Player: " << hp;

		txt = sf::String(h.str().c_str(),sans,35.f);
	}

	void Draw()
	{
		if(hp > 0)
		{

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		cam.Render();

		glTranslatef(x, y, z);

		float size = 1.0f;

		float h = 4.0f;

		float col[] = {1.0f, 0.0f, 0.0f, 1.0f};

		bool s = false;

		int l = 1;
		while(true)
		{
			if(x-l < 0 || (-(y-1))-l < 0 || z-l < 0)
			{
				break;
			}
			if(type[(int)x-l][(int)(-(y-1))-l][(int)z-l] != 0)
			{
				s = true;
				break;
			}
			++l;
		}

		
		if(s)
		{
			col[0] *= 0.5;
			col[1] *= 0.5;
			col[2] *= 0.5;
		}


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

		for(list<Bullet*>::iterator it = b.begin(); it != b.end(); ++it)
		{
			(*it)->Draw();
		}

		window.Draw(txt);

		}
		else
		{
			x = -100;
		}
		
	}

	void Update(float dt)
	{
		if(hp > 0)
		{

		y = 1;

		for(int i = 0; i < MAP_DEPTH; ++i)
		{
			if(type[(int)x][i][(int)z] > 0)
			{
				break;

			}
			y = -i;
		}

		if(x < 0)
		{
			x = 0;
		}
		if(z < 0)
		{
			z = 0;
		}
		if(x > MAP_LENGTH-1)
		{
			x = MAP_LENGTH-1;
		}
		if(z > MAP_WIDTH-1)
		{
			z = MAP_WIDTH-1;
		}
		
		if(y - oldY > 2)
		{
			x = oldX;
			y = oldY;
			z = oldZ;
		}

		oldX = x;
		oldY = y;
		oldZ = z;

		cam.posX = x;
		cam.posY = z;


		float move = 6.0f;

		if(input.IsKeyDown(Key::W))
		{
			x -= dt*move;
			z -= dt*move;
		}

		if(input.IsKeyDown(Key::S))
		{
			x += dt*move;
			z += dt*move;
		}

		if(input.IsKeyDown(Key::D))
		{
			x += dt*move;
			z -= dt*move;
		}

		if(input.IsKeyDown(Key::A))
		{
			x -= dt*move;
			z += dt*move;
		}

		
		if(input.IsMouseButtonDown(sf::Mouse::Right) && time1 > 2)
		{
			SetSphere(x,-(y+5),z,10,0);
			BuildVis();
			BuildLight();
			
			exp2->play();

			time1 = 0;
		}

#ifdef EDIT
		
		if(input.IsKeyDown(Key::F1))
		{
			SaveFile("level.txt");
		}
#endif

		if(input.IsMouseButtonDown(sf::Mouse::Left) && time2 > 0.3)
		{
			shoot->play();

			float rot = lookAt(400,300,input.GetMouseX(),input.GetMouseY());

			float off = -90-45;

			b.push_back(new Bullet(x,y+1,z, sin(ToRad(rot+off)) , cos(ToRad(rot+off)), 0));

			time2 = 0;
		}

		

		time1 += dt;
		time2 += dt;



		stringstream h;
		h << "Player: " << hp;

		txt.SetText(h.str().c_str());

		}

		for(list<Bullet*>::iterator it = b.begin(); it != b.end(); ++it)
		{
			if( (*it)->Update(dt) == 0)
			{
				break;
			}
		}


	}

	bool collide(float bx, float by, float bz)
	{

		if( abs((int)x - (int)bx) < 2 && abs((int)y - (int)by) < 4 && abs((int)z - (int)bz) < 2)
		{
			return true;
		}
		return false;
	}

};

