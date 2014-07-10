/*
 *  winapi.cpp
 *  
 *
 *  Created by System Administrator on 08-8-11.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "winapi.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <iconv.h>
//#include <CoreFoundation/CoreFoundation.h>

HANDLE CreateFile(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    /*LPSECURITY_ATTRIBUTES*/void* lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    )
{
	//printf("eee CreateFile!tttttttttttttttttttttttttttt\n");
	if (lpFileName == NULL)
	{
		printf("lpFileName == NULL\n");
		return NULL;
	}
	
	char mode[32];
	memset(mode , 0 , 32);	
	if(dwDesiredAccess==GENERIC_READ&&dwCreationDisposition==OPEN_EXISTING)
		strcpy(mode , "rb");
	else if (dwDesiredAccess==GENERIC_WRITE&&dwCreationDisposition==CREATE_ALWAYS)
		strcpy(mode , "wb");
	else if ( dwDesiredAccess==GENERIC_WRITE|GENERIC_READ&&dwCreationDisposition==CREATE_ALWAYS)
		strcpy(mode , "wb+");
	else if ( dwDesiredAccess==GENERIC_WRITE|GENERIC_READ&&dwCreationDisposition==OPEN_EXISTING)
		strcpy(mode , "rb+");
	else 
	{
		printf("else return NULL\n");
		return NULL;
	}

	//printf("mode is %s===\n", mode);
	FILE* fp = NULL;
	fp=fopen(lpFileName, mode);
	if (fp == NULL)
	{
		//printf("fp == NULL\n");
		return NULL;
	}

	return fp;
}

BOOL WriteFile(
    HANDLE hFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    )
{
	if (hFile == NULL)
	{
		return FALSE;
	}
	
	DWORD  nRead = fwrite(lpBuffer, 1, nNumberOfBytesToWrite, (FILE*)hFile);
	if (nRead<=0)
	{
		printf("writefile is <=0!!!\n");
		return FALSE;
	}
	*lpNumberOfBytesWritten = nRead;
	return TRUE;
}

BOOL ReadFile(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    )
{
	if (hFile == NULL)
	{
		return FALSE;
	}

	size_t nRead = fread(lpBuffer, 1, nNumberOfBytesToRead, (FILE*)hFile);
	//printf("ffffffread = %d, hFile=%d, nNumberOfBytesToRead=%d\n", nRead, hFile, nNumberOfBytesToRead);
	if (nRead<=0)
	{
printf("nRead <= 0!!!!!!!!!!!!!!!Failed to read file!\n");
		return FALSE;
	}
	*lpNumberOfBytesRead = nRead;
	return TRUE;
}	
	
DWORD SetFilePointer(
    HANDLE hFile,
    LONG lDistanceToMove,
    PLONG lpDistanceToMoveHigh,
    DWORD dwMoveMethod
    )
{
	if (hFile == NULL)
	{
		return -1;
	}
	
	//fseek没有改变原来的文件指针
	if (dwMoveMethod==FILE_CURRENT)
	{
		fseek((FILE*)hFile, lDistanceToMove, SEEK_CUR);
		//return (DWORD)hFile;
		return ftell((FILE*)hFile);
	}
	else if (dwMoveMethod == FILE_BEGIN)
	{
		fseek((FILE*)hFile, lDistanceToMove, SEEK_SET);
		//fseek((FILE*)hFile, lDistanceToMove, SEEK_CUR);
//		return (DWORD)hFile;
		return ftell((FILE*)hFile);
	}
	
	
	return -1;
}	

void CloseFile(HANDLE hFile)
{
	if (hFile)
	{
		fclose((FILE*)hFile);
	}
	
}

BOOL apiCreateDirectory(const char* path , void* p)
{
	return FALSE;
}

void printmsg(char* msg)
{
	printf(msg);
	printf("\n");
}

