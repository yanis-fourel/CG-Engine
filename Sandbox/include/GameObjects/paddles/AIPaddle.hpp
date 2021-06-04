#include "GameObjects/paddles/APaddle.hpp"

class AIPaddle : public APaddle
{
public:
	AIPaddle();

protected:
	void move(double deltatime) override;

private:
	CG::GameObject *m_ball = nullptr;
};