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
#include <QImage>
#include <QRgb>
#include <QFileDialog>
#include <QFileInfo>
#include <QStringList>
#include <QDir>
#include <QLabel>
#include <qmath.h>

#include "VegetationModel.hpp"
#include "BlobModel.hpp"

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
	void load();

public slots:
	void update();

private slots:
	void on_vegetationAdd_clicked();

	void on_vegetationDelete_clicked();

	void on_actionSave_triggered();

	void on_waterHeightSpin_valueChanged(double arg1);

	void on_terrainHeightMapEdit_textChanged(const QString &arg1);

	void on_terrainMaterialBox_currentIndexChanged(const QString &arg1);

	void on_terrainScaleSSpin_valueChanged(double arg1);

	void on_terrainScaleTSpin_valueChanged(double arg1);

	void on_terrainOffsetXSpin_valueChanged(double arg1);

	void on_terrainOffsetYSpin_valueChanged(double arg1);

	void on_terrainOffsetZSpin_valueChanged(double arg1);

	void on_terrainSizeXSpin_valueChanged(double arg1);

	void on_terrainSizeYSpin_valueChanged(double arg1);

	void on_terrainSizeZSpin_valueChanged(double arg1);

	void on_blobAdd_clicked();

	void on_blobDelete_clicked();

	void on_actionLoad_triggered();

private:
	Ui::MainWindow *ui;

	QLabel *statusLabel;
	QGraphicsScene *graphicsScene;

	QSettings *config;

	QString baseDir;

	QStringList masks;
	QStringList models;
	QStringList materials;

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

	QDataWidgetMapper *blobMapper;
	BlobDelegate *blobDelegate;
	BlobModel *blobModel;
};

#endif // MAINWINDOW_HPP
