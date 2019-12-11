#include "../inc/managers/CollisionManager.h"

CollisionManager* CollisionManager::colmanInstance = NULL;
bool CollisionManager::colmanInstantiated = false;


bool CollisionManager::colmanInit() {
	std::cout << "CollisionManager : init" << std::endl;
	return true;
}

CollisionManager::~CollisionManager() {
	colmanEraseAllContacts();
	std::cout << "CollisionManager : default destructed" << std::endl;
}

CollisionManager::CollisionManager() {
	colmanInstantiated = colmanInit();
	colmanGameObjectFactoryInstance = GameObjectFactory::gofCreate();
	colmanGraphicsManager = GraphicsManager::gfxCreate();
	std::cout << "CollisionManager : default constructed" << std::endl;
}

CollisionManager* CollisionManager::colmanCreate() {
	if (!colmanInstantiated) {
		colmanInstance = new CollisionManager();
	}
	return colmanInstance;
}

void CollisionManager::colmanDestroy() {
	colmanInstantiated = false;
	delete colmanInstance;
}

bool CollisionManager::colmanGetInstantiated() {
	return colmanInstantiated;
}

void CollisionManager::colmanUpdate() {

	if (NULL != colmanInstance) {
		colmanInstance->colmanReset();
	}

	if (!colmanGameObjectFactoryInstance->gofGameObjects.empty()) {
		GameObjectMap::iterator it1 = colmanGameObjectFactoryInstance->gofGameObjects.begin();
		GameObjectMap::iterator it2 = it1;
		GameObjectMap::iterator itend = colmanGameObjectFactoryInstance->gofGameObjects.end();

		for (; it1 != itend; ++it1) {
			GameObject* go1 = it1->second;
			it2 = it1;
			it2++;
			for (; it2 != itend; ++it2) {
					GameObject* go2 = it2->second;
					if (go1->gaxComponentExists<ColliderComponent<Box>>() && go2->gaxComponentExists<ColliderComponent<Box>>()) {
						if (colmanContactCheckCollide(go1, go2)) {
							// draw red box
							go1->gaxDebugDrawColor = vec3(1.0f, 0.0f, 0.0f);
							go2->gaxDebugDrawColor = vec3(1.0f, 0.0f, 0.0f);

							// add to contact map
							colmanCreateContact(go1, go2);
						}
						else {
							// draw green box
							go1->gaxDebugDrawColor = vec3(0.0f, 1.0f, 0.0f);
							go2->gaxDebugDrawColor = vec3(0.0f, 1.0f, 0.0f);
						}
					}
			}
		}
	}
}

void CollisionManager::colmanDraw() {

}

void CollisionManager::colmanHandleEvents() {

}

// non static method that can be called from instances
// purely syntactic sugar
bool CollisionManager::colmanGetExists() {
	return(colmanGetInstantiated());
}

void CollisionManager::colmanEraseAllContacts() {
	if (!colmanContactMap.empty()) {
		// just clear contents
		// don't erase 
		// as that is done in collision resolution
		colmanContactMap.clear();
	}
	std::cout << "GameObjectFactory : erased all Collisions\n";
}

bool CollisionManager::colmanEraseContact(ContactID _cid) {
	if (colmanContactMap.erase(_cid)) {
		return true;
	}
	return false;
}

void CollisionManager::colmanReset() {
	if (!colmanContactMap.empty()) {
		colmanContactMap.clear();
	}
}


ContactID CollisionManager::colmanCreateContact(GameObject* _a, GameObject* _b) {
	ContactID id = getContactID();
	ContactPair cp = ContactPair(_a, _b);
	ContactMapPair cmp = ContactMapPair(id, cp);
	colmanContactMap.insert(cmp);
	return id;
}

bool CollisionManager::colmanContactCheckCollide(GameObject* _go1, GameObject* _go2) {
	bool res = false;
	if (_go1->gaxComponentExists<ColliderComponent<Box>>() && _go2->gaxComponentExists<ColliderComponent<Box>>()) {
		res = _go1->gaxGetComponent<ColliderComponent<Box>>().collGenContact(_go2->gaxGetComponent<ColliderComponent<Box>>());
	}
	else if (_go1->gaxComponentExists<ColliderComponent<Sphere>>() && _go2->gaxComponentExists<ColliderComponent<Sphere>>()) {
		res = _go1->gaxGetComponent<ColliderComponent<Sphere>>().collGenContact(_go2->gaxGetComponent<ColliderComponent<Sphere>>());
	}
	else if (_go1->gaxComponentExists<ColliderComponent<Box>>() && _go2->gaxComponentExists<ColliderComponent<Sphere>>()) {
		res = _go1->gaxGetComponent<ColliderComponent<Box>>().collGenContact(_go2->gaxGetComponent<ColliderComponent<Sphere>>());
	}
	else if (_go1->gaxComponentExists<ColliderComponent<Sphere>>() && _go2->gaxComponentExists<ColliderComponent<Box>>()) {
		res = _go1->gaxGetComponent<ColliderComponent<Box>>().collGenContact(_go2->gaxGetComponent<ColliderComponent<Box>>());
	}
	return res;
}