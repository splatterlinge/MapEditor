#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	graphicsScene = new QGraphicsScene(ui->graphicsView);
	ui->graphicsView->setScene(graphicsScene);

	vegetationModel = new VegetationModel();
	vegetationDelegate = new VegetationDelegate();
	ui->vegetationBox->setItemDelegate(vegetationDelegate);
	ui->vegetationBox->setModel(vegetationModel);

	mapper = new QDataWidgetMapper();
	mapper->setModel(vegetationModel);
	mapper->setItemDelegate(vegetationDelegate);
	mapper->addMapping(ui->vegetationTypeEdit, 0);
	mapper->addMapping(ui->vegetationModelEdit, 0);
	mapper->addMapping(ui->vegetationPositionXSpin, 0);
	mapper->addMapping(ui->vegetationPositionYSpin, 0);
	mapper->addMapping(ui->vegetationRadiusSpin, 0);
	mapper->addMapping(ui->vegetationNumberSpin, 0);
	mapper->toFirst();

	baseDir = "/home/michael/work/zwostein-Ununoctium/data/landscape/earth/";
	config = new QSettings(baseDir+"landscape.ini", QSettings::IniFormat);

	config->beginGroup("Terrain");
		QString heightMapFile = baseDir+config->value("heightMapPath").toString();
		heightMap = QImage( heightMapFile );
	config->endGroup();

	int vegeNum = config->beginReadArray( "Vegetation" );
		for( int i=0; i<vegeNum; i++ )
		{
			config->setArrayIndex( i );

			vegetationModel->addData(
						config->value("type").toString(),
						config->value("model").toString(),
						config->value("position").toPoint(),
						config->value("radius").toInt(),
						config->value("number").toInt()
						);
		}
	config->endArray();
	ui->vegetationBox->setCurrentIndex(0);

	graphicsScene->setSceneRect(heightMap.rect());
	ui->graphicsView->setFixedWidth(heightMap.width());

	setGeometry(0, 0, heightMap.width()+300, heightMap.height()+75);

	update();

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

	int vegeNum = s.beginReadArray( "Vegetation" );
		for( int i=0; i<vegeNum; i++ )
		{
			s.setArrayIndex( i );
			QSharedPointer<AObject> f;
			QString type = s.value("type").toString();
			if( type == "forest" )
			{
				f = QSharedPointer<AObject>( new Forest( this,
						s.value("model").toString(), s.value("position").toPoint(),
						s.value("radius").toInt(), s.value("number").toInt() ) );
			}
			else if( type == "grass" )
			{
				f = QSharedPointer<AObject>( new Grass( this,
						s.value("model").toString(), s.value("position").toPoint(),
						s.value("radius").toInt(), s.value("number").toInt() ) );
			}

			mVegetation.append( f );
			add( f );
		}
	s.endArray();
	*/
}

MainWindow::~MainWindow()
{
	delete ui;
	delete graphicsScene;
	delete config;
}

void MainWindow::clear()
{
	graphicsScene->clear();
}

void MainWindow::update()
{
	clear();

	graphicsScene->addPixmap(QPixmap::fromImage(heightMap));

	QList<Vegetation *> list = vegetationModel->getList();

	for(int i=0; i<list.size(); i++)
	{
		Vegetation *v = list.at(i);
		int x = v->position.x() - v->radius;
		int y = v->position.y() - v->radius;
		int w = v->radius * 2;
		int h = v->radius * 2;

		QBrush color;
		if(i == ui->vegetationBox->currentIndex())
			color = QBrush(QColor(0,255,0,150));
		else
			color = QBrush(QColor(0,255,0,20));

		graphicsScene->addEllipse(x, y, w, h, QPen(Qt::white), color);
	}
}

void MainWindow::on_vegetationBox_currentIndexChanged(int index)
{
	mapper->setCurrentIndex(index);
	update();
}

void MainWindow::on_vegetationTypeEdit_textChanged(const QString &text)
{
	vegetationDelegate->commitData(ui->vegetationTypeEdit);
	update();
}

void MainWindow::on_vegetationModelEdit_textChanged(const QString &text)
{
	vegetationDelegate->commitData(ui->vegetationModelEdit);
	update();
}

void MainWindow::on_vegetationPositionXSpin_valueChanged(int value)
{
	vegetationDelegate->commitData(ui->vegetationPositionXSpin);
	update();
}

void MainWindow::on_vegetationPositionYSpin_valueChanged(int value)
{
	vegetationDelegate->commitData(ui->vegetationPositionYSpin);
	update();
}

void MainWindow::on_vegetationRadiusSpin_valueChanged(int value)
{
	vegetationDelegate->commitData(ui->vegetationRadiusSpin);
	update();
}

void MainWindow::on_vegetationNumberSpin_valueChanged(int value)
{
	vegetationDelegate->commitData(ui->vegetationNumberSpin);
	update();
}

void MainWindow::on_vegetationAdd_clicked()
{
	int size = vegetationModel->getList().size();
	vegetationModel->addData("", "", QPoint(0,0), 0, 0);
	ui->vegetationBox->setCurrentIndex(size);
}

void MainWindow::on_vegetationDelete_clicked()
{
	int index = ui->vegetationBox->currentIndex();
	vegetationModel->removeRow(index, QModelIndex());
	ui->vegetationBox->setCurrentIndex(index-1);
}

void MainWindow::on_actionSave_triggered()
{
	config->remove("Vegetation");

	int size = vegetationModel->getList().size();
	config->beginWriteArray("Vegetation", size);
	for(int i=0; i<size; i++)
	{
		Vegetation *v = vegetationModel->getList().at(i);
		config->setArrayIndex(i);
		config->setValue("type", v->type);
		config->setValue("model", v->model);
		config->setValue("position", v->position);
		config->setValue("radius", v->radius);
		config->setValue("number", v->number);
	}
	config->endArray();
}
