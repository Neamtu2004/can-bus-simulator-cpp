#include <vector>
#include <string>
#include <cstdint>
#include "CANMessage.h"
#include <iostream>


CANMessage::CANMessage(int id, std::vector<uint8_t> data, std::string senderName)
{
	this->id = id;
	this->data = data;
	this->senderName = senderName;
}
int CANMessage::getId() const
{
	return this->id;
}
std::vector<uint8_t> CANMessage::getData() const
{
	return this->data;
}
std::string CANMessage::getSenderName() const
{
	return this->senderName;
}