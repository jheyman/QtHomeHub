import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.VirtualKeyboard 2.3
import QtQuick.VirtualKeyboard.Settings 2.2
import HomeHub 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    HomeHubModel {
        id: model
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        HomePageTab {
            photoSource: model.homeHubPhotoSource

            // photo source is updated by the model when a new one has finished loading: cancel busy indicator then
            onPhotoSourceChanged: pictureLoadingIndicator = false

            // when picture area is touched, reload a fresh image
            imgclickregion.onPressed: {
                // show busy indicator
                pictureLoadingIndicator = true
                // call model to force a refresh of the picture (via an update of its source)
                model.refreshPicture()
            }
        }


        HomeAutomationTab {
        }

        TodoTab {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Général")
        }
        TabButton {
            text: qsTr("Domotique")
        }
        TabButton {
            text: qsTr("Todo")
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        Component.onCompleted: {
            VirtualKeyboardSettings.locale = "fr_FR";
        }

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
