#pragma once
#include<stdio.h>
#include<cjson/cJSON.h>
#include<sys/stat.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<io.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

static int get_file_size(const char* filePath) {
	int fd = open(filePath, O_RDONLY);
	struct stat statBuffer;
	fstat(fd, &statBuffer);
	return statBuffer.st_size;
};

struct QuestionLoader
{
	cJSON* questionJson = NULL;
	cJSON* questionList = NULL;
	int readSerialNumber = 1;
	int questionAmount = 0;
	int completeProgress = 0;
	int correctQuantity = 0;

	int LoadQuestions(int* questionType = NULL) {
		questionJson = NULL;
		questionList = NULL;
		readSerialNumber = 1;
		questionAmount = 0;

		int fileSize = get_file_size("Save/Questions.json");
		FILE* jsonFile = NULL;
		jsonFile = fopen("Save/Questions.json", "r");
		char* jsonStr = (char*)malloc(sizeof(char) * fileSize + 1);
		if (jsonStr == 0) {
			return -1;
		}
		fread(jsonStr, sizeof(char), fileSize, jsonFile);
		questionJson = cJSON_Parse(jsonStr);
		free(jsonStr);
		fclose(jsonFile);

		questionAmount = cJSON_GetObjectItem(questionJson, "questionsAmount")->valueint;
		questionList = cJSON_GetObjectItem(questionJson, "questions");
		readSerialNumber = 1 + cJSON_GetObjectItem(questionJson, "completionProgress")->valueint;
		if (questionType != NULL) {
			*questionType = cJSON_GetObjectItem(questionJson, "questionType")->valueint;
		}
		completeProgress = cJSON_GetObjectItem(questionJson, "completionProgress")->valueint;
		correctQuantity = cJSON_GetObjectItem(questionJson, "correctQuantity")->valueint;

		return readSerialNumber;
	}

	int UpdateProgress(int isCorrect) {
		completeProgress += 1;
		if (isCorrect) {
			correctQuantity += 1;
		}
		return 1;
	}

	int NextQuestion(char questionText[256], double options[4], int* rightChoice) {
		if (questionJson == NULL) {
			return -1;
		}
		if (readSerialNumber > questionAmount) {
			return 0;
		}
		//读取问题
		char charNum[128] = { 0 };
		_itoa(readSerialNumber, charNum, 10);
		cJSON* question = cJSON_GetObjectItem(questionList, charNum);
		_itoa(cJSON_GetObjectItem(question, "firstMultiplier")->valueint, questionText, 10);
		strcat(questionText, " ");
		strcat(questionText, cJSON_GetObjectItem(question, "signal")->valuestring);
		strcat(questionText, " ");
		_itoa(cJSON_GetObjectItem(question, "secondMultiplier")->valueint, charNum, 10);
		strcat(questionText, charNum);
		strcat(questionText, " = ?");
		readSerialNumber += 1;

		//读取选项
		int rightAnswerIndex = 0;
		options[0] = cJSON_GetObjectItem(question, "answer")->valuedouble;
		if (options[0] != 0) {
			options[1] = options[0] - 1.0;
			options[2] = options[0] * 2.0;
			options[3] = options[0] + options[1] + options[2];
		}
		else {
			options[1] = options[0] - 1.0;
			options[2] = (options[0] + 1) * 2.0;
			options[3] = options[0] + options[1] + options[2];
		}
		//打乱选项
		srand((unsigned)time(NULL));
		for (int i = 0; i < 4; i++) {
			int indexA = rand() % 4;
			int indexB = rand() % 4;
			double temp = options[indexA];
			options[indexA] = options[indexB];
			options[indexB] = temp;
			if (indexA != indexB) {
				if (indexA == rightAnswerIndex) {
					rightAnswerIndex = indexB;
				}
				else if (indexB == rightAnswerIndex) {
					rightAnswerIndex = indexA;
				}
			}
		}
		*rightChoice = rightAnswerIndex + 1;
		return 1;
	}

	int UnloadQuestions() {
		if (questionJson != NULL)
		{
			cJSON_ReplaceItemInObject(questionJson, "completionProgress", cJSON_CreateNumber(completeProgress));
			cJSON_ReplaceItemInObject(questionJson, "correctQuantity", cJSON_CreateNumber(correctQuantity));
			FILE* fp = NULL;
			if ((fp = fopen("./Save/Questions.json", "w")) == NULL) {
				printf("file open error\n");
				return -1;
			}

			if (fputs(cJSON_Print(questionJson), fp) == EOF) {
				printf("file write error\n");
				return -1;
			}
			fclose(fp);
			cJSON_Delete(questionJson);
		}
		questionJson = NULL;
		questionList = NULL;
		readSerialNumber = 1;
		questionAmount = 0;
		return 0;
	}
};
