#include "ArithmaticExerciseQt.h"
#include "QGraphicsDropShadowEffect"
#include "c_InitializeResource.h"
#include "c_QuestionGenerator.h"
#include<time.h>

//UI阴影效果
#define UI_ADD_SHADOW_EFFECT QGraphicsDropShadowEffect* frame_top_shadow = new QGraphicsDropShadowEffect;\
frame_top_shadow->setBlurRadius(15);\
frame_top_shadow->setColor(Qt::black);\
frame_top_shadow->setYOffset(1);\
frame_top_shadow->setXOffset(0);\
ui.top->setGraphicsEffect(frame_top_shadow);\
QGraphicsDropShadowEffect* frame_MAIN_MENU_shadow = new QGraphicsDropShadowEffect;\
frame_MAIN_MENU_shadow->setBlurRadius(25);\
frame_MAIN_MENU_shadow->setColor(Qt::black);\
frame_MAIN_MENU_shadow->setOffset(0);\
ui.MAIN_MENU->setGraphicsEffect(frame_MAIN_MENU_shadow);\
QGraphicsDropShadowEffect* frame_answerPanelFrame_shadow = new QGraphicsDropShadowEffect;\
frame_answerPanelFrame_shadow->setBlurRadius(20);\
frame_answerPanelFrame_shadow->setColor(Qt::black);\
frame_answerPanelFrame_shadow->setYOffset(2);\
frame_answerPanelFrame_shadow->setXOffset(-2);\
ui.answerPanelFrame->setGraphicsEffect(frame_answerPanelFrame_shadow);\
QGraphicsDropShadowEffect* frame_statisticsPanelFrame_shadow = new QGraphicsDropShadowEffect;\
frame_statisticsPanelFrame_shadow->setBlurRadius(20);\
frame_statisticsPanelFrame_shadow->setColor(Qt::black);\
frame_statisticsPanelFrame_shadow->setYOffset(2);\
frame_statisticsPanelFrame_shadow->setXOffset(-2);\
ui.statisticsPanelFrame->setGraphicsEffect(frame_statisticsPanelFrame_shadow);\
QGraphicsDropShadowEffect* frame_questionPanelFrame_shadow = new QGraphicsDropShadowEffect;\
frame_questionPanelFrame_shadow->setBlurRadius(20);\
frame_questionPanelFrame_shadow->setColor(Qt::black);\
frame_questionPanelFrame_shadow->setYOffset(2);\
frame_questionPanelFrame_shadow->setXOffset(-2);\
ui.questionPanelFrameShadow->setGraphicsEffect(frame_questionPanelFrame_shadow);\
QGraphicsDropShadowEffect* label_logo_math_shadow = new QGraphicsDropShadowEffect; \
label_logo_math_shadow->setBlurRadius(15); \
label_logo_math_shadow->setColor(Qt::black); \
label_logo_math_shadow->setOffset(0); \
ui.logo_math->setGraphicsEffect(label_logo_math_shadow);\
QGraphicsDropShadowEffect* button_submitButton_shadow = new QGraphicsDropShadowEffect; \
button_submitButton_shadow->setBlurRadius(15); \
button_submitButton_shadow->setColor(Qt::black); \
button_submitButton_shadow->setOffset(0); \
ui.submitButton->setGraphicsEffect(button_submitButton_shadow);



