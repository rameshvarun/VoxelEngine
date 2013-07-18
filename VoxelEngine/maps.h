

void Canyon()
{

#pragma region OldMap

	/*SetMap(1);


	srand(time(NULL));


	for(int x = 1; x < MAP_LENGTH-1; ++x)
	{
		
			for(int z = 1; z < MAP_WIDTH-1; ++z)
			{
				if(rand() % 10 < 9)
				{
					for(int y = 0; y < rand() % 8; ++y)
					{
						type[x][y][z] = 2;
					}
				}
			}
	}

	for(int x = 1; x < MAP_LENGTH-1; ++x)
	{
		
			for(int z = 1; z < MAP_WIDTH-1; ++z)
			{
				if(rand() % 10 < 2)
				{
					for(int y = 0; y < rand() % 3; ++y)
					{
						type[x][y][z] = 0;
					}
				}
			}
	}

	SetLowerThanY(10,3);

	SetRect(50,0,50,20,10,5,0);
	

	SetSphere( 20,-5, 20, 12, 0);
	SetSphere( 25,-4, 22, 12, 0);
	SetSphere( 30,-3, 24, 12, 0);

	SetSphere( 35,-2, 25, 12, 0);
	*/
#pragma endregion

	LoadFile("levels//canyon.txt");

	TypeToColor(1,0.61f,0.35f,0.24f);
	TypeToColor(2,0 , 0.40f,0);
	TypeToColor(3,0.40f , 0.40f,0.40f);


	StartMap(50,50);
}

void Ice()
{
	//SetMap(1);

	LoadFile("levels//ice.txt");

	//SetLowerThanY(10,3);

	TypeToColor(3,0, 0, 0.50f);

	TypeToColor(1,0.9f,0.9f,0.9f);

	StartMap(50,50);
}

void Island()
{
	LoadFile("levels//island.txt");

	SetLowerThanY(10,3);

	TypeToColor(1,0,0.6f,0.0f);
	
	TypeToColor(2,0.89f, 0.66f, 0.48f);

	TypeToColor(3,0.0f,0.0f,0.5f);

	StartMap(50,50);
}