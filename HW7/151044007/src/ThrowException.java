
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
public class ThrowException {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        PrintStream PrintStream;  
            GTUSet<Character> set1;
            set1 = new GTUSet<>();
            try
            {
                GTUSet<Character>.GTUIterator iter;
                iter = set1.new GTUIterator();
                if(true==set1.empty()) 
                    System.out.println("Set is empty");
                System.out.println("\n--------------------------------------------------------");
                System.out.printf("Size is-------->%d\n",set1.size());   
                System.out.println("\n--------------------------------------------------------");
                System.out.printf("Capacity is-------->%d\n",set1.max_size());
                System.out.println("\n------------------eleman ekliyorum----------------------");
                set1.insert('a');set1.insert('d');set1.insert('f');set1.insert('g');set1.insert('i');set1.insert('n');
                set1.printNext(iter);
                System.out.println("-------------eleman çıkarıyorum---------------------------");
                set1.erase('z');set1.erase('a');set1.erase('f');
                set1.printNext(iter);
                System.out.println("\n------elemanları previous ile yeniden yazdırıyorum-------");
                set1.printPrev(iter);
                System.out.println("\n---------------------------------------------------------");
                 if(true==set1.empty()) 
                    System.out.println("\nSet is empty");
                 else
                    System.out.println("\nSet isn't empty"); 
                System.out.println("\n-------------------------p elemanını arıyorum-----------------------");

                if(set1.count('p'))
                    System.out.print("\n Aranan eleman burada\n");
                else
                   System.out.print("\n Aranan eleman burada değil\n"); 

                   System.out.println("\n----------------------aynı elemanı insert ediyorum---------------"); 
                   set1.insert('d');
            }
            catch(IllegalArgumentException e)
            {
              System.err.println("\n----------aynı elemanı eklediniz--------------"); 
            }

    }
    
}
