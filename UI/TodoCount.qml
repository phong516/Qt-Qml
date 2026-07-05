import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    implicitHeight: mainLayout.implicitHeight
    implicitWidth: mainLayout.implicitWidth
    property int totalCount: 0
    property int doneCount: 0
    property int todoCount: 0
    property string filter: "all"
    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        RowLayout {
            id: layoutCount
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    anchors.fill: parent
                    text: "Total: " + root.totalCount
                }
            }
            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    anchors.fill: parent
                    text: "Done: " + root.doneCount
                }
            }
            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    anchors.fill: parent
                    text: "Todo: " + root.todoCount
                }
            }
        }
        RowLayout {
            id: layoutButton
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            RadioButton {
                id: allButton
                checked: true
                text: "All"
                onCheckedChanged: {
                    if (checked) {
                        root.filter = "all"
                    }
                }
            }
            RadioButton {
                id: doneButton
                checked: false
                text: "Done"
                onCheckedChanged: {
                    if (checked) {
                        root.filter = "done"
                    }
                }
            }
            RadioButton {
                id: todoButton
                checked: false
                text: "Todo"
                onCheckedChanged: {
                    if (checked) {
                        root.filter = "todo"
                    }
                }
            }
        }
    }
}