#include "mynote.h"

MyNote::MyNote(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent,f)
{
    all_files = false;
    watcher_is_working = false;

    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *v_boxlayout = new QVBoxLayout;

    label_info = new QLabel(tr("Wait please"));
    label_info->setMaximumHeight(label_hight);
    label_info->setMargin(note_label_margin_minimum);

    widget_left = createLeftSide();
    widget_left->setMinimumWidth(minimum_widget_width);

    widget_right = createRightSide();
    widget_right->setMinimumWidth(minimum_widget_width);

    QSplitter *splitter = new QSplitter();
    splitter->setChildrenCollapsible(false);
    splitter->setOrientation(Qt::Horizontal);

    splitter->addWidget(widget_left);
    splitter->addWidget(widget_right);

    v_boxlayout->addWidget(label_info);
    v_boxlayout->addWidget(splitter);

    setLayout(v_boxlayout);

    widget_left->setEnabled(false);
    widget_right->setEnabled(false);

    date_time = true;
}

QWidget* MyNote::createLeftSide()
{
    QVBoxLayout *v_boxlayout    = new QVBoxLayout;

    note_listmodel = new QStringListModel();
    note_listmodel->setStringList(QStringList(tr("Wait please")));

    note_list = new MyListView();
    connect(note_list,SIGNAL(onDoubleMousePressed(QModelIndex)),this,SLOT(chooseNote(QModelIndex)));
    connect(note_list,SIGNAL(onEnterKeyPressed(QModelIndex)),this,SLOT(chooseNote(QModelIndex)));
    connect(note_list,SIGNAL(onDeleteKeyPressed(QModelIndexList)),this,SLOT(deleteNoteKey(QModelIndexList)));
    connect(note_list,SIGNAL(onRightMouseButtonClick(QMouseEvent*,QModelIndex)),SLOT(rightMouseButtonClicK(QMouseEvent*,QModelIndex)));
    connect(note_list,SIGNAL(onCtrlPlusC(QModelIndexList)),this,SLOT(ctrlC(QModelIndexList)));
    connect(note_list,SIGNAL(onCtrlPlusV(QModelIndexList)),this,SLOT(ctrlV()));
    connect(note_list,SIGNAL(onCtrlPlusS()),this,SLOT(applyNote()));
    connect(note_list,SIGNAL(onCtrlPlusN()),this,SLOT(createNote()));
    connect(note_list,SIGNAL(myIndex(QModelIndex)),this,SLOT(changeCalendarDay(QModelIndex)));
    note_list->setModel(note_listmodel);

    mybutton *button_create = new mybutton(tr("Create"));

    button_create->setFixedHeight(2*label_hight);
    connect(button_create,SIGNAL(clicked()),this,SLOT(createNote()));

        box = new QComboBox;
        box->addItem(tr("Show notes for a day"));
        box->addItem(tr("Show notes for a mounth"));
        box->setCurrentIndex(0);
        connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(changeNotesVisibleOption(int)));

    v_boxlayout->addWidget(box);
    v_boxlayout->addWidget(note_list);
    v_boxlayout->addWidget(button_create);

    QWidget *widget = new QWidget();
    widget->setLayout(v_boxlayout);

    return widget;
}

