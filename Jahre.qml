import QtQuick 6.5
import Qt.labs.qmlmodels 6.5


     TableModel {
           TableModelColumn { display: "JahrId" }
           TableModelColumn { display: "Jahr" }

           rows: [
               {
                   "JahrId": "1",
                   "Jahr": "2001"
               },
               {
                   "JahrId": "2",
                   "Jahr": "2002"
               },
               {
                   "JahrId": "3",
                   "Jahr": "2003"
               }
           ]
       }