int MessageBox(HWND hWnd,
    LPCTSTR lpText,
    LPCTSTR lpCaption,
    UINT uType
)
{
	return 1;
}

 bool GetSystemTime(SYSTEMTIME* systime)
 {
// 	CFAbsoluteTime      absTime = CFAbsoluteTimeGetCurrent(); 
// 	//CFTimeZoneRef tzGMT = CFTimeZoneCopySystem();//Time zone get from system
// 	CFTimeZoneRef tzGMT = CFTimeZoneCreateWithName(kCFAllocatorDefault,CFSTR("Etc/GMT"),true);//Time Zone GMT+0
// 	CFGregorianDate gmtDate = CFAbsoluteTimeGetGregorianDate(absTime, tzGMT); 
// 	SInt32 dayofweek = CFAbsoluteTimeGetDayOfWeek(absTime,tzGMT);
// 	if(dayofweek == 7) dayofweek = 0;
// 
// 	systime->wYear = gmtDate.year;
// 	systime->wMonth = gmtDate.month;
// 	systime->wDayOfWeek = dayofweek;		
// 	systime->wDay = gmtDate.day;
// 	systime->wHour = gmtDate.hour;
// 	systime->wMinute = gmtDate.minute;
// 	systime->wSecond = (int)gmtDate.second;
// 	systime->wMilliseconds = (gmtDate.second - (double)systime->wSecond) * 1000;
// 	

	 time_t t;
	 struct tm *mtm;
	 struct timeval tv;
	 gettimeofday(&tv, 0);
	 t = tv.tv_sec;
	 time(&t); 
	 mtm = localtime(&t);
	 systime->wYear = mtm->tm_year + 1900;
	 systime->wMonth = mtm->tm_mon + 1;
	 systime->wDay = mtm->tm_mday;
	 systime->wDayOfWeek = mtm->tm_wday;
	 systime->wHour = mtm->tm_hour;
	 systime->wMinute = mtm->tm_min;
	 systime->wSecond = mtm->tm_sec;
	 systime->wMilliseconds = tv.tv_usec / 1000;

 	return TRUE;
 }

