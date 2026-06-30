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
    // TodoModel {
    //     id: todoModel
    // }

    BackendModel {
        id: backendModel
    }

    TodoManager {
        id: manager
        model: backendModel
    }

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
            // doneCount: todoModel.doneCount
            // totalCount: todoModel.totalCount
            // todoCount: todoModel.todoCount
            // onFilterChanged: todoModel.setFilter(countSection.filter)
        }

        TodoInput {
            Layout.fillWidth: true
            onTaskSubmitted: (text) => {
                if (manager.addTask(text)) {
                    console.log("Task added: " + text)
                }
                else {
                    console.log("Add task failed: " + text)
                }
            }
        }
        TodoListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 10
            model: backendModel
            delegate: Component {
                TodoDelegate {
                    width: ListView.view.width
                    onDeleteRequested: (uuid) => {
                        manager.removeTask(uuid)
                    }
                    onCheckedChanged: (uuid, checked) => {
                        manager.setDone(uuid, checked)
                    }
                }
            }
        }
    }
}