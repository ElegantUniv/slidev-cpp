// 방법 1: getchar()로 '\n' 제거
scanf("%d", &age);
getchar();               // '\n' 소비
scanf("%s", name);       // ✅

// 방법 2: 포맷 문자열 앞 공백
scanf("%d", &age);
scanf(" %c", &ch);       // ✅ 공백이 공백/개행 무시
scanf(" %[^\n]", name);  // ✅ 한 줄 읽기
