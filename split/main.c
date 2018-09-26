#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// FIXIT: 1) неясно из названия List, зачем нужна структура. Поля структуры показывают, что это не абстрактный список.
// 2) видимо lines - мн. ч.

struct List {
	int number;
	char ** line;
};

// 1) В названии ф-и глагол - splitString видимо. 2) Обычно сначала идут input аргументы, потом output
// 3) разные стили именования (давайте на семинаре этот момент обсудим)
struct List * strings_division(struct List * output, char * array_intput, char * special_symbols);
void Destroy(struct List * line);
struct List * New();

// FIXIT: магические числа 100 и 20 надо вынести в константы с ясным именем.

int main() {
	struct List * line = NULL;
	char input_string[100] = {0};
	char symbols[20] = {0};
	int counter = -1;
	fprintf(stderr, "Enter your string, use \\n to complete the line input:\n");
	do {
		counter++;
		assert(counter < 100);
		input_string[counter] = getchar();
	} while( input_string[counter] != '\n');
	input_string[counter] = '\0';
	counter = -1;
	fprintf(stderr, "Enter your tokens, use \\n to complete the line input:\n");
	do {
		counter++;
		assert(counter < 20);
		symbols[counter] = getchar();
	} while(symbols[counter] != '\n');
	symbols[counter] = '\0';
	line = strings_division(line, input_string, symbols);
	assert(line->number);
	printf("\nYour strings: \n");
	for(counter = 0; counter < line->number; counter++) {
		assert(line->line[counter]);
		printf("%s\n", line->line[counter]);
	}
	printf("The number of strings: %d\n", line->number);
	Destroy(line);
	return 0;
}

struct List * strings_division(struct List * output, char * array, char * array_sign) {
	assert(!output);
	int array_lenght = 0;
	int counter_1 = 0;
	int counter_2 = 0;
	output = New();
	assert(output);
	
	// FIXIT: код ниже повторяет функционал strtok. давайте просто воспользуемся готовой ф-ей. кода будет меньше.
	output->line[output->number] = array;
	output->number++;
	for(; array[counter_1] != '\0'; counter_1++) {
		for(counter_2 = 0; array_sign[counter_2] != '\0'; counter_2++) {
			if(array[counter_1] == array_sign[counter_2]) array[counter_1] = '\0';
		}
	}
	array_lenght = counter_1;
	for(counter_1 = 0; counter_1 < array_lenght; counter_1++) {
		if(array[counter_1] == '\0' && array[counter_1 + 1] != '\0') {
		output->line[output->number] = array + counter_1 + 1;
		output->number++;
		}
	}
	return output;
}

void Destroy(struct List * line) {
	free(line->line);
	free(line);
}

struct List * New() {
	struct List * output = NULL;
	output = (struct List *)calloc(1, sizeof(struct List));
	output->line = (char**)calloc(100, sizeof(char*));
	return output;
}
