#ifndef GTUMAP_H
#define GTUMAP_H 
#include <stdexcept>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>
#include <utility>
#include <string>
#include "gtuset.h"
using namespace std;
namespace _akincam_
{
	template<class K, class V>
	class GTUMap : public GTUSet<pair<K,V>>
	{
		public:
			GTUMap();//parametresiz constructor 			
			GTUMap(int size); //kullanıcının size belirleyebileceği constructor				
			GTUMap(const GTUMap<K,V>& _set);	 //copy constructor
			GTUMap(const K& index, const V& element);
			GTUMap<K,V>& operator =(const GTUMap<K,V>& rightSide); //pointerlar ile uğraştığımız için adres ataması yapılır
			~GTUMap();	
			V& operator [](const K& k);
			
			bool erase(const K& index, const V& element);	//istenilen elemanı siler eğer eleman yoksa program devam eder çalışmaya	
			void insert(const K& index, const V& element);
			 bool empty() const;		
			 int size() const;	//kullanıcının elaman sayısını yani toplam size ı döndürür
			 int max_size() const;	 //kullanılan bilgisayara gmre toplam _max_size döndürür	
			 void clear();	//elemanları temizler size ı düşürür		
			 bool count(const K& index, const V& element) const;	//istenilen elemanın set de olup olmadığına bakar set te her elemandan bir tane olduğu için T F döndürür
			typename GTUMap<K,V>::GTUIterator begin();
			typename GTUMap<K,V>::GTUIterator end() ;
			typename GTUMap<K,V>::GTUIterator find(const K& index);
			void sort(int n);
		private:
			shared_ptr<pair<K,V> >_sp{new pair<K,V>[100], default_delete<pair<K,V>[]>()};
			int _cap;
			int _used;
			

	};

}
#endif

