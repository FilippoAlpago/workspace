public class thread{
    static final int NTHREAD=5;
    public static class CreateThread extends Thread
    {
        
        final int index;

        CreateThread(int i)
        {
            this.index=i;
        }

        public void run()
        {
            try {
                System.out.println("thread "+this.getName()+"va a nanna");
                sleep(2000);
            } catch (InterruptedException e) {
                System.out.println("["+getName()+"]"+"AH mi hanno interrotto");
                
            }
            System.out.println("saluti dal thread"+this.getName());
        }
    }

    public static void main(String args[]) throws InterruptedException
    {
        int i;
        Thread t[]=new Thread[NTHREAD];
        for( i=0;i<NTHREAD;i++)
        {
            t[i]=new CreateThread(i);
            t[i].start();
        }
        t[3].interrupt();
        for(i=0;i<NTHREAD;i++)
        {
            t[i].join();
        }
        System.out.println("saluti dal thread "+Thread.currentThread().getName());
    }
}