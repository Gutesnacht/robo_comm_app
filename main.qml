import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls

Window {
    id: item

    width: 640
    height: 480
    visible: true
    title: qsTr("Refurb-Robo Comm.")



    signal qmlSignal()

    Button {
        text: "Ok"
        onClicked: item.qmlSignal()
        anchors.centerIn: parent
    }
    Button {
        text: "Cancel"
    }


}

