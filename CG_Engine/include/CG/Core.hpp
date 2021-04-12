#pragma once

#include <memory>

#include "CG/internal/ShaderManager.hpp"
#include "CG/Game.hpp"

namespace CG {

class Core
{
public:
	Core(std::unique_ptr<AGame> game);
	
	int run();
private:
	void updateGame(double deltatime);
	void cleanupDeadGameobjects();
	void displayGame();

public:
	std::unique_ptr<AGame> m_game;

	ShaderManager m_onlyShader; // TODO: delegae shader responsability to material
};

}
