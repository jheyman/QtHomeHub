import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.VirtualKeyboard 2.3
import QtQuick.VirtualKeyboard.Settings 2.2

import Shopping 1.0

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
                onClicked: shoppingList.clearItems()
            }
        }

        Text {
            id: shoppingTitle
            text: "Courses"
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
                onClicked: shoppingList.appendItem()
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

            model: ShoppingModel {
                list: shoppingList
            }

            delegate: RowLayout {
                id: rowL
                width:parent.width

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
