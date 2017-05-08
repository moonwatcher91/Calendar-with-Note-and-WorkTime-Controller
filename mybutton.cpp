#include "mybutton.h"

mybutton::mybutton(QWidget *parent) :
    QPushButton(parent)
{
    main_cursor = cursor();
}

mybutton::mybutton(const QString &text, QWidget *parent)
{
    setText(text);
    setParent(parent);
    main_cursor = cursor();
}

void mybutton::mousePressEvent(QMouseEvent *event)
{
    QCursor local_cursor = cursor();
    local_cursor.setShape(Qt::ClosedHandCursor);
    setCursor(local_cursor);
    QPushButton::mousePressEvent(event);
}

void mybutton::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(main_cursor);
    QPushButton::mouseReleaseEvent(event);
}
