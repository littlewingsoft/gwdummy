/*
	The author		: jazonsim 
	Create Date		: 1998/09/02

	Modify Date		: 2002/03/07
*/
#ifndef __WAVE_H
#define __WAVE_H

#include <windows.h>
#include <windowsx.h>

#pragma warning(disable:4201)
#include <mmsystem.h>
#pragma warning(default:4201)

#include <dsound.h>
#include <stdio.h>
#include "WinFile.h"


class CWave
{
	LPWAVEFORMATEX m_pwfxInfo;
	BYTE* m_Buf;
	int m_BufSize;
	double m_TimeSec;
	BOOL m_PlayFlag;
	
	LPDIRECTSOUNDBUFFER	m_lpdsb;
public:
	CWave() : m_Buf(0), m_lpdsb(0), m_PlayFlag(FALSE)		{ }
	~CWave()												{ Clear();	}
	
	void Clear();

	BOOL Load(char* filename);
	BOOL Load(CWinFile* fp);

	BOOL LoadBuf(char* filename);
	BOOL LoadBuf(CWinFile* fp);
	
	BOOL LoadBufEx(CWinFile* fp) 
	{
		if(!LoadBuf(fp)) return FALSE;
		CreateStaticDSB();
		return TRUE;
	}

#ifdef DEF_MODE_TOOL
	BOOL SaveBuf(CWinFile* fp);
#endif

	BOOL CreateStaticDSB();


	void Play() 
	{
		m_lpdsb->SetCurrentPosition(0);
		m_lpdsb->Play(0, 0, 0);
	}
	void Play(int vol) 
	{
		m_lpdsb->SetVolume(vol);
		m_lpdsb->SetCurrentPosition(0);
		m_lpdsb->Play(0, 0, 0);
	}
	void LoopPlay() 
	{
		m_lpdsb->SetCurrentPosition(0);
		m_lpdsb->Play(0, 0, DSBPLAY_LOOPING);
		m_PlayFlag = TRUE;
	}
	void LoopPlay(int vol) 
	{
		m_lpdsb->SetVolume(vol);
		m_lpdsb->SetCurrentPosition(0);
		m_lpdsb->Play(0, 0, DSBPLAY_LOOPING);
		m_PlayFlag = TRUE;
	}
	void Stop() 
	{
		if(!m_PlayFlag) return;

//		DWORD status;
//		m_lpdsb->GetStatus(&status);
//		if(status == DSBSTATUS_PLAYING) 
//		{
			m_lpdsb->Stop();
			m_lpdsb->SetCurrentPosition(0);
//		}
	}	

	double GetTimeSec(void)									{ return m_TimeSec;	}
	
	void SetVolume(int vol) 
	{
		m_lpdsb->SetVolume(vol);
	}
	int GetVolume() 
	{
		int vol;
		m_lpdsb->GetVolume((long*)&vol);
		return vol;
	}
protected:
	BOOL CreateStaticDSB(DWORD size, BYTE* data, LPWAVEFORMATEX header);
};

#endif

