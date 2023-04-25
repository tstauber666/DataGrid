import QtQuick 6.5
import QtQuick.Controls 6.5
import Qt.labs.qmlmodels 6.5

    Rectangle {
                implicitWidth: 100
                implicitHeight: 30
    //            color: selected ? "blue" : "lightgray"

    //            required property bool selected

               Text { text: display }

                TableView.editDelegate: TextField {
                                anchors.fill: parent
                                text: display
                                horizontalAlignment: TextInput.AlignHCenter
                                verticalAlignment: TextInput.AlignVCenter
                                Component.onCompleted: {
                                    selectAll()

                                }
                                TableView.onCommit: {
                                    display = text
                                    updateSql()

                                }


                            }
}
