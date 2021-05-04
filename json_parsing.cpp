#include "json_parsing.hpp"

void parseJSON(char *doc, int size, JSON *json)    // JSON 파싱 함수
{
    int pos = 0;           // 문자 검색 위치를 저장하는 변수

    if (doc[pos] != '{')   // 문서의 시작이 {인지 검사
        return;

    pos++;    // 다음 문자로

    while (pos < size)       // 문서 크기만큼 반복
    {
        switch (doc[pos])    // 문자의 종류에 따라 분기
        {
        case '"':            // 문자가 "이면 문자열
        {
            // 문자열의 시작 위치를 구함. 맨 앞의 "를 제외하기 위해 + 1
            char *begin = doc + pos + 1;

            // 문자열의 끝 위치를 구함. 다음 "의 위치
            char *end = strchr(begin, '"');
            if (end == NULL)    // "가 없으면 잘못된 문법이므로 
                break;          // 반복을 종료

            int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

            // 토큰 배열에 문자열 저장
            // 토큰 종류는 문자열
            json->tokens[json->token_count].type = TOKEN_STRING;
            // 문자열 길이 + NULL 공간만큼 메모리 할당
            json->tokens[json->token_count].string = (char *)malloc(stringLength + 1);
            // 할당한 메모리를 0으로 초기화
            memset(json->tokens[json->token_count].string, 0, stringLength + 1);

            // 문서에서 문자열을 토큰에 저장
            // 문자열 시작 위치에서 문자열 길이만큼만 복사
            memcpy(json->tokens[json->token_count].string, begin, stringLength);

            json->token_count++; // 토큰 인덱스 증가

            pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + "(+ 1)
        }
        break;
        }

        pos++; // 다음 문자로
    }
}

void freeJSON(JSON *json)    // JSON 해제 함수
{
    for (int i = 0; i < json->token_count; i++)            // 토큰 개수만큼 반복
    {
        if (json->tokens[i].type == TOKEN_STRING)    // 토큰 종류가 문자열이면
            free(json->tokens[i].string);            // 동적 메모리 해제
    }
}