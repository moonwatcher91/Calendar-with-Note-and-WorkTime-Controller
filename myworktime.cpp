#include "myworktime.h"

MyWorkTime::MyWorkTime(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent,f)
{
    //zero_h_lay
    QLabel *label_date = new QLabel(tr("Date"));
    label_date->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    label_date->setFixedWidth(note_label_lenght);
    label_work_date = new QLabel();
    label_work_date->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    //part of first_h_lay
    QLabel* duration = new QLabel(tr("Duration"));
    duration->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* empty_space = new QLabel(tr("All"));
    empty_space->setFixedWidth(note_label_lenght);
    empty_space->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* hour_1 = new QLabel(tr("[h]"));
    hour_1->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* minute_1 = new QLabel(tr("[m]"));
    minute_1->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    box_work_hour = createSpinBox(0,23,1,combo_box_width);
    box_work_minute = createSpinBox(0,59,1,combo_box_width);

    //part of second_h_lay
    QLabel* usedtime = new QLabel(tr("Work time"));
    usedtime->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* begin = new QLabel(tr("Start"));
    begin->setFixedWidth(note_label_lenght);
    begin->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* hour_2 = new QLabel(tr("[h]"));
    hour_2->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* minute_2 = new QLabel(tr("[m]"));
    minute_2->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    box_work_hour_start = createSpinBox(0,23,1,combo_box_width);
    box_work_minute_start = createSpinBox(0,59,1,combo_box_width);

    //part of third_h_lay
    QLabel* end = new QLabel(tr("Finish"));
    end->setFixedWidth(note_label_lenght);
    end->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* hour_3 = new QLabel(tr("[h]"));
    hour_3->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* minute_3 = new QLabel(tr("[m]"));
    minute_3->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    box_work_hour_finish = createSpinBox(0,23,1,combo_box_width);
    box_work_minute_finish = createSpinBox(0,59,1,combo_box_width);

    //part of forth_h_lay
    QLabel* finaltime = new QLabel(tr("Used time"));
    finaltime->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* empty_space_again = new QLabel(tr("All"));
    empty_space_again->setFixedWidth(note_label_lenght);
    empty_space_again->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* hour_4 = new QLabel(tr("[h]"));
    hour_4->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    QLabel* minute_4 = new QLabel(tr("[m]"));
    minute_4->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    box_work_hour_final = createSpinBox(0,23,1,combo_box_width);
    box_work_hour_final->setEnabled(false);
    box_work_minute_final = createSpinBox(0,59,1,combo_box_width);
    box_work_minute_final->setEnabled(false);

    //end of main_lay_vertical
    save = new mybutton(tr("Save"));
    connect(save,SIGNAL(clicked()),this,SLOT(saveWorkTime()));
    QLabel* analysing = new QLabel(tr("Analysing"));
    analysing->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    mybutton *week = new mybutton(tr("week"));
    connect(week,SIGNAL(clicked()),this,SLOT(analiseWeek()));
    mybutton *mounth = new mybutton(tr("mounth"));
    connect(mounth,SIGNAL(clicked()),this,SLOT(analiseMounth()));
    mybutton *year = new mybutton(tr("year"));
    connect(year,SIGNAL(clicked()),this,SLOT(analiseYear()));

    QVBoxLayout *main_lay_vertical = new QVBoxLayout;

        QHBoxLayout *zero_h_lay = new QHBoxLayout;

            zero_h_lay->addWidget(label_date);
            zero_h_lay->addWidget(label_work_date);

        QHBoxLayout *first_h_lay = new QHBoxLayout;

            first_h_lay->addWidget(empty_space);
            first_h_lay->addWidget(box_work_hour);
            first_h_lay->addWidget(hour_1);
            first_h_lay->addWidget(box_work_minute);
            first_h_lay->addWidget(minute_1);

        QHBoxLayout *second_h_lay = new QHBoxLayout;

            second_h_lay->addWidget(begin);
            second_h_lay->addWidget(box_work_hour_start);
            second_h_lay->addWidget(hour_2);
            second_h_lay->addWidget(box_work_minute_start);
            second_h_lay->addWidget(minute_2);

        QHBoxLayout *third_h_lay = new QHBoxLayout;

            third_h_lay->addWidget(end);
            third_h_lay->addWidget(box_work_hour_finish);
            third_h_lay->addWidget(hour_3);
            third_h_lay->addWidget(box_work_minute_finish);
            third_h_lay->addWidget(minute_3);

        QHBoxLayout *forth_h_lay = new QHBoxLayout;

            forth_h_lay->addWidget(empty_space_again);
            forth_h_lay->addWidget(box_work_hour_final);
            forth_h_lay->addWidget(hour_4);
            forth_h_lay->addWidget(box_work_minute_final);
            forth_h_lay->addWidget(minute_4);

    main_lay_vertical->addLayout(zero_h_lay);
    main_lay_vertical->addWidget(duration);
    main_lay_vertical->addLayout(first_h_lay);
    main_lay_vertical->addWidget(usedtime);
    main_lay_vertical->addLayout(second_h_lay);
    main_lay_vertical->addLayout(third_h_lay);
    main_lay_vertical->addWidget(finaltime);
    main_lay_vertical->addLayout(forth_h_lay);
    main_lay_vertical->addWidget(save);
    main_lay_vertical->addWidget(analysing);
    main_lay_vertical->addWidget(week);
    main_lay_vertical->addWidget(mounth);
    main_lay_vertical->addWidget(year);
    main_lay_vertical->addStretch();

    QHBoxLayout *main_lay_horizontal = new QHBoxLayout;

    main_lay_horizontal->addLayout(main_lay_vertical);
    main_lay_horizontal->addStretch();

    setLayout(main_lay_horizontal);
}

