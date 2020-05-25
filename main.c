#include <stdio.h>
#include <string.h>

void c(char s[3]) {
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
	: "al", "ah", "cl"
	);
	printf("%s\n", s);
}

int main() {	
	while (1) {
		char s[4];
		printf("Enter string with 3 digits (or <Ctrl+C> to exit): ");
		scanf("%s", s);
		for (int i = 0; i < 3; i++) {
			if (s[i] < '0' || s[i] > '9') {
				printf("Wrong format! Try again.\n");
				goto OUTER;
			}
		}
		if (s[3] != '\0') {
			printf("Wrong format! Try again.\n");
			continue;
		}

		f(s);
		OUTER: continue;
	}
}
