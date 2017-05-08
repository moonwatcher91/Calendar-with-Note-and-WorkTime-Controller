#ifndef MYSTYLE_H
#define MYSTYLE_H

#include <QtWidgets>

#define application_font            "Arial"
#define application_codec           "UTF-8"

#define note_path                   "/system_note"
#define time_work_path              "/system_timework"
#define settings_path               "/system_settings"

#define minimum_widget_width        100

#define normal                      20

#define icon_tool_bar_size          50

#define note_label_lenght           50
#define note_label_margin_minimum   0
#define note_label_margin_small     5
#define note_pixmap                 ":/note.png"

#define combo_box_width             45

#define label_hight                 25

#define calendar_pixmap_1           ":/mark_1_1.png"
#define calendar_pixmap_2           ":/mark_1_2.png"
#define calendar_pixmap_3           ":/mark_1_3.png"
#define calendar_pixmap_4           ":/mark_1_4.png"
#define calendar_pixmap_5           ":/mark_1_5.png"
#define calendar_pixmap_einstein    ":/einstein.png"

#define calendar_size_font          75
#define calendar_fixed_size         75
const QColor calendar_today         = Qt::red;
const QColor calendar_weekdays      = Qt::black;
const QColor calendar_weekend       = Qt::darkGreen;

#define work_time_pixmap            ":/work.png"

#define settings_pixmap            ":/gear.png"

#define path_day                    "d"
#define path_year                   "yyyy"
#define path_mounth                 "M"
#define path_day_mounth_year        "d.M.yyyy"
#define path_mounth_year            "M.yyyy"
#define date_view                   "dd.MM.yy"
#define date_view_long              "yyyy MMMM"
#define time_view_other             "hh.mm"

#define work_time_hour_duration     8
#define work_time_minute_duration   45
#define work_time_hour_start        9
#define work_time_minute_start      0
#define work_time_hour_finish       17
#define work_time_minute_finish     45

#endif // MYSTYLE_H
