#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambVal_, float diffVal_,
	float specVal_, glm::vec3 lightColour_)
{
	position = position_;
	ambVal = ambVal_;
	diffVal = diffVal_;
	specVal = specVal_;
	lightColour = lightColour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::getPosition() const
{
	return position;
}

float LightSource::getAmbVal() const
{
	return ambVal;
}

float LightSource::getDiffVal() const
{
	return diffVal;
}

float LightSource::getSpecVal() const
{
	return specVal;
}

glm::vec3 LightSource::getLightColour() const
{
	return lightColour;
}

void LightSource::setPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::setAmbVal(float ambVal_)
{
	ambVal = ambVal_;
}

void LightSource::setDiffVal(float diffVal_)
{
	diffVal = diffVal_;
}

void LightSource::setSpecVal(float specVal_)
{
	specVal = specVal_;
}

void LightSource::setLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}
