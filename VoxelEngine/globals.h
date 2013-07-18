
#define EDIT

//Main window object
sf::RenderWindow window(sf::VideoMode(800,600, 32), "Voxelvania");


//Object for getting input
const sf::Input& input = window.GetInput();


//Define map sizes
#define VOXEL_SIZE 1.0f
#define MAP_LENGTH 100.0f
#define MAP_WIDTH 100.0f
#define MAP_DEPTH 14.0f

#define MAXHP 40


//Vars for storing voxel data
int*** type;
bool*** visible;
bool*** shadow;
Vector3f*** color;

bool fullscreen = false;


//Global Font
Font sans;

//Helper Funtion for squaring a float
float sq(float x)
{
	return x*x;
}

//Convert Degrees to radians
float ToRad(float deg)
{
	return (deg*3.14)/180;
}

//Convert Radians to Degrees
float ToDeg(float rad)
{
	return (rad*180)/3.14;
}

//Get distance between two points
float GetDist(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}
float GetDist(Vector2f pos1, Vector2f pos2)
{
	return GetDist(pos1.x, pos1.y, pos2.x, pos2.y);
}


//Return angle to something
float lookAt(float x1, float y1, float x2, float y2)
{
	float vx = x2 - x1;
	float vy = y2 - y1;

	float rad = atan(vx/vy);

	if(vy < 0)
	{
		return rad * (180/3.14);
	}
	else
	{
		return (rad * (180/3.14)) - 180;
	}
}
float lookAt(Vector2f pos1, Vector2f pos2)
{
	return lookAt(pos1.x, pos1.y, pos2.x, pos2.y);
}