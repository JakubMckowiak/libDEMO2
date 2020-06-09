#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submitAddBook_clicked();

    void on_deleteBook_clicked();

    void on_findBook_clicked();

    void on_submitUserAdd_clicked();

    void on_findUser_clicked();

    void on_deleteUser_clicked();

    void on_giveBookToUser_clicked();

    void on_returnBookFromUser_clicked();

    void on_editUserBooks_clicked();

    bool dataValidation_books(bool search);

    bool dataValidation_users(bool search);

    void dataInFileReplace(QString inFileName, QString outFileName, QString searchRow, QString replaceRow);

    void on_editBook_clicked();

    void on_editUser_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
