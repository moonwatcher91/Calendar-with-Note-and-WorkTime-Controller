#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QCursor>
#include <QMouseEvent>
#include <QPushButton>

class mybutton : public QPushButton
{
    Q_OBJECT

public:
    explicit mybutton(QWidget *parent = 0);
    explicit mybutton(const QString &text, QWidget *parent=0);

public:
    QCursor main_cursor;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYBUTTON_H