QSpinBox *MyWorkTime::createSpinBox(int min, int max, int step, int width_size)
{
    QSpinBox *box = new QSpinBox();

    box->setFixedWidth(width_size);
    box->setMinimum(min);
    box->setMaximum(max);
    box->setSingleStep(step);

    connect(box,SIGNAL(valueChanged(int)),this,SLOT(refreshTime()));

    return box;
}

void MyWorkTime::showWorkTime(QDate date)
{
    save->setEnabled(true);
    current_date = date;
    current_path = QDir::currentPath()+time_work_path+"/"+date.toString(path_year)+"/"+date.toString(path_mounth);
    dir.setPath(current_path);
    file.setFileName(current_path+"/"+date.toString(path_day));
    if (file.exists())
    {
        showWorkFile();
    }
    else
    {
        resetAll();
        emit emptyDate(current_date,calendar_pixmap_2);
    }
}

void MyWorkTime::resetAll()
{
    label_work_date->setText("");

    box_work_hour->setValue(work_time_hour_duration);
    box_work_minute->setValue(work_time_minute_duration);

    box_work_hour_finish->setValue(work_time_hour_finish);
    box_work_minute_finish->setValue(work_time_minute_finish);

    box_work_hour_start->setValue(work_time_hour_start);
    box_work_minute_start->setValue(work_time_minute_start);
}

QTime MyWorkTime::timeDiscrepansy(const QTime &t1, const QTime &t2)
{
    int discrepansy = t1.secsTo(t2),
        seconds_per_hour = 3600,
        seconds_per_minute = 60;
    return QTime(discrepansy/seconds_per_hour,(discrepansy % seconds_per_hour)/seconds_per_minute);
}

void MyWorkTime::refreshTime()
{
    QTime time_2(box_work_hour_start->value(),box_work_minute_start->value()),
          time_3(box_work_hour_finish->value(),box_work_minute_finish->value()),
          time_4;

    if (time_2>time_3)
    {
        time_2=time_3;
        box_work_hour_start->setValue(time_2.hour());
        box_work_minute_start->setValue(time_2.minute());
    }

    time_4 = timeDiscrepansy(time_2,time_3);
    box_work_hour_final->setValue(time_4.hour());
    box_work_minute_final->setValue(time_4.minute());
    save->setEnabled(true);
}

