#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "shoppinglist.h"

ShoppingList::ShoppingList(QObject *parent) : QObject(parent)
{
    refreshList();
}

QVector<ShoppingItem> ShoppingList::items() const
{
    return mItems;
}

bool ShoppingList::setItemAt(int index, const ShoppingItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const ShoppingItem &oldItem = mItems.at(index);
    if (item.description == oldItem.description)
        return false;

    // Update the item in the database
    //Since the item name is the lookup key in the remote database, first delete the previous item
    QUrl url("http://192.168.0.13:8081/shoppinglist_delete.php");
    QUrlQuery query;
    query.addQueryItem("whereClause", oldItem.description);
    url.setQuery(query);

    qDebug()<<"REQUEST SHOPPING DELETE ITEM:"<<url.toString();
    m_networkAccessManager.get(QNetworkRequest(url));

    // then create a new one with the updated name
    QUrl url2("http://192.168.0.13:8081/shoppinglist_insert.php");
    QUrlQuery query2;
    query2.addQueryItem("newitem", item.description);
    url2.setQuery(query2);

    qDebug()<<"REQUEST SHOPPING INSERT NEW ITEM:"<<url2.toString();
    m_networkAccessManager.get(QNetworkRequest(url2));

    // and update the local list
    mItems[index] = item;

    return true;
}

void ShoppingList::appendItem()
{
    emit preItemAppended();

    ShoppingItem item;
    mItems.append(item);

    emit postItemAppended();
}

void ShoppingList::clearItems()
{
    for (int i = 0; i < mItems.size(); i++) {

            emit preItemRemoved(i);

            //Remote request to delete the item, by name
            QUrl url("http://192.168.0.13:8081/shoppinglist_delete.php");
            QUrlQuery query;
            query.addQueryItem("whereClause", mItems.at(i).description !=""? mItems.at(i).description : "");
            url.setQuery(query);
            qDebug()<<"REQUEST SHOPPING DELETE ITEM:"<<url.toString();
            m_networkAccessManager.get(QNetworkRequest(url));

            // Also remove it from the local list
            mItems.removeAt(i);

            emit postItemRemoved();
    }
}

void ShoppingList::refreshList()
{
    qDebug()<<"REQUEST SHOPPING REFRESH";
    QUrl url("http://192.168.0.13:8081/shoppinglist.php");
    QUrlQuery query;
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleShoppingData(rep); });
}

void ShoppingList::handleShoppingData(QNetworkReply *networkReply)
{
    if (!networkReply)
        return;

    qDebug()<<"RECEIVED SHOPPING REFRESH RESPONSE";

    if (!networkReply->error()) {

        QJsonDocument document = QJsonDocument::fromJson(networkReply->readAll());

        if (document.isObject()) {
            QJsonObject jdata = document.object();
            QJsonObject tempObject;
            QJsonValue val;

            if (jdata.contains(QStringLiteral("items"))) {

                val = jdata.value(QStringLiteral("items"));
                QJsonArray jArray = val.toArray();

                for(int i=0;i<jArray.size();i++){
                    val = jArray.at(i);
                    tempObject = val.toObject();

                    QString item = tempObject.value(QStringLiteral("item")).toString();

                    emit preItemAppended();
                    mItems.append({ item });
                    emit postItemAppended();
                }
            }
        }
    }
    networkReply->deleteLater();
}
