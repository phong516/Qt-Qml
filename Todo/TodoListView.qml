import QtQuick
import Todo

Item {
    id: root
    required property ListModel model
    required property Component delegate

    ListView {
        id: listView
        anchors.fill: parent
        model: visualModel

        DelegateModel {
            id: visualModel
            model: root.model
            delegate: root.delegate

            groups: [
                DelegateModelGroup {
                    name: "done"
                    includeByDefault: false
                },
                DelegateModelGroup {
                    name: "todo"
                    includeByDefault: false
                }
            ]

            items.onChanged: root.refreshGroups()
        }
    }

    Connections {
        target: root.model
        function onFilterChanged(filter) {
            root.setFilter(filter)
        }
    }

    function refreshGroups() {
        for (var i = 0; i < visualModel.items.count; i++) {
            var entry = visualModel.items.get(i)
            entry.inDone = entry.model.done
            entry.inTodo = !entry.model.done
        }
    }

    function setFilter(filter) {
        refreshGroups()
        if (filter === "all") {
            visualModel.filterOnGroup = "items"
        } else if (filter === "done") {
            visualModel.filterOnGroup = "done"
        } else if (filter === "todo") {
            visualModel.filterOnGroup = "todo"
        }
    }
}