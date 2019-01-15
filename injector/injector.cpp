#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include <Windows.h>
#include <detours.h>

bool start_process(boost::filesystem::path executable_path, boost::filesystem::path library_path)
{
	// Initializes auxiliary vars
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	// Starts the process
	bool process_created = DetourCreateProcessWithDllEx(
		executable_path.string().c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_DEFAULT_ERROR_MODE,
		NULL,
		executable_path.parent_path().string().c_str(),
		&si,
		&pi,
		library_path.string().c_str(),
		NULL);

	return process_created;
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: injector <library> <executable>" << std::endl;
		return 0;
	}

	boost::filesystem::path library_path = boost::filesystem::absolute(argv[1]);
	if (!boost::filesystem::exists(library_path))
	{
		std::cerr << "Could not find library " << library_path << std::endl;
		return 0;
	}

	boost::filesystem::path executable_path = boost::filesystem::absolute(argv[2]);
	if (!boost::filesystem::exists(executable_path))
	{
		std::cerr << "Could not find executable " << executable_path << std::endl;
		return 0;
	}

	if (!start_process(executable_path, library_path))
	{
		std::cerr << "There was a problem starting the process." << std::endl;
		return 0;
	}

	return 0;
}
