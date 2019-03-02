
import javafx.util.Pair;


/**
 *
 * @author akncam
 * @param <K>
 * @param <V>
 */
public class GTUMap<K,V>  extends GTUSet< javafx.util.Pair<K,V>>
{
    /**
     * parametresiz const içinde base class ın const kullanılır
     *
     */
    public GTUMap()
    {
        super();
    }
    /**
     * kullanıcıdan alınan size a göre yer ayrılır
     * @param size 
     */
    public GTUMap(int size)
    {
        super(size);
    }
    /**
     *eper eleman yoksa true return eder
     * @return 
     */
    @Override
       public boolean empty()
    {
	return _size==0;	
    }
       /**
        * size ı return eder
        * @return 
        */
    @Override
    public int size() 
    {
	return _size;
    }	
    /**
     *kapasiteyi return eder
     * @return
     */
    @Override
    public int max_size()
    {
	return _cap;
    }

    /**
     * verilen k eğer map te ise onun value değerini döndürür
     * eğer içinde yok ise null döndürür
     * @param k
     * @return 
     */


    public  V at(K k)
     {
          
         for(int i=0;i<_size;++i){
            if(this.getter(i).getKey()==k){
                 return (V) this.getter(i).getValue();
             }
         }     
        
         return null;  
     }

    /**
     * find burada pair objesi alır eğer keyler birbirine eşitse
     * iteratör için index döndürür bizde it.next ile ulaşabiliriz
     * eğer yoksa end() return eder
     * @param object
     * @return 
     */
    public GTUIterator find(javafx.util.Pair<K,V> object)
    {
        GTUMap<K,V>.GTUIterator it;
        for(int i=0; i<_size; ++i){
            if(object.getKey()==this.getter(i).getKey()){
               return new GTUIterator(i);
            }
        }
        it=this.end();
        return it;
    }
     /**
     * 2 interface objesini alır ver kesisimlerini döndürür
     * eğer kesisim yoksa ("\nThere is no intersection") çıktısı görülür
     * @param object
     * @return 
     */
     public GTUSetInt<javafx.util.Pair<K,V> > intersection( GTUSetInt<javafx.util.Pair<K,V>> object)
     {
         
         GTUMap<K,V> set1;
         set1=(GTUMap<K,V>) object;
         GTUSetInt set2=new <javafx.util.Pair<K,V>[]> GTUMap();
         for(int i=0;i<this.size();++i)
             for(int j=0;j<set1.size();++j)
                 if((this.getter(j).getKey()==this.getter(i).getKey())&&(this.getter(j).getValue()==this.getter(i).getValue())){
                     set2.insert(this.getter(i));
                 }
            if(set2.size()>0)
                return set2;
            else
                System.out.println("\nThere is no intersection\n");     
            return set2;
     }
     /**
      * burada key ve value eğerlerini alır eğer eleman mapte ise exception fırlatır
      * eğer yoksa super class ın insertü elemanı ekler
      * @param key
      * @param value 
      */
     public void insert(K key, V value)
    {		
	boolean boo=true;
	for(int i=0; i<_size;++i){//elemanın içinde olup olmadığına bakar
            if(getter(i).getKey()==key&&getter(i).getValue()==value){
		boo=false;
		break;
            }	
	}
        if(boo==false)
            throw new IllegalArgumentException("The element is member of set.");
        javafx.util.Pair<K,V> insert;
        insert = new   javafx.util.Pair<>(key,value);
	super.insert(insert);

    }
     /**
      * burada erase pair alır keyleri kontrol eder eğer aynı key varsa setter ile elemanı çıkarır
      * eğer key yoksa false return eder
      * @param element
      * @return 
      */
      public boolean erase(javafx.util.Pair<K,V> element)
     {
	int c=0;
	boolean a;
        int i=0;
	for( i=0; i<_size;++i)//elemanın içinde olup olmadığına bakar
            if(getter(i).getKey()==element.getKey()){
                c=1;
                break;
            }    

        if(c==0)//eğer eleman yoksa
            return false;
        if(_size==0)//çıkarılacak eleman yoksa
            return false;
       int size=_size;
        
        setter(i);
       return true;

    }
}    
