// main.cpp

#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QIcon>
#include "preset.h"
#include "stereomaker.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // --- CLI mode ---
    if (argc == 4) {
        QString depthPath   = argv[1];
        QString patternPath = argv[2];
        QString outputPath  = argv[3];

        // 1) Load & validate
        if (!QFile::exists(depthPath) || !QFile::exists(patternPath)) {
            qWarning() << "Error: input file not found.";
            return 1;
        }
        QImage depthMap(depthPath);
        QImage pattern (patternPath);
        if (depthMap.isNull() || pattern.isNull()) {
            qWarning() << "Error: failed to load images.";
            return 1;
        }

        // 2) Match GUI preset defaults
        Preset preset("CLI Preset");
        preset.setDotsPerInch     (150);
        preset.setObserverDistance(20.0f);
        preset.setEyeSeperation   (2.5f);
        preset.setMaximumDepth    (9.0f);
        preset.setMinimumDepth    (5.0f);
        preset.setIsParallel      (true);

        // 3) Hard-coded GUI slider values
        const float composeHeight = 0.1f;  // same as GUI “Compose 3D Height”
        const float composeScale  = 1.0f;  // same as GUI “Compose Scale”

        // 4) Convert depth map to 8-bit indexed using GUI’s gray palette
        depthMap = depthMap.convertToFormat(
            QImage::Format_Indexed8,
            StereoMaker::getGrayScale()
        );

        // 5) Scale depth map to result size (width × height from preset)
        depthMap = depthMap.scaled(
            preset.getResultWidth(),
            preset.getResultHeight()
        );

        // 6) Prepare “compose” image just like the GUI
        QImage composeImage = pattern;
        //   apply composeScale (even if ==1.0)
        composeImage = composeImage.scaled(
            int(composeImage.width()  * composeScale),
            int(composeImage.height() * composeScale),
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
        );
        composeImage = composeImage.convertToFormat(
            QImage::Format_Indexed8,
            StereoMaker::getGrayScale()
        );

        // 7) Run the composeDepth step
        StereoMaker maker;
        //maker.composeDepth(depthMap, composeImage, composeHeight);

        // 8) Final render (nil progress bar / helpers)
        QImage result = maker.render(
            depthMap,
            pattern,
            &preset,
            nullptr, nullptr, nullptr,
            false, false
        );

        // 9) Save and exit
        if (!result.save(outputPath)) {
            qWarning() << "Error: failed to write output.";
            return 1;
        }
        qDebug() << "Stereogram written to" << outputPath;
        return 0;
    }

    // --- GUI fallback ---
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/stereograma.svg"));
    QCoreApplication::setOrganizationName("Kapandaria");
    QCoreApplication::setApplicationName   ("Stereograma");
    MainWindow w;
    w.show();
    return a.exec();
}
