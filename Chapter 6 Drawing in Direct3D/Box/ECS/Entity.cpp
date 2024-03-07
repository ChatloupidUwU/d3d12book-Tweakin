// Include C++ standard tools
#include <iostream>

// Include needed classes
#include "./Entity.h"
#include "./Component.h"
#include "./Transform.h"


// Constru & Destru
Entity::Entity()
{
	// Creates and reset a Transform object, and gives it to the Entity
	Transform* TEntityTransform = new Transform();
	TEntityTransform->Identity();
	_pTransform = TEntityTransform;

	// Initalize std::vector members (lists) with an empty vector. Not doing this make compiler go no no :3
	_LpComponents = std::vector<Component*>();

	//_LpEntity.push_back(this);
}
Entity::~Entity()
{
	// Destroys the Entity's Transform object
	delete _pTransform;

	// Destroys every single Component linked to the Entity
	for (auto curPComp : _LpComponents)
	{
		RmvComponent(curPComp->GetCompSubType());
	}

	//for (auto curpEntity : _LpEntity)
	//{
	//	int iterator = 0;
	//	// If it's found, destroys & removes it
	//	if (curpEntity == this)
	//	{
	//		_LpEntity.erase(_LpEntity.begin() + iterator);
	//	}
	//	iterator++;
	//}

	std::cout << "ENTITY : Destructor called !\n";
}

// Add a Component to the Entity. This doesn't work if it already has it
void Entity::AddComponent(Component* ARGpComp)
{
	// Checks is the Component isn't already present
	for (auto pComp : _LpComponents)
	{
		// If it's already in there, quits the function
		if (pComp->GetCompSubType() == ARGpComp->GetCompSubType())
		{
			std::cout << "Component is already there !\n";
			return;
		}
	}

	// Adds the Component if it's already there
	_LpComponents.push_back(ARGpComp);
}

// Remove a Component of the Entity. This doesn't work if it doesn't already have it
void Entity::RmvComponent(compSubType ARGCompTypeTarget)
{
	// Look for a Component of this type
	int iterator = 0;
	for (auto pComp : _LpComponents)
	{
		// If it's found, destroys & removes it
		if (pComp->GetCompSubType() == ARGCompTypeTarget)
		{
			delete _LpComponents.at(iterator);
			_LpComponents.erase(_LpComponents.begin() + iterator);
			return;
		}
		iterator++;
	}
}

std::vector<Component*>* Entity::GetPCompListPtr()
{
	return &_LpComponents;
}