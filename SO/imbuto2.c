/*
 * Corso di Sistemi Operativi 2020
 * Seconda verifica: semafori
 *
 * Author: Riccardo Focardi
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

extern void inizializza_sem(int dim);
extern void distruggi_sem();
extern void entra_imbuto();
extern void esci_imbuto();

#define X 40		// dimensione griglia X
#define Y (X-2)/2	// dimensione griglia Y
#define N 50		 // massimo di palline nell'imbuto
#define SLEEP_REFRESH 100000	// temporizzazione refresh

#ifdef STRESSTEST		// stresstest tante palline 0 sleep!
#define SLEEP_BALL 0 	// temporizzzione palline
#define N_BALLS 1000    // totale thread pallina
#else
#define SLEEP_BALL 100000 	// temporizzzione palline
#define N_BALLS 300   		// totale thread pallina
#endif

char table[X][Y];	// griglia
sem_t mutex_table[X][Y],mymutex; // semafori ad uso interno
int n_balls=0; 		// numero di palline nell'imbuto in un certo istante
int n_balls_tot=0;	// numero di palline totali che sono entrate
int goingup=1; // se il numero sale o scende

// uscita in caso di errore
void die(char * s, int e) {
    printf("%s [%i]\n",s,e);
    exit(1);
}

// Stampa la griglia sullo schermo
void stampa_griglia() {
	int i,j;

	printf("\e[1;1H\e[2J"); // cancella
	for (i=0;i<Y;i++) {
		for (j=0;j<X;j++) {
			printf("%c",table[j][i]); // stampa l'elemento j,i
		}
		printf("\n");
	}
	// Dati sulle palline
	printf("\nPalline nell'imbuto: %d/%d (processate: %d/%d)\n",n_balls,N,n_balls_tot,N_BALLS);

}

// Inizializza la griglia con la forma di un imbuto
void init_imbuto() {
	int i,j;

	for (i=0;i<Y;i++) {
		for (j=0;j<X;j++) {
			// inizializza il mutex per lo spostamento sulla griglia
			sem_init(&mutex_table[j][i],0,1); 
			if (i<Y-1) {
				if (i==j) {
					table[j][i]='\\';
				} else if (X-i-2==j) {
					table[j][i]='/';
				} else {
					table[j][i]=' ';
				}
			} else {
				if (j==X/2 || j==X/2-2)
					table[j][i]='|';
				else
					table[j][i]=' ';
			}
		}
	}
}

// Random da 0 a max
long random_at_most(long max) {
  unsigned long
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  while (num_rand - defect <= (unsigned long)(x = random()));
  return x/bin_size;
}

// Thread pallina
void * pallina(void * id) {
	int x,y=0,nx,ny,dx;

	x = random_at_most(X-4)+1;

	entra_imbuto(); // Attende di entrare nell'imbuto

	// Statistiche di debug
	sem_wait(&mymutex);
	if (!goingup) {
		stampa_griglia();
		printf("[ERRORE] Le palline non dovrebbero entrare ma uscire\n");
		exit(1);
	}
	n_balls++; 		// pallina entra
	n_balls_tot++; 	// pallina entra
	if (n_balls==N) {
		goingup = 0; // ora di scendere!
	}
	sem_post(&mymutex);

	// Entra nell'imbuto
	sem_wait(&mutex_table[x][y]);
	table[x][y] = 'O'; 

	// Finché non arriva in fondo:
	while(y<Y) {
		usleep(SLEEP_BALL+random_at_most(SLEEP_BALL/100));
		ny = y+1;
		nx = x;
		dx = x+(x<X/2-1 ? 1 : (x==X/2-1 ? 0 : -1)); // spostamento "naturale" verso il centro
		if (table[x][ny] == '\\' || table[x][ny] == '/' || table[x][ny] == '|') {nx = dx; // si sposta verso il centro 
			// se occupato resta alla stessa altezza
			if (table[dx][ny] != ' ') ny=y;
		}
		else if (table[x][ny] == 'O') { // se occupato da altra pallina
			if (table[dx][ny] == ' ') nx = dx; // si sposta verso il centro
			else if (table[dx][y] == ' ') {    // resta alla stessa altezza
				nx = dx; ny = y;
			}
		} 

		// condizioni che non devono mai avverarsi:
		if (nx<ny) {
			printf("out of bound! (non deve succedere) %d %d -> %d %d (%d %d)\n",x,y,nx,ny,X,Y);
			exit(1);
		}
		if (nx > X || ny > Y || nx < 0 || ny < 0) {
			printf("overflow (non deve succedere) %d %d\n",nx,ny);
			exit(1);
		}

		// Se ancora sulla griglia occupa la nuova posizione
		if(ny<Y) {
			sem_wait(&mutex_table[nx][ny]);
			table[nx][ny] = 'O';
		}
		// Libera la vecchia posizione
		table[x][y] = ' ';
		sem_post(&mutex_table[x][y]);

		x=nx;y=ny;
	}

	// Statistiche di debug
	sem_wait(&mymutex);
	if (SLEEP_BALL >= 100000 && goingup) {
		stampa_griglia();
		printf("[ERRORE] Le palline non dovrebbero uscire ma entrare\n");
		exit(1);
	}
	n_balls--; // pallina esce
	if (n_balls==0) {
		goingup = 1; // e' ora di entrare!
	}
	sem_post(&mymutex);
	esci_imbuto();

	return NULL;
}

// Thread separato che fa il refresh della griglia e controlla che non 
// ci siano troppe palline nell'imbuto
void * refresh(void * id) {
	while(1) {
		sem_wait(&mymutex);
		stampa_griglia();
		if (n_balls > N) {
			printf("[ERRORE] Ci sono %d palline nell'imbuto. Dovrebbero essere al massimo %d\n",n_balls,N);
			exit(1);
		}
		sem_post(&mymutex);

		usleep(SLEEP_REFRESH);
	}
}

int main() {
    pthread_t tid[N_BALLS+1];
    int err,i;
    int n_palline=0;
    
    inizializza_sem(N); // inizializza i semafori

    sem_init(&mymutex,0,1); // mutex per debug

	srandom(time(NULL));

	init_imbuto(); // inizializza l'imbuto
	
	// Crea N_BALLS thread "pallina"
	for (i=0;i<N_BALLS;i++) {
		if((err=pthread_create(&tid[i],NULL,pallina,NULL))) {
			die("errore create",err);
		}
	}
	// Crea il thread "refresh"
	if((err=pthread_create(&tid[i],NULL,refresh,NULL))) {
		die("errore create",err);
	}	

	// Attende i thread pallina
	for (i=0;i<N_BALLS;i++) {
		if((err=pthread_join(tid[i],NULL))) {
			die("errore join",err);
		}
	}

	// Esce
	stampa_griglia();
	distruggi_sem();
	printf("Tutte le palline sono transitate!\n");
	exit(0);

}