
//+--------+----------+-------------+----------------------------------+------------+-------------------+
//| nIndex | FileName | ServicePack | ServicePack1                     | AlterData  | Description       |
//+--------+----------+-------------+----------------------------------+------------+-------------------+
//|      1 | calc.exe |             | 60b7c0fead45f2066e5b805a91f4f0fc | 2012-12-12 | windows¼ÆËãÆ÷³ÌÐò |
//+--------+----------+-------------+----------------------------------+------------+-------------------+
//create table Win7Md5Check(nIndex int(3) not null primary key auto_increment,
//FileName varchar(200),
//ServicePack varchar(32),
//ServicePack1 varchar(32),
//AlterData date,
//Description varchar(256));
typedef struct _QUERY_STRUCT
{
	char szFileName[200];
	char szFileMd5[32];
	char szDescription[256];
}QUERY_STRUCT,*PQUERY_STRUCT;


BOOL QueryInfoFromMd5AndSystemWin7Sp1(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData);
BOOL QueryInfoFromMd5AndSystemWin7Sp(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData);
BOOL QueryInfoFromMd5AndSystemWinXpSp(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData);
BOOL QueryInfoFromMd5AndSystemWinXpSp3(char *szMd5,char *szFileName,OUT PQUERY_STRUCT pQueryData);
BOOL QueryInfoFromMd5AndGame(char *szMd5,char *szFileName,OUT BOOL *bIsRunFlag,OUT PQUERY_STRUCT pQueryData);
BOOL QueryInfoFromMd5AndSoftWare(char *szMd5,char *szFileName,OUT BOOL *bIsRunFlag,OUT PQUERY_STRUCT pQueryData);