
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import static java.lang.System.exit;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


/**
 *
 * @author akncam
 */
public class gui extends ConnectFour
{
    private int size,mouse=0;
    private JPanel buttonpanel[];
    private JButton button[];
    
    private JLabel label;
    private final Font titlefont =new Font("TimesRoman",Font.LAYOUT_NO_LIMIT_CONTEXT,88);
    private final Font normalfont =new Font("monospaced",Font.LAYOUT_NO_LIMIT_CONTEXT,30);
    private final Font font1 =new Font("TimesRoman",Font.LAYOUT_NO_LIMIT_CONTEXT,30); 
    private final ImageIcon square=new ImageIcon("kare.png");
    private final ImageIcon square1=new ImageIcon("a.png");
    private final ImageIcon square2=new ImageIcon("aass.png");
    private final ImageIcon square3=new ImageIcon("aaa4.png");
    /**
     * bu constructor jFrame i initialize ediyor
     */
    
    public gui()
    {
        window=new JFrame(); 
    }        
    /**
     * burada verilen game areya ya göre oyun analını initialize ediyorum
     * for döngüsünde sabit bir alana alanı fotoğrafla orantılı olarak artırıp
     * gameboard u oluşturuyorum
     */
    
    private void createGameBoard()
    {
        window.setLocation(700, 200);
        window.setSize(87*(size), 82*(size));
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setBackground(Color.white);
        window.setResizable(false);
        window.setVisible(true);
        window.setLayout(new GridLayout(0,size));
        window.setTitle("ConnectFour");
        window.getContentPane();
 
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                JLabel deneme=new JLabel();
                deneme.setIcon(square);
                deneme.setLocation(87*j, 82*i);
                deneme.setSize(87,82);
                window.add(deneme);    
            }
        }  
    }
    /**
     * burada kullanıcından oyun tipini seçmesini sağlıyorum
     * burada istenilen oyun şeklini pvpOrpvc ye assign ediyorum
     * 
     */
    private void pVpOrpVc()
    {
        String[] choice = { "Player vs Player","Player vs Computer" };
           
        String input= (String) JOptionPane.showInputDialog(null, "Choose now...",null,
                          JOptionPane.QUESTION_MESSAGE,null,choice,choice[1]);
        if(input == null ? choice[0] == null : input.equals(choice[0]))
           this.pvpOrpvc='p';
        else
           this.pvpOrpvc='c';
 
    } 
    /**
     * bu fonksiyonda mouse ile tıklanan yere eleman eklenmesini sağlıyorum
     * mouse pressed fonksiyonunu kullandım
     */
    private void MouseActions()
    {
         char[] letter1={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
               
                window.addMouseListener(new MouseAdapter(){
                     public void mousePressed(MouseEvent e)
                     {
                        boolean check=false;
                        int x=e.getX();
                        int y=e.getY();
                        mouse=0;
                        for(int i=0;84*i<x;i++)
                            mouse=i;
                        if(pvpOrpvc=='p'&&symbol=='X'){//kullanıcıya karşı oynanmak istendiğinde
                            if(setPosition(letter1[mouse])){//eğer mouse ile tıklanan yerde boş alan var ise ekleme yapar yoksa hiçbirşey yapmaz.
                                check=play(letter1[mouse]);//oyunun bitip bitmediğini kontrol eder ve true ya da false değerini check tutar
                                displayGame();
                                addCircle(symbol);
                                symbol='O';
                                if(check)//eğer oyun bitmişse kullanıcıya tekrar oynamak isteyip istemediğini ya da çıkmak isteyip istemedğini sorar
                                    restartGame();
                            }
                        }
                        else if(pvpOrpvc=='p'&&symbol=='O'){//kullanıcıya karşı oynanmak istendiğinde diğer kullanıcı için
                            if(setPosition(letter1[mouse])){
                                check=play(letter1[mouse]);
                                displayGame();
                                addCircle(symbol);
                                symbol='X';
                                if(check)
                                   restartGame();
                            }
                        }
                        else if(pvpOrpvc=='c'){//bilgisayara karşı oynamak istediğinde kullanıcı her hamle yaptığında bilgisayarda hamle yapar
                            if(setPosition(letter1[mouse])){
                                symbol='X';
                                check=play(letter1[mouse]);
                                displayGame();
                                addCircle(symbol);     
                                if(check)
                                    restartGame();
                                symbol='O';
                                check=play();
                                displayGame();
                                 symbol='O';
                                addCircle(symbol);
                                int control=0;
                                for(int j=0;j<row;++j){//oyun alanının dolu olupolmadığını kontrol eder
                                    for(int i=0; i<column;++i)
                                       if(gameBoard[j][i].getCell()!='*'){
                                           ++control;		
                                        }		
                                }
                                if(size*size==control)
                                    gameBordFull();
                                if(check)
                                   restartGame();   
                            }     
                        }    
                        
                     }        
                });

    }
    /**
     * oyun bittiğinde yeniden başlatmak için
     */
    private void restartGame()
    {
        if(symbol=='X'&&pvpOrpvc=='p')
            symbol='O';
        else if(symbol=='O'&&pvpOrpvc=='p')
            symbol='X';

        String[] choice = {"Restart","Exit"};
        String input= (String) JOptionPane.showInputDialog(null, "USER "
                        + symbol+
                       "  WİN THE GAME",null,
        JOptionPane.CLOSED_OPTION,null,choice,choice[0]);
        if("Restart".equals(input)){//eğer yeniden başlatıcaksa window JFrame i yeniden initialize eder
            symbol='X';
            window.setVisible(false);
            window=new JFrame();
            this.playGame();
            
        }
        else
            exit(1);            
    }
    /**
     * kullanıcında 4 ile 15 arasında oyun alanı seçmesi için
     */
     private void takeField()
     {
           Integer[] field = { 4,5,6,7,8,9,10,11,12,13,14,15 };
           
           Integer input= (Integer) JOptionPane.showInputDialog(null, "Choose GameSize...",null,
                          JOptionPane.QUESTION_MESSAGE,null,field,field[0]);
          
           size=input;
           super.row=size;
           super.column=size;
    }
    /**
     * oyun alanına kullanıcıların sahip oldukları renkleri frame ekler.
     * @param sy 
     */ 
    private void addCircle(char sy)
    {
        JLabel deneme1;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(sy=='X')
                    deneme1=new JLabel(square2);
                else
                    deneme1=new JLabel(square3); 
                if(gameBoard[i][j].getCell()!='*')
                    window.add(deneme1);
                deneme1.setLocation(87*j, 82*i);
                deneme1.setSize(85,82);
            }
        }
    }
    /**
     * oyun alanı dolduğunda yeniden oynayıp oynamak istemediini veya çıkıp çıkmak istemediğnii sorar
     */
    private void gameBordFull()
    {

        String[] choice = {"Restart","Exit"};
        String input= (String) JOptionPane.showInputDialog(null, "GameArea is Full",null,
        JOptionPane.CLOSED_OPTION,null,choice,choice[0]);
        if("Restart".equals(input)){
            symbol='X';
            window.setVisible(false);
            window=new JFrame();
            this.playGame();
        }
        else
            exit(1);            
     }
    /**
     * oyunu initialize eder ve oynanmasını sağlar
     * kullanıcı tipini,oyun alanını,JFreame e resim ekleme işini halleder
     *  pVpOrpVc();
     *  takeField();
     *  super.playGame();
     *  createGameBoard();
     *  MouseActions();
     * yukarıdaki private fonksiyonları kullanır
     * @return 
     */
    public boolean playGame()
    {
        pVpOrpVc();
        takeField();
        super.playGame();
        createGameBoard();
        MouseActions();
        return false;
    }
    
    

}
