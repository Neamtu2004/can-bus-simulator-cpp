#pragma once
#include "CANNode.h"
#include "CANBus.h"
class EngineECU : public CANNode
{
private:
    int rpm;
    float temperature;

public:
    EngineECU(int rpm, float temperature);
    void receiveMessage(const CANMessage& message) override;
    std::string getName() const override;
    void sendData(CanBus& bus);
};