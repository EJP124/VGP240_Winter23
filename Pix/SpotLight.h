#pragma once

#include "Light.h"

class SpotLight : public Light
{
public:
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetDirection(const Vector3& direction);
	void SetPosition(const Vector3& position);
	void SetAttenuation(float constant, float linear, float quadratic);
	void SetDecay(float decay);
	void SetAngle(float angle);
private:
	Vector3 mDirection = {};
	Vector3 mPosition = {};
	float mAttenConst = {-1.0f};
	float mAttenLinear = {0.0f};
	float mAttenQuad = {0.0f};
	float mDecay = {0.0f};
	float mCosAngle = cos(X::Math::kPiByTwo);
};