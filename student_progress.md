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
  - Practice custom roles and advanced filtering
  - Extend C++ model with sorting capabilities
  - Add a persistence layer behind an abstract storage interface

### Current Task
- **Task:** Task 007 — Persistence Layer (In Progress)
- **Goal:** Add data persistence behind an abstract storage interface so the todo list survives app restarts. JSON file is the first concrete backend; a database backend can be dropped in later without touching the model or UI.
- **Status:** In Progress — abstract `TodoStorage` interface + `JsonTodoStorage` implementation designed; wiring into `TodoManager` planned

### Task 007 — Persistence Layer
- **Status:** In Progress
- **Goal:** Persist tasks across app restarts via a swappable storage backend
- **Design:**
  - `TodoStorage` (abstract base, `QObject`): defines `load(QList<Task_t>&)` and `save(const QList<Task_t>&)` — the WHAT, not the HOW
  - `JsonTodoStorage` (concrete): serializes to a single `.json` file via `QJsonDocument` + `QSaveFile`
  - `TodoManager` holds a `TodoStorage*`; calls `load()` on startup, `save()`/`persist()` after every mutation
  - Future `SqlTodoStorage` can implement the same interface — no model/UI changes needed
- **Learning Targets:**
  - Separate persistence from business logic via an interface (Dependency Inversion)
  - Use `QJsonDocument` / `QJsonArray` / `QJsonObject` for serialization
  - Use `QSaveFile` for atomic writes (no corrupt file on crash)
  - Use `QStandardPaths::AppDataLocation` for a portable data path
  - Wire load-on-start / save-on-change in the manager

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

### Task 006 — C++ Backend Integration
- **Status:** Completed
- **Score:**
  - **C++ Architecture:** 9/10
  - **QML-C++ Binding:** 9/10
  - **Model Implementation:** 10/10
  - **Proxy Pattern:** 9/10
- **Goal:** Integrate C++ `TodoManager` as backend model for QML
- **Completed Learning Targets:**
  - ✓ Expose C++ `QAbstractListModel` to QML via `QML_NAMED_ELEMENT`
  - ✓ Use `qt_add_qml_module` for C++ plugin registration in Backend module
  - ✓ Replace QML `ListModel` with C++ `TodoModel` + `TodoFilter` proxy
  - ✓ Understand QML-C++ data binding through context properties
- **Implementation Details:**
  - `TodoModel` (C++) implements `QAbstractListModel` with role-based data access
  - `TodoFilter` (C++) extends `QSortFilterProxyModel` for filtering logic
  - `TodoManager` (C++) exposes counted properties and invokable methods to QML
  - `main.cpp` wires manager → model → filter → QML context property
  - QML ListView binds to `manager.proxyModel` (filtered C++ model)
  - Delegate accesses role names: `uuid`, `desc`, `done` from C++ model
- **Key Insights:**
  - Using proxy pattern separates filtering from data — single model, multiple views possible
  - C++ model scales better than QML ListModel for 1000+ items
  - Role-based data access allows safe refactoring without breaking UI bindings
  - Context properties expose objects to QML root — alternative to QML modules for managers
