#ifndef __WINTYPEDEF_H__
#define __WINTYPEDEF_H__

#include <iostream>
#include <string.h>
#include <stdio.h>

#define MAX_PATH          260

#define FALSE   0
#define TRUE    1
//#define NULL    0

#define FILE_BEGIN           0
#define FILE_CURRENT         1
#define FILE_END             2

#define IN
#define OUT

//typedef unsigned int       DWORD, *PDWORD;
typedef unsigned int       DWORD;
typedef DWORD*				LPDWORD;
typedef DWORD*				PDWORD;

#ifndef DISABLE_BOOL_DEFINE
typedef signed char         BOOL , *LPBOOL ;
#endif

#define WINAPI	/**/
#define WINBASEAPI
//////////////////////////////////////////////////////////////////////////
//typedef long long int64_t;
typedef unsigned long long  uint64_t;
typedef char TCHAR;
#define _tcslen strlen
#define _tcsicmp strcasecmp
#define _tcscpy strcpy
#define _tcscmp strcmp
#define _tcscat strcat
#define _T(x)      x
//////////////////////////////////////////////////////////////////////////

typedef unsigned char       BYTE , *PBYTE , *LPBYTE;
typedef unsigned short      WORD;
typedef unsigned int        UINT;
typedef uint64_t			ULONGLONG;
typedef long long			LONGLONG;
typedef long				LONG;    
typedef LONG				*PLONG;    
typedef void				*LPVOID;
typedef void*				LPSECURITY_ATTRIBUTES;
typedef const char *LPCSTR, *PCSTR;
typedef char		*LPSTR, *PSTR;
typedef LPCSTR				LPCTSTR;
typedef LPSTR				LPTSTR;
typedef void				*HANDLE;
typedef HANDLE				HWND;
typedef const void			*LPCVOID;
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
//typedef unsigned short WCHAR;    // wc,   16-bit UNICODE character
typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR, *PWSTR;
typedef const WCHAR *LPCWSTR, *PCWSTR;
typedef int	INT;

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef struct _OVERLAPPED {
    DWORD   Internal;
    DWORD   InternalHigh;
    DWORD   Offset;
    DWORD   OffsetHigh;
    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct _WIN32_FIND_DATA
{  
	DWORD dwFileAttributes;  
	FILETIME ftCreationTime;  
	FILETIME ftLastAccessTime;  
	FILETIME ftLastWriteTime;  
	DWORD nFileSizeHigh;  
	DWORD nFileSizeLow;  
	DWORD dwReserved0;  
	DWORD dwReserved1;  
	char cFileName[MAX_PATH];  
	char cAlternateFileName[14];
} WIN32_FIND_DATA,  *PWIN32_FIND_DATA,  *LPWIN32_FIND_DATA;

//////////////////////////////////////////////////////////////////////////
typedef struct  _SECURITY_ATTRIBUTES
{
    DWORD nLength;
    /* [size_is] */ LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
    }	SECURITY_ATTRIBUTES;
//////////////////////////////////////////////////////////////////////////



#endif
