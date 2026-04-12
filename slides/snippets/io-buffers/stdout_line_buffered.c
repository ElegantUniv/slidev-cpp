// ./prog 직접 실행
printf("Step 1\n");  // \n → 즉시 화면 출력
printf("Step 2\n");  // \n → 즉시 화면 출력

// ⚠️ \n 없으면 나중에 출력될 수 있음
printf("loading...");
// (무거운 작업 진행 중)
// "loading..." 이 작업 중에 보이지 않을 수 있음
// fflush(stdout)으로 해결
printf(" done\n");
