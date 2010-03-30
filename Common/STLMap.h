
#ifndef _STLMap_H
#define _STLMap_H

#pragma warning(disable : 4786)		// Visual C++ Only

#include <map>
using namespace std;

template <class T1, class T2> class CSTLMap  
{
public:
	typedef typename map < T1, T2* >::iterator		Iterator;
	typedef typename map < T1, T2* >::value_type		ValueType;

	map < T1, T2* >		m_UserTypeMap;

	int GetSize() { return m_UserTypeMap.size(); };
	
	bool PutData( T1 key_value, T2* pData)
	{
		if( !pData ) return false;
		pair<Iterator, bool> temp_pair = m_UserTypeMap.insert( ValueType( key_value, pData ) );
		return temp_pair.second;
	};
	
	T2* GetData( T1 key_value )
	{
		T2* pData = NULL;
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return NULL;
		else
			pData = (*iter).second;
		
		return pData;
	};

	bool DeleteData( T1 key_value )
	{
		if( m_UserTypeMap.empty() )
			return false;
		
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return false;
		else {
			T2* pData = NULL;
			pData = (*iter).second;

			m_UserTypeMap.erase(iter);

			delete pData;
			pData = NULL;

			return true;
		}
	};

	void DeleteAllData()
	{
		Iterator iter1 = m_UserTypeMap.begin(), iter2 = m_UserTypeMap.end();
		for(; iter1 != iter2; iter1++ )
			delete (*iter1).second;
		
		m_UserTypeMap.clear();
	};

	bool IsExist( T1 key_value )
	{
		Iterator iter = m_UserTypeMap.find( key_value );
		if( iter == m_UserTypeMap.end() )
			return false;
		else
			return true;
	};

	bool IsEmpty() { return m_UserTypeMap.empty(); };

	CSTLMap() {};
	virtual ~CSTLMap() {
		DeleteAllData();
	};
};

#endif // _STLMap_H
