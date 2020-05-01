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
	printf("%d%d%d", s1, s2, s3);
}

void f(char s[4]) {
	__asm__(
		"# convert chars to numbers\n\t"
		"subb $48,  (%[s])  # s[0] := s[0] - '0'\n\t"
		"subb $48, 1(%[s])  # s[1] := s[1] - '0'\n\t"
		"subb $48, 2(%[s])  # s[2] := s[2] - '0'\n\t"
		"movb (%[s]), %%al  # AL <- s[0]\n\t"
		"divb %[d]          # AL <- (s[0] / 3), AH <- (s[0] mod 3)\n\t"
		"cmpb %%al, 1(%[s]) # if (s[0] / 3 != s[1])\n\t"
		"jne 1f             #     goto 1\n\t"
		"cmpb %%ah, 2(%[s]) # if (s[0] mod 3 != s[2])\n\t"
		"jne 1f             #     goto 1\n"
		"movb $5, %%cl      # CL <- 5\n\t"
		"subb 1(%[s]), %%cl # CL <- 5 - s[1]\n\t"
		"movb %%cl, 1(%[s]) # s[1] <- 5 - s[1]\n\t"
		"movb $5, %%cl      # CL <- 5\n\t"
		"subb 2(%[s]), %%cl # CL <- 5 - s[2]\n\t"
		"movb %%cl, 2(%[s]) # s[2] <- 5 - s[2]\n\t"
		"jmp 2f             # goto 2\n"
		"1:\n\t"
		"cmpb $0, (%[s])    # if (s1 == 0)\n\t"
		"je 2f              #     goto 2\n\t"
		"subb $1, (%[s])    # s1 := s1 - 1\n"
		"2:\n\t"
		"# bring chars back\n\t"
		"addb $48,  (%[s])  # s[0] := s[0] + '0'\n\t"
		"addb $48, 1(%[s])  # s[1] := s[1] + '0'\n\t"
		"addb $48, 2(%[s])  # s[2] := s[2] + '0'\n\t"
		"\n\t"
	: "=S" (s)
	: [s] "S" (s),
	[d] "b" ((int8_t)3)
	: "al", "ah"
	);
	printf("%s\n", s);
}

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
		f(tests[n][0]);
    }
}
