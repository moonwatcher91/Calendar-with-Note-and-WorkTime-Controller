#include "mylistview.h"

MyListView::MyListView(QWidget *parent) :
    QListView(parent)
{
    setSelectionMode(ExtendedSelection);
}

void MyListView::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::NoModifier)
    {
        switch(event->key())
        {
        case Qt::Key_Delete: emit onDeleteKeyPressed(selectedIndexes());break;
        case Qt::Key_Return: emit onEnterKeyPressed(currentIndex());break;
        default: QListView::keyPressEvent(event);
        }
    }
    else
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            switch(event->key())
            {
            case Qt::Key_C: emit onCtrlPlusC(selectedIndexes()); break;
            case Qt::Key_V: emit onCtrlPlusV(selectedIndexes()); break;
            case Qt::Key_A: selectAll(); break;
            case Qt::Key_S: emit onCtrlPlusS(); break;
            case Qt::Key_N: emit onCtrlPlusN(); break;
            default: QListView::keyPressEvent(event);
            }
        }
        else
        {
            QListView::keyPressEvent(event);
        }
    }

    emit myIndex(currentIndex());
}

void MyListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        emit onRightMouseButtonClick(event,currentIndex());
    }
    else
    {
        QListView::mousePressEvent(event);
        emit myIndex(currentIndex());
    }
}

void MyListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->modifiers() == Qt::NoModifier)
    {
        emit onDoubleMousePressed(currentIndex());
        emit myIndex(currentIndex());
    }
}

void MyListView::deleteAllNotes()
{
    emit onDeleteKeyPressed(selectedIndexes());
}
