// 참고자료 코딩도장: https://dojang.io/mod/page/view.php?id=724
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

// 토큰 종류 열거형
typedef enum _TOKEN_TYPE {
    TOKEN_STRING,    // 문자열 토큰
    TOKEN_NUMBER,    // 숫자 토큰
} TOKEN_TYPE;

// 토큰 구조체
typedef struct _TOKEN {
    TOKEN_TYPE type;    // 토큰 종류
    union {             // 두 종류 중 한 종류만 저장할 것이므로 공용체로 만듦
        char *string;       // 문자열 포인터
        double number;      // 실수형 숫자
    };
    bool isArray;       // 현재 토큰이 배열인지 표시
} TOKEN;

// 토큰의 최대 개수
#define TOKEN_COUNT 20

// JSON 구조체
typedef struct _JSON {
    TOKEN tokens[TOKEN_COUNT];    // 토큰 배열
	size_t token_count;
} JSON;

using namespace std;

void parseJSON(char *doc, int size, JSON *json);
void freeJSON(JSON *json);