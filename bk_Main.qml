import QtQuick
import QtQml
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root
    width: 1080
    height: 720
    visible: true
    title: qsTr("QML Learning")

    // task 1: traffic light
    Rectangle {
        id: trafficBox
        x: 50
        y: 50
        width: 70
        height: trafficLights.implicitHeight + trafficLights.spacing * 2
        border.color: "black"
        border.width: 3
        Component {
            id: trafficLightCircle
            Rectangle {
                width: 50
                height: width
                radius: width
            }
        }
        Column {
            id: trafficLights
            spacing: 10
            anchors.fill: parent
            anchors.margins: 10
            // method 1: create manually
            //Rectangle {
            //   width: 50
            //   height: width
            //   radius: width / 2
            //   color: "red"
            //}
            //Rectangle {
            //   width: 50
            //   height: width
            //   radius: width / 2
            //    color: "yellow"
            //}
            //Rectangle {
            //   width: 50
            //   height: width
            //   radius: width / 2
            //    color: "green"
            //}
            // method 2: use Component
            //Rectangle {
            //    Component.onCompleted: trafficLightCircle.createObject(trafficLights, { "color": "red"})
            //}
            //Rectangle {
            //    Component.onCompleted: trafficLightCircle.createObject(trafficLights, { "color": "yellow"})
            //}
            //Rectangle {
            //    Component.onCompleted: trafficLightCircle.createObject(trafficLights, { "color": "green"})
            //}
            // method 3: use Repeater
            Repeater {
                model: ["red", "yellow", "green"]
                Rectangle {
                    width: 50
                    height: width
                    radius: width / 2
                    color: modelData
                }
            }
        }
    }

    // task 2: profile card
    Rectangle {
        id: profileCard
        anchors.left: trafficBox.right
        anchors.top: trafficBox.top
        anchors.leftMargin: 50
        width: 200
        height: profileColumn.implicitHeight + 20
        border.color: "black"
        border.width: 3
        radius: 3

        Column {
            id: profileColumn
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter // Căn giữa toàn bộ Column
            spacing: 10
            topPadding: 10
            bottomPadding: 10
            Rectangle {
                id: avatar
                anchors.horizontalCenter: parent.horizontalCenter
                width: 100
                height: 100
                Image {
                    anchors.fill: parent
                    source: "/resource/images.jpg"
                    fillMode: Image.PreserveAspectCrop
                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: Rectangle {
                            width: avatar.width
                            height: avatar.height
                            radius: width / 2
                            visible: false
                        }
                    }
                }
            }

            Text {
                id: name
                font.pointSize: 15
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                text: "Some one"
                anchors.horizontalCenter: parent.horizontalCenter // Căn giữa toàn bộ Column
            }
            Text {
                id: desc
                text: "Nothing to worry about hello guys"
                horizontalAlignment: Text.AlignJustify
                font.pointSize: 10
                wrapMode: Text.WordWrap
                anchors.horizontalCenter: parent.horizontalCenter // Căn giữa toàn bộ Column
                width: avatar.width + 20
            }
        }
    }

    // task 3: calculator
    Rectangle {
        id: calculator
        anchors.left: profileCard.right
        anchors.top: profileCard.top
        anchors.leftMargin: 50
        width: 300
        height: 200
        border.color: "black"
        border.width: 3
        radius: 3
        GridLayout {
            anchors.fill: parent
            rows: 4
            columns: 5
            anchors.margins: 10
            Button {
                text: "7"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "8"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "9"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "*"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "/"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "4"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "5"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "6"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "+"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "-"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "1"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "2"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "3"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "="
                Layout.rowSpan: 2
                Layout.columnSpan: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                text: "0"
                Layout.columnSpan: 3
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }

    // task 5: mini todo app
    Rectangle {
        id: todoapp
        anchors.top: profileCard.bottom
        anchors.left: trafficBox.left
        anchors.topMargin: 10
        width: task5Layout.implicitWidth + 2 * 10
        height: Math.min(task5Layout.implicitHeight + 2 * 10, root.height - y - 10)
        property int total: task5ListModel.count
        property int done: task5ListModel.doneCount
        property int todo: total - done
        border.color: "black"
        radius: 5
        ColumnLayout {
            id: task5Layout
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5
            Label {
                text: "Mini Todo App"
                Layout.alignment: Qt.AlignHCenter
            }
            RowLayout {
                Layout.fillWidth: true
                spacing: 10
                TextField {
                    text: "Total: " + todoapp.total
                    readOnly: true
                }
                TextField {
                    text: "Done: " + todoapp.done
                    readOnly: true
                }
                TextField {
                    text: "Todo: " + todoapp.todo
                    readOnly: true
                }
            }
            RowLayout {
                spacing: 10
                Button {
                    text: "All"
                    onClicked: task5ListModel.setFilter("")
                }
                Button {
                    text: "Done"
                    onClicked: task5ListModel.setFilter("done")
                }
                Button {
                    text: "Todo"
                    onClicked: task5ListModel.setFilter("todo")
                }
            }
            ListView {
                Layout.fillWidth: true
                model: task5ListModel
                delegate: task5Component
                spacing: 5
                Layout.preferredHeight: contentHeight
                Layout.fillHeight: true
                ScrollBar.vertical: ScrollBar {}
                highlight: Rectangle {
                    color: "green"
                }
                highlightMoveDuration: 1
                currentIndex: -1
                property int lastCount: 0
                onHeightChanged: {
                    if (!currentItem.visible) {
                        currentIndex = -1;
                    }
                }
            }
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: task5Input
                    Layout.fillWidth: true
                    placeholderText: "Enter new task"
                    onAccepted: task5AddButton.clicked()
                }
                Button {
                    id: task5AddButton
                    text: "Add"
                    Layout.rightMargin: 10
                    onClicked: {
                        if (task5Input.text.length > 0) {
                            task5ListModel.addTask(task5Input.text);
                            task5Input.text = "";
                        }
                    }
                }
            }
            ListModel {
                id: task5ListModel

                property int doneCount: 0
                property string filteredCriteria: ""

                function addTask(desc) {
                    append({
                        desc: desc,
                        done: false
                    });
                }

                function removeTask(index) {
                    if (get(index).done) {
                        doneCount--;
                    }
                    remove(index);
                }

                function toggleDone(index) {
                    const newStatus = !get(index).done;
                    setProperty(index, "done", newStatus);
                    doneCount += newStatus ? 1 : -1;
                }

                function setFilter(criteria) {
                    filteredCriteria = criteria;
                }
            }
            Component {
                id: task5Component
                RowLayout {
                    width: ListView.view ? ListView.view.width : 0
                    required property string desc
                    required property bool done
                    required property int index
                    property var view: ListView.view
                    property bool matchFilter: view.model.filteredCriteria === "" || (view.model.filteredCriteria === "done" && done) || (view.model.filteredCriteria === "todo" && !done)
                    height: matchFilter ? implicitHeight : 0
                    visible: matchFilter ? true : false
                    CheckBox {
                        id: task5Desc
                        Layout.fillWidth: true
                        text: desc
                        onToggled: view.model.toggleDone(index)
                    }
                    Button {
                        text: "Delete"
                        Layout.rightMargin: 20
                        onClicked: {
                            view.model.removeTask(index)
                            if (view.currentIndex > 0)
                            {
                                view.currentIndex--
                            }
                        }
                    }
                    HoverHandler {
                        onHoveredChanged: {
                            if (hovered) {
                                view.currentIndex = index;
                            }
                        }
                    }
                }
            }
        }
    }
}