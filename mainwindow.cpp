#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputAddGenere->addItem("Adventure");
    ui->inputAddGenere->addItem("Biography/Autobiography");
    ui->inputAddGenere->addItem("Classic");
    ui->inputAddGenere->addItem("Crime and Detective");
    ui->inputAddGenere->addItem("Drama");
    ui->inputAddGenere->addItem("Essay");
    ui->inputAddGenere->addItem("Fable");
    ui->inputAddGenere->addItem("Fantasy");
    ui->inputAddGenere->addItem("Historical fiction");
    ui->inputAddGenere->addItem("Horror");
    ui->inputAddGenere->addItem("Legend");
    ui->inputAddGenere->addItem("Memoir");
    ui->inputAddGenere->addItem("Mythology");
    ui->inputAddGenere->addItem("Narrative Nonfiction");
    ui->inputAddGenere->addItem("Romance");
    ui->inputAddGenere->addItem("Satire");
    ui->inputAddGenere->addItem("Self-help Books");
    ui->inputAddGenere->addItem("Sci-Fi");
    ui->inputAddGenere->addItem("Speech");
    ui->inputAddGenere->addItem("Textbook");
    ui->inputAddGenere->addItem("Thriller");
    ui->inputAddGenere->addItem("Poetry");
    ui->inputAddGenere->addItem("Philosophie");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//function for adding new books

void MainWindow::on_submitAddBook_clicked()
{
    QFile file("Books.txt");
    if(!file.open(QFile::WriteOnly|QFile::Text|QIODevice::Append)){
        return;
    }
    QTextStream out(&file);
    out <<ui->inputAddTitle->text()<<'|'<<ui->inputAddFirstName->text()<<'|'
        <<ui->inputAddSurname->text()<<'|'<<ui->inputAddYear->text()<<'|'
        <<ui->inputAddGenere->currentText()<<"|0|\n";
    file.flush();
    file.close();
    QMessageBox::information(this,"title","The books has been added",QMessageBox::Ok);
}

//function for finding an already existing book, with filters

void MainWindow::on_pushButton_2_clicked()
{
    QFile file("Books.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text|QIODevice::Append)){
        return;
    }
    QTextStream in(&file);
    QString buffor;
    while(!file.atEnd()){
        buffor = in.readLine();

        //
        // !! METHOD NOT FINISHED !!
        //

    }
    file.close();
}
