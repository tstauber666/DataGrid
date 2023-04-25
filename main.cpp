// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "database.h"
#include "mainwindow.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QTableView>
#include <QQmlContext>
#include <QApplication>
#include <QFile>
#include "helper.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>


#include "meinmodel.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
     Q_INIT_RESOURCE(masterdetail);

     QApplication app(argc, argv);

     QQmlApplicationEngine engine;





    // Bereite qml vor, um die Abhängigkeiten zu setzen
    QQmlContext *context = engine.rootContext();


    if (!createConnection())
        return EXIT_FAILURE;

    // Datenbankkontext herstellen
    QFile albumDetails("albumdetails.xml");

    Helper helper;
    helper.file = &albumDetails;
    helper.readAlbumData();


   MeinModel *modelLista = new MeinModel;
   MeinModel *model = new MeinModel;


   model->setTable("artists"); model->generateRoleNames(); model->select();

    modelLista->setTable("albums");
    modelLista->generateRoleNames();
    modelLista->setRelation(2, QSqlRelation("artists", "id" ,"artist"));
    modelLista->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelLista->select();

//    modelLista->setHeaderData(0,Qt::Horizontal,"Artristid");
//     modelLista->setHeaderData(1,Qt::Horizontal,"Album");
//      modelLista->setHeaderData(2,Qt::Horizontal,"Autor");
//       modelLista->setHeaderData(3,Qt::Horizontal,"Jahr");

   // QQmlContext *ctxt = engine.rootContext(); ctxt->setContextProperty("modelListItems", model); ctxt->setContextProperty("modelList", modelLista);
  // siehe https://wiki.qt.io/QML_and_QSqlTableModel



    context->setContextProperty("sqlModel",modelLista);
    context->setContextProperty("sqlRelation",model);


    //qml-Kram
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    //QFile albumDetails("albumdetails.xml");
    //MainWindow window("artists", "albums", &albumDetails);
    //    window.show();
    return app.exec();
}
