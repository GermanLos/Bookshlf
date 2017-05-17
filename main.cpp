#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QDebug>

#include "bookshelf.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView* view = new QQuickView();
    Bookshelf* bookshelf = new Bookshelf(view);

    view->engine()->rootContext()->setContextProperty("bookshelf", bookshelf);
    view->engine()->rootContext()->setContextProperty("mBooks", bookshelf->model);

    view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
