#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent)
{
    my_cursor = cursor();
}

MyLabel::MyLabel(QPixmap pixmap)
{
    MyLabel();
    setPixmap(pixmap);
}

MyLabel::MyLabel(QString file_path)
{
    MyLabel(QPixmap(file_path));
}

MyLabel::MyLabel(const QString &text, QWidget *parent, Qt::WindowFlags f) :
    QLabel(text, parent, f)
{
    MyLabel();
    setText(text);
}

void MyLabel::setMyPixmap(QString pixmap_path, QString text, QColor color)
{
    QFont font(application_font,calendar_size_font);
    QPixmap pixmap(pixmap_path);
    QPainter painter(&pixmap);
    painter.setFont(font);
    painter.setPen(color);
    painter.drawText(QRect(0,0,pixmap.width(),pixmap.height()), Qt::AlignCenter, text);
    setPixmap(pixmap);
}

void MyLabel::currentLabel(MyLabel *label)
{
    current_label = label;
}

bool MyLabel::isItOk(QMouseEvent *mouse_event)
{
    int width_l = width()/2,
        height_l= height()/2,
        mouse_x = mouse_event->pos().x(),
        mouse_y = mouse_event->pos().y();

    if ( mouse_x < width_l+width_l/2   &&
         mouse_x > width_l/2           &&
         mouse_y < height_l+height_l/2 &&
         mouse_y > width_l/2 )
    {
        return true;
    }

    return false;
}

void MyLabel::paintEinstein()
{
    einstein_label = this;

    QPixmap einstein(calendar_pixmap_einstein);
    QSize einstein_size = einstein.size();
    if ( einstein_size.width() != einstein_size.height() )
    {
        if ( einstein_size.width() > einstein_size.height() )
        {
            einstein = einstein.scaledToHeight(einstein_size.height(),Qt::SmoothTransformation);
        }
        else
        {
            einstein = einstein.scaledToWidth(einstein_size.width(),Qt::SmoothTransformation);
        }
    }

    setPixmap(einstein);
}

void MyLabel::mouseReleaseEvent(QMouseEvent *mouse_event)
{
    setCursor(my_cursor);

    if ( isItOk(mouse_event) )
    {
        if (mouse_event->button() == Qt::LeftButton)
        {
            emit MousePressed();
            emit returnLabel(this);
        }
        else
        {
            if (mouse_event->button() == Qt::RightButton)
            {
                paintEinstein();
            }
        }
    }
}

void MyLabel::mousePressEvent(QMouseEvent *mouse_event)
{
    if (mouse_event->button() == Qt::LeftButton)
    {
        if ( this == current_label || !isItOk(mouse_event) )
        {
            QCursor cursor_none= cursor();
            cursor_none.setShape(Qt::ForbiddenCursor);
            setCursor(cursor_none);
        }
        else
        {
            QCursor cursor_capture = cursor();
            cursor_capture.setShape(Qt::ClosedHandCursor);
            setCursor(cursor_capture);
        }
    }
}

void MyLabel::keyPressEvent(QKeyEvent *event)
{
    emit returnKeyPressed(event);
}
