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
#include <QVector2D>
#include <QVector3D>
#include <QRgb>

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

	void on_waterHeightSpin_valueChanged(double arg1);

	void on_terrainHeightMapEdit_textChanged(const QString &arg1);

	void on_terrainMaterialEdit_textChanged(const QString &arg1);

	void on_terrainScaleSSpin_valueChanged(double arg1);

	void on_terrainScaleTSpin_valueChanged(double arg1);

	void on_terrainOffsetXSpin_valueChanged(double arg1);

	void on_terrainOffsetYSpin_valueChanged(double arg1);

	void on_terrainOffsetZSpin_valueChanged(double arg1);

	void on_terrainSizeXSpin_valueChanged(double arg1);

	void on_terrainSizeYSpin_valueChanged(double arg1);

	void on_terrainSizeZSpin_valueChanged(double arg1);

private:
	Ui::MainWindow *ui;

	QGraphicsScene *graphicsScene;

	QSettings *config;

	QString baseDir;

	QString heightMapPath;
	QImage heightMap;
	QString material;
	QVector2D materialScale;
	QVector3D offset;
	QVector3D size;

	double waterHeight;

	QDataWidgetMapper *vegetationMapper;
	VegetationDelegate *vegetationDelegate;
	VegetationModel *vegetationModel;
};

#endif // MAINWINDOW_HPP
