#include "Dashboard.h"
#include <iostream>


std::string Dashboard::getName() const
{
	return "Dashboard";
}
void Dashboard::receiveMessage(const CANMessage& message)
{
	if (message.getId() == 0x100)
	{
		const std::vector<uint8_t>& data = message.getData();
		if (data.size() >= 4)  // verifica ca avem toti bytes
		{
			int rpm = (data[0] << 8) | data[1];
			float temperature = ((data[2] << 8) | data[3]) / 10.0f;
			std::cout << "[Dashboard] Mesaj primit de la: "
				<< message.getSenderName()
				<< ", RPM: " << rpm
				<< ", Temp: " << temperature << "C" << std::endl;
		}
	}
	else if (message.getId() == 0x200)
	{
		const std::vector<uint8_t>& data = message.getData();
		if (!data.empty())
		{
			bool absActive = (data[0] > 0);
			std::cout << "[Dashboard] Mesaj primit de la: "
				<< message.getSenderName()
				<< ", ID: " << message.getId()
				<< ", ABS activ: " << (absActive ? "Da" : "Nu") << std::endl;
		}
	}
	else {
		std::cout << "[Dashboard] Mesaj primit de la: "
			<< message.getSenderName()
			<< ", ID: " << message.getId() << std::endl;
	}
}

