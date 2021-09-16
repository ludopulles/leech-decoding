#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "leech_utils.h"
#include "leech.h"
#include "leech_unsafe.c"

void print_result(uint32_t t[24]) {
	// t: target
	uint32_t out[24];
	// cv: output
	// d: distance
	uint64_t cv, d;

	for (int i = 0; i < 24; i++) t[i] %= Q;

	decoder_L24(t, &cv, &d);

	printf("Input:\n");
	printvu(t);

	printf("Output:\n");
	decode_pt(out, cv, 1);
	printvu(out);
	printf("Distance: %lu\n", d);

	for (int i=0; i<24; i++)
		t[i] = (t[i] >= out[i] ? (t[i] - out[i]) : (t[i] + Q - out[i])) % Q;
	printf("CVP:\n");
	printvu(t);
}

void compare_output(uint32_t t[24]) {
	// t, t2: target
	uint32_t t2[24], out[24];
	// cv, cv2: output
	// d, d2: distance
	uint64_t cv, cv2, d, d2;

	for (int i = 0; i < 24; i++) {
		t[i] %= Q;
		t2[i] = t[i];
	}

	decoder_L24(t, &cv, &d);
	decoder_L24_unsafe(t2, &cv2, &d2);

	if (cv != cv2) {
		printf("Different CVP!\nInput:\n");
		printvu(t);
		printf("Output\n");

		printvb(cv, 12);
		printvb(cv2, 12);

		decode_pt(out, cv, 1);
		printvu(out);
		for (int i=0; i<24; i++)
			t[i] = (t[i] >= out[i] ? (t[i] - out[i]) : (t[i] + Q - out[i])) % Q;
		decode_pt(out, cv2, 1);
		for (int i=0; i<24; i++)
			t2[i] = (t2[i] >= out[i] ? (t2[i] - out[i]) : (t2[i] + Q - out[i])) % Q;
		printvu(out);

		printvu(t);
		printvu(t2);

		printf("Distance: %lu VS %lu\n", d, d2);
	}
}

int main(int argc, char **argv) {
	uint32_t t[24];

	if (argc == 2) {
		int ith = atoi(argv[1]);
		if (ith < 0) {
			for (ith = 0; ith < 24; ith++) {
				for (int i=0; i<24; i++) {
					t[i] = leech[ith][i] * SCALE;
				}
				compare_output(t);
			}
			return 0;
		}

		for (int i = 0; i < 24; i++) {
			t[i] = leech[ith][i] * SCALE;
		}
	} else {
		for (int i = 0; i < 24; i++) {
			scanf("%u", &t[i]);
			t[i] %= Q;
		}
	}

	// compare_output(t);
	print_result(t);
	return 0;
}
