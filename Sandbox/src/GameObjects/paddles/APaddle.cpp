#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/renderer/LineRenderer.hpp>
#include <CG/components/Rigidbody.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>
#include "GameObjects/paddles/APaddle.hpp"

APaddle::APaddle(float posZ, const CG::Color &color, const CG::Color &bordureColor)
{
	getObjectsOfTag<"ball"_hs>([&](CG::GameObject &obj) {
		m_ball = &obj;
		});

	assert(m_ball && "Please instanciate ball *before* the paddle, or find a better way to get a reference to the ball");

	addComponent<CG::Transform>(
		CG::Vector3(0, 0, posZ),
		CG::Quaternion::fromLookDirection(CG::Vector3::Down(), CG::Vector3(0, 0, -posZ)),
		CG::Vector3(kPaddleWidth, 1, kPaddleHeight)
		);

	addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Plane())
		.material = std::make_unique<CG::material::Solid>(color, 32, kPaddleOpacity);



	for (int i = 0; i < 4; i++) {
		m_bordureRenderers[i] = &getGame()->instanciate<CG::GameObject>();
		m_bordureRenderers[i]->addComponent<CG::LineRenderer>().material = CG::material::Line(bordureColor);
	}
}

void APaddle::update(double deltatime)
{
	move(deltatime);

	if (doesCollideWithBall(m_ball->getComponent<CG::Transform>())) {
		auto &rb = m_ball->getComponent<CG::Rigidbody>();

		auto vel = rb.getVelocity();
		vel.z = -vel.z;
		rb.setVelocity(vel);
	}
}

void APaddle::lateUpdate(double deltatime)
{
	auto pos = getComponent<CG::Transform>().position;

	auto topLeft = pos + CG::Vector3(-0.5 * kPaddleWidth, 0.5 * kPaddleHeight, 0);
	auto topRight = pos + CG::Vector3(0.5 * kPaddleWidth, 0.5 * kPaddleHeight, 0);
	auto bottomRight = pos + CG::Vector3(0.5 * kPaddleWidth, -0.5 * kPaddleHeight, 0);
	auto bottomLeft = pos + CG::Vector3(-0.5 * kPaddleWidth, -0.5 * kPaddleHeight, 0);


	m_bordureRenderers[0]->getComponent<CG::LineRenderer>().from = topLeft;

	m_bordureRenderers[0]->getComponent<CG::LineRenderer>().to = topRight;
	m_bordureRenderers[1]->getComponent<CG::LineRenderer>().from = topRight;

	m_bordureRenderers[1]->getComponent<CG::LineRenderer>().to = bottomRight;
	m_bordureRenderers[2]->getComponent<CG::LineRenderer>().from = bottomRight;

	m_bordureRenderers[2]->getComponent<CG::LineRenderer>().to = bottomLeft;
	m_bordureRenderers[3]->getComponent<CG::LineRenderer>().from = bottomLeft;

	m_bordureRenderers[3]->getComponent<CG::LineRenderer>().to = topLeft;
}

bool APaddle::doesCollideWithBall(const CG::Transform &ballT) const noexcept
{
	auto pos = getComponent<CG::Transform>().position;

	// Z axis
	if (std::abs(ballT.position.z - pos.z) > 0.5 * ballT.scale.z)
		return false;

	// X axis
	if (std::abs(ballT.position.x - pos.x) > 0.5 * (ballT.scale.x + kPaddleWidth))
		return false;

	// X axis
	if (std::abs(ballT.position.y - pos.y) > 0.5 * (ballT.scale.y + kPaddleHeight))
		return false;

	return true;
}
