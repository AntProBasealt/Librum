import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import CustomComponents 1.0
import Librum.style 1.0
import Librum.icons 1.0
import Librum.controllers 1.0


MFlickWrapper
{
    id: root
    contentHeight: page.implicitHeight
    flickDeceleration: 3500
    
    
    Page
    {
        id: page
        width: parent.width
        horizontalPadding: 48
        bottomPadding: 22
        background: Rectangle { anchors.fill: parent; color: Style.colorPageBackground }
        
        
        ColumnLayout
        {
            id: layout
            width: parent.width
            spacing: 0
            
            
            RowLayout
            {
                id: titleRow
                Layout.fillWidth: true
                spacing: 0
                
                
                MTitle
                {
                    id: pageTitle
                    Layout.topMargin: 64
                    titleText: "General settings"
                    descriptionText: "Change the way Librum works"
                    titleSize: 25
                    descriptionSize: 13.25
                }
                
                Item { Layout.fillWidth: true }
                
                MButton
                {
                    id: resetButton
                    Layout.preferredWidth: 160
                    Layout.preferredHeight: 38
                    Layout.alignment: Qt.AlignBottom
                    borderWidth: 0
                    backgroundColor: Style.colorBasePurple
                    text: "Restore Defaults"
                    fontSize: 12
                    fontWeight: Font.Bold
                    textColor: Style.colorFocusedButtonText
                    
                    onClicked: resetSettingsPopup.open()
                }
            }
            
            Pane
            {
                id: downloadBlock
                Layout.fillWidth: true
                Layout.topMargin: 32
                verticalPadding: 24
                horizontalPadding: internal.pagePadding
                background: Rectangle
                {
                    color: Style.colorContainerBackground
                    border.color: Style.colorContainerBorder
                    radius: 4
                    antialiasing: true
                }
                
                
                ColumnLayout
                {
                    id: downloadColumn
                    anchors.fill: parent
                    spacing: 0
                    
                    Label
                    {
                        id: downloadTitle
                        Layout.fillWidth: true
                        text: "Books"
                        font.pointSize: 17
                        font.weight: Font.DemiBold
                        color: Style.colorText
                    }
                    
                    
                    Label
                    {
                        id: openBookAfterCreationTitle
                        Layout.fillWidth: true
                        Layout.topMargin: 24
                        text: "Open books after creation"
                        font.pointSize: 13
                        font.weight: Font.DemiBold
                        color: Style.colorText
                    }
                    
                    MOnOffToggle
                    {
                        id: openBookAfterCreationToggle
                        property string savedValue: SettingsController.generalSettings.OpenBooksAfterCreation
                        
                        Layout.topMargin: 4
                        onByDefault: savedValue === onText
                        
                        // Need rebinding on reset
                        onSavedValueChanged: savedValue == onText ? setOn() : setOff()
                        onToggled: (value) => internal.saveSetting(SettingKeys.OpenBooksAfterCreation, value)
                    }
                }
            }
        }
    }
    
    MResetSettingsPopup
    {
        id: resetSettingsPopup
        x: Math.round(root.width / 2 - implicitWidth / 2 - settingsSidebar.width / 2 - page.horizontalPadding)
        y: Math.round(root.height / 2 - implicitHeight / 2 - page.topPadding - 50)
        
        onKeepChoosed: close()
        onResetChoosed:
        {
            SettingsController.resetSettingGroup(SettingGroups.General);
            close();
        }
    }
    
    QtObject
    {
        id: internal
        property int pagePadding : 40
        
        
        /*
          Higher order functions to simplify the call on the SettingsController
          */
        function saveSetting(key, value)
        {
            SettingsController.setSetting(key, value, SettingGroups.General);
        }
    }
}