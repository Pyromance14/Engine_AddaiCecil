#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Fx/LightSource.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);
     void AddLightSource(LightSource* lightSource_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	std::vector<LightSource*>GetLightSource() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);
private:
	void UpdateCameraVectors();	
	 std::vector<LightSource*> lightSources;

	glm::vec3 position;
	glm::mat4 perspective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	

};

#endif //!CAMERA_H