#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
//OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler() {
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance() {
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
	colliders.clear();
	prevCollisions.clear();
	// scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_)
{
	/* if (scenePartition != nullptr) {
		scenePartition->AddObject(go_);
	}
	*/
	colliders.push_back(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
		                     CoreEngine::GetInstance()->GetScreenWitdth(),
		                     CoreEngine::GetInstance()->GetScreenHeight(),
		                     CoreEngine::GetInstance()->GetCamera());

	GameObject* hitResult = nullptr;
	float shortestDistance = FLT_MAX;
	
	/*if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);
		*/
	for (auto g : colliders) {
		if (mouseRay.isColliding(&g->GetBoundingBox())) {
			if (mouseRay.intersectionDist < shortestDistance) {
				hitResult = g;
				shortestDistance = mouseRay.intersectionDist;
			}
		}
	}
		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevCollisions) {
			if (hitResult != c && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
			// c = nullptr;
		}
		prevCollisions.clear();
		
		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	//}
}

void CollisionHandler::OnDestroy()
{
	/*delete scenePartition;
	scenePartition = nullptr;
	*/
	for (auto entry : colliders) {
		entry = nullptr;
	}
	colliders.clear();

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}
