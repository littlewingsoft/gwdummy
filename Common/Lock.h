#pragma once

class CLock
{
public:
	CLock( CRITICAL_SECTION&	cs): m_cs(cs)
		{ EnterCriticalSection(&m_cs);};
	~CLock(void)
		{ LeaveCriticalSection(&m_cs);};

private:
	CRITICAL_SECTION&	m_cs;
};
