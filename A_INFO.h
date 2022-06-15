#ifndef AINFO_HEADER
#define AINFO_HEADER

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct StudentInfo {
	char id[20]; // 학번
	char name[20]; // 이름
	int grade; // 학년
	double in_time; // 입실 시간
	int in_cnt; // 입실 상태 (1 이면 입실 완료)
	double out_time; // 퇴실 시간
	int out_cnt; // 퇴실 상태 1 이면 퇴실 완료)
	struct StudentInfo* next; // 다음 노드의 주소를 저장할 포인터
}SINFO;

void get_studentinfo();
void insert_node(SINFO* student);
void print_list();
void delete_list();
void search_list();
void update_node();
void print_star();
void print_line();
void error_id();
void info(SINFO* student);

SINFO* listhead = NULL;

#endif