QWidget* MyNote::createRightSide()
{
    QVBoxLayout *v_boxlayout        = new QVBoxLayout;
    QHBoxLayout *h_boxlayout_name   = new QHBoxLayout;
    QHBoxLayout *h_boxlayout_date   = new QHBoxLayout;
    QHBoxLayout *h_boxlayout_time   = new QHBoxLayout;
    QHBoxLayout *h_boxlayout_button = new QHBoxLayout;

    mybutton *button_delete = new mybutton(tr("Delete"));
    button_delete->setFixedHeight(label_hight);
    connect(button_delete,SIGNAL(clicked()),this,SLOT(deleteCurrent()));

    button_save = new mybutton(tr("Save"));
    button_save->setFixedHeight(label_hight);
    connect(button_save,SIGNAL(clicked()),this,SLOT(applyNote()));

    mybutton *button_close = new mybutton(tr("Close"));
    button_close->setFixedHeight(label_hight);
    connect(button_close,SIGNAL(clicked()),this,SLOT(closeNote()));

    textedit_note = new QTextEdit();
    textedit_note->setPlaceholderText(tr("Hello, it is your record, click on some record twice, or create new"));

    QLabel *label_name = new QLabel(tr("name:"));

    label_name->setFixedWidth(note_label_lenght);
    label_name->setMargin(note_label_margin_small);

    edit_file_name = new QLineEdit();
    edit_file_name->setPlaceholderText(tr("note name"));

    h_boxlayout_name->addWidget(label_name);
    h_boxlayout_name->addWidget(edit_file_name);

    QLabel *label_date_time = new QLabel(tr("Last change"));
    label_date_time->setMargin(note_label_margin_small);

    QLabel *label_date_const = new QLabel(tr("date:"),0,0);
    label_date_const->setFixedWidth(note_label_lenght);
    label_date_const->setMargin(note_label_margin_small);

    label_date = new QLabel(QDate::currentDate().toString());

    QLabel   *label_time_const = new QLabel(tr("time"),0,0);
    label_time_const->setFixedWidth(note_label_lenght);
    label_time_const->setMargin(note_label_margin_small);

    label_time = new QLabel(QTime::currentTime().toString());

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDateTime()));
    timer->start(1000);

    v_boxlayout->addLayout(h_boxlayout_name);

    v_boxlayout->addWidget(label_date_time);

    h_boxlayout_date->addWidget(label_date_const);
    h_boxlayout_date->addWidget(label_date);

    v_boxlayout->addLayout(h_boxlayout_date);

    h_boxlayout_time->addWidget(label_time_const);
    h_boxlayout_time->addWidget(label_time);

    v_boxlayout->addLayout(h_boxlayout_time);

    v_boxlayout->addWidget(textedit_note);

    h_boxlayout_button->addWidget(button_delete);
    h_boxlayout_button->addWidget(button_save);
    h_boxlayout_button->setMargin(note_label_margin_minimum);

    v_boxlayout->addLayout(h_boxlayout_button);
    v_boxlayout->addWidget(button_close);

    QWidget *widget = new QWidget();
    widget->setLayout(v_boxlayout);

    return widget;
}

void MyNote::showNotes(QDate date, bool enable)
{
    if ( !watcher_is_working )
    {
        watcher_is_working = true;

        closeNote();
        widget_left->setEnabled(false);

        current_date = date;

        all_files = enable;

        label_name_current_date_name = tr("date:") + current_date.toString(path_day_mounth_year);

        full_note_name_list.clear();
        add_dir_path.clear();

        watcher_start = new QFutureWatcher<void>;
        QFuture<void> future_name = QtConcurrent::run(std::mem_fn(&MyNote::openNameDataNote),this,date);
        connect(watcher_start, SIGNAL(finished()),
                this,SLOT(finishOpenNameDataNote()));
        watcher_start->setFuture(future_name);
    }
}

