import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FocusScope {
    id: root
    required property string uuid
    required property string desc
    signal deleteRequested(string uuid)
    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth
    RowLayout {
        id: layout
        anchors.fill: parent
        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Label {
                anchors.fill: parent
                text: desc
            }
        }
        Button {
            Layout.rightMargin: 10
            text: "Delete"
            onClicked: {
                root.deleteRequested(uuid)
            }
        }
    }
}