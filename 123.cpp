
//radius = 1

void MainWindow::process(cv::Mat *image){
    std::vector<cv::Rect> faces;
    faceHaarCascade.detectMultiScale( *image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(70, 70) );

        for( int i = 0; i < faces.size(); i++ ) {

            cv::Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
            if (!isnorm){
                ellipse( *image, center, cv::Size( 150, 150), 0, 0, 360, cv::Scalar( 255, 255, 255 ), 4, 8, 0 );
            } else {
            ellipse( *image, center, cv::Size( radius*150, radius*150), 0, 0, 360, cv::Scalar( 0,100, 0 ), 4, 8, 0 );

            if (radius < 1.3){
                radius +=0.05;
            } else {
                radius = 0.8;
              }
              }
        }
}


