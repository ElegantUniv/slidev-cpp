// 라인 버퍼링 (터미널)
printf("loading...");     // \n 없음 → 화면에 아직 안 나옴
do_heavy_work();
printf("done\n");         // \n → 두 문자열이 한꺼번에 출력

// 풀 버퍼링 (파일 리다이렉션: ./prog > out.txt)
printf("Hello");          // 버퍼에만 저장
printf("World");          // 버퍼에만 저장
// 프로그램 종료 → fflush() 자동 호출 → 파일에 기록됨

// 언버퍼드 (stderr)
fprintf(stderr, "Error"); // 즉시 출력, 항상
