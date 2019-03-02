#ifndef	GTUSET_H
#define GTUSET_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>

#include "gtusetbase.h"

using namespace std;
namespace _akincam_
{

	template<class T>

	class GTUSet: public GTUSetBase<T>
	{
		public:
			GTUSet();//parametresiz constructor 			
			GTUSet(int size); //kullanıcının size belirleyebileceği constructor				
			GTUSet(const GTUSet<T>& _set);	 //copy constructor
			
			GTUSet<T>& operator =(const GTUSet<T>& rightSide); //pointerlar ile uğraştığımız için adres ataması yapılır			
			 ~GTUSet();						
			 bool empty() const;		
			 virtual int size() const;	//kullanıcının elaman sayısını yani toplam size ı döndürür
			 int max_size() const;	 //kullanılan bilgisayara gmre toplam _max_size döndürür	
			 void insert(const T& element) override;	//eleman ekler eğer yer yoksa yer ayırır ve eleman ekler		
			 bool erase(const T& element);	//istenilen elemanı siler eğer eleman yoksa program devam eder çalışmaya		
			 void clear();	//elemanları temizler size ı düşürür		
			 bool count(const T& element) const;	//istenilen elemanın set de olup olmadığına bakar set te her elemandan bir tane olduğu için T F döndürür
			class GTUIterator
			{
				public:
					GTUIterator();//nullpointer döndürür
					GTUIterator(T* point);//iteratöre adresi ataması yapar
					GTUIterator(const GTUIterator& _right);
					GTUIterator& operator =(const GTUSet<T>& rightSide);
					~GTUIterator();//delete yapıp nullpointer atar dangling pointer durumunu önlemek için
					bool operator==(const GTUIterator& comp);
					bool operator!=(const GTUIterator& comp);
				
					GTUIterator getP() const; //Template pointer ın adresini döndürür
				
					GTUIterator& operator++();
					GTUIterator operator++(int);
				
					GTUIterator& operator--();
					GTUIterator operator--(int);
				
					T& operator*();
					T* operator->();
										
				protected:
					T* p;
				
			};		
			virtual void sort(int n);											
			virtual GTUSet<T>::GTUIterator begin();
			virtual GTUSet<T>::GTUIterator end() ;
			virtual GTUSet<T>::GTUIterator find(const T& element);

		protected:		
			shared_ptr<T>_sp{new T[150], default_delete<T[]>()};
			int _used;		
			int _cap;
			
			
	};
}
#endif




