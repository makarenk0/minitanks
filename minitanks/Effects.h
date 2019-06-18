
#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
class Effects
{
private:
	int _deviationX, _deviationY;
	uint16_t currentFrame = 0;
	uint16_t maxFrame = 0;
	bool isShaking = false;
	sf::View newView;
	void updateShake(sf::RenderWindow& target);
public:
	Effects(sf::RenderWindow &source);
	Effects();
	virtual ~Effects();
	void initEffects(sf::RenderWindow &source);
	void shakeScreen(uint16_t _frames);
	void updateEffects(sf::RenderWindow& target);
};

