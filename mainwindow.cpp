#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),counterClicks(0),
    numberRightAnswers(0),numberWrongAnswers(0)
{
    ui->setupUi(this);
    ui->label_2->setText("Ви збираєтесь почати тестування по С++ яке містить 80 питань");
    ui->label_2->setMinimumSize(400,50);
    ui->label_2->setMaximumSize(400,50);
    ui->label->setText("Для початку тесту натисніть на кнопку Почати");
    ui->label->setMinimumSize(100,100);
    ui->label->setMaximumSize(400,400);
    ui->pushButton->setText("Почати");
     for(int i = 0; i < 10; ++i)
      buttons[i]= NULL;
     for(int i = 0; i < NumberOfQuestions; ++i)
    {
        QString temp;
        temp.setNum(i);
        temp.append(".txt");
        filenames.push_back(temp);
    }
    for(int i = 0; i < NumberOfQuestions; ++i)
    {
        qDebug()<<filenames[i];
    }
    picturenames.push_back("1.jpg");
    picturenames.push_back("2.jpg");
    picturenames.push_back("3.jpg");
    picturenames.push_back("4.jpg");
    picturenames.push_back("5.jpg");
    picturenames.push_back("6.jpg");
    picturenames.push_back("7.jpg");
    picturenames.push_back("8.jpg");
    picturenames.push_back("9.jpg");
    picturenames.push_back("10.jpg");
    picturenames.push_back("11.jpg");
    picturenames.push_back("12.jpg");
    picturenames.push_back("13.jpg");
    picturenames.push_back("14.jpg");
    picturenames.push_back("15.jpg");
    picturenames.push_back("16.jpg");
    picturenames.push_back("17.jpg");
    picturenames.push_back("18.jpg");
    picturenames.push_back("19.jpg");
    picturenames.push_back("20.jpg");
    picturenames.push_back("21.jpg");
    picturenames.push_back("22.jpg");
    picturenames.push_back("23.jpg");

connect(this, SIGNAL(work_finish()),this, SLOT(on_finish_Work()));
connect(this, SIGNAL(actionQuit()),this, SLOT(on_actionQuit_triggered()));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    double w_ration = static_cast<double>(event->size().height())/event->oldSize().height();
    double h_ration = static_cast<double>(event->size().width())/event->oldSize().width();
   int w = ui->label->width()*w_ration;
   int h = ui->label->height()*h_ration;
   if(ui->label->pixmap() )
    {
// Uncomment line below to see bad scaling effects.
// #define BAD_SCALING
#ifndef BAD_SCALING
 ui->label->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio) );
#else
 lui->label->( ui->label->pixmap()->scaled(w,h,Qt::KeepAspectRatio) );
#endif
    }
   }


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAnswersInLabels()
{
    if(rightAnswer == checkAnswer)
    {
        ui->label_2->setStyleSheet("QLabel { background-color : green }");
        ui->label_2->setText(" Відповідь правильна");
        numberRightAnswers++;
    } else
    {
        ui->label_2->setStyleSheet("QLabel { background-color : red }");
        ui->label_2->setText(" Відповідь неправильна");
        numberWrongAnswers++;
    }

}

void MainWindow::closeEvent(QCloseEvent *bar)
{
    emit actionQuit();
    // If we are there --- user chose to ignore exit button.
    bar->ignore();
}

void MainWindow::on_actionQuit_triggered()
{
    QMessageBox quitMsg;
    quitMsg.setWindowTitle("Діалогове вікно виходу з програми");
    quitMsg.setText("Ви справді хочете вийти з програми ?");
    quitMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (quitMsg.exec() == QMessageBox::Yes)
        QApplication::instance()->quit();
    else
        return;
}

void MainWindow::on_finish_Work()
{
    this->setWindowTitle("Кінець тесту");
    QString finalString("Тестування завершене.\n");
    QString rghtAns;
    rghtAns.setNum(numberRightAnswers);
    rghtAns.insert(0,"Кількість правильних відповідей : ");
    float statistics = 100/(static_cast<float>(NumberOfQuestions)/static_cast<float>(numberRightAnswers));
    QString statisticString;
    statisticString.setNum(statistics);
    statisticString.append("%\n");
    QString wrgAns;
    wrgAns.setNum(numberWrongAnswers);
     wrgAns.insert(0,"Кількість неправильних відповідей : ");
    finalString.append(rghtAns+"\n");
    finalString.append(statisticString);
    finalString.append(wrgAns+"\n");
    ui->label->setText(finalString);
    ui->pushButton->setEnabled(false);

}

