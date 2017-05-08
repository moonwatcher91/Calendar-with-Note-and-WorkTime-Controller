Hello, it is widget calendar with notes and worktime controller.

!!!
My PROBLEM
it have QTranslator and spacial file QtLanguage_ru.qm than contains all translation.
When you click on a button at the lower left-hand window corner, the languages must change,
by call method repaint(), but it does not work.
Do not foget to transferal file *.qm to folder with *.exe.
!!!

Maybe it is not very usefull, but i can't delete it.

it is containe custom:
1. QLable - to set your own pixmap easyly;
2. QListView - to do something like basic windows folder;
3. QTranslator - to change language.

it is containe #include <QtConcurrent/QtConcurrent>, to do thread much more easy than use ordinary QThread
(you can have a lot of notes, that's why you need thread).

Behavior:
1. All days with note (or worktime) painted in special QPixmap;
2. Selected day also painted in special QPixmap;
3. Today have red QFont;
4. WeekDays have green QFont;
5. Spacial QPixmap for days from another mounth;
6. Use keyboard to guide;
7. Use mouse to guide;
8. Create note;
9. Monitor your worktime. 

Keyboard operations:
1. Key_Up - take away 7 days;
2. Key_Down - add 7 days;
3. Key_Left - take away 1 days;
4. Key_Right - add 1 days;

5. Key_Delete - delete all notes for current days;

6. CTRL + Key_Up - take away 1 mounth;
7. CTRL + Key_Down - add 1 mounth;
8. CTRL + Key_Left - take away 1 mounth;
9. CTRL + Key_Right - add 1 mounth;

10. CTRL + Key_T - jump on current day;
11. CTRL + Key_N - create new note for this day;
12. CTRL + Key_S - save note (or workday);

13. Shift + Key_Up - take away 1 year;
14. Shift + Key_Down - add 1 year;
15. Shift + Key_Left - take away 1 year;
16. Shift + Key_Right - add 1 year;

17. Alt + Key_Up - take away 5 year;
18. Alt + Key_Down - add 5 year;
19. Alt + Key_Left - take away 5 year;
20. Alt + Key_Right - add 5 year;

21. CTRL + Alt + Key_Up - take away 10 year;
22. CTRL + Alt + Key_Down - add 10 year;
23. CTRL + Alt + Key_Left - take away 10 year;
24. CTRL + Alt + Key_Right - add 10 year;

25. Shift + Alt + Key_Up - take away 100 year;
26. Shift + Alt + Key_Down - add 100 year;
27. Shift + Alt + Key_Left - take away 100 year;
28. Shift + Alt + Key_Right - add 100 year;

29. CTRL + Key_C - copy selected note (notes);
30. CTRL + Key_V - insert note (notes);

31. CTRL + Key_W - analize week;
32. CTRL + Key_M - analize mounth;
33. CTRL + Key_Y - analize year;

34. CTRL + Key_1 - choose note;
35. CTRL + Key_1 - choose worktime;
35. CTRL + Alt + Key_F4 - close programm;