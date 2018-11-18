#ifndef HOTEL_H
#define HOTEL_H
#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <utility>



class Room{
public:

    Room(){
        this->description = "Одна комната + 10$/сутки\n";
        this->amount = 10;
        this->roomForRent = false;
    }
    virtual std::string getDescription(){
        return this->description;
    }
    virtual int getAmount(){
        return this->amount;
    }
    bool isRent(){
        return this->roomForRent;
    }
    void changeStatus(){
        this->roomForRent = !this->roomForRent;
    }
private:
    bool roomForRent; //false - свободна
    std::string description;
    int amount;

};

class UpgradeDecorator : public Room{
    virtual std::string getDescription() = 0;
};

class RoomUpgrade : public UpgradeDecorator{
    Room *room;
public:
    RoomUpgrade(Room *room){
        this->room = room;
    }
    std::string getDescription(){
        return this->room->getDescription() + "Дополнительная комната + 7$/сутки\n";
    }
    int getAmount(){
        return this->room->getAmount() + 7;
    }
};

class FridgeUpgrade : public UpgradeDecorator{
    Room *room;
public:
    FridgeUpgrade(Room *room){
        this->room = room;
    }
    std::string getDescription(){
        return this->room->getDescription() + "Холодильник + 4$/сутки\n";
    }
    int getAmount(){
        return this->room->getAmount() + 4;
    }
};
class BagaUpgrade : public UpgradeDecorator{
    Room *room;
public:
    BagaUpgrade(Room *room){
        this->room = room;
    }
    std::string getDescription(){
        return this->room->getDescription() + "Бага + 4000$/сутки\n";
    }
    int getAmount(){
        return this->room->getAmount() + 4000;
    }
};


class Hotel{
public:
    Hotel(){
        lastNum = 0;
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
        else return "Комната не найдена";
    }
    int getAmount(int num){
        auto search = this->rooms.find(num);
        if(search != this->rooms.end()){
            return search->second->getAmount();
        }
        else return 0;
    }
    Room* getRoom(int num){
        return this->rooms.find(num)->second;
    }
    bool roomExist(int num){
        return this->rooms.find(num)->first;
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
    std::map<int, Room*> rooms;
private:
    //std::map<int, Room*> rooms;
    int lastNum;
};

class RoomFactory{
public:
    RoomFactory(Hotel &hotel){ // база хол бага = 320
        this->hotel = hotel;
    }
    void createRoom(std::string code){ //0 - базовая комната; 1 - холодильник; 2 - доп комната; 3 - Бага :)
        Room *room;
        for(auto it = code.rbegin(); it != code.rend(); ++it){
            switch (*it) {
            case '0':
                room = new Room();
                break;
            case '1':
                room = new FridgeUpgrade(room);
                break;
            case '2':
                room = new RoomUpgrade(room);
                break;
            case '3':
                room = new BagaUpgrade(room);
                break;
            default:
                room = nullptr;
                break;
            }
        }
        this->hotel.addRoom(room);
    }
private:
    Hotel hotel;
};

#endif // HOTEL_H
