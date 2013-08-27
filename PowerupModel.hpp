#ifndef POWERUPMODEL_HPP
#define POWERUPMODEL_HPP

#include <QDebug>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemDelegate>
#include <QList>
#include <QString>
#include <QPoint>

class Powerup
{
public:
	const QString toString() const { return type; }

	QString type;
	QPoint pos;
	int radius;
};

Q_DECLARE_METATYPE(Powerup*)

class PowerupDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	explicit PowerupDelegate(QObject * parent = 0) : QItemDelegate(parent) {}

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class PowerupModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit PowerupModel(QObject * parent = 0) : QAbstractListModel(parent) {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	void addData(QString type, QPoint pos, int radius);
	bool removeRow(int row, const QModelIndex &parent);

	QList<Powerup *> getList() { return items; }

signals:

public slots:

private:
	QList<Powerup *> items;
};

#endif // POWERUPMODEL_HPP
