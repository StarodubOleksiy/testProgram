#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QApplication>
#include <QtGui>
#include <QLabel>
#include <QWidget>
#include <QResizeEvent>
#include <QApplication>
#include <QSharedPointer>
#include <stdexcept>

#define USE_SMART_POINTERS
#define NumberOfQuestions 80

namespace Ui {
class MainWindow;
}

class DataFileError: public std::runtime_error
{
public:

 DataFileError(const QString& s): std::runtime_error(s.toStdString()) {}

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
 void work_finish();
 void actionQuit();

private slots:
    void on_pushButton_clicked();
    void on_finish_Work();
    void on_actionQuit_triggered();
    void slotButtonClicked();

private:
    enum isPictureIsPresent {No, Yes};
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *bar);
    QVector<QString> filenames;
    QVector<QString> picturenames;
    QVector<int> previousNumbersRadioButtons;
    int counterClicks;
    int checkAnswer;
    int rightAnswer;
    void setAnswersInLabels();
    void setRadioButtons(int temp, QTextStream &in);
    void isFileRight(const QString rightFileName);
    void deleteRadioButtons();
    void insertPictureInLabel(QTextStream &in);
    void splitLongString(QString &SplittedStr);
    unsigned int numberRightAnswers;
    unsigned int numberWrongAnswers;
    //const int NumberOfQuestions = 8;
    QRadioButton *buttons[10];
   bool IsPicturePresent;
   QString readFileLine;
   QPixmap img;


protected:
   void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
