#include "stdafx.h"
#include "X_ElokoDataBase.h"
#include "X_QueryCheck.h"

BOOL QueryInfoFromMd5AndSystemWin7Sp1(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData)
{
	MYSQL_RES *MySqlRes;
	MYSQL_ROW MySqlRow;
	BOOL bRet;
	char szCommand[MAX_PATH];
	int nRet;
	int j;

	j = 0;
	bRet = FALSE;
	RtlZeroMemory(szCommand,sizeof(char)*MAX_PATH);

	sprintf_s(szCommand,"select ServicePack1 from %s where FileName=\'%s\'","win7md5check",szFileName);
	nRet = mysql_query(hMySqlWin7CheckMd5,szCommand);
	if (!nRet)
	{
		MySqlRes = mysql_store_result(hMySqlWin7CheckMd5);
		while(MySqlRow = mysql_fetch_row(MySqlRes))
		{
			if (strcmp(MySqlRow[0],szMd5) == 0)
			{
				bRet = TRUE;
			}
			else
			{
				bRet = FALSE;
			}
		}
	}
	if (MySqlRes != NULL)
	{
		mysql_free_result(MySqlRes);
	}
	return bRet;
}
BOOL QueryInfoFromMd5AndSystemWin7Sp(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData)
{
	MYSQL_RES *MySqlRes;
	MYSQL_ROW MySqlRow;
	BOOL bRet;
	char szCommand[MAX_PATH];
	int nRet;
	int j;

	j = 0;
	bRet = FALSE;
	RtlZeroMemory(szCommand,sizeof(char)*MAX_PATH);
	sprintf_s(szCommand,"select ServicePack from %s where FileName=\'%s\'","win7md5check",szFileName);
	nRet = mysql_query(hMySqlWin7CheckMd5,szCommand);
	if (!nRet)
	{
		MySqlRes = mysql_store_result(hMySqlWin7CheckMd5);
		while(MySqlRow = mysql_fetch_row(MySqlRes))
		{
			if (strcmp(MySqlRow[0],szMd5) == 0)
			{
				bRet = TRUE;
			}
			else
			{
				bRet = FALSE;
			}
		}
	}
	if (MySqlRes != NULL)
	{
		mysql_free_result(MySqlRes);
	}
	return bRet;
}
BOOL QueryInfoFromMd5AndSystemWinXpSp(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData)
{
	MYSQL_RES *MySqlRes;
	MYSQL_ROW MySqlRow;
	BOOL bRet;
	char szCommand[MAX_PATH];
	int nRet;
	int j;

	j = 0;
	bRet = FALSE;
	RtlZeroMemory(szCommand,sizeof(char)*MAX_PATH);
	sprintf_s(szCommand,"select ServicePack from %s where FileName=\'%s\'","winxpmd5check",szFileName);
	nRet = mysql_query(hMySqlWinXpCheckMd5,szCommand);
	if (!nRet)
	{
		MySqlRes = mysql_store_result(hMySqlWinXpCheckMd5);
		while(MySqlRow = mysql_fetch_row(MySqlRes))
		{
			if (strcmp(MySqlRow[0],szMd5) == 0)
			{
				bRet = TRUE;
			}
			else
			{
				bRet = FALSE;
			}
		}
	}
	if (MySqlRes != NULL)
	{
		mysql_free_result(MySqlRes);
	}
	return bRet;
}
BOOL QueryInfoFromMd5AndSystemWinXpSp3(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData)
{
	MYSQL_RES *MySqlRes;
	MYSQL_ROW MySqlRow;
	BOOL bRet;
	char szCommand[MAX_PATH];
	int nRet;
	int j;

	j = 0;
	bRet = FALSE;
	RtlZeroMemory(szCommand,sizeof(char)*MAX_PATH);
	sprintf_s(szCommand,"select ServicePack3 from %s where FileName=\'%s\'","winxpmd5check",szFileName);
	nRet = mysql_query(hMySqlWinXpCheckMd5,szCommand);
	if (!nRet)
	{
		MySqlRes = mysql_store_result(hMySqlWinXpCheckMd5);
		while(MySqlRow = mysql_fetch_row(MySqlRes))
		{
			if (strcmp(MySqlRow[0],szMd5) == 0)
			{
				bRet = TRUE;
			}
			else
			{
				bRet = FALSE;
			}
		}
	}
	if (MySqlRes != NULL)
	{
		mysql_free_result(MySqlRes);
	}
	return bRet;
}
BOOL QueryInfoFromMd5AndGame(char *szMd5,char *szFileName,OUT BOOL *bIsRunFlag,OUT PQUERY_STRUCT pQueryData)
{
	MYSQL_RES *MySqlRes;
	MYSQL_ROW MySqlRow;
	BOOL bRet;
	int nRet;
	char *szTable;
	char *szCurrent;
	char *szCommand;
	unsigned int num_fields;

	bRet = FALSE;
	if (mysql_query(hMySqlGameCheckMd5,"show tables"))
	{
		//error
	}
	else
	{
		MySqlRes = mysql_store_result(hMySqlGameCheckMd5);
		if (MySqlRes)
		{
			num_fields = mysql_num_rows(MySqlRes);
			szTable = (char*)malloc(num_fields*sizeof(char)*32);
			if (szTable == NULL)
			{
				//error
			}
			RtlZeroMemory(szTable,num_fields*sizeof(char)*32);
			szCurrent = szTable;
			while (MySqlRow = mysql_fetch_row(MySqlRes))
			{
				strncpy(szCurrent,MySqlRow[0],strlen(MySqlRow[0]));
				szCurrent[strlen(MySqlRow[0])] = '\0';
				szCurrent = szCurrent + strlen(MySqlRow[0]) + 1;
			}
			szCurrent = szTable;
			if (MySqlRes)
			{
				mysql_free_result(MySqlRes);
			}
			szCommand = (char*)malloc(strlen(szTable) + sizeof(char) * MAX_PATH);
			if (szCommand == NULL)
			{
				//error
			}
			RtlZeroMemory(szCommand,strlen(szTable) + sizeof(char) * MAX_PATH);
			for (int i = 0;i < num_fields;i++)
			{
				sprintf(szCommand,"select ServicePack from %s where FileName=\'%s\'",szCurrent,szFileName);
				nRet = mysql_query(hMySqlSoftWareCheckMd5,szCommand);
				if (!nRet)
				{
					MySqlRes = mysql_store_result(hMySqlSoftWareCheckMd5);
					while(MySqlRow = mysql_fetch_row(MySqlRes))
					{
						if (strncmp(szMd5,MySqlRow[0],strlen(szMd5)) == 0)
						{
							bRet = TRUE;
							break;
						}
						else
						{
							bRet = FALSE;
							break;
						}
					}
				}
				if (bRet == TRUE)
				{
					if (MySqlRes != NULL)
					{
						mysql_free_result(MySqlRes);
						sprintf(szCommand,"select Flag from %s where FileName=\'%s\'",szCurrent,szFileName);
						nRet = mysql_query(hMySqlSoftWareCheckMd5,szCommand);
						if (!nRet)
						{
							MySqlRes = mysql_store_result(hMySqlSoftWareCheckMd5);
							if (MySqlRes)
							{
								while (MySqlRow = mysql_fetch_row(MySqlRes))
								{
									if (strcmp(MySqlRow[0],"1") == 0)
									{
										*bIsRunFlag = TRUE;
									}
									else
									{
										*bIsRunFlag = FALSE;
									}
								}
							}
							break;
						}
					}

				}
				szCurrent = szCurrent + strlen(szCurrent) + 1;
			}
		}
	}
	if (szCommand)
	{
		free(szCommand);
	}
	if (szTable)
	{
		free(szTable);
	}
	if (MySqlRes != NULL)
	{
		mysql_free_result(MySqlRes);
	}
	return bRet;
}
BOOL QueryInfoFromMd5AndSoftWare(char *szMd5,char *szFileName,OUT BOOL *bIsRunFlag,OUT PQUERY_STRUCT pQueryData)
{
	MYSQL_RES *MySqlRes;
	MYSQL_ROW MySqlRow;
	BOOL bRet;
	int nRet;
	char *szTable;
	char *szCurrent;
	char *szCommand;
	unsigned int num_fields;

	bRet = FALSE;
	if (mysql_query(hMySqlSoftWareCheckMd5,"show tables"))
	{
		//error
	}
	else
	{
		MySqlRes = mysql_store_result(hMySqlSoftWareCheckMd5);
		if (MySqlRes)
		{
			num_fields = mysql_num_rows(MySqlRes);
			szTable = (char*)malloc(num_fields*sizeof(char)*32);
			if (szTable == NULL)
			{
				//error
			}
			RtlZeroMemory(szTable,num_fields*sizeof(char)*32);
			szCurrent = szTable;
			while (MySqlRow = mysql_fetch_row(MySqlRes))
			{
				strncpy(szCurrent,MySqlRow[0],strlen(MySqlRow[0]));
				szCurrent[strlen(MySqlRow[0])] = '\0';
				szCurrent = szCurrent + strlen(MySqlRow[0]) + 1;
			}
			szCurrent = szTable;
			if (MySqlRes)
			{
				mysql_free_result(MySqlRes);
			}
			szCommand = (char*)malloc(strlen(szTable) + sizeof(char) * MAX_PATH);
			if (szCommand == NULL)
			{
				//error
			}
			RtlZeroMemory(szCommand,strlen(szTable) + sizeof(char) * MAX_PATH);
			for (int i = 0;i < num_fields;i++)
			{
				sprintf(szCommand,"select ServicePack from %s where FileName=\'%s\'",szCurrent,szFileName);
				nRet = mysql_query(hMySqlSoftWareCheckMd5,szCommand);
				if (!nRet)
				{
					MySqlRes = mysql_store_result(hMySqlSoftWareCheckMd5);
					while(MySqlRow = mysql_fetch_row(MySqlRes))
					{
						if (strncmp(szMd5,MySqlRow[0],strlen(szMd5)) == 0)
						{
							bRet = TRUE;
							break;
						}
						else
						{
							bRet = FALSE;
							break;
						}
					}
				}
				if (bRet == TRUE)
				{
					if (MySqlRes != NULL)
					{
						mysql_free_result(MySqlRes);
						sprintf(szCommand,"select Flag from %s where FileName=\'%s\'",szCurrent,szFileName);
						nRet = mysql_query(hMySqlSoftWareCheckMd5,szCommand);
						if (!nRet)
						{
							MySqlRes = mysql_store_result(hMySqlSoftWareCheckMd5);
							if (MySqlRes)
							{
								while (MySqlRow = mysql_fetch_row(MySqlRes))
								{
									if (strcmp(MySqlRow[0],"1") == 0)
									{
										*bIsRunFlag = TRUE;
									}
									else
									{
										*bIsRunFlag = FALSE;
									}
								}
							}
							break;
						}
					}

				}
				szCurrent = szCurrent + strlen(szCurrent) + 1;
			}
		}
	}
	if (szCommand)
	{
		free(szCommand);
	}
	if (szTable)
	{
		free(szTable);
	}
	if (MySqlRes != NULL)
	{
		mysql_free_result(MySqlRes);
	}
	return bRet;
}