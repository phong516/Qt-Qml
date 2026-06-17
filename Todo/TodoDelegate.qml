import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FocusScope {
    id: root
    required property string uuid
    required property string desc
    signal deleteRequested(string uuid)
    implicitHeight: layout.implicitHeight
    implicitWidth: 500
    RowLayout {
        id: layout
        Frame {
            Layout.fillWidth: true
            Label {
               text: desc
            }
        }
        Button {
            text: "Delete"
            onClicked: {
                root.deleteRequested(uuid)
            }
        }
    }
}