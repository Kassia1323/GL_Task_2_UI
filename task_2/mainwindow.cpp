#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_create_file_button_clicked()
{
    QString folder_path = ui->path_line->text();
    QString filename = ui->filename_line->text();
    QJsonObject j_main;
    JSONDirectoryTree(fs::path(folder_path.toStdWString()), j_main);
    CreateJSONFile(filename,j_main);

}

void MainWindow::on_exit_button_clicked()
{
    QApplication::quit();
}
void MainWindow::CreateJSONFile( QString& filename,QJsonObject& json ){
    QFile saveFile(filename);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
       QMessageBox::critical(this,"Error","File wasn't created.");
       return;
    }
    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());
    QMessageBox::information(this,"","File was created.");
}
void MainWindow::JSONDirectoryTree(const fs::path& pathToShow, QJsonObject& j_main, int level)
{
    QJsonArray files, children;
    for (const auto& entry : fs::directory_iterator(pathToShow))
    {
        QJsonObject j_entry;
        j_entry.insert("Name",QString::fromStdString(entry.path().filename().u8string()));
      //  j_entry["Name"] = entry.path().filename().u8string();
        time_t cftime = std::chrono::system_clock::to_time_t(fs::last_write_time(entry));
        j_entry.insert("Date Created",asctime(localtime(&cftime)));
        if (fs::is_directory(entry.status()))
        {
            JSONDirectoryTree(entry.path(), j_entry, level + 1);
            children.push_back(std::move(j_entry));
        }
        else
        {
           j_entry.insert("Size",QString::number(fs::file_size(entry)));
           j_entry.insert("Path",QString::fromStdString(fs::absolute(entry.path()).u8string()));
           files.push_back(std::move(j_entry));
        }
    }
    j_main.insert("Files",files);
    j_main.insert("Children",children);

}
