import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 320
    height: 320
    title: 'Scroll'

    Canvas {
        id: canvas
        anchors.fill: parent
        smooth: false

        property point pos: Qt.point(0, 0)

        onPaint: {
            var ctx = getContext("2d");

            for (var i = Math.floor(pos.y / 256); i <= (pos.y + canvas.height) / 256; ++i) {
                for (var j = Math.floor(pos.x / 256); j <= (pos.x + canvas.width) / 256; ++j) {
                    ctx.drawImage('image://a/' + i + '/' + j,
                                  256*j - Math.floor(pos.x),
                                  256*i - Math.floor(pos.y),
                                  256, 256);
                }
            }
        }

        onImageLoaded: requestPaint()

        onPosChanged: canvas.requestPaint()

        MouseArea {
            id: ma
            anchors.fill: parent
            property point lastPos: Qt.point(0, 0)

            onPressed: {
                lastPos = Qt.point(mouse.x, mouse.y)
            }

            onPositionChanged: {
                canvas.pos.x += lastPos.x - mouse.x
                canvas.pos.y += lastPos.y - mouse.y
                if (canvas.pos.y < 0) canvas.pos.y = 0;
                lastPos = Qt.point(mouse.x, mouse.y)
            }

            onWheel: {
                canvas.pos.x -= wheel.angleDelta.x
                canvas.pos.y -= wheel.angleDelta.y
                if (canvas.pos.y < 0) canvas.pos.y = 0;
            }
        }
    }
}
