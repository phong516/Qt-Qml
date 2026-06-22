import QtQuick
import Todo

ListView {
    id: root
    required property ListModel listmodel
    DelegateModel {
        id: visualModel
        model: root.listmodel
        groups: [
            DelegateModelGroup {
                name: "done"
            }
            DelegateModelGroup {
                name: "todo"
            }
        ]
    }
    function setFilter(filter) {
        if (filter === "all") {
            return visualModel.parts.items
        }
        else if (filter === "done") {
            return visualModel.parts.done
        }
        else if (filter === "todo") {
            return visualModel.parts.todo
        }
    }
}