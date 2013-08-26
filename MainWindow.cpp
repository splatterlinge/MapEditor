#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QDoubleSpinBox>

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

	vegetationMapper = new QDataWidgetMapper();
	vegetationMapper->setModel(vegetationModel);
	vegetationMapper->setItemDelegate(vegetationDelegate);
	vegetationMapper->addMapping(ui->vegetationTypeEdit, 0);
	vegetationMapper->addMapping(ui->vegetationModelEdit, 0);
	vegetationMapper->addMapping(ui->vegetationPositionXSpin, 0);
	vegetationMapper->addMapping(ui->vegetationPositionYSpin, 0);
	vegetationMapper->addMapping(ui->vegetationRadiusSpin, 0);
	vegetationMapper->addMapping(ui->vegetationNumberSpin, 0);
	vegetationMapper->toFirst();

	blobModel = new BlobModel(this);
	blobDelegate = new BlobDelegate(this);
	ui->blobBox->setItemDelegate(blobDelegate);
	ui->blobBox->setModel(blobModel);

	blobMapper = new QDataWidgetMapper(this);
	blobMapper->setModel(blobModel);
	blobMapper->setItemDelegate(blobDelegate);
	blobMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
	blobMapper->addMapping(ui->blobMaskEdit, 0);
	blobMapper->addMapping(ui->blobMaterialEdit, 0);
	blobMapper->addMapping(ui->blobScaleXSpin, 0);
	blobMapper->addMapping(ui->blobScaleYSpin, 0);
	blobMapper->addMapping(ui->blobPositionXSpin, 0);
	blobMapper->addMapping(ui->blobPositionYSpin, 0);
	blobMapper->addMapping(ui->blobSizeXSpin, 0);
	blobMapper->addMapping(ui->blobSizeYSpin, 0);
	blobMapper->toFirst();

	connect(ui->toolBox, SIGNAL(currentChanged(int)), this, SLOT(update()));

	connect(ui->vegetationBox, SIGNAL(currentIndexChanged(int)), vegetationMapper, SLOT(setCurrentIndex(int)));
	connect(ui->vegetationPositionXSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));
	connect(ui->vegetationPositionYSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));
	connect(ui->vegetationRadiusSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));
	connect(ui->vegetationNumberSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));

	connect(ui->blobBox, SIGNAL(currentIndexChanged(int)), blobMapper, SLOT(setCurrentIndex(int)));
	connect(ui->blobMaskEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
	connect(ui->blobPositionXSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));
	connect(ui->blobPositionYSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));
	connect(ui->blobSizeXSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));
	connect(ui->blobSizeYSpin, SIGNAL(valueChanged(int)), this, SLOT(update()));

	baseDir = "/home/michael/work/zwostein-Ununoctium/data/landscape/earth/";
	config = new QSettings(baseDir+"landscape.ini", QSettings::IniFormat);

	config->beginGroup("Terrain");
		heightMapPath = config->value("heightMapPath").toString();
		ui->terrainHeightMapEdit->setText(heightMapPath);
		heightMap = QImage( baseDir+heightMapPath );

		material = config->value("material").toString();
		ui->terrainMaterialEdit->setText(material);
		materialScale = QVector2D(
							config->value("materialScaleS").toFloat(),
							config->value("materialScaleT").toFloat()
							);
		ui->terrainScaleSSpin->setValue(materialScale.x());
		ui->terrainScaleTSpin->setValue(materialScale.y());

		offset = QVector3D(
					 config->value("offsetX").toFloat(),
					 config->value("offsetY").toFloat(),
					 config->value("offsetZ").toFloat()
					 );
		ui->terrainOffsetXSpin->setValue(offset.x());
		ui->terrainOffsetYSpin->setValue(offset.y());
		ui->terrainOffsetZSpin->setValue(offset.z());

		size = QVector3D(
				   config->value("sizeX").toFloat(),
				   config->value("sizeY").toFloat(),
				   config->value("sizeZ").toFloat()
				   );
		ui->terrainSizeXSpin->setValue(size.x());
		ui->terrainSizeYSpin->setValue(size.y());
		ui->terrainSizeZSpin->setValue(size.z());
	config->endGroup();

	config->beginGroup("Water");
		waterHeight = config->value("height").toDouble();
		ui->waterHeightSpin->setValue(waterHeight);
	config->endGroup();

	int vegeNum = config->beginReadArray("Vegetation");
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

	int blobNum = config->beginReadArray("Blob");
		for( int i=0; i<blobNum; i++ )
		{
			config->setArrayIndex( i );

			blobModel->addData(
						config->value("maskPath").toString(),
						config->value("material").toString(),
						config->value("materialScaleS").toDouble(),
						config->value("materialScaleT").toDouble(),
						config->value("rect").toRect()
						);
		}
	config->endArray();
	ui->blobBox->setCurrentIndex(0);

	graphicsScene->setSceneRect(heightMap.rect());
	ui->graphicsView->setFixedWidth(heightMap.width());

	setGeometry(0, 0, heightMap.width()+400, heightMap.height()+75);

	ui->toolBox->setCurrentIndex(0);

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

	QImage img = heightMap;
	if(size.y() != 0)
	{
		int limit = qMax((double)256 / size.y() * -offset.y(), (double)0.0);
		{
			for(int i=0; i<img.width(); i++)
			{
				for(int j=0; j<img.height(); j++)
				{
					int g = qGray(img.pixel(i, j));
					if(g < limit+waterHeight)
					{
						img.setPixel(i, j, qRgb(0,111,255));
					}
				}
			}
		}
	}

	graphicsScene->addPixmap(QPixmap::fromImage(img));

	int px = -offset.x() * heightMap.width() / size.x();
	int py = -offset.z() * heightMap.height() / size.z();
	graphicsScene->addLine(px, 0, px, heightMap.height(), QPen(Qt::red, 1, Qt::DotLine));
	graphicsScene->addLine(0, py, heightMap.width(), py, QPen(Qt::red, 1, Qt::DotLine));

	if(ui->toolBox->currentWidget()->objectName() == "blobPage")
	{
		QList<Blob *> blobList = blobModel->getList();
		for(int i=0; i<blobList.size(); i++)
		{
			if(i == ui->blobBox->currentIndex())
			{
				Blob *v = blobList.at(i);

				QImage alpha(baseDir+ui->blobMaskEdit->text());
				if(!alpha.isNull())
				{
					alpha = alpha.scaled(ui->blobSizeXSpin->value(), ui->blobSizeYSpin->value());
					QImage img(alpha.width(), alpha.height(), QImage::Format_ARGB32);
					img = img.scaled(alpha.width(), alpha.height());
					img.fill(QColor(255,0,255));
					img.setAlphaChannel(alpha);

					QGraphicsPixmapItem *item = graphicsScene->addPixmap(QPixmap::fromImage(img));
					item->setPos(ui->blobPositionXSpin->value(), ui->blobPositionYSpin->value());
					graphicsScene->addRect(
								ui->blobPositionXSpin->value(),
								ui->blobPositionYSpin->value(),
								ui->blobSizeXSpin->value(),
								ui->blobSizeYSpin->value(),
								QPen(QColor(255,0,255), 2, Qt::DotLine));
				}
			}
		}
	}

	QList<Vegetation *> vegeList = vegetationModel->getList();
	for(int i=0; i<vegeList.size(); i++)
	{
		Vegetation *v = vegeList.at(i);
		int x = v->position.x() - v->radius;
		int y = v->position.y() - v->radius;
		int w = v->radius * 2;
		int h = v->radius * 2;

		QBrush color;
		if(ui->toolBox->currentWidget()->objectName() == "vegetationPage")
		{
			if(i == ui->vegetationBox->currentIndex())
			{
				x = ui->vegetationPositionXSpin->value() - ui->vegetationRadiusSpin->value();
				y = ui->vegetationPositionYSpin->value() - ui->vegetationRadiusSpin->value();
				w = ui->vegetationRadiusSpin->value() * 2;
				h = ui->vegetationRadiusSpin->value() * 2;
				color = QBrush(QColor(0,255,0,150));
			}
			else
			{
				color = QBrush(QColor(0,255,0,30));
			}
		}
		else
		{
			color = QBrush(QColor(0,255,0,30));
		}

		graphicsScene->addEllipse(x, y, w, h, QPen(Qt::transparent), color);
	}
}

