#include "mycalendar.h"

Calendar::Calendar(QWidget *parent) :
    QWidget(parent)
{
    qtTranslator.load("QtLanguage_ru_RU");
    qApp->installTranslator(&qtTranslator);

    date = QDate::currentDate();

    QVBoxLayout *lay_left = new QVBoxLayout;
    lay_left->setMargin(note_label_margin_minimum);

        note = new mybutton();
        note->setIcon(QIcon(QPixmap(note_pixmap)));
        note->setIconSize(QSize(icon_tool_bar_size,icon_tool_bar_size));
        note->setFixedSize(icon_tool_bar_size,icon_tool_bar_size);

            note_widget = new MyNote(this,Qt::Widget);

        worktime = new mybutton();
        worktime->setIcon(QIcon(QPixmap(work_time_pixmap)));
        worktime->setIconSize(QSize(icon_tool_bar_size,icon_tool_bar_size));
        worktime->setFixedSize(icon_tool_bar_size,icon_tool_bar_size);

            work_widget = new MyWorkTime();
            label_analysing = new QLabel();

        language = new mybutton();
        language->setText(tr("En"));
        language->setFixedSize(icon_tool_bar_size,icon_tool_bar_size);

        mybutton *setting = new mybutton();
        setting->setIcon(QIcon(QPixmap(settings_pixmap)));
        setting->setIconSize(QSize(icon_tool_bar_size,icon_tool_bar_size));
        setting->setFixedSize(icon_tool_bar_size,icon_tool_bar_size);

    lay_left->addWidget(note);
    lay_left->addWidget(worktime);
    lay_left->addStretch();
    lay_left->addWidget(language);
    lay_left->addWidget(setting);

    QWidget *widget_left = new QWidget;
    widget_left->setLayout(lay_left);
    widget_left->setFixedWidth(icon_tool_bar_size);

    QWidget *widget_calendar = new QWidget;

        QVBoxLayout *lay_calendar = new QVBoxLayout;

            date_label = new QLabel;
            date_label->setFont(QFont(application_font,normal));
            calendar = new CalendarWidget();

        lay_calendar->addWidget(date_label);
        lay_calendar->addWidget(calendar);
        lay_calendar->addStretch();

    widget_calendar->setLayout(lay_calendar);

    main_widget = new QStackedWidget;
    main_widget->addWidget(note_widget);
    main_widget->addWidget(work_widget);
    main_widget->addWidget(label_analysing);

    QSplitter *splitter = new QSplitter();
    splitter->setChildrenCollapsible(true);
    splitter->setOrientation(Qt::Horizontal);

    splitter->addWidget(widget_calendar);
    splitter->addWidget(main_widget);

    splitter->setFrameStyle(QFrame::Panel | QFrame::Plain);
    splitter->setLineWidth(1);

    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(widget_left);
    lay->addWidget(splitter);

    setLayout(lay);

    showMaximized();

    connect(note,       SIGNAL(clicked()),                this,       SLOT(noteClick()));
    connect(worktime,   SIGNAL(clicked()),                this,       SLOT(worktimeClick()));
    connect(language,   SIGNAL(clicked()),                this,       SLOT(languageClick()));
    connect(calendar,   SIGNAL(returnDatePressed(QDate)), this,       SLOT(onDateClick(QDate)));
    connect(calendar,   SIGNAL(returnKeyPressed(QKeyEvent*)),this,    SLOT(myKeyPressEvent(QKeyEvent*)));
    connect(note_widget,SIGNAL(emptyDate(QDate,QString)), calendar,   SLOT(emptyDate(QDate,QString)));
    connect(note_widget,SIGNAL(fullDate(QDate,QString)),  calendar,   SLOT(fullDate(QDate,QString)));
    connect(note_widget,SIGNAL(unChooseDay()),            calendar,   SLOT(unChooseDay()));
    connect(note_widget,SIGNAL(chooseDay(int)),           calendar,   SLOT(chooseDay(int)));
    connect(work_widget,SIGNAL(emptyDate(QDate,QString)), calendar,   SLOT(emptyDate(QDate,QString)));
    connect(work_widget,SIGNAL(fullDate(QDate,QString)),  calendar,   SLOT(fullDate(QDate,QString)));
    connect(work_widget,SIGNAL(focusToCalendar()),        calendar,   SLOT(setFocus()));

    QDir dir(QDir::currentPath()+settings_path);
    dir.mkdir(dir.path());
    QFile file(dir.absolutePath()+"/current_page");
    qint8 page;
    if (file.open(QIODevice::ReadWrite))
    {
        bool ok;
        QString current_page = file.readAll();
        file.close();
        page = current_page.toInt(&ok);
        if (!ok)
        {
            page = 0;
            writeFile(page);
        }
    }
    else
    {
        page = 0;
        file.close();
        writeFile(page);
    }

    start(page);
}

void Calendar::start(qint8 page)
{
    switch(page)
    {
    case 0: noteClick(); break;
    case 1: worktimeClick(); break;
    default: noteClick();
    }
}

void Calendar::writeFile(qint8 page)
{
    QDir dir(QDir::currentPath()+settings_path);
    dir.mkdir(dir.path());
    QFile file(dir.absolutePath()+"/current_page");
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream.setCodec(application_codec);
    stream<<QString::number(page);
    file.close();
}

void Calendar::retranslator()
{
    language->setText(tr("En"));
}

void Calendar::noteClick()
{
    writeFile(0);
    note->setEnabled(false);
    worktime->setEnabled(true);
    calendar->createCalendar(date,0);
    main_widget->setCurrentIndex(0);
    onDateClick(date);
}