void MainWindow::deleteRadioButtons()
{
    for(int i = 0; i < previousNumbersRadioButtons[counterClicks-1]; ++i)
         {
     ui->verticalLayout->removeWidget(buttons[i]);
     delete buttons[i];
         }

}

void MainWindow::insertPictureInLabel(QTextStream &in)
{
    qDebug()<<QDir::currentPath();
    readFileLine = in.readLine();
    qDebug()<<readFileLine;
    img.load(picturenames[readFileLine.toInt()]);
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui->label->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));

}
void MainWindow::splitLongString(QString &SplittedStr)
{
    QStringList list = SplittedStr.split("~");
    SplittedStr.clear();
    for(int i = 0; i < list.size(); ++i )
     SplittedStr.append(list[i]+"\n");

}

void MainWindow::setRadioButtons(int temp, QTextStream &in)
{
    if(temp < 1 || temp > 9 )
        throw DataFileError("Неправильний формат чисел в файлі "+filenames[counterClicks]);
    for(int i = 0; i < temp ; ++i)
    {
      buttons[i]  = new  QRadioButton();
      readFileLine = in.readLine();
      if(readFileLine.contains("~")) //Для розбиття дуже  довгого рядка
      {
          splitLongString(readFileLine);
      }
      buttons[i]->setText(readFileLine);
      connect(buttons[i], SIGNAL(clicked()), SLOT(slotButtonClicked()));
      ui->verticalLayout->addWidget(buttons[i]);
    }

}

void MainWindow::isFileRight(const QString rightFileName)
{
    if (rightFileName != "1234567890RightFile")
    throw DataFileError("Файл "+filenames[counterClicks]+" невірний");
}
void MainWindow::on_pushButton_clicked()
{
    QString titlestring;
    titlestring.setNum(counterClicks+1);
   this->setWindowTitle("Питання "+titlestring);
     ui->pushButton->setText("Далі");
    ui->pushButton->setEnabled(false);
    if(counterClicks >= NumberOfQuestions)
    {
        setAnswersInLabels();
        deleteRadioButtons();
        emit on_finish_Work();
        qDebug()<<"End ";
        return;
          } else {
    QFile file(filenames[counterClicks]);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file "));
        return;
    }
    QTextStream in(&file);
    readFileLine = in.readLine();
    try
    {
    isFileRight(readFileLine);
    readFileLine = in.readLine();
    int checkInsertPicture = readFileLine.toInt();
    qDebug()<<checkInsertPicture;
    if(checkInsertPicture == Yes)
    {
      insertPictureInLabel(in);
     } else
    {
     readFileLine = in.readLine();
     if(readFileLine.contains("~")) //Для розбиття дуже  довгого рядка
     {
         splitLongString(readFileLine);
     }
     ui->label->setText(readFileLine);
    }
    readFileLine = in.readLine();
    if (counterClicks > 0)
    {
    deleteRadioButtons();
    setAnswersInLabels();
    }
    int temp = readFileLine.toInt();
    previousNumbersRadioButtons.push_back(temp);
    setRadioButtons(temp, in);
    } catch(DataFileError error)
    {
        QMessageBox quitMsg;
        quitMsg.setWindowTitle("Error open file!");
        quitMsg.setText(QString(error.what())+" Програма буде закрита");
        if (quitMsg.exec() == QMessageBox::Ok)
                QApplication::instance()->quit();
        }
       readFileLine = in.readLine();
      rightAnswer = readFileLine.toInt();
      qDebug()<<"rightAnswer = "<<rightAnswer;
    qDebug()<< "counterClicks = " <<counterClicks++;
    }
}


void MainWindow::slotButtonClicked()
{
ui->pushButton->setEnabled(true);
    if(buttons[0]->isChecked()) {
        checkAnswer = 1;
        qDebug()<<"checkAnswer = "<<checkAnswer;
    }
    else if(buttons[1]->isChecked()) {
        checkAnswer = 2;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    }
    else if(buttons[2]->isChecked()) {
        checkAnswer = 3;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    }
    else if(buttons[3]->isChecked()) {
        checkAnswer = 4;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    }
    else if(buttons[4]->isChecked()) {
        checkAnswer = 5;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    }
    else if(buttons[5]->isChecked()) {
        checkAnswer = 6;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    }
    else if(buttons[6]->isChecked()) {
        checkAnswer = 7;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    }
    else if(buttons[7]->isChecked()) {
        checkAnswer = 8;
        qDebug()<<"checkAnswer = "<<checkAnswer;
    }
    else if(buttons[8]->isChecked()) {
        checkAnswer = 9;
        qDebug()<<"checkAnswer = "<<checkAnswer;;
    } else qDebug()<<"Виберіть варіант відповіді";

}
