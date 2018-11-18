#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>

std::string replaceAll(std::string str, std::string&& a, std::string&& b) {
        std::size_t found = str.find_first_of(a);
        while (found != std::string::npos)
        {
            str.replace(found, a.length(), b);
            found = str.find_first_of(a, found + 1);
        }
        return str;
}


std::string reverseStr(std::string& str){
    std::string result = "";
    for(auto it = str.rbegin(); it != str.rend() ; ++it){
        result += *it;
    }
    return result;
}
std::string toString(int num){
    if(num){
        std::string answer = "";
        while(num){
            answer += (num%10 + '0');
            num/=10;
        }
        answer = reverseStr(answer);
        return answer;
    }else return "0";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), rf(&this->hotel) , currentFile("")
{
    try{
    this -> ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->amountOutput->setText("Итого: 0$");
    QIcon icon("icon.ico");
    this->setWindowIcon(icon);
    this->on_lineEdit_editingFinished();
    }catch(std::bad_alloc){
        std::cerr << "Недостаточно памяти" << std::endl;
        QMessageBox::warning(0, "Ошибка!" , "Недостаточный объем свободной оперативной памяти!");
        on_action_4_triggered();
        exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_editingFinished()
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        ui->description->setText((this->hotel.getRoomDescription(num)).c_str());
        ui->amountOutput->setText((std::string("Итого: ") +
                                   toString(this->hotel.getAmount(num)) + "$").c_str());
        ui->rentorLabel->setText(this->hotel.getRenter(num).c_str());
        ui->cleaningCB->setChecked(this->hotel.isCleaning(num));
    }
    else{
        ui->description->setText("Номер не найден");
        ui->amountOutput->setText("");
        ui->rentorLabel->setText("Номер не существует");
        ui->cleaningCB->setChecked(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    try{
    this->hotel.addRoom(new Room(rf.getBaseRoomCost()));
    }catch(std::bad_alloc){
        std::cerr << "Недостаточно памяти" << std::endl;
        QMessageBox::warning(0, "Ошибка!" , "Недостаточный объем свободной оперативной памяти!");
        on_action_4_triggered();
        exit(1);
    }
    ui->lineEdit->setText(toString(this->hotel.getLastNum()).c_str());
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_pushButton_2_clicked()
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        try{
            auto search = this->hotel.find(num);
            Room *room = new FridgeUpgrade(search->second , rf.getFridgeCost());
            search->second = room;
            this->on_lineEdit_editingFinished();
        }catch(std::bad_alloc){
            std::cerr << "Недостаточно памяти" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Недостаточный объем свободной оперативной памяти!");
            on_action_4_triggered();
            exit(1);
        }catch(std::exception){
            std::cerr << "Непредусмотренное исключение" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Непредусмотренное исключение!\nОсвободите память и попробуйте снова(Работа программы будет остановлена)");
            on_action_4_triggered();
            exit(1);
        }
    }

    //this->hotel.addRoom(ui->lineEdit->text().toInt() , room);
}

void MainWindow::on_pushButton_3_clicked()
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        try{
        auto search = this->hotel.find(num);
        Room *room = new RoomUpgrade(search->second , rf.getAddRoomCost());
        search->second = room;
        this->on_lineEdit_editingFinished();
        }catch(std::bad_alloc){
            std::cerr << "Недостаточно памяти" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Недостаточный объем свободной оперативной памяти!");
            on_action_4_triggered();
            exit(1);
        }catch(std::exception){
            std::cerr << "Непредусмотренное исключение" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Непредусмотренное исключение!\nОсвободите память и попробуйте снова(Работа программы будет остановлена)");
            on_action_4_triggered();
            exit(1);
        }
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        try{
        auto search = this->hotel.find(num);
        Room *room = new BagaUpgrade(search->second , rf.getBagaCost());
        search->second = room;
        this->on_lineEdit_editingFinished();
        }catch(std::bad_alloc){
            std::cerr << "Недостаточно памяти" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Недостаточный объем свободной оперативной памяти!");
            on_action_4_triggered();
            exit(1);
        }catch(std::exception){
            std::cerr << "Непредусмотренное исключение" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Непредусмотренное исключение!\nОсвободите память и попробуйте снова(Работа программы будет остановлена)");
            on_action_4_triggered();
            exit(1);
        }
    }

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    /*int num = ui->lineEdit->text().toInt();
    auto search = this->hotel.rooms.find(ui->lineEdit->text().toInt())->second;
    if(this->hotel.roomExist(num))
        search->changeStatus();*/
    this->on_lineEdit_editingFinished();
}


