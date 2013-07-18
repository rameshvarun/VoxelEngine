


void InitVox()
{
	GLInitStuff();

	sans.LoadFromFile("FreeSansBold.ttf");

	type = new int**[(int)MAP_LENGTH];

	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		type[x] = new int*[(int)MAP_DEPTH];

		for(int y = 0; y < MAP_DEPTH; ++y)
		{
			type[x][y] = new int[(int)MAP_WIDTH];

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				type[x][y][z] = 1;
			}
		}
	}

	visible = new bool**[(int)MAP_LENGTH];

	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		visible[x] = new bool*[(int)MAP_DEPTH];

		for(int y = 0; y < MAP_DEPTH; ++y)
		{
			visible[x][y] = new bool[(int)MAP_WIDTH];

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				visible[x][y][z] = true;
			}
		}
	}

	color = new Vector3f**[(int)MAP_LENGTH];

	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		color[x] = new Vector3f*[(int)MAP_DEPTH];

		for(int y = 0; y < MAP_DEPTH; ++y)
		{
			color[x][y] = new Vector3f[(int)MAP_WIDTH];

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				color[x][y][z] = Vector3f(1,1,1);
			}
		}
	}

	shadow = new bool**[(int)MAP_LENGTH];

	for(int x = 0; x < MAP_LENGTH; ++x)
	{
		shadow[x] = new bool*[(int)MAP_DEPTH];

		for(int y = 0; y < MAP_DEPTH; ++y)
		{
			shadow[x][y] = new bool[(int)MAP_WIDTH];

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				shadow[x][y][z] = false;
			}
		}
	}


}

void BuildLight()
{

	for(int x = 0; x < MAP_LENGTH; ++x)
	{

		for(int y = 0; y < MAP_DEPTH; ++y)
		{

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				shadow[x][y][z] = false;
			}
		}
	}


	for(int x = 0; x < MAP_LENGTH; ++x)
	{

		for(int y = 0; y < MAP_DEPTH; ++y)
		{

			for(int z = 0; z < MAP_WIDTH; ++z)
			{
				int l = 1;
				while(true)
				{
					if(x-l < 0 || y-l < 0 || z-l < 0)
					{
						break;
					}

					if(type[x-l][y-l][z-l] != 0)
					{
						shadow[x][y][z] = true;

						break;
					}

					++l;
				}
			}
		}
	}
}

void BuildVis()
{
	for(int x = 1; x < MAP_LENGTH-1; ++x)
	{
		for(int y = 1; y < MAP_DEPTH-1; ++y)
		{
			for(int z = 1; z < MAP_WIDTH-1; ++z)
			{
				visible[x][y][z] = false;

				if(type[x + 1][y][z] == 0)
				{
					visible[x][y][z] = true;
				}
				if(type[x - 1][y][z] == 0)
				{
					visible[x][y][z] = true;
				}

				if(type[x][y + 1][z] == 0)
				{
					visible[x][y][z] = true;
				}
				if(type[x][y - 1][z] == 0)
				{
					visible[x][y][z] = true;
				}

				if(type[x][y][z + 1] == 0)
				{
					visible[x][y][z] = true;
				}
				if(type[x][y][z - 1] == 0)
				{
					visible[x][y][z] = true;
				}
				
			}
		}
	}
}





void DrawVoxel(float x, float y, float z, float size, Vector3f c,bool s)
{
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	cam.Render();

	glTranslatef(x, y, z);

	glBindTexture(GL_TEXTURE_2D, tex1);

	float col[] = {c.x, c.y, c.z, 1.0f};

	if(s)
	{
		col[0] *= 0.5f;
		col[1] *= 0.5f;
		col[2] *= 0.5f;
	}

	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

	glBegin(GL_QUADS);

	

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0,  size);	// Point 1 (Front)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( size, 0,  size);	// Point 2 (Front)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);	// Point 3 (Front)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  size,  size);	// Point 4 (Front)


		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0);	// Point 1 (Back)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0,  size, 0);	// Point 2 (Back)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, 0);	// Point 3 (Back)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size, 0, 0);	// Point 4 (Back)


		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  size, 0);	// Point 1 (Top)
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0,  size,  size);	// Point 2 (Top)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);	// Point 3 (Top)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, 0);	// Point 4 (Top)


		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0);	// Point 1 (Bottom)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( size, 0, 0);	// Point 2 (Bottom)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size, 0,  size);	// Point 3 (Bottom)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0,  size);	// Point 4 (Bottom)


		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(1.0f, 0.0f); glVertex3f( size, 0, 0);	// Point 1 (Right)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, 0);	// Point 2 (Right)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);	// Point 3 (Right)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size, 0,  size);	// Point 4 (Right)


		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);	// Point 1 (Left)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0,  size);	// Point 2 (Left)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0,  size,  size);	// Point 3 (Left)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  size, 0);	// Point 4 (Left)



	glEnd();
}