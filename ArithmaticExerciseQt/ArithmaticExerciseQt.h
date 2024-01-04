#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ArithmaticExerciseQt.h"
#include <qwidget.h>
#include "c_LoadQuestion.h"
#include <Windows.h>
#include "qpropertyanimation.h"
#include "QGraphicsOpacityEffect"

enum {
    NO_SELECT, SELECT_A, SELECT_B, SELECT_C, SELECT_D, CHECK_ANSWER, SUBMIT
};

enum {
    GREETING, SMILE, THINKING, SAD
};

class ArithmaticExerciseQt : public QMainWindow
{
    Q_OBJECT

public:
    ArithmaticExerciseQt(QWidget *parent = nullptr);
    ~ArithmaticExerciseQt();
    int m_questionAmount = -1;
    int choice = NO_SELECT;
    int rightChoice = 0;

private:
    Ui::ArithmaticExerciseQtClass ui;
    struct QuestionLoader ql;

    void LoadQuestionMenu() {
        //通过API获取下一问题信息
        char questionText[256] = { 0 };
        double options[4] = { 0 };
        int ret = -1;
        if ((ret = ql.NextQuestion(questionText, options, &rightChoice)) == 1) {
            ui.question->setText(questionText);
            //更新选项
            ui.sA->setText(QString::number(options[0], 'g', 2));
            ui.sB->setText(QString::number(options[1], 'g', 2));
            ui.sC->setText(QString::number(options[2], 'g', 2));
            ui.sD->setText(QString::number(options[3], 'g', 2));
            //更新正确率
            char tempStr[64] = "Accuracy Rate: ";
            char tempChar[8];
            _itoa(round(((double)ql.correctQuantity / (double)ql.completeProgress) * 10000) / 100, tempChar, 10);
            strcat(tempStr, tempChar);
            strcat(tempStr, "%");
            ui.accuracyRate->setText(tempStr);
        }
        else if (ret == 0) {
            //所有问题均作答后NextQuestion会返回0，此处改变提交 按键功能->跳转结算界面
            ui.question->setText("Submit\n  ↘");
            UpdateEmotion(GREETING);
            ui.submitButton->setText("SUBMIT");
            choice = SUBMIT;
        }
    }

    void UpdateSelect() {
        switch (choice)
        {
        case NO_SELECT:
            ui.selectCursor->hide();
            ui.sad->hide();
            ui.smile->hide();
            ui.thinking->show();
            break;
        case SELECT_A:
            ui.selectCursor->setGeometry(55, 77, 41, 41);
            ui.selectCursor->show();
            break;
        case SELECT_B:
            ui.selectCursor->setGeometry(230, 77, 41, 41);
            ui.selectCursor->show();
            break;
        case SELECT_C:
            ui.selectCursor->setGeometry(415, 77, 41, 41);
            ui.selectCursor->show();
            break;
        case SELECT_D:
            ui.selectCursor->setGeometry(600, 77, 41, 41);
            ui.selectCursor->show();
            break;
        default:
            ui.selectCursor->hide();
            break;
        }
        return;
    }

    void UpdateEmotion(int emotion) {
        ui.sad->hide();
        ui.smile->hide();
        ui.thinking->hide();
        ui.statisticsPanelCover->hide();
        switch (emotion)
        {
        case GREETING:
            ui.statisticsPanelCover->show();
            break;
        case SMILE:
            ui.smile->show();
            break;
        case THINKING:
            ui.thinking->show();
            break;
        case SAD:
            ui.sad->show();
            break;
        }
        return;
    }

    void InitializePanel() {
        ui.accuracyRate->setText("Accuracy Rate: qwq");
        ui.questionsAmount->setText("Questions Amount: qwp");
        ui.practiceMode->setText("Practice Mode: pwp");
    }

    void LoadPanelQuestionAmount() {
        //显示Question Amount:
        char tempStr[128] = "Questions Amount: ";
        char tempChar[32];
        _itoa(m_questionAmount, tempChar, 10);
        strcat(tempStr, tempChar);
        ui.questionsAmount->setText(tempStr);
    }

    void LoadPanelQuestionType(int type) {
        switch (type)
        {
        case 1:
            ui.practiceMode->setText("Practice Mode : Addtion");
            break;
        case 2:
            ui.practiceMode->setText("Practice Mode : Subtraction");
            break;
        case 3:
            ui.practiceMode->setText("Practice Mode : Multiplication");
            break;
        case 4:
            ui.practiceMode->setText("Practice Mode : Division");
            break;
        }
    }

    void ShowPrize(int point) {
        ui.level1->hide();
        ui.level2->hide();
        ui.level3->hide();
        switch (point)
        {
        case 0:
        case 1:
            ui.level3->show();
            break;
        case 2:
            ui.level2->show();
            break;
        case 3:
            ui.level1->show();
            break;
        }
    }

    void Settlement() {
        ql.UnloadQuestions();
        char tempStr[128];
        int accRate = round(((double)ql.correctQuantity / (double)ql.completeProgress) * 100);
        _itoa(accRate, tempStr, 10);
        strcat(tempStr, "%");
        ui.settleAccuracyRate->setText(tempStr);
        this->InitializePanel();
        this->ShowPrize((int)(accRate / 30));
        ui.answerPanelCover->show();
        UpdateEmotion(GREETING);
        ui.questionPanelStackedWidget->setCurrentIndex(3);
    }

private slots:
    void on_selectAddtion_clicked();
    void on_selectSubtraction_clicked();
    void on_selectMultiplication_clicked();
    void on_selectDivision_clicked();
    void on_closeButton_clicked();
    void on_submitButton_clicked();
    void on_selectNewPractice_clicked();
    void on_selectContinue_clicked();
    void on_backButton_clicked();
    void on_selectA_clicked();
    void on_selectB_clicked();
    void on_selectC_clicked();
    void on_selectD_clicked();
};
