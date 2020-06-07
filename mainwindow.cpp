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

//
//  BOOKS MANAGEMENT SECTION
//

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
        QMessageBox::information(this,"Succeess!","The books has been added",QMessageBox::Ok);
    }
    file.flush();
    file.close();
}

//function for finding an already existing book, with filters

void MainWindow::on_findBook_clicked()
{
    //the line doesn't work ui->tableWidget->clear(); //clears any leftovers from our table
    //int u = ui->tableWidget->rowCount()-1;
    QStringList columnHeaders;
    columnHeaders << "Title" << "Author's name" << "& surname" <<"Year of pub."<<
                     "Genere"<<"Owner";
    ui->tableWidget->setHorizontalHeaderLabels(columnHeaders);

    ui->tableWidgetUserBooks->setHorizontalHeaderLabels(columnHeaders);

    QFile file("Books.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    //ui->labelTest->setText("I'm here"+in.readLine()+in.readLine());
    QString bufforLine=".";
    QString bufforKey, bufforTitle, bufforFirstName,        //Line from .txt file; Key word from .txt; the others are to pass the metadata
            bufforSurname,bufforYear,bufforGenere, bufforPossessor; //of a found book to the ui table


    int bufforCount = -1;
    int bufforFalse = 0;            //this variable is to count the unmatching parameters (if 0 in the end, all of the
                                                                                            //chosen parameters are eql)
    while(!file.seek(-1)&&bufforCount<100){
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

            if (bufforCount == ui->tableWidget->rowCount()-1)ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                                                //the line above checkes is there is a need for a new row
                                                //and if so: inserts it
            if (bufforCount == ui->tableWidgetUserBooks->rowCount()-1)ui->tableWidgetUserBooks->insertRow(ui->tableWidgetUserBooks->rowCount());
            bufforCount++;

            ui->tableWidget->setItem(bufforCount, 0, new QTableWidgetItem(bufforTitle));
            ui->tableWidgetUserBooks->setItem(bufforCount, 0, new QTableWidgetItem(bufforTitle));

            ui->tableWidget->setItem(bufforCount, 1, new QTableWidgetItem(bufforFirstName));
            ui->tableWidgetUserBooks->setItem(bufforCount, 1, new QTableWidgetItem(bufforFirstName));

            ui->tableWidget->setItem(bufforCount, 2, new QTableWidgetItem(bufforSurname));
            ui->tableWidgetUserBooks->setItem(bufforCount, 2, new QTableWidgetItem(bufforSurname));

            ui->tableWidget->setItem(bufforCount, 3, new QTableWidgetItem(bufforYear));
            ui->tableWidgetUserBooks->setItem(bufforCount, 3, new QTableWidgetItem(bufforYear));

            ui->tableWidget->setItem(bufforCount, 4, new QTableWidgetItem(bufforGenere));
            ui->tableWidgetUserBooks->setItem(bufforCount, 4, new QTableWidgetItem(bufforGenere));

            ui->tableWidget->setItem(bufforCount, 5, new QTableWidgetItem(bufforPossessor));
            ui->tableWidgetUserBooks->setItem(bufforCount, 5, new QTableWidgetItem(bufforPossessor));

        }
    }
    file.close();
}

