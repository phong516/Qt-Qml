import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Todo

ApplicationWindow {
    id: root
    width: 500
    height: 500
    visible: true
    title: "ToDo App"

    TodoModel {
        id: todoModel
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        TodoInput {
            Layout.fillWidth: true
            onTaskSubmitted: (text) => {
                todoModel.addTask(text)
            }
        }
        TodoListView {
            Layout.fillWidth: parent.width
            Layout.fillHeight: true
            model: todoModel
            delegate: TodoDelegate {
                width: ListView.view.width
                onDeleteRequested: (uuid) => {
                    todoModel.removeTask(uuid)
                }
            }
        }
    }
}