void MyWorkTime::saveWorkTime()
{
    dir.mkpath(current_path);

    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream data(&file);
        data.setCodec(application_codec);
        data << createText();
        file.close();
        save->setEnabled(false);

        emit fullDate(current_date,calendar_pixmap_1);
        emit focusToCalendar();
    }
}

QString MyWorkTime::createText()
{
    QTime time_1(box_work_hour->value(),box_work_minute->value()),
          time_2(box_work_hour_start->value(),box_work_minute_start->value()),
          time_3(box_work_hour_finish->value(),box_work_minute_finish->value()),
          time_4 = timeDiscrepansy(time_2,time_3);

    return(current_date.toString(date_view)+"//"+tr("Date")+"\n"+
           time_1.toString(time_view_other)+"//"+tr("Duration")+"\n"+
           time_2.toString(time_view_other)+"//"+tr("Work time")+tr("Start")+"\n"+
           time_3.toString(time_view_other)+"//"+tr("Work time")+tr("Finish")+"\n"+
           time_4.toString(time_view_other)+"//"+tr("Used time"));
}

void MyWorkTime::showWorkFile()
{
    if (file.open(QIODevice::ReadWrite))
    {
        QString work_text = file.readAll();
        file.close();

        work_text=work_text.simplified();
        work_text=work_text.remove(QRegExp("[^\\d+^.+^//+]"));

        if (work_text.length()==38)
        {
            QString work_1 = work_text.section("//",0,0),
                    work_2 = work_text.section("//",1,1),
                    work_3 = work_text.section("//",2,2),
                    work_4 = work_text.section("//",3,3);

            QDate date_file(work_1.section(".",2,2).toInt(),work_1.section(".",1,1).toInt(),work_1.section(".",0,0).toInt());

            QTime time_1(work_2.section(".",0,0).toInt(),work_2.section(".",1,1).toInt()),
                  time_2(work_3.section(".",0,0).toInt(),work_3.section(".",1,1).toInt()),
                  time_3(work_4.section(".",0,0).toInt(),work_4.section(".",1,1).toInt());

            if (date_file.isValid() && time_1.isValid() && time_2.isValid() && time_3.isValid())
            {
                label_work_date->setText(date_file.toString(date_view));

                box_work_hour->setValue(time_1.hour());
                box_work_minute->setValue(time_1.minute());

                box_work_hour_finish->setValue(time_3.hour());
                box_work_minute_finish->setValue(time_3.minute());

                box_work_hour_start->setValue(time_2.hour());
                box_work_minute_start->setValue(time_2.minute());

                emit fullDate(current_date,calendar_pixmap_1);
            }
            else
            {
                file.remove();
                resetAll();
                emit emptyDate(current_date,calendar_pixmap_2);
            }
        }
        else
        {
            file.remove();
            resetAll();
            emit emptyDate(current_date,calendar_pixmap_2);
        }
    }
}

void MyWorkTime::analiseWeek()
{
    int start = current_date.day()-current_date.dayOfWeek()+1,
        end = start+6,
        readable_days = 0;

    QDateTime date_we_need(QDate(1,1,1),QTime(0,0,0)),
              date_we_have(QDate(1,1,1),QTime(0,0,0));

    analyseWeekMounth(date_we_have, date_we_need, readable_days, dir, current_date, start, end);
    outputInformation(tr("One week work time analysing"), readable_days, date_we_have, date_we_need);
    emit focusToCalendar();
}

void MyWorkTime::analiseMounth()
{
    int start = 1,
        end = current_date.daysInMonth(),
        readable_days = 0;

    QDateTime date_we_need(QDate(1,1,1),QTime(0,0,0)),
              date_we_have(QDate(1,1,1),QTime(0,0,0));

    analyseWeekMounth(date_we_have, date_we_need, readable_days, dir, current_date, start, end);
    outputInformation(tr("One mounth work time analysing"), readable_days, date_we_have, date_we_need);
    emit focusToCalendar();
}

