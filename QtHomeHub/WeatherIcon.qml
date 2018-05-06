/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: container

    property string weatherIcon: "00"

    Image {
        id: img
        fillMode: Image.PreserveAspectFit
        sourceSize.width: 256
        sourceSize.height: 256
        source: {
            switch (weatherIcon) {
            case "01d":
            case "01n":
                 "../icons/erikflowers/wi-day-sunny.svg"
                break;
            case "02d":
            case "02n":
                "../icons/erikflowers/wi-day-cloudy.svg"
                break;
            case "03d":
            case "03n":
                "../icons/erikflowerst/wi-cloud.svg"
                break;
            case "04d":
            case "04n":
                "../icons/erikflowers/wi-cloudy.svg"
                break;
            case "09d":
            case "09n":
                "../icons/erikflowers/wi-day-rain.svg"
                break;
            case "10d":
            case "10n":
                "../icons/erikflowers/wi-rain.svg"
                break;
            case "11d":
            case "11n":
                "../icons/erikflowers/wi-thunderstorm.svg"
                break;
            case "13d":
            case "13n":
                "../icons/erikflowers/wi-snow.svg"
                break;
            case "50d":
            case "50n":
                "../icons/erikflowers/wi-fog.svg"
                break;
            default:
                "../icons/weather-unknown.png"
            }
         /*
            case "01d":
            case "01n":
                 "../icons/weather-sunny.png"
                break;
            case "02d":
            case "02n":
                "../icons/weather-sunny-very-few-clouds.png"
                break;
            case "03d":
            case "03n":
                "../icons/weather-few-clouds.png"
                break;
            case "04d":
            case "04n":
                "../icons/weather-overcast.png"
                break;
            case "09d":
            case "09n":
                "../icons/weather-showers.png"
                break;
            case "10d":
            case "10n":
                "../icons/weather-showers.png"
                break;
            case "11d":
            case "11n":
                "../icons/weather-thundershower.png"
                break;
            case "13d":
            case "13n":
                "../icons/weather-snow.png"
                break;
            case "50d":
            case "50n":
                "../icons/weather-fog.png"
                break;
            default:
                "../icons/weather-unknown.png"
            }
            */
        }
        smooth: true
        anchors.fill: parent
    }

    ColorOverlay{
            anchors.fill: img
            source:img
            color:"pink"
            //transform:rotation
            antialiasing: true
        }
}
