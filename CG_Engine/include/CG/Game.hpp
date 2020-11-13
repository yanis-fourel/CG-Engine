#pragma once

namespace CG {

class AGame {
public:
	virtual void start() {};
	virtual void update(float deltatime) {};
};

}