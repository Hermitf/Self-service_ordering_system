#include "ComboItemDelegate.h"
#include <QComboBox>


ComboItemDelegate::ComboItemDelegate(QStringList items, QObject* parent)
    : QStyledItemDelegate(parent)
{
    this->items.append(items);
}

QWidget* ComboItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    auto* editor = new QComboBox(parent);
    editor->addItems(items);
    return editor;
}

void ComboItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    dynamic_cast<QComboBox*>(editor)->setCurrentText(index.data(Qt::EditRole).toString());
}

void ComboItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
    const QModelIndex& index) const
{
    model->setData(index, dynamic_cast<QComboBox*>(editor)->currentText(), Qt::EditRole);
}

void ComboItemDelegate::updateEditorGeometry(QWidget* editor,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}