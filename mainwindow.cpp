#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QChar>
#include <QPushButton>
#include <QLineEdit>
#include<QAbstractItemView>

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
    if(MainWindow::dataValidation_books(false)){
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
}

//function for finding an already existing book, with filters

void MainWindow::on_findBook_clicked()
{
    if(MainWindow::dataValidation_books(true)){
    ui->tableWidget->clear(); //clears any leftovers from our table //it did work
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
}

void MainWindow::on_deleteBook_clicked(){
                                             //the method operates on two .txt files
                                            //(Books.txt and BooksBuffor.txt) rewrinting everyting except
                                            //data selected from the table (variable SelectedRow)
    if (ui->tableWidget->currentRow()<0)QMessageBox::information(this,"Error","Please select book from table first",QMessageBox::Ok);
    else{

    if(ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text()=="0"){
    int row = ui->tableWidget->currentRow();



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
        else QMessageBox::information(this,"Error","Before wiping data about the book, it must be returned to the library",QMessageBox::Ok);
    }
}

//
//  USERS MANAGEMENT SECTION
//

void MainWindow::on_submitUserAdd_clicked()
{
    if(MainWindow::dataValidation_users(false)){

    //Now, we are going to check if the Id is already existing in the file
    //isIiAlreadyThere will show us if id or email is already existing
    bool isItAlreadyThere = false;
    QFile fileIdCheck("Users.txt");
    if(!fileIdCheck.open(QFile::ReadOnly|QFile::Text)){
        return;
    }
    QTextStream in(&fileIdCheck);
    QString bufforLine = in.readLine();
    while(!bufforLine.isNull()){
        if(bufforLine.contains('$'+ui->inputUserID->text()+'$')||bufforLine.contains('$'+ui->inputUserEmail->text()+'$'))isItAlreadyThere=true;
                bufforLine = in.readLine();
    }
    fileIdCheck.close();
    //
    if(!isItAlreadyThere){
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
    else QMessageBox::information(this,"Error","The email or id number has been already used!",QMessageBox::Ok);
    }
}

void MainWindow::on_findUser_clicked()
{
    if(MainWindow::dataValidation_users(true)){
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
}

void MainWindow::on_deleteUser_clicked()
{
    int row = ui->tableWidgetUsers->currentRow();
    if (row==-1)QMessageBox::information(this,"Error","Please select user from table first",QMessageBox::Ok);
    else{
        if(ui->tableWidgetUsers->item(row,4)->text()=='0'){ //if the user still has any books on his counter,
                                                          //our system won't allow to delete his account
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
        else QMessageBox::information(this,"Error","Cannot delete the user, until he doesn't return books",QMessageBox::Ok);
    }
    }

void MainWindow::on_giveBookToUser_clicked()
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
            if(!fileInBookAmount.open(QIODevice::ReadOnly|QIODevice::Text)){
                return;
            }

        QTextStream inBA(&fileInBookAmount);

        SelectedRow.clear();

        for(int col=0;col<4;col++)
        SelectedRow = SelectedRow + ui->tableWidgetUsers->item(userRow,col)->text() + '$';

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
                SelectedRow = SelectedRow + QString::number(amountOfBooks) + "$";
                if(!safetyFirst)
                    outBA <<SelectedRow;
                else outBA <<"\n"<< SelectedRow;
                safetyFirst=true;
            }
        }
        fileOutBookAmount.close();
        fileOutBookAmount.flush();
        fileInBookAmount.close();
        fileIn.close();
        fileOut.close();
        fileOut.flush();

        remove("Books.txt"); //deleting the old file
        rename("BooksBuffor.txt","Books.txt"); //files' names cleaning
        remove("Users.txt"); //deleting the old file
        rename("UsersBuffor.txt","Users.txt"); //files' names cleaning


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
            fileIn.flush();
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
            int amountOfBooks;
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
                        amountOfBooks = bufforLine.toInt();
                        amountOfBooks--;

                        SelectedRow = SelectedRow + QString::number(amountOfBooks) + '$';

                        if(!safetyFirst)
                            outUser <<SelectedRow;
                        else outUser <<"\n"<< SelectedRow;
                        safetyFirst=true;
                    }
                }

                fileInUser.close();
                fileInUser.flush();
                fileOutUser.close();

                remove("Users.txt"); //deleting the old file
                rename("UsersBuffor.txt","Users.txt"); //files' names cleaning
                ui->tableWidgetUserBooks->setItem(ui->tableWidgetUserBooks->currentRow(),5,new QTableWidgetItem("0"));
                ui->tableWidgetUsers->clearContents();
                MainWindow::on_findUser_clicked();
                QMessageBox::information(this,"Success!","Book retunred",QMessageBox::Ok);
    }
    else QMessageBox::information(this,"Error","This book has been already returned!",QMessageBox::Ok);
    }
    else QMessageBox::information(this,"Error","Please select the book, that has been delevered first",QMessageBox::Ok);
}

