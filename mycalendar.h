#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QtWidgets>

#include "mynote.h"
#include "mystyle.h"
#include "mylabel.h"
#include "mybutton.h"
#include "myworktime.h"
#include "mycalendarwidget.h"

class Calendar : public QWidget
{
    Q_OBJECT

public:
   Calendar(QWidget* parent = 0);

public:
   QTranslator qtTranslator;
   MyNote *note_widget;
   MyWorkTime *work_widget;

   QLabel *date_label;

   mybutton *note;
   mybutton *worktime;
   mybutton *language;

   CalendarWidget *calendar;

   QStackedWidget *main_widget;

   QLabel *label_analysing;

   QDate date;

public:
   QWidget      *createWorktimeWidget();
   QComboBox    *createComboBox(int start, int end, int width);

public:
   void start(qint8 page);
   void writeFile(qint8 page);
   void retranslator();

private slots:
   void noteClick();
   void worktimeClick();
   void languageClick();

   void onDateClick(QDate date);

   void myKeyPressEvent(QKeyEvent *event);

signals:
    void close(int widget_number);
    void calendarEvent(QString event);

protected:
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYCALENDAR_H