int WideCharToMultiByte(
  UINT CodePage, 
  DWORD dwFlags, 
  LPCWSTR lpWideCharStr,
  int cchWideChar, 
  LPSTR lpMultiByteStr, 
  int cbMultiByte,
  LPCSTR lpDefaultChar,    
  LPBOOL lpUsedDefaultChar
)
{

 	if(lpWideCharStr == NULL) return 0;
 	if(lpMultiByteStr == NULL && cbMultiByte !=0)return 0;
 
 	int wclen;
 	//if(cchWideChar == -1) 
	if(lpMultiByteStr==NULL && cbMultiByte==0)
 	{
 		WCHAR* p = (WCHAR*)lpWideCharStr;
 		wclen = 0;
 		
 		while(*p!=0x00)
 		{
 			p++;
 			wclen++;
 		}
		
		//如果只是求长度
		return wclen;	
 	}
 	else 
	{
   		//solution 2
		cbMultiByte = cchWideChar;
		wclen = cchWideChar*2;
//printf("wclen=%d\n", wclen);
                BYTE *ttt = (BYTE*)lpWideCharStr;
                for(int i=0;i<wclen;i++)
                {
                    //printf("^^^^^^^^lpWideCharStr=%c",ttt[i]);
                }
//printf("\n");

		iconv_t cd = iconv_open("UTF-8","UNICODE");
		if((iconv_t)-1 == cd)
		{
		    printf("Donot support this convert!\n");
		    return 0;
		}
	
		size_t stwclen = wclen;
		size_t stcbMultiByte = cbMultiByte;
		char* pCh = (char*)lpWideCharStr;		
//		printf("iconv before %d , %d\n" , wclen , cbMultiByte);		
//		int retSize = iconv(cd,&pCh, (size_t*)&wclen, &lpMultiByteStr,(size_t*)&cbMultiByte);
		int retSize = iconv(cd,&pCh, (size_t*)&stwclen, &lpMultiByteStr,(size_t*)&stcbMultiByte);
		wclen = stwclen;
		cbMultiByte = stcbMultiByte;
//		printf("iconv %d , %d , %d , %s\n" , retSize , wclen , cbMultiByte , lpMultiByteStr);
//		int retSize = 0;
//		memset(lpMultiByteStr , 'A' , 1);
//		cbMultiByte = cchWideChar;
		if(-1==retSize)
		{
		    //perror("iconv");
		    return 0;
		}
		iconv_close(cd);
//printf("iconv successed! retSize = %d, lpMultiByteStr = %s\n", retSize,lpMultiByteStr);
                
                return cbMultiByte;

//		wclen = cchWideChar;
//		printf("wclen=%d,sizeof wchar_t=%d\n", wclen,sizeof(wchar_t));
//                BYTE *ttt = (BYTE*)lpWideCharStr;
//		for(int i=0;i<wclen;i+=2)
//		{
//		    printf("^^^^^^^^^^^^^^^^^^lpWideCharStr=%c",ttt[i]);
//		}
//printf("\n");
//		int n = wcstombs(lpMultiByteStr,(wchar_t*)lpWideCharStr,wclen);
//		if(-1 == n)
//		{
//			perror("WideCharToMultiByte error!");
//			return 0;
//		} 
		
//		return n;
	}
 
// 	CFStringRef cfstr = CFStringCreateWithBytes(NULL, (UInt8*)lpWideCharStr , wclen * sizeof(WCHAR), 
// 											kCFStringEncodingUTF16LE,false);
// 				
// 
// 	CFRange rangeToProcess = CFRangeMake(0, CFStringGetLength(cfstr));	
// 	int TotalConvertlen = 0;
// 	int TotalCpyLen = 0;
// 	int TotalMBBufLen = cbMultiByte;
// 		
// 	while(rangeToProcess.length > 0)
// 	{
// 		UInt8 localBuffer[100];
// 		CFIndex usedBufferLength;
// 		CFIndex numChars;
// 		
// 		if(cbMultiByte != 0)
// 		{
// 			numChars = CFStringGetBytes(cfstr, rangeToProcess, 
// 								CodePage, 
// 								'?', FALSE, (UInt8 *)localBuffer, 100, &usedBufferLength);	
// 		}
// 		else
// 		{
// 			numChars = CFStringGetBytes(cfstr, rangeToProcess, 
// 									CodePage, 
// 									'?', FALSE, NULL, 0, &usedBufferLength);
// 		}
// 		
// 		if (numChars == 0) break;   // Failed to convert anything...
// 		rangeToProcess.location += numChars;
// 		rangeToProcess.length -= numChars;		
// 		
// 		TotalConvertlen += numChars;
// 		
// 		if( TotalCpyLen + usedBufferLength <= TotalMBBufLen && cbMultiByte !=0)
// 		{
// 			memcpy(lpMultiByteStr+TotalCpyLen , localBuffer , usedBufferLength);
// 			TotalCpyLen += usedBufferLength;	
// 		}
// 
// 	}
// 	
// 	return TotalConvertlen;
	return 0;
 }
 
