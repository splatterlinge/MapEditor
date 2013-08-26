#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDebug>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSettings>
#include <QList>
#include <QDataWidgetMapper>
#include <QAbstractListModel>
#include <QStandardItemModel>
#include <QItemDelegate>

#include "VegetationModel.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void clear();
	void update();

private slots:
	void on_vegetationBox_currentIndexChanged(int index);

	void on_vegetationPositionXSpin_valueChanged(int arg1);

	void on_vegetationPositionYSpin_valueChanged(int arg1);

	void on_vegetationRadiusSpin_valueChanged(int arg1);

	void on_vegetationNumberSpin_valueChanged(int arg1);

	void on_vegetationModelEdit_textChanged(const QString &arg1);

	void on_vegetationTypeEdit_textChanged(const QString &arg1);

	void on_vegetationAdd_clicked();

	void on_vegetationDelete_clicked();

	void on_actionSave_triggered();

private:
	Ui::MainWindow *ui;

	QGraphicsScene *graphicsScene;

	QString baseDir;
	QImage heightMap;
	QSettings *config;

	QDataWidgetMapper *mapper;
	VegetationDelegate *vegetationDelegate;
	VegetationModel *vegetationModel;
};

#endif // MAINWINDOW_HPP
