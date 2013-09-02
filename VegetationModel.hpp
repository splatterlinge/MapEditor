#ifndef LISTMODEL_HPP
#define LISTMODEL_HPP

#include <QAbstractListModel>
#include <QItemDelegate>
#include <QListView>
#include <QList>
#include <QPoint>

class Vegetation
{
public:
	const QString toString() const { return type+","+model; }

	QString type;
	QString model;
	QPoint position;
	int radius;
	int number;
	int priority;
};

Q_DECLARE_METATYPE(Vegetation*)

class VegetationDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class VegetationModel : public QAbstractListModel
{
	Q_OBJECT
public:
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	void addData(QString type, QString model, QPoint position, int radius, int number, int priority);
	bool removeRow(int row, const QModelIndex &parent);

	QList<Vegetation *> getList() { return items; }

signals:

public slots:

private:
	QList<Vegetation *> items;
};

#endif // LISTMODEL_HPP
