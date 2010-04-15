// Sound.h: interface for the CSound class.
// ����   : �Ѱ������ ���� Ŭ�����̸�
//          �������� �ε��Ͽ� �����ϱ����ؼ���
//          �Ѱ�� �ʿ��� ����(m_pDSBuffer)�� ���������Ͽ�
//          ���� ����� �����.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__297F644C_C097_49AB_9D33_C13343AB1A75__INCLUDED_)
#define AFX_SOUND_H__297F644C_C097_49AB_9D33_C13343AB1A75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define ERRORMSG(str)	MessageBox( NULL, str, "ERROR", MB_OK | MB_ICONERROR)

template< typename PD3DOBJECT >
VOID D3DSAFE_RELEASE( PD3DOBJECT &pD3DObject )
{
	if( pD3DObject ){ pD3DObject->Release(); }
	pD3DObject = NULL;
}

//note : OggVorbis �������
#include    "vorbis/codec.h"
#include    "vorbis/vorbisfile.h"

    
#pragma comment(lib, "winmm")
#pragma comment(lib, "dsound")

#ifdef _DEBUG
	// ����� ���
	#pragma comment(lib, "lib/ogg_static_d")
	#pragma comment(lib, "lib/vorbis_static_d")
	#pragma comment(lib, "lib/vorbisfile_static_d")
#else
	// ������ ���
	#pragma comment(lib, "lib/ogg_static")
	#pragma comment(lib, "lib/vorbis_static")
	#pragma comment(lib, "lib/vorbisfile_static")
#endif

//note : ����ũ��
#define     BUFSIZE    1048576*60

class CSound  
{
public:
	CSound();
	virtual ~CSound();

	bool	OnCreate( HWND hWnd);
	void	OnRelease();

	void	Loop( bool bLoop );
	bool	Open( char *filename);		// ���� �ε�
    bool	Play(bool bLoop);						// ���
	void	Pause();
    void	Stop();						// ����
	
protected:
	LPDIRECTSOUNDBUFFER	m_pDSBuffer;	// the buffer
    LPDIRECTSOUND8		m_pDSound;		// DX Sound
    OggVorbis_File		m_sVF;			// OggVorbis ���� ����ü
	bool		        m_bInitDS;		// �ʱ�ȭ üũ

};

#endif // !defined(AFX_SOUND_H__297F644C_C097_49AB_9D33_C13343AB1A75__INCLUDED_)
