import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import CustomComponents 1.0
import Librum.style 1.0
import Librum.icons 1.0


Popup
{
    id: root
    property var saveFunction
    property var discardMethod
    signal decisionMade
    
    implicitWidth: 646
    implicitHeight: layout.height
    padding: 0
    closePolicy: Popup.NoAutoClose
    background: Rectangle { color: "transparent"; radius: 4 }
    modal: true
    Overlay.modal: Rectangle { color: Style.colorPopupDim; opacity: 1 }
    
    
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
                id: backgroundRect
                Layout.fillWidth: true
                topPadding: 86
                horizontalPadding: 62
                bottomPadding: 62
                background: Rectangle { color: Style.colorPopupBackground; radius: 6 }
                
                
                ColumnLayout
                {
                    id: inRectLayout
                    width: parent.width
                    spacing: 22
                    
                    
                    Label
                    {
                        id: whoopsText
                        Layout.alignment: Qt.AlignHCenter
                        Layout.topMargin: 18
                        text: "Whoops"
                        color: Style.colorTitle
                        font.weight: Font.Medium
                        font.pointSize: 42
                    }
                    
                    Label
                    {
                        id: explenation
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        text: "It looks like you forgot to save your changes, are you sure that you dont want to save them?"
                        horizontalAlignment: Qt.AlignHCenter
                        color: Style.colorLightText
                        font.weight: Font.Medium
                        font.pointSize: 15
                    }
                    
                    RowLayout
                    {
                        id: buttonRow
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: acceptButton.height
                        Layout.topMargin: 24
                        spacing: 42
                        
                        
                        MButton
                        {
                            id: acceptButton
                            Layout.preferredWidth: 120
                            Layout.preferredHeight: 40
                            Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                            borderWidth: activeFocus ? 0 : 1
                            backgroundColor: activeFocus ? Style.colorBasePurple : "transparent"
                            opacityOnPressed: 0.7
                            text: "Save"
                            fontSize: 12.75
                            fontWeight: Font.Bold
                            textColor: activeFocus ? Style.colorFocusedButtonText : Style.colorUnfocusedButtonText
                            
                            onClicked: internal.save()
                            
                            KeyNavigation.tab: discardButton
                            KeyNavigation.right: discardButton
                            Keys.onReturnPressed: internal.save()
                        }
                        
                        MButton
                        {
                            id: discardButton
                            Layout.preferredWidth: 120
                            Layout.preferredHeight: 40
                            Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
                            borderWidth: focus ? 0 : 1
                            backgroundColor: focus ? Style.colorBasePurple : "transparent"
                            opacityOnPressed: 0.7
                            text: "Don't save"
                            fontSize: 12.75
                            fontWeight: Font.Bold
                            textColor: focus ? Style.colorFocusedButtonText : Style.colorUnfocusedButtonText
                            
                            onClicked: internal.discard()
                            
                            KeyNavigation.tab: acceptButton
                            KeyNavigation.left: acceptButton
                            Keys.onReturnPressed: internal.discard()
                        }
                    }
                }
            }
        }
    }
    
    QtObject
    {
        id: internal
        
        function save()
        {
            root.saveFunction();
            root.close();
            root.decisionMade();
        }
        
        function discard()
        {
            root.discardMethod();
            root.close();
            root.decisionMade();
        }
    }
    
    
    function giveFocus()
    {
        acceptButton.forceActiveFocus();
    }
}