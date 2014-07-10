/*
 *  winapi.h
 *  
 *
 *  Created by System Administrator on 08-8-11.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
 
#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

#define FILE_SHARE_READ                 0x00000001  
#define FILE_SHARE_WRITE                0x00000002  
#define FILE_SHARE_DELETE               0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001   
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002   
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004   
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008   
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010   
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020   
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040   
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100   
#define FILE_ACTION_ADDED                   0x00000001   
#define FILE_ACTION_REMOVED                 0x00000002   
#define FILE_ACTION_MODIFIED                0x00000003   
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004   
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005   
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1) 
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1) 
#define FILE_CASE_SENSITIVE_SEARCH      0x00000001  
#define FILE_CASE_PRESERVED_NAMES       0x00000002  
#define FILE_UNICODE_ON_DISK            0x00000004  
#define FILE_PERSISTENT_ACLS            0x00000008  
#define FILE_FILE_COMPRESSION           0x00000010  
#define FILE_VOLUME_QUOTAS              0x00000020  
#define FILE_SUPPORTS_SPARSE_FILES      0x00000040  
#define FILE_SUPPORTS_REPARSE_POINTS    0x00000080  
#define FILE_SUPPORTS_REMOTE_STORAGE    0x00000100  
#define FILE_VOLUME_IS_COMPRESSED       0x00008000  
#define FILE_SUPPORTS_OBJECT_IDS        0x00010000  
#define FILE_SUPPORTS_ENCRYPTION        0x00020000  

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

#define INVALID_HANDLE_VALUE (HANDLE)-1

#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation

#include "wintypedef.h"

#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#define lstrcpy(des,src) strcpy((des),(src))

#define _istspace   _ismbcspace
#define _PUC    unsigned char *
#define _CPUC   const unsigned char *
#define _PC     char *
#define _CPC    const char *
#define _UI     unsigned int

static int _ismbcspace( int c )
{
	if(c == 0x20) return 1;
	else return 0;
};

static unsigned char *_mbsinc( const unsigned char *current )
{
	return (unsigned char*)current+1;
};

static char *_mbsupr(  char *str )
{
	int len = strlen(str);
	int i;
	for (i=0; i<len; i++)
	{
		if(str[i]>=0x61 && str[i]<=0x7a)
			str[i] = str[i] - 0x20;
	}
	
	return str;
};

// static char *_strlwr(  char * str)
// {
// 	int len = strlen(str);
// 	int i;
// 	for (i=0; i<len; i++)
// 	{
// 		if(str[i]>=0x41 && str[i]<=0x5a)
// 			str[i] = str[i] + 0x20;
// 	}
// 	
// 	return str;
// };

// static int _stricmp(const char *string1,const char *string2 )
// {
// 	int len = strlen(string1);
// 	char* c1 = new char[len+1];
// 	strcpy(c1 , string1);
// 	c1[len] = 0;
// 	_strlwr(c1);
// 	
// 	len = strlen(string2);
// 	char* c2 = new char[len+1];
// 	strcpy(c2 , string2);
// 	c2[len] = 0;	
// 	_strlwr(c2);	
// 	
// 	int ret = strcmp(c1 , c2);
// 	delete c1;
// 	delete c2;
// 	
// 	return ret;
// };

__inline _PC _tcsinc(_CPC _s1) {return (_PC)_mbsinc((_CPUC)_s1);}
__inline _PC _tcsupr(_PC _s1) {return (_PC)_mbsupr((_PC)_s1);}
__inline _PC _tcsstr(_CPC _s1,_CPC _s2) {return (_PC)strstr((_CPC)_s1,(_CPC)_s2);}

#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

//√≤À∆√ª”√µΩ
WINBASEAPI
DWORD
WINAPI
GetFileSize(
			HANDLE hFile,
			LPDWORD lpFileSizeHigh
    );

WINBASEAPI
BOOL
WINAPI
CloseHandle(
			HANDLE hObject
    );

HANDLE CreateFile(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    /*LPSECURITY_ATTRIBUTES*/void* lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );

BOOL WriteFile(
    HANDLE hFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    );

BOOL ReadFile(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    );
	
DWORD SetFilePointer(
    HANDLE hFile,
    LONG lDistanceToMove,
    PLONG lpDistanceToMoveHigh,
    DWORD dwMoveMethod
    );


//void CloseFile(HANDLE hFile);

int MessageBox(HWND hWnd,
    LPCTSTR lpText,
    LPCTSTR lpCaption,
    UINT uType
);

BOOL apiCreateDirectory(const char* path , void* p = NULL);


void printmsg(char* msg);

bool GetSystemTime(SYSTEMTIME* systime);

int MultiByteToWideChar(
  UINT CodePage, 
  DWORD dwFlags,         
  LPCSTR lpMultiByteStr, 
  int cbMultiByte,       
  LPWSTR lpWideCharStr,  
  int cchWideChar        
);

int WideCharToMultiByte(
  UINT CodePage, 
  DWORD dwFlags, 
  LPCWSTR lpWideCharStr,
  int cchWideChar, 
  LPSTR lpMultiByteStr, 
  int cbMultiByte,
  LPCSTR lpDefaultChar,    
  LPBOOL lpUsedDefaultChar
);

BOOL SystemTimeToFileTime(
  const SYSTEMTIME* lpSystemTime,
  LPFILETIME lpFileTime
);

BOOL LocalFileTimeToFileTime(
  const FILETIME* lpLocalFileTime,
  LPFILETIME lpFileTime
);

#define ASSERT(f)	(void(0))
