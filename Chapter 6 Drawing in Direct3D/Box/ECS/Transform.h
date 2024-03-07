﻿#pragma once

#include <DirectXPackedVector.h>

using namespace DirectX;

class Transform
{
public:


	XMFLOAT4 qScal; // Scaling du quaternion
	XMFLOAT4X4 mScal; // Scaling de la matrice

	XMFLOAT3 mDir; // Orientation (Yaw)
	XMFLOAT3 mRight; // Orientation (Pitch)
	XMFLOAT3 mUp; // Orientation (Roll)


	XMFLOAT4 qRot; // Rotation actuelle du quaternion
	XMFLOAT4X4 mRot; // Rotation actuelle de la matrice

	XMFLOAT4  qPos; // Position actuelle du quaternion
	XMFLOAT4X4  mPos; // Position actuelle de la matrice

	XMFLOAT4X4  matrix; // matrice "finale"


	Transform();
	~Transform();

	void Identity(); // Remet les rotations à 0 RAZ
	void UpdateMatrix(); // Mettre à jour la matrice après les transformations
	void Rotate(float yaw, float pitch, float roll); // Rotation générale 


private:

};