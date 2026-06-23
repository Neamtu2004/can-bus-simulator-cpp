#pragma once
#include <vector>
#include <string>
#include <cstdint>

class CANMessage
{
private:
	int id;
	std::vector<uint8_t> data;
	std::string senderName;
public:
	CANMessage(int id, std::vector<uint8_t> data, std::string senderName);
	int getId() const;
	std::vector<uint8_t> getData() const;
	std::string getSenderName() const;
};