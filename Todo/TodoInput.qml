import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

FocusScope {
    id: root
    implicitHeight: rowLayout.implicitHeight
    implicitWidth: rowLayout.implicitWidth
    signal taskSubmitted(string text)

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        TextField {
            id: textInput
            Layout.fillWidth: true
            placeholderText: "Enter your task"
            onAccepted: buttonInput.clicked()
            focus: true
        }
        Button {
            id: buttonInput
            text: "Add"
            Layout.rightMargin: 10
            onClicked: {
                if (textInput.text.length > 0) {
                    root.taskSubmitted(textInput.text)
                    textInput.text = ""
                }
                textInput.forceActiveFocus()
            }
        }
    }
}