void MainWindow::on_editUserBooks_clicked()
{
    if(ui->tableWidgetUsers->currentRow()>0){
    int j=0;
    int userRow = ui->tableWidgetUsers->currentRow();   //getting selected row's number from a table
    QString bufforKey,id = ui->tableWidgetUsers->item(userRow,0)->text();

        ui->tableWidgetUserBooks->clearContents(); //clearing table before writing on it

        QFile file("Books.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
        QTextStream in(&file);
        QString bufforLine=in.readLine();
        while(!bufforLine.isEmpty()){
            if(bufforLine.contains(id)){ //if the line contains id number of our user, it's the books he has borrowed
                for (int i=0; 6>i; i++) {
                    bufforKey=bufforLine.chopped(bufforLine.length()-bufforLine.indexOf('|')); //in this loop we get the whole line chopped
                    bufforLine.remove(bufforKey+'|');
                    if(i==5)bufforKey.remove('|');
                    ui->tableWidgetUserBooks->setItem(j,i,new QTableWidgetItem(bufforKey));    //and pushed to book's table's cells

                }
                j++;    //this iteration is getting every result in higher and higher (by number) rows
            }
            bufforLine=in.readLine();
        }

    }
    else QMessageBox::information(this,"Error","Please select the user first",QMessageBox::Ok);
}

bool MainWindow::dataValidation_books(bool search){
    bool check=true;
    bool raportFirstName=true;
    bool raportSurname=true;
    bool raportYear=true;

    //FILTERERS CHECK:
    bool filterFirstName = ui->checkBoxFirstName->isChecked();
    bool filterSurname = ui->checkBoxSurname->isChecked();
    bool filterYear = ui->checkBoxYear->isChecked();

    //NAMES VALIDATION (BASED ON ASCII SIGNS OUTCLUDE)

    //FIRST NAME

    //Getting input to a buffor string
    QString stringBuffor= ui->inputAddFirstName->text();

    //If user decides to be very unkind to the program and inputs many ' '
    //we remove the trush right here
    while(stringBuffor[0]==' ')
        stringBuffor.remove(0,1);
    for (int i = 1;stringBuffor.length()>i;i++) {
        while(stringBuffor[i]==' '&&stringBuffor[i+1]==' ')
            stringBuffor.remove(i,1);
    }

    //Formatting incorect (in mean of capitalization) input text
    QChar a = stringBuffor[0].toUpper();
    stringBuffor[0]=a;

    for (int i=1;stringBuffor.length()>i;i++) {
        if(stringBuffor[i-1].isUpper())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1].isLower())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1]==' ')a = stringBuffor[i].toUpper();
        else if(stringBuffor[i-1]=='-')a = stringBuffor[i].toUpper();
        else a = stringBuffor[i];
        stringBuffor[i] = a;
    }

    if((search==true&&filterFirstName==true)||search==false){

    //Input cannot be longer than 64 characters (should be enought for a name)
        if(stringBuffor.length()>63) raportFirstName = false;

    //Checking every character in the input (if isn't letter, '-', or ' ')
    for(int i=0;i<stringBuffor.length();i++){
        if(!(stringBuffor[i].isLetter())&&(stringBuffor[i]!='-')&&(stringBuffor[i]!=' '))
            raportFirstName=false;
    }
    }
    //if the input is valid, we put the formatted data back to the textline we took it from
    if(raportFirstName&&filterFirstName)ui->inputAddFirstName->setText(stringBuffor);

    //END OF FIRST NAME VALIDATION

    //SURNAME

    stringBuffor= ui->inputAddSurname->text();

    //If user decides to be very unkind to the program and inputs many ' '
    //we remove the trush right here
    while(stringBuffor[0]==' ')
        stringBuffor.remove(0,1);
    for (int i = 1;stringBuffor.length()>i;i++) {
        while(stringBuffor[i]==' '&&stringBuffor[i+1]==' ')
            stringBuffor.remove(i,1);
    }

    //Formatting incorect (in mean of capitalization) input text
    a = stringBuffor[0].toUpper();
    stringBuffor[0] = a;

    for (int i=1;stringBuffor.length()>i;i++) {
        if(stringBuffor[i-1].isUpper())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1].isLower())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1]==' ')a = stringBuffor[i].toUpper();
        else if(stringBuffor[i-1]=='-')a = stringBuffor[i].toUpper();
        else a = stringBuffor[i];
        stringBuffor[i] = a;
    }

    if((search==true&&filterSurname==true)||search==false){

    //Input cannot be longer than 64 characters (should be enought for a name)
    if(stringBuffor.length()>63) raportSurname = false;

    //Checking every character in the input (if isn't letter, '-', or ' ')
    for(int i=0;i<stringBuffor.length();i++){
        if(!(stringBuffor[i].isLetter())&&(stringBuffor[i]!='-')&&(stringBuffor[i]!=' '))
            raportSurname=false;
        }
    }
    //if the input is valid, we put the formatted data back to the textline we took it from
    if(raportSurname&&filterSurname)ui->inputAddSurname->setText(stringBuffor);

    //END OF SURNAME VALIDATION

    //END OF NAMES VALIDATION

    //YEAR'S VALIDATION
    //(ASCII: 48-58 AND MAX 4 DIGITS INCLUDING '-' IN THE BEGGINING)

    if((search==true&&filterYear==true)||search==false){
    if(ui->inputAddYear->text().length()>4) raportYear=false;
    for(int i=32;i<48;i++){
    if(i!='-'){
    if(ui->inputAddYear->text().contains(i)) raportYear=false;
    }
    else{if(ui->inputAddYear->text().indexOf('-')>0) raportYear=false;}
    }

    for(int i=58;i<127;i++){
    if(ui->inputAddYear->text().contains(i)) raportYear=false;
    }
    }

    //END OF YEAR'S VALIDATION



    //FEEDBACK ON WHAT'S WRONG USING MESSAGEBOXES

    if(raportFirstName==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed first name (cannot use special characters and start with a capital letter and isn't longer than 64 characteres)",QMessageBox::Ok);
        check=false;
    }

    if(raportSurname==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed surname (cannot use special characters and start with a capital letter and isn't longer than 64 characters)",QMessageBox::Ok);
        check=false;
    }

    if(raportYear==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed year (choose from -999 to 9999)",QMessageBox::Ok);
        check=false;
    }

    //END OF FEEDBACK

    return check;
}

bool MainWindow::dataValidation_users(bool search){

    bool check=true;
    bool raportId=true;
    bool raportFirstName=true;
    bool raportSurname=true;
    bool raportEmail=true;

    //FILTERERS CHECK:
    bool filterFirstName = ui->checkBoxUserFirstName->isChecked();
    bool filterSurname = ui->checkBoxUserSurname->isChecked();
    bool filterId = ui->checkBoxUserID->isChecked();
    bool filterEmail = ui->checkBoxUserEmail->isChecked();

    //ID'S VALIDATION
    //(ASCII: 48-58 AND MAX 20 DIGITS MIN 1 AND NOT SMALLER THAN 1 [0 IS RESERVED FOR THE LIBRARY])

    if((search==true&&filterId==true)||search==false){
    if(ui->inputUserID->text().length()>20||(ui->inputUserID->text().toLong())<1) raportId=false;
    for(int i=32;i<48;i++){
    if(ui->inputUserID->text().contains(i)) raportId=false;
    }

    for(int i=58;i<127;i++){
    if(ui->inputUserID->text().contains(i)) raportId=false;
    }
    }

    //END OF ID'S VALIDATION

    //NAMES VALIDATION (BASED ON ASCII SIGNS OUTCLUDE)

    //FIRST NAME

    //Getting input to a buffor string
    QString stringBuffor= ui->inputUserFirstName->text();

    //If user decides to be very unkind to the program and inputs many ' '
    //we remove the trush right here
    while(stringBuffor[0]==' ')
        stringBuffor.remove(0,1);
    for (int i = 1;stringBuffor.length()>i;i++) {
        while(stringBuffor[i]==' '&&stringBuffor[i+1]==' ')
            stringBuffor.remove(i,1);
    }

    //We've observed that there is space sign automatically added to textline when clicked
    //so right there we are preventing the user from raging
    if(stringBuffor[0]==' ')stringBuffor.remove(0,1);

    //Formatting incorect (in mean of capitalization) input text
    QChar a = stringBuffor[0].toUpper();
    stringBuffor[0]=a;

    for (int i=1;stringBuffor.length()>i;i++) {
        if(stringBuffor[i-1].isUpper())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1].isLower())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1]==' ')a = stringBuffor[i].toUpper();
        else if(stringBuffor[i-1]=='-')a = stringBuffor[i].toUpper();
        else a = stringBuffor[i];
        stringBuffor[i] = a;
    }

    if((search==true&&filterFirstName==true)||search==false){

    //Input cannot be longer than 64 characters (should be enought for a name)
        if(stringBuffor.length()>63) raportFirstName = false;

    //Checking every character in the input (if isn't letter, '-', or ' ')
    for(int i=0;i<stringBuffor.length();i++){
        if(!(stringBuffor[i].isLetter())&&(stringBuffor[i]!='-')&&(stringBuffor[i]!=' '))
            raportFirstName=false;
    }
    }
    //if the input is valid, we put the formatted data back to the textline we took it from
    if(raportFirstName&&filterFirstName)ui->inputUserFirstName->setText(stringBuffor);

    //END OF FIRST NAME VALIDATION

    //SURNAME

    stringBuffor = ui->inputUserSurname->text();

    //If user decides to be very unkind to the program and inputs many ' '
    //we remove the trush right here
    while(stringBuffor[0]==' ')
        stringBuffor.remove(0,1);
    for (int i = 1;stringBuffor.length()>i;i++) {
        while(stringBuffor[i]==' '&&stringBuffor[i+1]==' ')
            stringBuffor.remove(i,1);
    }


    //Formatting incorect (in mean of capitalization) input text
    a = stringBuffor[0].toUpper();
    stringBuffor[0] = a;

    for (int i=1;stringBuffor.length()>i;i++) {
        if(stringBuffor[i-1].isUpper())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1].isLower())a = stringBuffor[i].toLower();
        else if(stringBuffor[i-1]==' ')a = stringBuffor[i].toUpper();
        else if(stringBuffor[i-1]=='-')a = stringBuffor[i].toUpper();
        else a = stringBuffor[i];
        stringBuffor[i] = a;
    }

    if((search==true&&filterSurname==true)||search==false){

    //Input cannot be longer than 64 characters (should be enought for a name)
    if(stringBuffor.length()>63) raportSurname = false;

    //Checking every character in the input (if isn't letter, '-', or ' ')
    for(int i=0;i<stringBuffor.length();i++){
        if(!(stringBuffor[i].isLetter())&&(stringBuffor[i]!='-')&&(stringBuffor[i]!=' '))
            raportSurname=false;
        }
    }
    //if the input is valid, we put the formatted data back to the textline we took it from
    if(raportSurname&&filterSurname)ui->inputUserSurname->setText(stringBuffor);

    //END OF NAMES VALIDATION

    //END OF SURNAME VALIDATION



    //EMAIL VALIDATION
    //address validation:3 - 32 CHARS, A-Z, 0-9, ".", "_", STARTS WITH A LETTER

    stringBuffor= ui->inputUserEmail->text();

    //If user decides to be very unkind to the program and inputs many ' '
    //we remove the trush right here
    while(stringBuffor[0]==' ')
        stringBuffor.remove(0,1);
    for (int i = 1;stringBuffor.length()>i;i++) {
        while(stringBuffor[i]==' '&&stringBuffor[i+1]==' ')
            stringBuffor.remove(i,1);
    }

    //Formatting incorect (in mean of capitalization) input text
    a = stringBuffor[0].toLower();
    stringBuffor[0] = a;

    for (int i=1;stringBuffor.length()>i;i++) {
        if(stringBuffor[i].isUpper())a = stringBuffor[i].toLower();
        else a = stringBuffor[i];
        stringBuffor[i] = a;
    }

    if((search==true&&filterEmail==true)||search==false){

    //Input cannot be longer than 254 characters (should be enought for a name)
    if(stringBuffor.length()>254) raportEmail = false;

    //Since in email there can be only one '@' we need to prevent the user from inputting more than one
    //by getting position of the first one, and allowing it only in that perticular possision
    int monkeyPossition = stringBuffor.indexOf('@');
    //if there is none, the input is valid
    if(monkeyPossition == -1)raportEmail=false;

    //Checking every character in the input (if isn't letter, '.', or '_', or one '@')
    for(int i=0;i<stringBuffor.length();i++){
        if(!(stringBuffor[i].isLetter())&&(stringBuffor[i]!='.')&&(stringBuffor[i]!='_')&&(stringBuffor[i]!='@'))
            raportEmail=false;
        if (stringBuffor[i]=='@'){
            if (i!=monkeyPossition)
                raportEmail=false;
        }
        }
    }
    //if the input is valid, we put the formatted data back to the textline we took it from
    if(raportEmail&&filterEmail)ui->inputUserEmail->setText(stringBuffor);


    //END OD EMAIL VALIDATION


    //FEEDBACK ON WHAT'S WRONG USING MESSAGEBOXES

    if(raportFirstName==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed first name (cannot use special characters and start with a capital letter and cannot be longer than 64 characteres)",QMessageBox::Ok);
        check=false;
    }

    if(raportSurname==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed surname (cannot use special characters and start with a capital letter and cannot be longer than 64 characteres)",QMessageBox::Ok);
        check=false;
    }

    if(raportId==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed ID number (choose from 1 to 999999999)\nWe highly recommend using phone numbers as ID numbers",QMessageBox::Ok);
        check=false;
    }

    if(raportEmail==false){
        QMessageBox::information(this,"Error","Incorrect format of the inputed ID e-mail (a-z, 0-9, '.', '_', starts with a letter + @your_email_domain)",QMessageBox::Ok);
        check=false;
    }

    //END OF FEEDBACK

    return check;
}

