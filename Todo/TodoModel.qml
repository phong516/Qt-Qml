import QtQuick
import QtCore

ListModel {
    id: root
    property int doneCount: 0
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
    }

    function update() {
        doneCount = 0
        for (let i = 0; i < count; i++) {
            if (get(i).done) {
                doneCount++
            }
        }
    }

    function toggleDone(uuid) {
        for (let i = 0; i < count; i++) {
            if (get(i).uuid === uuid) {
                get(i).done = !get(i).done
            }
        }
    }

    function setFilter(filter) {
        root.filterChanged(filter)
    }
}