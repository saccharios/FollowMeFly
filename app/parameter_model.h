#pragma once

#include "table_model_base.h"
#include <QObject>

class ParameterModel : public TableModelBase
{
    Q_OBJECT
    using Base = TableModelBase;

    static constexpr int rows = 2;
    static constexpr int cols = 5;
public:
    explicit ParameterModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

signals:
    void editCompleted(const QString &);
};
