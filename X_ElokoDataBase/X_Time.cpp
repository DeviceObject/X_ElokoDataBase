#include "stdafx.h"
#include "X_InitDataBase.h"
#include "X_Time.h"

DWORD WINAPI CheckTimeOut(LPVOID lpParam)
{
	while (TRUE)
	{
		Sleep(1000 * 60 * 60 * 7);
		InitLogin();
	}
	return 0;
}