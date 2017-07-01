#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace g         // пространство имен игры
{
	struct GameData {
		int WindowStyle;
		int Width;
		int Height;
		int Sound;
		int Volume;
	};
}

void Loading(g::GameData & _data);  // Функция загрузки настроек игры

int main()
{
	g::GameData pData;
	sf::Window window(sf::VideoMode(800, 600), "My window", sf::Style::Close);  //создание окна

	Loading(pData);   //Загрузка настроек из файла

  //Изменние настроек окна согласно файлу настроек
	if (pData.WindowStyle == 0)
		window.create(sf::VideoMode(pData.Width, pData.Height), "My window", sf::Style::Close);
	if (pData.WindowStyle == 1)
		window.create(sf::VideoMode(pData.Width, pData.Height), "My window", sf::Style::Fullscreen);

  //основной рабочий цикл
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}


void Loading(g::GameData & _data)
{
	std::ifstream fin("Settings.txt", std::ios::in);
	if (!fin)
		return;

	char s[50], num[4];
	unsigned short int line = 1;
	while (!fin.eof())
	{
		for (int x = 0; x < 4; x++)
		{
			num[x] = ' ';
		}
		fin.getline(s, 50);
		if (s[0] == '#')
		{
			for (int i = 1; s[i] != ';'; i++)
			{
				if (s[i] == ' ')
					for (int j = i + 1, x = 0; s[j] != ';'; j++, x++)
					{
						num[x] = s[j];
					}
			}
			switch (line)
			{
			case 1: _data.WindowStyle = (int)atoi(num); break;
			case 2: _data.Sound = (int)atoi(num); break;
			case 3: _data.Volume = (int)atoi(num); break;
			case 4: _data.Width = (int)atoi(num); break;
			case 5: _data.Height = (int)atoi(num); break;
			}
		}
		line++;
	}
	fin.close();
}
