#ifndef MYCALENDARWIDGET_H
#define MYCALENDARWIDGET_H

#include <QtWidgets>

#include "mylabel.h"

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    CalendarWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

public:
    void createCalendar(QDate date, qint8 sender);
    QStringList createRule(QDate date, qint8 sender);
    QColor weekdaysOrWeekendOrToday(QDate date);

public:
    bool first_time;
    QGridLayout     *calendar_grid;
    QMap<MyLabel*,qint8> map_widget,
    map_widget_delta;
    QDate current_date,
          selected_date;
    MyLabel *selected_label;
    qint8 from_who;
    QString previous_pixmap_path;

public slots:
    void chooseDay(int day);
    void onDateClick(MyLabel *label);
    void emptyDate(QDate date, QString pixmap_path);
    void fullDate(QDate date, QString pixmap_path);
    void jumpToDay(int direct);
    void jumpToMounth(int direct);
    void jumpToYear(int direct);
    void jumpToday();
    void unChooseDay();

signals:
    void returnDatePressed(QDate date);
    void returnKeyPressed(QKeyEvent *event);
    void returnCurrentLabel(MyLabel *label);

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYCALENDARWIDGET_H
