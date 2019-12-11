#include "../inc/components/PhysicsComponent.h"

PhysicsComponent::PhysicsComponent() {

	phyGravity = vec3(0.0, 0.0f, 0.0);
	phyInvMass = phyMass = 0.0f;
	phyMass = 1.0f;
	phyCurrForce = phyPrevForce = vec3(0.0f, 0.0f, 0.0f);
	phyCurrAcc = phyPrevAcc = vec3(0.0f, 0.0f, 0.0f);
	phyCurrVel = phyPrevVel = vec3(0.0f, 0.0f, 0.0f);
	phyCurrPos = phyPrevPos = vec3(0.0f, 0.0f, 0.0f);
	phyStateMachineInstance = NULL;

	phyBoxColliderInstance = NULL;
	phySphereColliderInstance = NULL;
	phyTxfInstance = NULL;
	phyCollisionManager = NULL;
	phyFrameRateManager = NULL;

	// managers
	phyCollisionManager = CollisionManager::colmanCreate();
	phyFrameRateManager = FrameRateManager::fpsCreate();
	phyTileMapManager = TileMapManager::tmmCreate();

}

PhysicsComponent::~PhysicsComponent() {
}

void PhysicsComponent::comInit() {
	// actively do shit only if the components actuall exist
	// else skip
	if (comOwner->gaxComponentExists<TransformComponent>()) {
		phyTxfInstance = &comOwner->gaxGetComponent<TransformComponent>();
		phyCurrPos = phyPrevPos = phyTxfInstance->txfPosition;
	}
	if (comOwner->gaxComponentExists<ColliderComponent<Box>>()) {
		phyBoxColliderInstance = &comOwner->gaxGetComponent<ColliderComponent<Box>>();
	}
	if (comOwner->gaxComponentExists<ColliderComponent<Sphere>>()) {
		phySphereColliderInstance = &comOwner->gaxGetComponent<ColliderComponent<Sphere>>();
	}
	if (comOwner->gaxComponentExists<StateMachineComponent>()) {
		phyStateMachineInstance = &comOwner->gaxGetComponent<StateMachineComponent>();
	}

	//mass updates
	if (0.0f == phyMass) {
		phyInvMass = 0.0f;
	}
	else {
		phyInvMass = 1 / phyMass;
	}

}

