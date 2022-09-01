#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_NOMBRE 50

typedef struct juego {
	int id_juego;
	char nombre[MAX_NOMBRE];
} juego_t;

int main(int argc, char const *argv[]){
	
	FILE* juegos = fopen("juegos.dat", "w+");

	if (juegos == NULL){
		printf("error al abrir");
		return -1;
	}

	juego_t juego_uno;
	juego_uno.id_juego = 1;
	strcpy(juego_uno.nombre, "Ajedrez");
	fwrite(&juego_uno, sizeof(juego_t), 1, juegos);

	juego_t juego_dos;
	juego_dos.id_juego = 2;
	strcpy(juego_dos.nombre, "Clue");
	fwrite(&juego_dos, sizeof(juego_t), 1, juegos);

	juego_t juego_tres;
	juego_tres.id_juego = 3;
	strcpy(juego_tres.nombre, "Hearthstone");
	fwrite(&juego_tres, sizeof(juego_t), 1, juegos);

	fclose(juegos);
	
	return 0;
}