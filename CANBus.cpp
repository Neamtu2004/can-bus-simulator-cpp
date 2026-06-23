#include "CANBus.h"
#include "CANNode.h"
void CanBus::addNode(CANNode* node)
{
	this->nodes.push_back(node);
}
void CanBus::sendMessage(const CANMessage& message)
{
	for (CANNode* node : this->nodes)
	{
		node->receiveMessage(message);
	}
}