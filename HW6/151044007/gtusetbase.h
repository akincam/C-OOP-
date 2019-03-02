#ifndef	GTUSETBASE_H
#define GTUSETBASE_H	

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>

using namespace std;
namespace _akincam_
{
	template<class T>
	class GTUSetBase
	{
		public:
			GTUSetBase();//parametresiz constructor			
			GTUSetBase(int size); //kullanıcının size belirleyebileceği constructor					
			GTUSetBase(const GTUSetBase<T>& _set);	 //copy constructor
			
			GTUSetBase<T>& operator =(const GTUSetBase<T>& rightSide);//pointerlar ile uğraştığımız için adres ataması yapılır
			
			int getUsed() const; //size döndürür
			int getMaxCap() const;//capasity döndürür							
			virtual ~GTUSetBase()=0;	
					
			virtual bool empty() const=0;		
			virtual int size() const=0;	
			virtual int max_size() const=0;		
			virtual void insert(const T& element)=0;			
			virtual bool erase(const T& element)=0;			
			virtual void clear()=0;			
			virtual bool count(const T& element) const=0;
			class GTUIterator
			{
				public:
					GTUIterator();//nullpointer döndürür
					GTUIterator(T* point);//iteratöre adresi ataması yapar
					GTUIterator(const GTUIterator& _right);
					GTUIterator& operator =(const GTUSetBase<T>& rightSide);
					~GTUIterator();//delete yapıp nullpointer atar dangling pointer durumunu önlemek için
					virtual bool operator==(const GTUIterator& comp);
					virtual bool operator!=(const GTUIterator& comp);
				
					virtual GTUIterator getP() const; //Template pointer ın adresini döndürür
				
					virtual GTUIterator& operator++();
					virtual GTUIterator operator++(int);
				
					virtual GTUIterator& operator--();
					virtual GTUIterator operator--(int);
				
					virtual T& operator*();
					virtual T* operator->();
										
				protected:
					T* p;
				
			};	
			virtual void sort(int n)=0;																
			typename GTUSetBase<T>::GTUIterator begin();
			typename GTUSetBase<T>::GTUIterator end();
			typename GTUSetBase::GTUIterator find(const T& element);
			
			
			protected:		
				shared_ptr<T>_sp{new T[150], default_delete<T[]>()};
				int _used;		
				int _cap;
				
	};
}
#endif


