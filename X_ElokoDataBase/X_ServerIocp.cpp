#include "stdafx.h"
#include <vector> 
#include <iostream>
#include "X_InitDataBase.h"
#include "X_QueryCheck.h"
#include "X_ServerIocp.h"

#pragma warning(disable:4018)

HANDLE hMutex = NULL;
using namespace std;
vector < PER_HANDLE_DATA* > ClientGroup;
BOOL StartIOCPServer()
{
	WSADATA WsaData;
	WORD wVersionRequested = MAKEWORD(2,2);
	hMutex = CreateMutex(NULL,FALSE,NULL);
	DWORD dwError = WSAStartup(wVersionRequested,&WsaData);
	if (dwError)
	{
		OutputDebugString(L"Request Windows Socket Library Error!\n");
		return FALSE;
	}
	//if (LOBYTE(WsaData.wVersion != 2) || HIBYTE(WsaData.wVersion) != 2)
	//{
	//	WSACleanup();
	//	OutputDebugString(L"Request Windows Socket Version 2.2 Error!\n");
	//	return FALSE;
	//}
	HANDLE hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
	if (NULL == hCompletionPort)
	{
		OutputDebugString(L"CreateIoCompletionPort failed.\n");
		return FALSE;
	}
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	for (int i = 0;i < 1/*(SystemInfo.dwNumberOfProcessors * 2)*/;i++)
	{
		HANDLE hThread = CreateThread(NULL,0,ServerWorkThread,hCompletionPort,0,NULL);
		if (NULL == hThread)
		{
			CloseHandle(hThread);
			OutputDebugString(L"Create Thread Handle failed.\n");
			return FALSE;
		}
		CloseHandle(hThread);
	}

	SOCKET SrvSocket = socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN SrvAddr;
	SrvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	SrvAddr.sin_family = AF_INET;
	SrvAddr.sin_port = htons(DefaultPort);
	
	int BindResult = bind(SrvSocket,(SOCKADDR*)&SrvAddr,sizeof(SOCKADDR));
	if (SOCKET_ERROR == BindResult)
	{
		OutputDebugString(L"Bind failed.\n");
		return FALSE;
	}

	int ListenResult = listen(SrvSocket,10);
	if (SOCKET_ERROR == ListenResult)
	{
		OutputDebugString(L"Listen failed.\n");
		return FALSE;
	}
	OutputDebugString(L"服务器已准备就绪，等待客户端接入...\n");
	//HANDLE hSendThread = CreateThread(NULL,0,ServerSendThread,0,0,NULL);
	while (TRUE)
	{
		PER_HANDLE_DATA *pPerHandleData = NULL;
		SOCKADDR_IN SockRemote;
		int RemoteLen;
		SOCKET AcceptSocket;

		RemoteLen = sizeof(SockRemote);
		AcceptSocket = accept(SrvSocket,(SOCKADDR*)&SockRemote,&RemoteLen);
		if (SOCKET_ERROR == AcceptSocket)
		{
			OutputDebugString(L"Accept Socket Error.\n");
			return FALSE;
		}

		pPerHandleData = (PPER_HANDLE_DATA)GlobalAlloc(GPTR,sizeof(PER_HANDLE_DATA));
		pPerHandleData->Socket = AcceptSocket;
		memcpy(&pPerHandleData->ClientAddr,&SockRemote,RemoteLen);
		ClientGroup.push_back(pPerHandleData);

		CreateIoCompletionPort((HANDLE)(pPerHandleData->Socket),hCompletionPort,(DWORD)pPerHandleData,0);

		PPER_IO_OPERATEION_DATA pPerIoOperateionData = NULL;
		pPerIoOperateionData = (PPER_IO_OPERATEION_DATA)GlobalAlloc(GPTR,sizeof(PER_IO_OPERATEION_DATA));
		ZeroMemory(&(pPerIoOperateionData->OverLapped),sizeof(OVERLAPPED));
		pPerIoOperateionData->DataBuff.len = 1024;
		pPerIoOperateionData->DataBuff.buf = pPerIoOperateionData->buffer;
		pPerIoOperateionData->OperationType = 0;   //read

		DWORD dwRecvBytes;
		DWORD dwFlags = 0;
		WSARecv(pPerHandleData->Socket,&(pPerIoOperateionData->DataBuff),1,&dwRecvBytes,&dwFlags,&(pPerIoOperateionData->OverLapped),NULL);
		pPerHandleData->pRecvQueryInfo = (PRECV_QUERY_INFORMATION)pPerIoOperateionData->DataBuff.buf;
	}
}