//插槽函数
//四种题目的创建按钮
//加
void ArithmaticExerciseQt::on_selectAddtion_clicked() {
    this->m_questionAmount = ui.questionAmountSlider->value();
    if (this->m_questionAmount > 0) {
        QuestionGenerator(ADDTION, this->m_questionAmount);

        //载入问题
        int continueIndex = 1;
        int questionsType = 0;
        if ((continueIndex = ql.LoadQuestions(&questionsType)) == -1) {
            ui.testOutput->setText("Ooch!LoadError");
        }
        else {
            char tempText[64] = "Continue from ";
            char tempIndex[8];
            _itoa(continueIndex, tempIndex, 10);
            strcat(tempText, tempIndex);
            ui.testOutput->setText(tempText);
        }
        this->LoadPanelQuestionType(questionsType);
        this->LoadQuestionMenu();
        ui.accuracyRate->setText("Accuracy Rate: 100%");
        ui.answerPanelCover->hide();
        UpdateEmotion(THINKING);
        this->LoadPanelQuestionAmount();
        ui.questionPanelStackedWidget->setCurrentIndex(2);
    }
}
//减
void ArithmaticExerciseQt::on_selectSubtraction_clicked() {
    this->m_questionAmount = ui.questionAmountSlider->value();
    if (this->m_questionAmount > 0) {
        QuestionGenerator(SUBTRACTION, this->m_questionAmount);

        //载入问题
        int continueIndex = 1;
        int questionsType = 0;
        if ((continueIndex = ql.LoadQuestions(&questionsType)) == -1) {
            ui.testOutput->setText("Ooch!LoadError");
        }
        else {
            char tempText[64] = "Continue from ";
            char tempIndex[8];
            _itoa(continueIndex, tempIndex, 10);
            strcat(tempText, tempIndex);
            ui.testOutput->setText(tempText);
        }
        this->LoadPanelQuestionType(questionsType);
        this->LoadQuestionMenu();
        ui.accuracyRate->setText("Accuracy Rate: 100%");
        ui.answerPanelCover->hide();
        UpdateEmotion(THINKING);
        this->LoadPanelQuestionAmount();
        ui.questionPanelStackedWidget->setCurrentIndex(2);
    }
}
//乘
void ArithmaticExerciseQt::on_selectMultiplication_clicked() {
    this->m_questionAmount = ui.questionAmountSlider->value();
    if (this->m_questionAmount > 0) {
        QuestionGenerator(MULTIPLICATION, this->m_questionAmount);
        
        //载入问题
        int continueIndex = 1;
        int questionsType = 0;
        if ((continueIndex = ql.LoadQuestions(&questionsType)) == -1) {
            ui.testOutput->setText("Ooch!LoadError");
        }
        else {
            char tempText[64] = "Continue from ";
            char tempIndex[8];
            _itoa(continueIndex, tempIndex, 10);
            strcat(tempText, tempIndex);
            ui.testOutput->setText(tempText);
        }
        this->LoadPanelQuestionType(questionsType);
        this->LoadQuestionMenu();
        ui.accuracyRate->setText("Accuracy Rate: 100%");
        ui.answerPanelCover->hide();
        UpdateEmotion(THINKING);
        this->LoadPanelQuestionAmount();
        ui.questionPanelStackedWidget->setCurrentIndex(2);
    }
}
//除
void ArithmaticExerciseQt::on_selectDivision_clicked() {
    this->m_questionAmount = ui.questionAmountSlider->value();
    if (this->m_questionAmount > 0) {
        QuestionGenerator(DIVISION, this->m_questionAmount);
        
        //载入问题
        int continueIndex = 1;
        int questionsType = 0;
        if ((continueIndex = ql.LoadQuestions(&questionsType)) == -1) {
            ui.testOutput->setText("Ooch!LoadError");
        }
        else {
            char tempText[64] = "Continue from ";
            char tempIndex[8];
            _itoa(continueIndex, tempIndex, 10);
            strcat(tempText, tempIndex);
            ui.testOutput->setText(tempText);
        }
        this->LoadPanelQuestionType(questionsType);
        this->LoadQuestionMenu();
        ui.accuracyRate->setText("Accuracy Rate: 100%");
        ui.answerPanelCover->hide();
        UpdateEmotion(THINKING);
        this->LoadPanelQuestionAmount();
        ui.questionPanelStackedWidget->setCurrentIndex(2);
    }
}


//关闭程序按键
void ArithmaticExerciseQt::on_closeButton_clicked() {
    if (ql.UnloadQuestions() == -1) {
        ui.testOutput->setText("Ooch!SaveError");
    }
    this->close();
}
//返回按键
void ArithmaticExerciseQt::on_backButton_clicked() {
    if (ql.UnloadQuestions() == -1) {
        ui.testOutput->setText("Ooch!SaveError");
    }
    UpdateEmotion(GREETING);
    ui.answerPanelCover->show();
    this->InitializePanel();
    ui.questionPanelStackedWidget->setCurrentIndex(0);
}


//创建新练习按键
void ArithmaticExerciseQt::on_selectNewPractice_clicked() {
    ui.questionPanelStackedWidget->setCurrentIndex(1);
}
//继续练习按键
void ArithmaticExerciseQt::on_selectContinue_clicked() {
    
    //载入问题
    int continueIndex = 1;
    int questionsType = 0;
    if ((continueIndex = ql.LoadQuestions(&questionsType)) == -1) {
        ui.testOutput->setText("Ooch!LoadError");
    }
    else {
        char tempText[64] = "Continue from ";
        char tempIndex[8];
        _itoa(continueIndex, tempIndex, 10);
        strcat(tempText, tempIndex);
        ui.testOutput->setText(tempText);
    }
    this->LoadPanelQuestionType(questionsType);
    this->LoadQuestionMenu();
    ui.accuracyRate->setText("Accuracy Rate: 100%");
    ui.answerPanelCover->hide();
    UpdateEmotion(THINKING);
    this->LoadPanelQuestionAmount();
    ui.questionPanelStackedWidget->setCurrentIndex(2);
}



