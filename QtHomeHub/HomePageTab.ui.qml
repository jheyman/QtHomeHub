import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    width: 600
    height: 400
    property alias photoSource: image.source
    property alias photoPathName: image.pathName

    property alias imgclickregion: image.clickregion
    property alias pictureLoadingIndicator: image.pictureLoadingIndicator

    property alias currentWeatherIcon: current.weatherIcon
    property alias currentWeatherTemperature: current.topText
    property alias currentWeatherDescription: current.bottomText

    property alias forecast1WeatherIcon: forecast1.weatherIcon
    property alias forecast1WeatherTemperature: forecast1.topText
    property alias forecast1WeatherDescription: forecast1.bottomText

    property alias forecast2WeatherIcon: forecast2.weatherIcon
    property alias forecast2eatherTemperature: forecast2.topText
    property alias forecast2WeatherDescription: forecast2.bottomText

    property alias forecast3WeatherIcon: forecast3.weatherIcon
    property alias forecast3WeatherTemperature: forecast3.topText
    property alias forecast3WeatherDescription: forecast3.bottomText

    property alias forecast4WeatherIcon: forecast4.weatherIcon
    property alias forecast4WeatherTemperature: forecast4.topText
    property alias forecast4WeatherDescription: forecast4.bottomText

    /////////////////////////
    // PHOTOFRAME WIDGET PART
    /////////////////////////
    Rectangle {
        id: photoFrame
        width: 800
        height: 600
        color: "transparent"
        //color: "red"

        property real margin: 5

        // Use Canvas to draw custom corners with lines
        Canvas {
            id: canvas
            anchors.centerIn: parent
            anchors.fill: parent
            width: parent.width
            anchors.margins: parent.margin
            //anchors.margins: 0
            property real corner_margin: 8
            property real corner_length: 25

            onPaint: {
                var context = getContext("2d")

                // clear canvas
                context.reset()

                // Render image pathname text
                context.fillStyle = "white"
                context.font = "12px sans-serif"
                context.fillText(
                            photoPathName,
                            image.imageStartX + image.paintedWidth / 2 - context.measureText(
                                photoPathName).width / 2,
                            image.imageStartY - corner_margin - 8)
                context.stroke()

                // Draw corners around image
                context.beginPath()
                context.lineWidth = 2

                context.strokeStyle = "white"

                // top-left corner
                context.moveTo(image.imageStartX - corner_margin,
                               image.imageStartY - corner_margin)
                context.lineTo(
                            image.imageStartX - corner_margin + corner_length,
                            image.imageStartY - corner_margin)
                context.moveTo(image.imageStartX - corner_margin,
                               image.imageStartY - corner_margin)
                context.lineTo(
                            image.imageStartX - corner_margin,
                            image.imageStartY - corner_margin + corner_length)

                // top-right
                context.moveTo(
                            image.imageStartX + image.paintedWidth + corner_margin,
                            image.imageStartY - corner_margin)
                context.lineTo(
                            image.imageStartX + image.paintedWidth + corner_margin - corner_length,
                            image.imageStartY - corner_margin)
                context.moveTo(
                            image.imageStartX + image.paintedWidth + corner_margin,
                            image.imageStartY - corner_margin)
                context.lineTo(
                            image.imageStartX + image.paintedWidth + corner_margin,
                            image.imageStartY - corner_margin + corner_length)

                // bottom-left
                context.moveTo(
                            image.imageStartX - corner_margin,
                            image.imageStartY + image.paintedHeight + corner_margin)
                context.lineTo(
                            image.imageStartX - corner_margin + corner_length,
                            image.imageStartY + image.paintedHeight + corner_margin)
                context.moveTo(
                            image.imageStartX - corner_margin,
                            image.imageStartY + image.paintedHeight + corner_margin)
                context.lineTo(
                            image.imageStartX - corner_margin,
                            image.imageStartY + image.paintedHeight + corner_margin - corner_length)

                // bottom-right
                context.moveTo(
                            image.imageStartX + image.paintedWidth + corner_margin,
                            image.imageStartY + image.paintedHeight + corner_margin)
                context.lineTo(
                            image.imageStartX + image.paintedWidth + corner_margin - corner_length,
                            image.imageStartY + image.paintedHeight + corner_margin)
                context.moveTo(
                            image.imageStartX + image.paintedWidth + corner_margin,
                            image.imageStartY + image.paintedHeight + corner_margin)
                context.lineTo(
                            image.imageStartX + image.paintedWidth + corner_margin,
                            image.imageStartY + image.paintedHeight + corner_margin - corner_length)

                context.stroke()
            }

            Image {
                id: image
                cache: false
                anchors.centerIn: parent
                anchors.fill: parent

                // top margin is higher, to give some canvas space for image tile text rendering
                anchors.topMargin: 30

                // other margin are set to accomodate the image corners
                anchors.bottomMargin: canvas.corner_margin + 1
                anchors.leftMargin: canvas.corner_margin + 1
                anchors.rightMargin: canvas.corner_margin + 1

                source: "image://imageProvider/emptypic"
                sourceSize.width: width
                sourceSize.height: height
                fillMode: Image.PreserveAspectFit

                property alias clickregion: clickregion
                property alias pictureLoadingIndicator: busyIndicator.running

                property real imageStartX
                property real imageStartY
                property string pathName

                // depending on actual/resized to fit image size, adjust image top-left corner coordinate variables
                // and force a repaint of the Canvas, so that the image corners are re-drawn accordingly
                onPaintedGeometryChanged: {
                    imageStartX = image.anchors.leftMargin
                            + (image.width / 2 - image.paintedWidth / 2)
                    imageStartY = image.anchors.topMargin
                            + (image.height / 2 - image.paintedHeight / 2)
                    canvas.requestPaint()
                }

                BusyIndicator {
                    id: busyIndicator
                    // activate it by default: loading of first image will stop it once completed.
                    running: true
                    anchors.centerIn: parent
                    width: 50
                    height: 50
                }

                MouseArea {
                    id: clickregion
                    anchors.fill: parent
                }
            }
            /*
            Rectangle {
                anchors.fill: parent
                color: "green"
                z: -1
            }
            */
        }
    }

    ///////////////////////
    // WEATHER WIDGET PART
    ///////////////////////
    Rectangle {
        id: weatherWidget
        width: 800
        height: 400
        color: "transparent"
        anchors.top: photoFrame.bottom
        anchors.left: photoFrame.left

        //border.width: 1
        //border.color: "grey"
        property real margin: 5

        Item {
            id: weatherWidgetMain
            anchors.fill: parent
            //anchors.margins: parent.margin
            // Somehow this way to define it supresses warning "Unable to assign [undefined] to double"
            Binding on anchors.margins {
                when: true
                value: parent.margin
            }

            Column {
                spacing: 6

                anchors {
                    fill: parent
                    topMargin: 6
                    bottomMargin: 6
                    leftMargin: 6
                    rightMargin: 6
                }

                BigForecastIcon {
                    id: current
                    width: weatherWidgetMain.width - 12
                    height: 2 * (weatherWidgetMain.height - 25 - 12) / 3
                }

                Row {
                    id: iconRow
                    spacing: 6
                    width: weatherWidgetMain.width - 12
                    height: (weatherWidgetMain.height - 25 - 24) / 3

                    property real iconWidth: iconRow.width / 4 - 10
                    property real iconHeight: iconRow.height

                    ForecastIcon {
                        id: forecast1
                        width: iconRow.iconWidth
                        height: iconRow.iconHeight
                    }
                    ForecastIcon {
                        id: forecast2
                        width: iconRow.iconWidth
                        height: iconRow.iconHeight
                    }
                    ForecastIcon {
                        id: forecast3
                        width: iconRow.iconWidth
                        height: iconRow.iconHeight
                    }
                    ForecastIcon {
                        id: forecast4
                        width: iconRow.iconWidth
                        height: iconRow.iconHeight
                    }
                }
            }
        }
    }

    ///////////////////////
    // TOP RIGHT WIDGET PART
    ///////////////////////
    Rectangle {
        id: todoListWidget
        width: 500
        height: 500
        color: "transparent"
        anchors.top: photoFrame.top
        anchors.left: photoFrame.right

        //border.width: 1
        //border.color: "grey"
        property real margin: 5

        ToDoList {
            anchors.centerIn: parent
            anchors.fill: parent
            anchors.margins: 15
        }
    }

    ///////////////////////
    // BOTTOM RIGHT WIDGET PART
    ///////////////////////
    Rectangle {
        id: shoppingListWidget
        width: 500
        height: 500
        color: "transparent"
        anchors.top: todoListWidget.bottom
        anchors.left: todoListWidget.left

        //border.width: 1
        //border.color: "grey"
        property real margin: 5

        ShoppingList {
            anchors.centerIn: parent
            anchors.fill: parent
            anchors.margins: 15
        }
    }


    /////////////////////////
    // GRAPH WIDGET PART
    /////////////////////////
    Rectangle {
        id: graphFrame
        width: 500
        height: 200
        //color: "transparent"
        color: "red"

        anchors.top: todoListWidget.top
        anchors.left: todoListWidget.right

        property real margin: 5

        // Use Canvas to draw custom corners with lines
        Canvas {
            id: graphCanvas
            anchors.centerIn: parent
            anchors.fill: parent
            width: parent.width
            anchors.margins: parent.margin
            //anchors.margins: 0
            property real corner_margin: 8
            property real corner_length: 25

            onPaint: {
                var context = getContext("2d")

                // clear canvas
                context.reset()

                // Render image pathname text
                /*
                context.fillStyle = "white"
                context.font = "12px sans-serif"
                context.fillText(
                            photoPathName,
                            image.imageStartX + image.paintedWidth / 2 - context.measureText(
                                photoPathName).width / 2,
                            image.imageStartY - corner_margin - 8)
                context.stroke()
                */

                // Draw corners around image
                context.beginPath()
                context.lineWidth = 2

                context.strokeStyle = "white"

                // top-left corner
                /*
                context.moveTo(image.imageStartX - corner_margin,
                               image.imageStartY - corner_margin)
                context.lineTo(
                            image.imageStartX - corner_margin + corner_length,
                            image.imageStartY - corner_margin)

                 context.stroke()
                */
            }
        }
    }


}
