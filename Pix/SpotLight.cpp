#include "SpotLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color SpotLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	auto cam = Camera::Get();
	auto mm = MaterialManager::Get();

	auto dirToLight = mPosition - position;
	auto distanceToLight = MathHelper::Magnitude(dirToLight);
	dirToLight /= distanceToLight;

	auto lightDir = -dirToLight;
	float dirDot = MathHelper::Dot(lightDir, mDirection);
	if (dirDot < mCosAngle)
	{
		return 0.0f;
	}
	float spot = std::pow(dirDot, mDecay);
	float atten = spot / (mAttenConst + (mAttenLinear * distanceToLight) + (mAttenQuad * distanceToLight * distanceToLight));
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

void SpotLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}

void SpotLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void SpotLight::SetAttenuation(float constant, float linear, float quadratic)
{
	mAttenConst = constant;
	mAttenLinear = linear;
	mAttenQuad = mAttenQuad;
}

void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}

void SpotLight::SetAngle(float angle)
{
	mCosAngle = std::cos(angle);
}
