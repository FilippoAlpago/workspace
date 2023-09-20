public class Interferenze extends Thread {
    static final int MAX=1000000;           // iterazioni massime
    Contatore c;                            // Monitor passato dal main

    // costruttore, memorizza il monitor nel campo c
    Interferenze(Contatore cont) {
        c=cont;
    }
    //   i thread incrementano MAX volte il contatore
    //   NOTA: non possono fare c.count++ perche' e' privato! 
    public void run() {
        int i;
        for (i=0;i<MAX;i++)
            c.incrementa();     // questo metodo e' in MUTEX perche' synchronized
    }

    //   il main crea i thread, attende la terminazione e stampa il contatore 
    public static void main(String args[]) throws InterruptedException {
        int j=0;
        Thread t[] = new Thread[2];
        Contatore cont = new Contatore(); // crea un singolo monitor
        
        // crea i 2 thread e li esegue
        for(j=0;j<2;j++) {
            t[j] = new Interferenze(cont); // passa il monitor ai thread
            t[j].start();
        }

        // attende la terminazione
        for(j=0;j<2;j++) t[j].join();

        // stampa il contatore, il valore atteso ed esce
        System.out.println("FINITO " + cont.valore() + " mi aspettavo " + MAX*2);
    }
}

/*  questa classe implementa un Monitor in cui e' possibile incrementare il valore 
 *  di un contatore da diversi thread in mutua esclusione.
 *  provare a togliere il 'synchronized' dal metodo incrementa per osservare 
 *  le interferenze */
class Contatore {
    private int count=0;    // privato: no accessi diretti!

    // il metodo synchronized garantisce mutua esclusione sullo stesso oggetto
    synchronized void incrementa() {
        //oppure: synchronized(this) {count++;}
        count++;
    }

    // non serve sincronizzarlo visto che lo usiamo alla fine dal main: gli altri
    // thread sono gia' terminati (la join garantisce che il main e' l'unico 
    // thread in esecuzione) inoltre la lettura non crea mai interferenze
    int valore() {
        return(count);
    }
}
