import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import UI

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

        Label {
            text: "To Do App"
            Layout.alignment: Qt.AlignHCenter
        }

        TodoCount {
            id: countSection
            Layout.fillWidth: true
            doneCount: todoModel.doneCount
            totalCount: todoModel.totalCount
            todoCount: todoModel.todoCount
            onFilterChanged: todoModel.setFilter(countSection.filter)
        }

        TodoInput {
            Layout.fillWidth: true
            onTaskSubmitted: (text) => {
                todoModel.addTask(text)
            }
        }
        TodoListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.bottomMargin: 10
            model: todoModel
            delegate: Component {
                TodoDelegate {
                    width: ListView.view.width
                    onDeleteRequested: (uuid) => {
                        todoModel.removeTask(uuid)
                    }
                    onCheckedChanged: (uuid, checked) => {
                        todoModel.setDone(uuid, checked)
                    }
                }
            }
        }
    }
}