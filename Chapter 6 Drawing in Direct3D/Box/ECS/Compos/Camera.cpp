// Include needed classes
#include "./Camera.h"

// Include DirectX libs
#include <DirectXMath.h>

// Stuff to print in the Visual console
#include <windows.h>
#include <stdio.h>
char buff[200];

// Constru & Destru
Camera::Camera(Entity* ARGpEOwner, float ARGfTheta, float ARGfPhi, float ARGfRadius, MousePos ARGStartMousePos)
	: Component(ARGpEOwner, CAMERA), _fTheta(ARGfTheta), _fPhi(ARGfPhi), _fRadius(ARGfRadius), _PrevMousePos(ARGStartMousePos)
{
	_fLIMThetaMin = 0.0f;
	_fLIMThetaMax = 0.0f;
	_fLIMPhiMin = 0.1f;
	_fLIMPhiMax = DirectX::XM_PI - 0.1f;
}
Camera::~Camera()
{

}

// This method needs to be called every time the player moves the mouse (or every frame if we go cave-man mode)
void Camera::UpdateCam(int ARGiNewPosX, int ARGiNewPosY)
{
	_snprintf_s(buff, 200, _TRUNCATE, "=>UpdateCam(int ARGiNewPosX = %d, int ARGiNewPosY = %d)\n", ARGiNewPosX, ARGiNewPosY);
	OutputDebugStringA(buff);
	// Calculates the difference in movement of the mouse
	int iDiffX = ARGiNewPosX - _PrevMousePos.x;
	int iDiffY = ARGiNewPosY - _PrevMousePos.y;

	// Applies a factor on the movement of the mouse. You can think of it as the sensibility of the mouse movements.
	float fFactoredDiffX = 0.25f * iDiffX;
	float fFactoredDiffY = 0.25f * iDiffY;

	// Converts both distances in radians, so we interpret the "magnitude" of the mouse move by actual Camera movement
	float fActualMovementX = DirectX::XMConvertToRadians(fFactoredDiffX);
	float fActualMovementY = DirectX::XMConvertToRadians(fFactoredDiffY);

	// Updates both the angles
	_fTheta = fActualMovementX;
	_fPhi = fActualMovementY;

	// Finally, restrict angles to limit where the player can see
	_fPhi = _fPhi < _fLIMPhiMin ? _fLIMPhiMin : (_fPhi > _fLIMPhiMax ? _fLIMPhiMax : _fPhi);
	/*_fTheta = _fTheta < _fLIMThetaMin ? _fLIMThetaMin : (_fTheta > _fLIMThetaMax ? _fLIMThetaMax : _fTheta);*/

	_snprintf_s(buff, 200, _TRUNCATE, "\tValue updated :\n\t _fTheta = %.5f\n\t _fPhi = %.5f", _fTheta, _fPhi);
	OutputDebugStringA(buff);
	_snprintf_s(buff, 200, _TRUNCATE, "\n\t<> EXITING...\n");
	OutputDebugStringA(buff);
}

// Getters to construct View Matrix with the Camera
float Camera::GetTheta() { return _fTheta; }
float Camera::GetPhi() { return _fPhi; }
float Camera::GetRadius() { return _fRadius; }

// Setter to update the mouse position when we want to start moving the Camera around
void Camera::SetMousePos(MousePos ARGStartMousePos)
{
	_PrevMousePos = ARGStartMousePos;
}