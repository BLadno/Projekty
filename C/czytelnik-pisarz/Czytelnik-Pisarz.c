#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define MAX 128

char buf[MAX];
int plik,lbajt,k=10,w=2;
char* file;

pthread_mutex_t mojmuteks=PTHREAD_MUTEX_INITIALIZER;
void *Zapis(void *arg){
	int i;
	for (i=0;i<k;i++){
		pthread_mutex_lock(&mojmuteks);
		lbajt=k;
		buf[i]=(char)(i+65);
		plik = open(file,O_WRONLY);
		if(plik == -1) {
			perror("blad otwarcia pliku");
			exit(1);
		}
		if(write(plik,buf,lbajt)==-1){
			perror("blad zapisu pliku");
			exit(1);
		}
		printf("\nZapisuje plik (watek %d): ",pthread_self());
		sleep(1);
		if(close(plik == -1)){
			perror("blad zamkniecia pliku");
			exit(1);
		}
		fflush(stdout);
		pthread_mutex_unlock(&mojmuteks);
		sleep(1);
	}
	return NULL;
}
void *Odczyt(void *arg){
	int i;
	for (i=0;i<k;i++){
		pthread_mutex_lock(&mojmuteks);
		fflush(stdout);
		plik = open(file,O_RDONLY);
		if(plik == -1) {
			perror("blad otwarcia pliku");
			exit(1);
		}
		printf("\nOdczytuje plik(watek %d): ",pthread_self());
		sleep(1);
		while((lbajt = read(plik,buf,MAX))>0){
			printf("%s",buf);
		}
		if(close(plik == -1)){
			perror("blad zamkniecia pliku");
			exit(1);
		}
		pthread_mutex_unlock(&mojmuteks);
		sleep(1);
	}
	return NULL;
}
int main(int argc,char* argv[]){
	if(argc<2){
		printf("brakuje argumentow <nazwa pliku> <liczba powtorzen> <liczba watkow>\n");
		exit(1);
	}
	if(argc>2){
		if(atoi(argv[2])<MAX){
			k=atoi(argv[2]);
		}
	}
	if(argc>3){
		if(atoi(argv[3])<9){
			w=atoi(argv[3]);
		}
		w=atoi(argv[3]);
	}
	pthread_t watek[8];
	int i;
	file=argv[1];
	plik=creat(file,0640);
	
	if(pthread_create(&watek[0],NULL,Zapis,NULL)){
		printf("błąd przy tworzeniu wątku\n");
		abort();
	}
	for (i=1;i<w;i++){
		if(pthread_create(&watek[i],NULL,Odczyt,NULL)){
			printf("błąd przy tworzeniu wątku\n");
			abort();
		}
	}

	for (i=0;i<w;i++){
		if(pthread_join(watek[i],NULL)){
			printf("bład w kończeniu wątku %d\n",i);
			exit(0);
		}
	}
	printf("\nProgram zakonczyl prace\n");
	exit(0);
}