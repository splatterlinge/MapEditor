#include "BlobModel.hpp"

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QSlider>

void BlobDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (!index.isValid())
		return;

	Blob *v = index.data(Qt::EditRole).value<Blob *>();

	if(editor->objectName() == "blobMaskBox")
	{
		QComboBox * edit = static_cast<QComboBox*>(editor);
		if(edit)
		{
			edit->setCurrentIndex(edit->findText(v->mask));
		}
		return;
	}
	if(editor->objectName() == "blobMaterialBox")
	{
		QComboBox * edit = static_cast<QComboBox*>(editor);
		if(edit)
			edit->setCurrentIndex(edit->findText(v->material));
		return;
	}
	if(editor->objectName() == "blobScaleXSpin")
	{
		QDoubleSpinBox * edit = static_cast<QDoubleSpinBox*>(editor);
		if(edit)
			edit->setValue(v->scaleS);
		return;
	}
	if(editor->objectName() == "blobScaleYSpin")
	{
		QDoubleSpinBox * edit = static_cast<QDoubleSpinBox*>(editor);
		if(edit)
			edit->setValue(v->scaleT);
		return;
	}
	if(editor->objectName() == "blobPositionXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->rect.left());
		return;
	}
	if(editor->objectName() == "blobPositionYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->rect.top());
		return;
	}
	if(editor->objectName() == "blobSizeXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->rect.width());
		return;
	}
	if(editor->objectName() == "blobSizeYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			edit->setValue(v->rect.height());
		return;
	}
	if(editor->objectName() == "blobPrioritySlider")
	{
		QSlider * edit = static_cast<QSlider*>(editor);
		if(edit)
			edit->setValue(v->priority);
		return;
	}
}

void BlobDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (!index.isValid())
		return;

	Blob *v = model->data(index, Qt::EditRole).value<Blob *>();

	if(editor->objectName() == "blobMaskBox")
	{
		QComboBox * edit = static_cast<QComboBox*>(editor);
		if(edit)
			v->mask = edit->currentText();
		return;
	}
	if(editor->objectName() == "blobMaterialBox")
	{
		QComboBox * edit = static_cast<QComboBox*>(editor);
		if(edit)
			v->material = edit->currentText();
	}
	if(editor->objectName() == "blobScaleXSpin")
	{
		QDoubleSpinBox * edit = static_cast<QDoubleSpinBox*>(editor);
		if(edit)
			v->scaleS = edit->value();
		return;
	}
	if(editor->objectName() == "blobScaleYSpin")
	{
		QDoubleSpinBox * edit = static_cast<QDoubleSpinBox*>(editor);
		if(edit)
			v->scaleT = edit->value();
		return;
	}
	if(editor->objectName() == "blobPositionXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->rect.moveLeft(edit->value());
		return;
	}
	if(editor->objectName() == "blobPositionYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->rect.moveTop(edit->value());
		return;
	}
	if(editor->objectName() == "blobSizeXSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->rect.setWidth(edit->value());
		return;
	}
	if(editor->objectName() == "blobSizeYSpin")
	{
		QSpinBox * edit = static_cast<QSpinBox*>(editor);
		if(edit)
			v->rect.setHeight(edit->value());
		return;
	}
	if(editor->objectName() == "blobPrioritySlider")
	{
		QSlider * edit = static_cast<QSlider*>(editor);
		if(edit)
			v->priority = edit->value();
		return;
	}
}

int BlobModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return items.count();
}

QVariant BlobModel::data(const QModelIndex &index, int role) const
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

void BlobModel::addData(QString mask, QString material, double scaleS, double scaleT, QRect rect, int priority)
{
	Blob *b = new Blob;
	b->mask = mask;
	b->material = material;
	b->scaleS = scaleS;
	b->scaleT = scaleT;
	b->rect = rect;
	b->priority = priority;

	items.append(b);
}

bool BlobModel::removeRow(int row, const QModelIndex &parent)
{
	Q_UNUSED(parent);

	items.removeAt(row);

	return true;
}

