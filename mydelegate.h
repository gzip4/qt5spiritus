#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QStyledItemDelegate>

class MyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MyDelegate(QObject *parent);
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MYDELEGATE_H
