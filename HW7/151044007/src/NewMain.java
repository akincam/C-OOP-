
import java.io.PrintStream;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author akncam
 */
public class NewMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
                     System.out.println("*********************Map için test**********************\n");
            System.out.println("----*****************Map için test*****************-----\n");
            System.out.println("--------*************Map için test*************---------\n");
            System.out.println("----*****************Map için test*****************-----\n");
            System.out.println("*********************Map için test**********************\n");

            GTUMap<Integer,Character> mp;
            mp= new GTUMap<>();
            GTUMap<Integer,Character>.GTUIterator mit;
            mit = mp.new GTUIterator();
            if(true==mp.empty()) 
                System.out.println("Set is empty");
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Size is-------->%d\n",mp.size());   
            System.out.println("\n--------------------------------------------------------");
            System.out.printf("Capacity is-------->%d\n",mp.max_size());
            System.out.println("\n------------------eleman ekliyorum----------------------");
            mp.insert(3,'a');
            mp.insert(5,'b');
            mp.insert(6,'k');
            mp.insert(7,'e');
            mp.insert(34,'h');
            mp.insert(55,'m');
        PrintStream PrintStream = System.out.printf("\n----At methodunu kullanıyorum |3|---> %s\n",mp.at(3)); /*printf*/
             PrintStream /*printf*/ = System.out.printf("\n----At methodunu kullanıyorum |7|---> %s\n",mp.at(7));
            mp.printNext(mit);
            System.out.println("-------------eleman çıkarıyorum---------------------------");
             javafx.util.Pair<Integer,Character> insert1;
             insert1 = new   javafx.util.Pair<>(34,'h');
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

              
    }
    
}
