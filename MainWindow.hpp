#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDebug>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	QGraphicsScene *graphicsScene;

	QString baseDir;
	QImage heightMap;
	QSettings * config;
};

#endif // MAINWINDOW_HPP
