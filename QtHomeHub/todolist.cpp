#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    refreshList();
}

QVector<ToDoItem> ToDoList::items() const
{
    return mItems;
}

bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const ToDoItem &oldItem = mItems.at(index);
    if (item.done == oldItem.done && item.description == oldItem.description)
        return false;

    // Update the item in the database
    if (item.description != oldItem.description) {

        //Since the item name is the lookup key in the remote database, first delete the previous item
        QUrl url("http://192.168.0.13:8081/todolist_delete.php");
        QUrlQuery query;
        query.addQueryItem("whereClause", oldItem.description);
        url.setQuery(query);

        qDebug()<<"REQUEST TODO DELETE ITEM:"<<url.toString();
        m_networkAccessManager.get(QNetworkRequest(url));

        // then create a new one with the updated name
        QUrl url2("http://192.168.0.13:8081/todolist_insert.php");
        QUrlQuery query2;
        query2.addQueryItem("newitem", item.description);
        query2.addQueryItem("priority", "1");
        query2.addQueryItem("creationdate", QDateTime::currentDateTime().toString("dd MMM yyyy à HH:mm"));
        url2.setQuery(query2);

        qDebug()<<"REQUEST TODO INSERT NEW ITEM:"<<url2.toString();
        m_networkAccessManager.get(QNetworkRequest(url2));
    }
        // and update the local list
        mItems[index] = item;

    return true;
}

void ToDoList::appendItem()
{
    emit preItemAppended();

    ToDoItem item;
    item.done = false;
    mItems.append(item);

    emit postItemAppended();
}

void ToDoList::removeCompletedItems()
{
    for (int i = 0; i < mItems.size(); ) {
        if (mItems.at(i).done) {
            emit preItemRemoved(i);

            //Remote request to delete the item, by name
            QUrl url("http://192.168.0.13:8081/todolist_delete.php");
            QUrlQuery query;
            query.addQueryItem("whereClause", mItems.at(i).description !=""? mItems.at(i).description : "");
            url.setQuery(query);
            qDebug()<<"REQUEST TODO DELETE ITEM:"<<url.toString();
            m_networkAccessManager.get(QNetworkRequest(url));

            // Also remove it from the local list
            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}

void ToDoList::refreshList()
{
    qDebug()<<"REQUEST TODO REFRESH";
    QUrl url("http://192.168.0.13:8081/todolist.php");
    QUrlQuery query;
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleTodoData(rep); });
}

void ToDoList::handleTodoData(QNetworkReply *networkReply)
{
    if (!networkReply)
        return;

    qDebug()<<"RECEIVED TODO REFRESH RESPONSE";

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
                    //int priority = jobj.value(QStringLiteral("priority")).toInt();
                    //QString creationDate = jobj.value(QStringLiteral("creationDate"));

                    emit preItemAppended();
                    mItems.append({ false, item });
                    emit postItemAppended();

                }
            }
        }
    }
    networkReply->deleteLater();
}



