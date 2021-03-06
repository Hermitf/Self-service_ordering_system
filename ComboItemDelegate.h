#pragma once

#include <QItemDelegate>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QValidator>
#include <QWidget>

class ComboItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
        QStringList items;

public:
    ComboItemDelegate(QStringList items, QObject* parent = 0);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
        const QModelIndex& index) const;

    void updateEditorGeometry(QWidget* editor,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const;
};