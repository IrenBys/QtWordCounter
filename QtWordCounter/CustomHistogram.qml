import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: histogramItem
    property var wordCounter: null
    width: parent.width
    height: parent.height

    ScrollView {
        id: scrollView
        width: histogramItem.width
        height: histogramItem.height

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
