#include "GameObjects/paddles/APaddle.hpp"

class AIPaddle : public APaddle
{
public:
	AIPaddle();

protected:
	void move(double deltatime) override;

};