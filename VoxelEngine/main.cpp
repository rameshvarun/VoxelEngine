#include <windows.h>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



#include<iostream>

#include<sstream>


#include <stdio.h>	

using namespace sf;

#include<list>



#include<fstream>

using namespace std;

#include"globals.h"

#include"camera.h"

int tex1;

#include"sound.h"

#include"util.h"

#include"voxel.h"

#include"time.h"

#include"player.h"



#include"map.h"


#include"maps.h"



#include"Menu.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	InitSound();

	InitVox();

	//Canyon();

	//Ice();

	//Island();

	Menu();
}