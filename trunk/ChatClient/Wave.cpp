/*
	The author		: jazonsim 
	Create Date		: 1998/09/02

	Modify Date		: 2002/03/07
*/
#include "DxSound.h"
#include "Wave.h"
#include <stdlib.h>

void CWave::Clear()
{
	Stop();

	free(m_Buf);

	if(m_lpdsb) 
	{
		m_lpdsb->Release();
		m_lpdsb = 0;
	}
}

BOOL CWave::Load(char* filename)
{
	CWinFile fp;
	if(!fp.OpenRead(filename)) return FALSE;
	Load(&fp);
	//fp.Close();
	return TRUE;
}

BOOL CWave::Load(CWinFile* fp) 
{
	//Clear();

	DWORD dwType;
	fp->Read(&dwType, sizeof(DWORD));
    if(dwType != mmioFOURCC('R', 'I', 'F', 'F')) return FALSE;	

	DWORD dwLength;
	fp->Read(&dwLength, sizeof(DWORD));
	fp->Read(&dwType, sizeof(DWORD));
    if(dwType != mmioFOURCC('W', 'A', 'V', 'E')) return FALSE;

	m_BufSize = dwLength - 4;
	
	m_Buf = (BYTE*)malloc(m_BufSize);
	fp->Read(m_Buf, m_BufSize);

	DWORD* pdw = (DWORD*)m_Buf;
	DWORD* pdwEnd = (DWORD*)(m_Buf + m_BufSize);

	while(pdw < pdwEnd) 
	{
		dwType = *pdw++;
		dwLength = *pdw++;
		switch(dwType) 
		{
		case mmioFOURCC('f', 'm', 't', ' ') :
			m_pwfxInfo = (WAVEFORMATEX*)pdw;
			break;
		case mmioFOURCC('d', 'a', 't', 'a') :
			m_TimeSec = (double)dwLength / m_pwfxInfo->nAvgBytesPerSec;
			goto FINISH;
		}
		pdw = (DWORD*)((BYTE*)pdw + dwLength);
	}

FINISH:
	BOOL bResult = CreateStaticDSB(dwLength, (BYTE*)pdw, m_pwfxInfo);

	free(m_Buf);
	m_Buf = 0;

	return bResult;
}

BOOL CWave::LoadBuf(char* filename) 
{
	CWinFile fp;
	if(!fp.OpenRead(filename)) return FALSE;

	//Clear();

    DWORD dwType;
	fp.Read(&dwType, sizeof(DWORD));
    if(dwType != mmioFOURCC('R', 'I', 'F', 'F')) return FALSE;
	
    DWORD dwLength;
	fp.Read(&dwLength, sizeof(DWORD));
	fp.Read(&dwType, sizeof(DWORD));
    if(dwType != mmioFOURCC('W', 'A', 'V', 'E')) return FALSE;

	m_BufSize = dwLength - 4;
	m_Buf = (BYTE*)malloc(m_BufSize);
	fp.Read(m_Buf, m_BufSize);
	//fp.Close();
	return TRUE;
}

BOOL CWave::LoadBuf(CWinFile* fp) 
{
	//Clear();

	fp->Read(&m_BufSize, sizeof(int));
	m_Buf = (BYTE *)malloc(m_BufSize);
	if(m_Buf == 0) return FALSE;
	fp->Read(m_Buf, m_BufSize);

	return TRUE;
}

#ifdef DEF_MODE_TOOL
BOOL CWave::SaveBuf(CWinFile* fp) 
{
	if(m_Buf == NULL) return FALSE;
	fp->Write(&m_BufSize, sizeof(int));
	fp->Write(m_Buf, m_BufSize);
	return TRUE;
}
#endif

BOOL CWave::CreateStaticDSB() 
{
	if(m_Buf == 0) return FALSE;

    DWORD dwType;
    DWORD dwLength;

	DWORD* pdw = (DWORD*)m_Buf;
	DWORD* pdwEnd = (DWORD*)(m_Buf + m_BufSize);

	while(pdw < pdwEnd) 
	{
		dwType = *pdw++;
		dwLength = *pdw++;
		switch(dwType) 
		{
		case mmioFOURCC('f', 'm', 't', ' ') :
			m_pwfxInfo = (WAVEFORMATEX*)pdw;
			break;
		case mmioFOURCC('d', 'a', 't', 'a') :
			m_TimeSec = (double)dwLength / m_pwfxInfo->nAvgBytesPerSec;
			goto FINISH;
		}
		pdw = (DWORD*)((BYTE*)pdw + dwLength);
	}

FINISH:
	BOOL bResult = CreateStaticDSB(dwLength, (LPBYTE)pdw, m_pwfxInfo);
	
	free(m_Buf);
	m_Buf = 0;
	return bResult;
}

BOOL CWave::CreateStaticDSB(DWORD size, BYTE* data, LPWAVEFORMATEX header) 
{
	DSBUFFERDESC dsbd;
	BYTE *pbData = 0;
	BYTE *pbData2 = 0;
	DWORD dwLength, dwLength2;  

	memset(&dsbd, 0, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_STATIC;
	dsbd.dwBufferBytes = size;
	dsbd.lpwfxFormat = header;

	HRESULT dsrval = DS.GetDS()->CreateSoundBuffer(&dsbd, &m_lpdsb, NULL);
	if(dsrval == DS_OK) 
	{
		dsrval = m_lpdsb->Lock(0, size, (void**)&pbData, &dwLength, (void**)&pbData2, &dwLength2, 0L);
		if(dsrval == DS_OK) 
		{
			CopyMemory(pbData, data, dwLength);
			if(dwLength2) CopyMemory(pbData2, data + dwLength, dwLength2);
			m_lpdsb->Unlock(pbData, dwLength, pbData2, dwLength2);
			return TRUE;
		}
	}
	/*
	} else {
		int i;
		HRESULT ErrorMessage[] = {
			DSERR_ALLOCATED,
			DSERR_BADFORMAT,
			DSERR_INVALIDPARAM,
			DSERR_NOAGGREGATION,
			DSERR_OUTOFMEMORY,
			DSERR_UNINITIALIZED,
			DSERR_UNSUPPORTED
		};
		for(i = 0; i < 7; i++) {
			if(ErrorMessage[i] == dsrval) {
				ZDebugBox("Direct Sound : %d Error", i);
			}
		}
	}
	*/
	return FALSE;
}