void MainWindow::on_action_triggered() //save how
{
    QFileDialog fd;
    QString name = fd.getSaveFileName(0, "Сохранение" , "" , "*.hl");
    std::ofstream fout;
    fout.open(name.toStdString());
    fout << this->hotel.getLastNum() << '\n';
    for(auto &el : this->hotel){
        fout << el.second->getCode() << ' ';
        std::string name = el.second->getRenter();
        name = replaceAll(name , " " , "_");
        fout << name << ' ';
        fout <<  el.second->isCleaning() << '\n';
    }
    fout.close();
    this->on_lineEdit_editingFinished();
}



void MainWindow::on_action_2_triggered() //open
{
    QFileDialog fd;
    QString name = fd.getOpenFileName(0, "Открытие" , "" , "*.hl");
    this->currentFile = name.toStdString();
    std::ifstream fin;
    std::string str;
    std::string renter;
    std::string cleaning;
    fin.open(name.toStdString());
    fin >> str;
    int num = QString(str.c_str()).toInt();
    this->hotel.clear();
    for(int i = 0; i < num; ++i){
        fin >> str;
        this->rf.createRoom(str);
        fin >> renter;
        renter = replaceAll(renter , "_", " ");
        this->hotel.setRenter(i+1 , renter);
        fin >> cleaning;
        if(cleaning == "1") this->hotel.changeCleaningStatus(i+1);
    }
    this->on_lineEdit_editingFinished();
    fin.close();
}

void MainWindow::on_action_3_triggered() //new
{
    this->hotel.clear();
    ui->lineEdit->setText("1");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_pushButton_5_clicked() //media
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        try{
        auto search = this->hotel.find(num);
        Room *room = new MediaUpgrade(search->second , rf.getMediaCost());
        search->second = room;
        this->on_lineEdit_editingFinished();
        }catch(std::bad_alloc){
            std::cerr << "Недостаточно памяти" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Недостаточный объем свободной оперативной памяти!");
            on_action_4_triggered();
            exit(1);
        }catch(std::exception){
            std::cerr << "Непредусмотренное исключение" << std::endl;
            QMessageBox::warning(0, "Ошибка!" , "Непредусмотренное исключение!\nОсвободите память и попробуйте снова(Работа программы будет остановлена)");
            on_action_4_triggered();
            exit(1);
        }
    }
}

void MainWindow::on_action_4_triggered() // save
{
    std::ofstream fout;
    fout.open(this->currentFile);
    fout << this->hotel.getLastNum() << '\n';
    for(auto &el : this->hotel){
        fout << el.second->getCode() << ' ';
        std::string name = el.second->getRenter();
        name = replaceAll(name , " " , "_");
        fout << name << ' ';
        fout <<  el.second->isCleaning() << '\n';
    }
    fout.close();
    this->on_lineEdit_editingFinished();
    QMessageBox::information(0 , "Оповещение", "Файл успешно сохранен" );
}

void MainWindow::on_getForRentButton_clicked()
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        if(this->hotel.getRenter(num) == "Номер свободен" && !this->hotel.isCleaning(num)){
        QString name = QInputDialog::getText(0, "Сдать в аренду" , "ФИО съемщика" ,
                              QLineEdit::Normal , "ФИО");
        int num = ui->lineEdit->text().toInt();
        this->hotel.setRenter(num , name.toStdString());
        }
        else if(this->hotel.isCleaning(num)){
            QMessageBox::information(0 , "Оповещение", "В номере проводится уборка!" );
        }
        else{
            QMessageBox::information(0 , "Оповещение", "Номер уже сдается!" );
        }
    }
    else {
        QMessageBox::information(0 , "Оповещение", "Данный номер не существует!" );
    }

    this->on_lineEdit_editingFinished();
}

