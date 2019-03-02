
/**
 *
 * GTUSetInt i interface olarak tanımladım
 * implementasyonunu daha sonra yapmak için
 * @author akncam
 * @param <T>
 */
public interface GTUSetInt<T> 
{   
    public boolean empty();		
    public int size();	
    public int max_size();		
    public void insert(T element);			
    public boolean erase(T element);			
    public void clear();			
    public boolean count(T element);
	

    public Object begin();
    public Object end();
    public Object find(T element);
    public GTUSetInt<T> intersection( GTUSetInt<T> object);    
}
