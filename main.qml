import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 480
    height: 480
    title: 'Scroll'

    ScrollView {
        id: sc
        anchors.fill: parent
//        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        ListView {
            width: parent.width
            model: automaton_model

            delegate: Image {
//                width: parent.width
//                height: 40
                source: model.display
                smooth: false
            }
            transform: Scale { xScale: 4; yScale: 4 }
        }
    }
}
