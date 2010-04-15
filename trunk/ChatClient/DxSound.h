/*
	The author		: jazonsim
	Create Date		: 1998/08/25

	Modify Date		: 2001/05/24
*/
#pragma once
#ifndef __DXSOUND_H
#define __DXSOUND_H

#define DEF_DXSOUND_VER1
//#define DEF_DXSOUND_VER9


#include <windows.h>

#pragma warning(disable:4201)
#include <mmsystem.h>
#pragma warning(default:4201)


#include "dsound.h"


#ifdef DEF_DXSOUND_VER1
	class CDxSound 
	{
	protected:
		LPDIRECTSOUND	m_pDirectSoundObj;
		HWND			m_hWnd;

	public:
		CDxSound(HWND hWnd = 0) : m_hWnd(hWnd), m_pDirectSoundObj(0)	{ }
		~CDxSound()														{ ExitDS(); }

		BOOL InitDS(HWND hWnd);
		void ExitDS();

		BOOL IsOk() {
			if(m_pDirectSoundObj == NULL) return FALSE;
			return TRUE;
		}
		LPDIRECTSOUND GetDS()											{ return m_pDirectSoundObj;	}
	};
#endif	//DEF_DXSOUND_VER1


#ifdef DEF_DXSOUND_VER9
	class CDxSound 
	{
	protected:
		LPDIRECTSOUND8	m_pDirectSoundObj;
		HWND			m_hWnd;

	public:
		CDxSound(HWND hWnd = 0) : m_hWnd(hWnd), m_pDirectSoundObj(0)	{ }
		~CDxSound()														{ ExitDS(); }

		BOOL InitDS(HWND hWnd);
		void ExitDS();

		BOOL IsOk() {
			if(m_pDirectSoundObj == NULL) return FALSE;
			return TRUE;
		}
		LPDIRECTSOUND8 GetDS()											{ return m_pDirectSoundObj;	}
	};
#endif



extern CDxSound DS;


#endif

