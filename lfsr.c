#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/**
 * Initialise un générateur pseudo-aléatoire.
 */
void init_random() {
	srand((unsigned int) time(NULL));
}

/**
 * Initialise le polynôme de rétroaction du registre.
 * coefficients un pointeur vers un tableau de caractères.
 * length le degré du polynôme.
 */
void init_coefficients(char *coefficients, int length) {
	for (int i = 0; i < length; i++) {
		coefficients[i] = rand() % 2;
	}
}

/**
 * Initialise le registre avec des bits aléatoires.
 * registers un pointeur vers un tableau de caractères.
 * length le nombre de registres.
 */
void init_lfsr(char *registers, int length) {
	for (int i = 0; i < length; i++) {
		registers[i] = rand() % 2;
	}
}

/**
 * Affiche le contenu du registre.
 * registers un pointeur vers un tableau de caractères.
 * length la longueur du registre.
 */
void print_registers(char *registers, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d", registers[i]);
	}
}

/**
 * Affiche le polynôme de rétroaction du registre.
 * coefficients un pointeur vers un tableau de caractères.
 * length le degré du polynôme.
 */
void print_coefficients(char *coefficients, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d", coefficients[i]);
	}
}

/**
 * Effectue un tour du LFSR.
 * Applique le polynôme de rétroaction au registre et décale celui-ci.
 * registers un pointeur vers un tableau de caractères.
 * length la longueur du registre.
 * Retourne le bit de poids faible du registre.
 */
char clock_lfsr(char *registers, char *coefficients, int length) {
	// Application des coefficients
	char new;
	for (int i = 0; i < length; i++) {
		if ((unsigned int) coefficients[i]) {
			new = new ^ (unsigned int) registers[i];
		}
	}

	// Sauvegarde du bit de poids faible
	char last = registers[length - 1];

	// Décalage du registre
	char tmp;
	for (int i = length - 1; i > 0; i--) {
		registers[i] = registers[i - 1];
	}

	// Insertion du nouveau bit
	registers[0] = new;

	// Retourne le bit de poids faible du registre
	return last;
}

void berlekamp_massey(char *random, unsigned int length, char *result) {
	unsigned int L = 0;
	int m;
	char *f = malloc(sizeof(char) * L);
	char *g = malloc(0);

	for (int n = 0; n < length; n++) {
		char sum;
		for (int l = 0; l < L; l++) {
			sum = sum ^ f[l] ^ random[n - l];
		}
		char d = random[n] ^ sum; 

		if (d == 1) {
			char *t = malloc(sizeof(f));
			strncpy(t, f, sizeof(f));



			if (2 * L <= n) {
				L = n + 1 - L;
				m = n;
				g = t;
				free(g);
				g = malloc(sizeof(t));
				strncpy(g, t, sizeof(t));
			}
			
			free(t);
		}
	}

	result = malloc(sizeof(char) * L);
	strncpy(result, f, sizeof());

	free(f);
	free(g);
}

int main(int argc, char **argv) {
	unsigned int length = atoi(argv[1]);
	char registers[length];

	// Initialisation d'un générateur pseudo-aléatoire
	init_random();

	// Initialisation du registre
	init_lfsr(registers, length);

	// Génération du polynôme de rétroaction du registre
	char coefficients[length];
	init_coefficients(coefficients, length);

	// DEBUG
	printf("Coefficients : ");
	print_coefficients(coefficients, length);
	printf("\n");

	// Génère les la suite pseudo-aléatoire
	for (int i = 0; i < length * 2; i++) {
		unsigned int rand = clock_lfsr(registers, coefficients, length);
		printf("%d", rand);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
