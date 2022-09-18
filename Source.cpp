//to use graphics
#include <SFML/Graphics.hpp>
#include <iostream>

//in the standard namespace
using namespace std;

//variables
const int width{ 1920 };
const int height{ 1080 };
//we have to define how big we want the tiles to be, something that would divide our width and height nicely.
//i like to do 50 to start with, we can change it later.
int tile_size{ 25 };
bool paused{ true };
bool mouse_held{ false };

//to start with, we have to come up with this idea of a tile. 
//i like to think of them as tiles, at least. the easiest way
//to do this would be to create what's called a class.

//defining an object

class Tile
{
	//in order for it's value to be accessible, we have to make the attributes public.
public:
	
	//now, we have to store whether it's dead or alive. we will do that with a boolean (a true or false value)
	bool alive;
	//now, we want every tile to know how many living neighbors it has!
	//it wouldn't be conways game of life without the good ol' sum!
	int living_friends;
	//i know it's morbid, but it'll be okay!

	Tile(bool alive)
	{
		//now for the default constructor, or what is created when we call 'Tile()' under our definition.
		this->alive = alive;
		//now, when we call 'Tile(true)', the Tile created is alive and well.
	}

};


//now we need something to store all of our tiles in!
//i think of it as a grid of sorts, because, well, that's what we have to make right?

vector<vector<Tile>> tilemap;
//a vector is a list of sorts. think of it as a row of Tiles, in a perfect line.
//then, we create a vector INSIDE each segment of the first vector, creating a grid.

//now if we are gonna be swapping things back and forth, we need what's called a buffer.
//somewhere to slap the data mid frame without borking the rest of the tilemap! without it, it would try to 
//count while swapping and it wouldn't be pretty, trust me.

//we'll probably do it by accident anyways haha.

vector<vector<Tile>> tilemap_buffer;