DWORD WINAPI ServerWorkThread(LPVOID lpParam)
{
	HANDLE hCompletionPort = (HANDLE)lpParam;
	DWORD dwBytesTransferred;
	LPOVERLAPPED lpOverLapped;
	PPER_HANDLE_DATA pPerHandleData = NULL;
	PPER_IO_OPERATEION_DATA pPerIoData = NULL;
//	DWORD dwRecvBytes;
	DWORD dwFlags = 0;
	BOOL bRet = FALSE;

	while (TRUE)
	{
		bRet = GetQueuedCompletionStatus(hCompletionPort,&dwBytesTransferred,(PULONG_PTR)&pPerHandleData,(LPOVERLAPPED*)&lpOverLapped,INFINITE);
		if (bRet == FALSE)
		{
			OutputDebugString(L"GetQueuedCompletionStatus error.\n");
		}
		pPerIoData = (PPER_IO_OPERATEION_DATA)CONTAINING_RECORD(lpOverLapped,PER_IO_OPERATEION_DATA,OverLapped);
		if (0 == dwBytesTransferred)
		{
			closesocket(pPerHandleData->Socket);
			GlobalFree(pPerHandleData);
			GlobalFree(pPerIoData);
			continue;
		}

		//WaitForSingleObject(hMutex,INFINITE);
		//OutputDebugString()
		pPerHandleData->pRecvQueryInfo = (PRECV_QUERY_INFORMATION)pPerIoData->DataBuff.buf;
		if (strncmp(pPerHandleData->pRecvQueryInfo->szSystemVersion,"win7",strlen(pPerHandleData->pRecvQueryInfo->szSystemVersion)) == 0)
		{
			pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSystemWin7Sp(pPerHandleData->pRecvQueryInfo->szQueryMd5,pPerHandleData->pRecvQueryInfo->szQueryFileName,NULL);
			if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
			{
				//查询游戏
				//查询软件
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndGame(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
					pPerHandleData->pRecvQueryInfo->szQueryFileName, \
					&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
					NULL);
				if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSoftWare(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
						pPerHandleData->pRecvQueryInfo->szQueryFileName, \
						&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
						NULL);
					if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = FALSE;
					}
					else
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
						pPerHandleData->pRecvQueryInfo->bIsSoftWare = TRUE;
					}
				}
				else
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
					pPerHandleData->pRecvQueryInfo->bIsGameFile = TRUE;
				}
			}
			else
			{
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
				pPerHandleData->pRecvQueryInfo->bIsSystemFile = TRUE;
			}
			
		}
		else if (strncmp(pPerHandleData->pRecvQueryInfo->szSystemVersion,"win7sp1",strlen(pPerHandleData->pRecvQueryInfo->szSystemVersion)) == 0)
		{
			pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSystemWin7Sp1(pPerHandleData->pRecvQueryInfo->szQueryMd5,pPerHandleData->pRecvQueryInfo->szQueryFileName,NULL);
			if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
			{
				//查询游戏
				//查询软件
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndGame(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
					pPerHandleData->pRecvQueryInfo->szQueryFileName, \
					&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
					NULL);
				if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSoftWare(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
						pPerHandleData->pRecvQueryInfo->szQueryFileName, \
						&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
						NULL);
					if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = FALSE;
					}
					else
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
						pPerHandleData->pRecvQueryInfo->bIsSoftWare = TRUE;
					}
				}
				else
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
					pPerHandleData->pRecvQueryInfo->bIsGameFile = TRUE;
				}
			}
			else
			{
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
				pPerHandleData->pRecvQueryInfo->bIsSystemFile = TRUE;
			}
		}
		else if (strncmp(pPerHandleData->pRecvQueryInfo->szSystemVersion,"winxpsp2",strlen(pPerHandleData->pRecvQueryInfo->szSystemVersion)) == 0)
		{
			pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSystemWinXpSp(pPerHandleData->pRecvQueryInfo->szQueryMd5,pPerHandleData->pRecvQueryInfo->szQueryFileName,NULL);
			if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
			{
				//查询游戏
				//查询软件
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndGame(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
					pPerHandleData->pRecvQueryInfo->szQueryFileName, \
					&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
					NULL);
				if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSoftWare(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
						pPerHandleData->pRecvQueryInfo->szQueryFileName, \
						&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
						NULL);
					if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = FALSE;
					}
					else
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
						pPerHandleData->pRecvQueryInfo->bIsSoftWare = TRUE;
					}
				}
				else
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
					pPerHandleData->pRecvQueryInfo->bIsGameFile = TRUE;
				}
			}
			else
			{
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
				pPerHandleData->pRecvQueryInfo->bIsSystemFile = TRUE;
			}
		}
		else if (strncmp(pPerHandleData->pRecvQueryInfo->szSystemVersion,"winxpsp3",strlen(pPerHandleData->pRecvQueryInfo->szSystemVersion)) == 0)
		{
			pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSystemWinXpSp3(pPerHandleData->pRecvQueryInfo->szQueryMd5,pPerHandleData->pRecvQueryInfo->szQueryFileName,NULL);
			if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
			{
				//查询游戏
				//查询软件
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndGame(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
					pPerHandleData->pRecvQueryInfo->szQueryFileName, \
					&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
					NULL);
				if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = QueryInfoFromMd5AndSoftWare(pPerHandleData->pRecvQueryInfo->szQueryMd5, \
						pPerHandleData->pRecvQueryInfo->szQueryFileName, \
						&pPerHandleData->pRecvQueryInfo->bIsRunFlag, \
						NULL);
					if (pPerHandleData->pRecvQueryInfo->bIsNotEqu == FALSE)
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = FALSE;
					}
					else
					{
						pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
						pPerHandleData->pRecvQueryInfo->bIsSoftWare = TRUE;
					}
				}
				else
				{
					pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
					pPerHandleData->pRecvQueryInfo->bIsGameFile = TRUE;
				}
			}
			else
			{
				pPerHandleData->pRecvQueryInfo->bIsNotEqu = 1;
				pPerHandleData->pRecvQueryInfo->bIsSystemFile = TRUE;
			}
		}
		else if (strncmp(pPerHandleData->pRecvQueryInfo->szSystemVersion,"winvista",strlen(pPerHandleData->pRecvQueryInfo->szSystemVersion)) == 0)
		{

		}
		else
		{
		}
		send(pPerHandleData->Socket,(char*)pPerHandleData->pRecvQueryInfo,sizeof(RECV_QUERY_INFORMATION),0);
		//ReleaseMutex(hMutex);

		ZeroMemory(&(pPerIoData->OverLapped),sizeof(OVERLAPPED));
		pPerIoData->DataBuff.len = 1024;
		pPerIoData->DataBuff.buf = pPerIoData->buffer;
		pPerIoData->OperationType = 0;		//read
		//WSARecv(pPerHandleData->Socket,&(pPerIoData->DataBuff),1,&dwRecvBytes,&dwFlags,&(pPerIoData->OverLapped),NULL);
	}
	return 0;
}

DWORD WINAPI ServerSendThread(LPVOID lpParam)
{
	while (TRUE)
	{
		WaitForSingleObject(hMutex,INFINITE);
		for (int i = 0;i < ClientGroup.size();i++)
		{
			send(ClientGroup[i]->Socket,(char*)ClientGroup[i]->pRecvQueryInfo,sizeof(RECV_QUERY_INFORMATION),0);
		}
		ReleaseMutex(hMutex);
	}
}