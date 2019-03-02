#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>
#include <stdexcept>

#include "gtuset.h"
using namespace std;
namespace _akincam_
{
	//kapasiteyi 5 alır parametre olmadığında
	template<class T>
	GTUSet<T>::GTUSet() :_used(0),_cap(5)
	{
		shared_ptr<T>_sp(new T[_cap], default_delete<T[]>());	
	}
	//kullanıcı legal bir değer girdiğinde atama yapar
	template<class T>
	GTUSet<T>::GTUSet(int size) :_used(0)
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
	GTUSet<T>::GTUSet(const GTUSet<T>& _set)
				  :_cap(_set.getMaxCap()),
				  _used(_set.getUsed())	
	{
		shared_ptr<T>_sp(new T[_cap], default_delete<T[]>());
		for(int i=0; i<_used; ++i)
			_sp.get()[i]=_set._sp.get()[i];	
	}	 
	template<class T>
	GTUSet<T>& GTUSet<T>::operator =(const GTUSet<T>& rightSide)
	{
		if(_cap!=rightSide.getMaxCap())
		{
			shared_ptr<T>_sp(new T[rightSide.getMaxCap()], default_delete<T[]>());
		}	
		_cap=rightSide._cap;
		_used=rightSide._used;
		for(int i=0;i<_used;++i)
			_sp.get()[i]=rightSide._sp.get()[i];
		return *this;	
	}
	template<class T>		
	GTUSet<T>::~GTUSet()
	{
		//shared pointer olduğu ve referans count döndürdüğü için kendi delete yapıyor
	}
	//eğer set içinde _used 0 ise true döndürür
	template<class T>	
	bool GTUSet<T>::empty() const
	{
		if(size()==0)
			return true;
		else
			return false;	
	}
	//size ı döndürür
	template<class T>
	int GTUSet<T>::size() const
	{
		return _used;
	}
	//toplam kapasite için ayrılan max size ı döndürür
	template<class T>
	int GTUSet<T>::max_size() const
	{
		return _cap;
	}
	//eleman var ise çıkarır
	template<class T>	
	bool GTUSet<T>::erase(const T& element)
	{
		int c=0;
		
		for(int i=0; i<_used;++i)
			if(_sp.get()[i]==element)
					c=1;
		if(c==0)
			return false;			
		shared_ptr<T>_sp1(new T[_cap], default_delete<T[]>());
		for(int p=0;p<_used;++p)
				_sp1.get()[p]=_sp.get()[p];
		for(int i=0; i<_used;++i){
			if(_sp.get()[i]==element){//kaldırılmak istenen eleman sonda değilse
				if(i==0){
					for(int p=0,k=1;k<_used;++p,++k)
						_sp.get()[p]=_sp1.get()[k];
						_used-=1;
						sort(_used);
					return true;
					
				}	
				if(i==_used-1){			
					for(int p=0;p<_used-1;++p)
						_sp.get()[p]=_sp1.get()[p];
					_used-=1;
					sort(_used);
					return true;
				}
				else{
					for(int p=0,k=0;k<_used;++p,++k){
						if(k==i)
							k++;
						_sp.get()[p]=_sp1.get()[k];
					}	
						_used-=1;
						sort(_used);
					return true;
				}		
				
				
			}
			
			
		}
	}
	template<class T>
	//eleman eklemek için kullanılır
	void GTUSet<T>::insert(const T& element)
	{
		
		bool boo=true;
		for(int i=0; i<_used;++i){
			if(_sp.get()[i]==element){//elemanın set içinde olup olmadığına bakar
				boo=false;
				break;
			}	
		}
		if(boo==false)
			throw invalid_argument("The element is member of set.");
		if(boo==true)//eğer yoksa
		{	
			if(_used>=_cap)//yer yoksa yeniden yer ayrılır
			{
				shared_ptr<T>_sp1(new T[_cap+1], default_delete<T[]>());
				_cap =_cap+1;	
				for(int p=0;p<_used;++p)
					_sp1.get()[p]=_sp.get()[p];
				shared_ptr<T>_sp(new T[_cap], default_delete<T[]>());
				for(int p=0;p<_used;++p)
					_sp1.get()[p]=_sp.get()[p];	
			}
			_sp.get()[_used]=element;
			_used++;
			sort(_used);
			return;
		}	
		return;	
	}
	//set i temizler
	template<class T>	
	void GTUSet<T>::clear()
	{
		if(_used>0)
		{
			
			_used=0;
			_cap=0;		
		}
	}
	//elemanın olup olmadığına bakar set olduğu için true false döndürür
	template<class T>			
	bool GTUSet<T>::count(const T& element) const
	{
		for(int i=0; i<_used;++i)
			if(_sp.get()[i]==element)
				return true;
		
			return false;
					
	}
	template <class T>
	void GTUSet<T>::sort(int n)
	{
		int i,j;
		T temp;
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				if(_sp.get()[i]>_sp.get()[j]){
					temp=_sp.get()[i];
					_sp.get()[i]=_sp.get()[j];
					_sp.get()[j]=temp;
				}
			}
		}
	}
	template<class T>
	GTUSet<T>::GTUIterator::GTUIterator()
	{
		p=nullptr;
		
	}
	template<class T>
	GTUSet<T>::GTUIterator::GTUIterator(T* point)
	{ 
		p=point;
	}
	template<class T>	
	GTUSet<T>::GTUIterator::GTUIterator(const typename GTUSet<T>::GTUIterator& _right)
	{
		p=_right.p;//adres ataması yapılır copyalama için 
	}
	template<class T>
	typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator =(const GTUSet<T>& rightSide)
	{
		p= rightSide._sp.get(); 
		return *this;
	}
	template<class T>
	GTUSet<T>::GTUIterator::~GTUIterator()
	{
		//empty
	}
}
namespace _akincam_
{	
	//T++ için yaplan overloading
	template<class T>				
	typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator++()
	{
	 	p++;
		return *this;
	}
	//prefix overloading
	template<class T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator++(int)
	{
		GTUIterator point = *this;
	 	p++; 
	 	return GTUIterator(point);	
	}
	template<class T>				
	typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator--()
	{
		p--;
		return *this;
		
	}
	template<class T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::operator--(int)
	{
		GTUIterator point = *this;
	 	p--; 
	 	return point;
	}
	template<class T>				
	T& GTUSet<T>::GTUIterator::operator*()
	{
		return *p;
	}
	template<class T>
	T* GTUSet<T>::GTUIterator::operator->() 
	{
		return p;
	}
	template<class T>					
	typename GTUSet<T>::GTUIterator GTUSet<T>::GTUIterator::getP() const
	{
		return p;
	}					
	template<class T>
	bool GTUSet<T>::GTUIterator::operator==(const typename GTUSet<T>::GTUIterator & comp)
	{
		if(p==comp.p)
			return true;
		return false;		
	}
	template<class T>
	bool GTUSet<T>::GTUIterator::operator!=(const typename GTUSet<T>::GTUIterator & comp)
	{
		if(p!=comp.p)
			return true;
		return false;		
	}
	//ilk elemanın adresini döndürür
	template<class T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::begin()
	{ 
		return GTUSet<T>::GTUIterator(_sp.get());
	}
	//_cap+1 yani array in dışında bir yer döndürür
	template<class T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::end()
	{
		if(this->size()==0)
			_cap=0;
		 return  GTUSet<T>::GTUIterator(&_sp.get()[_used]);
	}
	//eğer eleman var ise o adresi yoksa end() döndürür
	template<class T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::find(const T& element)
	{
		for(int i=0; i<_used; ++i){
			if(_sp.get()[i]==element)
				return  GTUSet<T>::GTUIterator(&_sp.get()[i]);
		}		
		return GTUSet<T>::GTUIterator(&_sp.get()[_used]);	
	}
}	