void MainWindow::on_deleteBook_clicked(){    //the method operates on two .txt files
                                            //(Books.txt and BooksBuffor.txt) rewrinting everyting except
                                            //data selected from the table (variable SelectedRow)
    int row = ui->tableWidget->currentRow();
    if (row==-1)QMessageBox::information(this,"Error","Please select book from table first",QMessageBox::Ok);
    else{

    QString SelectedRow;

    for(int col=0;col<6;col++)
    SelectedRow = SelectedRow + ui->tableWidget->item(row,col)->text() + '|';
                                            //SelectedRow collects data from the whole selected row
    ui->tableWidget->removeRow(row);
    ui->tableWidgetUserBooks->removeRow(row);

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
}

//
//  USERS MANAGEMENT SECTION
//

void MainWindow::on_submitUserAdd_clicked()
{
    QFile file("Users.txt");
    if(!file.open(QFile::WriteOnly|QFile::Text|QIODevice::Append)){
        return;
    }
    QTextStream out(&file);
    if(ui->inputUserID->text().isEmpty()||ui->inputUserFirstName->text().isNull()||                 //if the parameters are empty, the finding method breaks
            ui->inputUserSurname->text().isNull()||ui->inputUserEmail->text().isNull())                 //so this line prevents it
        QMessageBox::information(this,"Error","Please, fill all of the parameters",QMessageBox::Ok);

    else {
        out << ui->inputUserID->text()<<'$'<<ui->inputUserFirstName->text()<<'$'                     //if the parameters are all existing
        <<ui->inputUserSurname->text()<<'$'<<ui->inputUserEmail->text()<<"$0$\n";                      //the user can be added to the Users.txt

        QMessageBox::information(this,"Success!","The user has been added",QMessageBox::Ok);
    }
    file.flush();
    file.close();
}

void MainWindow::on_findUser_clicked()
{
    ui->tableWidgetUsers->clear(); //clears any leftovers from our table
    //int u = ui->tableWidget->rowCount()-1;
    QStringList columnHeaders;
    columnHeaders << "ID" << "User's name" << "& surname" <<"E-mail"<<"Number of books";
    ui->tableWidgetUsers->setHorizontalHeaderLabels(columnHeaders);

    QFile file("Users.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);

    QString bufforLine;
    QString bufforKey, bufforID, bufforFirstName,        //Line from .txt file; Key word from .txt; the others are to pass the metadata
            bufforSurname,bufforEmail,bufforPossessor;   //of a found user to the ui find user table


    int bufforCount = -1;
    int bufforFalse = 0;            //this variable is to count the unmatching parameters (if 0 in the end, all of the
                                                                                            //chosen parameters are eql)
    while(!file.seek(-1)&&bufforCount<100){
        bufforLine = in.readLine();                    //getting a line from the Users.txt file using QFileStream
        if(bufforLine.isNull())break;                  //check if the line, that we are going to operate on is not the end of the file, if so - the loop breaks
        bufforFalse = 0;                               //integer variable to for mettring missmatches

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('$'));    //passing only the title from bufforLine to bufforKey
            bufforLine.remove(bufforKey+'$');                                             //removing the taken Key word (here it is ID) from the current line

            if((ui->checkBoxUserID->isChecked())&&                            //if the filter (here it is ID) is turned on (checkBox is checked)
                    (bufforKey!=ui->inputUserID->text())) bufforFalse++;   //and ui key word value != file key word value,
                                                                             //we count that missmatch with bufforFalse mettring
            bufforID=bufforKey;


            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('$'));
            bufforLine.remove(bufforKey+'$');
            if((ui->checkBoxUserFirstName->isChecked())&&
                    (bufforKey!=ui->inputUserFirstName->text())) bufforFalse++;
            bufforFirstName=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('$'));
            bufforLine.remove(bufforKey+'$');
            if((ui->checkBoxUserSurname->isChecked())&&
                    (bufforKey!=ui->inputUserSurname->text())) bufforFalse++;
            bufforSurname=bufforKey;

            bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('$'));
            bufforLine.remove(bufforKey+'$');
            if((ui->checkBoxUserEmail->isChecked())&&
                    (bufforKey!=ui->inputUserEmail->text())) bufforFalse++;
            bufforEmail=bufforKey;

            bufforKey = bufforLine.remove('$'); //we have '$' to remove only
            bufforPossessor=bufforKey;



        if(bufforFalse==0){

            if (bufforCount == ui->tableWidgetUsers->rowCount()-1)ui->tableWidgetUsers->insertRow(ui->tableWidgetUsers->rowCount());
                                                //the line above checkes is there is a need for a new row
                                                //and if so: inserts it
            bufforCount++;

            ui->tableWidgetUsers->setItem(bufforCount, 0, new QTableWidgetItem(bufforID));
            ui->tableWidgetUsers->setItem(bufforCount, 1, new QTableWidgetItem(bufforFirstName));
            ui->tableWidgetUsers->setItem(bufforCount, 2, new QTableWidgetItem(bufforSurname));
            ui->tableWidgetUsers->setItem(bufforCount, 3, new QTableWidgetItem(bufforEmail));
            ui->tableWidgetUsers->setItem(bufforCount, 4, new QTableWidgetItem(bufforPossessor));
        }
    }
    file.close();

}

