import QtQuick
import QtCore

ListModel {
    id: root
    property int doneCount: 0
    property int totalCount: count
    property int todoCount: totalCount - doneCount
    signal filterChanged(string filter)
    // example data
    // ListElement {uuid: "uuid", desc: "desc", done: false}
    function createUUID() {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
            var r = Math.random() * 16 | 0,
                v = c === 'x' ? r : (r & 0x3 | 0x8);
            return v.toString(16);
        });
    }
    function addTask(desc) {
        append({
                uuid: root.createUUID(),
                desc: desc,
                done: false
            })
    }
    function removeTask(uuid) {
        for (let i = 0; i < count; i++) {
            if (get(i).uuid === uuid) {
                remove(i)
            }
        }
        updateCount()
    }

    function updateCount() {
        resetCount()
        for (let i = 0; i < count; i++) {
            if (get(i).done) {
                doneCount++
            }
        }
    }

    function resetCount() {
        doneCount = 0
    }

    function setDone(uuid, done) {
        for (let i = 0; i < count; i++) {
            if (get(i).uuid === uuid) {
                get(i).done = done
            }
        }
        updateCount()
    }

    function setFilter(filter) {
        root.filterChanged(filter)
    }
}