void PhysicsComponent::comUpdate() {



}
void PhysicsComponent::phyIntegrate(float32 _gravity, float32 _dt) {
	float32 dt = _dt;

	// store prev data
	phyPrevPos.x = phyCurrPos.x;
	phyPrevPos.y = phyCurrPos.y;
	phyPrevPos.z = phyCurrPos.z;

	phyPrevVel.x = phyCurrVel.x;
	phyPrevVel.y = phyCurrVel.y;
	phyPrevVel.z = phyCurrVel.z;
	// make updates

	phyCurrForce.y -= _gravity;

	// ForceUpdates accelration
	phyCurrAcc.y = phyCurrForce.y * phyInvMass;
	phyCurrAcc.x = phyCurrForce.x * phyInvMass;
	phyCurrAcc.z = phyCurrForce.z * phyInvMass;
	// acceleration updates velocity
	phyCurrVel.x = phyPrevVel.x + phyCurrAcc.x * dt;
	phyCurrVel.y = phyPrevVel.y + phyCurrAcc.y * dt;
	phyCurrVel.z = phyPrevVel.z + phyCurrAcc.z * dt;
	// velocity updates position
	phyCurrPos.x = phyPrevPos.x + phyCurrVel.x * dt;
	phyCurrPos.y = phyPrevPos.y + phyCurrVel.y * dt;
	phyCurrPos.z = phyPrevPos.z + phyCurrVel.z * dt;

	TilePair z = phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y));
	//std::cout << "mappos : " <<z.first<<" "<<z.second<<std::endl;


	if (phyCurrVel.x > 0) {
		int i = phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y)).second + 1;
		int j = 15 - (phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y))).first;
		if (phyTileMapManager->map[i][j] == 1) {
			//std::cout << "collided ! " << std::endl;
			phyCurrPos.x = (int)(phyCurrPos.x + 1);
			phyCurrVel.x = 0.0f;
		}
		else {
			//std::cout << "not collided !" << std::endl;
		}
	}
	if (phyCurrVel.x < 0) {
		int i = phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y)).second - 1;
		int j = 15 - (phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y))).first;
		if (phyTileMapManager->map[i][j] == 1) {
			//std::cout << "collided ! " << std::endl;
			phyCurrPos.x = (int)(phyCurrPos.x + 1);
			phyCurrVel.x = 0.0f;
		}
		else {
			//std::cout << "not collided !" << std::endl;
		}
	}
	if (phyCurrVel.y > 0) {
		int i = phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y)).second;
		int j = 15 - (phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y))).first - 1;
		if (phyTileMapManager->map[i][j] == 1) {
			//std::cout << "collided ! " << std::endl;
			phyCurrPos.y = (int)(phyCurrPos.y - 1);
			phyCurrVel.y = 0.0f;
		}
		else {
			//std::cout << "not collided !" << std::endl;
		}
	}
	if (phyCurrVel.y < 0) {
		int i = phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y)).second + 1;
		int j = 15 - (phyTileMapManager->tmmGetMapLoc(vec2(phyCurrPos.x, phyCurrPos.y))).first;
		if (phyTileMapManager->map[i][j] == 1) {
			//std::cout << "collided ! " << std::endl;
			phyCurrPos.y = (int)(phyCurrPos.y + 1);
			phyCurrVel.y = 0.0f;
		}
		else {
			//std::cout << "not collided !" << std::endl;
		}
	}
	if (phyCurrVel.x < 0) {
		if (phyTileMapManager->map[glm::max(z.first-1,0)][15 - glm::min(z.second,15)] == 1) {
			std::cout << "collided ! " << std::endl;
			phyCurrVel.x = 0.0f;
			//phyCurrPos.x = (int)phyCurrPos.x;
		}
		else {
			std::cout << "not collided !" << std::endl;
		}
	}
	if (phyCurrVel.y > 0) {
		if (phyTileMapManager->map[z.first][15 - glm::min((z.second + 1),15)] == 1) {
			std::cout << "collided ! " << std::endl;
			phyCurrVel.y = 0.0f;
			//phyCurrPos.x = (int)phyCurrPos.x;
		}
		else {
			std::cout << "not collided !" << std::endl;
		}
	}
	if (phyCurrVel.y < 0) {
		if (phyTileMapManager->map[z.first][15 - glm::max((z.second - 1), 0)] == 1) {
			std::cout << "collided ! " << std::endl;
			phyCurrVel.y = 0.0f;
			//phyCurrPos.x = (int)phyCurrPos.x;
		}
		else {
			std::cout << "not collided !" << std::endl;
		}
	}

	
	//// moving towards left or stopped
	//if (phyCurrVel.x < 0) {
	//	float hsz = phyTileMapManager->tmmBlockSize / 2;
	//	// top left
	//	vec3 tl = phyCurrPos.x - vec3(hsz, hsz-1,0);
	//	// bottom left
	//	vec3 bl = phyCurrPos.x - vec3(hsz, -hsz+1, 0);

	//	TilePair a = phyTileMapManager->tmmGetMapLoc(vec2(tl.x, tl.y));
	//	TilePair b = phyTileMapManager->tmmGetMapLoc(vec2(bl.x, bl.y));

	//	//std::cout << " map pos :" << phyTileMapManager->map[a.first][a.second]<<std::endl;

	//	if (phyTileMapManager->map[a.first][15 - a.second] != 0 || phyTileMapManager->map[b.first][15 - b.second] != 0) {
	//		phyCurrPos.x = (int)phyCurrPos.x + 1;
	//		phyCurrVel.x = 0.0f;
	//	}
	//}

	//// else if moving right
	//else {
	//	float hsz = phyTileMapManager->tmmBlockSize / 2;
	//	// top right
	//	vec3 tr = phyCurrPos.x + vec3(hsz, hsz-1, 0);
	//	// bottom right
	//	vec3 br = phyCurrPos.x + vec3(hsz, -hsz+1, 0);

	//	TilePair a = phyTileMapManager->tmmGetMapLoc(vec2(tr.x, tr.y));
	//	TilePair b = phyTileMapManager->tmmGetMapLoc(vec2(br.x, br.y));

	//	//std::cout << " map pos :" << phyTileMapManager->map[a.first][a.second] << std::endl;

	//	if (phyTileMapManager->map[a.second][15 - a.first] != 0 || phyTileMapManager->map[b.second][15 - b.first] != 0) {
	//		phyCurrPos.x = (int)phyCurrPos.x;
	//		phyCurrVel.x = 0.0f;
	//	}  
	//} 

	//// moving up
	//if (phyCurrVel.y > 0 ) {
	//	float hsz = phyTileMapManager->tmmBlockSize / 2;
	//	// top left
	//	vec3 tl = phyCurrPos.x + vec3(-hsz, hsz - 1, 0);
	//	// top right
	//	vec3 tr = phyCurrPos.x + vec3(hsz, hsz - 1, 0);

	//	TilePair a = phyTileMapManager->tmmGetMapLoc(vec2(tl.x, tl.y));
	//	TilePair b = phyTileMapManager->tmmGetMapLoc(vec2(tr.x, tr.y));

	//	//std::cout << " map pos :" << phyTileMapManager->map[a.first][a.second] << std::endl;

	//	if (phyTileMapManager->map[a.second][15 - a.first] != 0 || phyTileMapManager->map[b.second][15 - b.first] != 0) {
	//		phyCurrPos.y = (int)phyCurrPos.y + 1;
	//		phyCurrVel.y = 0.0f;
	//	}
	//}
	////moving down
	//else {
	//	float hsz = phyTileMapManager->tmmBlockSize / 2;
	//	// bottom left
	//	vec3 bl = phyCurrPos.x + vec3(-hsz, -hsz + 1, 0);
	//	// bottom right
	//	vec3 br = phyCurrPos.x + vec3(hsz, -hsz + 1, 0);

	//	TilePair a = phyTileMapManager->tmmGetMapLoc(vec2(bl.x, bl.y));
	//	TilePair b = phyTileMapManager->tmmGetMapLoc(vec2(br.x, br.y));

	//	//std::cout << " map pos :" << phyTileMapManager->map[a.first][a.second] << std::endl;

	//	if (phyTileMapManager->map[a.first][15 - a.second] != 0 || phyTileMapManager->map[b.first][15 - b.second] != 0) {
	//		phyCurrPos.y = (int)phyCurrPos.y;
	//		phyCurrVel.y = 0.0f;
	//	}
	//}

	// reset the forces and velocities to 0
	phyCurrVel.x = phyCurrVel.y = phyCurrVel.z = 0.f;
	phyCurrForce.x = phyCurrForce.y = phyCurrForce.z = 0.0f;

	// state updates
	if (NULL != phyStateMachineInstance) {
		phyStateMachineInstance->smcPrevTouchRight = phyStateMachineInstance->smcCurrTouchRight;
		phyStateMachineInstance->smcPrevTouchLeft = phyStateMachineInstance->smcCurrTouchLeft;
		phyStateMachineInstance->smcPrevTouchUp = phyStateMachineInstance->smcCurrTouchUp;
		phyStateMachineInstance->smcPrevTouchDown = phyStateMachineInstance->smcCurrTouchDown;
	}

	// push chanes to transform component
	if (phyMass != 0.0f) {
		if (NULL != phyTxfInstance) {
			phyTxfInstance->txfPosition = phyCurrPos;
		}
	}
	else {
		phyCurrPos = phyTxfInstance->txfPosition;
	}

}
void PhysicsComponent::comDraw() {

}
void PhysicsComponent::comHandleEvents() {

}

void PhysicsComponent::testAddVelocity(vec3 _v) {
	phyCurrVel.x = _v.x;
	phyCurrVel.y = _v.y;
	phyCurrVel.z = _v.z;
}
