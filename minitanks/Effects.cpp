#include "Effects.h"
#define DEVIATION_MAX 100


Effects::Effects(sf::RenderWindow &source)
{
	initEffects(source);
}

Effects::Effects() {}

void Effects::initEffects(sf::RenderWindow &source) {
	srand(time(0));
	newView.setSize(source.getDefaultView().getSize());
}

void Effects::shakeScreen(uint16_t _frames) {
	this->currentFrame = 0;
	this->maxFrame = _frames;
	this->isShaking = true;

		
}
void Effects::updateShake(sf::RenderWindow& target) {
	if (currentFrame <= maxFrame) {
		this->_deviationX = rand() % (2 * DEVIATION_MAX) - DEVIATION_MAX;
		this->_deviationY = rand() % (2 * DEVIATION_MAX) - DEVIATION_MAX;
		newView.setCenter(target.getDefaultView().getCenter().x + _deviationX, target.getDefaultView().getCenter().y + _deviationY);
		newView.setRotation(_deviationX % 30 );
		target.setView(newView);
	}
	else {
		target.setView(target.getDefaultView());
		this->isShaking = false;
	}
	currentFrame++;
}

void Effects::updateEffects(sf::RenderWindow& target) {
	if (isShaking)
		updateShake(target);
}

Effects::~Effects()
{
}

