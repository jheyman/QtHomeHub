import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.VirtualKeyboard 2.3
import QtQuick.VirtualKeyboard.Settings 2.2

import ToDo 1.0

ColumnLayout {

    RowLayout {
        Layout.fillWidth: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 6

        Image {
            anchors.left: parent.left

            source: "images/delete-button.svg"
            sourceSize.width: 32
            sourceSize.height: 32

            MouseArea {
                anchors.fill: parent
                onClicked: toDoList.removeCompletedItems()
            }
        }

        Text {
            id: todoTitle
            text: "Todo"
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.pointSize: 20
            Layout.fillWidth: true
            Layout.preferredHeight: 30
        }

        Image {
            anchors.right: parent.right
            source: "images/add-button.svg"
            sourceSize.width: 32
            sourceSize.height: 32

            MouseArea {
                anchors.fill: parent
                onClicked: toDoList.appendItem()
            }
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        ListView {

            anchors.fill: parent
            clip: true
            currentIndex: count-1

            model: ToDoModel {
                list: toDoList
            }

            delegate: RowLayout {
                id: rowL
                width:parent.width
                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }

                TextField {
                    text: model.description
                    color: "white"

                    onEditingFinished: {
                        model.description = text
                        focus = false
                    }
                    Layout.fillWidth: true
                }
            }
        }
    }
}
