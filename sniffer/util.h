#pragma once

constexpr char hex_map[] = { '0', '1', '2', '3', '4', '5', '6', '7',
						   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

/**
	Generates a string with the hex representation of a buffer.
*/
std::string hex_to_string(const char * buf, int len)
{
	// Allocates two times len because two hex numbers are needed per char.
	std::string s(len * 2, ' ');

	// Iterates over all characters
	for (int i = 0; i < len; ++i) {
		// Extracts hi and lo from current char then map to its hex representation.
		// Faster than casting each char into an hex string stream
		s[2 * i] = hex_map[((unsigned char)*buf & 0xF0) >> 4];
		s[2 * i + 1] = hex_map[(unsigned char)*buf & 0x0F];

		buf++;
	}
	return s;
}

/**
	Creates a string with format "ip:port" from a socket connection.
*/
std::string socket_to_ipport(SOCKET s)
{
	// Auxiliary vars.
	sockaddr_in address;
	int address_size = sizeof(address);

	// Gets socket information.
	getpeername(s, (sockaddr *)&address, &address_size);

	// Parses socket information to a string stream. Easier than doing an explicit
	// transformation.
	std::stringstream ss;
	ss << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port);

	// Returns the string.
	return ss.str();

}