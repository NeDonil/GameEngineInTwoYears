#include "Box.h"

namespace Sandbox
{

	Box::Box(b2World* world, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		: m_Position(position), m_Size(size), m_Color(color)
	{
		b2BodyDef bodyDefs;
		bodyDefs.type = b2_dynamicBody;
		bodyDefs.position.Set(position.x, position.y);

		m_Body = world->CreateBody(&bodyDefs);

		b2PolygonShape shape;
		shape.SetAsBox(size.x / 2, size.y / 2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		m_Fixture = m_Body->CreateFixture(&fixtureDef);
	}

}
