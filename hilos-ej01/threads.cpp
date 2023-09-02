#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>


using namespace std;

void *funcionIncrementa(void *data){
	
	//Declaramos un puntero a la variable global
	int* punteroVariableGlobal = static_cast<int*>(data);
	
	cout << "\nThread1 instancia: " << *punteroVariableGlobal + 1<< endl;
	
	int numeroRandom = rand()%100 + 1;

	Sleep(numeroRandom/100);
	
	//Incrementar variable compartida
	*punteroVariableGlobal = *punteroVariableGlobal + 1;
	
	cout << "La variable compartida es: " << *punteroVariableGlobal << endl;
	
	return NULL;
}
	
void *funcionNormal(void *data){
	
	//Declaramos un puntero a la variable global
	int* punteroParametros = static_cast<int*>(data);
	
	cout << "\nThread2 instancia: " << punteroParametros[0]<< endl;
	
	int numeroRandom = rand()%100 + 1;
	
	Sleep(numeroRandom/100);
	
	cout << "La variable compartida es: " << punteroParametros[1]<<endl;
	
	return NULL;
	
}

int main(int argc, char *argv[]) {
	
	//INICIAR rand()
	srand(time(NULL));
	
	//Variable global
	int variableGlobal = 0;
	
	//Ingreso de valores de N y M
	cout << "Ingresa un numero para N" << endl;
	
	int opcionN = 0;
	cin >> opcionN;
	
	cout << "Ingresa un numero para M" << endl;
	
	int opcionM;
	cin >> opcionM;
	//---------------------------
	
	pthread_t* n_procesos = new pthread_t[opcionN];
	
	pthread_t* m_procesos = new pthread_t[opcionM];
	
	int parametros[2] = {0, 0};
	
	for (int i=0; i < opcionN; i++){
		pthread_t proceso;
		n_procesos[i] = proceso;
	
		pthread_create(&n_procesos[i], NULL, &funcionIncrementa, &variableGlobal); //No hace falta mandar el número de bucle
	
		pthread_join(n_procesos[i], NULL);
		
		parametros[1] = variableGlobal;
	}
	
	for (int j=0; j < opcionM; j++){
		pthread_t procesoM;
		m_procesos[j] = procesoM;
		
		parametros[0] = j+1;

		pthread_create(&m_procesos[j], NULL, &funcionNormal, &parametros);
		
		pthread_join(m_procesos[j], NULL);
	}
	
	return 0;
}

