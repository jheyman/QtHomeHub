import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.VirtualKeyboard 2.3
import QtQuick.VirtualKeyboard.Settings 2.2

import ToDo 1.0

ColumnLayout {
    Text {
        id: todotitre
        text: "A faire"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.pointSize: 20
        Layout.fillWidth: true
        Layout.preferredHeight: 30
        //Layout.fillHeight: true
        /*
        Rectangle {
            color: "green"
            opacity: 0.4
            anchors.fill: parent
        }*/
    }
    //Frame {
    RowLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        ListView {

            //implicitWidth: parent.width
            //implicitHeight: 250
            anchors.fill: parent
            clip: true
            currentIndex: count-1

            model: ToDoModel {
                list: toDoList
            }

            delegate: RowLayout {
                id: rowL
                //width: ListView.isCurrentItem ? parent.width: 200
                width:parent.width
                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }

                TextField {
                    id: ttt
                    text: model.description
                    color: "white"

                    onEditingFinished: {
                        model.description = text
                        focus = false
                    }
                    Layout.fillWidth: true
                }
            }
            /*
            Rectangle {
                color: "yellow"
                opacity: 0.4
                anchors.fill: parent
            }
            */
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Button {
            text: qsTr("Add new item")
            onClicked: toDoList.appendItem()

            Layout.fillWidth: true

            /*
            Rectangle {
                color: "blue"
                opacity: 0.4
                anchors.fill: parent
            }
            */
        }
        Button {
            text: qsTr("Remove completed")
            onClicked: toDoList.removeCompletedItems()
            Layout.fillWidth: true
           /*
            Rectangle {
                color: "red"
                opacity: 0.4
                anchors.fill: parent
            }
            */
        }






    }
}
