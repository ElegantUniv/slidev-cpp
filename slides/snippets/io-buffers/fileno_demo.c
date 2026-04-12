#include <stdio.h>

printf("%d\n", fileno(stdin));   // 0
printf("%d\n", fileno(stdout));  // 1
printf("%d\n", fileno(stderr));  // 2
