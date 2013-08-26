#include "VegetationModel.hpp"

#include <QLineEdit>
#include <QSpinBox>

void VegetationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (!index.isValid())
		return;

	Vegetation *v = index.data(Qt::EditRole).value<Vegetation *>();

	if(editor->objectName() == "vegetationTypeEdit")
	{
		QLineEdit * edit = static_cast<QLineEdit*>(editor);
		if(edit)
			edit->setText(v->type);
		return;
	}
	if(editor->objectName() == "vegetationModelEdit")
	{
		QLineEdit * edit = static_cast<QLineEdit*>(editor);
		if(edit)
			edit->setText(v->model);
		return;
	}
	if(editor->objectName() == "vegetationPositionXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->position.x());
		return;
	}
	if(editor->objectName() == "vegetationPositionYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->position.y());
		return;
	}
	if(editor->objectName() == "vegetationRadiusSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->radius);
		return;
	}
	if(editor->objectName() == "vegetationNumberSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->number);
		return;
	}
}

void VegetationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (!index.isValid())
		return;

	Vegetation *v = model->data(index, Qt::EditRole).value<Vegetation *>();
	//Vegetation *v = index.data(Qt::EditRole).value<Vegetation *>();

	if(editor->objectName() == "vegetationTypeEdit")
	{
		QLineEdit * edit = static_cast<QLineEdit*>(editor);
		if(edit)
			v->type = edit->text();
		return;
	}
	if(editor->objectName() == "vegetationModelEdit")
	{
		QLineEdit * edit = static_cast<QLineEdit*>(editor);
		if(edit)
			v->model = edit->text();
		return;
	}
	if(editor->objectName() == "vegetationPositionXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->position.setX(edit->value());
		return;
	}
	if(editor->objectName() == "vegetationPositionYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->position.setY(edit->value());
		return;
	}
	if(editor->objectName() == "vegetationRadiusSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->radius = edit->value();
		return;
	}
	if(editor->objectName() == "vegetationNumberSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->number = edit->value();
		return;
	}
}

int VegetationModel::rowCount(const QModelIndex &parent) const
{
	return items.count();
}

QVariant VegetationModel::data(const QModelIndex &index, int role) const
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

void VegetationModel::addData(QString type, QString model, QPoint position, int radius, int number)
{
	Vegetation * v = new Vegetation;
	v->type = type;
	v->model = model;
	v->position = position;
	v->radius = radius;
	v->number = number;

	items.append(v);
}

bool VegetationModel::removeRow(int row, const QModelIndex &parent)
{
	items.removeAt(row);
}