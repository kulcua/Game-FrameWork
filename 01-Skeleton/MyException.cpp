#include "pch.h"
#include "MyException.h"

void debug_out(char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	char dbg_out[4096];
	vsprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

MyException::MyException(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
{
	std::ostringstream ss;
	ss << "[Exception]: " << msg << "\n";
	ss << "[Line]: " << line << "\n";
	ss << "[Func]: " << func << "\n";
	ss << "[File]: " << file << "\n";
	msgOut = ss.str();
}

void MyException::Throw(LPCSTR msg, UINT line, LPCSTR func, LPCSTR file)
{
	MyException ex(msg, line, func, file);
	DebugOut(ex.what());
	throw ex;
}