#pragma once
#include "CANNode.h"
#include "CanBus.h"

class ABSNode : public CANNode
{
private:
    float wheelSpeed;    // viteza rotilor in km/h
    bool absActive;      // true daca ABS-ul e activ

public:
    ABSNode(float wheelSpeed);
    void receiveMessage(const CANMessage& message) override;
    std::string getName() const override;
    void sendData(CanBus& bus);
};