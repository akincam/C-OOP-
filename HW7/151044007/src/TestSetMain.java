
import java.io.PrintStream;


/**
 *
 * @author akncam
 */
public class TestSetMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
         PrintStream PrintStream;  
            GTUSet<Integer> set1;
            set1 = new GTUSet<>();

            GTUSet<Integer>.GTUIterator iter;
            iter = set1.new GTUIterator();
            if(true==set1.empty()) 
                System.out.println("Set is empty");
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Size is-------->%d\n",set1.size());   
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",set1.max_size());
            System.out.println("\n------------------eleman ekliyorum----------------------");
            set1.insert(10);set1.insert(20);set1.insert(30);set1.insert(40);set1.insert(55);set1.insert(64);
            set1.printNext(iter);
            System.out.println("-------------eleman çıkarıyorum---------------------------");
            set1.erase(10);set1.erase(30);set1.erase(2320);
            set1.printNext(iter);
            System.out.println("\n------elemanları previous ile yeniden yazdırıyorum-------");
            set1.printPrev(iter);
            System.out.println("\n---------------------------------------------------------");
             if(true==set1.empty()) 
                System.out.println("\nSet is empty");
             else
                System.out.println("\nSet isn't empty"); 
            System.out.println("\n---------------------------------------------------------");
            
            if(set1.count(64))
                System.out.print("\n Aranan eleman burada\n");
            else
               System.out.print("\n Aranan eleman burada değil\n"); 
            System.out.printf("Size is-------->%d\n",set1.size());   
            System.out.println("\n---------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",set1.max_size());

            System.out.println("\n-------------- setInt oluşturdum eleman ekledim----------");      
            GTUSetInt<Integer> set2;
            set2 = new GTUSet<>();

            set2.insert(40);
            set2.insert(15);
            set2.insert(24);
            
            System.out.println("\n-------------- 40/15/24 ekledim------------------------\n");
            System.out.println("\n------------- setInt oluşturdum yeniden eleman ekledim---");   
            GTUSetInt<Integer> set6;
            set6= new GTUSet<>();
            set6.insert(40);
            set6.insert(15);
            System.out.println("\n-------------- 40/15 ekledim---------------------------\n");
            GTUSetInt<Integer> set3;

            System.out.println("\n---------Intersection yaptım --------------------------\n");
            set3= set2.intersection(set6);

            PrintStream = System.out.printf("Intersection size is--> %d\n",set3.size()); /*printf*/

            GTUSet<Integer> set8=new GTUSet<>();
            set8=(GTUSet<Integer>) set3;
             System.out.println("--------------------------------------------------------\n");
            GTUSet<Integer>.GTUIterator iter1;
            iter1 = set8.new GTUIterator();
            set8.printPrev(iter1);

            System.out.println("********************************************************\n");
            System.out.println("----***********************************************-----\n");
            System.out.println("--------***************************************---------\n");
            System.out.println("----***********************************************-----\n");
            System.out.println("********************************************************\n");

            GTUSet<String> st1;
            st1 = new GTUSet<>();

            GTUSet<String>.GTUIterator it;
            it = st1.new GTUIterator();
            if(true==st1.empty()) 
                System.out.println("Set is empty");
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Size is-------->%d\n",st1.size());   
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",st1.max_size());
            System.out.println("\n------------------eleman ekliyorum----------------------");
           
            st1.insert("akin");st1.insert("altun");st1.insert("ebru");st1.insert("hidayet");st1.insert("kangal");st1.insert("sivas");
           
            st1.printNext(it);
            System.out.println("-------------eleman çıkarıyorum---------------------------");
            st1.erase("akin");st1.erase("ebru");st1.erase("abc");
            st1.printNext(it);
            
            System.out.println("\n------elemanları previous ile yeniden yazdırıyorum-------");
            st1.printPrev(it);
            System.out.println("\n---------------------------------------------------------");
             if(true==st1.empty()) 
                System.out.println("\nSet is empty");
             else
                System.out.println("\nSet isn't empty"); 
            System.out.println("\n---------------------------------------------------------");
            System.out.printf("Size is-------->%d\n",st1.size());   
            System.out.println("\n---------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",st1.max_size());

            System.out.println("\n-------------- setInt oluşturdum eleman ekledim----------");      
            GTUSet<String> st2;
            st2 = new GTUSet<>();

            st2.insert("bardak");
            st2.insert("klavye");
            st2.insert("laptop");   
            System.out.println("\n------------- setInt oluşturdum yeniden eleman ekledim---");   
            GTUSetInt<String> st6;
            st6= new GTUSet<>();
            st6.insert("aaa");
            st6.insert("bbb");
            GTUSetInt<String> st3;

            System.out.println("\n---------Intersection yaptım --------------------------\n");
            st3= st2.intersection(st6);

            PrintStream = System.out.printf("Intersection size is--> %d\n",st3.size()); /*printf*/

            GTUSet<String> st8=new GTUSet<String>();
            st8=(GTUSet<String>) st3;
             System.out.println("--------------------------------------------------------\n");
            GTUSet<String>.GTUIterator it11;
            it11= st8.new GTUIterator();
            st8.printNext(it11);
            System.out.println("---------find yapıyorum----sivas ı arıyorum----------------\n");
            it=st1.find("sivas");
            if(it!=st1.end())
                PrintStream /*printf*/ = System.out.printf("\nfinding element is--> %s\n",it.next());

            System.out.println("*********************Map için test**********************\n");
            System.out.println("----*****************Map için test*****************-----\n");
            System.out.println("--------*************Map için test*************---------\n");
            System.out.println("----*****************Map için test*****************-----\n");
            System.out.println("*********************Map için test**********************\n");

            GTUMap<String,Integer> mp;
            mp= new GTUMap<>();
            GTUMap<String,Integer>.GTUIterator mit;
            mit = mp.new GTUIterator();
            if(true==mp.empty()) 
                System.out.println("Set is empty");
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Size is-------->%d\n",mp.size());   
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",mp.max_size());
            System.out.println("\n------------------eleman ekliyorum----------------------");
            mp.insert("akin",3);
            mp.insert("altun",5);
            mp.insert("ebru",6);
            mp.insert("hidayet",7);
            mp.insert("kangal",22);
            mp.insert("sivas",34);
            PrintStream /*printf*/ = System.out.printf("\n----At methodunu kullanıyorum |akin|---> %s\n",mp.at("akin"));
             PrintStream /*printf*/ = System.out.printf("\n----At methodunu kullanıyorum |ali|---> %s\n",mp.at("ali"));
            mp.printNext(mit);
            System.out.println("-------------eleman çıkarıyorum---------------------------");
             javafx.util.Pair<String,Integer> insert1;
             insert1 = new   javafx.util.Pair<>("hidayet",7);
            mp.erase(insert1);
            mp.printNext(mit);
            System.out.println("\n------elemanları previous ile yeniden yazdırıyorum-------");
            mp.printPrev(mit);
            System.out.println("\n---------------------------------------------------------");
             if(true==mp.empty()) 
                System.out.println("\nSet is empty");
             else
                System.out.println("\nSet isn't empty"); 
            System.out.println("\n---------------------------------------------------------");
            System.out.printf("Size is-------->%d\n",mp.size());   
            System.out.println("\n---------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",mp.max_size());

            System.out.println("\n-------------- setInt oluşturdum eleman ekledim----------");      
            GTUSetInt<javafx.util.Pair<String,String>> mp2;
            mp2 = new GTUMap<>();
            
           javafx.util.Pair<String,String> insert;
             insert = new   javafx.util.Pair<>("elma","armut");
             
              javafx.util.Pair<String,String> insert2;
             insert2 = new   javafx.util.Pair<>("kivi","nar");
             
              javafx.util.Pair<String,String> insert3;
             insert3 = new   javafx.util.Pair<>("greyfurt","name");
             mp2.insert(insert);
             mp2.insert(insert2);
             mp2.insert(insert3);
            System.out.println("\n------------- setInt oluşturdum yeniden eleman ekledim---");   
           GTUSetInt<javafx.util.Pair<String,String>> mp3;
            mp3= new GTUMap<>();
            mp3.insert(insert);
            mp3.insert(insert2);
            
            GTUSetInt<javafx.util.Pair<String,String>> mp6;

            System.out.println("\n---------Intersection yaptım --------------------------\n");
            mp6= mp2.intersection(mp3);

            PrintStream = System.out.printf("Intersection size is--> %d\n",mp6.size()); /*printf*/

             GTUMap<String,String> m;
              m= new GTUMap<String,String>();
            m=( GTUMap<String,String>) mp6;
             System.out.println("--------------------------------------------------------\n");
             GTUMap<String,String>.GTUIterator it1;
            it1 = m.new GTUIterator();
            
             GTUMap<String,String>.GTUIterator it2;
            it2 = m.new GTUIterator();
            
            m.printNext(it2);
            System.out.println("\n---------find yapıyorum----------------------\n");
           
            GTUMap<String,Integer>.GTUIterator mit2;
            mit2 = mp.new GTUIterator();
            
             javafx.util.Pair<String,Integer> insert4;
             insert4 = new   javafx.util.Pair<>("ebru",6);
            
               mit=mp.find(insert4);
             if(mit!=mp.end())
                 PrintStream /*printf*/ = System.out.printf("\nfinding element is--> %s\n",mit.next());
              //System.out.println("\n---------find yapıyorum----------------------\n");
              
        
    
    } 
}
