import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import CustomComponents 1.0
import Librum.style 1.0
import Librum.icons 1.0


Popup
{
    id: root
    signal decisionMade
    signal resetChoosed
    signal keepChoosed
    
    implicitWidth: 646
    implicitHeight: layout.height
    padding: 0
    modal: true
    background: Rectangle { color: "transparent"; radius: 4 }
    Overlay.modal: Rectangle { color: Style.colorPopupDim; opacity: 1 }
    
    onOpened: keepButton.forceActiveFocus()
    
    
    MFlickWrapper
    {
        id: flickWrapper
        anchors.fill: parent
        contentHeight: layout.height
        
        
        ColumnLayout
        {
            id: layout
            width: parent.width
            spacing: -92
            
            
            Image
            {
                id: attentionIllustration
                z: 2
                Layout.alignment: Qt.AlignHCenter
                Layout.rightMargin: 10
                source: Icons.attentionPurple
                sourceSize.width: 250
                fillMode: Image.PreserveAspectFit
            }
            
            Pane
            {
                id: container
                Layout.fillWidth: true
                topPadding: 86
                horizontalPadding: 82
                bottomPadding: 66
                background: Rectangle { color: Style.colorPopupBackground; radius: 6 }
                
                
                ColumnLayout
                {
                    id: contentLayout
                    width: parent.width
                    spacing: 22
                    
                    
                    Label
                    {
                        id: whoopsText
                        Layout.alignment: Qt.AlignHCenter
                        Layout.topMargin: 18
                        text: "Reset settings?"
                        color: Style.colorTitle
                        font.weight: Font.Medium
                        font.pointSize: 42
                    }
                    
                    Label
                    {
                        id: permanentActionText
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        text: "Resetting your settings is a permanent action, there will be no way to restore them!"
                        horizontalAlignment: Qt.AlignHCenter
                        color: Style.colorLightText
                        font.weight: Font.Medium
                        font.pointSize: 15
                    }
                    
                    RowLayout
                    {
                        id: buttonRow
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: keepButton.height
                        Layout.topMargin: 36
                        spacing: 42
                        
                        MButton
                        {
                            id: keepButton
                            Layout.preferredWidth: 180
                            Layout.preferredHeight: 40
                            Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                            borderWidth: activeFocus ? 0 : 1
                            backgroundColor: activeFocus ? Style.colorBasePurple : "transparent"
                            opacityOnPressed: 0.7
                            text: "No, Keep"
                            fontSize: 12.75
                            fontWeight: Font.Bold
                            textColor: activeFocus ? Style.colorFocusedButtonText : Style.colorUnfocusedButtonText
                            
                            onClicked: internal.keep()
                            
                            KeyNavigation.tab: resetButton
                            KeyNavigation.right: resetButton
                            Keys.onReturnPressed: internal.keep()
                        }
                        
                        MButton
                        {
                            id: resetButton
                            Layout.preferredWidth: 180
                            Layout.preferredHeight: 40
                            Layout.alignment: Qt.AlignBottom
                            borderWidth: activeFocus ? 0 : 1
                            backgroundColor: activeFocus ? Style.colorRed : "transparent"
                            opacityOnPressed: 0.7
                            text: "Yes, Reset"
                            fontSize: 12.75
                            fontWeight: Font.Bold
                            textColor: activeFocus ? Style.colorFocusedButtonText : Style.colorUnfocusedButtonText
                            
                            onClicked: internal.reset()
                            
                            KeyNavigation.tab: keepButton
                            KeyNavigation.left: keepButton
                            Keys.onReturnPressed: internal.reset()
                        }
                    }
                }
            }
        }
    }
    
    QtObject
    {
        id: internal
        
        
        function reset()
        {
            root.resetChoosed();
            root.decisionMade();
        }
        
        function keep()
        {
            root.keepChoosed();
            root.decisionMade();
        }
    }
    
    function giveFocus()
    {
        acceptButton.forceActiveFocus();
    }
}