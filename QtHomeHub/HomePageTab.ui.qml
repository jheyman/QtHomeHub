import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
    width: 600
    height: 400
    property alias photoSource: image.source
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

        //border.width: 1
        //border.color: "grey"
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
        anchors.top : photoFrame.bottom
        anchors.left: photoFrame.left

        //border.width: 1
        //border.color: "grey"
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
            Item {
                id: weatherWidgetMain
                anchors.fill: parent
                anchors.margins: parent.margin

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
    }

    ///////////////////////
    // TOP RIGHT WIDGET PART
    ///////////////////////
    Rectangle {
        id: topRightWidget
        width: 800
        height: 600
        color: "transparent"
        anchors.top : photoFrame.top
        anchors.left: photoFrame.right

        //border.width: 1
        //border.color: "grey"
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
            Item {
                anchors.fill: parent
                anchors.margins: parent.margin
            }
        }
    }

    ///////////////////////
    // BOTTOM RIGHT WIDGET PART
    ///////////////////////
    Rectangle {
        id: bottomRightWidget
        width: 800
        height: 400
        color: "transparent"
        anchors.top : weatherWidget.top
        anchors.left: weatherWidget.right

        //border.width: 1
        //border.color: "grey"
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
            Item {
                anchors.fill: parent
                anchors.margins: parent.margin
            }
        }
    }
}
