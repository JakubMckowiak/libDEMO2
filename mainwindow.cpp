#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
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
    if(ui->inputAddTitle->text().isEmpty()||ui->inputAddFirstName->text().isNull()||                 //if the parameters are empty, the finding method breaks
            ui->inputAddSurname->text().isNull()||ui->inputAddYear->text().isNull())                 //so this line prevents it
        QMessageBox::information(this,"Error","Please, fill all of the parameters",QMessageBox::Ok);

    else {
        out <<ui->inputAddTitle->text()<<'|'<<ui->inputAddFirstName->text()<<'|'                     //if the parameters are all existing
        <<ui->inputAddSurname->text()<<'|'<<ui->inputAddYear->text()<<'|'                            //the book can be added to the Books.txt
        <<ui->inputAddGenere->currentText()<<"|0|\n";
        QMessageBox::information(this,"title","The books has been added",QMessageBox::Ok);
    }
    file.flush();
    file.close();
}

//function for finding an already existing book, with filters

void MainWindow::on_findBook_clicked()
{
    QFile file("Books.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    //ui->labelTest->setText("I'm here"+in.readLine()+in.readLine());
    QString bufforLine=".";
    QString bufforKey, bufforTitle, bufforFirstName,        //Line from .txt file; Key word from .txt; the others are to pass the metadata
            bufforSurname,bufforYear,bufforGenere, bufforPossessor;                                      //of a found book to the ui table

    int bufforCount = 0;
    while(bufforCount<15){                                              //the loop is for flushing already
    ui->tableWidget->setItem(bufforCount, 0, new QTableWidgetItem("")); //existant items from the table
    ui->tableWidget->setItem(bufforCount, 1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(bufforCount, 2, new QTableWidgetItem(""));
    ui->tableWidget->setItem(bufforCount, 3, new QTableWidgetItem(""));
    ui->tableWidget->setItem(bufforCount, 4, new QTableWidgetItem(""));
    ui->tableWidget->setItem(bufforCount, 5, new QTableWidgetItem(""));
    bufforCount++;
    }

    bufforCount=0;
    int bufforFalse = 0;            //this variable is to count the unmatching parameters (if 0 in the end, all of the
                                                                                            //chosen parameters are eql)
    while(!file.seek(-1)&&bufforCount<15){
        bufforLine = in.readLine();                    //getting a line from the Books.txt file using QFileStream
        if(bufforLine.isNull())break;                  //check if the line, that we are going to operate on is not the end of the file, if so - the loop breaks
        bufforFalse = 0;                               //integer variable to for mettring missmatches

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));    //passing only the title from bufforLine to bufforKey
            bufforLine.remove(bufforKey+'|');                                             //removing the taken Key word (here it is title) from the current line

            if((ui->checkBoxTitle->isChecked())&&                            //if the filter (here it is title) is turned on (checkBox is checked)
                    (bufforKey!=ui->inputAddTitle->text())) bufforFalse++;   //and ui key word value != file key word value,
                                                                             //we count that missmatch with bufforFalse mettring
            bufforTitle=bufforKey;


            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->checkBoxFirstName->isChecked())&&
                    (bufforKey!=ui->inputAddFirstName->text())) bufforFalse++;
            bufforFirstName=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->checkBoxSurname->isChecked())&&
                    (bufforKey!=ui->inputAddSurname->text())) bufforFalse++;
            bufforSurname=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->checkBoxYear->isChecked())&&
                    (bufforKey!=ui->inputAddYear->text())) bufforFalse++;
            bufforYear=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|'));
            bufforLine.remove(bufforKey+'|');
            if((ui->checkBoxGenere->isChecked())&&
                    (bufforKey!=ui->inputAddGenere->currentText())) bufforFalse++; //small change caused by the specifics of Comboboxes used for "book's genere" input
            bufforGenere=bufforKey;

            bufforKey = bufforLine.remove('|'); //we have '|' to remove only
            bufforPossessor=bufforKey;



        if(bufforFalse==0){
            ui->tableWidget->setItem(bufforCount, 0, new QTableWidgetItem(bufforTitle));
            ui->tableWidget->setItem(bufforCount, 1, new QTableWidgetItem(bufforFirstName));
            ui->tableWidget->setItem(bufforCount, 2, new QTableWidgetItem(bufforSurname));
            ui->tableWidget->setItem(bufforCount, 3, new QTableWidgetItem(bufforYear));
            ui->tableWidget->setItem(bufforCount, 4, new QTableWidgetItem(bufforGenere));
            ui->tableWidget->setItem(bufforCount, 5, new QTableWidgetItem(bufforPossessor));
            bufforCount++;
        }
    }
    file.close();
}

void MainWindow::on_deleteBook_clicked()    //the method operates on two .txt files
                                            //(Books.txt and BooksBuffor.txt) rewrinting everyting except
                                            //data selected from the table (variable SelectedRow)
    int row = ui->tableWidget->currentRow();
    QString SelectedRow;

    for(int col=0;col<6;col++)
    SelectedRow = SelectedRow + ui->tableWidget->item(row,col)->text() + '|';
                                            //SelectedRow collects data from the whole selected row
    QString bufforLine = ".";

    QFile fileIn("Books.txt");              //the file we'll read from
        if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
    QTextStream in(&fileIn);

    QFile fileOut("BooksBuffor.txt");       //the file we'll write to
        if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text)){
            return;
        }

    QTextStream out(&fileOut);
    bool safetyFirst=0;     //this variable is being used to prevent program from braking
                            //caused by inserting two empty lines at the end of a file
        while(!bufforLine.isNull())
        {
            bufforLine = in.readLine();
            if(bufforLine != SelectedRow){  //if the read line is eql to data selected from a row
                                            //it won't rewrite it to the new file
                if(!safetyFirst)
                    out <<bufforLine;
                else out <<"\n"<< bufforLine;
                safetyFirst=true;
            }
        }

        fileIn.close();
        fileOut.close();

        remove("Books.txt"); //deleting the old file
        rename("BooksBuffor.txt","Books.txt"); //files' names cleaning
}
