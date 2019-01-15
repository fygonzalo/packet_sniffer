#pragma once
#include <WinSock2.h>
#include <Windows.h>

#include <boost/filesystem/fstream.hpp>

#define PACKETSOURCE_SERVER "Server"
#define PACKETSOURCE_CLIENT "Client"

class Logger
{
public:
	Logger();
	void append_packet(std::string source, SOCKET s, const char * buf, int len);
private:
	boost::filesystem::ofstream output;
};