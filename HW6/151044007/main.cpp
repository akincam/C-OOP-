#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <memory>
#include <utility>
using namespace std;
#include <stdexcept>
#include "gtusetbase.h"
#include "gtuset.h"

#include "gtumap.cpp"
#include "gtuset.cpp"
#include "gtusetbase.cpp"
using namespace _akincam_;

//hocam sadece yazabildim bu globali test edemedim cok az zaman kalmıştı
template<class T>
shared_ptr<GTUSetBase<T> > setIntersection(const GTUSetBase<T>& object1 ,const GTUSetBase<T>& object2)
{

	GTUSet<T> a;
	int n1 =object1.size();
	int n2 =object2.size();
	
	auto s1=object1.begin();
	auto s2=object2.begin();
	if(n1<n2){
		for(int i=0;i<n2;++i){
			for(s1=object1.begin();s1!=object1.end();s1++)
				if(*s1==*s2)
					a.insert(*s2);
			s2++;		
			}
	}
	else{
		for(int i=0;i<n1;++i){
			for(s2=object1.begin();s2!=object1.end();s2++)
				if(*s1==*s2)
					a.insert(*s1);
			s1++;
			}
		}
	
	shared_ptr<GTUSet<T> > temp{new GTUSet<T>(a.size())};
	
	for(auto s3=a.begin();s3!=a.end();s3++)
		temp->insert(*s3);
	return temp;
}		