void MainWindow::on_cleaningCB_stateChanged(int arg1)
{
    /*int num = ui->lineEdit->text().toInt();
    this->hotel.changeCleaningStatus(num);
    this->on_lineEdit_editingFinished();*/
}

void MainWindow::on_cleaningCB_clicked()
{
    int num = ui->lineEdit->text().toInt();
    if(num <= this->hotel.getLastNum())
        if(this->hotel.getRenter(num) == "Номер свободен")
        this->hotel.changeCleaningStatus(num);
        else{
            QMessageBox::information(0 , "Оповещение", "Номер занят, уборку проводить нельзя!" );
        }
    else QMessageBox::information(0 , "Оповещение", "Номер не существует" );
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_freeRoom_clicked()
{
    int num = ui->lineEdit->text().toInt();
    if(this->hotel.roomExist(num)){
        if(this->hotel.getRenter(num) != "Номер свободен"){
            this->hotel.setRenter(num,"Номер свободен");
            this->on_lineEdit_editingFinished();
            QMessageBox::information(0 , "Оповещение" , "Номер освобожден");
        }
        else{
            QMessageBox::information(0, "Оповещение" , "Номер уже свободен");
        }
    }else{
        QMessageBox::information(0, "Оповещение" , "Номер не существует");
    }
}

void MainWindow::on_deleteRoomButton_clicked()
{
    int num = ui->lineEdit->text().toInt();
    this->hotel.removeUpgrade(num , "2");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_deleteBagaButton_clicked()
{
    int num = ui->lineEdit->text().toInt();
    this->hotel.removeUpgrade(num , "3");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_deleteFridgeButton_clicked()
{
    int num = ui->lineEdit->text().toInt();
    this->hotel.removeUpgrade(num , "1");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_deleteMediaButton_clicked()
{
    int num = ui->lineEdit->text().toInt();
    this->hotel.removeUpgrade(num , "4");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_action_5_triggered()
{
    std::string cost = toString(QInputDialog::getInt(0, "Изменить стоимость базовой комнаты" , "Цена:"));
    rf.setBaseRoomCost(cost);
    QMessageBox::information(0 , "Оповещение", "Для полного действия изменений перезапустите программу\nДо тех пор изменения будут работать только для новых комнат");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_action_6_triggered()
{
    std::string cost = toString(QInputDialog::getInt(0, "Изменить стоимость дополнительной комнаты" , "Цена:"));
    rf.setAddRoomCost(cost);
    QMessageBox::information(0 , "Оповещение", "Для полного действия изменений перезапустите программу\nДо тех пор изменения будут работать только для новых комнат");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_action_7_triggered()
{
    std::string cost = toString(QInputDialog::getInt(0, "Изменить стоимость Баги" , "Цена:"));
    rf.setBagaCost(cost);
    QMessageBox::information(0 , "Оповещение", "Для полного действия изменений перезапустите программу\nДо тех пор изменения будут работать только для новых комнат");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_action_9_triggered()
{
    std::string cost = toString(QInputDialog::getInt(0, "Изменить стоимость медиацентра" , "Цена:"));
    rf.setMediaCost(cost);
    QMessageBox::information(0 , "Оповещение", "Для полного действия изменений перезапустите программу\nДо тех пор изменения будут работать только для новых комнат");
    this->on_lineEdit_editingFinished();
}

void MainWindow::on_action_8_triggered()
{
    std::string cost = toString(QInputDialog::getInt(0, "Изменить стоимость холодильника" , "Цена:"));
    rf.setFridgeCost(cost);
    QMessageBox::information(0 , "Оповещение", "Для полного действия изменений перезапустите программу\nДо тех пор изменения будут работать только для новых комнат");
    this->on_lineEdit_editingFinished();
}
