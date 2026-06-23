#pragma once
#include "CANNode.h"
#include "CANMessage.h"
#include <vector>
class CanBus
{
private:
	std::vector<CANNode*> nodes;
public:
	void addNode(CANNode* node);
	void sendMessage(const CANMessage& message);
};