void MyNote::openNameDataNote(QDate date)
{
    if ( all_files )
    {
        note_list->setSelectionMode(QAbstractItemView::SingleSelection);

        emit unChooseDay();

        current_path = QDir::currentPath()+note_path+"/"+date.toString(path_mounth_year);
        dir.setPath(current_path);

        QStringList info_list = dir.entryList(QStringList(), QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        int info_list_i = info_list.size();
        if ( info_list_i > 0 )
        {
            for ( int i=0; i<info_list_i; i++ )
            {
                QDir local_dir(current_path + "/" + info_list.at(i));
                QStringList local_list = local_dir.entryList(QStringList(), QDir::Files, QDir::Name);
                for (int j=0;j<local_list.size();j++)
                {
                    add_dir_path.append("/" + info_list.at(i));
                }
                full_note_name_list.append(local_list);
            }
        }
    }
    else
    {
        note_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

        box->setCurrentIndex(0);

        current_path = QDir::currentPath()+note_path+"/"+date.toString(path_mounth_year)+"/"+date.toString(path_day);
        dir.setPath(current_path);
        if (dir.exists())
        {
            full_note_name_list  = dir.entryList(QStringList() << "*.txt", QDir::Files, QDir::Time);

            if ( full_note_name_list.size() == 0 )
            {
                dir.rmpath(current_path);
                emit emptyDate(date,calendar_pixmap_2);
            }
            else
            {
                emit fullDate(date,calendar_pixmap_1);
            }
        }
        else
        {
            emit emptyDate(date,calendar_pixmap_2);
        }
    }
}

void MyNote::finishOpenNameDataNote()
{
    note_listmodel->setStringList(full_note_name_list);
    note_list->setModel(note_listmodel);

    widget_left->setEnabled(true);

    count_row = full_note_name_list.count();

    if ( all_files )
    {
        label_info->setText(tr("Record count ") + QString::number(count_row));
    }
    else
    {
        label_info->setText(tr("Record count") + QString::number(count_row) + " " + label_name_current_date_name);
    }

    watcher_start->cancel();

    watcher_is_working = false;
}

void MyNote::updateDateTime()
{
    if (date_time)
    {
        QDate qdate = QDate::currentDate();
        label_date->setText(qdate.toString());

        QTime qtime = QTime::currentTime();
        label_time->setText(qtime.toString());
    }
}

void MyNote::chooseNote(const QModelIndex &index)
{
    if (index.isValid())
    {
        date_time = false;

        int row = index.row();

        if ( add_dir_path.size() > 0 )
        {
            dir.setPath(current_path+add_dir_path.at(row));
        }

        QFileInfo info = dir.entryInfoList(QStringList()<<full_note_name_list.at(row)).at(0);

        QString path = info.absoluteFilePath();
        QFile file(path);

        if (file.exists() && file.open(QIODevice::ReadWrite))
        {
            QString text = file.readAll();
            file.close();

            old_name = info.baseName();
            edit_file_name->setText(old_name);

            label_date->setText(info.lastModified().date().toString());
            label_time->setText(info.lastModified().time().toString());
            textedit_note->setText(text);

            button_save->setText(tr("Change"));

            widget_right->setEnabled(true);
        }
    }
}

bool MyNote::onTextChanged(QString new_text)
{
     if (!full_note_name_list.contains(new_text+".txt")  ||
         new_text == old_name)
     {
         return true;
     }
     else
     {
        return false;
     }
}

void MyNote::deleteNoteKey(const QModelIndexList &index_list)
{
    if (!index_list.isEmpty() && !all_files)
    {
        QModelIndexList index_list_new = index_list;
        qSort(index_list_new.begin(),index_list_new.end(),qGreater<QModelIndex>());

        QMessageBox msgBox;
        msgBox.setText(tr("The delete button was clicked!"));

        int index_list_size = index_list_new.size();

        if (index_list_size==1)
        {
            msgBox.setInformativeText((tr("Do you want to delete one note?")));
        }
        else
        {
            msgBox.setInformativeText(tr("Do you want to delete selected notes?") + QString::number(index_list_size));
        }

        msgBox.addButton(tr("Yup"),QMessageBox::YesRole);
        msgBox.addButton(tr("No"),QMessageBox::NoRole);

        int start = msgBox.exec();

        switch (start)
        {
        case 0:
        {
            closeNote();

            label_info->setText(tr("Delete"));

            widget_left->setEnabled(false);

            change_row=0;

            watcher_delete = new QFutureWatcher<void>;
            QFuture<void> future_delete = QtConcurrent::run(std::mem_fn(&MyNote::onStartDeleteNote),this, index_list_new);
            connect(watcher_delete, SIGNAL(finished()),
                    this,SLOT(onFinishDeleteNote()));
            watcher_delete->setFuture(future_delete);
        }
        break;
        }
    }
}

void MyNote::onStartDeleteNote(const QModelIndexList &index_list)
{
    int index_list_i = index_list.size(),
        row = 0;

    for (int i=0;i<index_list_i;++i)
    {
        row = index_list.at(i).row();

        QFileInfo info = dir.entryInfoList(QStringList()<<full_note_name_list.at(row)).at(0);

        if (list_ctrl_c.contains(info))
        {
            list_ctrl_c.removeOne(info);
        }

        QFile::remove(info.absoluteFilePath());
        full_note_name_list.removeAt(row);

        change_row++;
        count_row--;
    }

    current_row = row;
}

void MyNote::onFinishDeleteNote()
{
    watcher_delete->cancel();

    label_info->setText(tr("Record count") + QString::number(count_row) + " " +label_name_current_date_name);

    widget_left->setEnabled(true);

    note_listmodel->setStringList(full_note_name_list);

    note_list->setFocus();

    if (current_row<count_row && count_row!=0)
    {
        note_list->setCurrentIndex(note_listmodel->index(current_row));
    }
    else
    {
        note_list->setCurrentIndex(note_listmodel->index(count_row-1));
    }

    updateDateTime();

    if (count_row==0)
    {
        dir.rmpath(current_path);
        emit emptyDate(current_date,calendar_pixmap_2);
    }
}

void MyNote::rightMouseButtonClicK(QMouseEvent *event, const QModelIndex &index)
{
    if (index.isValid() && !all_files)
    {
        QMenu *my_menu = new QMenu();

        my_menu->setAttribute(Qt::WA_DeleteOnClose);

            QAction *action_name        = new QAction(full_note_name_list.at(index.row()),0);
            QAction *action_open        = new QAction(tr("Open"),0);
            QAction *action_delete      = new QAction(tr("Delete"),0);
            QAction *action_change_name = new QAction(tr("Change"),0);

        my_menu->addAction(action_name);
        my_menu->addAction(action_open);
        my_menu->addAction(action_delete);
        my_menu->addAction(action_change_name);

        my_menu->popup(mapToGlobal(event->pos()),0);
        my_menu->show();
    }
}

void MyNote::ctrlC(const QModelIndexList & index_list)
{
    if (!index_list.isEmpty() && !all_files)
    {
        list_ctrl_c.clear();

        label_info->setText(tr("Copy process"));

        widget_left->setEnabled(false);

        watcher_ctrlC = new QFutureWatcher<void>;
        QFuture<void> future_ctrlCV = QtConcurrent::run(std::mem_fn(&MyNote::ctrlCStart),this, index_list);
        connect(watcher_ctrlC, SIGNAL(finished()),
                this,SLOT(ctrlCFinish()));
        watcher_ctrlC->setFuture(future_ctrlCV);
    }
}

void MyNote::ctrlCStart(const QModelIndexList & index_list)
{
    int modelCtrlC_i = index_list.size();

    QStringList local_list;

    for (int i=0;i<modelCtrlC_i;i++)
    {
        int row = index_list.at(i).row();
        local_list.append(full_note_name_list.at(row));
    }

    list_ctrl_c = dir.entryInfoList(local_list);
}

void MyNote::ctrlCFinish()
{
    watcher_ctrlC->cancel();

    label_info->setText(tr("Record count") + QString::number(count_row) + " " +label_name_current_date_name);

    widget_left->setEnabled(true);
    note_list->setFocus();
}

void MyNote::deleteCurrent()
{
    QModelIndex current_index = note_list->currentIndex();
    if ( current_index.isValid() && !all_files)
    {
        deleteNoteKey(QModelIndexList()<<note_list->currentIndex());
    }
}

void MyNote::deleteAllNotes()
{
    note_list->selectAll();
    note_list->deleteAllNotes();
}

void MyNote::ctrlV()
{
    if (!list_ctrl_c.isEmpty() && !all_files)
    {
        closeNote();
        label_info->setText(tr("Insert pocess"));

        widget_left->setEnabled(false);

        change_row = 0;

        watcher_ctrlV = new QFutureWatcher<void>;
        QFuture<void> future_ctrlCV = QtConcurrent::run(std::mem_fn(&MyNote::onStartAddNote),this, list_ctrl_c);
        connect(watcher_ctrlV, SIGNAL(finished()),
                this,SLOT(onFinishAddNote()));
        watcher_ctrlV->setFuture(future_ctrlCV);
    }
}

void MyNote::onStartAddNote(const QFileInfoList &list)
{
    int modelCtrlC_i = list.size();

    current_row = note_list->currentIndex().row();

    for (int i=0;i<modelCtrlC_i;i++)
    {
        int oder = 1,
            cycle = 1;

        QString abs_path = list.at(i).absoluteFilePath(),
                add_name = "",
                path = list.at(i).path(),
                name = list.at(i).baseName();

        QFile file(abs_path);

        if(file.exists())
        {
            QString name_add = tr(" copy"),
                    new_abs_path = path+"/"+name+name_add+".txt";

            while (!QFile::copy(file.fileName(),new_abs_path))
            {
                if (cycle==100)
                {
                    name_add = name_add + tr(" copy");
                    cycle = 0;
                    oder = 1;
                }

                add_name = QString::number(oder);
                new_abs_path = path+"/"+name+name_add + add_name +".txt";
                cycle++;
                oder++;
            }


            count_row++;
            change_row++;
            full_note_name_list.insert(current_row,name+name_add + add_name +".txt");
            current_row++;
        }
    }
}

void MyNote::onFinishAddNote()
{
    watcher_ctrlV->cancel();

    label_info->setText(tr("Record count") + QString::number(count_row) + " " +label_name_current_date_name);

    note_listmodel->setStringList(full_note_name_list);

    widget_left->setEnabled(true);

    note_list->setFocus();
    note_list->setCurrentIndex(note_listmodel->index(current_row));
}

void MyNote::createNote()
{
    if (!all_files)
    {
        old_name = "";

        edit_file_name->clear();
        edit_file_name->setPlaceholderText(tr("new note"));

        textedit_note->clear();
        textedit_note->setPlaceholderText(tr("Winnie-the-Pooh"));

        date_time = true;
        updateDateTime();

        button_save->setText(tr("Save"));
        widget_right->setEnabled(true);

        edit_file_name->setFocus();
    }
}

void MyNote::applyNote()
{
    if (widget_right->isEnabled() && !all_files)
    {
        QString name = edit_file_name->text();

        if ( name == "" )
        {
            name = tr(" copy");
        }

        while (!onTextChanged(name))
        {
            name = name + tr(" copy");
        }

        if (date_time)
        {
            dir.mkpath(current_path);

            QString note_name = name+".txt",
                    path = current_path+"/"+note_name,
                    text = textedit_note->toPlainText();

            QFile file(path);

            if (file.open(QIODevice::ReadWrite))
            {
                QTextStream data(&file);
                data.setCodec(application_codec);
                data << text;

                full_note_name_list.push_back(note_name);

                note_listmodel->setStringList(full_note_name_list);

                count_row++;
                label_info->setText(tr("Record count") + QString::number(count_row) + " " +label_name_current_date_name);

                button_save->setText(tr("Change"));

                file.close();

                emit fullDate(current_date,calendar_pixmap_1);
            }
        }
        else
        {
            int row = note_list->currentIndex().row();

            QFileInfo info = dir.entryInfoList(QStringList()<<full_note_name_list.at(row)).at(0);

            QString note_name = name+".txt",
                    path = info.absoluteFilePath(),
                    text = textedit_note->toPlainText();

            QFile file(path);

            if (file.open(QIODevice::ReadWrite))
            {
                file.rename(current_path+"/"+note_name);

                file.remove();
                file.open(QIODevice::ReadWrite);

                QTextStream data(&file);
                data.setCodec(application_codec);
                data << text;

                path = current_path+"/"+note_name;

                full_note_name_list.removeAt(row);
                full_note_name_list.insert(row,note_name);

                note_listmodel->setStringList(full_note_name_list);

                file.close();
            }
        }

        closeNote();
    }
}

void MyNote::closeNote()
{
    edit_file_name->clear();
    edit_file_name->setPlaceholderText(tr("note name"));

    textedit_note->clear();
    textedit_note->setPlaceholderText(tr("Hello, it is your record, click on some record twice, or create new"));

    date_time = true;

    widget_right->setEnabled(false);
    updateDateTime();

    note_list->setFocus();
}

void MyNote::changeNotesVisibleOption(int index)
{
    if ( index == 0 )
    {
        showNotes(current_date, false);
    }
    else
    {
        showNotes(current_date, true);
    }
}

void MyNote::changeCalendarDay(const QModelIndex &index)
{
    if ( all_files )
    {
        if (index.isValid())
        {
            bool ok;
            int day = add_dir_path.at(index.row()).mid(1).toInt(&ok);
            if ( ok )
            {
                current_date.setDate(current_date.year(),current_date.month(),day);
                emit chooseDay(day);
            }
        }
    }
}
