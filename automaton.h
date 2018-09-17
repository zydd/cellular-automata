#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QAbstractListModel>

class Automaton : public QAbstractListModel
{
    Q_OBJECT
public:
    Automaton(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    QVariant data(const QModelIndex &, int) const override;

private:
    int m_count;
};

#endif // AUTOMATON_H
