import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 320
    height: 320
    title: 'Scroll'

    Component.onCompleted: {
        render.rule = 30
    }

    ColumnLayout {
        anchors.fill: parent
        Canvas {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: canvas
            smooth: false

            property point pos: Qt.point(768, 0)
            property real scale: 2
            property real size: 256 * scale

            onPaint: {
                var ctx = getContext("2d");
                var p = Qt.point(pos.x * scale, pos.y * scale);

                for (var i = Math.floor(p.y / size); i <= (p.y + canvas.height) / size; ++i) {
                    for (var j = Math.floor(p.x / size); j <= (p.x + canvas.width) / size; ++j) {
                        var uri = 'image://a/' + slider.changes + '/' + i + '/' + j;
                        ctx.drawImage(uri,
                                      size*j - Math.floor(p.x),
                                      size*i - Math.floor(p.y),
                                      size, size);
                    }
                }
            }

            onImageLoaded: requestPaint()

            onPosChanged: {
                canvas.requestPaint()
                console.log(pos)
            }

            MouseArea {
                id: ma
                anchors.fill: parent
                property point lastPos

                onPressed: {
                    lastPos = Qt.point(mouse.x, mouse.y)
                }

                onPositionChanged: {
                    canvas.pos.x += (lastPos.x - mouse.x) / canvas.scale
                    canvas.pos.y += (lastPos.y - mouse.y) / canvas.scale
                    if (canvas.pos.y < 0) canvas.pos.y = 0;
                    if (canvas.pos.x < 0) canvas.pos.x = 0;
                    lastPos = Qt.point(mouse.x, mouse.y)
                }

                onWheel: {
                    if (wheel.modifiers & Qt.ControlModifier) {
                        if (wheel.angleDelta.y > 0)
                            canvas.scale += 1;
                        else if (wheel.angleDelta.y < 0 && canvas.scale > 1)
                            canvas.scale -= 1;
                        canvas.requestPaint()
                    } else {
                        canvas.pos.x -= wheel.angleDelta.x / canvas.scale
                        canvas.pos.y -= wheel.angleDelta.y / canvas.scale
                        if (canvas.pos.y < 0) canvas.pos.y = 0;
                        if (canvas.pos.x < 0) canvas.pos.x = 0;
                    }
                }
            }
        }
        RowLayout {
            height: 40
            Slider {
                id: slider
                Layout.fillWidth: true
                from: 0
                to: 128
                stepSize: 1
                live: true
                focus: true
                property int changes: 0

                onValueChanged: {
                    changes += 1
                    canvas.requestPaint()
                }

                Component.onCompleted: render.rule = Qt.binding(function() { return value })

            }
            Text {
                Layout.minimumWidth: 25
                text: slider.value
            }
            Switch {
                onCheckedChanged: {
                    slider.changes += 1
                    render.random = checked
                    canvas.requestPaint()
                }
            }
        }
    }
}
