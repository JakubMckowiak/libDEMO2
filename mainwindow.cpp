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

void MainWindow::on_findBook_clicked()
{
    QFile file("Books.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        return;
    }
    QTextStream in(&file);
    QString bufforLine=".";
    QString bufforKey, bufforTitle, bufforFirstName,        //Line from .txt file; Key word from .txt; the others are to pass the metadata
            bufforSurname,bufforYear,bufforGenere;                                      //of a found book to the ui table
    bool bufforCheck;
    int bufforCount = 0;

    while((!file.atEnd())&&(bufforCount<15)){

        bufforLine = in.readLine();                                     //getting a line from the Books.txt file
        while(bufforLine!=nullptr){                                     //this line is only here not to waste time for checking every Key in the line
            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));    //passing only the title from bufforLine to bufforKey
            bufforLine.remove(bufforKey+'|');
            if((ui->radioButtonTitle->isChecked())&&                    //if the filter is on
                    (bufforKey!=ui->inputAddTitle->text())) break;   //and ui key value != file key value
            bufforTitle=bufforKey;
            ui->labelTest->setText("I'm here" + bufforKey);

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->radioButtonFirstName->isChecked())&&
                    (bufforKey!=ui->inputAddFirstName->text())) break;
            bufforFirstName=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->radioButtonSurname->isChecked())&&
                    (bufforKey!=ui->inputAddSurname->text())) break;
            bufforSurname=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->radioButtonYear->isChecked())&&
                    (bufforKey!=ui->inputAddYear->text())) break;
            bufforYear=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->radioButtonGenere->isChecked())&&
                    (bufforKey!=ui->inputAddGenere->currentText())) break; //small change caused by the specifics of Comboboxes used for "book's genere" input
            bufforGenere=bufforKey;


            bufforCheck = true;
            bufforLine = nullptr;          //there is still data not needed in this search that needs to be destroyed
        }
        bufforLine='.';
        if(bufforCheck==true){
            ui->tableWidget->setItem(bufforCount, 0, new QTableWidgetItem(bufforTitle));
            ui->tableWidget->setItem(bufforCount, 1, new QTableWidgetItem(bufforFirstName));
            ui->tableWidget->setItem(bufforCount, 2, new QTableWidgetItem(bufforSurname));
            ui->tableWidget->setItem(bufforCount, 3, new QTableWidgetItem(bufforGenere));
            ui->tableWidget->setItem(bufforCount, 4, new QTableWidgetItem(bufforYear));
            bufforCount++;
            bufforCheck = false;
        }

    }
    file.close();

}

void MainWindow::on_deleteBook_clicked()
{                          //X, Y, item
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(ui->inputAddTitle->text()));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(ui->inputAddFirstName->text()));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(ui->inputAddSurname->text()));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(ui->inputAddGenere->currentText()));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(ui->inputAddYear->text()));
}
