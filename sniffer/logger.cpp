#include "logger.h"

#include <vector>

#include <WinSock2.h>
#include <Windows.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <nlohmann/json.hpp>

#include "util.h"

Logger::Logger()
{
	// Gets timestamp
	auto init_timestamp = boost::posix_time::second_clock::universal_time();

	// Creates path on current folder, using timestamp as filename, extension .snif.
	auto file_path = boost::filesystem::current_path() / boost::posix_time::to_iso_string(init_timestamp);
	file_path.replace_extension(".ndjson");

	// Creates the output file
	output.open(file_path);
}

void Logger::append_packet(std::string source, SOCKET s, const char* buf, int len)
{
	// Gets the server ip:port
	std::string server = socket_to_ipport(s);

	// Gets the time when packet arrived
	auto arrival_timestamp = boost::posix_time::second_clock::universal_time();
	std::string timestamp = boost::posix_time::to_simple_string(arrival_timestamp);

	// Creates buffer string
	std::string buffer = hex_to_string(buf, len);

	// Creates json structure
	auto packet = nlohmann::json{
		{"timestamp", timestamp},
		{"server", server},
		{"source", source},
		{"buffer", buffer}
	};

	// Writes to the output file stream
	output << packet << std::endl << std::flush;
}