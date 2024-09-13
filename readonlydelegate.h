#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QStyledItemDelegate>

class ReadOnlyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ReadOnlyDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        // Не создавать редактор
        return nullptr;
    }
};

#endif // READONLYDELEGATE_H
