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
// 공개용 함수
//////////////////////////////////////////////////////////////////////////
//note : 클래스 사용에 필요한 객체생성
bool CSound::OnCreate( HWND hWnd)
{	
	// Direct Sound 초기화
	if(FAILED( DirectSoundCreate8(NULL, &m_pDSound, NULL)))
	{
		ERRORMSG( "DirectSound 생성실패[CSound::OnCreate()]");
        return m_bInitDS = FALSE;
	}
	
	m_pDSound->Initialize( NULL);
	m_pDSound->SetCooperativeLevel( hWnd, DSSCL_PRIORITY);
	
    m_bInitDS = TRUE;

	return m_bInitDS;
}
//note : 객체소거
void CSound::OnRelease()
{
	D3DSAFE_RELEASE( m_pDSBuffer);
	D3DSAFE_RELEASE( m_pDSound);
}
//note : 사운드 파일 로드/Wave 컨버전
bool CSound::Open( char *filename)
{
    if(!m_bInitDS)
	{
		ERRORMSG( "DirectSound 초기화가 되어있지않음(CSound::OpenOgg())");
		return FALSE;
	}
	
	LPDIRECTSOUNDBUFFER  pTemp;	// 임시버퍼

    FILE *f;
    errno_t er = fopen_s( &f, filename, "rb");
	// File Loading 실패시
    if (!f) return FALSE;

	// vorbis의 ov_open함수를 사용항 Ogg 파일 오픈
    ov_open(f, &m_sVF, NULL, 0);

    // vorbis의 ov_info()함수를 이용 Ogg 정보 얻어오기
    vorbis_info *vi = ov_info(&m_sVF,-1);

    // DX SDK에서 지원하는 wave헤더 구조체
    WAVEFORMATEX        wfm;

	// wave header 셋팅 후 Ogg파일에서 가져온 정보를 이용하여 채워준다
    memset(&wfm, 0, sizeof(wfm));
    wfm.cbSize          = sizeof(wfm);
    wfm.nChannels       = vi->channels;
    wfm.wBitsPerSample  = 16;									// ogg vorbis는 항상 16bit
    wfm.nSamplesPerSec  = vi->rate;
    wfm.nAvgBytesPerSec = wfm.nSamplesPerSec*wfm.nChannels*2;	// 테이터사이즈 셋팅
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
    
    // 위에서 채워논 Ogg->wav 컨버전 헤더파일과
	// vorbis의 ov_read함수를 이용 Ogg->wav파일로 컨버팅 한다
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

	// vorbis를 이용 Ogg정보를 다 사용한후 삭제해준다.
	ov_clear(&m_sVF);
	fclose(f);

	buf = NULL;

    return TRUE;
}
//note : Ogg 파일재생
bool CSound::Play(bool bLoop )
{
    if(!m_bInitDS)
	{
		ERRORMSG( "DirectSound 초기화가 되어있지않음(CSound::PlayOgg())");
		return false;
	}
	DWORD dwStatus;

	m_pDSBuffer->GetStatus(&dwStatus);
	// 곡이 재생중이면 첨부터 다시 재생
	if( dwStatus & DSBSTATUS_PLAYING)
	{
		Pause();
		return false;
	}
	else if( dwStatus & DSBSTATUS_TERMINATED )
	{
		m_pDSBuffer->SetCurrentPosition(0);
	}

	m_pDSBuffer->SetVolume( 0 );		// 볼름 크기는 임의로 정함

	HRESULT hr = m_pDSBuffer->Play( 0, 0, bLoop ? DSBPLAY_LOOPING : 0 );	// 반복재생을 위해서는 재생지 플래그 설정

	return (hr == S_OK);
}
//note : Ogg 파일정지
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