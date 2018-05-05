#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    mItems.append({ true, QStringLiteral("Wash the car") });
    mItems.append({ false, QStringLiteral("Fix the sink") });
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

            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}

void ToDoList::refreshList()
{
    /*
    QUrl url("http://192.168.0.13:8081/getRandomImagePath.php");
    QUrlQuery query;
    query.addQueryItem("basepath", "/mnt/photo");
    url.setQuery(query);

    QNetworkReply *rep = m_networkAccessManager.get(QNetworkRequest(url));
    connect(rep, &QNetworkReply::finished, this, [this, rep]() { handleRandomImagePathReception(rep); });
    */
}

void ToDoList::handleTodoData(QNetworkReply *networkReply)
{

}
