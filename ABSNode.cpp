#pragma once

#include "ABSNode.h"
#include "CANMessage.h"
#include "CANBus.h" 
#include <string>
#include <iostream>

ABSNode::ABSNode(float wheelSpeed)
{
	this->wheelSpeed = wheelSpeed;
	this->absActive = false;
}
std::string ABSNode::getName() const
{
	return "ABSNode";
}
void ABSNode::receiveMessage(const CANMessage& message)
{
	// Procesarea mesajului CAN
	if (message.getId() == 0x100) // Exemplu: ID-ul pentru mesajele de frânare
	{
		// Extrage datele din mesaj și actualizează starea ABS
		const std::vector<uint8_t>& data = message.getData();
		if (!data.empty())
		{
			this->absActive = (data[0] > 0); // Exemplu: primul byte indică activarea ABS
			std::cout << "[ABSNode] Mesaj primit de la: "
				<< message.getSenderName()
				<< ", ID: " << message.getId()
				<< ", ABS activ: " << (this->absActive ? "Da" : "Nu") << std::endl;
		}
	}
}
void ABSNode::sendData(CanBus& bus)
{
	std::vector<uint8_t> data;
	data.push_back(this->absActive ? 1 : 0); // Byte care indică dacă ABS-ul este activ
	CANMessage message(0x200, data, getName()); // ID-ul pentru mesajele de stare ABS
	bus.sendMessage(message);
}
