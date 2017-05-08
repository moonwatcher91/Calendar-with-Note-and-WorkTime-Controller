#ifndef MYWORKTIME_H
#define MYWORKTIME_H

#include <QtWidgets>

#include "mystyle.h"
#include "mybutton.h"

class MyWorkTime : public QWidget
{
    Q_OBJECT

public:
    MyWorkTime(QWidget *parent = 0, Qt::WindowFlags f = 0);

public:
    QSpinBox *createSpinBox(int min, int max, int step, int width_size);
    void showWorkTime(QDate date);
    void showWorkFile();
    QString createText();
    QTime timeDiscrepansy(const QTime &t1,const QTime &t2);
    void outputInformation(QString information, int amount_days, QDateTime dt1, QDateTime dt2);
    void analyseWeekMounth(QDateTime &date_we_have, QDateTime &date_we_need, int &readable_days, QDir dir_to_analyse, QDate date, int start, int end);
    void resetAll();

private Q_SLOTS:
    void refreshTime();

public Q_SLOTS:
    void saveWorkTime();
    void analiseWeek();
    void analiseMounth();
    void analiseYear();

public:
    QFile file;
    QDir dir;
    QString current_path;
    QDate current_date;
    QSpinBox* box_work_hour_start;
    QSpinBox* box_work_minute_start;
    QSpinBox* box_work_hour_finish;
    QSpinBox* box_work_minute_finish;
    QSpinBox* box_work_hour;
    QSpinBox* box_work_minute;
    QSpinBox* box_work_hour_final;
    QSpinBox* box_work_minute_final;
    mybutton* save;
    QLabel*   label_work_date;

signals:
    void fullDate(QDate date,QString pixmap_path);
    void emptyDate(QDate date,QString pixmap_path);
    void focusToCalendar();
};

#endif // MYWORKTIME_H
