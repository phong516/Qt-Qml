import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import UI
import Backend

ApplicationWindow {
    id: root
    width: 500
    height: 500
    visible: true
    title: "ToDo App"

    ColumnLayout {
        id: layout
        anchors.fill: parent

        Label {
            text: "To Do App"
            Layout.alignment: Qt.AlignHCenter
        }

        TodoCount {
            id: countSection
            Layout.fillWidth: true
            doneCount: manager.doneCount
            totalCount: manager.totalCount
            todoCount: manager.todoCount
            onFilterChanged: manager.setFilter(countSection.filter)
        }

        TodoInput {
            Layout.fillWidth: true
            onTaskSubmitted: text => {
                if (manager.addTask(text)) {
                    console.log("Task added: " + text);
                } else {
                    console.log("Add task failed: " + text);
                }
            }
        }
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 10
            model: manager.proxyModel
            delegate: TodoDelegate {
                width: ListView.view.width
                onDeleteRequested: uuid => {
                    manager.removeTask(uuid);
                }
                onCheckedChanged: (uuid, checked) => {
                    manager.setDone(uuid, checked);
                }
            }
        }
    }
}
