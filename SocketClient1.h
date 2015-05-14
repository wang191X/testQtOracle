#pragma once
#include "SocketClient.h"
#include "DataStruct.h"

class SocketClient1 :
	public SocketClient
{
public:
	SocketClient1(boost::asio::io_service& io_service_);
	~SocketClient1(void);

	std::vector<SACL> sacls_;

private:
			
			std::string outbound_data_;
			std::vector<char> inbound_data_;

	void toSerialize();
	void fromSerialize();

public:
	void sendData1();
	int recvData1();
};
