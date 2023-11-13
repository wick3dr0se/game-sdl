#pragma once
#include <iostream>
#include "Components.h"
#include "../Network/NetworkManager.h"

class NetworkComponent : public Component
{
public:
	NetworkComponent(std::string objectId, std::string objectType, NetworkManager* networkManager)
		: objectId(objectId), objectType(objectType), networkManager(networkManager) {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

	void update() override
	{
		auto const x = transform->position.x;
		auto const y = transform->position.y;
		auto const message = std::string(std::to_string(x) + " " + std::to_string(y));

		if (message == lastMessage)
			return;

		lastMessage = message;
		networkManager->send(objectId, objectType, message);


		std::cout << message << std::endl;
	}

	TransformComponent* transform;

private:
	std::string lastMessage;
	std::string objectId;
	std::string objectType;
	NetworkManager* networkManager;
};