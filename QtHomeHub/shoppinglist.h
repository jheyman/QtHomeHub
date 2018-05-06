#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include <QObject>
#include <QVector>
#include <QNetworkRequest>
#include <QNetworkReply>

struct ShoppingItem
{
    QString description;
};

class ShoppingList : public QObject
{
    Q_OBJECT
public:
    explicit ShoppingList(QObject *parent = nullptr);

    QVector<ShoppingItem> items() const;

    bool setItemAt(int index, const ShoppingItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void clearItems();
    void refreshList();

private:
    QVector<ShoppingItem> mItems;
    QNetworkAccessManager m_networkAccessManager;

private slots:
    void handleShoppingData(QNetworkReply *networkReply);
};

#endif // SHOPPINGLIST_H
