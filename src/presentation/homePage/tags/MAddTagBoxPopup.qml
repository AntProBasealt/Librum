import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import CustomComponents 1.0
import QtQml.Models 2.15
import Librum.style 1.0
import Librum.icons 1.0
import Librum.controllers 1.0


Popup
{
    id: root
    property string currentlySelectedData
    signal itemSelected()
    
    onOpened: listView.currentIndex = -1
    onAboutToHide:
    {
        // Make sure to stop renaming (if something is currently being renamed) when closing
        let currentItem = listView.itemAtIndex(rightClickMenu.index);
        if(currentItem !== null && currentItem.renameable)
        {
            currentItem.stopRenaming(false);
        }
        
        rightClickMenu.close()
    }
    
    implicitWidth: 200
    padding: 8
    focus: true
    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
    background: Rectangle
    {
        color: Style.colorBackground
        border.width: 1
        border.color: Style.colorLightBorder
        radius: 4
        antialiasing: true
    }
    
    ColumnLayout
    {
        id: mainLayout
        width: parent.width
        
        
        ListView
        {
            id: listView            
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            Layout.maximumHeight: 208
            maximumFlickVelocity: 550
            keyNavigationEnabled: true
            currentIndex: -1
            clip: true
            focus: true
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { }
            
            model: UserController.tagsModel
            
            delegate: MBaseListItem
            {
                width: listView.width
                height: 32
                containingListview: listView
                fontSize: 11.5
                fontColor: Style.colorLightText3
                checkBoxStyle: false
                
                function getContent()
                {
                    return model.name;
                }
                
                onClicked: (mouse, index) => listView.selectItem(index)
                
                onRightClicked:
                    (mouse, index) =>
                    {
                        // Stop editing for previous item
                        let currItem = listView.itemAtIndex(rightClickMenu.index);
                        if(currItem.renameable)
                        {
                            currItem.stopRenaming();
                        }
                        
                        let absoluteMousePosition = mapToItem(mainLayout, mouse.x, mouse.y);
                        
                        rightClickMenu.x = absoluteMousePosition.x + 2;
                        rightClickMenu.y = absoluteMousePosition.y + 2;
                        rightClickMenu.index = index;
                        rightClickMenu.open();
                    }
                
                onRenamed: (index, text) =>
                           {
                               let currentItem = listView.itemAtIndex(rightClickMenu.index);
                               let tagName = currentItem.getContent();
                               let uuid = UserController.getTagUuidForName(tagName);
                               
                               let success = UserController.renameTag(uuid, text);
                               if(success)
                               {
                                   let oldText = rightClickMenu.originalTextOfLastEdited;
                                   BookController.renameTags(oldText, text);
                               }
                           }
            }
            
            
            Keys.onReturnPressed:
            {
                if(listView.currentIndex !== -1)
                    selectItem(listView.currentIndex);
            }
            
            
            function selectItem(index)
            {
                // Stop the renaming of the currentItem
                if(listView.itemAtIndex(rightClickMenu.index).renameable)
                    listView.itemAtIndex(rightClickMenu.index).stopRenaming();
                
                let newSelected = listView.itemAtIndex(index);
                
                root.currentlySelectedData = newSelected.getContent();
                root.itemSelected();
                root.close();
            }
        }
    }
    
    
    MRightClickMenu
    {
        id: rightClickMenu
        property int index
        property string originalTextOfLastEdited
        
        visible: false
        
        
        objectModel: ObjectModel
        {
            MRightClickMenuItem
            {
                width: rightClickMenu.width
                imagePath: Icons.plusSquare
                imageSize: 17
                text: "Add"
                
                onClicked:
                {
                    listView.selectItem(rightClickMenu.index);
                    rightClickMenu.close();
                }
            }
            
            MRightClickMenuItem
            {
                width: rightClickMenu.width
                imagePath: Icons.editGray
                imageSize: 17
                text: "Rename"
                
                onClicked:
                {
                    let currentItem = listView.itemAtIndex(rightClickMenu.index);
                    rightClickMenu.originalTextOfLastEdited = currentItem.getContent();
                    
                    currentItem.startRenaming();
                    rightClickMenu.close();
                }
            }
            
            MRightClickMenuItem
            {
                width: rightClickMenu.width
                imagePath: Icons.trashGray
                imageSize: 16
                text: "Delete"
                
                onClicked:
                {
                    let tagName = listView.itemAtIndex(rightClickMenu.index).getContent();
                    let uuid = UserController.getTagUuidForName(tagName);
                    
                    let success = UserController.removeTag(uuid);
                    if(success)
                    {
                        BookController.deleteAllTagsWithUuid(uuid);
                    }
                    
                    rightClickMenu.close();
                }
            }
        }
    }
}