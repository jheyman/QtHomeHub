import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Page 3")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    TextField {
        id: text1
        onEditingFinished: focus = false
        anchors.bottom: parent.bottom
    }

    Label {
        text: qsTr("You are on Page 3.")
        anchors.centerIn: parent
    }
}
