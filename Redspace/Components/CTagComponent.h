#ifndef CTAGCOMPONENT_H
#define CTAGCOMPONENT_H

class CTagComponent
{
private:
	ObjectTypes tag;

public:
	CTagComponent(ObjectTypes tag);

	ObjectTypes getTag();
};

#endif