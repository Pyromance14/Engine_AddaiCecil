#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Core/Timer.h"

class StartScene : public Scene {
public:
	StartScene();
	virtual ~StartScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;


private:
	GameObject* shape;
};

#endif // !STARTSCENE_H