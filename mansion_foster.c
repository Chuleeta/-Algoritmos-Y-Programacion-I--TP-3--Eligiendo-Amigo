#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#define MAX_NOMBRE 50
#define MAX_COLOR 50
#define MAX_VIRTUDES 10
#define MAX_DEFECTOS 10
#define MAX_DESCRIPCION 200

const char IGUAL ='=';
const char MENOR = '<';


typedef struct aspecto {
	char descripcion[MAX_DESCRIPCION ];
} aspecto_t;


typedef struct amigo{
	char nombre[MAX_NOMBRE ];
	char color[MAX_COLOR ];
	int altura;
	aspecto_t virtudes[MAX_VIRTUDES ];
	int tope_virtudes;
	aspecto_t defectos[MAX_DEFECTOS ];
	int tope_defectos;
	bool esta_en_mansion;
} amigo_t;


//Pre condiciones: Reccibe la ruta del archivo binario en un sting que debe ser menor a MAX_NOMBRE.
//Post condiciones: Devuelve por terminar los nombres de todos los amigos que esten en la mansion.
void listar(char archivo_binario_mansion[MAX_NOMBRE]){
	FILE* amigos_mansion = fopen(archivo_binario_mansion, "r");

	if (amigos_mansion == NULL){
		printf("error al abrir archivo .DAT\n");
		return;
	}

	amigo_t amigo;
	fread(&amigo, sizeof(amigo_t), 1, amigos_mansion);
	
	while(!feof(amigos_mansion)){
		if(amigo.esta_en_mansion == true){
			printf("%s\n", amigo.nombre);
		}
		fread(&amigo, sizeof(amigo_t), 1, amigos_mansion);
	}

	fclose(amigos_mansion);
}


//Pre condiciones: Recibe amigo_disponible y color que debe tener una cantidad de caracteres menor a MAX_COLOR.
//Post condiciones: Verifica si amigo_disponible.color sea igual al color dado.
bool tiene_color_pedido(amigo_t amigo_disponible, char color[MAX_COLOR]){
	if (strcmp(amigo_disponible.color, color) == 0){
		return true;
	}
	return false;
}


//Pre condiciones: Recibe amigo_disponible, referencia_altura que puede ser '=' o '<' y la altura.
//Post condiciones: En el caso de referencia_altura ser: 
//								'=' la altura de amigo_disponible debe ser igual a la altura dada
//								'<' la altura de amigo_disponible debe ser menor a la altura dada
//					si referencia_altura no es ninguno de estos entonces chequea que la altura de
//					amigo_disponible sea mayor a la dada.
bool tiene_altura_pedida(amigo_t amigo_disponible, char referencia_altura, int altura){
	if (referencia_altura == IGUAL){
		if (amigo_disponible.altura == altura){
			return true;
		}
	}else if (referencia_altura == MENOR){
		if (amigo_disponible.altura < altura){
			return true;
		}
	}else{
		if (amigo_disponible.altura > altura){
			return true;
		}
	}
	return false;
}


//Pre condiciones: Recibe amigo_disponible y virtud que debe tener una cantidad de caracteres menos a MAX_VIRTUD.
//Post condiciones: Chequea si alguna virtud del array de virtudes del amigo_disponible sea igual a la virtud dada.
bool tiene_virtud_pedida(amigo_t amigo_disponible, char virtud[MAX_DESCRIPCION]){
	for (int i = 0; i < amigo_disponible.tope_virtudes; i++){
		if (strcmp(amigo_disponible.virtudes[i].descripcion, virtud) == 0){
			return true;
		}
	}
	return false;	
}


//Pre condiciones: Recibe amigo_disponible y defecto que debe tener una cantidad de caracteres menos a MAX_DEFECTO.
//Post condiciones: Chequea que ningun defecto del array de defectos del amigo_disponible sea igual al defeto dado.
bool no_tiene_defecto_pedido(amigo_t amigo_disponible, char defecto[MAX_DESCRIPCION]){
	for (int i = 0; i < amigo_disponible.tope_defectos; i++){
		if (strcmp(amigo_disponible.defectos[i].descripcion, defecto) == 0){
			return false;
		}
	}
	return true;	
}


//Pre condiciones: Recibe amigo disponible y todos los valores impuestos por el archivo txt
//				   Entre estos estan: color, virtud y defecto que deben tener una cantidad 
//				   de caracteres menor a MAX_COLOR, MAX_VIRTUD y MAX_DEFECTO respectivamente.
//				   Luego recibe referencia_altura que puede ser '=', '<' o '>'
//				   Y tambien recibe la altura.
//Post condiciones: Chequea si amigo_disponible cumple con todos los requisitos, de ser asi devuelve true.
bool cumple_requisitos(amigo_t amigo_disponible, char color[MAX_COLOR], char referencia_altura, int altura, char virtud[MAX_DESCRIPCION], 
	char defecto[MAX_DESCRIPCION]){

	if (tiene_color_pedido(amigo_disponible, color) && tiene_altura_pedida(amigo_disponible, referencia_altura, altura) && 
		tiene_virtud_pedida(amigo_disponible, virtud) && no_tiene_defecto_pedido(amigo_disponible, defecto)){
		return true;
	}

	return false;
}


