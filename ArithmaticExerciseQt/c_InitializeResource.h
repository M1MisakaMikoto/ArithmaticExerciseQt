#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<cjson/cJSON.h>
#include<stdio.h>
#include<io.h>
#include<direct.h>

int InitializeResource() {
	FILE* fp = NULL;

	if (_access("./Save", 0) == -1) {
		if (_mkdir("./Save") == -1) {
			printf("[ERROR]UnableToCreateFiles");
			return -1;
		}
		printf("create the path [Save].\n");
	}

	if (_access("./Save/Questions.json", 0) == -1) {
		if ((fp = fopen("./Save/Questions.json", "wb")) == NULL) {
			printf("[ERROR]UnableToCreateFiles");
		}
		printf("create the file [./Save/Questions.json]");
	}

	return 0;
}