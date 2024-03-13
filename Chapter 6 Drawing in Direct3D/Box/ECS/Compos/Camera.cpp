// Include needed classes
#include "./Camera.h"

// Include DirectX libs
#include <DirectXMath.h>

// Stuff to print in the Visual console
#include <windows.h>
#include <stdio.h>
#define VSCPrint(buffer, msg, ...) \
    do{ \
        _snprintf_s(buffer, sizeof(buffer), _TRUNCATE, msg, __VA_ARGS__); \
        OutputDebugStringA(buffer); \
    } while(0)
char buff[200]; // Global within the class (in main.cpp, it's a member to avoid problems)

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
	VSCPrint(buff, "=>UpdateCam(int ARGiNewPosX = %d, int ARGiNewPosY = %d)\n", ARGiNewPosX, ARGiNewPosY);

	// Calculates the difference in movement of the mouse
	int iDx = ARGiNewPosX - _PrevMousePos.x;
	int iDy = ARGiNewPosY - _PrevMousePos.y;
	VSCPrint(buff, "\tiDx = %d ||| iDy = %d\n", iDx, iDy);

	// Applies a factor on the movement of the mouse. You can think of it as the sensibility of the mouse movements.
	float fDegAngleX = 0.25f * static_cast<float>(iDx);
	float fDegAngleY = 0.25f * static_cast<float>(iDy);
	VSCPrint(buff, "\tfDegAngleX = %.5f ||| fDegAngleY = %.5f\n", fDegAngleX, fDegAngleY);

	// Converts both distances in radians, so we interpret the "magnitude" of the mouse move by actual Camera movement
	float fRadAngleX = DirectX::XMConvertToRadians(fDegAngleX);
	float fRadAngleY = DirectX::XMConvertToRadians(fDegAngleY);
	VSCPrint(buff, "\tfRadAngleX = %.5f ||| fRadAngleY = %.5f\n", fRadAngleX, fRadAngleY);

	// Updates both the angles
	_fTheta += fRadAngleX;
	_fPhi += fRadAngleY;

	// Finally, restrict angles to limit where the player can see
	_fPhi = _fPhi < _fLIMPhiMin ? _fLIMPhiMin : (_fPhi > _fLIMPhiMax ? _fLIMPhiMax : _fPhi);
	/*_fTheta = _fTheta < _fLIMThetaMin ? _fLIMThetaMin : (_fTheta > _fLIMThetaMax ? _fLIMThetaMax : _fTheta);*/

	// Updates the mouse position
	_PrevMousePos.x = ARGiNewPosX;
	_PrevMousePos.y = ARGiNewPosY;

	VSCPrint(buff, "\tValue post-clamp : _fTheta = %.5f   _fPhi = %.5f", _fTheta, _fPhi);
	VSCPrint(buff, "\n<> EXITING...\n");
}

// Getters to construct View Matrix with the Camera
float Camera::GetTheta() { return _fTheta; }
float Camera::GetPhi() { return _fPhi; }
float Camera::GetRadius() { return _fRadius; }

// Setter to update the mouse position when we want to start moving the Camera around
void Camera::SetMousePos(MousePos ARGStartMousePos)
{
	_PrevMousePos = ARGStartMousePos;
	VSCPrint(buff, "Camera::MousePos is at (%d, %d)\n", _PrevMousePos.x, _PrevMousePos.y);
}