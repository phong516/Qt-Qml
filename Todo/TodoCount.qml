import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth
    property int totalCount: 0
    property int doneCount: 0
    property int todoCount: 0
    RowLayout {
        id: layout
        anchors.fill: parent
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
}
