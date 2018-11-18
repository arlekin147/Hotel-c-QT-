#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "hotel2.h"
#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_pushButton_5_clicked();

    void on_action_4_triggered();

    void on_getForRentButton_clicked();

    void on_cleaningCB_stateChanged(int arg1);

    void on_cleaningCB_clicked();

    void on_freeRoom_clicked();

    void on_deleteRoomButton_clicked();

    void on_deleteBagaButton_clicked();

    void on_deleteFridgeButton_clicked();

    void on_deleteMediaButton_clicked();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_9_triggered();

    void on_action_8_triggered();

private:
    Ui::MainWindow *ui;
    Hotel hotel;
    RoomFactory rf;
    std::string currentFile;
};

#endif // MAINWINDOW_H
