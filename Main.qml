import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Todo

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: "ToDo App"

    TodoModel {
        id: todoModel
    }

    ColumnLayout {
        anchors.fill: parent
        TodoInput {
            onTaskSubmitted: {
                todoModel.addTask(text)
            }
        }
        TodoListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: todoModel
            delegate: TodoDelegate {
                uuid: model.uuid
                desc: model.desc
                onDeleteRequested: {
                    todoModel.removeTask(uuid)
                }
            }
        }
    }
}