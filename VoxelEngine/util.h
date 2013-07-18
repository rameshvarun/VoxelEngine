GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 1.0, 1.0, 1.0, 0.0 };

void GLInitStuff()
{
	glEnable(GL_CULL_FACE);

	glClearDepth(1.0f);
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, ((float)window.GetWidth() /window.GetHeight()) ,1.0f,1000.0f);

	window.PreserveOpenGLStates(true);

	window.SetCursorPosition(window.GetWidth()/2,window.GetHeight()/2);
}

void SetMap(int t)
{
	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		
			for(int z = 0; z < MAP_WIDTH; ++z)
			{
					for(int y = 0; y < MAP_DEPTH; ++y)
					{
						type[x][y][z] = t;
					}
				
			}
	}
}

void SetSphere(int xPos,int yPos,int zPos, float rad, int t)
{
	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		for(int y = 0; y < MAP_DEPTH; ++y)
		{
			for(int z = 0; z < MAP_WIDTH; ++z)
			{

				float dist = sqrt((double)(sq(xPos-x) + sq(yPos-y) + sq(zPos-z)));

				if(dist < rad)
				{
					type[x][y][z] = t;
				}
			}
		}
	}
}

void SetRect(int xPos,int yPos,int zPos,int width,int length,int depth,int t)
{
	for(int x = xPos; x < xPos + width; ++x)
	{

		for(int y = yPos; y < yPos + depth; ++y)
		{

			for(int z = zPos; z < zPos + length; ++z)
			{
				if(x < MAP_LENGTH && z < MAP_WIDTH && y < MAP_DEPTH)
				{
					type[x][y][z] = t;
				}
			}
		}
	}
}

void TypeToColor(int t, float r, float g, float b)
{
	for(int x = 0; x < MAP_LENGTH; ++x)
	{

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
					for(int y = 0; y < MAP_DEPTH; ++y)
					{
						if(type[x][y][z] == t)
						{
							color[x][y][z] = Vector3f(r + float(rand() % 100)*0.0005f , g + float(rand() % 100)*0.0005f, b + float(rand() % 100)*0.0005f);
						}
					}
			}
	}
}

void SetLowerThanY(float yPos, int t)
{
	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		
			for(int z = 0; z < MAP_WIDTH; ++z)
			{
					for(int y = yPos; y < MAP_DEPTH; ++y)
					{
						type[x][y][z] = t;
					}
				
			}
	}
}

void SaveFile(const char* filename)
{
	ofstream file;

	file.open(filename);

	for(int x = 0; x < MAP_LENGTH; ++x)
	{

		for(int y = 0; y < MAP_DEPTH; ++y)
		{

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				file << type[x][y][z] << " ";
			}
		}
	}

	file.close();
}

void LoadFile(const char* filename)
{
	ifstream file;

	file.open(filename);

	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		for(int y = 0; y < MAP_DEPTH; ++y)
		{
			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				int t;

				file >> t;

				type[x][y][z] = t;
			}
		}
	}

	file.close();
}