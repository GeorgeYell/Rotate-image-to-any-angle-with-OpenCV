#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

const double PI = atan(1) * 4;

void rotate(cv::Mat src, int degree)
{
    //угол поворота в радианах
    double a = degree * PI / 180.;

    //расчёт размеров нового изображения
    int newWidth = src.cols * fabs(cos(a)) + src.rows * fabs(cos(PI / 2 - a));
    int newHeight = src.cols * fabs(sin(a)) + src.rows * fabs(sin(PI / 2 - a));

    //объявление матрицы нового изображения
    cv::Mat output = cv::Mat(newHeight, newWidth, src.type());

            //расчёт полувысот для нового и старого изображения
    const int hwd = newHeight / 2,
              hhd = newWidth / 2,
              hws = src.cols / 2, 
              hhs = src.rows / 2,
             //расчёт радиуса вращения
              r = sqrt(hws * hws + hhs * hhs);

            //расёт угла наклона отрезка к оси оХ
    double b = atan2(1. * hhs, hws);

            //Цикл наполнения матрицы нового изображения
    for (int i = 0 - hwd; i < newWidth - hwd; i++)
    {
        for (int j = 0 - hhd; j < newHeight - hhd; j++)
        {
            // I и J - координаты точек исходной картинки
            int I = i * cos(a) - j * sin(a) + r * cos(b);
            int J = i * sin(a) + j * cos(a) + r * sin(b);

            // проверяем, не выходят ли точки за границы исходной картинки
            if (I < 2 * hws && I >= 0 && J < 2 * hhs && J >= 0)
                output.at<cv::Vec3b>(i + hwd, j + hhd) = src.at<cv::Vec3b>(I, J);
            else
                output.at<cv::Vec3b>(i + hwd, j + hhd) = cv::Vec3b(255, 255, 255);
        }
    }
    cv::imwrite("final.jpg", output); //сохраням изображение
    cv::imshow("Результат", output); // выводим результат
}

int main()
{
    setlocale(LC_ALL, "Rus");
    int degree;
    std::cout << "Программа для поворота изображения на произвольный угол\n";
    std::string imageName("M:/MjGyD/PROGRAMMS/openCV_test/guap.jpg");
    cv::Mat img = cv::imread(imageName); // открываем исходное изображение

    if (!img.data)
    {
        std::cout << "Не удалось открыть изображение!\n";
        cv::waitKey(0);
    }
    
    std::cout << "Введите на какой градус повернуть изображение: ";
    std::cin >> degree;
    cv::imshow("Оргигинальное изображение", img);
    rotate(img, degree);
    cv::waitKey(0);
}