//Pre condiciones: Recibe el amigo_disponible y potenciales_amigos, este ultimo debe 
//				   tener una cantidad de caracteres menor a MAX_NOMBRE.
//Post condiciones: Compara si ambos strings son iguales y devuelve si es asi o no.
bool fue_amigo(amigo_t amigo_disponible, char potenciales_amigos[MAX_NOMBRE]){
	if (strcmp(amigo_disponible.nombre, potenciales_amigos) == 0){
		return true;
	}

	return false;
}


//Pre condiciones: Recibe la ruta del archivo de texto y el nombre del amigo elegido. 
//				   Ambos debes tener una cantidad de caracteres menor a MAX_NOMBRE.
//Post condiciones:Chequea entre los amigos_t del archivo binario cual cumple todas las condiciones 
//					impuestas por el archivo txt dado. Entre estos compara cual es el mas grande y 
//					lo iguala al nombre del amigo elegido.
void elegir_amigo(char archivo_de_texto[MAX_NOMBRE], char nombre_amigo_elegido[MAX_NOMBRE], bool* encontro_amigo){
	FILE* amigo_ninio = fopen(archivo_de_texto, "r+");

	if (amigo_ninio == NULL){
		printf("error al abrir archivo .TXT\n");
		return;
	}

	FILE* amigos_mansion = fopen("amigos_mansion.dat", "r+");

	if (amigos_mansion == NULL){
		printf("error al abrir archivo amigos_mansion.DAT\n");
		fclose(amigo_ninio);
		return;
	}

	
	amigo_t amigo_a_elegir;
	char referencia_altura;

	int amigos_leidos = fscanf(amigo_ninio, "%[^;];%c%i;%[^;];%[^\n]\n", amigo_a_elegir.color, &referencia_altura, &amigo_a_elegir.altura,
	amigo_a_elegir.virtudes[0].descripcion , amigo_a_elegir.defectos[0].descripcion);

	amigo_t amigo_disponible;
	char potenciales_amigos[MAX_NOMBRE];
	fread(&amigo_disponible, sizeof(amigo_t), 1, amigos_mansion);
	
	char string_aux[MAX_NOMBRE];
	while(!feof(amigos_mansion) && amigos_leidos != EOF){
		if(cumple_requisitos(amigo_disponible, amigo_a_elegir.color, referencia_altura, amigo_a_elegir.altura, 
			amigo_a_elegir.virtudes[0].descripcion, amigo_a_elegir.defectos[0].descripcion)){

			bool esta_entre_ex_amigos = false;
			if((amigo_disponible.esta_en_mansion == true)){ 
				while(amigos_leidos != EOF){
					amigos_leidos = fscanf(amigo_ninio, "%[^\n]\n", potenciales_amigos);
					if (fue_amigo(amigo_disponible, potenciales_amigos)){
						esta_entre_ex_amigos = true;
					}
				}
				if(esta_entre_ex_amigos == true){
					fseek(amigo_ninio, 0, SEEK_SET);
					fscanf(amigo_ninio, "%[^\n]\n", string_aux);
				}else{
					(*encontro_amigo) = true;
					strcpy(nombre_amigo_elegido, amigo_disponible.nombre);
					fseek(amigo_ninio, 0, SEEK_SET);
					fscanf(amigo_ninio, "%[^\n]\n", string_aux);
				}
			}
		}

		fread(&amigo_disponible, sizeof(amigo_t), 1, amigos_mansion);
	}
	if((*encontro_amigo) == true){
		printf("-----------------------------------------\n");
		printf("El amigo elegido es %s\n", nombre_amigo_elegido);
		printf("-----------------------------------------\n");
	}else printf("No se encontro ningun amigo ideal :(\n");

	fclose(amigo_ninio);
	fclose(amigos_mansion);
}


