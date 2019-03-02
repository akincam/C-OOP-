
import java.io.PrintStream;

/**
 *GTUSet classını generic olarak oluşturdum
 * @author akncam
 * @param <T>
 */


public class GTUSet<T> implements GTUSetInt<T> 
{
    protected T[] data;//set için veriyi tutar
    protected int _size=0;
    protected int _cap=0;

   /**
    *GTUSet parametresiz const. oluşturdum
    * yer aldım ve size ı initialize ettim
    * @author akncam
    */
    public GTUSet() 
    {
        _size=0;       
        _cap=1;
        data=(T[])new Object[_cap];
    }
    /**
    *GTUSet size alan const oluşturdum
    * kullanıcıdan alınan size kadar yer ayırdum
    * @author akncam
    * @param size
    */
    public  GTUSet(int size)
    {
	if(size<0)//constructorla birlikte girilen size negatif ise
	{
            System.err.println("Size must be positive integer");
       	    System.exit(1);
	}
        _size=0;
        _cap=size;
        data=(T[])new Object[_cap];
    }
    /**
     * kullanıcı direk constructor ile eleman ekleme işlemi yapmak isterse
     * yer yoksa yer ayırıyorum ve ekliyorum gereken indexe
     * @param data1 
     */
    public GTUSet(T data1)//kullanıcı constructorla eleman eklemek isterse
    {
       if(_size>=_cap)//eğer yeterli kapasite yoksa yeniden yer alma işlemi yapar
       {
            T[] data2;
            data2=(T[])new  Object[_cap+1];
            _cap =_cap+1;	
            for(int p=0;p<_size;++p)
                  data2[p]=data[p];
            data=(T[])new Object[_cap];
            for(int p=0;p<_size;++p)
                 data[p]=data2[p];	
        }
        data[_size]=data1;
        _size++;
    }
    /**
     * eğer hiç eleman insert edilmediyse true döndürür
     * @return 
     */
    @Override
    public boolean empty()
    {
	return _size==0;	
    }
    /**
     * insert edilen eleman sayısını döndürür 
     * @return 
     */
    @Override
    public int size()
    {
	return _size;
    }
    /**
     * toplam set kapasitesini döndürür
     * @return 
     */
    @Override
    public int max_size()
    {
	return _cap;
    }
    /**
     * extend edilen map classında data ya erişmek için oluşturuldu
     * @param index
     * @return 
     */
    protected T getter(int index)
    {
        return data[index];
    }
    /**
     * map classında erase yaptığımzda setter fonksiyonu ile
     * ilgili eleman kaldırılır.
     * elemanın yerine göre işlem yapılır
     * elemanın başta ortada ve sonda olmasına göre
     * @param index 
     */
    protected void setter(int index)
    {
        if(index==0){
          T[] data1=(T[])new Object[_size];
          for(int i=1;i<_size;++i)
              data1[i-1]=data[i];
            
          data=(T[])new Object[_size];
          data=data1;
          _size=_size-1;
        }
        if(index==_size-1){
            _size=_size-1;
            
        }
        else{
            T[] data1=(T[])new Object[_size];
            for(int i=0;i<_size;++i)
                 data1[i]=data[i];
             for(int p=0,k=0;k<_size;++p,++k){
                if(k==index)
                    k++;
                data[p]=data1[k];
             }	
              _size-=1;
            
        }   
    }
    /**
     * eleman eklemek için kullanılır
     * template element alır ve ekler
     * eğer aynı eleman varsa IllegalArgumentException() fırlatır
     * eğer yeterli yer yoksa yer ayırır ve ekleme işlemini yapar
     * @param element 
     */
    @Override
    public void insert(T element)
    {		
	boolean boo=true;
	for(int i=0; i<_size;++i){//elemanın içinde olup olmadığına bakar
            if(data[i]==element){
		boo=false;
		break;
            }	
	}
        if(boo==false)
            throw new IllegalArgumentException();
	if(boo==true)
	{	
            if(_size>=_cap)//eğer yeterli kapasite yoksa yeniden yer alma işlemi yapar
            {
		T[] data1;
		data1=(T[])new  Object[_cap+1];
		_cap =_cap+1;	
		for(int p=0;p<_size;++p)
                    data1[p]=data[p];
                data=(T[])new Object[_cap];
		for(int p=0;p<_size;++p)
                    data[p]=data1[p];	
            }          
            data[_size]=element;
            _size++;

            
 
  
	}	
    }
    /**
     * burada kullanıcıdan value alır
     * alınan value sette ise elemanı bulunduğu lokasyona göre
     * farklı bir işlemle çıkarılır
     * eğer eleman yoksa false return eder
     * @param element
     * @return 
     */
     public boolean erase(T element)
     {
	int c=0;
		
	for(int i=0; i<_size;++i)//elemanın içinde olup olmadığına bakar
            if(data[i]==element)
                c=1;
        if(c==0)//eğer eleman yoksa
            return false;
        if(_size==0)//çıkarılacak eleman yoksa
            return false;
        
	T[] data1=(T[])new  Object[_cap];
		
	for(int p=0;p<_size;++p)
            data1[p]=data[p];
        data =(T[])new  Object[_cap-1];
        _cap=_cap-1;
	for(int i=0; i<_size;++i){
            if(data1[i]==element){
		if(i==0)//çıkarılacak eleman en başta ise
                {
                    for(int p=0,k=1;k<_size;++p,++k)
                        data[p]=data1[k];
                    _size-=1;
                    return true;					
		}	
		if(i==_size-1){//çıkarılacak eleman en sonda ise			
			for(int p=0;p<_size-1;++p)
                            data[p]=data1[p];
			_size-=1;
                    
			
			return true;
		}
		else{//çıkarılacak eleman başta ve sonda değil ise
                    for(int p=0,k=0;k<_size;++p,++k){
			if(k==i)
                            k++;
                         data[p]=data1[k];
                    }	
                    _size-=1;
                    return true;
		}		
            }
	}
	return false;
    }
     /**
      *verilen set eğer boş değilse temizler
      * 
      */
    @Override
    public void clear()
    {
	if(_size>0)
	{
            _size=0;
            _cap=1;
            data=null;
            System.gc();
            data =(T[])new Object[_cap];
					
	}
    }
    /**
     * kullanıcıdan aldığı value eğer sette var ise true return eder
     * @param element
     * @return 
     */
    @Override
    public boolean count(T element)
    {
	for(int i=0; i<_size;++i)
            if(data[i]==element)
		return true;
	return false;
    }


