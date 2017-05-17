
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: mainWindow_
    visible: true
    width: 500
    height: 300
    title: qsTr("Bookshelf")
    color: "snow"



    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "New"
                onTriggered: bookshelf.clearAll()
            }
            MenuItem {
                text: "Open"
                onTriggered: {
                    fileDialog.title = "Load file"
                    fileDialog.selectExisting = true
                    fileDialog.visible = true
                }
            }
            MenuItem {
                text: "Save"
                onTriggered: {
                    fileDialog.title = "Save file"
                    fileDialog.selectExisting = false
                    fileDialog.visible = true
                }
            }
            MenuItem {
                text: "Exit"
                onTriggered: mainWindow_.close()
            }
        }
        Menu {
            title: "Book"
            MenuItem {
                text: "Add"
                onTriggered: editField.visible = true
            }
            MenuItem {
                text: "Remove"
                onTriggered: bookshelf.removeBook(tableView_.currentRow)
            }
        }
        Menu {
            title: "Sort"
            MenuItem {
                text: "Sort by name"
                onTriggered: bookshelf.changeSortType(0)
            }
            MenuItem {
                text: "Sort by author"
                onTriggered: bookshelf.changeSortType(1)
            }
            MenuItem {
                text: "Sort by genre"
                onTriggered: bookshelf.changeSortType(2)
            }
            MenuItem {
                text: "Sort by date"
                onTriggered: bookshelf.changeSortType(3)
            }
            MenuItem {
                text: "Reverse sort"
                onTriggered: bookshelf.changeSortType(4)
            }
        }
        Menu {
            title: "About"
            MenuItem {
                text: "Nothing..."
                onTriggered: about.visible = true
            }
        }
    }



    FileDialog {
        id: fileDialog
        visible: false
        folder: shortcuts.documents
        nameFilters: [ "Text files (*.dat)" ]
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            if (fileDialog.selectExisting)
            {
                bookshelf.load(fileDialog.fileUrl)
            }
            else
            {
                bookshelf.save(fileDialog.fileUrl)
            }
            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            Qt.quit()
        }
    }



    TableView {
            id: tableView_
            anchors.fill: parent
            model: mBooks


            // Table header.
            headerDelegate:Rectangle {
                height: 20
                anchors.topMargin: -10
                anchors.rightMargin: -5

                implicitWidth: 20
                radius: 1
                border.color: "gray"
                gradient: Gradient {
                    GradientStop { position: 0.1; color: "snow" }
                    GradientStop { position: 0.4; color: "lightgray" }
                    GradientStop { position: 1.0; color: "gray" }
                }

                Text {
                    id: textItem
                    text: styleData.value
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: styleData.textAlignment
                    elide: Text.ElideRight
                    renderType: Text.NativeRendering
                    anchors { fill: parent; leftMargin: 7; }
                    font.pointSize: 8
                }

                Connections {
                    target: styleData
                    onPressedChanged: {
                        bookshelf.changeSortType(styleData.column)
                    }
                }
            }

            itemDelegate: Item {
                Text {
                    text: styleData.value
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: styleData.textAlignment
                    elide: Text.ElideRight
                    renderType: Text.NativeRendering
                    anchors { fill: parent; leftMargin: 7; }
                    font.pointSize: 8
                }
            }

            TableViewColumn {
                role: "bName"
                title: "Name"
                width: 200
            }

            TableViewColumn {
                role: "bAuthor"
                title: "Author"
                width: 100
            }

            TableViewColumn {
                role: "bGenre"
                title: "Genre"
                width: 100
            }

            TableViewColumn {
                role: "bDate"
                title: "Date"
                width: 60
            }
        }



    Window {
            id: editField
            width: 300
            height: 230
            visible: false
            title: "Edit"

            Rectangle {
                anchors.fill: parent

                // Input data.
                Text {
                    id: inpNameText
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    text: "Name"
                }

                Rectangle {
                    id: inpNameField
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpNameText.bottom
                    width: parent.width - 40
                    height: 30

                    TextField {
                        id: nameField
                        anchors.fill: parent
                    }
                }

                Text {
                    id: inpAuthorText
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpNameField.bottom
                    text: "Author"
                }

                Rectangle {
                    id: inpAuthorField
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpAuthorText.bottom
                    width: parent.width - 40
                    height: 30

                    TextField {
                        id: authorField
                        anchors.fill: parent
                    }
                }

                Text {
                    id: inpGenreText
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpAuthorField.bottom
                    text: "Genre"
                }

                Rectangle {
                    id: inpGenreField
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpGenreText.bottom
                    width: parent.width - 40
                    height: 30

                    TextField {
                        id: genreField
                        anchors.fill: parent
                    }
                }

                Text {
                    id: inpDateText
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpGenreField.bottom
                    text: "Date"
                }

                Rectangle {
                    id: inpDateField
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: inpDateText.bottom
                    width: parent.width - 40
                    height: 30

                    TextField {
                        id: dateField
                        anchors.fill: parent
                    }
                }


                // Buttons.
                Row {
                    id: editFieldButtons
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 10

                    Button {
                        text: "Add"
                        onClicked: {
                            bookshelf.addBookFromQml(nameField.text,
                                          authorField.text,
                                          genreField.text,
                                          dateField.text)
                            nameField.text = ""
                            authorField.text = ""
                            genreField.text = ""
                            dateField.text = ""
                            editField.visible = false
                        }
                    }

                    Button {
                        text: "Cancel"
                        onClicked: {
                            nameField.text = ""
                            authorField.text = ""
                            genreField.text = ""
                            dateField.text = ""
                            editField.visible = false
                        }
                    }
                }
            }
        }



    Window {
            id: about
            width: 150
            height: 150
            visible: false
            title: "Edit"

            Rectangle {
                anchors.centerIn: parent
                width: parent.width / 3 * 2
                height: parent.height / 3 * 2

                gradient: Gradient {
                    GradientStop {
                        id: color1
                        position: 0.00;
                        color: Qt.rgba(Math.random(),
                                       Math.random(),
                                       Math.random(), 1);
                    }
                    GradientStop {
                        id: color2
                        position: 0.55;
                        color: Qt.rgba(Math.random(),
                                       Math.random(),
                                       Math.random(),
                                       1);
                    }
                    GradientStop {
                        id: color3
                        position: 1.00;
                        color: Qt.rgba(Math.random(),
                                       Math.random(),
                                       Math.random(),
                                       1);
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        color1.color = Qt.rgba(Math.random(),
                                               Math.random(),
                                               Math.random(),
                                               1);
                        color2.color = Qt.rgba(Math.random(),
                                               Math.random(),
                                               Math.random(),
                                               1);
                        color3.color = Qt.rgba(Math.random(),
                                               Math.random(),
                                               Math.random(),
                                               1);
                    }
                }
            }
    }
}
