#ifndef MYLABLE_H
#define MYLABLE_H

#include <QtWidgets>
#include "mystyle.h"

class MyLabel : public QLabel
{
    Q_OBJECT

public:
    MyLabel(QWidget *parent = 0);
    MyLabel(QPixmap pixmap);
    MyLabel(QString file_path);
    MyLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);

public:
    bool isItOk(QMouseEvent *mouse_event);
    void paintEinstein();

public:
    QCursor my_cursor;
    MyLabel *current_label;
    MyLabel *einstein_label;

public slots:
    void setMyPixmap(QString pixmap_path, QString text, QColor color);
    void currentLabel(MyLabel *label);

protected:
    void mouseReleaseEvent(QMouseEvent *mouse_event);
    void mousePressEvent(QMouseEvent *mouse_event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void MousePressed();
    void returnLabel(MyLabel *label);
    void returnKeyPressed(QKeyEvent *event);
};

#endif // MYLABLE_H
