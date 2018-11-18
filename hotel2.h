#ifndef HOTEL2_H
#define HOTEL2_H
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <exception>
#include <QMessageBox>
#include "mainwindow.h"




class Room{
public:

    Room(){
        this->amount = "10";
        this->description = "Одна комната + " + this->amount + "$/сутки\n";
        this->code = "0";
        this->renter = "Номер свободен";
        this->cleaning = false;
    }
    Room(std::string amount){
        this->amount = amount;
        this->description = std::string("Одна комната + ") + this->amount + "$/сутки\n";
        this->code = "0";
        this->renter = "Номер свободен";
        this->cleaning = false;
    }
    /*Room(const Room& other){
        this->description = other.description;
        this->amount = other.amount;
        this->code = other.code;
        this->renter = other.renter;
        this->cleaning = other.cleaning;
    }
    Room operator = (const Room& other){
        this->description = other.description;
        this->amount = other.amount;
        this->code = other.code;
        this->renter = other.renter;
        this->cleaning = other.cleaning;
        return *this;
    }
    Room(Room&& other){
        this->description = other.description;
        this->amount = other.amount;
        this->code = other.code;
        this->renter = other.renter;
        this->cleaning = other.cleaning;
    }
    Room operator = (Room&& other){
        this->description = other.description;
        this->amount = other.amount;
        this->code = other.code;
        this->renter = other.renter;
        this->cleaning = other.cleaning;
        return *this;
    }*/
    virtual ~Room(){}
    virtual std::string getDescription(){
        return this->description;
    }
    virtual int getAmount(){
        return QString(this->amount.c_str()).toInt();
    }
    virtual std::string getCode(){
        return this->code;
    }
    virtual std::string getRenter(){
        return this->renter;
    }
    virtual bool isCleaning(){
        return this->cleaning;
    }
    virtual Room* removeUpgrade(std::string code){
        return nullptr;
    }
    std::string getCurrentCode(){
        return this->code;
    }

    virtual void setRenter(std::string renter){
        this->renter = renter;
    }
    virtual void changeCleaningStatus(){
        this->cleaning = !this->cleaning;
    }
    virtual Room* getRoom(){
        return nullptr;
    }
    virtual void setRoom(Room *room){

    }
protected:
    std::string description;
    std::string amount;
    std::string code;
    std::string renter;
    bool cleaning;

};

class UpgradeDecorator : public Room{
protected:
    Room *room;
public :

    Room* getRoom(){
        return this->room;
    }
    void setRoom(Room *room){
        this->room = room;
    }
    std::string getDescription(){
        return this->room->getDescription() + this->description;
    }
    int getAmount(){
        return this->room->getAmount() + QString(this->amount.c_str()).toInt();
    }
    std::string getCode() = 0;
    std::string getRenter(){
        return this->room->getRenter();
    }
    void setRenter(std::string renter){
        this->room->setRenter(renter);
    }
    bool isCleaning(){
        return this->room->isCleaning();
    }
    void changeCleaningStatus(){
        this->room->changeCleaningStatus();
    }
    Room* removeUpgrade(std::string code){
        if(this->code == code) return this->getRoom();
        else{
            Room *room = this;
            while(room && room->getRoom()->getCurrentCode() != "0" && room->getRoom()->getCurrentCode() != code){
                room = room->getRoom();
            }
            if(room && room->getRoom()->getCurrentCode() == code){
                Room *del = room->getRoom();
                room->setRoom(room->getRoom()->getRoom());
                del->setRoom(nullptr);
            }
        }
        return this;
    }
};

