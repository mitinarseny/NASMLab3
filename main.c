#include <stdio.h>

void c(char s[4]) {
	int8_t s1 = s[0] - '0';
	int8_t s2 = s[1] - '0';
	int8_t s3 = s[2] - '0';
	if (s1 / 3 == s2 && s1 % 3 == s3) {
		s2 = 5 - s2;
		s3 = 5 - s3;
	} else if (s1 != 0) {
		s1 -= 1;
	}
	printf("%d%d%d\n", s1, s2, s3);
}

void f(char s[3]) {
	
}

/* void f(int8_t s[3]) { */
/*     __asm__( */
/* 		"push %%ax\n\t" */
/* 		"mov cl, ()" */
/*         "div bl\n\t" */
/*         "cmp al, \t" */
/*         "jne 1f\n\t" */
/*         "cmp ah, dl\n\t" */
/*         "jnz 1f\n\t" */
/*         "mov al, 5\n\t" */
/*         "sub al, cl\n\t" */
/*         "mov cl, al\n\t" */
/*         "mov al, 5\n\t" */
/*         "sub al, dl\n\t" */
/*         "mov dl, al\n\t" */
/*         "pop ax\n\t" */
/*         "jmp 2f\n" */
/*         "1:\n\t" */
/*         "pop ax\n\t" */
/*         "cmp al, 0\n\t" */
/*         "jz 2f\n\t" */
/*         "sub al, 1\n" */
/*         "2:\n\t" */
/*         "nop" */
/*     : "=S" (s) // AL -> x1 */
/*     : [s] "S" (s), // x1 -> AL */
/*     [d] "b" (3),     // 3  -> BL */
/*     [com] "c" (5)   // x2 -> CL */
/*     ); */
/* 	for (int i = 0; i < 3; i++) */
/* 		printf("%d", s[i]); */
/* 	printf("\n"); */
/* } */

int main() {
    char tests[][2][4] = {
		{"000", "055"},
		{"001", "001"},
		{"111", "011"},
		{"123", "023"},
		{"321", "221"},
		{"555", "455"},
		{"411", "444"},
		{"412", "312"},
		{"721", "734"},
		{"930", "925"},
		{"938", "838"},
    };

    for (int n = 0; n < sizeof(tests) / sizeof(*tests); n++) {
		printf("f(%s): [should be %s] ", tests[n][0], tests[n][1]);
		c(tests[n][0]);
        /* f(tests[n]); */
    }
}
