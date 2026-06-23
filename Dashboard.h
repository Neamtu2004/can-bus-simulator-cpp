#pragma once
#include "CANNode.h"

class Dashboard : public CANNode
{
public:
	void receiveMessage(const CANMessage& message) override;
	std::string getName() const override;
};