#pragma once

// Enum for Component to keep track of its sub-class
// Idk why it doesn't work when in other header but oh well
enum compSubType
{
	UNKNOWN = 0,
	CAMERA,
	COLLIDER,
	FACTORY,
	ROTATE,
	MOVE,
	PARTICLE_GEN,
	GAME_OBJECT,
};