int MultiByteToWideChar(
  UINT CodePage, 
  DWORD dwFlags,         
  LPCSTR lpMultiByteStr, 
  int cbMultiByte,       
  LPWSTR lpWideCharStr,  
  int cchWideChar        
)
{
 	if(lpMultiByteStr == NULL) return 0;
 	if(lpWideCharStr == NULL && cchWideChar !=0)return 0;
 		
 	int mblen;
 	//if(cbMultiByte == -1) 
	if(lpWideCharStr==NULL && cchWideChar==0)
	{
		mblen = strlen(lpMultiByteStr);
		return mblen;
	}
 	else 
	{
		//if((cchWideChar-cbMultiByte)==1)
			//cbMultiByte = cchWideChar;
		mblen = (cbMultiByte+1)*2;
		int nLength = cbMultiByte;
//printf("cbMultiByte=%d\n", cbMultiByte);
		//char* szTmp = new char[mblen];
		//memset(szTmp,0, mblen);

		iconv_t cd = iconv_open("UNICODE","UTF-8");
		if((iconv_t)-1 == cd)
		{
		    printf("Don't support this convert!\n");
		    return 0;
		}
		char* pCh = (char*)lpWideCharStr;
		size_t stcbMultiByte = cbMultiByte;
		size_t stmblen = mblen;

		int retSize = iconv(cd,(char**)&lpMultiByteStr, (size_t*)&stcbMultiByte, &pCh,(size_t*)&stmblen);
		cbMultiByte = stcbMultiByte;
		mblen = stmblen;
		//there are always tow more devil characters.
		//memcpy(szTmp,(char*)lpWideCharStr,mblen);
		//memset((char*)lpWideCharStr,0, mblen);
		//memcpy((char*)lpWideCharStr,szTmp+2, mblen-2);
		//delete szTmp;
		//szTmp = NULL;
		if(-1==retSize)
		{
		    //perror("eeeeeeeerrno iconv! MultiByteToWideChar\n");
		    return 0;
		}
		iconv_close(cd);
		


		/*int m = mbstowcs(lpWideCharStr,lpMultiByteStr,mblen); 
		if(m == -1)
		{
			 perror("MultiByteToWideChar error!");
			 return 0;
		}*/

//printf("fffffffff return=%d\n", nLength-cbMultiByte);
		 return nLength-cbMultiByte;
	}
 
 
// 	CFStringRef cfstr = CFStringCreateWithBytes(NULL, (UInt8*)lpMultiByteStr , mblen, CodePage,false);
// 	//CFStringRef cfstr = CFStringCreateWithCString(NULL,lpMultiByteStr,CodePage);
// 	CFRange rangeToProcess = CFRangeMake(0, CFStringGetLength(cfstr));	
// 	int TotalConvertlen = 0;
// 	int TotalCpyLen = 0;
// 	int TotalWCBufLen = cchWideChar * sizeof(WCHAR);
// 	
// 	
// 	while(rangeToProcess.length > 0)
// 	{
// 		UInt8 localBuffer[100];
// 		CFIndex usedBufferLength;
// 		CFIndex numChars;
// 		
// 		if(cchWideChar != 0)
// 		{
// 			numChars = CFStringGetBytes(cfstr, rangeToProcess, 
// 								kCFStringEncodingUTF16LE, 
// 								'?', FALSE, (UInt8 *)localBuffer, 100, &usedBufferLength);	
// 		}
// 		else
// 		{
// 			numChars = CFStringGetBytes(cfstr, rangeToProcess, 
// 									kCFStringEncodingUTF16LE, 
// 									'?', FALSE, NULL, 0, &usedBufferLength);
// 		}
// 		
// 		if (numChars == 0) break;   // Failed to convert anything...
// 		rangeToProcess.location += numChars;
// 		rangeToProcess.length -= numChars;		
// 		
// 		TotalConvertlen += numChars;
// 		
// 		if( TotalCpyLen + usedBufferLength <= TotalWCBufLen && cchWideChar !=0)
// 		{
// 			memcpy(lpWideCharStr+TotalCpyLen , localBuffer , usedBufferLength);
// 			TotalCpyLen += usedBufferLength;	
// 		}
// 
// 	}
// 	
// 	return TotalConvertlen;
// 
	//return 0;
 }


