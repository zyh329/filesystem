/**************************************************************************
MFC中有一个非常好用的CMemFile类，可以让我们像读写文件一样来操作一块内存。
但是它的最大缺点就是使用了MFC，从CObject继承，这样我们在写非MFC程序时就不能
使用这个方便的内存文件类了。下面是我根据MFC的CMemFile的源代码改写的一个
CAnsiMemFile类，去掉了CMemFile中使用MFC的部分，希望对大家有用。

  CAnsiMemFile的使用非常简单，只用把下面的代码保存到一个AnsiMemFile.h头文件中
  （这个类没有CPP文件），然后在你的VC工程中#include "AnsiMemFile.h"就可以了。
  该类的接口和MF的CMemFile类基本一致，可以参考MSDN中CMemFile类的文档。
  
	// AnsiMemFile.h: the CAnsiMemFile class.
	//
	// A memory file class without MFC 
	// Version: 1.0
	// Data: 2005-10-27
	// 
	// www.farproc.com
*****************************************************************************/

#if !defined(AFX_ANSIMEMFILE_H__2F568214_9834_4B67_B97E_FFB21CDB61F1__INCLUDED_)
#define AFX_ANSIMEMFILE_H__2F568214_9834_4B67_B97E_FFB21CDB61F1__INCLUDED_

#include <exception>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
//#include 
//#include 
//#include 

//#ifndef UINT

//#endif
namespace LibHowen{
	class CAnsiMemFile
	{
	protected:
		UINT m_nGrowBytes;
		DWORD m_nPosition;
		DWORD m_nBufferSize;
		DWORD m_nFileSize;
		BYTE* m_lpBuffer;
		BOOL m_bAutoDelete;
		
#pragma intrinsic(memcpy)
		BYTE* Memcpy(BYTE* lpMemTarget, const BYTE* lpMemSource,
			UINT nBytes)
		{
			if(0==nBytes)
				return NULL;
			assert(lpMemTarget != NULL);
			assert(lpMemSource != NULL);
			
			//assert(AfxIsValidAddress(lpMemTarget, nBytes));
			//assert(AfxIsValidAddress(lpMemSource, nBytes, FALSE));
			
			return (BYTE*)memcpy(lpMemTarget, lpMemSource, nBytes);
		}
#pragma function(memcpy)
		
		void Free(BYTE *lpMem){free(lpMem);}
		BYTE* Realloc(BYTE *lpMem,DWORD nBytes){
//			//Free(lpMem);
//			if(nBytes<=m_nFileSize){ //Not support
//				//throw exception("Not support");
//				throw "Realloc Error!";
//			}
//			BYTE *pNewBlock=Alloc(nBytes);
//			//copy to new block
//			::memcpy(pNewBlock,lpMem,m_nFileSize);
//			Free(lpMem);
//			return pNewBlock;
			return (BYTE*)realloc(lpMem, (UINT)nBytes);
		}
		BYTE * Alloc(DWORD nBytes){
			//BYTE *pNewBlock=new BYTE[nBytes];
			//assert(pNewBlock!=NULL);
			//return pNewBlock;
			return (BYTE*)malloc((UINT)nBytes);
		}
		
		void GrowFile(DWORD dwNewLen)
		{
			assert(this);
			
			if (dwNewLen > m_nBufferSize)
			{
				// grow the buffer
				DWORD dwNewBufferSize = (DWORD)m_nBufferSize;
				
				// watch out for buffers which cannot be grown!
				assert(m_nGrowBytes != 0);
				//if (m_nGrowBytes == 0)
				// AfxThrowMemoryException();
				
				// determine new buffer size
				while (dwNewBufferSize < dwNewLen)
					dwNewBufferSize += m_nGrowBytes;
				
				// allocate new buffer
				BYTE* lpNew;
				if (m_lpBuffer == NULL)
					lpNew = Alloc(dwNewBufferSize);
				else
					lpNew = Realloc(m_lpBuffer, dwNewBufferSize);
				
				if (lpNew == NULL){
					//AfxThrowMemoryException();
					//throw exception("分配内存错误！");
                                throw "Encounter error when allocating memory!";
				}

				
				m_lpBuffer = lpNew;
				m_nBufferSize = dwNewBufferSize;
			}
			assert(this);
		}
	public:
		enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
		
		//nGrowBytes 该文件需要增大时的增大粒度（每次增大nGrowBytes个字节）
		CAnsiMemFile(UINT nGrowBytes = 1024)
		{
			assert(nGrowBytes <= UINT_MAX);
			
			m_nGrowBytes = nGrowBytes;
			m_nPosition = 0;
			m_nBufferSize = 0;
			m_nFileSize = 0;
			m_lpBuffer = NULL;
			m_bAutoDelete = TRUE;
		}
		//相对于构造后调用Attach
		CAnsiMemFile(const BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0)
		{
			assert(nGrowBytes <= UINT_MAX);
			
			m_nGrowBytes = nGrowBytes;
			m_nPosition = 0;
			m_nBufferSize = nBufferSize;
			m_nFileSize = nGrowBytes == 0 ? nBufferSize : 0;
			m_lpBuffer=Alloc(nBufferSize);
			memcpy(m_lpBuffer,lpBuffer,nBufferSize);
		//	m_lpBuffer = lpBuffer;
			m_bAutoDelete = TRUE;
		}
		
		~CAnsiMemFile()
		{
			// Close should have already been called, but we check anyway
			if (m_lpBuffer)
				Close();
			assert(m_lpBuffer == NULL);
			
			m_nGrowBytes = 0;
			m_nPosition = 0;
			m_nBufferSize = 0;
			m_nFileSize = 0;
		}
		