void MyWorkTime::analiseYear()
{
    QDir year_dir;
    QString local_path = QDir::currentPath()+time_work_path+"/"+current_date.toString(path_year)+"/";
    QDate local_current_date(current_date.year(),1,1);

    QDateTime date_we_need(QDate(1,1,1),QTime(0,0,0)),
              date_we_have(QDate(1,1,1),QTime(0,0,0));

    int start = 1,
        end = 0,
        readable_days = 0;

    for (int i=1;i<=12;i++)
    {
        year_dir.setPath(local_path+QString::number(i));
        end = local_current_date.daysInMonth();
        analyseWeekMounth(date_we_have, date_we_need, readable_days, year_dir, local_current_date, start, end);
        local_current_date.addMonths(1);
    }

    outputInformation(tr("One year work time analysing"), readable_days, date_we_have, date_we_need);
    emit focusToCalendar();
}

void MyWorkTime::outputInformation(QString information, int amount_days, QDateTime dt1, QDateTime dt2)
{
    QDateTime date_discrepancy(QDate(1,1,1),QTime(0,0,0)),
              date_to_compare_with_zero(QDate(1,1,1),QTime(0,0,0));

    int seconds_discrepancy = dt1.secsTo(dt2);
    qreal transformation = 1.0/3600;

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("The job is not a wolf"));
    msgBox.setText(information);

    QString more_or_less,
            hour = tr(" [h]");

    if (seconds_discrepancy<0)
    {
        date_discrepancy = date_discrepancy.addSecs(-seconds_discrepancy);
        more_or_less = tr("Working through");
    }
    else
    {
        date_discrepancy = date_discrepancy.addSecs(seconds_discrepancy);
        more_or_less = tr("Incomplete work");
    }

    msgBox.setInformativeText
    (
    tr("Work time") + QString::number(date_to_compare_with_zero.secsTo(dt2)*transformation)+hour+"\n"+
    tr("Real time") + QString::number(date_to_compare_with_zero.secsTo(dt1)*transformation)+hour+"\n"+
    more_or_less + QString::number(date_to_compare_with_zero.secsTo(date_discrepancy)*transformation)+hour+"\n"+
    tr("Amount of files") + QString::number(amount_days)
    );
    msgBox.addButton(tr("The job is not a wolf"),QMessageBox::YesRole);
    msgBox.exec();
}

void MyWorkTime::analyseWeekMounth(QDateTime &date_we_have, QDateTime &date_we_need, int &readable_days, QDir dir_to_analyse, QDate date, int start, int end)
{
    QStringList list = dir_to_analyse.entryList(QStringList()<<"*",QDir::Files,QDir::Name);

    if (list.size()>0)
    {
        QFile file_read;
        QTime     time_to_summa(0,0);

        if (start<1)
        {
            start=1;
        }

        if (end>date.daysInMonth())
        {
            end=date.daysInMonth();
        }

        for (;start<=end;start++)
        {
            QString string_start = QString::number(start);

            if (list.contains(string_start))
            {
                file_read.setFileName(dir_to_analyse.absolutePath()+"/"+string_start);

                if (file_read.open(QIODevice::ReadOnly))
                {
                    QString work_text = file_read.readAll();
                    file_read.close();
                    work_text=work_text.simplified();
                    work_text=work_text.remove(QRegExp("[^\\d+^.+^//+]"));

                    if (work_text.length()==38)
                    {
                        QString work_1 = work_text.section("//",1,1),
                                work_5 = work_text.section("//",4,4);
                        QTime time_we_need_from_file(work_1.section(".",0,0).toInt(),work_1.section(".",1,1).toInt()),
                              time_we_have_from_file(work_5.section(".",0,0).toInt(),work_5.section(".",1,1).toInt());
                        if (time_we_need_from_file.isValid() && time_we_have_from_file.isValid())
                        {
                            readable_days++;
                            date_we_need = date_we_need.addSecs(time_to_summa.secsTo(time_we_need_from_file));
                            date_we_have = date_we_have.addSecs(time_to_summa.secsTo(time_we_have_from_file));
                        }
                    }
                }

                list.removeOne(string_start);

                if (list.size()==0)
                {
                    break;
                }
            }
        }
    }
}