void MainWindow::on_deleteUser_clicked()
{
    int row = ui->tableWidgetUsers->currentRow();
    if (row==-1)QMessageBox::information(this,"Error","Please select user from table first",QMessageBox::Ok);
    else{
    QString SelectedRow;

    for(int col=0;col<5;col++)
    SelectedRow = SelectedRow + ui->tableWidgetUsers->item(row,col)->text() + '$';
                                            //SelectedRow collects data from the whole selected row
    ui->tableWidgetUsers->removeRow(ui->tableWidgetUsers->currentRow());
    QString bufforLine = ".";

    QFile fileIn("Users.txt");              //the file we'll read from
        if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
    QTextStream in(&fileIn);

    QFile fileOut("UsersBuffor.txt");       //the file we'll write to
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

        remove("Users.txt"); //deleting the old file
        rename("UsersBuffor.txt","Books.txt"); //files' names cleaning
        }
}

void MainWindow::on_giveBookToUser_clicked() //NEED'S REWORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
{
    int row = ui->tableWidgetUserBooks->currentRow(); //number of book's row is collected from a table
    int userRow = ui->tableWidgetUsers->currentRow(); //number of user's row is collected from a table
    if (row==-1||userRow==-1) //when row is at -1, it means it's nonexistant (in this case: none selected)
        QMessageBox::information(this,"Error","Please select book and user from tables first",QMessageBox::Ok);
    else{
    if (ui->tableWidgetUserBooks->item(row,5)->text()=="0"){ //if the book belongs to the library...
    QString id = ui->tableWidgetUsers->item(userRow,0)->text(); //getting id of the selected user
    QString SelectedRow; //this variable will hold line ready to replace into a buffor file

    for(int col=0;col<5;col++)
    SelectedRow = SelectedRow + ui->tableWidgetUserBooks->item(row,col)->text() + '|';
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
            if(!bufforLine.contains(SelectedRow)){  //if the read line is eql to data selected from a row
                                                    //it won't rewrite it to the new file
                if(!safetyFirst)
                    out <<bufforLine;
                else out <<"\n"<< bufforLine;
                safetyFirst=true;
            }
            else if(bufforLine.contains(SelectedRow)){
                SelectedRow = SelectedRow + ui->tableWidgetUsers->item(userRow,0)->text() + '|';
                                                    //completing the line with users ID number
                if(!safetyFirst)
                    out <<SelectedRow;
                else out <<"\n"<< SelectedRow;
                safetyFirst=true;
            }
        }
        ui->tableWidgetUserBooks->setItem(row, 5, new QTableWidgetItem(id)); //updating data on a table

        int amountOfBooks = ui->tableWidgetUsers->item(userRow,4)->text().toInt() + 1; //getting counter of books and increasing it by one

        ui->tableWidgetUsers->setItem(userRow, 4, new QTableWidgetItem(QString::number(amountOfBooks))); //setting higher book counter on a table

        QFile fileOutBookAmount("UsersBuffor.txt");       //the file we'll write to
            if(!fileOutBookAmount.open(QIODevice::WriteOnly|QIODevice::Text)){
                return;
            }

        QTextStream outBA(&fileOutBookAmount); //the code below is taking placing increased book counter (variable amountOfBooks) in user's data line

        QFile fileInBookAmount("Users.txt");       //the file we'll write to
            if(!fileInBookAmount.open(QIODevice::WriteOnly|QIODevice::Text)){
                return;
            }

        QTextStream inBA(&fileInBookAmount);

        for(int col=0;col<4;col++)
        SelectedRow = SelectedRow + ui->tableWidgetUsers->item(row,col)->text() + '$';

        bufforLine='.';
        safetyFirst=false;

        while(!bufforLine.isNull())
        {
            bufforLine = inBA.readLine();
            if(!bufforLine.contains(SelectedRow)){

                if(!safetyFirst)
                    outBA <<bufforLine;
                else outBA <<"\n"<< bufforLine;
                safetyFirst=true;
            }
            else if(bufforLine.contains(SelectedRow)){
                SelectedRow = SelectedRow + QString::number(amountOfBooks) + "$\n";
                if(!safetyFirst)
                    outBA <<SelectedRow;
                else outBA <<"\n"<< SelectedRow;
                safetyFirst=true;
            }
        }
        fileOutBookAmount.close();
        fileInBookAmount.close();
        fileIn.close();
        fileOut.close();

        remove("Books.txt"); //deleting the old file
        rename("Books.txt","BooksBuffor.txt"); //files' names cleaning
        remove("Users.txt"); //deleting the old file
        rename("Users.txt","UsersBuffor.txt"); //files' names cleaning


    }

    else QMessageBox::information(this,"Error","This book is not available",QMessageBox::Ok);
    }
}