void  MainWindow::dataInFileReplace(QString inFileName, QString outFileName, QString searchRow, QString replaceRow){

    QString bufforLine = ".";

    QFile fileIn(inFileName);              //the file we'll read from
        if(!fileIn.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
    QTextStream in(&fileIn);

    QFile fileOut(outFileName);       //the file we'll write to
        if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text)){
            return;
        }

    QTextStream out(&fileOut);
    bool safetyFirst=0;     //this variable is being used to prevent program from braking
                            //caused by inserting two empty lines at the end of a file
        while(!bufforLine.isNull())
        {
            bufforLine = in.readLine();
            if(bufforLine != searchRow){  //if the read line is eql to data selected from a row
                                            //it won't rewrite it to the new file
                if(!safetyFirst)
                    out <<bufforLine;
                else out <<"\n"<< bufforLine;
                safetyFirst=true;
            }
            else{
                if(!safetyFirst)
                    out <<replaceRow;
                else out <<"\n"<< replaceRow;
                safetyFirst=true;
            }
        }

        fileIn.close();
        fileOut.close();

        remove("Books.txt"); //deleting the old file
        rename("BooksBuffor.txt","Books.txt"); //files' names cleaning
}

void MainWindow::on_editBook_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if(currentRow!=-1){
        //the line below ensure's us, that there is any data checked to be swaped
    if(ui->checkBoxTitle->isChecked()||ui->checkBoxFirstName->isChecked()||ui->checkBoxSurname->isChecked()||ui->checkBoxYear->isChecked()||ui->checkBoxGenere->isChecked()){
    if(MainWindow::dataValidation_books(true)){
        QString searchRow, replaceRow, bufforReplacement;
        //searchRow is the string that imitates the line we'd like to change
        //replaceRow is the string we are going to put into the file in the place of the outdated data
        //bufforReplacement is here se we can create replaceRow based on searchRow
        for (int i = 0; i<6 ;i++) {
            bufforReplacement = ui->tableWidget->item(currentRow,i)->text();
            searchRow = searchRow + bufforReplacement + '|';

            if(i==0&&ui->checkBoxTitle->isChecked()){
            replaceRow = replaceRow + ui->inputAddTitle->text() + '|';
            ui->tableWidget->setItem(currentRow,i,new QTableWidgetItem(ui->inputAddTitle->text()));
            }

            else if(i==1&&ui->checkBoxFirstName->isChecked()){
            replaceRow = replaceRow + ui->inputAddFirstName->text() + '|';
            ui->tableWidget->setItem(currentRow,i,new QTableWidgetItem(ui->inputAddFirstName->text()));
            }

            else if(i==2&&ui->checkBoxSurname->isChecked()){
            replaceRow = replaceRow + ui->inputAddSurname->text() + '|';
            ui->tableWidget->setItem(currentRow,i,new QTableWidgetItem(ui->inputAddSurname->text()));
            }

            else if(i==3&&ui->checkBoxYear->isChecked()){
            replaceRow = replaceRow + ui->inputAddSurname->text() + '|';
            ui->tableWidget->setItem(currentRow,i,new QTableWidgetItem(ui->inputAddYear->text()));
            }

            else if(i==4&&ui->checkBoxGenere->isChecked()){
            replaceRow = replaceRow + ui->inputAddGenere->currentText() + '|';
            ui->tableWidget->setItem(currentRow,i,new QTableWidgetItem(ui->inputAddGenere->currentText()));
            }

            else replaceRow = replaceRow + bufforReplacement + '|';
        }

       MainWindow::dataInFileReplace("Books.txt", "BooksBuffor.txt", searchRow, replaceRow);
       QMessageBox::information(this,"Success!","Books has been edited",QMessageBox::Ok);
    }
    }
    else QMessageBox::information(this,"Error","Please check the equivalent checkboxes for the parameters of the book, you want to edit",QMessageBox::Ok);
    }
    else QMessageBox::information(this,"Error","Please, select the book from the table first",QMessageBox::Ok);
}

