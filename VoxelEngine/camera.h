

class Camera
{
public:

	sf::Vector3f pos;
	sf::Vector3f target;
	sf::Vector3f up;

	float posX;
	float posY;


	Camera()
	{
		pos = sf::Vector3f(10,0,0);
		target = sf::Vector3f(0,0,0);
		up = sf::Vector3f(0,1,0);

		posX = 0;
		posY = 0;
	
	}

	void SetPos(float x, float y, float z)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	void LookAt(float x, float y, float z)
	{
		target.x = x;
		target.y = y;
		target.z = z;
	}

	void Up(float x, float y, float z)
	{
		up.x = x;
		up.y = y;
		up.z = z;
	}

	void Render()
	{
		gluLookAt(pos.x,pos.y,pos.z,target.x,target.y,target.z,up.x,up.y,up.z);

	}

	void Update(float dt)
	{
		float zoom = 10;

		target.x = posX;
		target.z = posY;
		target.y = 0;

		pos.x = posX+zoom;
		pos.z = posY+zoom;
		pos.y = zoom*3;

		float move = dt*10;

		if(input.GetMouseX() > window.GetWidth()*0.6 )
		{
			posX += move;
			posY -= move;
		}

		if(input.GetMouseX() < window.GetWidth()*0.4 )
		{
			posX -= move;
			posY += move;
		}

		if(input.GetMouseY() > window.GetHeight()*0.6 )
		{
			posX += move;
			posY += move;
		}

		if(input.GetMouseY() < window.GetHeight()*0.4 )
		{
			posX -= move;
			posY -= move;
		}
	}
};

Camera cam;