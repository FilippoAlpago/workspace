public class CreaTantiThread extends Thread {
    static final int NTHREAD=5;     // numero di thread da creare
    final int index;                // indice del thread appena creato

    // costruttore: memorizza l'indice del thread 
    CreaTantiThread(int i) {
        index = i;
    }
    
    // codice da eseguire allo startup del thread 
    public void run()  {
        try {
            // NOTA: se l'interruzione arriva prima della sleep viene
            // bufferizzata!
            sleep(2000);  // dorme per 2 secondi
        } catch(InterruptedException e) {
            System.out.println("["+getName()+"]"+" Ah mi hanno interrotto!!");
            return; 
        }
        // saluta ed esce
        System.out.println("Saluti dal thread " + getName());
    }

    /* main: crea i NTHREAD thread ne interrompe alcuni e attende la
       terminazione. NOTA: con join devo gestire InterruptedException,
       ma nessuno interrompera' mai le join di questo main quindi la 
       ignoriamo */
    public static void main(String args[]) throws InterruptedException {
        int i;
        Thread t[] = new Thread[NTHREAD];
        
        // crea 5 thread e li esegue
        for(i=0;i<NTHREAD;i++) {
            t[i] = new CreaTantiThread(i);
            t[i].start();
        }
        
        // interrompe il terzo thread
        t[3].interrupt();
        
        // attende la terminazione dei thread
        for(i=0;i<NTHREAD;i++) {
            t[i].join();
           }
        
        // saluta ed esce
        System.out.println("Saluti dal thread " + Thread.currentThread().getName());
    }
}