		//////////////////////取属性
		
		//取得当前读写位置
		DWORD GetPosition() const
		{
			assert(this);
			return m_nPosition;
		}
		//取得文件的当前大小
		DWORD GetLength() const
		{
			//		DWORD dwLen, dwCur;
			//		// Seek is a non const operation
			//		CAnsiMemFile* pFile = (CAnsiMemFile*)this;
			//		dwCur = pFile->Seek(0L, current);
			//		dwLen = pFile->SeekToEnd();
			//		pFile->Seek(dwCur, begin);
			//		
			//		return dwLen;
			return m_nFileSize;
		}
		//取得内存数据指针
		//注意：只读，不要修改该指针指向的内容。如果需要读写该文件内容，请用Read()和Write()
		const BYTE  * GetPtr()
		{
			return m_lpBuffer;
		}
		
		///////////////////////操作
		
		//指定本文件所用的内存
		//该对象析构时不会释放改内存块
		void Attach(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes)
		{
			assert(m_lpBuffer == NULL);
			
			m_nGrowBytes = nGrowBytes;
			m_nPosition = 0;
			m_nBufferSize = nBufferSize;
			m_nFileSize = nGrowBytes == 0 ? nBufferSize : 0;
			m_lpBuffer = lpBuffer;
			m_bAutoDelete = FALSE;
		}
		//解除该文件和它当前占用的内存块的关联
		//返回该内存块的指针
		BYTE* Detach()
		{
			BYTE* lpBuffer = m_lpBuffer;
			m_lpBuffer = NULL;
			m_nFileSize = 0;
			m_nBufferSize = 0;
			m_nPosition = 0;
			
			return lpBuffer;
		}
		//移动读写位置到文件最后
		DWORD SeekToEnd()
		{ 
			return Seek(0, CAnsiMemFile::end); 
		}
		//移动读写位置到文件开头
		void SeekToBegin()
		{ 
			Seek(0, CAnsiMemFile::begin); 
		}
		//改变文件长度
		//如果需要会重新分配所占内存
		void SetLength(DWORD dwNewLen)
		{
			assert(this);
			
			if (dwNewLen > m_nBufferSize)
				GrowFile(dwNewLen);
			
			if (dwNewLen < m_nPosition)
				m_nPosition = dwNewLen;
			
			m_nFileSize = dwNewLen;
			assert(this);
		}
		//从当前读写位置读取指定长度的数据
		UINT Read(void* lpBuf, UINT nCount)
		{
			assert(this);
			
			if (nCount == 0)
				return 0;
			
			assert(lpBuf != NULL);
			//assert(AfxIsValidAddress(lpBuf, nCount));
			
			if (m_nPosition > m_nFileSize)
				return 0;
			
			UINT nRead;
			if (m_nPosition + nCount > m_nFileSize)
				nRead = (UINT)(m_nFileSize - m_nPosition);
			else
				nRead = nCount;
			
			Memcpy((BYTE*)lpBuf, (BYTE*)m_lpBuffer + m_nPosition, nRead);
			m_nPosition += nRead;
			
			assert(this);
			
			return nRead;
		}
		//写指定长度的数据到文件内
		void Write(const void* lpBuf, UINT nCount)
		{
			assert(this);
			
			if (nCount == 0)
				return;
			
			assert(lpBuf != NULL);
			//assert(AfxIsValidAddress(lpBuf, nCount, FALSE));
			
			if (m_nPosition + nCount > m_nBufferSize)
				GrowFile(m_nPosition + nCount);
			
			assert(m_nPosition + nCount <= m_nBufferSize);
			
			Memcpy((BYTE*)m_lpBuffer + m_nPosition, (BYTE*)lpBuf, nCount);
			
			m_nPosition += nCount;
			
			if (m_nPosition > m_nFileSize)
				m_nFileSize = m_nPosition;
			
			assert(this);
		}
		//移动读写位置
		//lOff 移动的距离
		//nFrom 指定从哪里开始移动
		//
		//第二个参数可以为：
		//enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
		LONG Seek(LONG lOff, UINT nFrom)
		{
			assert(this);
			assert(nFrom == begin || nFrom == end || nFrom == current);
			
			LONG lNewPos = m_nPosition;
			
			if (nFrom == begin)
				lNewPos = lOff;
			else if (nFrom == current)
				lNewPos += lOff;
			else if (nFrom == end)
				lNewPos = m_nFileSize + lOff;
			else
				return -1;
			
			if (lNewPos < 0){
				//exception e("Seek错误");
				throw "Encounter error when seek file!";
			}
			
			m_nPosition = lNewPos;
			
			assert(this);
			return m_nPosition;
		}
		//关闭内存文件，释放所占用的内存，置长度为0。
		//该内存文件不可增长（即不可再写入任何数据）
		//析构函数会自动调用Close
		void Close()
		{
			assert((m_lpBuffer == NULL && m_nBufferSize == 0) ||
				!m_bAutoDelete || TRUE);
			assert(m_nFileSize <= m_nBufferSize);
			
			m_nGrowBytes = 0;
			m_nPosition = 0;
			m_nBufferSize = 0;
			m_nFileSize = 0;
			if (m_lpBuffer && m_bAutoDelete)
				Free(m_lpBuffer);
			m_lpBuffer = NULL;
		}
	};

}
/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_ANSIMEMFILE_H__2F568214_9834_4B67_B97E_FFB21CDB61F1__INCLUDED_)
