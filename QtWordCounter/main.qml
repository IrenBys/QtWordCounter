import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import com.example.WordCounter

Window {
    id: appWindow
    width: 400
    height: 700
    visible: true
    title: qsTr("Word Counter")

    WordCounter {
        id: wordCounter
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        padding: 10
        spacing: 10

        Row {
            spacing: 10

            Button {
                id: openButton
                width: appWindow.width/2 - 2 * parent.spacing
                height: textButton.height * 1.5
                padding: textButton.height * 0.6

                contentItem: Row {
                    spacing: 5
                    anchors.centerIn: parent

                    Text {
                        id: textButton
                        anchors.centerIn: parent
                        text: qsTr("ОТКРЫТЬ")
                        font.bold: true
                        color: "white"
                    }
                }

                background: Rectangle {
                    color: "teal"
                    radius: 2
                }

                onClicked: {
                    console.log("openButton")
                   fileDialog.open();
                }

                FileDialog {
                    id: fileDialog
                    title: "Select a file"
                    nameFilters: ["Text files (*.txt)", "All files (*)"]
                    onAccepted: {
                        console.log("fileDialog");
                        if(fileDialog.currentFile) {
                            var filePath = fileDialog.currentFile.toString().replace("file:///", "")
                            wordCounter.openFile(filePath)
                            console.log("File " + filePath + " is open")
                        } else {
                            console.log("No file selected.");
                        }
                    }
                    onRejected: {
                        console.log("File selection was canceled.")
                    }
                }
            }

            Button {
                id: startButton
                width: openButton.width
                height: openButton.height
                padding: openButton.padding

                contentItem: Row {
                    spacing: 5
                    anchors.centerIn: parent

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("СТАРТ")
                        font.bold: true
                        color: "white"
                    }
                }

                background: Rectangle {
                    color: "teal"
                    radius: 2
                }

                onClicked: {
                    console.log("startButton")
                    wordCounter.startProcessing()
                }

            }

        }
    }
}
