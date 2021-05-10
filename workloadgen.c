#include <stdio.h>
#include <stdlib.h>

#define NUMPATIENTS 300

//float PRIORITY_PROBS[] = {0.2, 0.2, 0.2, 0.2, 0.2};
float PRIORITY_PROBS[] = {0.4, 0.3, 0.2, 0.05, 0.05};

int mygetline(char *str) {
	char c;
	int i = 0;

	while((c = getchar()) != '\n' && c != EOF)
		str[i++] = c;
	str[i] = '\0';

	if(c == EOF)
		return 0;
	else
		return 1;
}

void main() {
	char names[300][30];
	int numnames = 0, i, j;
	float unirand, cumulprob;

	while(mygetline(names[numnames++]));
	numnames--;				// one extra empty line is read to detect an EOF

	for(i = 0; i < NUMPATIENTS; i++) {
		unirand = (rand() % 100000) / 100000.0;
		cumulprob = 0;
		for(j = 0; j < 5; j++) {
			cumulprob += PRIORITY_PROBS[j];
			if(cumulprob > unirand)
				break;
		}

		printf("%d %d %s\n", i, j, names[rand() % numnames]);
	}

}