void Calendar::worktimeClick()
{
    writeFile(1);
    note->setEnabled(true);
    worktime->setEnabled(false);
    calendar->createCalendar(date,1);
    main_widget->setCurrentIndex(1);
    onDateClick(date);
}

void Calendar::languageClick()
{
    if ( language->text() == "En" )
    {
        qtTranslator.load("QtLanguage_ru_RU",".");
        qApp->installTranslator(&qtTranslator);
    }
    else
    {
        qtTranslator.load("QtLanguage_en_GB",".");
        qApp->installTranslator(&qtTranslator);
    }
}

void Calendar::onDateClick(QDate date)
{
    date_label->setText(date.toString(date_view_long));

    switch(main_widget->currentIndex())
    {
        case 0:
        {
            note_widget->showNotes(date, false);
            calendar->setFocus();
        }
        break;

        case 1:
        {
            work_widget->showWorkTime(date);
            calendar->setFocus();
        }
        break;

        default: break;
    }
}

void Calendar::closeEvent(QCloseEvent *event)
{
    calendar->close();
    note_widget->close();
    emit close(4);
    QWidget::closeEvent(event);
}

void Calendar::keyPressEvent(QKeyEvent *event)
{
    myKeyPressEvent(event);
}

void Calendar::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        cursor().setShape(Qt::ClosedHandCursor);
    }
}

void Calendar::myKeyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::NoModifier)
    {
        switch(event->key())
        {
        case Qt::Key_Up:    calendar->jumpToDay(-7); break;
        case Qt::Key_Down:  calendar->jumpToDay(7); break;
        case Qt::Key_Left:  calendar->jumpToDay(-1); break;
        case Qt::Key_Right: calendar->jumpToDay(1); break;
        case Qt::Key_Delete:if (main_widget->currentIndex()==0) note_widget->deleteAllNotes(); break;
        default: QWidget::keyPressEvent(event);
        }
    }
    else
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            switch(event->key())
            {
            case Qt::Key_Up: calendar->jumpToMounth(-1); break;
            case Qt::Key_Left: calendar->jumpToMounth(-1); break;
            case Qt::Key_Down: calendar->jumpToMounth(1); break;
            case Qt::Key_Right: calendar->jumpToMounth(1); break;
            case Qt::Key_T: calendar->jumpToday(); break;
            case Qt::Key_N: if (main_widget->currentIndex()==0) note_widget->createNote(); break;
            case Qt::Key_S:
                            {
                                switch (main_widget->currentIndex())
                                {
                                case 0: note_widget->applyNote(); break;
                                case 1: work_widget->saveWorkTime(); break;
                                default: break;
                                }
                            }break;
            case Qt::Key_W:
                            {
                                switch (main_widget->currentIndex())
                                {
                                case 0: note_widget->closeNote(); break;
                                case 1: work_widget->analiseWeek(); break;
                                default: break;
                                }
                            }break;
            case Qt::Key_M: if (main_widget->currentIndex()==1) work_widget->analiseMounth(); break;
            case Qt::Key_Y: if (main_widget->currentIndex()==1) work_widget->analiseYear(); break;
            case Qt::Key_1: if (main_widget->currentIndex()!=0) noteClick(); break;
            case Qt::Key_2: if (main_widget->currentIndex()!=1) worktimeClick(); break;
            default: QWidget::keyPressEvent(event);
            }
        }
        else
        {
            if (event->modifiers() == (Qt::ShiftModifier))
            {
                switch(event->key())
                {
                case Qt::Key_Up: calendar->jumpToYear(-1); break;
                case Qt::Key_Left: calendar->jumpToYear(-1); break;
                case Qt::Key_Down: calendar->jumpToYear(1); break;
                case Qt::Key_Right: calendar->jumpToYear(1); break;
                default: QWidget::keyPressEvent(event);
                }
            }
            else
            {
                if (event->modifiers() == (Qt::AltModifier))
                {
                    switch(event->key())
                    {
                    case Qt::Key_Up: calendar->jumpToYear(-5); break;
                    case Qt::Key_Left: calendar->jumpToYear(-5); break;
                    case Qt::Key_Down: calendar->jumpToYear(5); break;
                    case Qt::Key_Right: calendar->jumpToYear(5); break;
                    default: QWidget::keyPressEvent(event);
                    }
                }
                else
                {
                    if (event->modifiers() == (Qt::ControlModifier | Qt::AltModifier))
                    {
                        switch(event->key())
                        {
                        case Qt::Key_Up: calendar->jumpToYear(-10); break;
                        case Qt::Key_Left: calendar->jumpToYear(-10); break;
                        case Qt::Key_Down: calendar->jumpToYear(10); break;
                        case Qt::Key_Right: calendar->jumpToYear(10); break;
                        case Qt::Key_F4: exit(0);
                        default: QWidget::keyPressEvent(event);
                        }
                    }
                    else
                    {
                        if (event->modifiers() == (Qt::ShiftModifier | Qt::AltModifier))
                        {
                            switch(event->key())
                            {
                            case Qt::Key_Up: calendar->jumpToYear(-100); break;
                            case Qt::Key_Left: calendar->jumpToYear(-100); break;
                            case Qt::Key_Down: calendar->jumpToYear(100); break;
                            case Qt::Key_Right: calendar->jumpToYear(100); break;
                            default: QWidget::keyPressEvent(event);
                            }
                        }
                        else
                        {
                            QWidget::keyPressEvent(event);
                        }
                    }
                }
            }
        }
    }
}

void Calendar::changeEvent(QEvent *event)
{
    if ( event->type() == QEvent::LanguageChange )
    {
        repaint();
    }

    QWidget::changeEvent(event);
}
