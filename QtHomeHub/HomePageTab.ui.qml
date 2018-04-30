import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
    width: 600
    height: 400
    property alias theText: myLabel.text
    property alias photoSource: image.source
    property alias imgclickregion: image.clickregion
    property alias pictureLoadingIndicator: image.pictureLoadingIndicator

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        id: myLabel
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }

    TextField {
        id: textField
        x: 71
        y: 73
        text: qsTr("Text Field")
    }

    Image {
        id: image
        cache: false
        x: 71
        y: 140
        width: 640
        height: 480
        source: "image://imageProvider/emptypic"
        sourceSize.width: width
        sourceSize.height: height
        fillMode: Image.PreserveAspectFit
        property alias clickregion: clickregion
        property alias pictureLoadingIndicator: busyIndicator.running

        BusyIndicator {
            id: busyIndicator
            running: false
            anchors.centerIn: parent
            width: 50
            height: 50
        }

        MouseArea {
            id: clickregion
            anchors.fill: parent
        }
    }
}
