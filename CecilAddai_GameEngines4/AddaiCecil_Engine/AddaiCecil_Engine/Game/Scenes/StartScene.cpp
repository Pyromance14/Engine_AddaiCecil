#include "StartScene.h"

StartScene::StartScene() :shape(nullptr) {

}

StartScene::~StartScene() {
	delete shape;
	shape = nullptr;
}

bool StartScene::OnCreate() {
	Debug::Info("Creating StartScene", "StartScene.cpp", __LINE__);

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	Model* model1 = new Model();
	model1->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model1);

	return true;
}

void StartScene::Update(const float deltaTime_) {

}

void StartScene::Render() {
	shape->Render();
}