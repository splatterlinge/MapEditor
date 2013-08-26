#ifndef BLOBMODEL_HPP
#define BLOBMODEL_HPP

#include <QDebug>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemDelegate>
#include <QList>
#include <QRect>

class Blob
{
public:
	const QString toString() const { return mask+","+material; }

	QString mask;
	QString material;
	double scaleS;
	double scaleT;
	QRect rect;
};

Q_DECLARE_METATYPE(Blob*)

class BlobDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class BlobModel : public QAbstractListModel
{
	Q_OBJECT
public:
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	void addData(QString mask, QString material, double scaleS, double scaleT, QRect rect);
	bool removeRow(int row, const QModelIndex &parent);

	QList<Blob *> getList() { return items; }
signals:

public slots:

private:
	QList<Blob *> items;
};

#endif // BLOBMODEL_HPP
