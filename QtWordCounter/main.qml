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

    property string filePath: ""

    WordCounter {
        id: wordCounter
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 10

        Row {
            spacing: 10

            Button {
                id: openButton
                width: appWindow.width/4 - 2 * parent.spacing
                height: textButton.height * 2
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
                    color: "#1DB93C"
                    radius: 6
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
                            filePath = fileDialog.currentFile.toString().replace("file:///", "")
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
                    color: "#1DB93C"
                    radius: 6
                }

                onClicked: {
                    console.log("startButton")
                    wordCounter.startProcessing()
                }

            }

            Button {
                id: cancelButton
                width: openButton.width
                height: openButton.height
                padding: openButton.padding

                contentItem: Row {
                    spacing: 5
                    anchors.centerIn: parent

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("ОТМЕНА")
                        font.bold: true
                        color: "white"
                    }
                }

                background: Rectangle {
                    color: "#1DB93C"
                    radius: 6
                }

                onClicked: {
                    console.log("cancelButton")
                    wordCounter.cancelProcessing()
                    filePath = "не выбран"
                }
            }

            Button {
                id: testButton
                width: openButton.width
                height: openButton.height
                padding: openButton.padding

                contentItem: Row {
                    spacing: 5
                    anchors.centerIn: parent

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("test")
                        font.bold: true
                        color: "white"
                    }
                }

                background: Rectangle {
                    color: "#1DB93C"
                    radius: 6
                }

                onClicked: {
                    console.log("testButton")
                    wordCounter.printList()
                }
            }
        }

        Text {
            id: fileInfoText
            width: parent.width
            wrapMode: Text.WordWrap
            text: filePath !== "" ? qsTr("Файл ") + filePath : qsTr("Файл не выбран")
            color: "black"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }

        ProgressBar {
            id: progressBar
            width: parent.width
            height: 10
            value: wordCounter.getProgress/100
        }

        Column {
            id: histogram
            width: parent.width
            spacing: 5

            Repeater {
                model: wordCounter.getWordHighestResult
                delegate: Row {
                    width: histogram.width
                    height: 30
                    spacing: 5

                    Rectangle {
                        width: (modelData.count / (wordCounter.getWordHighestResult.length > 0 ? wordCounter.getWordHighestResult[0].count : 1)) * histogram.width
                        height: parent.height
                        color: "#1DB93C"
                        radius: 4

                        Text {
                            text: modelData.word + " (" + modelData.count + ")"
                            color: "white"
                            anchors.centerIn: parent
                            elide: Text.ElideRight
                            font.pixelSize: 12
                        }
                    }
                }
            }
        }
    }
}
