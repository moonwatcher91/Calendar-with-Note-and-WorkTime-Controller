#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QtWidgets>

class MyListView : public QListView
{
    Q_OBJECT

public:
    MyListView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public:
    void deleteAllNotes();

signals:
    void myIndex(const QModelIndex & index);
    void onCtrlPlusS();
    void onCtrlPlusN();
    void onCtrlPlusC(const QModelIndexList & index_list);
    void onCtrlPlusV(const QModelIndexList & index_list);
    void onEnterKeyPressed(const QModelIndex & index);
    void onDoubleMousePressed(const QModelIndex & index);
    void onDeleteKeyPressed(const QModelIndexList & index_list);
    void onRightMouseButtonClick(QMouseEvent *event,const QModelIndex & index);
};

#endif // MYLISTVIEW_H
