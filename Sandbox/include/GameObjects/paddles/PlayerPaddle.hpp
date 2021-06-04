#include "GameObjects/paddles/APaddle.hpp"

class PlayerPaddle : public APaddle
{
public:
	PlayerPaddle();

protected:
	void move(double deltatime) override;
};