//Pre condiciones: Recibe la ruta del archivo de texto y el nombre del amigo elegido. 
//				   Ambos debes tener una cantidad de caracteres menor a MAX_NOMBRE.
//Post condiciones: Actualiza tanto el archivo de texto dado como el binario. En el 
//					archivo de texto agrega el nombre del amigo al final de todo.
//					En el caso del binario cambia el valor del bool.
void actualizar_archivos(char archivo_de_texto[MAX_NOMBRE], char nombre_amigo_elegido[MAX_NOMBRE], 
	char ruta_archivo_ninio[MAX_NOMBRE]){
	FILE* amigo_ninio = fopen(archivo_de_texto, "r+");

	if (amigo_ninio == NULL){
		printf("error al abrir archivo .TXT\n");
		return;
	}

	FILE* amigos_mansion = fopen("amigos_mansion.dat", "r+");

	if (amigos_mansion == NULL){
		printf("error al abrir archivo amigos_mansion.DAT\n");
		fclose(amigo_ninio);
		return;
	}

	bool se_encontro_amigo = false;
	amigo_t amigo_auxiliar;
	while(!se_encontro_amigo){
		fread(&amigo_auxiliar, sizeof(amigo_t), 1, amigos_mansion);
		if(strcmp(amigo_auxiliar.nombre, nombre_amigo_elegido) == 0){
			
			fseek(amigos_mansion, -1*((int)sizeof(amigo_t)), SEEK_CUR);
			amigo_auxiliar.esta_en_mansion = false;
			fwrite(&amigo_auxiliar, sizeof(amigo_t), 1, amigos_mansion);
			se_encontro_amigo = true;
		}
	}

	FILE* amigo_ninio_actualizado = fopen("amigos_del_ninio_actualizado.txt", "w+");

	if (amigo_ninio_actualizado == NULL){
		fclose(amigo_ninio);
		fclose(amigos_mansion);
		printf("error al abrir archivo\n");
		return;
	}

	char linea_del_archivo_txt[MAX_NOMBRE];
	while(!feof(amigo_ninio)){
		fscanf(amigo_ninio,"%[^\n]\n", linea_del_archivo_txt);
		fprintf(amigo_ninio_actualizado,"%s\n", linea_del_archivo_txt);
	}
	fprintf(amigo_ninio_actualizado,"%s\n", nombre_amigo_elegido);


	fclose(amigo_ninio_actualizado);
	fclose(amigo_ninio);
	fclose(amigos_mansion);


	remove(ruta_archivo_ninio);
	rename("amigos_del_ninio_actualizado.txt", ruta_archivo_ninio);
}


//Pre condiciones: Recibe el nombre del amigo que se quiera devolver, este tiene que tener menos de MAX_NOMBRE caracteres.
//Post condiciones: Cambia a true el esta_en_mansion del amigo dado, si es que existe en el archivo binario.
void devolver_amigo(char nombre_amigo_dado[MAX_NOMBRE]){
	FILE* amigos_mansion = fopen("amigos_mansion.dat", "r+");

	if (amigos_mansion == NULL){
		printf("error al abrir archivo amigos_mansion.DAT\n");
		return;
	}

	bool se_encontro_amigo = false;
	amigo_t amigo_auxiliar;
	while(!se_encontro_amigo && !feof(amigos_mansion)){
		fread(&amigo_auxiliar, sizeof(amigo_t), 1, amigos_mansion);
		if((strcmp(amigo_auxiliar.nombre, nombre_amigo_dado) == 0) && (amigo_auxiliar.esta_en_mansion == false)){
			
			fseek(amigos_mansion, -1*((int)sizeof(amigo_t)), SEEK_CUR);
			amigo_auxiliar.esta_en_mansion = true;
			fwrite(&amigo_auxiliar, sizeof(amigo_t), 1, amigos_mansion);
			se_encontro_amigo = true;
		}
	}

	if (se_encontro_amigo){
		printf("Se devolvio el amigo a la mansion!\n");
	}else printf("No se pudo devolver el amigo a la mansion :c\n");

	fclose(amigos_mansion);
}


//Pre condiciones: -
//Post condiciones: Imprimer por pantalla que el comando no fue valido y especifica los comandos validos.
void imprimir_comando_no_valido(){
	printf("No ingresaste un comando valido!\n");
	printf("Los comandos posibles son los siguentes:\n");
	printf("\t listar_amigos: Lista los amigos disponibles en la mansion\n");
	printf("\t elegir_amigo: Elige el amigo que cumpla los requisitos del archivo .txt dado\n");
	printf("\t devolver_amigo: Devuelve el amigo indicado a la mansion\n");
}


int main(int argc, char const *argv[]){

	char nombre_amigo_elegido[MAX_NOMBRE];

	if (argc == 2){
		if (strcmp("listar_amigos", argv[1]) == 0){
			listar("amigos_mansion.dat");
		}else{
			imprimir_comando_no_valido();
		}
	}else if(argc == 3){
		if (strcmp("elegir_amigo", argv[1]) == 0){
			char ruta_archivo_ninio[MAX_NOMBRE];
			bool encontro_amigo = false;
			strcpy(ruta_archivo_ninio, argv[2]);
			elegir_amigo(ruta_archivo_ninio, nombre_amigo_elegido, &encontro_amigo);
			if(encontro_amigo){
				actualizar_archivos(ruta_archivo_ninio, nombre_amigo_elegido, ruta_archivo_ninio);
			}
		}else if (strcmp("devolver_amigo", argv[1]) == 0){
			char nombre_amigo_dado[MAX_NOMBRE];
			strcpy(nombre_amigo_dado, argv[2]);
			devolver_amigo(nombre_amigo_dado);
		}else{
			imprimir_comando_no_valido();
		}
	}else{
		imprimir_comando_no_valido();
	}
	
	return 0;
}