#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>
#include <stdexcept>
#include "gtumap.h"
#include "gtuset.h"

using namespace std;
namespace _akincam_
{
	template<class K, class V>
	GTUMap<K,V>::GTUMap() :_used(0), _cap(1)
	{
		shared_ptr<pair<K,V> >_sp{new pair<K,V>[1], default_delete<pair<K,V>[]>()};
	}
	template<class K, class V>
	GTUMap<K,V>::GTUMap(int size) :_used(0)
	{
		if(size<0)
		{
			cerr<<endl<<"Size must be positive integer"<<endl;
			exit(1);
		}
		shared_ptr<pair<K,V> >_sp{new pair<K,V>[_cap], default_delete<pair<K,V>[]>()};
		_cap=size;

	}
	template<class K, class V>
	GTUMap<K,V>::GTUMap(const GTUMap<K,V>& _set)
					  :_cap(_set._cap),
				  		_used(_set._used)	
	{
		shared_ptr<pair<K,V> >_sp(new pair<K,V>[_cap], default_delete<pair<K,V>[]>());
		for(int i=0; i<_used; ++i){
			_sp.get()[i].first=_set._sp.get()[i].first;
			_sp.get()[i].second=_set._sp.get()[i].second;
		}		
	}	 
	template<class K, class V>
	GTUMap<K,V>& GTUMap<K,V>::operator =(const GTUMap<K,V>& rightSide)
	{
		if(_cap!=rightSide._cap)
		{
			shared_ptr<pair<K,V> >_sp(new pair<K,V>[rightSide._cap], default_delete<pair<K,V>[]>());
		}	
		_cap=rightSide._cap;
		_used=rightSide._used;
		for(int i=0; i<_used; ++i){
			_sp.get()[i].first=rightSide._sp.get()[i].first;
			_sp.get()[i].second=rightSide._sp.get()[i].second;
		}		
		return *this;	
	
	}
	template<class K, class V>
	GTUMap<K,V>::GTUMap(const K& index, const V& element)
	{
		shared_ptr<pair<K,V> >_sp(new pair<K,V>[1], default_delete<pair<K,V>[]>());
		_sp.get()[0].first=index;
		_sp.get()[0].second=element;
	
	}
	template<class K, class V>
	GTUMap<K,V>::~GTUMap()
	{
		//empty
		
	}	
	template<class K, class V>
	bool GTUMap<K,V>::empty() const
	{if(_used==0) return true; else return false;}
	
	template<class K, class V>			
	int GTUMap<K,V>::size() const
	{ return _used; }
	
	template<class K, class V>
	int GTUMap<K,V>::max_size() const
	{ return _cap; }
	
	template<class K, class V>
	void GTUMap<K,V>::clear()
	{ 
		if(_used>0)
		{
			_used=0;
			_cap=0;		
		}
	
	}
	template<class K, class V>		
	bool GTUMap<K,V>::count(const K& index, const V& element) const
	{
		
		for(int i=0; i<_used;++i)
			if(_sp.get()[i].first==index)
				if(_sp.get()[i].second==element)
					return true;
			return false;		
	
	}
	template<class K, class V>
	V& GTUMap<K,V>::operator [](const K& k)
	{
		for(int i=0; i<_used;++i){						
			if(this->_sp.get()[i].first==k){
				return _sp.get()[i].second;	
			}	
		}
		if(_used>=_cap){//eğer yer yoksa yer alır yeniden eleman eklemek için							
			shared_ptr<pair<K,V> >_sp1(new pair<K,V>[_cap+1], default_delete<pair<K,V>[]>());
			for(int i=0; i<_used; ++i){
				_sp1.get()[i].second=_sp.get()[i].second;	
				_sp1.get()[i].first=_sp.get()[i].first;		
		}			
			_cap=_cap+1;
			shared_ptr<pair<K,V> >_sp(new pair<K,V>[_cap], default_delete<pair<K,V>[]>());
			for(int i=0; i<_used; ++i){
				_sp.get()[i].second=_sp1.get()[i].second;
				_sp.get()[i].first=_sp1.get()[i].first;		
			}	

	}
	_sp.get()[_used].first=k;//elemanın indexini atar		
	this->_used=_used+1;	
	sort(_used-1);		
	return this->_sp.get()[_used-1].second;
}
template<class K, class V>
	//eleman eklemek için kullanılır
	void GTUMap<K,V>::insert(const K& index, const V& element)
	{
		for(int i=0; i<_used;++i){	//elemanın set te olup olmadığına bakar varsa excp fırlatır					
			if(this->_sp.get()[i].first==index){//ilk index aynımı diye bakar
				if(this->_sp.get()[i].second==element){//index değerleri aynı mı diye bakar
					throw invalid_argument("The element is member of set.");
					return;
				}
				if(this->_sp.get()[i].second!=element){
					this->_sp.get()[i].second=element;
					return;
				}	
			}	
		}
		if(_used>=_cap){	
								
			shared_ptr<pair<K,V> >_sp1(new pair<K,V>[_cap+1], default_delete<pair<K,V>[]>());
			for(int i=0; i<_used; ++i){
				_sp1.get()[i].second=element;	
				_sp1.get()[i].first=index;		
			}	
					
			_cap=_cap+1;
			
			shared_ptr<pair<K,V> >_sp(new pair<K,V>[_cap], default_delete<pair<K,V>[]>());
			for(int i=0; i<_used; ++i){
				_sp.get()[i].second=element;
				_sp.get()[i].first=index;		
			}
		}		
		_sp.get()[_used].first=index;
		this->_sp.get()[_used].second=element;	
		_used=_used+1;
		sort(_used);
					
	}
		
