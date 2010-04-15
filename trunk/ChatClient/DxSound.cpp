/*
	The author		: jazonsim
	Create Date		: 1998/08/25

	Modify Date		: 2001/05/24
*/
#include "DxSound.h"

#pragma comment(lib, "dsound.lib")

CDxSound DS;



#ifdef DEF_DXSOUND_VER1
	BOOL CDxSound::InitDS(HWND hWnd) 
	{
		m_hWnd = hWnd;
		// Create the main DirectSound object.
		HRESULT result = DirectSoundCreate(0, &m_pDirectSoundObj, 0);
		if(result != DS_OK) return FALSE;
		
		// Set the priority level.
		result = m_pDirectSoundObj->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
		if(result != DS_OK) 
		{
			m_pDirectSoundObj = 0;
			return FALSE;
		}
		return TRUE;
	}

	void CDxSound::ExitDS(void) 
	{
		if(m_pDirectSoundObj != 0) 
		{
			m_pDirectSoundObj->Release();
			m_pDirectSoundObj = 0;
		}
	}
#endif	//DEF_DXSOUND_VER1



#ifdef DEF_DXSOUND_VER9
	BOOL CDxSound::InitDS(HWND hWnd) 
	{
		m_hWnd = hWnd;
		// Create the main DirectSound object.
		HRESULT result = DirectSoundCreate8(0, &m_pDirectSoundObj, 0);
		if(result != DS_OK) return FALSE;
		
		// Set the priority level.
		result = m_pDirectSoundObj->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
		if(result != DS_OK) 
		{
			m_pDirectSoundObj = 0;
			return FALSE;
		}
		return TRUE;
	}

	void CDxSound::ExitDS(void) 
	{
		if(m_pDirectSoundObj != 0) 
		{
			m_pDirectSoundObj->Release();
			m_pDirectSoundObj = 0;
		}
	}
#endif	//DEF_DXSOUND_VER9




