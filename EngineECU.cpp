#include <iostream>
#include "EngineECU.h"



	EngineECU::EngineECU(int rpm, float temperature)
	{
		this->rpm = rpm;
		this->temperature = temperature;
	}

	std::string EngineECU::getName() const
	{
		return "EngineECU";
	}
	void EngineECU::receiveMessage(const CANMessage& message)
	{
		if (message.getId() == 0x200) // doar mesaje ABS (viteza rotilor)
		{
			std::cout << "[EngineECU] Mesaj primit de la: "
				<< message.getSenderName()
				<< ", ID: " << message.getId() << std::endl;
		}
	}
	void EngineECU::sendData(CanBus& bus)
	{
		uint16_t temp = static_cast<uint16_t>(temperature * 10);

		std::vector<uint8_t> data;
		data.push_back(static_cast<uint8_t>(rpm >> 8));      // rpm high
		data.push_back(static_cast<uint8_t>(rpm & 0xFF));    // rpm low
		data.push_back(static_cast<uint8_t>(temp >> 8));     // temp high
		data.push_back(static_cast<uint8_t>(temp & 0xFF));   // temp low

		CANMessage message(0x100, data, getName());
		bus.sendMessage(message);
	}