int main()
{
	//set up window
	sf::RenderWindow window(sf::VideoMode(width, height), "game_of_life", sf::Style::Fullscreen);
	sf::Event event;

	//before the window is actually open and the program is running, we need to fill the map with it's tiles!
	//we made the map, sure, but it's just a *container* for the tiles, there is nothing in it to start.

	//we are going to use loops to do this. it's easier than it looks, once you know how to break it down.

	for (int i = 0; i < width / tile_size; i++)
	{
		vector<Tile> row;
		//we have to nest another loop inside it to achieve what we're looking for here, which is generating them in a grid pattern.
		for (int j = 0; j < height / tile_size; j++)
		{
			//okay, we have our loops, now we have to create the rows for the map
			row.push_back(Tile(true));
			//for every iteration of 'J', we add a tile to 'Row'
		}
		//add row to map
		//tilemap sounds better anyways, eh?
		tilemap.push_back(row);
	}

	//now we have to load the button image to the program!
	sf::Texture button_texture;
	if (!button_texture.loadFromFile("button.png"))
	{
		cout << "error loading button.png!" << endl;
	}
	sf::Texture button_texture2;
	if (!button_texture2.loadFromFile("button2.png"))
	{
		cout << "error loading button2.png!" << endl;
	}
	sf::Sprite button;
	
	button.setPosition(sf::Vector2f(width-50, height-50));


	
	//look for events while the window is open
	while (window.isOpen())
	{
		tilemap_buffer = tilemap;
		if (mouse_held)
		{
			int mouse_x_tile;
			mouse_x_tile = sf::Mouse::getPosition(window).x / tile_size;
			int mouse_y_tile;
			mouse_y_tile = sf::Mouse::getPosition(window).y / tile_size;
			//so what we've done here is we are now able to pinpoint what tile has
			//been clicked on through just math. now let's make it relative to 
			//the window, and have it do something when clicked!
			tilemap[mouse_x_tile][mouse_y_tile].alive = true;
			
			//oops out of bounds! haha
			
		}



		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					

					if (sf::Mouse::getPosition(window).x > (width - 50) && sf::Mouse::getPosition(window).y > (height - 50))
					{
						paused = !paused;
					}
					else
					{
						mouse_held = true;
						
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouse_held = false;
					
				}
			}
		}
		//clear the window
		window.clear();

		if (!paused)
		{


			for (int i = 0; i < width / tile_size; i++)
			{
				for (int j = 0; j < height / tile_size; j++)
				{
					//we have to loop back through all the elements to display them.
					if (tilemap[i][j].alive == true)
					{
						

						tilemap[i][j].living_friends = 0;
						//to reset the amount before every call, otherwise the numbers would just stack up!

						//now we have to have it count the neighbors that are alive!
						if (i > 0 && tilemap[i - 1][j].alive == true)
							tilemap[i][j].living_friends++;
						if (i < (width / tile_size) - 1 && tilemap[i + 1][j].alive == true)
							tilemap[i][j].living_friends++;
						if (j > 0 && tilemap[i][j - 1].alive == true)
							tilemap[i][j].living_friends++;
						if (j < (height / tile_size) - 1 && tilemap[i][j + 1].alive == true)
							tilemap[i][j].living_friends++;
						if (i > 0 && j > 0 && tilemap[i - 1][j - 1].alive == true)
							tilemap[i][j].living_friends++;
						if (i > 0 && j < (height / tile_size) - 1 && tilemap[i - 1][j + 1].alive == true)
							tilemap[i][j].living_friends++;
						if (j > 0 && i < (width / tile_size) - 1 && tilemap[i + 1][j - 1].alive == true)
							tilemap[i][j].living_friends++;
						if (i < (width / tile_size) - 1 && j < (height / tile_size) - 1 && tilemap[i + 1][j + 1].alive == true)
							tilemap[i][j].living_friends++;







						if (tilemap[i][j].living_friends < 2)
							tilemap_buffer[i][j].alive = false;
						if (tilemap[i][j].living_friends > 3)
							tilemap_buffer[i][j].alive = false;
						if (tilemap[i][j].living_friends == 2 || tilemap[i][j].living_friends == 3)
							tilemap_buffer[i][j].alive = true;

						//here's where we start getting the cool stuff, how about that!
					}
					else if (tilemap[i][j].alive == false)
					{




						//AND THERE WE GO FOLKS (:
						//CONWAYS GAME OF LIFE IN C++ WITH SFML

						//my github with the project will be posted in the description,
						//i will go add it to the prior videos as well. thanks for watching!


						







						

						//now we have to have it count the neighbors that are alive!
						if (i > 0 && tilemap[i - 1][j].alive == true)
							tilemap[i][j].living_friends++;
						if (i < (width / tile_size) - 1 && tilemap[i + 1][j].alive == true)
							tilemap[i][j].living_friends++;
						if (j > 0 && tilemap[i][j - 1].alive == true)
							tilemap[i][j].living_friends++;
						if (j < (height / tile_size) - 1 && tilemap[i][j + 1].alive == true)
							tilemap[i][j].living_friends++;
						if (i > 0 && j > 0 && tilemap[i - 1][j - 1].alive == true)
							tilemap[i][j].living_friends++;
						if (i > 0 && j < (height / tile_size) - 1 && tilemap[i - 1][j + 1].alive == true)
							tilemap[i][j].living_friends++;
						if (j > 0 && i < (width / tile_size) - 1 && tilemap[i + 1][j - 1].alive == true)
							tilemap[i][j].living_friends++;
						if (i < (width / tile_size) - 1 && j < (height / tile_size) - 1 && tilemap[i + 1][j + 1].alive == true)
							tilemap[i][j].living_friends++;

						if (tilemap[i][j].living_friends == 3)
							tilemap_buffer[i][j].alive = true;


					}
				}
			}


			tilemap = tilemap_buffer;
		}
		
		
		
		//we have to seperate the display from the sum now!

		for (int i = 0; i < width / tile_size; i++)
		{
			for (int j = 0; j < height / tile_size; j++)
			{
				if (tilemap[i][j].alive == true)
				{
					//we never declared it's size! silly me.
					sf::RectangleShape Tile_image(sf::Vector2f(50, 50));
					Tile_image.setFillColor(sf::Color(255, 255, 255));
					Tile_image.setPosition(i* tile_size, j* tile_size);
					Tile_image.setOutlineColor(sf::Color(0, 0, 0));
					Tile_image.setOutlineThickness(1);
					//we have created a square for every tile to display, and if it's alive we will set it white.
					//if it's dead, it'll be black to blend with the background.

					//ahh, we have CREATED the images to be drawn, but we haven't passed them to the display yet!
					//without that, the pc doesn't know to draw it!
					window.draw(Tile_image);
				}
				else if (tilemap[i][j].alive == false)
				{
					sf::RectangleShape Tile_image(sf::Vector2f(50, 50));
					Tile_image.setFillColor(sf::Color(30, 30, 30));
					Tile_image.setPosition(i* tile_size, j* tile_size);
					Tile_image.setOutlineColor(sf::Color(0, 0, 0));
					Tile_image.setOutlineThickness(1);
					window.draw(Tile_image);
				}
			}
		}


		if (paused)
			button.setTexture(button_texture2);
		if (!paused)
			button.setTexture(button_texture);
		window.draw(button);
		//draw the window
		window.display();
		window.setFramerateLimit(60);
		//let's do that before it bites us in the ass later lol
		//i always forget.
	}
	//return okay if the program exits properly
    return 0;
}