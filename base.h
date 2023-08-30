

#include <SDL.h>

class entity_base {
public:
	virtual void init() = 0;
	virtual void update(float dt) = 0;


};

