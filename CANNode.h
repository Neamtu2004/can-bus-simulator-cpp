
#pragma once
#include "CANMessage.h"
#include <string>
#include <vector>
using namespace std;
class CANNode
{
public:
	virtual void receiveMessage(const CANMessage& message) = 0;
	virtual string getName() const = 0;
	virtual ~CANNode() = default;
};