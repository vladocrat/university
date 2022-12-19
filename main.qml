import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12
import User 1.0
import UserRepository 1.0
import AccessRightsRepository 1.0
import GroupRepository 1.0
import ContractTypeRepository 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Students Management System")

    QtObject {
        id: internal

        function openChildWindow(windowName) {
            var child = Qt.createComponent(windowName);
            var window = child.createObject(root);
            window.show();
        }
    }

    Rectangle {
        id: topbar

        anchors.top: parent.top
        width: parent.width
        height: parent.height * 0.1
        color: "grey"

        RowLayout {
            anchors.fill: parent
            spacing: 1

            Text {
                Layout.alignment : Qt.AlignRight
                text: User.role
            }

            Item {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: 1
            }
        }
    }

    Rectangle {
        id: mainMenu

        anchors.top: topbar.bottom
        height: root.height
        width: root.width / 5
        color: "red"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            MenuButton {
                id: btn

                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "student"

                onClicked: {
                    if (studentMenu.visible === true) {
                        studentMenu.visible = false;
                    } else {
                        studentMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "contract"

                onClicked: {
                    if (contractMenu.visible === true) {
                        contractMenu.visible = false;
                    } else {
                        contractMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "gap year"

                onClicked: {
                    if (gapYearMenu.visible === true) {
                        gapYearMenu.visible = false;
                    } else {
                        gapYearMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "users"

                onClicked: {
                    if (userMenu.visible === true) {
                        userMenu.visible = false;
                    } else {
                        userMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "access rights"

                onClicked: {
                    if (accessRightsMenu.visible === true) {
                        accessRightsMenu.visible = false;
                    } else {
                        accessRightsMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "group"

                onClicked: {
                    if (groupMenu.visible === true) {
                        groupMenu.visible = false;
                    } else {
                        groupMenu.visible = true;
                    }
                }
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 40
                Layout.fillWidth: true
                pressColor: "red"
                btnText: "contract type"

                onClicked: {
                    if (contractTypeMenu.visible === true) {
                        contractTypeMenu.visible = false;
                    } else {
                        contractTypeMenu.visible = true;
                    }
                }
            }

            Item {
                Layout.preferredHeight: parent.height - btn.height
                Layout.preferredWidth: 1
            }
        }
    }

    ActionsMenu {
        id: studentMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5
    }

    ActionsMenu {
        id: contractMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5
    }

    ActionsMenu {
        id: gapYearMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5
    }

    ActionsMenu {
        id: userMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5

        onGetAllClicked: {
            UserRepository.getAll();
            usersResultList.visible = true;
        }

        onInsertClicked: {
            insertPopup.open();
        }

        onDeleteClicked: {
            deletePopup.open();
        }

        onUpdateClicked: {
            updatePopup.open();
        }
    }

    ActionsMenu {
        id: accessRightsMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5

        onGetAllClicked: {
            AccessRightsRepository.getAll();
            accessRighsResultList.visible = true;
        }

        onInsertClicked: {
            insertPopup.open();
        }

        onDeleteClicked: {
            AccessRightsRepository.getAll();
            deletePopup.open();
        }

        onUpdateClicked: {
            AccessRightsRepository.getAll();
            updatePopup.open();
        }
    }

    ActionsMenu {
        id: groupMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5

        onGetAllClicked: {
            GroupRepository.getAll();
            groupResultList.visible = true;
        }

        onInsertClicked: {
            insertPopup.open();
        }

        onDeleteClicked: {
            GroupRepository.getAll();
            deletePopup.open();
        }

        onUpdateClicked: {
            GroupRepository.getAll();
            updatePopup.open();
        }
    }

    ActionsMenu {
        id: contractTypeMenu

        anchors.top: topbar.bottom
        anchors.left: mainMenu.right
        height: root.height
        width: root.width / 5

        onGetAllClicked: {
            ContractTypeRepository.getAll();
            contractTypeResultList.visible = true;
        }

        onInsertClicked: {
            insertPopup.open();
        }

        onDeleteClicked: {
            ContractTypeRepository.getAll();
            deletePopup.open();
        }

        onUpdateClicked: {
            ContractTypeRepository.getAll();
            updatePopup.open();
        }
    }

    ListView {
        id: accessRighsResultList
        anchors.left: studentMenu.right
        anchors.top: topbar.bottom
        width: root.width - mainMenu.width - studentMenu.width
        height: root.height
        visible: false
        clip: true
        model: accessRightsModel

        delegate: Rectangle {
            height: 50
            width: parent.width
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                spacing: 2

                EntityCell {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Name: " + model.name
                }
            }
        }
    }

    ListView {
        id: usersResultList
        anchors.left: studentMenu.right
        anchors.top: topbar.bottom
        width: root.width - mainMenu.width - studentMenu.width
        height: root.height
        visible: false
        clip: true
        model: usersModel

        delegate: Rectangle {
            height: 50
            width: parent.width
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                spacing: 2

                EntityCell {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Role: " + model.role
                }

                EntityCell {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Login: " + model.login
                }

                EntityCell {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Email: " + model.email
                }
            }
        }
    }

    ListView {
        id: groupResultList
        anchors.left: studentMenu.right
        anchors.top: topbar.bottom
        width: root.width - mainMenu.width - studentMenu.width
        height: root.height
        visible: false
        clip: true
        model: groupModel

        delegate: Rectangle {
            height: 50
            width: parent.width
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                spacing: 2

                EntityCell {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Name: " + model.name
                }
            }
        }
    }

    ListView {
        id: contractTypeResultList
        anchors.left: studentMenu.right
        anchors.top: topbar.bottom
        width: root.width - mainMenu.width - studentMenu.width
        height: root.height
        visible: false
        clip: true
        model: contractTypeModel

        delegate: Rectangle {
            height: 50
            width: parent.width
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                spacing: 2

                EntityCell {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text: "Name: " + model.name
                }
            }
        }
    }


    Popup {
        id: insertPopup

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {
            anchors.fill: parent

            ComboBox {
                id: insertFormChoice

                Layout.alignment: Qt.AlignCenter
                model: ["", "student", "contract", "gap year", "user", "role", "group", "contract type"]
            }

            ColumnLayout {
                id: studentInsert

                visible: insertFormChoice.currentIndex === 1
            }

            ColumnLayout {
                id: contractInsert

                visible: insertFormChoice.currentIndex === 2
            }

            ColumnLayout {
                id: gapyearInsert

                visible: insertFormChoice.currentIndex === 3
            }


            ColumnLayout {
                id: userInsert

                Layout.alignment: Qt.AlignCenter
                visible: insertFormChoice.currentIndex === 4

                Text {
                    Layout.alignment: Qt.AlignCenter
                    text: "INSERT USER"
                }

                TextField {
                    id: userLogin

                    Layout.alignment: Qt.AlignCenter
                    placeholderText: "login"
                }

                TextField {
                    id: userEmail

                    Layout.alignment: Qt.AlignCenter
                    placeholderText: "email"
                }

                TextField {
                    id: userPassword

                    Layout.alignment: Qt.AlignCenter
                    placeholderText: "password"
                }

                ComboBox {
                    id: userRole

                    Layout.alignment: Qt.AlignCenter
                    model: ["", "admin", "mro", "accountant"]
                }

                MenuButton {
                    Layout.alignment: Qt.AlignCenter
                    onClicked: {
                        if (UserRepository.insert(userLogin.text,
                                                  userEmail.text,
                                                  userRole.currentIndex,
                                                  userPassword.text)) {
                        }
                    }
                }
            }

            ColumnLayout {
                id: roleInsert

                Layout.alignment: Qt.AlignCenter
                visible: insertFormChoice.currentIndex === 5

                Text {
                    Layout.alignment: Qt.AlignCenter
                    text: "INSERT ROLE"
                }

                TextField {
                    id: name
                    placeholderText: "role name";
                }

                MenuButton {
                    onClicked: {
                        if (AccessRightsRepository.insert(name.text)) {

                        }
                    }
                }
            }

            ColumnLayout {
                id: groupInsert

                Layout.alignment: Qt.AlignCenter
                visible: insertFormChoice.currentIndex === 6

                Text {
                    Layout.alignment: Qt.AlignCenter
                    text: "INSERT GROUP"
                }

                TextField {
                    id: groupName
                    placeholderText: "group name";
                }

                MenuButton {
                    onClicked: {
                        if (GroupRepository.insert(groupName.text)) {

                        }
                    }
                }
            }

            ColumnLayout {
                id: contractTypeInsert

                Layout.alignment: Qt.AlignCenter
                visible: insertFormChoice.currentIndex === 7

                Text {
                    Layout.alignment: Qt.AlignCenter
                    text: "INSERT CONTRACT TYPES"
                }

                TextField {
                    id: contractTypeName
                    placeholderText: "contract type name";
                }

                MenuButton {
                    onClicked: {
                        if (ContractTypeRepository.insert(contractTypeName.text)) {

                        }
                    }
                }
            }
        }
    }

    Popup {
        id: deletePopup

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {
            anchors.fill: parent

            Text {
                Layout.alignment: Qt.AlignCenter
                text: "DELETE"
                font.pointSize: 12
            }

            ComboBox {
                id: deleteFormChoice

                Layout.alignment: Qt.AlignCenter
                model: ["", "student", "contract", "gap year", "user", "role", "group", "contract type"]

                onCurrentIndexChanged: {
                    if (deleteFormChoice.currentIndex === 4) {
                        getAllUsers.visible = true;
                    }

                    if (deleteFormChoice.currentIndex === 5) {
                        getAllAccessRights.visible = true;
                    }

                    if (deleteFormChoice.currentIndex === 6) {
                        getAllGroups.visible = true;
                    }

                    if (deleteFormChoice.currentIndex === 7) {
                        getAllContractTypes.visible = true;
                    }
                }
            }

            ColumnLayout {
                Layout.preferredHeight: parent.height - deleteFormChoice.height - 30
                Layout.preferredWidth: parent.width  - 30
                Layout.alignment: Qt.AlignCenter


                ListView {
                    id: getAllUsers

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: usersModel

                    onVisibleChanged: {
                        UserRepository.getAll();
                    }

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                console.log(index);
                                if (UserRepository.deleteOne(index)) {
                                    UserRepository.getAll();
                                }
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Role: " + model.role
                            }

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Login: " + model.login
                            }

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Email: " + model.email
                            }
                        }
                    }
                }

                ListView {
                    id: getAllAccessRights

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: accessRightsModel

                    onVisibleChanged: {
                        AccessRightsRepository.getAll();
                    }

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                if (AccessRightsRepository.deleteOne(index)) {

                                }
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Role: " + model.name
                            }
                        }
                    }
                }

                ListView {
                    id: getAllGroups

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: groupModel

                    onVisibleChanged: {
                        GroupRepository.getAll();
                    }

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                if (GroupRepository.deleteOne(index)) {

                                }
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Name: " + model.name
                            }
                        }
                    }
                }

                ListView {
                    id: getAllContractTypes

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: contractTypeModel

                    onVisibleChanged: {
                        ContractTypeRepository.getAll();
                    }

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                if (ContractTypeRepository.deleteOne(index)) {

                                }
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Name: " + model.name
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: updatePopup

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {
            anchors.fill: parent

            Text {
                Layout.alignment: Qt.AlignCenter
                text: "Update"
                font.pointSize: 12
            }

            ComboBox {
                id: updateFormChoice

                Layout.alignment: Qt.AlignCenter
                model: ["", "student", "contract", "gap year", "user", "role", "group", "contract type"]

                onCurrentIndexChanged: {
                    if (updateFormChoice.currentIndex === 4) {
                        updateGetAllUsers.visible = true;
                    }

                    if (updateFormChoice.currentIndex === 5) {
                        updateGetAllAccessRights.visible = true;
                    }

                    if (updateFormChoice.currentIndex === 6) {
                        updateGetAllGroups.visible = true;
                    }

                    if (updateFormChoice.currentIndex === 7) {
                        updateGetAllContractTypes.visible = true;
                    }
                }
            }

            ColumnLayout {
                Layout.preferredHeight: parent.height - updateFormChoice.height - 30
                Layout.preferredWidth: parent.width  - 30
                Layout.alignment: Qt.AlignCenter

                ListView {
                    id: updateGetAllUsers

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: usersModel

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                updatePopup.close();
                                userUpdateForm.open();
                                userUpdateForm.userIx = index;
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Role: " + model.role
                            }

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Login: " + model.login
                            }

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Email: " + model.email
                            }
                        }
                    }
                }

                ListView {
                    id: updateGetAllAccessRights

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: accessRightsModel

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                updatePopup.close();
                                accessRightsUpdateForm.open();
                                accessRightsUpdateForm.userIx = index;
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Name: " + model.name
                            }
                        }
                    }
                }

                ListView {
                    id: updateGetAllGroups

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: groupModel

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                updatePopup.close();
                                groupsUpdateForm.open();
                                groupsUpdateForm.userIx = index;
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Name: " + model.name
                            }
                        }
                    }
                }

                ListView {
                    id: updateGetAllContractTypes

                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width
                    visible: false
                    clip: true
                    model: contractTypeModel

                    delegate: Rectangle {
                        height: 50
                        width: parent.width
                        border.width: 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                updatePopup.close();
                                contractTypeUpdateForm.open();
                                contractTypeUpdateForm.userIx = index;
                            }
                        }

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 2

                            EntityCell {
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                text: "Name: " + model.name
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: userUpdateForm

        property int userIx: -1

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {

            TextField {
                id: userUpdateLogin
                Layout.alignment: Qt.AlignCenter
                placeholderText: "login"
            }

            TextField {
                id: userUpdateEmail
                Layout.alignment: Qt.AlignCenter
                placeholderText: "email"
            }

            TextField {
                id: userUpdatePassword
                Layout.alignment: Qt.AlignCenter
                placeholderText: "password"
            }

            ComboBox {
                id: userUpdateRole
                Layout.alignment: Qt.AlignCenter
                model: ["", "admin", "mro", "accountant"]
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    if (UserRepository.update(userUpdateLogin.text,
                                              userUpdateEmail.text,
                                              userUpdateRole.currentIndex,
                                              userUpdatePassword.text,
                                              userUpdateForm.userIx)) {
                    }
                }
            }
        }
    }

    Popup {
        id: accessRightsUpdateForm

        property int userIx: -1

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {

            TextField {
                id: accessRightsUpdateName
                Layout.alignment: Qt.AlignCenter
                placeholderText: "name"
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    if (AccessRightsRepository.update(accessRightsUpdateName.text,
                                                      accessRightsUpdateForm.userIx)) {
                    }
                }
            }
        }
    }

    Popup {
        id: groupsUpdateForm

        property int userIx: -1

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {

            TextField {
                id: groupUpdateName
                Layout.alignment: Qt.AlignCenter
                placeholderText: "name"
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    if (GroupRepository.update(groupUpdateName.text,
                                               groupsUpdateForm.userIx)) {
                    }
                }
            }
        }
    }

    Popup {
        id: contractTypeUpdateForm

        property int userIx: -1

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: root.width / 2
        height: root.height / 1.3
        focus: true
        modal: true
        closePolicy: Popup.CloseOnEscape;

        contentItem: ColumnLayout {

            TextField {
                id: contractTypeUpdateName
                Layout.alignment: Qt.AlignCenter
                placeholderText: "name"
            }

            MenuButton {
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    if (ContractTypeRepository.update(contractTypeUpdateName.text,
                                              contractTypeUpdateForm.userIx)) {
                    }
                }
            }
        }
    }
}





