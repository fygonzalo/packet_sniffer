#include "hook.h"

#include <WinSock2.h>
#include <Windows.h>

#include <detours.h>

#include "logger.h"

// Winsock2 functions.
int (WINAPI *real_send)(SOCKET s, const char* buf, int len, int flags) = send;
int (WINAPI *real_recv)(SOCKET s, char* buf, int len, int flags) = recv;

// Custom functions definition.
int WINAPI custom_send(SOCKET s, const char* buf, int len, int flags);
int WINAPI custom_recv(SOCKET s, char* buf, int len, int flags);

// Global logger to be accessed from custom send/recv functions.
Logger logger;

bool hook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Tries to attach custom send function
	LONG send_error = DetourAttach(&(PVOID&)real_send, custom_send);
	if (send_error != NO_ERROR)
	{
		// Failed
		const char * message = "There was a problem hooking send function.\nError code: " + send_error;
		MessageBoxA(GetTopWindow(NULL), message, "PACKET SNIFFER - ERROR", MB_ICONERROR | MB_OK);

		return false;
	}

	// Tries to attach custom recv function
	LONG recv_error = DetourAttach(&(PVOID&)real_recv, custom_recv);
	if (recv_error != NO_ERROR)
	{
		// Failed
		const char * message = "There was a problem hooking recv function.\nError code: " + recv_error;
		MessageBoxA(GetTopWindow(NULL), message, "PACKET SNIFFER - ERROR", MB_ICONERROR | MB_OK);

		return false;
	}

	DetourTransactionCommit();

	// Hook was suscefull. Shows disclaimer and returns.
	const char* disclaimer = "WARNING: All network data that goes through this "
		"program will be logged."
		"\n\nDo you want to continue?";
	if (MessageBox(NULL, disclaimer, "PACKET SNIFFER", MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
	{
		return true;
	}

	return false;
}

int WINAPI custom_send(SOCKET s, const char* buf, int len, int flags)
{
	// Replicates real procedure
	int send_result = real_send(s, buf, len, flags);

	if (send_result > 0)
	{
		// There wasn't any error. Save the packet.
		logger.append_packet(PACKETSOURCE_CLIENT, s, buf, send_result);
	}

	// Replicates real procedure
	return send_result;
}

int WINAPI custom_recv(SOCKET s, char* buf, int len, int flags)
{
	// Replicates real procedure
	int recv_result = real_recv(s, buf, len, flags);

	if (recv_result > 0)
	{
		// There wasn't any error. Save the packet.
		logger.append_packet(PACKETSOURCE_SERVER, s, buf, recv_result);
	}

	// Replicates real procedure
	return recv_result;
}