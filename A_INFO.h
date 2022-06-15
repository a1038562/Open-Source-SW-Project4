#ifndef AINFO_HEADER
#define AINFO_HEADER

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct StudentInfo {
	char id[20]; // �й�
	char name[20]; // �̸�
	int grade; // �г�
	double in_time; // �Խ� �ð�
	int in_cnt; // �Խ� ���� (1 �̸� �Խ� �Ϸ�)
	double out_time; // ��� �ð�
	int out_cnt; // ��� ���� 1 �̸� ��� �Ϸ�)
	struct StudentInfo* next; // ���� ����� �ּҸ� ������ ������
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