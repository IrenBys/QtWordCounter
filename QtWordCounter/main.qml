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

    minimumHeight: header.height + openButton.height + fileInfoText.height + progressBar.height + footer.height + 100
    minimumWidth: 3 * openButton.width

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

    Rectangle {
        id: header
        width: parent.width
        height: openButton.height
        color: "light grey"

        Row {
            anchors.centerIn: parent
            spacing: 10

            Text {
                id: appTitle
                text: qsTr("Word Counter")
                color: "white"
                font.bold: true
                font.pixelSize: 14
            }

        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        anchors.topMargin: spacing
        anchors.bottom: footer.top
        anchors.bottomMargin: spacing
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

        CustomHistogram {
            id: histogramComponent
            wordCounter: wordCounter
            width: appWindow.width - 4 * parent.spacing
            height: appWindow.height - header.height - openButton.height - fileInfoText.height - progressBar.height - footer.height - 5 * parent.spacing
        }
    }

    Rectangle {
        id: footer
        width: parent.width
        height: openButton.height
        anchors.bottom: parent.bottom
        color: "light grey"

        Row {
            anchors.centerIn: parent
            spacing: 20

            Text {
                id: footerText
                text: qsTr("Test task for 2GIS")
                color: "white"
                font.bold: true
                font.pixelSize: 14
            }
        }
    }
}