int main(){

	GTUSet<int>::GTUIterator set;
	GTUSet<int> s1;
	try{
	
	cout<<"------------------------"<<endl;
	if(s1.empty()==1)
		cout<<"Set is empty"<<endl;
	else
		cout<<"Set have element"<<endl;
		
	cout<<"------------------------"<<endl;
	
	cout<<"The set of size "<<s1.size()<<endl;
	
	cout<<"------------------------"<<endl;	
	
	cout<<"The set of max size "<<s1.max_size()<<endl;	
	
	cout<<"------------------------"<<endl;	
	cout<<"Eleman ekledim"<<endl;
	s1.insert(4);	
	s1.insert(41);
	s1.insert(2);
	s1.insert(3);
	s1.insert(8);
	
	for(set=s1.begin();set!=s1.end(); set++)
		cout<<"  "<<*set<<endl;
	cout<<endl;
		
	cout<<"------------------------"<<endl;
	cout<<"Eleman çıkardım"<<endl;	
	cout<<"------------------------"<<endl;
	s1.erase(4);	
	s1.erase(41);

	for(set=s1.begin();set!=s1.end(); set++)
		cout<<"  "<<*set<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;	
	cout<<"The set of size "<<s1.size()<<endl;	
	cout<<"------------------------"<<endl;
	cout<<"Clear yaptım"<<endl;
	cout<<"------------------------"<<endl;
	s1.clear();
	for(set=s1.begin();set!=s1.end(); set++)
		cout<<"  "<<*set<<endl;
	cout<<endl;
	
	s1.insert(5);

	cout<<"------------------------"<<endl;
	for(set=s1.begin();set!=s1.end(); set++)
		cout<<"  "<<*set<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;
	if(s1.count(41)==1)
		cout<<"element is there"<<endl;
	else
		cout<<"count is 0"<<endl;
			
	cout<<"------------------------"<<endl;
	s1.insert(5);
	}
	catch(invalid_argument a){
	
		cerr<<"Thrown a Execption!!!!!!"<<endl;
		cerr<<"the element in the set"<<endl;
		
	}
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	GTUSet<double>::GTUIterator set1;
	GTUSet<double> s4;
	try{
	
	cout<<"------------------------"<<endl;
	if(s4.empty()==1)
		cout<<"Set is empty"<<endl;
	else
		cout<<"Set have element"<<endl;
		
	cout<<"------------------------"<<endl;
	
	cout<<"The set of size "<<s4.size()<<endl;
	
	cout<<"------------------------"<<endl;	
	
	cout<<"The set of max size "<<s4.max_size()<<endl;	
	
	cout<<"------------------------"<<endl;	
	
	s4.insert(4.1);	
	s4.insert(4.2);
	s4.insert(2.3);
	s4.insert(3.5);
	s4.insert(8.6);
	
	for(set1=s4.begin();set1!=s4.end(); set1++)
		cout<<"  "<<*set1<<endl;
	cout<<endl;
		
	cout<<"------------------------"<<endl;	
	s4.erase(4.6);	
	s4.erase(3.5);

	for(set1=s4.begin();set1!=s4.end(); set1++)
		cout<<"  "<<*set1<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;	
	cout<<"The set of size "<<s4.size()<<endl;	
	cout<<"------------------------"<<endl;
	
	s4.clear();
	for(set1=s4.begin();set1!=s4.end(); set1++)
		cout<<"  "<<*set<<endl;
	cout<<endl;
	
	s4.insert(5.9);

	cout<<"------------------------"<<endl;
	for(set1=s4.begin();set1!=s4.end(); set1++)
		cout<<"  "<<*set1<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;
	if(s4.count(5.9)==1)
		cout<<"element is there"<<endl;
	else
		cout<<"count is 0"<<endl;
			
	cout<<"------------------------"<<endl;
	
	}
	catch(invalid_argument a){
	
		cerr<<"Thrown a Execption!!!!!!"<<endl;
		cerr<<"the element in the set"<<endl;
		exit(1);
	}
	
	
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	GTUSet<char>::GTUIterator set3;
	GTUSet<char> s2;
	try{
	
	cout<<"------------------------"<<endl;
	if(s2.empty()==1)
		cout<<"Set is empty"<<endl;
	else
		cout<<"Set have element"<<endl;
		
	cout<<"------------------------"<<endl;
	
	cout<<"The set of size "<<s2.size()<<endl;
	
	cout<<"------------------------"<<endl;	
	
	cout<<"The set of max size "<<s2.max_size()<<endl;	
	
	cout<<"------------------------"<<endl;	
	
	s2.insert('k');	
	s2.insert('a');
	s2.insert('b');
	s2.insert('c');
	s2.insert('f');
	
	for(set3=s2.begin();set3!=s2.end(); set3++)
		cout<<"  "<<*set3<<endl;
	cout<<endl;
		
	cout<<"------------------------"<<endl;	
	s2.erase('c');	
	s2.erase('a');

	for(set3=s2.begin();set3!=s2.end(); set3++)
		cout<<"  "<<*set3<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;	
	cout<<"The set of size "<<s4.size()<<endl;	
	cout<<"------------------------"<<endl;
	
	for(set3=s2.begin();set3!=s2.end(); set3++)
		cout<<"  "<<*set3<<endl;
	cout<<endl;
	
	s2.insert('p');

	cout<<"------------------------"<<endl;
	for(set3=s2.begin();set3!=s2.end(); set3++)
		cout<<"  "<<*set3<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;
	if(s4.count('a')==1)
		cout<<"element is there"<<endl;
	else
		cout<<"count is 0"<<endl;
			
	cout<<"------------------------"<<endl;
	
	}
	catch(invalid_argument a){
	
		cerr<<"Thrown a Execption!!!!!!"<<endl;
		cerr<<"the element in the set"<<endl;
		exit(1);
	}
	
	
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	GTUSet<string> s5;
	GTUSet<string>::GTUIterator set5;
	try{
	
	cout<<"------------------------"<<endl;
	if(s5.empty()==1)
		cout<<"Set is empty"<<endl;
	else
		cout<<"Set have element"<<endl;
		
	cout<<"------------------------"<<endl;
	
	cout<<"The set of size "<<s5.size()<<endl;
	
	cout<<"------------------------"<<endl;	
	
	cout<<"The set of max size "<<s5.max_size()<<endl;	
	
	cout<<"------------------------"<<endl;	
	
	s5.insert("akin");		
	s5.insert("hidayet");
	s5.insert("sivas");
	s5.insert("ebru");
	s5.insert("öykürü");
	s5.insert("bağlama");	
	s5.insert("gtü");
	s5.insert("hasan");
	

	
	
	
	for(set5=s5.begin();set5!=s5.end(); set5++)
		cout<<"  "<<*set5<<endl;
	cout<<endl;
	
	cout<<"------------------------"<<endl;	
	s5.erase("akin");	
	s5.erase("sasas");
	s5.erase("gtü");
	s5.erase("hasan");

	for(set5=s5.begin();set5!=s5.end(); set5++)
		cout<<"  "<<*set5<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;	
	cout<<"The set of size "<<s5.size()<<endl;	
	cout<<"------------------------"<<endl;
	
	for(set5=s5.begin();set5!=s5.end(); set5++)
		cout<<"  "<<*set5<<endl;
	cout<<endl;
	
	s5.insert("paa");

	cout<<"------------------------"<<endl;
	for(set5=s5.begin();set5!=s5.end(); set5++)
		cout<<"  "<<*set5<<endl;
	cout<<endl;
	cout<<"------------------------"<<endl;
	cout<<"The set of size "<<s5.size()<<endl;
	
	if(s5.count("hidayet")==true)
		cout<<"element is there"<<endl;
	else
		cout<<"count is 0"<<endl;
			
	cout<<"------------------------"<<endl;
	s5.insert("paa");
	}
	catch(invalid_argument a){
	
		cerr<<"Thrown a Execption!!!!!!"<<endl;
		cerr<<"the element in the set"<<endl;
		
	}
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	cout<<"****************************************************************************"<<endl;
	
	GTUMap<string ,int>::GTUIterator it;
	GTUMap<string, int> map;
	
	cout<<"------------------------"<<endl;
	cout<<"The set of size "<<map.size()<<endl;
	cout<<"------------------------"<<endl;
	map["sari"]=5;
	map["yesil"]=2;
	map["beyaz"]=7;
	map["turuncu"]=4;
	map["bordo"]=121;
	map["kirmizi"]=54;
	map["mavi"]=444;
	map["mor"]=32;	
	for(it=map.begin();it!=map.end();it++)
		cout<<it->first<<" ---> "<<it->second<<endl;
	cout<<"------------------------"<<endl;	
	cout<<"eleman çıkardım"<<endl;
	map.erase("sari",5);
	map.erase("mavi",444);
	map.erase("beyaz",5);
	cout<<"------------------------"<<endl;
	for(it=map.begin();it!=map.end();it++)
		cout<<it->first<<" ---> "<<it->second<<endl;
			
	cout<<"------------------------"<<endl;
	cout<<"The set of size "<<map.size()<<endl;
	cout<<"------------------------"<<endl;
	cout<<"insert yaptım"<<endl;
	cout<<"------------------------"<<endl<<endl;
	map.insert("sari",9);
	map.insert("kahve",444);
	map.insert("gri",5);
	for(it=map.begin();it!=map.end();it++)
		cout<<it->first<<" ---> "<<it->second<<endl;
		cout<<"------------------------"<<endl;
	if(map.find("yesil")!=map.end())
		cout<<"yeşil is in the map"<<endl;
		cout<<"------------------------"<<endl;
	if(map.find("saris")==map.end())
		cout<<"saris isn't in the map"<<endl;
		cout<<"------------------------"<<endl;	
		cout<<"The set of max_size "<<map.max_size()<<endl;
		cout<<"------------------------"<<endl;
		map.clear();
		for(it=map.begin();it!=map.end();it++)
			cout<<it->first<<" ---> "<<it->second<<endl;

	return 0;
}
























	
			
	




