#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

LightManager* LightManager::Get()
{
	static LightManager sInstance;
	return &sInstance;
}

void LightManager::OnNewFrame()
{
	mLights.clear();
}

void LightManager::AddDirectionalLight(const Vector3& direction)
{
	auto light = std::make_unique<DirectionalLight>();
	light->SetDirection(direction);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::AddPointLight(const Vector3& position, float constant, float linear, float quadratic)
{
	auto light = std::make_unique<PointLight>();
	light->SetPosition(position);
	light->SetAttenConst(constant);
	light->SetAttenLinear(linear);
	light->SetAttenQuad(quadratic);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::AddSpotLight(const Vector3& position, const Vector3& direction, float constant, float linear,float quadratic,float angle, float decay)
{
	auto light = std::make_unique<SpotLight>();
	light->SetPosition(position);
	light->SetDirection(direction);
	light->SetAttenuation(constant, linear, quadratic);
	light->SetDecay(decay);
	light->SetAngle(angle);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::SetLightingAmbient(const X::Color& color)
{
	mAmbient = color;
}

void LightManager::SetLightingDiffuse(const X::Color& color)
{
	mDiffuse = color;
}

void LightManager::SetLightingSpecular(const X::Color& color)
{
	mSpecular = color;
}

X::Color LightManager::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	if (mLights.empty())
	{
		return X::Colors::White;
	}

	X::Color color;
	for (auto& light : mLights)
	{
		color += light->ComputeLightColor(position, normal);
	}

	return color;
}
