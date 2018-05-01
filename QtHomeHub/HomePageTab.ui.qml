import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
    width: 600
    height: 400
    property alias photoSource: image.source
    property alias imgclickregion: image.clickregion
    property alias pictureLoadingIndicator: image.pictureLoadingIndicator

    Column {

        Rectangle {
            id: photoFrame
            width: 800
            height: 600
            color: "transparent"
            border.width: 1
            border.color: "grey"

            property real margin: 5

            // Use Canvas to draw custom corners with lines
            Canvas {
                anchors.centerIn: parent
                anchors.fill: parent
                anchors.margins: parent.margin
                onPaint: {
                    var context = getContext("2d")

                    // Setup line tracing
                    context.beginPath()
                    context.lineWidth = 2
                    context.strokeStyle = "white"

                    // top-left corner
                    context.moveTo(0, 0)
                    context.lineTo(0, 30)
                    context.moveTo(0, 0)
                    context.lineTo(30, 0)

                    //top-right corner
                    context.moveTo(width, 0)
                    context.lineTo(width - 30, 0)
                    context.moveTo(width, 0)
                    context.lineTo(width, 30)

                    //bottom-left corner
                    context.moveTo(0, height)
                    context.lineTo(0, height - 30)
                    context.moveTo(0, height)
                    context.lineTo(30, height)

                    // bottom-right corner
                    context.moveTo(width, height)
                    context.lineTo(width - 30, height)
                    context.moveTo(width, height)
                    context.lineTo(width, height - 30)

                    //render
                    context.stroke()
                }

                Image {
                    id: image
                    cache: false
                    anchors.centerIn: parent
                    anchors.fill: parent
                    anchors.margins: 15

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
        }

        Rectangle {
            id: weatherWidget
            width: 800
            height: 200
            color: "transparent"
            border.width: 1
            border.color: "grey"

            property real margin: 5

            // Use Canvas to draw custom corners with lines
            Canvas {
                anchors.centerIn: parent
                anchors.fill: parent
                anchors.margins: parent.margin
                onPaint: {
                    var context = getContext("2d")

                    // Setup line tracing
                    context.beginPath()
                    context.lineWidth = 2
                    context.strokeStyle = "white"

                    // top-left corner
                    context.moveTo(0, 0)
                    context.lineTo(0, 30)
                    context.moveTo(0, 0)
                    context.lineTo(30, 0)

                    //top-right corner
                    context.moveTo(width, 0)
                    context.lineTo(width - 30, 0)
                    context.moveTo(width, 0)
                    context.lineTo(width, 30)

                    //bottom-left corner
                    context.moveTo(0, height)
                    context.lineTo(0, height - 30)
                    context.moveTo(0, height)
                    context.lineTo(30, height)

                    // bottom-right corner
                    context.moveTo(width, height)
                    context.lineTo(width - 30, height)
                    context.moveTo(width, height)
                    context.lineTo(width, height - 30)

                    //render
                    context.stroke()
                }
            }
        }
    }
}
