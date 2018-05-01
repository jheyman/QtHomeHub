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
            //////////////////////////
            // PHOTOFRAME-related data
            //////////////////////////
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

            //////////////////////////
            // WEATHER-related data
            //////////////////////////
            currentWeatherIcon: (model.hasValidWeather ? model.currentWeather.weatherIcon : "00")
            currentWeatherTemperature: (model.hasValidWeather ? model.currentWeather.temperature : "??")
            currentWeatherDescription:(model.hasValidWeather ? model.currentWeather.weatherDescription : "No weather data")

            forecast1WeatherIcon: (model.hasValidWeather ? model.forecast1Weather.weatherIcon : "00")
            forecast1WeatherTemperature: (model.hasValidWeather ? model.forecast1Weather.dayOfWeek : "??")
            forecast1WeatherDescription: (model.hasValidWeather ? model.forecast1Weather.temperature : "??/??")

            forecast2WeatherIcon:(model.hasValidWeather ? model.forecast2Weather.weatherIcon : "00")
            forecast2eatherTemperature: (model.hasValidWeather ? model.forecast2Weather.dayOfWeek : "??")
            forecast2WeatherDescription: (model.hasValidWeather ? model.forecast2Weather.temperature : "??/??")

            forecast3WeatherIcon:(model.hasValidWeather ? model.forecast3Weather.weatherIcon : "00")
            forecast3WeatherTemperature: (model.hasValidWeather ? model.forecast3Weather.dayOfWeek : "??")
            forecast3WeatherDescription: (model.hasValidWeather ? model.forecast3Weather.temperature : "??/??")

            forecast4WeatherIcon:(model.hasValidWeather ? model.forecast4Weather.weatherIcon : "00")
            forecast4WeatherTemperature: (model.hasValidWeather ? model.forecast4Weather.dayOfWeek : "??")
            forecast4WeatherDescription: (model.hasValidWeather ? model.forecast4Weather.temperature : "??/??")
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
