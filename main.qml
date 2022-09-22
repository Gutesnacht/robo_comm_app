import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.3

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

    ComboBox {
        width: 200
        editable: true
        model: ListModel {
            id: model
            ListElement { text: "No Device found yet"; color: "Red" }
        }
        onAccepted: {
            if (find(currentText) === -1) {
                model.append({text: editText})
                currentIndex = find(editText)
            }
        }
    }

    // we need a drop down menu that gives us potential interface names


}

