#include <stdio.h>

/*void c(int8_t x1, int8_t x2, int8_t x3) {
    if (x1 / 3 == x2 && x1 % 3 == x3) {
        x2 = 5 - x2;
        x3 = 5 - x3;
    } else if (x1 != 0) {
        x1 -= 1;
    }
    printf("%d%d%d", x1, x2, x3);
}*/

void f(int8_t x1, int8_t x2, int8_t x3) {
    __asm__(
        ".intel_syntax noprefix\n\t" // ensure intel syntax
        "push ax\n\t"
        "div bl\n\t"                 // (x1 / 3) -> 
        "cmp al, cl\n\t"
        "jne 1f\n\t"
        "cmp ah, dl\n\t"
        "jnz 1f\n\t"
        "mov al, 5\n\t"
        "sub al, cl\n\t"
        "mov cl, al\n\t"
        "mov al, 5\n\t"
        "sub al, dl\n\t"
        "mov dl, al\n\t"
        "pop ax\n\t"
        "jmp 2f\n"
        "1:\n\t"
        "pop ax\n\t"
        "cmp al, 0\n\t"
        "jz 2f\n\t"
        "sub al, 1\n"
        "2:\n\t"
        "nop"
    : "=a" (x1), // AL -> x1
    "=c" (x2),   // CL -> x2
    "=d" (x3)    // DL -> x3
    : [x1] "a" (x1), // x1 -> AL
    [d] "b" (3),     // 3  -> BL
    [x2] "c" (x2),   // x2 -> CL
    [x3] "d" (x3)    // x3 -> DL
    );
    printf("%d%d%d\n", x1, x2, x3);
}

int main() {
    int8_t tests[][3] = {
        {0, 0, 0},
        {0, 0, 1},
        {1, 1, 1},
        {1, 2, 3},
        {3, 2, 1}, 
        {5, 5, 5},
        {4, 1, 1},
        {4, 1, 2},
        {7, 2, 1},
        {9, 3, 0},
        {9, 3, 8},
    };

    for (int i = 0; i < sizeof(tests) / sizeof(*tests); i++) {
        int8_t x1 = tests[i][0], x2 = tests[i][1], x3 = tests[i][2];
        printf("f(%d%d%d): ", x1, x2, x3);
        //c(x1, x2, x3);
        f(x1, x2, x3);
    }
}
