#include "PowerupModel.hpp"

#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

void PowerupDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (!index.isValid())
		return;

	Powerup *v = index.data(Qt::EditRole).value<Powerup *>();

	if(editor->objectName() == "powerupTypeBox")
	{
		QComboBox * edit = static_cast<QComboBox*>(editor);
		if(edit)
		{
			edit->setCurrentText(v->type);
		}
		return;
	}
	if(editor->objectName() == "powerupPosXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->pos.x());
		return;
	}
	if(editor->objectName() == "powerupPosYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->pos.y());
		return;
	}
	if(editor->objectName() == "powerupRadiusSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->radius);
		return;
	}
}

void PowerupDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (!index.isValid())
		return;

	Powerup *v = model->data(index, Qt::EditRole).value<Powerup *>();

	if(editor->objectName() == "powerupTypeBox")
	{
		QComboBox * edit = static_cast<QComboBox*>(editor);
		if(edit)
		{
			v->type = edit->currentText();
		}
		return;
	}
	if(editor->objectName() == "powerupPosXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->pos.setX(edit->value());
		return;
	}
	if(editor->objectName() == "powerupPosYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->pos.setY(edit->value());
		return;
	}
	if(editor->objectName() == "powerupRadiusSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->radius = edit->value();
		return;
	}
}

int PowerupModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return items.count();
}

QVariant PowerupModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
		return QVariant();

	if(index.row() >= items.size() || index.row() < 0)
		return QVariant();

	if(role == Qt::DisplayRole)
		return items.at(index.row())->toString();

	if(role == Qt::EditRole)
		return QVariant::fromValue(items.at(index.row()));

	return QVariant();
}

void PowerupModel::addData(QString type, QPoint pos, int radius)
{
	Powerup *p = new Powerup;
	p->type = type;
	p->pos = pos;
	p->radius = radius;

	items.append(p);
}

bool PowerupModel::removeRow(int row, const QModelIndex &parent)
{
	Q_UNUSED(parent);

	items.removeAt(row);

	return true;
}