void MainWindow::on_editUser_clicked()
{
    int currentRow = ui->tableWidgetUsers->currentRow();
    if(currentRow!=-1){
        //the line below ensure's us, that there is any data checked to be swaped
    if(ui->checkBoxUserID->isChecked()||ui->checkBoxUserFirstName->isChecked()||ui->checkBoxUserSurname->isChecked()||ui->checkBoxUserEmail->isChecked()){
    if(MainWindow::dataValidation_users(true)){
        QString searchRow, replaceRow, bufforReplacement;
        //searchRow is the string that imitates the line we'd like to change
        //replaceRow is the string we are going to put into the file in the place of the outdated data
        //bufforReplacement is here se we can create replaceRow based on searchRow
        for (int i = 0; i<5 ;i++) {
            bufforReplacement = ui->tableWidgetUsers->item(currentRow,i)->text();
            searchRow = searchRow + bufforReplacement + '|';

            if(i==0&&ui->checkBoxUserID->isChecked()){
            replaceRow = replaceRow + ui->inputUserID->text() + '|';
            ui->tableWidgetUsers->setItem(currentRow,i,new QTableWidgetItem(ui->inputUserID->text()));
            }

            else if(i==1&&ui->checkBoxUserFirstName->isChecked()){
            replaceRow = replaceRow + ui->inputUserFirstName->text() + '|';
            ui->tableWidgetUsers->setItem(currentRow,i,new QTableWidgetItem(ui->inputUserFirstName->text()));
            }

            else if(i==2&&ui->checkBoxUserSurname->isChecked()){
            replaceRow = replaceRow + ui->inputUserSurname->text() + '|';
            ui->tableWidgetUsers->setItem(currentRow,i,new QTableWidgetItem(ui->inputUserSurname->text()));
            }

            else if(i==3&&ui->checkBoxUserEmail->isChecked()){
            replaceRow = replaceRow + ui->inputUserEmail->text() + '|';
            ui->tableWidgetUsers->setItem(currentRow,i,new QTableWidgetItem(ui->inputUserEmail->text()));
            }

            else replaceRow = replaceRow + bufforReplacement + '|';
        }

       MainWindow::dataInFileReplace("Books.txt", "BooksBuffor.txt", searchRow, replaceRow);
       QMessageBox::information(this,"Success!","User has been edited",QMessageBox::Ok);
    }

    }
    else QMessageBox::information(this,"Error","Please check the equivalent checkboxes for the parameters of the user, you want to edit",QMessageBox::Ok);
    }
    else QMessageBox::information(this,"Error","Please, select the user from the table first",QMessageBox::Ok);
}
