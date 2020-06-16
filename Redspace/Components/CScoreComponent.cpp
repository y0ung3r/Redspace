#include "CScoreComponent.h"

CScoreComponent::CScoreComponent(unsigned int score)
	: score(score)
{ }

unsigned int CScoreComponent::getScore()
{
	return this->score;
}

void CScoreComponent::addScore(unsigned int score)
{
	this->score += score;
}
