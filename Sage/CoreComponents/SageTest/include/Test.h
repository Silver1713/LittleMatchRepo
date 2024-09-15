#include <cstdarg>
#include <cstdio>

void headerOnlyPrintf(const char* str, ...)
{
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);

}