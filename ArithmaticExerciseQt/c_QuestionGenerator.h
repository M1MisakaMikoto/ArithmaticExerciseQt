#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include<cjson/cJSON.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>

enum {
	ADDTION = 1, SUBTRACTION, MULTIPLICATION, DIVISION
};

int QuestionGenerator(int questionsType, int questionsAmount) {

	printf("generating questions...\n");

	cJSON* questions = cJSON_CreateObject();

	cJSON** questionUnit = (cJSON**)malloc(sizeof(cJSON*) * questionsAmount);
	for (int i = 0; i < questionsAmount; i++) {
		questionUnit[i] = cJSON_CreateObject();
	}

	int multiplierQuantity = 0;
	int generatorCount = 0;

	//随机序号
	char serialNumber[16] = { 0 };
	int* questionSerialNumber = (int*)malloc(sizeof(int) * questionsAmount);
	for (int i = 0; i < questionsAmount; i++) {
		questionSerialNumber[i] = i + 1;
	}
	int swapTimes = questionsAmount * ceil(sqrt(questionsAmount));
	srand((unsigned)time(NULL));
	for (int i = 0; i < swapTimes; i++) {
		int indexA = rand() % questionsAmount;
		int indexB = rand() % questionsAmount;
		int temp = questionSerialNumber[indexA];
		questionSerialNumber[indexA] = questionSerialNumber[indexB];
		questionSerialNumber[indexB] = temp;
	}

	switch (questionsType)
	{
	case ADDTION:
		multiplierQuantity = ceil(sqrt(questionsAmount));
		for (int firstMultiplier = 1; firstMultiplier <= multiplierQuantity; firstMultiplier++) {
			for (int secondMultiplier = 1; secondMultiplier <= multiplierQuantity; secondMultiplier++) {

				char equation[256] = { 0 };
				int answer = firstMultiplier + secondMultiplier;
				_itoa(questionSerialNumber[generatorCount], serialNumber, 10);
				cJSON_AddItemToObject(questionUnit[generatorCount], "firstMultiplier", cJSON_CreateNumber(firstMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "secondMultiplier", cJSON_CreateNumber(secondMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "signal", cJSON_CreateString("＋"));
				cJSON_AddItemToObject(questionUnit[generatorCount], "answer", cJSON_CreateNumber(answer));
				cJSON_AddItemToObject(questions, serialNumber, questionUnit[generatorCount]);

				if (++generatorCount >= questionsAmount) {
					break;
				}
			}
			if (generatorCount >= questionsAmount) {
				break;
			}
		}
		break;

	case SUBTRACTION:
		multiplierQuantity = ceil(sqrt(questionsAmount));
		for (int firstMultiplier = 1; firstMultiplier <= multiplierQuantity; firstMultiplier++) {
			for (int secondMultiplier = 1; secondMultiplier <= multiplierQuantity; secondMultiplier++) {
				char equation[256] = { 0 };
				int answer = firstMultiplier - secondMultiplier;
				_itoa(questionSerialNumber[generatorCount], serialNumber, 10);
				cJSON_AddItemToObject(questionUnit[generatorCount], "firstMultiplier", cJSON_CreateNumber(firstMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "secondMultiplier", cJSON_CreateNumber(secondMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "signal", cJSON_CreateString("－"));
				cJSON_AddItemToObject(questionUnit[generatorCount], "answer", cJSON_CreateNumber(answer));
				cJSON_AddItemToObject(questions, serialNumber, questionUnit[generatorCount]);

				if (++generatorCount >= questionsAmount) {
					break;
				}
			}
			if (generatorCount >= questionsAmount) {
				break;
			}
		}
		break;

	case MULTIPLICATION:
		multiplierQuantity = ceil(sqrt(questionsAmount));

		for (int firstMultiplier = 1; firstMultiplier <= multiplierQuantity; firstMultiplier++) {
			for (int secondMultiplier = 1; secondMultiplier <= multiplierQuantity; secondMultiplier++) {

				char equation[256] = { 0 };
				int answer = firstMultiplier * secondMultiplier;
				_itoa(questionSerialNumber[generatorCount], serialNumber, 10);
				cJSON_AddItemToObject(questionUnit[generatorCount], "firstMultiplier", cJSON_CreateNumber(firstMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "secondMultiplier", cJSON_CreateNumber(secondMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "signal", cJSON_CreateString("×"));
				cJSON_AddItemToObject(questionUnit[generatorCount], "answer", cJSON_CreateNumber(answer));
				cJSON_AddItemToObject(questions, serialNumber, questionUnit[generatorCount]);

				if (++generatorCount >= questionsAmount) {
					break;
				}
			}
			if (generatorCount >= questionsAmount) {
				break;
			}
		}
		break;

	case DIVISION:
		multiplierQuantity = ceil(sqrt(questionsAmount));
		for (double firstMultiplier = 1; firstMultiplier <= multiplierQuantity; firstMultiplier++) {
			for (double secondMultiplier = 1; secondMultiplier <= multiplierQuantity; secondMultiplier++) {

				char equation[256] = { 0 };
				double answer = (round((firstMultiplier / secondMultiplier) * 100))/100;
				_itoa(questionSerialNumber[generatorCount], serialNumber, 10);
				cJSON_AddItemToObject(questionUnit[generatorCount], "firstMultiplier", cJSON_CreateNumber(firstMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "secondMultiplier", cJSON_CreateNumber(secondMultiplier));
				cJSON_AddItemToObject(questionUnit[generatorCount], "signal", cJSON_CreateString("÷"));
				cJSON_AddItemToObject(questionUnit[generatorCount], "answer", cJSON_CreateNumber(answer));
				cJSON_AddItemToObject(questions, serialNumber, questionUnit[generatorCount]);

				if (++generatorCount >= questionsAmount) {
					break;
				}
			}
			if (generatorCount >= questionsAmount) {
				break;
			}
		}
		break;
	}

	cJSON* json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "questionsAmount", cJSON_CreateNumber(questionsAmount));
	cJSON_AddItemToObject(json, "completionProgress", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(json, "correctQuantity", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(json, "questionType", cJSON_CreateNumber(questionsType));

	cJSON_AddItemToObject(json, "questions", questions);
	FILE* fp = NULL;
	if ((fp = fopen("./Save/Questions.json", "w")) == NULL) {
		printf("file open error\n");
		return -1;
	}

	if (fputs(cJSON_Print(json), fp) == EOF) {
		printf("file write error\n");
		return -1;
	}

	fclose(fp);
	printf("questions create success\n");

	cJSON_Delete(json);
	//cJSON的cJSON_Delete()API有bug，不调了

	free(questionUnit);

	return 0;
};