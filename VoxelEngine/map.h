int StartMap(float x, float z)
{
	menu->stop();
	mapm->play();

	Player player = Player(x,1,z);

	Bot bot1 = Bot(x+40,1,z,1);

	Bot bot2 = Bot(x-40,1,z,2);

	Bot bot3 = Bot(x,1,z+40,3);

	BuildVis();

	BuildLight();

	PostFX bloom;
	bloom.LoadFromFile("bloom.sfx");
	bloom.SetTexture("framebuffer",NULL);


	cam = Camera();

	cam.SetPos(100,0,100);

	sf::Clock Clock;

	sf::String win("",sans,35.0f);
	win.SetPosition(Vector2f(400-100,300));

	float wintime = 0;

	bool pause = false;

	while(window.IsOpened())
	{
		sf::Event e;

		while(window.GetEvent(e))
		{
			if(e.Type == Event::Closed)
			{
				window.Close();
			}

			if(e.Type == Event::KeyPressed)
			{
				if(e.Key.Code == Key::Escape)
				{
					window.Close();
				}
				if(e.Key.Code == Key::F)
				{
					fullscreen = !fullscreen;

					window.Close();

					if(fullscreen)
					{
						window.Create(sf::VideoMode(800,600, 32), "Voxel Terrain Engine",Style::Fullscreen);
					}
					else
					{
						window.Create(sf::VideoMode(800,600, 32), "Voxel Terrain Engine");
					}

					GLInitStuff();
					glViewport(0,0,window.GetWidth(), window.GetHeight());
				}
				if(e.Key.Code == Key::P || e.Key.Code == Key::Escape || e.Key.Code == Key::Space)
				{
					pause = !pause;
				}
			}

			if(e.Type == Event::Resized)
			{
				glViewport(0,0,window.GetWidth(), window.GetHeight());
			}

		}


		window.SetActive();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		for(int x = 0; x < MAP_LENGTH; ++x)
		{
			if(x < cam.posX + 30 && x > cam.posX - 60)
			{

				for(int z = 0; z < MAP_WIDTH; ++z)
				{
					if( z < cam.posY + 30 && z > cam.posY - 60)
					{
						for(int y = 0; y < MAP_DEPTH; ++y)
						{
							if(type[x][y][z] != 0 && visible[x][y][z])
							{
						
								DrawVoxel( x*VOXEL_SIZE, -y*VOXEL_SIZE, z*VOXEL_SIZE, VOXEL_SIZE, color[x][y][z], shadow[x][y][z]);
							}
						}
					}
				}

			}
		}

		player.Draw();
		bot1.Draw();
		bot2.Draw();
		bot3.Draw();

		window.Draw(bloom);

		window.Draw(win);

		window.Display();

		float dt = Clock.GetElapsedTime();
		Clock.Reset();

		cam.Update(dt);

		win.SetText("Game Paused");


		if(!pause)
		{

		player.Update(dt);


		bot1.Update(dt, Vector2f(player.x,player.z), Vector2f(bot2.x,bot2.z), Vector2f(bot3.x,bot3.z));
		bot2.Update(dt, Vector2f(player.x,player.z), Vector2f(bot1.x,bot1.z), Vector2f(bot3.x,bot3.z));
		bot3.Update(dt, Vector2f(player.x,player.z), Vector2f(bot1.x,bot1.z), Vector2f(bot2.x,bot2.z));

		for(list<Bullet*>::iterator it = b.begin(); it != b.end(); ++it)
		{
			if((*it)->side != 0 && player.collide((*it)->x,(*it)->y,(*it)->z))
			{
				player.hp -= 1;
				b.remove((*it));
				break;
			}

			if((*it)->side != 1 && bot1.collide((*it)->x,(*it)->y,(*it)->z))
			{
				bot1.hp -= 1;
				b.remove((*it));
				break;
			}

			if((*it)->side != 2 && bot2.collide((*it)->x,(*it)->y,(*it)->z))
			{
				bot2.hp -= 1;
				b.remove((*it));
				break;
			}

			if((*it)->side != 3 && bot3.collide((*it)->x,(*it)->y,(*it)->z))
			{
				bot3.hp -= 1;
				b.remove((*it));
				break;
			}
		}
		
		win.SetText("");
		if(bot1.hp <= 0 && bot2.hp <= 0 && bot3.hp <= 0)
		{
			win.SetText("Player Wins");
			wintime += dt;
		}
		if(player.hp <= 0 && bot2.hp <= 0 && bot3.hp <= 0)
		{
			win.SetText("Bot1 Wins");
			wintime += dt;
		}
		if(player.hp <= 0 && bot1.hp <= 0 && bot3.hp <= 0)
		{
			win.SetText("Bot2 Wins");
			wintime += dt;
		}
		if(player.hp <= 0 && bot1.hp <= 0 && bot2.hp <= 0)
		{
			win.SetText("Bot3 Wins");
			wintime += dt;
		}

		if(wintime > 2)
		{
			break;
		}

		}
	}

	mapm->stop();
	mapm->setPan(0);

	menu->setPan(0);
	menu->play();

	return 0;
}