BOOL SystemTimeToFileTime(
  const SYSTEMTIME* lpSystemTime,
  LPFILETIME lpFileTime
)
{	
// 	CFGregorianDate gmtDate;
// 	gmtDate.year = lpSystemTime->wYear;
// 	gmtDate.month = lpSystemTime->wMonth;
// 	gmtDate.day = lpSystemTime->wDay;
// 	gmtDate.hour = lpSystemTime->wHour;
// 	gmtDate.minute = lpSystemTime->wMinute;
// 	gmtDate.second = (double)lpSystemTime->wSecond + (double)lpSystemTime->wMilliseconds / (double)1000;
// 
// 	//CFTimeZoneRef tzGMT = CFTimeZoneCopySystem();//Time zone get from system
// 	CFTimeZoneRef tzGMT = CFTimeZoneCreateWithName(kCFAllocatorDefault,CFSTR("Etc/GMT"),true);//Time Zone GMT+0
// 	
// 	CFAbsoluteTime absTime = CFGregorianDateGetAbsoluteTime(gmtDate,tzGMT);
// 	
// 	CFGregorianDate gmtDatepast;
// 	gmtDatepast.year = 1601;
// 	gmtDatepast.month = 1;
// 	gmtDatepast.day = 1;
// 	gmtDatepast.hour = 0;
// 	gmtDatepast.minute = 0;
// 	gmtDatepast.second = 0;	
// 	CFAbsoluteTime absTimepast = CFGregorianDateGetAbsoluteTime(gmtDatepast,tzGMT);	
// 	
// 	//CFGregorianUnits unit = CFAbsoluteTimeGetDifferenceAsGregorianUnits(
// 	//								absTime,absTimepast,tzGMT,kCFGregorianAllUnits);
// 	double diff = absTime - absTimepast;
// 	SInt64 nanosec = diff * 10000000;//100 nano seconds
// 	
//     DWORD dwLowDateTime;
//     DWORD dwHighDateTime;
// 	
// 	dwLowDateTime = nanosec;
// 	dwHighDateTime = nanosec >> 32;
// 
// 	lpFileTime->dwHighDateTime = dwHighDateTime;
// 	lpFileTime->dwLowDateTime = dwLowDateTime;
// 


	if (lpSystemTime == NULL)
	{
		return FALSE;
	}
	struct tm gm = {lpSystemTime->wSecond, 
					lpSystemTime->wMinute, 
					lpSystemTime->wHour, 
					lpSystemTime->wDay, 
					lpSystemTime->wMonth-1, 
					lpSystemTime->wYear-1900, 
					lpSystemTime->wDayOfWeek, 
					0, 
					0};

	time_t tmt = mktime(&gm);
	ULONGLONG QuadPart = (ULONGLONG)tmt*(ULONGLONG)10000000+(ULONGLONG)116444736000000000;
	lpFileTime->dwLowDateTime = QuadPart;
	lpFileTime->dwLowDateTime += (DWORD)lpSystemTime->wMilliseconds*10000;//加上millisecondes
 	lpFileTime->dwHighDateTime = QuadPart >> 32;

    
 	return TRUE;
 }

BOOL LocalFileTimeToFileTime(
  const FILETIME* lpLocalFileTime,
  LPFILETIME lpFileTime
)
{
// 	CFTimeZoneRef tzGMT0 = CFTimeZoneCreateWithName(kCFAllocatorDefault,CFSTR("Etc/GMT"),true);//Time Zone GMT+0
// 	CFTimeZoneRef tzGMTSys = CFTimeZoneCopySystem();//Time zone get from system
// 	
// 	CFAbsoluteTime absTime_GMTSys = CFAbsoluteTimeGetCurrent(); 
// 		
// 	CFGregorianDate gmtDate = CFAbsoluteTimeGetGregorianDate(absTime_GMTSys, tzGMT0);
// 	
// 	CFAbsoluteTime absTime_GMT0 = CFGregorianDateGetAbsoluteTime(gmtDate,tzGMT0);
// 	
// 	double diff_sec = absTime_GMT0 - absTime_GMTSys;
// 	SInt64 diff_nanosec = diff_sec * 10000000;//100 nano seconds
// 	
//     SInt64 localFileTime64 = lpLocalFileTime->dwHighDateTime;
// 	localFileTime64 = localFileTime64 << 32;
// 	localFileTime64 += lpLocalFileTime->dwLowDateTime;
// 	
// 	SInt64 toFileTime64 = localFileTime64 + diff_nanosec;
// 	
//     lpFileTime->dwHighDateTime = toFileTime64 >> 32;	
// 	lpFileTime->dwLowDateTime = toFileTime64;	
// 	

	//在UTC的情况下
	lpFileTime->dwHighDateTime = lpLocalFileTime->dwHighDateTime;
	lpFileTime->dwLowDateTime = lpLocalFileTime->dwLowDateTime;
 	return TRUE;
 }


WINBASEAPI
DWORD
WINAPI
GetFileSize(
			HANDLE hFile,
			LPDWORD lpFileSizeHigh
    )
{
	if (hFile == NULL)
	{
		lpFileSizeHigh = 0;
		return 0xFFFFFFFF;
	}

	fseek((FILE*)hFile, 0, SEEK_END);
	DWORD dwHigh = ftell((FILE*)hFile);
	*lpFileSizeHigh = dwHigh;
	fseek((FILE*)hFile, 0, SEEK_SET);
	return *lpFileSizeHigh;
}

WINBASEAPI
BOOL
WINAPI
CloseHandle(
			HANDLE hObject
    )
{
	if (hObject)
	{
		fclose((FILE*)hObject);
		return TRUE;
	}
	return FALSE;
}
