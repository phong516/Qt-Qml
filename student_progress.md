### Student Progress
- **Current Level:** Intermediate
- **Current Task:** None (Task 005 completed)
- **Skills Practiced:**
  - Using `Column` for vertical layout
  - Understanding `anchors` and `spacing`
  - Using `implicitHeight` for dynamic sizing
  - QML module system (`qmldir`, CMake plugin targets)
  - `DelegateModel` and `DelegateModelGroup` for list filtering
  - Signal chains across multiple components
  - `ListModel.setProperty()` for safe model mutation
  - UUID generation in QML/JS
- **Challenges Faced:**
  - Adjusting `Column` margins inside a parent `Rectangle`
  - Avoiding manual height calculations
  - `onFilterChanged` arrow function not receiving parameter (QML property-change signals don't pass value)
  - `get(i).done = done` silently failing — `ListModel` requires `setProperty()`
  - Understanding `DelegateDataObject` structure (`.model`, `.inDone`, `.inTodo`)
- **Next Steps:**
  - Explore animations and transitions
  - Practice C++ `QAbstractListModel` integration

### Current Task
- **Task:** Task 006 — C++ Backend Integration (Pending)
- **Goal:** Integrate C++ `TodoManager` as backend model for QML

### Task 001 — Traffic Light
- **Status:** Completed
- **Score:**
  - **Visual Accuracy:** 9/10
  - **Layout Logic:** 8/10
  - **Anchor Understanding:** 7/10
  - **Cleanliness:** 8/10
- **Feedback:**
  - Successfully implemented a vertical traffic light layout.
  - Minor issues with `anchors.margins` understanding, but resolved.
  - Good use of `Column` and `spacing`.
- **Next Steps:**
  - Practice dynamic layouts with `Repeater`.

### Task 002 — Profile Card
- **Status:** Completed
- **Score:**
  - **Visual Accuracy:** 9/10
  - **Layout Logic:** 8/10
  - **Anchor Understanding:** 8/10
  - **Cleanliness:** 8/10
- **Feedback:**
  - Profile card layout is visually correct and dynamic height is implemented.
  - Minor issues with `implicitHeight` handling initially, but resolved.
  - Good use of `Image` and `Text` components.
- **Next Steps:**
  - Practice more dynamic layouts with `ListView` or `Repeater`.
  - Explore advanced styling and animations.

### Task 003 — Calculator Layout
- **Status:** Completed
- **Score:**
  - **Visual Accuracy:** 10/10
  - **Layout Logic:** 9/10
  - **Anchor Understanding:** 9/10
  - **Cleanliness:** 9/10
- **Feedback:**
  - Excellent use of `GridLayout` for arranging buttons in a grid.
  - Dynamic layout with proper use of `Layout.fillHeight` and `Layout.fillWidth`.
  - Minor improvements can be made in spacing and alignment for better aesthetics.
- **Next Steps:**
  - Explore `ListView` for dynamic data-driven layouts.
  - Practice adding interactivity to the calculator (e.g., button click handling).

### Task 004 — Todo List with ListView (Monolithic)
- **Status:** Completed
- **Feedback:**
  - Successfully built a dynamic todo list using `ListView` and `ListModel`.
  - Correct use of `delegate` for item rendering.
  - Foundation for the modular refactor in Task 005.

### Task 005 — Modular Todo App
- **Status:** Completed
- **Components Built:** `Model/TodoModel.qml`, `UI/TodoDelegate.qml`, `UI/TodoInput.qml`, `UI/TodoListView.qml`, `UI/TodoCount.qml`
- **Score:**
  - **Architecture:** 9/10
  - **Signal Design:** 9/10
  - **Filtering Logic:** 10/10
  - **Cleanliness:** 9/10
  - **Modularity/Reusability:** 10/10
- **Feedback:**
  - Clean component decomposition with well-defined signals and required properties.
  - Excellent use of `DelegateModel` + `DelegateModelGroup` for all/done/todo filtering.
  - Two bugs caught and fixed: QML property-change signal parameter misuse, and `ListModel` direct mutation.
  - UUID-based task identity is a solid design choice.
  - **Module separation completed:** TodoModel moved to Model module, UI components moved to UI module for better reusability.

### Task 006 — C++ Backend Integration (Pending)
- **Status:** Not Started
- **Goal:** Integrate C++ `TodoManager` as backend model for QML
- **Learning Target:** 
  - Expose C++ `QAbstractListModel` to QML
  - Use `qt_add_qml_module` for C++ plugin registration
  - Replace QML `ListModel` with C++ model
  - Understand QML-C++ data binding