void ArithmaticExerciseQt::on_selectA_clicked() {
    this->choice = SELECT_A;
    this->UpdateSelect();
}
void ArithmaticExerciseQt::on_selectB_clicked() {
    this->choice = SELECT_B;
    this->UpdateSelect();
}
void ArithmaticExerciseQt::on_selectC_clicked() {
    this->choice = SELECT_C;
    this->UpdateSelect();
}
void ArithmaticExerciseQt::on_selectD_clicked() {
    this->choice = SELECT_D;
    this->UpdateSelect();
}



void ArithmaticExerciseQt::on_submitButton_clicked() {
    switch (this->choice)
    {
    case NO_SELECT:
        return;
    case SELECT_A:
        if (rightChoice == SELECT_A) {
            ui.sA->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
            UpdateEmotion(SMILE);
            ql.UpdateProgress(TRUE);
        }
        else {
            UpdateEmotion(SAD);
            ui.sA->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(255, 0, 0);"));
            switch (rightChoice)
            {
            case 1:
                break;
            case 2:
                ui.sB->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 3:
                ui.sC->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 4:
                ui.sD->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            }
            ql.UpdateProgress(FALSE);
        }
        this->choice = CHECK_ANSWER;
        ui.selectCursor->hide();
        ui.submitButton->setText("NEXT");
        break;
    case SELECT_B:
        if (rightChoice == SELECT_B) {
            ui.sB->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
            UpdateEmotion(SMILE);
            ql.UpdateProgress(TRUE);
        }
        else {
            UpdateEmotion(SAD);
            ui.sB->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(255, 0, 0);"));
            switch (rightChoice)
            {
            case 1:
                ui.sA->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 2:
                break;
            case 3:
                ui.sC->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 4:
                ui.sD->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            }
            ql.UpdateProgress(FALSE);
        }
        this->choice = CHECK_ANSWER;
        ui.selectCursor->hide();
        ui.submitButton->setText("NEXT");
        break;
    case SELECT_C:
        if (rightChoice == SELECT_C) {
            ui.sC->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
            UpdateEmotion(SMILE);
            ql.UpdateProgress(TRUE);
        }
        else {
            UpdateEmotion(SAD);
            ui.sC->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(255, 0, 0);"));
            switch (rightChoice)
            {
            case 1:
                ui.sA->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 2:
                ui.sB->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 3:
                break;
            case 4:
                ui.sD->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            }
            ql.UpdateProgress(FALSE);
        }
        this->choice = CHECK_ANSWER;
        ui.selectCursor->hide();
        ui.submitButton->setText("NEXT");
        break;
    case SELECT_D:
        if (rightChoice == SELECT_D) {
            ui.sD->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
            UpdateEmotion(SMILE);
            ql.UpdateProgress(TRUE);
        }
        else {
            UpdateEmotion(SAD);
            ui.sD->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(255, 0, 0);"));
            switch (rightChoice)
            {
            case 1:
                ui.sA->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 2:
                ui.sB->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 3:
                ui.sC->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(65, 205, 82);"));
                break;
            case 4:
                break;
            }
            ql.UpdateProgress(FALSE);
        }
        this->choice = CHECK_ANSWER;
        ui.selectCursor->hide();
        ui.submitButton->setText("NEXT");
        break;
    case CHECK_ANSWER:
        ui.sA->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(0, 0, 0);"));
        ui.sB->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(0, 0, 0);"));
        ui.sC->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(0, 0, 0);"));
        ui.sD->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\ncolor: rgb(0, 0, 0);"));
        this->choice = 0;
        this->UpdateSelect();
        ui.submitButton->setText("CONFIRM");
        this->LoadQuestionMenu();
        break;
    case SUBMIT:
        //调用结算函数
        this->Settlement();
        break;
    }
    return;
}





//构造函数
ArithmaticExerciseQt::ArithmaticExerciseQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //绘制阴影
    UI_ADD_SHADOW_EFFECT;
    //初始化选择标记
    ui.selectCursor->hide();
    UpdateEmotion(GREETING);
    //初始化拖动条位置
    ui.questionAmountSlider->setValue(10);
    //显示日期
    struct tm* sysTime;
    time_t sysDay;
    time(&sysDay);
    sysTime = localtime(&sysDay);
    char tempStr[128] = "Date: ";
    char tempChar[16];
    _itoa(1900+sysTime->tm_year, tempChar, 10);
    strcat(tempStr, tempChar);
    strcat(tempStr, "-");
    _itoa(sysTime->tm_mon + 1, tempChar, 10);
    strcat(tempStr, tempChar);
    strcat(tempStr, "-");
    _itoa(sysTime->tm_mday, tempChar, 10);
    strcat(tempStr, tempChar);
    ui.date->setText(tempStr);
    //无边框窗口
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //初始化存储文件
    InitializeResource();
}
ArithmaticExerciseQt::~ArithmaticExerciseQt()
{
}