    public class GTUIterator
    {
        private int num=0;
                
        public GTUIterator()
        {    
            this.num=0;
        }        
        /**
         *begin ve end için oluşturdum
         * begin için index i 0 a end için sona getirir
         * @param num
         */
        public GTUIterator(int num)
        {
            this.num=num;
          
        }       
        private void setNum(int n)
        {
            num=n;
        }
        private int getNum()
        {
            return this.num;
        }        
        /**
         *eğer iteratör indexi set içindeki elemandan küçük ise
         * set içinde ilerlememiz için bir nevi izin verir
         * @return
        */
	public boolean hasNext()
        {
            return _size>num;
               
        } 
        /**
         * eğer hasnext true ise num değerini bir artırır 
         * num-1 indexindeki datayı döndürür
         * hasnextkontrol edilmeden yapılırsa exception fırlatır
         * @return 
         */
	public T next()
        {
            if(hasNext()==true)
            {
                num++;
               
                return data[num-1];  
            }             
            throw new IllegalArgumentException("İllegal next element\n");
        }
        /**
         *eğer iteratör indexi set içindeki elemandan büyük ise
         * set içinde geriye doğru gelmemiz için bir nevi izin verir
         * @return
        */
        public boolean hasPrevious()
        {
            return num>=1;
                       
        }
        /**
         * eğer hasprev true ise num değerini bir azaltır 
         * num indexindeki datayı döndürür
         * hasnextkontrol edilmeden yapılırsa exception fırlatır
         * @return 
         */
	public T previous()
        {
            if(hasPrevious()==true)
            {
                num--;
                return data[num];  
            }
            throw new IllegalArgumentException("Illegal previous element\n");
        }      
    }

    /**
     *İlk elemanın bulunduğu indexi döndürür
     * it=begin(); den sonda it.next yazarsak
     * ilk elemanı return eder
     * @return
     */
    public  GTUIterator begin()
    {
        int index=0; 
        return new GTUIterator(0);
        
    }
     /**
     *İlk elemandan sonraki yerin bulunduğu indexi döndürür
     * it=end(); den sonda it.prev yazarsak
     * ilk elemanı return eder
     * @return
     */
    public GTUIterator end()
    {
        int index=_size;
        return new GTUIterator(this._size);
    }
    /**
     * eleman içinde ise it.next()
     * yazdığımızda o elemanı bize verir
     * yoksa bize end i döndürür
     * @param element
     * @return 
     */
    public GTUIterator find(T element)
    {
        int i=0;
        for(i=0; i<_size; ++i){
            if(data[i]==element)
            return new  GTUIterator(i);
        }
        
        return new GTUIterator(i);
    }
    /**
     * 2 interface objesini alır ver kesisimlerini döndürür
     * eğer kesisim yoksa ("\nThere is no intersection") çıktısı görülür
     * @param object
     * @return 
     */
     public GTUSetInt<T> intersection( GTUSetInt<T> object)
     {
         
         GTUSet set1;
         set1=(GTUSet) object;
         GTUSetInt set2=new GTUSet();
         for(int i=0;i<this.size();++i)
             for(int j=0;j<set1.size();++j)
                 if(set1.data[j]==this.data[i]){
                     set2.insert(this.data[i]);
                 }
            if(set2.size()>0)
                return set2;
            else
                System.out.println("\nThere is no intersection\n");
         return set2;
     }
     public String toString()
     {
         return String.format("SİZE İS %d\n"
                 + "----------\n"
                 + "MAX SİZE İS %d\n"
                 + "----------\n"
                 + "Is empty %b\n",this.size(),this.max_size(),this.empty());
     }
     /**
      * elemanları baştan sonra hasnext ve next is kullanarak yazdırmak için
      * @param it 
      */
     public void printNext(GTUIterator it)
     {
        it=begin();
        PrintStream PrintStream;
         while(it.hasNext())  
             PrintStream /*printf*/ = System.out.printf("\nelemnts--> %s\n",it.next());
        it=begin(); 
     }
     /**
      * elemanları sondan başa doğru hasprev ve prev is kullanarak yazdırmak için
      * @param it 
      */
     public void printPrev(GTUIterator it)
     {
        it=end();
        PrintStream PrintStream;
         while(it.hasPrevious())  
             PrintStream /*printf*/ = System.out.printf("\nelemnts--> %s\n",it.previous());
        it=begin(); 
     }
}
