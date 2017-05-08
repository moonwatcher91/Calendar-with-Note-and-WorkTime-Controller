#ifndef MYNOTE_H
#define MYNOTE_H

#include <QtWidgets>

#include <functional>
#include <QtConcurrent/QtConcurrent>

#include "mystyle.h"
#include "mybutton.h"
#include "mylistview.h"

class MyNote : public QWidget
{
    Q_OBJECT

public:
    MyNote(QWidget* parent = 0, Qt::WindowFlags f = 0);

public:
    QWidget* createLeftSide();
    QWidget* createRightSide();
    void showNotes(QDate date, bool enable);
    void openNameDataNote(QDate date);
    bool onTextChanged(QString new_text);
    void onStartAddNote(const QFileInfoList &list);
    void ctrlCStart(const QModelIndexList & index_list);
    void onStartDeleteNote(const QModelIndexList &index_list);

public:
    QDir                dir;
    bool                date_time,
                        all_files,
                        watcher_is_working;

    int                 count_row,
                        change_row,
                        current_row;

    QString             current_path,
                        old_name,
                        label_name_current_date_name;

    QWidget             *widget_right,
                        *widget_left;
    QLabel              *label_date,
                        *label_time,
                        *label_info;

    QFileInfoList       list_ctrl_c;
    MyListView          *note_list;
    QDate               current_date;
    mybutton            *button_save;
    QTextEdit           *textedit_note;
    QLineEdit           *edit_file_name;
    QStringListModel    *note_listmodel;
    QStringList         full_note_name_list,
                        add_dir_path;
    QComboBox           *box;

public slots:
    void ctrlV();
    void applyNote();
    void closeNote();
    void createNote();
    void ctrlCFinish();
    void deleteCurrent();
    void deleteAllNotes();
    void updateDateTime();
    void onFinishAddNote();
    void changeCalendarDay(const QModelIndex & index);
    void onFinishDeleteNote();
    void finishOpenNameDataNote();
    void changeNotesVisibleOption(int index);
    void chooseNote(const QModelIndex & index);
    void ctrlC(const QModelIndexList & index_list);
    void deleteNoteKey(const QModelIndexList & index_list);
    void rightMouseButtonClicK(QMouseEvent *event,const QModelIndex & index);

public:
    QFutureWatcher<void> *watcher_start;
    QFutureWatcher<void> *watcher_delete;
    QFutureWatcher<void> *watcher_ctrlC;
    QFutureWatcher<void> *watcher_ctrlV;

signals:
    void fullDate(QDate date,QString pixmap_path);
    void emptyDate(QDate date,QString pixmap_path);
    void unChooseDay();
    void chooseDay(int day);
};

#endif // MYNOTE_H
