#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <experimental/filesystem>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QMessageBox>
namespace fs = std::experimental::filesystem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void CreateJSONFile( QString& filename,QJsonObject& json );
    void JSONDirectoryTree(const fs::path& pathToShow, QJsonObject& j_main, int level = 0);
    ~MainWindow();

private slots:

    void on_create_file_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
