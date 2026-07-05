import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

FocusScope {
    id: root
    required property string uuid
    required property string desc
    required property bool done
    signal deleteRequested(string uuid)
    signal checkedChanged(string uuid, bool checked)
    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth
    RowLayout {
        id: layout
        anchors.fill: parent
        CheckBox {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: root.desc
            checked: root.done
            onCheckedChanged: {
                if (checked !== root.done)
                    root.checkedChanged(root.uuid, checked)
            }
        }
        Button {
            Layout.rightMargin: 10
            text: "Delete"
            onClicked: {
                root.deleteRequested(root.uuid);
            }
        }
    }
}
