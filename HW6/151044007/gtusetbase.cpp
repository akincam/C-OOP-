#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>


using namespace std;
#include "gtusetbase.h"
namespace _akincam_
{
	template<class T>
	GTUSetBase<T>::GTUSetBase() : _used(0), _cap(5)
	{
		shared_ptr<T>_sp(new T[_cap], default_delete<T[]>());	
	}
	template<class T>
	GTUSetBase<T>::GTUSetBase(int size) : _used(0)
	{
	
		if(size<0)
		{
			cerr<<endl<<"Size must be positive integer"<<endl;
			exit(1);
		}
		shared_ptr<T>_sp(new T[size], default_delete<T[]>());
		_cap=size;
		
	}
	template<class T>
	GTUSetBase<T>::GTUSetBase(const GTUSetBase<T>& _set)
				  :_cap(_set.getMaxCap()),
				  _used(_set.getUsed())	
	{
		shared_ptr<T>_sp(new T[_cap], default_delete<T[]>());
		for(int i=0; i<_used; ++i)
			_sp.get()[i]=_set._sp.get()[i];	
	}	 
	template<class T>
	GTUSetBase<T>& GTUSetBase<T>::operator =(const GTUSetBase& rightSide)
	{
		if(_cap!=rightSide._cap)
		{
			shared_ptr<T>_sp(new T[rightSide._cap], default_delete<T[]>());
		}	
		_cap=rightSide._cap;
		_used=rightSide._used;
		for(int i=0;i<_used;++i)
			_sp.get()[i]=rightSide._sp.get()[i];
		return *this;	
	}

	template<class T>		
	GTUSetBase<T>::~GTUSetBase()
	{
		//empty
	}
	template<class T>	
	int GTUSetBase<T>::getUsed() const
	{
	 	return _used;
	}
	template<class T>	
	int GTUSetBase<T>::getMaxCap() const
	{
		return _cap;
	}	

}				