class RoomUpgrade : public UpgradeDecorator{
public:
    RoomUpgrade(Room *room){
        this->amount = "7";
        this->description = std::string("Дополнительная комната + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "2";
    }
    RoomUpgrade(Room *room ,std::string amount){
        this->amount = amount;
        this->description = std::string("Дополнительная комната + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "2";
    }
    std::string getCode(){
        return this->code + this->room->getCode();
    }
    ~RoomUpgrade(){
        delete this->room;
    }
};

class MediaUpgrade : public UpgradeDecorator{
public:
    MediaUpgrade(Room *room){
        this->amount = "3";
        this->description = std::string("Медиацентр + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "4";
    }
    MediaUpgrade(Room *room , std::string amount){
        this->amount = amount;
        this->description = std::string("Медиацентр + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "4";
    }
    std::string getCode(){
        return this->code + this->room->getCode();
    }
    ~MediaUpgrade(){
        delete this->room;
    }
};

class FridgeUpgrade : public UpgradeDecorator{
public:
    FridgeUpgrade(Room *room){
        this->amount = "4";
        this->description = std::string("Холодильник + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "1";
    }
    FridgeUpgrade(Room *room , std::string amount){
        this->amount = amount;
        this->description = std::string("Холодильник + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "1";
    }
    std::string getCode(){
        return this->code + this->room->getCode();
    }
    ~FridgeUpgrade(){
        delete this->room;
    }
};
class BagaUpgrade : public UpgradeDecorator{
public:
    BagaUpgrade(Room *room){
        this->amount = "4000";
        this->description = std::string("Бага + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "3";
    }
    BagaUpgrade(Room *room , std::string amount){
        this->amount = amount;
        this->description = std::string("Бага + ") + this->amount + std::string("$/сутки\n");
        this->room = room;
        this->code = "3";
    }
    std::string getCode(){
        return this->code + this->room->getCode();
    }
    ~BagaUpgrade(){
        delete this->room;
    }
};


class Hotel{
public:
    Hotel(){
        lastNum = 0;
    }
    ~Hotel(){
        for(auto el : this->rooms){
            delete el.second;
        }
    }
    Hotel(const Hotel& other){
        this->rooms = other.rooms;
        this->lastNum = other.lastNum;
    }
    Hotel operator = (const Hotel& other){
        this->rooms = other.rooms;
        this->lastNum = other.lastNum;
    }
    Hotel(Hotel&& other){
        this->rooms = std::move(other.rooms);
        this->lastNum = other.lastNum;
    }
    Hotel operator = (Hotel&& other){
        this->rooms = std::move(other.rooms);
        this->lastNum = other.lastNum;
    }
    void addRoom(Room *room){
        this->rooms.insert(std::pair<int, Room*>(++lastNum , room));
    }
    void addRoom(int num , Room *room){
        std::pair<int , Room*> pair(num , room);
        this->rooms.insert(pair);
    }
    std::string getRoomDescription(int num){
        auto search = this->rooms.find(num);
        if(search != this->rooms.end()){
            return search->second->getDescription();
        }
        else return "Номер не найден";
    }
    void removeUpgrade(int num , std::string code){
        auto search = this->rooms.find(num);
        if(search != this->rooms.end() && search->second->getCurrentCode() != "0")
        search->second = search->second->removeUpgrade(code);
    }
    int getAmount(int num){
        auto search = this->rooms.find(num);
        if(search != this->rooms.end()){
            return search->second->getAmount();
        }
        else return 0;
    }
    std::string getRenter(int num){
        auto it = this->rooms.find(num);
        if(it != this->end()){
            return it->second->getRenter();
        }
        else return "";
    }
    void setRenter(int num , std::string renter){
        auto it = this->rooms.find(num);
        if(it != this->end()){
            it->second->setRenter(renter);
        }
    }
    bool roomExist(int num){
        auto it = this->rooms.find(num);
        return it != this->end();
    }
    int getLastNum(){
        return this->lastNum;
    }
    typename std::map<int , Room*>::const_iterator begin(){
        return this->rooms.begin();
    }
    typename std::map<int , Room*>::const_iterator end(){
        return this->rooms.end();
    }
    void clear(){
        this->rooms.clear();
        this->lastNum = 0;
    }
    bool isCleaning(int num){
        auto it = this->rooms.find(num);
        if(it != this->end()){
            return it->second->isCleaning();
        }
        else return false;
    }
    int size(){
        return this->rooms.size();
    }
    void changeCleaningStatus(int num){
        auto it = this->rooms.find(num);
        if(it != this->end()){
            it->second->changeCleaningStatus();
        }
    }
    typename std::map<int , Room*>::iterator find(int num){
        return this->rooms.find(num);
    }
private:
    std::map<int, Room*> rooms;
    int lastNum;
};

class RoomFactory{
public:
    RoomFactory(Hotel *hotel){
        std::ifstream fin("settings.ini");
        fin >> this->baseRoomCost;
        fin >> this->addRoomCost;
        fin >> this->bagaCost;
        fin >> this->fridgeCost;
        fin >> this->mediaCost;
        fin.close();
        this->hotel = hotel;
    }
    ~RoomFactory(){
        std::ofstream fout("settings.ini");
        fout << this->baseRoomCost << "\n";
        fout << this->addRoomCost << "\n";
        fout << this->bagaCost << "\n";
        fout << this->fridgeCost << "\n";
        fout << this->mediaCost << "\n";
        this->hotel = nullptr;
    }
    RoomFactory(const RoomFactory& other){
        if(other.hotel)
            *this->hotel = *other.hotel;
        else
            this->hotel = nullptr;
        this->baseRoomCost = other.baseRoomCost;
        this->addRoomCost = other.addRoomCost;
        this->bagaCost = other.bagaCost;
        this->fridgeCost = other.fridgeCost;
        this->mediaCost = other.mediaCost;
    }
    RoomFactory operator = (const RoomFactory& other){
        if(other.hotel)
            *this->hotel = *other.hotel;
        else
            this->hotel = nullptr;
        *this->hotel = *other.hotel;
        this->baseRoomCost = other.baseRoomCost;
        this->addRoomCost = other.addRoomCost;
        this->bagaCost = other.bagaCost;
        this->fridgeCost = other.fridgeCost;
        this->mediaCost = other.mediaCost;
    }
    RoomFactory(RoomFactory&& other){
        this->hotel = std::move(other.hotel);
        this->baseRoomCost = other.baseRoomCost;
        this->addRoomCost = other.addRoomCost;
        this->bagaCost = other.bagaCost;
        this->fridgeCost = other.fridgeCost;
        this->mediaCost = other.mediaCost;
    }
    RoomFactory operator = (RoomFactory&& other){
        this->hotel = std::move(other.hotel);
        this->baseRoomCost = other.baseRoomCost;
        this->addRoomCost = other.addRoomCost;
        this->bagaCost = other.bagaCost;
        this->fridgeCost = other.fridgeCost;
        this->mediaCost = other.mediaCost;
    }

    std::string getBaseRoomCost(){
        return this->baseRoomCost;
    }
    std::string getAddRoomCost(){
        return this->addRoomCost;
    }
    std::string getBagaCost(){
        return this->bagaCost;
    }
    std::string getMediaCost(){
        return this->mediaCost;
    }
    std::string getFridgeCost(){
        return this->fridgeCost;
    }
   void setBaseRoomCost(std::string cost){
        this->baseRoomCost = cost;
    }
    void setAddRoomCost(std::string cost){
        this->addRoomCost = cost;
    }
    void setBagaCost(std::string cost){
        this->bagaCost = cost;
    }
    void setMediaCost(std::string cost){
        this->mediaCost = cost;
    }
    void setFridgeCost(std::string cost){
        this->fridgeCost = cost;
    }


    void createRoom(std::string code){ //0 - базовая комната; 1 - холодильник; 2 - доп комната; 3 - Бага; 4 - медиа :)
        Room *room ;
        for(auto it = code.rbegin(); it != code.rend(); ++it){
                try{
                switch (*it) {
                case '0':
                    //while(true) new int[1000000];
                    room = new Room(baseRoomCost);
                    break;
                case '1':
                    room = new FridgeUpgrade(room , fridgeCost);
                    break;
                case '2':
                    room = new RoomUpgrade(room , addRoomCost);
                    break;
                case '3':
                    room = new BagaUpgrade(room, bagaCost);
                    break;
                case '4':
                    room = new MediaUpgrade(room, mediaCost);
                    break;
                default:
                    room = nullptr;
                    break;
                }
            }catch(std::bad_alloc){
                throw std::bad_alloc();
            }
        }
        this->hotel->addRoom(room);
    }
private:
    Hotel *hotel;
    std::string bagaCost;
    std::string baseRoomCost;
    std::string addRoomCost;
    std::string mediaCost;
    std::string fridgeCost;
};

#endif // HOTEL2_H
