#include "Graphics.h"
#include "Viewport.h"
#include"Clipper.h"
#include"Camera.h"
#include "MatrixStack.h"
#include "DepthBuffer.h"
#include "MaterialManager.h"
#include "LightManager.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	Camera::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	DepthBuffer::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
	LightManager::Get()->OnNewFrame();

}
