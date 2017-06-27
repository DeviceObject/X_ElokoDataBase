const int DataBuffSize = 2 * 1024;

typedef struct _PER_IO_OPERATEION_DATA
{
	OVERLAPPED OverLapped;
	WSABUF	DataBuff;
	char buffer[DataBuffSize];
	int BufferLen;
	int OperationType;
}PER_IO_OPERATEION_DATA,*PPER_IO_OPERATEION_DATA;
typedef struct _RECV_QUERY_INFORMATION
{
	char szSystemVersion[50];
	char szQueryFileName[100];
	char szQueryMd5[32];
	char szDescriptor[256];
	BOOL bIsNotEqu;
	BOOL bIsSystemFile;
	BOOL bIsGameFile;
	BOOL bIsSoftWare;
	BOOL bIsTrojan;
	BOOL bIsRunFlag;
}RECV_QUERY_INFORMATION,*PRECV_QUERY_INFORMATION;
typedef struct _PER_HANDLE_DATA
{
	SOCKET Socket;
	SOCKADDR ClientAddr;
	PRECV_QUERY_INFORMATION pRecvQueryInfo;
}PER_HANDLE_DATA,*PPER_HANDLE_DATA;

const int DefaultPort = 6000;

// 记录客户端的向量组  



BOOL StartIOCPServer();
DWORD WINAPI ServerWorkThread(LPVOID lpParam);
DWORD WINAPI ServerSendThread(LPVOID lpParam);