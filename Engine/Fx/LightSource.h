
#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/vec3.hpp>
class LightSource
{
public:

	LightSource(glm::vec3 position_, float ambVal_, float diffVal_,
		float specVal_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 getPosition() const;
	float getAmbVal() const;
	float getDiffVal() const;
	float getSpecVal() const;
	glm::vec3 getLightColour() const;


	void setPosition(glm::vec3 position_);
	void setAmbVal(float ambVal_);
	void setDiffVal(float diffVal_);
	void setSpecVal(float specVal_);
	void setLightColour(glm::vec3 lightColour_);

private:
	
	glm::vec3 position;
	float ambVal;
	float diffVal;
	float specVal;
	glm::vec3 lightColour;
};

#endif // !LIGHTSOURCE_H
