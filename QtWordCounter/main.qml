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

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 10

        Row {
            spacing: 10

            CustomButton {
                id: openButton
                buttonText: qsTr("ОТКРЫТЬ")

                onClicked: {
                    console.log("openButton")
                   fileDialog.open();
                }
            }

            CustomButton {
                id: startButton
                buttonText: qsTr("СТАРТ")

                onClicked: {
                    console.log("startButton")
                    wordCounter.startProcessing()
                }

            }

            CustomButton {
                id: cancelButton
                buttonText: qsTr("ОТМЕНА")

                onClicked: {
                    console.log("cancelButton")
                    wordCounter.cancelProcessing()
                    filePath = "не выбран"
                }
            }
        }

        Text {
            id: fileInfoText
            width: appWindow.width - 4 * parent.spacing
            wrapMode: Text.WordWrap
            text: filePath !== "" ? qsTr("Файл ") + filePath : qsTr("Файл не выбран")
            color: "grey"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }

        ProgressBar {
            id: progressBar
            width: appWindow.width - 4 * parent.spacing
            height: 10
            value: wordCounter.getProgress/100
        }

        ScrollView {
            id: scrollView
            width: appWindow.width - 4 * parent.spacing
            height: appWindow.height - openButton.height - fileInfoText.height - progressBar.height  - 5 * parent.spacing

            Column {
                id: histogram
                width: scrollView.width - 10
                spacing: 5

                Repeater {
                    model: wordCounter.getWordHighestResult
                    delegate: Row {
                        width: histogram.width
                        height: 34
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
}