void MainWindow::on_returnBookFromUser_clicked()
{
    int userRow = ui->tableWidgetUserBooks->currentRow();   //getting selected row's number from a table
    if(userRow!=-1){
    QString id = ui->tableWidgetUserBooks->item(ui->tableWidgetUserBooks->currentRow(),5)->text(); //getting id number from book table
    if(id!="0"){

        QString bufforLine = ".",
                SelectedRow;
        for(int col=0;col<5;col++)
                SelectedRow = SelectedRow + ui->tableWidgetUserBooks-> //creating line for replacement
                        item(userRow,col)->text() + '|';


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
                if(!bufforLine.contains(SelectedRow)){  //if the read line is eql to data selected from a row
                                                //it won't rewrite it to the new file
                    if(!safetyFirst)
                        out <<bufforLine;
                    else out <<"\n"<< bufforLine;
                    safetyFirst=true;
                }
                else if(bufforLine.contains(SelectedRow)){
                    SelectedRow = SelectedRow + "0|";
                    if(!safetyFirst)
                        out <<SelectedRow;
                    else out <<"\n"<< SelectedRow;
                    safetyFirst=true;
                }
            }

            fileIn.close();
            fileOut.close();

            remove("Books.txt"); //deleting the old file
            rename("BooksBuffor.txt","Books.txt"); //files' names cleaning

            QFile fileInUser("Users.txt");              //the file we'll read from
                if(!fileInUser.open(QIODevice::ReadOnly|QIODevice::Text)){
                    return;
                }
            QTextStream inUser(&fileInUser);

            QFile fileOutUser("UsersBuffor.txt");       //the file we'll write to
                if(!fileOutUser.open(QIODevice::WriteOnly|QIODevice::Text)){
                    return;
                }

            bufforLine='.';
            QTextStream outUser(&fileOutUser);
            safetyFirst=0;     //this variable is being used to prevent program from braking
                                    //caused by inserting two empty lines at the end of a file
                while(!bufforLine.isNull()){
                    bufforLine = inUser.readLine();
                    if(!bufforLine.contains(id)){  //if the read line is eql to data selected from a row
                                                    //it won't rewrite it to the new file
                        if(!safetyFirst)
                            outUser <<bufforLine;
                        else outUser <<"\n"<< bufforLine;
                        safetyFirst=true;
                    }
                    else if(bufforLine.contains(id)){
                        SelectedRow = bufforLine;
                        for(int i=0; i<4; i++){
                            bufforLine = bufforLine.remove(0,bufforLine.indexOf('$')+1);
                        }
                        SelectedRow.remove(bufforLine);
                        bufforLine = bufforLine.remove('$');
                        int amountOfBooks = bufforLine.toInt();
                        amountOfBooks--;

                        SelectedRow = SelectedRow + QString::number(amountOfBooks) + '$';

                        if(!safetyFirst)
                            outUser <<SelectedRow;
                        else outUser <<"\n"<< SelectedRow;
                        safetyFirst=true;
                    }
                }

                fileInUser.close();
                fileOutUser.close();

                remove("Users.txt"); //deleting the old file
                rename("UsersBuffor.txt","Users.txt"); //files' names cleaning

    }
    else QMessageBox::information(this,"Error","This book has been already returned",QMessageBox::Ok);
    }
    else QMessageBox::information(this,"Error","Please select the book, that has been delevered first",QMessageBox::Ok);
}
