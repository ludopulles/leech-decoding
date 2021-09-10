#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "leech_utils.h"
#include "leech.h"
#include "leech_unsafe.c"

int main(int argc, char **argv)
{
	// target, output, distance
	uint32_t t[24];
	uint64_t cv, cv2, d;

	if (argc == 2) {
		int ith = atoi(argv[1]);
		for (int i = 0; i < 24; i++) {
			t[i] = leech[ith][i] * SCALE;
		}
	} else {
		for (int i = 0; i < 24; i++) {
			scanf("%u", &t[i]);
			t[i] %= Q;
		}
	}

	for (int i = 0; i < 24; i++) {
		t[i] %= Q;
	}

	decoder_L24(t, &cv, &d);
	decoder_L24_unsafe(t, &cv2, &d);

	assert(cv == cv2);


	printf("Input\n");
	printvu(t);
	printf("Output\n");

	printvb(cv, 12);

	printf("Distance\n%lu\n", d);
	
	return 0;
}