void MainWindow::on_actionSave_triggered()
{
	config->beginGroup("Terrain");
		config->setValue("heightMapPath", heightMapPath);
		config->setValue("material", material);
		config->setValue("materialScaleS", (double)materialScale.x());
		config->setValue("materialScaleT", (double)materialScale.y());
		config->setValue("offsetX", (double)offset.x());
		config->setValue("offsetY", (double)offset.y());
		config->setValue("offsetZ", (double)offset.z());
		config->setValue("sizeX", (double)size.x());
		config->setValue("sizeY", (double)size.y());
		config->setValue("sizeZ", (double)size.z());
	config->endGroup();

	config->beginGroup("Water");
		config->setValue("height", waterHeight);
	config->endGroup();

	config->remove("Vegetation");
	int vegeSize = vegetationModel->getList().size();
	config->beginWriteArray("Vegetation", vegeSize);
	for(int i=0; i<vegeSize; i++)
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

	config->remove("Blob");
	int blobSize = blobModel->getList().size();
	config->beginWriteArray("Blob", blobSize);
	for(int i=0; i<blobSize; i++)
	{
		Blob *v = blobModel->getList().at(i);
		config->setArrayIndex(i);
		config->setValue("maskPath", v->mask);
		config->setValue("material", v->material);
		config->setValue("materialScaleS", v->scaleS);
		config->setValue("materialScaleT", v->scaleT);
		config->setValue("rect", v->rect);
	}
	config->endArray();
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

void MainWindow::on_waterHeightSpin_valueChanged(double value)
{
	waterHeight = value;
	update();
}

void MainWindow::on_terrainHeightMapEdit_textChanged(const QString &text)
{
	heightMapPath = text;
	update();
}

void MainWindow::on_terrainMaterialEdit_textChanged(const QString &text)
{
	material = text;
	update();
}

void MainWindow::on_terrainScaleSSpin_valueChanged(double value)
{
	materialScale.setX(value);
	update();
}

void MainWindow::on_terrainScaleTSpin_valueChanged(double value)
{
	materialScale.setY(value);
	update();
}

void MainWindow::on_terrainOffsetXSpin_valueChanged(double value)
{
	offset.setX(value);
	update();
}

void MainWindow::on_terrainOffsetYSpin_valueChanged(double value)
{
	offset.setY(value);
	update();
}

void MainWindow::on_terrainOffsetZSpin_valueChanged(double value)
{
	offset.setZ(value);
	update();
}

void MainWindow::on_terrainSizeXSpin_valueChanged(double value)
{
	size.setX(value);
	update();
}

void MainWindow::on_terrainSizeYSpin_valueChanged(double value)
{
	size.setY(value);
	update();
}

void MainWindow::on_terrainSizeZSpin_valueChanged(double value)
{
	size.setZ(value);
	update();
}

void MainWindow::on_blobAdd_clicked()
{
	int size = blobModel->getList().size();
	blobModel->addData("", "", 0, 0, QRect());
	ui->blobBox->setCurrentIndex(size);
}

void MainWindow::on_blobDelete_clicked()
{
	int index = ui->blobBox->currentIndex();
	blobModel->removeRow(index, QModelIndex());
	ui->blobBox->setCurrentIndex(index-1);
}
