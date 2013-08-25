#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	graphicsScene = new QGraphicsScene(ui->graphicsView);
	ui->graphicsView->setScene(graphicsScene);

	baseDir = "/home/michael/work/zwostein-Ununoctium/data/landscape/earth/";
	config = new QSettings(baseDir+"landscape.ini", QSettings::IniFormat);

	config->beginGroup("Terrain");
		QString heightMapFile = baseDir+config->value("heightMapPath").toString();
		qDebug() << heightMapFile;
		heightMap = QImage( heightMapFile );
	config->endGroup();

	graphicsScene->addPixmap(QPixmap::fromImage(heightMap));
	graphicsScene->setSceneRect(heightMap.rect());
	ui->graphicsView->setFixedWidth(heightMap.width());

	/*
	s.beginGroup( "Terrain" );
		QString heightMapPath = s.value( "heightMapPath", "height.png" ).toString();
		mTerrainSize = QVector3D(
			s.value( "sizeX", 1000.0f ).toFloat(),
			s.value( "sizeY", 100.0f ).toFloat(),
			s.value( "sizeZ", 1000.0f ).toFloat()
		);
		mTerrainOffset = QVector3D(
			s.value( "offsetX", -500.0f ).toFloat(),
			s.value( "offsetY", -50.0f ).toFloat(),
			s.value( "offsetZ", -500.0f ).toFloat()
		);
		QString terrainMaterial = s.value( "material" ).toString();
		mTerrainMaterialScale = QVector2D(
			s.value( "materialScaleS", 1.0f ).toFloat(),
			s.value( "materialScaleT", 1.0f ).toFloat()
		);
		int smoothingPasses = s.value( "smoothingPasses", 1 ).toInt();
	s.endGroup();
	*/
}

MainWindow::~MainWindow()
{
	delete ui;
	delete graphicsScene;
	delete config;
}
