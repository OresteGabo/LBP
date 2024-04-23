#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

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

int main() {
    // Lire l'image d'entrée
    auto inputImage1 = cv::imread("texmos2.s512.tiff", cv::IMREAD_GRAYSCALE);
    auto inputImage2 = cv::imread("texmos3.s512.tiff", cv::IMREAD_GRAYSCALE);
    auto inputImage3 = cv::imread("1.4.05.tiff", cv::IMREAD_GRAYSCALE);
    if (inputImage1.empty() || inputImage2.empty() || inputImage3.empty()) {
        std::cerr << "Échec de lecture de l'image d'entrée." << std::endl;
        return -1;
    }

    // Modifier les images
    auto outputImage1 = modifyImage(inputImage1);
    auto outputImage2 = modifyImage(inputImage2);
    auto outputImage3 = modifyImage(inputImage3);

    // Enregistrer les images de sortie
    cv::imwrite("outputImage1.jpg", outputImage1);
    cv::imwrite("outputImage2.jpg", outputImage2);
    cv::imwrite("outputImage3.jpg", outputImage3);

    // Afficher les images d'entrée et de sortie
    cv::imshow("Image d'entrée", inputImage3);
    cv::imshow("Image de sortie", outputImage3);
    cv::waitKey(0);

    return 0;
}
