

Image bs;
Image bu;

class Button
{
public:
	float x;
	float y;

	Sprite s1;
	Sprite s2;

	sf::String text;

	bool clicked;

	Button(float xPos, float yPos, const char* txt)
	{
		clicked = false;

		x = xPos;
		y = yPos;

		s1 = Sprite(bs,Vector2f(xPos,yPos));

		s2 = Sprite(bu,Vector2f(xPos,yPos));

		text = String(txt,sans,35.f);

		text.SetPosition(xPos + 299/2 - text.GetRect().GetWidth()/2, yPos + 38/2 - text.GetRect().GetHeight()/2);
	}

	void Draw()
	{
		clicked = false;

		if(input.GetMouseX() > x && input.GetMouseX() < x + 299 && input.GetMouseY() > y && input.GetMouseY() < y + 47)
		{
			window.Draw(s1);

			if(input.IsMouseButtonDown(Mouse::Left))
			{
				clicked = true;

				selectm->play();
			}

		}
		else
		{
			window.Draw(s2);
		}

		
		window.Draw(text);
		
	}

};

void LevelSelect();
void Instructions();

void Menu()
{
	
	menu->play();

	sf::Clock Clock;

	Image menuback;
	menuback.LoadFromFile("images//menuback.png");

	

	
	bs.LoadFromFile("images//buttons.png");
	
	bu.LoadFromFile("images//buttonu.png");

	Button inst = Button(400-299/2,300,"Instructions");

	Button play = Button(400-299/2,400,"Play Game");

	Button about = Button(800-299,600-47,"About");

	Sprite back(menuback);

	

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
			}

			if(e.Type == Event::Resized)
			{
				glViewport(0,0,window.GetWidth(), window.GetHeight());
			}

		}


		window.SetActive();

		window.Draw(back);

		about.Draw();
		play.Draw();
		inst.Draw();

		window.Display();

		float dt = Clock.GetElapsedTime();
		Clock.Reset();

		if(inst.clicked == true)
		{
			Instructions();
		}

		if(about.clicked == true)
		{
			about.clicked = false;
			system("about.html");
			about.clicked = false;
		}

		if(play.clicked == true)
		{
			play.clicked = false;
			LevelSelect();
			play.clicked = false;
			about.clicked = false;
		}


	}
}

void LevelSelect()
{
	

	sf::Clock Clock;

	Image menuback;
	menuback.LoadFromFile("images//menuback2.png");

	Button backb = Button(0,600-47,"Back");


	Button canyon = Button(400-299/2,100,"Canyon");

	Button ice = Button(400-299/2,200,"Ice");

	Button island = Button(400-299/2,300,"Island");


	Sprite back(menuback);

	

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
			}

			if(e.Type == Event::Resized)
			{
				glViewport(0,0,window.GetWidth(), window.GetHeight());
			}

		}


		window.SetActive();

		window.Draw(back);

		backb.Draw();
		canyon.Draw();

		ice.Draw();
		island.Draw();

		if(backb.clicked == true)
		{
			backb.clicked = false;
			return;
		}

		if(canyon.clicked)
		{
			canyon.clicked = false;

			Canyon();

			canyon.clicked = false;
		}

		if(ice.clicked)
		{
			ice.clicked = false;

			Ice();

			ice.clicked = false;
		}

		if(island.clicked)
		{
			island.clicked = false;
			Island();

			island.clicked = false;
		}

		window.Display();


	}
}

void Instructions()
{
	

	sf::Clock Clock;

	Image menuback;
	menuback.LoadFromFile("images//menuback3.png");

	Button backb = Button(0,600-47,"Back");


	Sprite back(menuback);

	sf::String txt("Instructions:\n\nMaps are played as 4-person deathmatches, \nwith one player and 3 bots.\n\nControls-\nWASD - Movement\nSpace, P - Pause\nLeft Click - Shoot Bullet\nRight Click - Explosion\n\nF - Fullscreen",sans,35.5f);
	txt.SetPosition(10,10);
	

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
			}

			if(e.Type == Event::Resized)
			{
				glViewport(0,0,window.GetWidth(), window.GetHeight());
			}

		}


		window.SetActive();

		window.Draw(back);

		window.Draw(txt);

		backb.Draw();


		if(backb.clicked == true)
		{
			backb.clicked = false;
			return;
		}

		window.Display();

	}
}