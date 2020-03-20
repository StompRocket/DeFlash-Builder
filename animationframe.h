#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include <QObject>
#include <QImage>
#include <QTableWidgetItem>

/**
 * @brief The AnimationFrame class describes a single frame in an animation.
 */
class AnimationFrame : public QObject
{
    Q_OBJECT
public:
    explicit AnimationFrame(int width = 640, int height = 480, QObject *parent = nullptr);
    explicit AnimationFrame(const AnimationFrame &frame, QObject *parent = nullptr);
    AnimationFrame &operator =(const AnimationFrame &frame);
    /**
     * @brief getIsBlank
     * @return true if the frame is blank, false otherwise.
     */
    bool getIsBlank();
    void resize(const QSize newSize);
    /**
     * @brief Call update after changes are made to the frame's underlying image
     *        in order to set its state to modified
     */
    void update();
    QImage image;
    QTableWidgetItem tableWidget;
    int getHeight() const;
    int getWidth() const;
    void clear();

private:
    bool blank = true;
    int height;
    int width;
};

#endif // ANIMATIONFRAME_H
