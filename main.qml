import QtQuick 6.5
import QtQuick.Controls 6.5
import Qt.labs.qmlmodels 6.5

ApplicationWindow {
    id: window
    visible: true
    height: 860
    width: 460

//diese Variante funzt unter QML 6.4
 /*   TableView{
        id: tabelle

          anchors.fill: parent
          columnSpacing: 2
          rowSpacing: 2
          clip: true
          focus: true

        topMargin: horizontalHeader.implicitHeight

        model: sqlModel


                selectionModel: ItemSelectionModel {
                   model: tabelle.model
                }

                 delegate: Rectangle {
                     implicitWidth: eingabe.width
                     implicitHeight: eingabe.height
                     color: selected ? "yellow" : "lightgray"

                     required property bool selected

                     TextInput {
                         id: eingabe
                         text: display
                         onEditingFinished:
                         {
                            console.log(model.row)
                             console.log(model.column)

                             console.log(display)

                              console.log(text)
                             display = eingabe.text
                             updateSql()
                         }

                     }
                     MouseArea {
                         onDoubleClicked: selected = true
                     }
    }

                 leftMargin: checkColumn.width

                 VerticalHeaderView {
                     id: checkColumn
                     parent: tabelle
                     syncView: tabelle
                     selectionModel: tabelle.selectionModel
                     boundsBehavior: tabelle.boundsBehavior
                     delegate: CheckBox {
                         required property int row
                         required property bool selected
                         checked: selected
                         onToggled: tabelle.selectionModel.select(tabelle.model.index(row, 0), ItemSelectionModel.Toggle | ItemSelectionModel.Rows)
                     }
                 }


        ScrollIndicator.vertical: ScrollIndicator { }
        ScrollIndicator.horizontal: ScrollIndicator { }


    }  // ende tabelle

    */

    TableView {
        id: tabelle
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        resizableColumns: true
        resizableRows: true
        clip: true
         topMargin: horizontalHeader.implicitHeight

         //leftMargin: checkColumn.width


        model: sqlModel


        selectionModel: ItemSelectionModel {
            model: tabelle.model
        }

    delegate: DelegateChooser {

    DelegateChoice{
        column: 0
        delegate: Feld{}
    }
    DelegateChoice{
        column: 1
        delegate: Feld{}
    }
    DelegateChoice{
                    column: 2
                     delegate: ComboBox {
                         id: myCBox
                         implicitWidth: 140

                         onActivated: {
                           sqlModel.setData(sqlModel.index(row, column), currentIndex)
                           updateSql()
                         }
                         Component.onCompleted: {
                           model = sqlModel.getRelation(sqlModel.index(row, column))
                            // console.log("myCBox here must be completed:", myCBox.find(currentText));
                            // console.log("kram: ",sqlModel.data(sqlModel.index(row, column)))
                            // var ComboBoxIdx = myCBox.find(sqlModel.data(sqlModel.index(row, column)))
                            // console.log("Index:",ComboBoxIdx)
                             currentIndex =myCBox.find(sqlModel.data(sqlModel.index(row, column)))

                         }
                     }
    }

    DelegateChoice{
        column: 3
        delegate: Feld{}
        }
    }

    }





function updateSql(){
    sqlModel.updateModel()
}

//property alias operation: tabelle.contentHeight
//Button {
//    id: deleteButton
//    x: 0
//    y: operation + horizontalHeader.implicitHeight
////    anchors.left: operation
////    anchors.left: tabelle.left
////    anchors.right: tabelle.right
//    width: text.implicitHeight
//    height: text.implicitWidth
////    implicitWidth: 10
////    implicitHeight: 10

//    text: ' - '

//    onClicked: {
//        var selectedRows = tabelle.selectionModel.selectedRows();
//        var sel = [];
//      console.log(operation + horizontalHeader.implicitHeight)
//        selectedRows.forEach(function(rowIndex) {sel.push(rowIndex.row)})
//                    //tabelle.selectionModel.selectedRows()  .forEach(function(rowIndex) {selectedRows.push(rowIndex)})
//                    sqlModel.deleteRows(sel)
//                    tabelle.selectionModel.clear()
//                    //tabelle.selectionModel.select(tableView.currentRow)

//         sqlModel.updateModel()
//  }
// }

// }

//    HorizontalHeaderView {
//               id: horizontalHeader
//               syncView: tabelle
//               model: sqlModel
//               anchors.left: tabelle.left

//           }

}
