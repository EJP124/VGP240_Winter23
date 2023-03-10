#include "PointLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	auto cam = Camera::Get();
	auto mm = MaterialManager::Get();

	auto dirToLight = mPosition - position;
	auto distanceToLight = MathHelper::Magnitude(dirToLight);
	dirToLight /= distanceToLight;

	float atten = 1.0f / (mAttenConst + (mAttenLinear * distanceToLight) + (mAttenQuad * distanceToLight * distanceToLight));
	float attenValue = X::Math::Clamp(atten, 0.0f, 1.0f);

	X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient() * attenValue;

	float dot = MathHelper::Dot(dirToLight, normal);
	X::Color colorDiffuse = mDiffuse * mm->GetMaterialDiffuse() * X::Math::Max(dot, 0.0f) * attenValue;

	auto dirToEye = cam->GetPosition();
	auto half = MathHelper::Normalize(dirToLight + dirToEye);
	float fallOff = pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess());
	X::Color colorSpecular = mSpecular * mm->GetMaterialSpecular() * X::Math::Max(fallOff, 0.0f) * attenValue;

	return colorAmbient + colorDiffuse + colorSpecular;
}

void PointLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void PointLight::SetAttenConst(float attenConst)
{
	mAttenConst = attenConst;
}

void PointLight::SetAttenLinear(float attenLinear)
{
	mAttenLinear = attenLinear;
}

void PointLight::SetAttenQuad(float attenQuad)
{
	mAttenQuad = attenQuad;
}
