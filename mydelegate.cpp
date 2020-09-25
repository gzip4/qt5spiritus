#include <QDoubleValidator>
#include <QStyledItemDelegate>
#include <QLineEdit>

#include "mydelegate.h"

MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto editor = new QLineEdit(parent);
    auto v = new QDoubleValidator(0.0, 100000.0, 2);
    v->setNotation(QDoubleValidator::StandardNotation);
    editor->setValidator(v);
    return editor;
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index,Qt::EditRole).toDouble();
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    line->setText(QString().setNum(value));
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index,value);
}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
