#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

// Fonction s pour calculer la valeur en fonction des pixels environnants
int s(int target, int current) {
    return (current - target) <= 0 ? 1 : 0;
}

// Fonction pour modifier l'image selon l'algorithme décrit
cv::Mat modifyImage(const cv::Mat& inputImage) {
    cv::Mat outputImage = inputImage.clone();

    // Parcourir chaque pixel de l'image (en excluant les pixels de bordure)
    for (auto y = 1; y < inputImage.rows - 1; ++y) {
        for (auto x = 1; x < inputImage.cols - 1; ++x) {
            auto sum = 0;

            // Parcourir le voisinage 3x3 autour du pixel courant
            for (auto dy = -1; dy <= 1; ++dy) {
                for (auto dx = -1; dx <= 1; ++dx) {
                    // Calculer la puissance de 2 en fonction de la distance par rapport au pixel central
                    auto power = std::abs(dy) + std::abs(dx);

                    // Ajouter la contribution du pixel à la somme
                    sum += std::pow(2, power) * s(inputImage.at<uchar>(y + dy, x + dx), inputImage.at<uchar>(y, x));
                }
            }

            // Mettre à jour la valeur du pixel dans l'image de sortie
            outputImage.at<uchar>(y, x) = cv::saturate_cast<uchar>(sum);
        }
    }

    return outputImage;
}

// Fonction pour calculer l'histogramme d'une image
std::vector<int> calculateHistogram(const cv::Mat& image) {
    // Créer un tableau pour stocker l'histogramme
    std::vector<int> histogram(256, 0);

    // Calculer l'histogramme
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            histogram[image.at<uchar>(y, x)]++;
        }
    }

    return histogram;
}

int main() {
    // Lire l'image d'entrée
    auto inputImage1 = cv::imread("1.4.05.tiff", cv::IMREAD_GRAYSCALE);
    if (inputImage1.empty()) {
        std::cerr << "Échec de lecture de l'image d'entrée." << std::endl;
        return -1;
    }

    // Modifier l'image
    auto outputImage1 = modifyImage(inputImage1);

    cv::imshow("Image de d'entrée", inputImage1);
    cv::imshow("Image de sortie", outputImage1);

    // Calculer l'histogramme
    std::vector<int> histogram = calculateHistogram(outputImage1);

    // Créer une image vide pour afficher l'histogramme
    cv::Mat histImage(400, 512, CV_8UC3, cv::Scalar(255, 255, 255));

    // Déterminer la largeur d'une barre d'histogramme
    int binWidth = histImage.cols / 256;

    // Trouver la valeur maximale dans l'histogramme pour normaliser l'affichage
    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    // Dessiner l'histogramme
    for (int i = 0; i < 256; ++i) {
        int binHeight = cvRound(static_cast<double>(histogram[i]) / maxCount * histImage.rows);
        cv::rectangle(histImage, cv::Point(i * binWidth, histImage.rows), cv::Point((i + 1) * binWidth, histImage.rows - binHeight), cv::Scalar(0, 0, 0), -1);
    }

    // Dessiner les axes
    cv::line(histImage, cv::Point(0, histImage.rows - 1), cv::Point(histImage.cols - 1, histImage.rows - 1), cv::Scalar(0, 0, 0));
    cv::line(histImage, cv::Point(0, 0), cv::Point(0, histImage.rows - 1), cv::Scalar(0, 0, 0));

    // Afficher l'histogramme
    cv::imshow("Histogramme", histImage);
    cv::waitKey(0);

    return 0;
}
