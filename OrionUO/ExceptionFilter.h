//----------------------------------------------------------------------------------
#ifndef EXCEPTIONFILTER_H
#define EXCEPTIONFILTER_H
//----------------------------------------------------------------------------------
#include "Globals.h"
//----------------------------------------------------------------------------------
LONG __stdcall OrionUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo);
//----------------------------------------------------------------------------------
#endif //EXCEPTIONFILTER_H
//----------------------------------------------------------------------------------
