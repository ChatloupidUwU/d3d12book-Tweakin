#pragma once

// Forward declarations
class Entity;

// Include the enum defining component "types"
#include "./__BSHeader.h"

// Component class.
// Bridge between component sub-classes (if they need to interact), and interface for Entity to "attach" them
class Component
{
protected:
	Entity* _pEOwner;
	compSubType _compSubType;

public:
	// Constru & Destru
	Component::Component(Entity* pEArgOwner, compSubType subType);
	virtual Component::~Component() = 0;

	// Getter & Setter
	compSubType Component::GetCompSubType();
};