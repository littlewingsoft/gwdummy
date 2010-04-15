// Sound.cpp: implementation of the CSound class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Sound.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSound::CSound()
{
	m_pDSBuffer	= NULL;
	m_pDSound	= NULL;
	m_bInitDS	= FALSE;
}

CSound::~CSound()
{
}

//////////////////////////////////////////////////////////////////////////
// ������ �Լ�
//////////////////////////////////////////////////////////////////////////
//note : Ŭ���� ��뿡 �ʿ��� ��ü����
bool CSound::OnCreate( HWND hWnd)
{	
	// Direct Sound �ʱ�ȭ
	if(FAILED( DirectSoundCreate8(NULL, &m_pDSound, NULL)))
	{
		ERRORMSG( "DirectSound ��������[CSound::OnCreate()]");
        return m_bInitDS = FALSE;
	}
	
	m_pDSound->Initialize( NULL);
	m_pDSound->SetCooperativeLevel( hWnd, DSSCL_PRIORITY);
	
    m_bInitDS = TRUE;

	return m_bInitDS;
}
//note : ��ü�Ұ�
void CSound::OnRelease()
{
	D3DSAFE_RELEASE( m_pDSBuffer);
	D3DSAFE_RELEASE( m_pDSound);
}
//note : ���� ���� �ε�/Wave ������
bool CSound::Open( char *filename)
{
    if(!m_bInitDS)
	{
		ERRORMSG( "DirectSound �ʱ�ȭ�� �Ǿ���������(CSound::OpenOgg())");
		return FALSE;
	}
	
	LPDIRECTSOUNDBUFFER  pTemp;	// �ӽù���

    FILE *f;
    errno_t er = fopen_s( &f, filename, "rb");
	// File Loading ���н�
    if (!f) return FALSE;

	// vorbis�� ov_open�Լ��� ����� Ogg ���� ����
    ov_open(f, &m_sVF, NULL, 0);

    // vorbis�� ov_info()�Լ��� �̿� Ogg ���� ������
    vorbis_info *vi = ov_info(&m_sVF,-1);

    // DX SDK���� �����ϴ� wave��� ����ü
    WAVEFORMATEX        wfm;

	// wave header ���� �� Ogg���Ͽ��� ������ ������ �̿��Ͽ� ä���ش�
    memset(&wfm, 0, sizeof(wfm));
    wfm.cbSize          = sizeof(wfm);
    wfm.nChannels       = vi->channels;
    wfm.wBitsPerSample  = 16;									// ogg vorbis�� �׻� 16bit
    wfm.nSamplesPerSec  = vi->rate;
    wfm.nAvgBytesPerSec = wfm.nSamplesPerSec*wfm.nChannels*2;	// �����ͻ����� ����
    wfm.nBlockAlign     = 2*wfm.nChannels;
    wfm.wFormatTag      = 1;

    // set up the buffer
    DSBUFFERDESC desc;

    desc.dwSize         = sizeof(desc);
    desc.dwFlags        = 0;
    desc.lpwfxFormat    = &wfm;
	desc.dwReserved     = 0;
    desc.dwBufferBytes  = BUFSIZE;


	// CREATE TEMPORARY BUFFER
    m_pDSound->CreateSoundBuffer(&desc, &pTemp, NULL );

	DWORD   size = BUFSIZE;
    DWORD   pos = 0;
    int     sec = 0;
    int     ret = 1;

    char    *buf;
    char    *buf2;

    pTemp->Lock(0, size, (LPVOID*)&buf, &size, NULL, NULL, DSBLOCK_ENTIREBUFFER);
    
    // ������ ä���� Ogg->wav ������ ������ϰ�
	// vorbis�� ov_read�Լ��� �̿� Ogg->wav���Ϸ� ������ �Ѵ�
    while(ret && pos<size)
    {
        ret = ov_read(&m_sVF, buf+pos, size-pos, 0, 2, 1, &sec);
        pos += ret;
    }

    pTemp->Unlock( buf, size, NULL, NULL );

	//CREATE BUFFER TO MATCH ACTUAL SIZE OF FILE
    desc.dwBufferBytes  = pos;
	
    m_pDSound->CreateSoundBuffer( &desc, &m_pDSBuffer, NULL );
	m_pDSBuffer->Lock(0, pos, (LPVOID*)&buf2, &pos, NULL, NULL, DSBLOCK_ENTIREBUFFER);
    CopyMemory(buf2,buf,pos);
	m_pDSBuffer->Unlock( buf2, size, NULL, NULL );
	
	//DUMP THE TEMP BUFFER
	pTemp->Release();

	// vorbis�� �̿� Ogg������ �� ������� �������ش�.
	ov_clear(&m_sVF);
	fclose(f);

	buf = NULL;

    return TRUE;
}
//note : Ogg �������
bool CSound::Play(bool bLoop )
{
    if(!m_bInitDS)
	{
		ERRORMSG( "DirectSound �ʱ�ȭ�� �Ǿ���������(CSound::PlayOgg())");
		return false;
	}
	DWORD dwStatus;

	m_pDSBuffer->GetStatus(&dwStatus);
	// ���� ������̸� ÷���� �ٽ� ���
	if( dwStatus & DSBSTATUS_PLAYING)
	{
		Pause();
		return false;
	}
	else if( dwStatus & DSBSTATUS_TERMINATED )
	{
		m_pDSBuffer->SetCurrentPosition(0);
	}

	m_pDSBuffer->SetVolume( 0 );		// ���� ũ��� ���Ƿ� ����

	HRESULT hr = m_pDSBuffer->Play( 0, 0, bLoop ? DSBPLAY_LOOPING : 0 );	// �ݺ������ ���ؼ��� ����� �÷��� ����

	return (hr == S_OK);
}
//note : Ogg ��������
void CSound::Stop( )
{
	m_pDSBuffer->Stop();
	m_pDSBuffer->SetCurrentPosition(0);
}

//bool    CSound::Loop(bool bLoop )
//{
//	DSBCAPS cc;
//	m_pDSBuffer->GetCaps( & cc );
//	
//}
void CSound::Pause()
{
	DWORD status;
	HRESULT hr = m_pDSBuffer->GetStatus( &status );

	m_pDSBuffer->Stop();
}