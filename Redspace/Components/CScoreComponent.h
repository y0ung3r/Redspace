#ifndef CSCORECOMPONENT_H
#define CSCORECOMPONENT_H

class CScoreComponent
{
private:
	unsigned int score;

public:
	CScoreComponent(unsigned int score = 0);

	unsigned int getScore();

	void addScore(unsigned int score);
};

#endif