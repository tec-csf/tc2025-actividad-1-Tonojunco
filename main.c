//
//  main7.c
//  Tarea Apuntadores
//
//  Antonio Junco de Haas
//  21/Agosto/2020
//


#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int cama;
	int disponible;
	int paginas;
	char * titulo;
	char * autor;
    
} libro;
void printCamas(libro *, libro *);
int camaDisponible(libro *, libro *);
int camaFinal(libro *, libro *);

int main(int argc, const char * argv[])
{
	printf("Bienvenido al software del hospital :\n");
	libro * biblioteca;
	libro * aux;
	//----------Variables a utilizar----------//
	int cantidad = 0; //Cantidad de camas habilitadas
	int personas = 0;//Cantidad de personas en el hospital
	int cama_dis=1;//Primera cama disponible -------------------------------------MAYBE FIX THIS
	int contador=0;//Contador para ver si se adregaron la cantidad correspondiente
	int main_menu=0;//Input de instruccion de usuario
	//________________________________________//


	//----------Crear biblioteca y final----------//
	biblioteca = (libro *) malloc(sizeof(libro) * cantidad);
	libro * final = biblioteca + cantidad;
	//____________________________________________//

	
	
	while(main_menu!=5){
		printf("Seleccion de menu principal: \n1. Agregar\n2. Quitar\n3. Mostrar Pacientes\n4. Mostrar Camas\n5. Salir\n");
		scanf("%d", &main_menu);
		switch(main_menu){
			case (1):
				printf("¿Cuántos pacientes quieres dar de alta? : ");
			//----------Recibir nuevos pacientes----------//
			int masPersonas=0;
			
			scanf("%d", &masPersonas);
			personas+=masPersonas;
			cantidad=personas;
			//____________________________________________//




			//----------Crear Nuevas Camas----------//
			while(cantidad%5!=0)
				cantidad++;
			printf("Total de cams creadas: %d\n",cantidad);
			//______________________________________//
			
			biblioteca = (libro *) realloc(biblioteca, sizeof(libro) * (cantidad));
			final = biblioteca + cantidad;
			int camaActual=1;
			for (aux = biblioteca; aux < final; ++aux) {
				if(contador<personas){
					if(aux->disponible==0){
			    			//printf("CREATED NEW PERSON \n");
						aux->titulo = (char * ) malloc(sizeof(char) * 25);

						//Asigna la primera cama disponible y escribe la siguiente
						cama_dis=camaDisponible(biblioteca,final);
						aux->cama = cama_dis;
						

						//La cama asingada no va a ser se convierte en ocupada
						aux->disponible = 1;
						
						printf("Entre el nombre de la persona: ");
						scanf("%s", aux->titulo);

						aux->autor = (char * ) malloc(sizeof(char) * 25);

						printf("Entre apellido de la persona: ");
						scanf("%s", aux->autor);

						printf("Entre el número telefonico: ");
						scanf("%d", &aux->paginas);
						contador++;
					}
				}
				//Camas extras adregadas
				else{
					//printf("CREATED AVAILABLE BED \n");
					aux->titulo = (char * ) malloc(sizeof(char) * 25);

					//Asigna la primera cama disponible y escribe la siguiente
					cama_dis=camaActual;//camaDisponible(biblioteca,final);
					aux->cama = cama_dis;

					//Las camas estan libres
					aux->disponible = 0;

					aux->autor = (char * ) malloc(sizeof(char) * 25);


				}
			camaActual++;
			}
			cama_dis=camaDisponible(biblioteca,final);
			break;
			case(2):
			printf("\n\n--- Selecciona cual cama quieres vaciar ---\n\n");
			printf("\n\n--- Listado de pacientes ---\nCama  Disponible  Nombre                          Apellido                         Telefono\n");
			for (aux = biblioteca; aux < final; ++aux) {
				printf("%6d \t %8d \t %25s \t %25s \t %8d \n",
				aux->cama,
				aux->disponible,
				aux->titulo,
				aux->autor,
				aux->paginas);
			}
			int quitar;
			scanf("%d", &quitar);
			for (aux = biblioteca; aux < final; ++aux) {
				if(aux->cama==quitar){
				aux->disponible=0;
				aux->titulo="";
				aux->autor="";
				aux->paginas=0;	
				}	
			}	
			break;

			case (3):
			printf("\n\n--- Listado de pacientes ---\nCama  Disponible  Nombre                          Apellido                         Telefono\n");
			for (aux = biblioteca; aux < final; ++aux) {
				printf("%6d \t %8d \t %25s \t %25s \t %8d \n",
				aux->cama,
				aux->disponible,
				aux->titulo,
				aux->autor,
				aux->paginas);
			}
			break;
			case(4):
			printCamas(biblioteca, final);
			break;
			case(5):
				printf("Cerrando el programa\n");
			break;
			default:
				printf("Input Incorrecto \n");
		}
	}
    /*
	// Mostrar los pacientes
	printf("\n\n--- Listado de pacientes ---\n\n");
	for (aux = biblioteca; aux < final; ++aux) {
		printf("%2d \t %1d \t %25s \t %25s \t %4d \n",
		aux->cama,
		aux->disponible,
		aux->titulo,
		aux->autor,
		aux->paginas);
	}*/
	//printCamas(biblioteca, final);
    
	// Liberar la memoria

	for (aux = biblioteca; aux < final; ++aux) {
		free(aux->titulo);
		free(aux->autor);
	}

	free(biblioteca);

	return 0;
	}

void printCamas(libro * biblioteca, libro * final){
	int ocupadas=0;
	int desocupadas=0;
	// Camas Libres
	printf("\n\n--- Listado todas las camas ---\n\n");
	for (libro * aux = biblioteca; aux < final; ++aux) {
		if(aux->disponible==0){
        		printf("%d Disponible\n",
			aux->cama);
			desocupadas++;
		}
			else{
			printf("%d NO Disponible\n",
			aux->cama);
			ocupadas++;
		}
	}
	printf("Camas disponibles: %d\n",desocupadas);
	printf("Camas ocupadas: %d\n\n\n",ocupadas);
}

int camaDisponible(libro * biblioteca, libro * final){
	int flag=0;
	int index=1;
	for (libro * aux = biblioteca; aux < final; ++aux) {
		if(aux->disponible==0&&flag==0){
        		flag=index;
			printf("La primera cama disponible es: %d\n", flag);
		}
		index++;
	}
	if(flag==0)
		printf("No hay camas disponibles\n");
	return flag;
}

int camaFinal(libro * biblioteca, libro * final){
	int index=1;
	for (libro * aux = biblioteca; aux < final; ++aux) {
		index++;
	}
	printf("La cama FINAL es: %d\n", index);
	return index;
}






