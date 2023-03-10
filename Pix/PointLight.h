#pragma once 

#include "Light.h"

class PointLight : public Light
{
public:
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetPosition(const Vector3& position);
	void SetAttenConst(float attenConst);
	void SetAttenLinear(float attenLinear);
	void SetAttenQuad(float attenQuad);
	
private:
	Vector3 mPosition;
	float mAttenConst;
	float mAttenLinear;
	float mAttenQuad;
};