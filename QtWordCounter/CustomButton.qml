import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: customButton
    property alias buttonText: textButton.text
    signal onClickedSignal

    width: appWindow.width/3 - 2 * parent.spacing
    height: textButton.height * 2
    padding: textButton.height * 0.6

    contentItem: Row {
        spacing: 5
        anchors.centerIn: parent

        Text {
            id: textButton
            anchors.centerIn: parent
            text: qsTr("")
            font.bold: true
            color: "white"
        }
    }

    background: Rectangle {
        color: "#1DB93C"
        radius: 6
    }

    onClicked: {
        customButton.onClickedSignal()
    }

}