	template<class K, class V>
	void GTUMap<K,V>::sort(int n)
	{
		int i,j;
		V temp1;
		K temp2;
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				if(_sp.get()[i].first>_sp.get()[j].first){
					temp2=_sp.get()[i].first;
					temp1=_sp.get()[i].second;
					_sp.get()[i].first=_sp.get()[j].first;
					_sp.get()[i].second=_sp.get()[j].second;
					_sp.get()[j].first=temp2;
					_sp.get()[j].second=temp1;
				}
			}
		}
		
	}
	template<class K, class V>
	 bool GTUMap<K,V>::erase(const K& index, const V& element)
	 {
		 int c=0;
		
		for(int i=0; i<_used;++i)//elemanın listede olup olmadığını kontrol eder
			if(_sp.get()[i].first==index)
				if(_sp.get()[i].second==element)
					c=1;
		if(c==0)//listede yoksa
			return false;	
		shared_ptr<pair<K,V> >_sp1(new pair<K,V>[_cap], default_delete<pair<K,V>[]>());
		for(int p=0;p<_used;++p){
				_sp1.get()[p].first=_sp.get()[p].first;
				_sp1.get()[p].second=_sp.get()[p].second;
		}		
		for(int i=0; i<_used;++i){
			if(_sp.get()[i].first==index&&_sp.get()[i].second==element){//kaldırılmak istenen eleman sonda değilse
				if(i==0){
					for(int p=0,k=1;k<_used;++p,++k){//eleman listenin başındaysa
						_sp.get()[p].first=_sp1.get()[k].first;
						_sp.get()[p].second=_sp1.get()[k].second;
					}	
						_used-=1;
						sort(_used);
					return true;
					
				}	
				if(i==_used-1){	//eleman listenin sonundaysa		
					for(int p=0;p<_used-1;++p){
						_sp.get()[p].first=_sp1.get()[p].first;
						_sp.get()[p].second=_sp1.get()[p].second;
					}	
					_used-=1;
					sort(_used);
					return true;
				}
				else{//eleman başta ve sonda değil ise
					for(int p=0,k=0;k<_used;++p,++k){
						if(k==i)
							k++;
						_sp.get()[p].first=_sp1.get()[k].first;
						_sp.get()[p].second=_sp1.get()[k].second;
					}	
						_used-=1;
						sort(_used);	
					return true;
				}		

			}
		}			
	 }
	 template<class K, class V>
	typename GTUMap<K,V>::GTUIterator GTUMap<K,V>::find(const K& index)
	{
		for(int i=0; i<_used; ++i){
			if(_sp.get()[i].first==index)
				return  (&_sp.get()[i]);
		}		
		return &_sp.get()[_used];
	
	}	
	 template<class K, class V>
	 typename GTUMap<K,V>::GTUIterator GTUMap<K,V>::begin()
	 {
	 	sort(_used);
	 	return (_sp.get());
	 }
	template<class K, class V>
	typename GTUMap<K,V>::GTUIterator GTUMap<K,V>::end()
	{
		return (_sp.get()+_used);
	}
	
}
	
	
					
