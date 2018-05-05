#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "todolist.h"
#include "todomodel.h"
#include <homehubmodel.h>
#include <imageprovider.h>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug:\t%s (%s:%u)\n", localMsg.constData(), context.file, context.line);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info:\t%s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning:\t%s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical:\t%s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal:\t%s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qInstallMessageHandler(myMessageOutput);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<WeatherData>("WeatherInfo", 1, 0, "WeatherData");
    qmlRegisterType<HomeHubModel>("HomeHub", 1, 0, "HomeHubModel");

    qmlRegisterType<ToDoModel>("ToDo", 1, 0, "ToDoModel");
    qmlRegisterUncreatableType<ToDoList>("ToDo", 1, 0, "ToDoList",
           QStringLiteral("ToDoList should not be created in QML"));

    ToDoList toDoList;

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("imageProvider"), new ImageProvider);
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"), &toDoList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
