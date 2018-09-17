#include "automaton.h"

#include <QtDebug>

Automaton::Automaton(QObject *parent) : QAbstractListModel(parent),
    m_count(20)
{
}

int Automaton::rowCount(const QModelIndex &) const
{
    return m_count;
}

bool Automaton::canFetchMore(const QModelIndex &/*parent*/) const
{
    return true;
}

void Automaton::fetchMore(const QModelIndex &/*parent*/)
{
    beginInsertRows(QModelIndex(), m_count, m_count+100-1);

    m_count += 100;

    endInsertRows();
}

QVariant Automaton::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    int row = index.row();

    return QString("image://a/%1").arg(row);
}

