#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>
#include <QNetworkRequest>
#include <QNetworkReply>

struct ToDoItem
{
    bool done;
    QString description;
};

class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QObject *parent = nullptr);

    QVector<ToDoItem> items() const;

    bool setItemAt(int index, const ToDoItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();
    void refreshList();

private:
    QVector<ToDoItem> mItems;
    QNetworkAccessManager m_networkAccessManager;

private slots:
    void handleTodoData(QNetworkReply *networkReply);
};

#endif // TODOLIST_H
